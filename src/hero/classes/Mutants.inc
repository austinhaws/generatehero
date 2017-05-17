<?php
namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\enums\SkillPrograms;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\superabilities\TablePsionics;
use Heroes\tables\superabilities\TableSuperAbilities;
use Heroes\tables\TableEducation;

class Mutants extends BaseClass
{
    // has psionics?
    public $psionics;
    // how many isp points does I have?
    public $isp;

    // cause of mutation
    public $cause;
    public $wildEducationDescription;
    // organization sponsoring the mutation
    public $organization;
    public $organizationRelationship;
    // what makes me weird
    public $characteristics;

    public function postCreate(Hero &$hero)
    {
        parent::postCreate($hero);
        if ($this->psionics) {
            $this->isp = (new TablePsionics($this->engine))->mutantAlienISP($hero, $this->engine);
        }
    }


    /**
     * create a character's class
     *
     * @param Hero $hero the hero
     * @throws \Exception ya ya, whatever
     */
    public function create(Hero &$hero)
    {
        if ($this->engine->roller->rollDice(new Roll('Mutant Type', 1, 2)) === 1) {
            $this->createMutant($hero);
        } else {
            $this->createAnimalMutant($hero);
        }
    }

    private function organizationAnimalMutant()
    {
        $this->organization = $this->engine->tableRoller->rollTable('Mutant Animal: Organization', [
            new TableEntry(25, 'Biological Research Facility'),
            new TableEntry(45, 'Private Industry'),
            new TableEntry(50, 'Secret Medical Experiment Organization'),
            new TableEntry(55, 'Secret Criminal Organization'),
            new TableEntry(60, 'Secret Crime Fighting Organization'),
            new TableEntry(65, 'Secret Military Organization'),
            new TableEntry(70, 'Secret Espionage Organization'),
            new TableEntry(75, 'Secret Medical Research Organization'),
            new TableEntry(100, 'Military Organization'),
        ]);
    }

    private function createAnimalMutant(Hero &$hero)
    {
        $hero->SDCCalculated = true;

        // determine animal type - randomly choose from all types
        $this->causeAnimalMutant($hero);

        // includes education
        $this->organization = $this->organizationAnimalMutant();

        // do the BIO-E hard work
        $this->generateAnimalMutant();
    }

    private function applyMutantAnimalDetails(Hero &$hero, $details)
    {
        // set the education flag on the hero so they do not get double education
        $educationTable = new TableEducation($this->engine);

        // All skill bonuses apply only to skill programs, not Secondary skills.
        $numSkillPrograms = isset($details['skillPrograms']) ? $details['skillPrograms'] : false;
        $numSecondarySkills = isset($details['secondarySkills']) ? $details['secondarySkills'] : false;
        $skillBonus = isset($details['skillBonus']) ? $details['skillBonus'] : 0;
        $bonusHighSchoolCollegeSkills = isset($details['bonusHighSchoolCollegeSkills']) ? $details['bonusHighSchoolCollegeSkills'] : 0;
        if ($numSkillPrograms || $numSecondarySkills) {
            $hero->educationLevel = TableEducation::MUTANT_WILD_ANIMAL;
            if ($numSkillPrograms) {
                $educationTable->pickPrograms($skillBonus ? $skillBonus : $bonusHighSchoolCollegeSkills, $numSkillPrograms, $hero);
            }
            if ($numSecondarySkills) {
                $educationTable->pickSecondarySkills($numSecondarySkills, $hero, false, $bonusHighSchoolCollegeSkills);
            }

        }


        $numHighSchoolSkills = isset($details['highSchoolSkills']) ? $details['highSchoolSkills'] : false;
        if ($numHighSchoolSkills) {
            $educationTable->pickSecondarySkills($numHighSchoolSkills, $hero, SkillPrograms::HIGH_SCHOOL, $bonusHighSchoolCollegeSkills);
        }


        $skillPrograms = new SkillPrograms($this->engine);
        foreach ($details as $key => $value) {
            $skills = false;
            switch ($key) {
                case 'skillPrograms':
                case 'secondarySkills':
                case 'skillBonus':
                case 'wildAnimalEducation':
                    // already handled
                    break;

                case 'bonuses':
                    $hero->addBonus($value);
                    break;

                case 'physicalSkills':
                    $skills = $skillPrograms->skillsForProgram(SkillPrograms::PHYSICAL, $hero);
                    break;

                case 'militaryProgram':
                    $skillPrograms->addSkillsForProgram(SkillPrograms::MILITARY, 0, $hero);
                    break;

                case 'espionageProgram':
                    $skillPrograms->addSkillsForProgram(SkillPrograms::ESPIONAGE, 0, $hero);
                    break;

                case 'weaponProficiencies':
                    $skills = $skillPrograms->skillsForProgram(SkillPrograms::WEAPON_PROFICIENCIES, $hero);
                    break;

                case 'allHighSchoolSkills':
                    $skills = $skillPrograms->skillsForProgram(SkillPrograms::HIGH_SCHOOL, $hero);
                    break;

                case 'collegeSkills':
                    $skills = $skillPrograms->skillsForProgram(SkillPrograms::COLLEGE, $hero);
                    break;

                case 'bonusHighSchoolCollegeSkills':
                    $skills = array_merge(
                        $skills = $skillPrograms->skillsForProgram(SkillPrograms::HIGH_SCHOOL, $hero),
                        $skills = $skillPrograms->skillsForProgram(SkillPrograms::COLLEGE, $hero)
                    );
                    break;

                case 'militarySkills':
                    $skills = $skillPrograms->skillsForProgram(SkillPrograms::MILITARY, $hero);
                    break;

                case 'ancientOrNinjaWeaponProficiencies':
                    $skills = $skillPrograms->skillsForProgram(SkillPrograms::WP_ANCIENT_WEAPONS, $hero);
                    break;

                default:
                    throw new \Exception("Unknown animal mutant detail: $key  => $value");
            }

            if ($skills) {
                if ($value !== true && $value !== false) {
                    $skills = $skillPrograms->selectSkills($value, $hero, 0, $skills, false);
                }

                $skillPrograms->addSkills($hero, $skills, 0, 'Mutant Animal Education');
            }
        }
    }

    private function causeAnimalMutant(Hero &$hero)
    {
        list($this->cause, $education) = $this->engine->tableRoller->rollTable('Mutant Animal: Cause', [
            new TableEntry(14, ['Random Mutation: The animal just happened to come out like that.', 'wild']),
            new TableEntry(60, ['Accidental Encounter: Some \'strange stuff\' (radiation, energy, chemicals, biological, or other strangeness) causes the animals to mutate.', 'wild']),
            new TableEntry(60, ['Accidental Encounter: Some \'strange stuff\' (radiation, energy, chemicals, biological, or other strangeness) causes the animals to mutate.', 'wild']),
            new TableEntry(100, ['Deliberate Experimentation: Some kind of laboratory experiment is performed on the animal that causes the changes. The animal\'s structure or genetics were purposely altered for some purpose.', 'experiment']),
        ]);
        $details = [];
        if ($education === 'experiment') {
            list ($this->organizationRelationship, $details) = $this->engine->tableRoller->rollTable('Mutant Animal: organization relationship', [
                new TableEntry(10, ['Adopted and raised as one of a researcher\'s family. Still living in the home; mutually loves and is loved by family members. This character has been treated as a human and while some discrimination may have been experienced, the character will feel that humans are basically good.', [
                    'skillPrograms' => 2,
                    'secondarySkills' => 8,
                    'bonuses' => [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Adopted - wealth', 3, 6, 1000), 'Mutant Animal: Adopted')
                    ]
                ]]),

                new TableEntry(20, ['Raised in the home of a researcher as a pet. Still living in the home and fairly loyal to the family members. The character will resent humans somewhat, but will still attempt to find acceptance among mankind. Trained instead of educated.', [
                    'highSchoolSkills' => 3,
                    'secondarySkills' => 12,
                    'bonuses' => [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Raised - wealth', 1, 6, 1000), 'Mutant Animal: Raised')
                    ]
                ]]),

                new TableEntry(30, ['Raised in the home of a researcher as a pet. Escaped and hostile, but not hunted with deadly force. The character will be resentful of humans.', [
                    'wildAnimalEducation' => true,
                ]]),

                new TableEntry(40, ['Brought up as an experiment. Trained and educated with cruel punishments. The character will distrust humans. Now hunted by the organization.', [
                    'physicalSkills' => 6,
                    'secondarySkills' => 12,
                    'bonuses' => [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Experiment - wealth', 2, 6, 500), 'Mutant Animal: Raised')
                    ]
                ]]),

                new TableEntry(50, ['Raised as a caged, experimental animal. Character escaped and wants to destroy the organization, and has a strong distrust (and possibly hatred) of all humans.', [
                    'wildAnimalEducation' => true,
                ]]),

                new TableEntry(60, ['Educated and trained as if the character were a normal human. Character has good relationships and a balanced outlook on humans. Separated from the organization, but with a good relationship.', [
                    'skillPrograms' => 2,
                    'secondarySkills' => 8,
                    'skillBonus' => 10,
                    'bonuses' => [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Educated/Trained - wealth', 2, 6, 2000), 'Mutant Animal: Educated/Trained')
                    ]
                ]]),

                new TableEntry(70, ['Rescued from the organization and adopted by a friendly researcher at a young age. Raised while continuously being hunted by the organization. Character distrusts humans, but knows that there are some good people who deserve help and friendship.', [
                    'militaryProgram' => true,
                    'secondarySkills' => 10,
                    'skillBonus' => 5,
                    'bonuses' => [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Rescued - wealth', 2, 6, 200), 'Mutant Animal: Rescued')
                    ]
                ]]),

                new TableEntry(80, ['Highly trained and educated as a specialist using the character\'s natural abilities. The character feels equal or superior to most humans; no ill feelings. Character is a valuable employee of the organization and is paid at least triple the going rate.', [
                    'skillPrograms' => 3,
                    'secondarySkills' => 10,
                    'skillBonus' => 30,
                    'bonuses' => [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Highly Trained - wealth', 1, 6, 10000), 'Mutant Animal: Highly Trained')
                    ]
                ]]),

                new TableEntry(80, ['Highly trained as a specialist using the character\'s natural abilities. Character distrusts most humans. Hunted by law enforcement agencies and the organization. The character was treated as a slave and eventually escaped.', [
                    'skillPrograms' => 3,
                    'secondarySkills' => 14,
                    'skillBonus' => 15,
                    'bonuses' => [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Highly Trained Distrusting - wealth', 3, 6, 10000), 'Mutant Animal: Highly Trained Distrusting')
                    ]
                ]]),

                new TableEntry(100, ['Deliberately raised as assassins or warriors.', [
                    'espionageProgram' => true,
                    'militaryProgram' => true,
                    'weaponProficiencies' => 5,
                    'secondarySkills' => 8,
                    'skillBonus' => 20,
                    'bonuses' => [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Highly Trained Distrusting - wealth', 3, 6, 10000), 'Mutant Animal: Highly Trained Distrusting')
                    ]
                ]]),

            ]);
        }

        $this->applyMutantAnimalDetails($hero, $details);

        // do wild education
        if ($education === 'wild' || isset($details['wildAnimalEducation'])) {
            list($this->wildEducationDescription, $wildDetails) = $this->engine->tableRoller->rollTable('Mutant Animal: Wild Education', [
                new TableEntry(20, [
                    'Everything is self-taught, as the animal lives in the wild, with no help or assistance. Character mistrusts humans and other animals.',
                    [
                        'bonuses' => [
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PROWL, 24, 'Mutant Animal: Wild Education - self-taught'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_WILDERNESS_SURVIVAL, 24, 'Mutant Animal: Wild Education - self-taught'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_ESCAPE_ARTIST, 10, 'Mutant Animal: Wild Education - self-taught'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 15, 'Mutant Animal: Wild Education - self-taught'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_SWIMMING, 10, 'Mutant Animal: Wild Education - self-taught'),
                            new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::SDC, 1.1, 'Mutant Animal: Wild Education - self-taught'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 6, 'Mutant Animal: Wild Education - self-taught'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 3, 'Mutant Animal: Wild Education - self-taught'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 2, 'Mutant Animal: Wild Education - self-taught'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 2, 'Mutant Animal: Wild Education - self-taught'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Wild Education : self-taught - money', 3, 6, 100), 'Mutant Animal: Wild Education - self-taught'),
                        ],
                        'secondarySkills' => 1,
                    ]
                ]),
                new TableEntry(40, [
                    'By skulking around the fringes of society the character picks up a rudimentary education. The character probably has a small number of human friends, but distrusts people in general.',
                    [
                        'allHighSchoolSkills' => true,
                        'secondarySkills' => 12,
                        'bonuses' => [
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PROWL, 12, 'Mutant Animal: Wild Education - rudimentary'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 1, 'Mutant Animal: Wild Education - rudimentary'),
                            new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_HAND_TO_HAND_BASIC, 0, 'Mutant Animal: Wild Education - rudimentary'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Wild Education : rudimentary - money', 3, 6, 200), 'Mutant Animal: Wild Education - rudimentary'),
                        ],
                    ]
                ]),
                new TableEntry(90, [
                    'Adopted by a "mentor" who teaches and guides the character in some form of special training. These characters will learn to be philosophic about all creatures. Their attitude could be summed up as, some people are good, some are bad, everyone deserves a chance to earn your trust.',
                    [
                        'highSchoolSkills' => 5,
                        'militarySkills' => 3,
                        'collegeSkills' => 2,
                        'secondarySkills' => 6,
                        'ancientOrNinjaWeaponProficiencies' => 3,
                        'bonuses' => [
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS, 0, 'Mutant Animal: Wild Education - mentor'),
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Wild Education : mentor - money', 3, 6, 100), 'Mutant Animal: Wild Education - mentor'),
                        ],
                    ]
                ]),
                new TableEntry(100, [
                    'Character goes public and is educated at a major university. The character likes and trusts humanity in general.',
                    [
                        'highSchoolSkills' => 5,
                        'collegeSkills' => 10,
                        'secondarySkills' => 18,
                        'bonusHighSchoolCollegeSkills' => 27,
                        'bonuses' => [
                            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant Animal: Wild Education : public - money', 2, 6, 500), 'Mutant Animal: Wild Education - public'),
                        ],
                    ]
                ]),
            ]);
            $this->applyMutantAnimalDetails($hero, $wildDetails);
        }
    }

    private function createMutant(Hero &$hero)
    {
        // step 1 : attributes - already done by generator; education - normal education

        // step 2 : THE CAUSE OF THE MUTATION
        $this->causeHumanMutant();

        // step 3: UNUSUAL PHYSICAL CHARACTERISTICS
        $this->unusualCharacteristics();


        // mutants starting SDC & Cash
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Mutant'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant - Starting Money', 4, 4, 100), 'Mutant'));
        $this->hasCar($hero, 88);

        // determine super abilities / psionics
        if ($this->engine->roller->rollDice(new Roll('Mutant Abilities', 1, 2)) === 1) {
            (new TableSuperAbilities($this->engine))->randomSuperAbilities($hero);
        } else {
            $this->psionics = true;
            (new Psionics($this->engine))->createMutantAlien($hero);
        }
    }

    private function causeHumanMutant()
    {
        $this->cause = $this->engine->tableRoller->rollTable('Mutant: cause', [
            new TableEntry(20, 'An unknown, random element. A complete mystery.'),
            new TableEntry(40, 'Accidental encounter with \'strange stuff\'. This can be almost anything: industrial waste, chemicals, radiation, alien sub-stance, energy, or other strangeness.'),
            new TableEntry(60, 'Genetic aberration. Mutant gene structure (a million in one chance of fate) is responsible for the mutation and powers.'),
            new TableEntry(80, 'Deliberate Experimentation. Some kind of laboratory experiment that purposely mutates the individual.'),
            new TableEntry(100, 'Radiation. An unexplainable mutant transformation caused by exposure to some type of radiation (usually accidental). It is likely that the radiation itself is not the direct cause of the mutation, but triggers a mutating agent (probably genetic) which has laid dormant within the individual.'),
        ]);
    }

    private function unusualCharacteristics()
    {
        list($this->characteristics, $bonuses) = $this->engine->tableRoller->rollTable('Mutant: unusual', [
            new TableEntry(30, ['No unusual physical traits.', false]),
            new TableEntry(34, ['Pointy or larger than normal ears.', false]),
            new TableEntry(39, ['Odd skin color: yellow', false]),
            new TableEntry(40, ['Odd skin color: green', false]),
            new TableEntry(41, ['Odd skin color: red', false]),
            new TableEntry(42, ['Odd skin color: grey', false]),
            new TableEntry(43, ['Ambidextrous: Use the right and left hand with equal skill and dexterity.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Mutant: ambidextrous'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Mutant: ambidextrous'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 10, 'Mutant: ambidextrous'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_ESCAPE_ARTIST, 5, 'Mutant: ambidextrous'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PICK_LOCKS, 5, 'Mutant: ambidextrous'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SPECIAL_MECHANICAL_AND_ELECTRICAL_REPAIR, 5, 'Mutant: ambidextrous'),
            ]]),
            new TableEntry(48, ['Odd hair color: green', false]),
            new TableEntry(49, ['Odd hair color: light blue', false]),
            new TableEntry(50, ['Odd hair color: white streaked', false]),
            new TableEntry(51, ['Odd hair color: bright flame red', false]),
            new TableEntry(52, ['Odd hair color: stark white', false]),
            new TableEntry(53, ['Double-Jointed - has extremely limber joints and can twist and bend their bones into normally impossible positions. These contortions enable the character to collapse the bones in his hands to easily slip out of handcuffs or manacles, temporarily and painlessly dislocate joints to wiggle out of ropes, slip through small openings and fit into small areas.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 2, 'Mutant: Double-jointed'),
            ]]),

            new TableEntry(54, ['Unusual eyes: very small', false]),
            new TableEntry(55, ['Unusual eyes: round', false]),
            new TableEntry(56, ['Unusual eyes: very large', false]),
            new TableEntry(57, ['Unusual eyes: odd color', false]),
            new TableEntry(58, ['Unusual eyes: very elliptical', false]),

            new TableEntry(59, ['Extreme amount of body hair: very bushy, full head of hair', false]),
            new TableEntry(60, ['Extreme amount of body hair: very hairy all over the body', false]),
            new TableEntry(61, ['Extreme amount of body hair: human hair all over the body, so thick that it resembles fur', false]),
            new TableEntry(62, ['Extreme amount of body hair: fur; short, half inch length, covers most of body except face, feet, and hands', false]),
            new TableEntry(64, ['Extreme amount of body hair: fur covers most of the boyd except face, bottom of feet, and palms of hands', false]),

            new TableEntry(68, 'Prehensile Feet/Toes: The feet greatly resemble a monkey\'s feet, with long, finger-like toes, and thumb-like appendage for grabbing and holding.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 30, 'Mutant - Prehensile feet/toes'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 1, 'Mutant - Prehensile feet/toes'),
            ]),

            new TableEntry(72, ['Scaly Skin: A tough, smooth, reptilian skin with small scales', [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Mutant: Scaly Skin')]]),
            new TableEntry(76, ['No body hair', false]),
            new TableEntry(79, ['Small horns 1D4 inches long protruding from forehead', false]),
            new TableEntry(84, ['Tough lumpy skin', [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Mutant: tough lumpy skin')]]),
            new TableEntry(89, ['Prehensile tail - The tail could be monkey-like, devil-like, furry, flat, or anything the player or game master feels appropriate. The tail can seize and grasp.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Mutant: prehensile tail'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Mutant: prehensile tail'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 20, 'Mutant: prehensile tail'),
            ]]),

            new TableEntry(94, ['Retractable Claws, like a cat, in the fingers. The small claws do minimal damage; about equal to a knife 2D4 per each swipe.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 10, 'Mutant: Retractable Claws'),
            ]]),

            new TableEntry(100, ['Stocky, exceptionally broad or husky.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::WEIGHT, 50, 'Mutant: Stocky'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Mutant: Stocky - PS', 1, 4), 'Mutant: Stocky'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Mutant: Stocky - SDC', 4, 4), 'Mutant: Stocky'),
            ]]),

            new TableEntry(101, ['Odd skin color: light blue', false]),
            new TableEntry(102, ['Odd skin color: stark white', false]),
            new TableEntry(103, ['Odd skin color: dark blue', false]),
            new TableEntry(104, ['Odd skin color: coal black', false]),
            new TableEntry(105, ['Odd skin color: purple', false]),
            new TableEntry(106, ['Odd skin color: orange', false]),

            new TableEntry(107, ['Unusual eyes: glowing', false]),

            new TableEntry(108, ['Odd hair color: bright yellow', false]),
            new TableEntry(109, ['Odd hair color: metallic silver', false]),
            new TableEntry(110, ['Odd hair color: dark blue', false]),
            new TableEntry(111, ['Odd hair color: purple', false]),
            new TableEntry(112, ['Odd hair color: orange', false]),
        ]);
    }
}
