<?php
namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Ability;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

class Aliens extends BaseClass
{
    public $appearance;
    public $physiologicalModification;
    public $reasonForComing;
    public $familiarity;
    public $earthClothesDisguise;
    public $specialWeapon;
    public $vehicle;

    function imageName()
    {
        return 'aliens.png';
    }

    function create(Hero &$hero)
    {
        // all aliens have a base 20 SDC
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 20, 'Alien base SDC'));

        $this->rollAppearance($hero);

        $this->rollPhysiologicalModification($hero);

        $this->rollSuperabilities($hero);

        $this->rollEducation($hero);

        $this->rollReason($hero);

        $this->rollFamiliarity($hero);

        $this->rollEquipment($hero);

        $this->rollVehicle($hero);

        $this->rollMoney($hero);

    }

    private function rollMoney(Hero &$hero)
    {
        list($dice, $sides) = $this->engine->tableRoller->rollTable('Alien: Money Category', [
            new TableEntry(14, [1, 4]),
            new TableEntry(29, [1, 6]),
            new TableEntry(44, [2, 4]),
            new TableEntry(59, [3, 4]),
            new TableEntry(74, [4, 4]),
            new TableEntry(88, [4, 6]),
            new TableEntry(100, [6, 6]),
        ]);
        $money = $this->engine->roller->rollDice(new Roll('Alien: Money', $dice, $sides));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, $money * 1000, 'Alien: Money'));
    }

    private function rollVehicle(Hero &$hero)
    {
        $this->vehicle = $this->engine->tableRoller->rollTable('Alien: Vehicle', [
            new TableEntry(13, 'One-Man Hover Car - Maximum Speed: 160mph, SDC: 180; Hovers 3 to 12 feet above the ground'),
            new TableEntry(25, 'Two-Man Hover Car - Maximum Speed: 160mph, SDC: 240; Hovers 3 to 12 feet above the ground'),
            new TableEntry(37, 'Hover Cycle (2 or 4 person type) - Maximum Speed: 120mph, SDC: 130; hovers 3 to 20 feet above the ground'),
            new TableEntry(50, 'Hover Platform (round or square covers about a 4X4 foot area) - Maximum Speed: 90mph, SDC: 130; hovers 3 to 300ft above the ground, comfortably supports 2 people, but can hold up to four'),
            new TableEntry(62, 'Detachable, Flying Jet Pack - Maximum Speed: 90mph, SDC: 50; hovers 3 to 600ft above the ground, straps on to the person\'s back'),
            new TableEntry(74, 'Antigravity Disc - Maximum Speed: 90mph, SDC: 40, Maximum Weight Allowance: 1000lbs; Hovers 1 to 1200ft above the ground; Can attach to feet, back, or chest and are about the size of a standard dinner plate; Controlled by a simple hand control or by voice actuated computer'),
            new TableEntry(86, 'Antigravity Flight Ring or Medallion - Maximum Speed: 40mph, SDC: 8, Maximum Weight Allowance: 500lbs; Creates an anti-gravity field around the person'),
            new TableEntry(100, 'ATV Hover Vehicle - Maximum Speed: 140mph, SDC: 440; Hovers 3 to 12 feet above the ground; Large sedan sized hover vehicle holds up to five people, plus pilot, comfortably; Space and underwater flight also possible'),
        ]);
    }

    private function rollEquipment(Hero &$hero)
    {
        // clothes
        $this->earthClothesDisguise = $this->engine->roller->rollDice(new Roll('Alien: equipment', 1, 100)) <= 40 ? 'None' : 'Several suits of clothing';

        // special weapon
        $this->specialWeapon = $this->engine->tableRoller->rollTable('Alien: Special Weapon', [
            new TableEntry(18, 'Laser Rifle - Range: 1200ft; Damage: 6d6; 20 shot energy clip'),
            new TableEntry(29, 'Laser Pistol - Range: 135ft; Damage: 4D6; 12 shot energy clip'),
            new TableEntry(38, 'Stun Pistol - Range: 135ft; Damage: Temporarily short-circuits nervous system of its victim making him dazed; -10 to strike, parry, and dodge for 2D4 melees; 8 shot energy clip'),
            new TableEntry(49, 'Ion Blaster - Range 100ft; Damage 3D6; 20 shot energy clip'),
            new TableEntry(57, 'Plasma Ejector (large rifle or bazooka-looking weapon) - Range: 1200ft, Damage: 6D6 + 20; 10 shot energy clip'),
            new TableEntry(67, 'Sub-Machinegun type weapon (fires armor piercing projectile) - Range 600ft; Damage 4D6 per round; Feed: 30 round magazine'),
            new TableEntry(78, 'Mini-Laser (A small hand held rod about as big as a flashlight) - Range: 80ft, Damage: 2D6, 8 shot energy clip'),
            new TableEntry(89, 'Mini-Smoke Grenades (About the size of a silver dollar) - Range: Thrown about 90ft, Damage: cloud of smoke fills a 20X20ft area, all in smoke are -8 to strike, has 2D6 grenades'),
            new TableEntry(100, 'Mini-Explosive Grenades - Range: Thrown about 90ft, Damage 1D4 X 10, Effective casualty radius: 12ft, has 2D4 grenades'),
        ]);
    }

    private function rollFamiliarity(Hero &$hero)
    {
        $result = $this->engine->tableRoller->rollTable('Alien: Familiarity', [
            new TableEntry(20, 'none'),
            new TableEntry(60, 'some'),
            new TableEntry(100, 'studied'),
        ]);

        switch ($result) {
            case 'none':
                $this->familiarity = 'No familiarity with Earth\'s culture, science, or laws. However, can understand, speak, and write English quite well.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_LANGUAGE, 88, 'Alien: Familiarity - none'));
                break;

            case 'some':
                $this->familiarity = 'Some familiarity with Earth, its major nations, cultures, and laws. Can speak, read, and write four Earth languages.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_LANGUAGE, 90, 'Alien: Familiarity - some'));
                break;

            case 'studied':
                $this->familiarity = 'Has studied Earth intensely and is as knowledgeable as a well-informed native human. Can speak, read and write six different Earth languages fluently.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_LANGUAGE, 98, 'Alien: Familiarity - studied'));
                break;

            default:
                throw new \Exception("Unknown familiarity: $result");
        }
    }

    private function rollReason(Hero &$hero)
    {
        $result = $this->engine->tableRoller->rollTable('Alien: Reason for Coming', [
            new TableEntry(19, 'last of race'),
            new TableEntry(38, 'crash landed'),
            new TableEntry(55, 'outcast'),
            new TableEntry(70, 'intergalactic champion'),
            new TableEntry(85, 'glory hound'),
            new TableEntry(100, 'study earth'),
        ]);

        switch ($result) {
            case 'last of race':
                $reason = $this->engine->tableRoller->rollTable('Alien: last of race', [
                    new TableEntry(25, 'earth reminds him of him.'),
                    new TableEntry(50, 'it\'s a nice place; likes the planet.'),
                    new TableEntry(75, 'to save mankind from itself.'),
                    new TableEntry(100, 'crash landed; no hope to salvage spaceship.'),
                ]);
                $this->reasonForComing = "Last of a race of people who has come to Earth because $reason";
                break;

            case 'crash landed':
                $reason = $this->engine->tableRoller->rollTable('Alien: crash landed!', [
                    new TableEntry(20, 'it\'s a barbaric, backwater world!'),
                    new TableEntry(40, 'it\'s a nice place, likes it here.'),
                    new TableEntry(60, 'reminds him of home.'),
                    new TableEntry(80, 'too primitive for his taste.'),
                    new TableEntry(100, 'undecided.'),
                ]);
                $this->reasonForComing = "Crash landed! Trapped on Earth, but will try to make the best of things. Spaceship is destroyed. Feelings about earth are $reason";
                break;

            case 'outcast':
                $reason = $this->engine->tableRoller->rollTable('Alien: outcast', [
                    new TableEntry(20, 'it is more primitive and life should be easy.'),
                    new TableEntry(40, 'to be free of his world\'s prejudice and persecution.'),
                    new TableEntry(60, 'it\'s a nice place and he likes it here.'),
                    new TableEntry(80, 'to hide from his people who might seek him out for punishment.'),
                    new TableEntry(100, 'lost, and this seemed as good a planet as any to settle on.'),
                ]);
                $this->reasonForComing = "Outcast! A fugitive from his own world. Has selected Earth as his new home because $reason";
                break;

            case 'intergalactic champion':
                $reason = $this->engine->tableRoller->rollTable('Alien: Champion', [
                    new TableEntry(20, 'Earth needs guidance and direction if it is to blossom in to a productive member of the intergalactic community.'),
                    new TableEntry(40, 'it caught his eye and seemed like a worthy cause. Likes Earth and its people.'),
                    new TableEntry(60, 'he likes the planet and its people. Tends to be very paternal about his adopted world.'),
                    new TableEntry(80, 'he was assigned to Earth. Finds humans to be very interesting, but has not yet decide if he likes them or not.'),
                    new TableEntry(100, 'he was assigned to Earth. Finds its people primitive, aggressive, unfriendly, crude, and generally beneath him. The alien tends to be rude, arrogant, and condescending toward most "inferior" humans. But he does his job the best he can.'),
                ]);
                $this->reasonForComing = "Intergalactic Champion of Justice. Has come to protect the Earth because $reason";
                break;

            case 'glory hound':
                $this->reasonForComing = 'Glory Hound who chose Earth to get fame and fortune. Since Earth is a bit more primitive than the alien\'s homeworld, it seemed like an idea, easy opportunity. While hte alien views Earth as "inferior", it does not mean he dislikes Earth. It\'s just that he and his world are superior. This character is friendly, sincere, and gung-ho, but also a condescending, arrogant braggart, and show-off.';
                break;

            case 'study earth':
                $this->reasonForComing = 'Came to study Earth and could not help getting emotionally involved. The alien likes the Earth very much and strives to become a champion of the people.';
                break;

            default:
                throw new \Exception("Unknown Alien Reason: $result");
        }
    }

    const GENERAL_STUDIES = 'General Studies';
    const MILITARY_SPECIALIST = 'Military Specialist';
    const SCIENCE_SPECIALIST = 'Science Specialist';
    const COMBAT_SPECIALIST = 'Combat Specialist';
    const ENGINEER = 'Engineer';
    private function rollEducation(Hero &$hero)
    {
        $skills = [];
        $secondarySkills = [];
        $skillBonus = 0;
        $secondarySkillBonus = 0;

        $educationLevel = $this->engine->tableRoller->rollTable('Alien Education', [
            new TableEntry(20, Aliens::GENERAL_STUDIES),
            new TableEntry(40, Aliens::MILITARY_SPECIALIST),
            new TableEntry(60, Aliens::SCIENCE_SPECIALIST),
            new TableEntry(80, Aliens::COMBAT_SPECIALIST),
            new TableEntry(100, Aliens::ENGINEER),
        ]);

        switch ($educationLevel) {
            case Aliens::GENERAL_STUDIES:
                $skills = $this->engine->skillPrograms->selectSkills(2, $hero, 5, BonusTargets::scienceSkills(false), false);
                $secondarySkills = $this->engine->skillPrograms->selectSkills(12, $hero, 5, BonusTargets::allSkills(true), $skills);
                $skillBonus = 5;
                $secondarySkillBonus = 5;
                break;

            case Aliens::MILITARY_SPECIALIST:
                $skillBonus = $this->engine->roller->rollDice(new Roll('Alien Military Specialist Skill Bonus', 1, 20));
                $secondarySkillBonus = 0;
                $skills = array_merge(
                    $this->engine->skillPrograms->selectSkills(5, $hero, $skillBonus, array_merge(BonusTargets::espionageSkills(false), BonusTargets::militarySkills(false)), false),
                    $this->engine->skillPrograms->selectSkills(1, $hero, $skillBonus, BonusTargets::handToHandSkills(false), false),
                    $this->engine->skillPrograms->selectSkills(3, $hero, $skillBonus, BonusTargets::physicalSkills(false), false),
                    $this->engine->skillPrograms->selectSkills(4, $hero, $skillBonus, BonusTargets::weaponProficienciesSkills(false), false)
                );
                $secondarySkills = $this->engine->skillPrograms->selectSkills(4, $hero, 0, BonusTargets::allSkills(true), $skills);
                break;

            case Aliens::SCIENCE_SPECIALIST:
                $skillBonus = $this->engine->roller->rollDice(new Roll('Alien Science Specialist Skill Bonus', 1, 20));
                $secondarySkillBonus = 0;
                // give computer op / read sense so that picking skills doesn't reselect these
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_COMPUTER_OPERATION, 0, 'Alien Science Specialist'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS, 0, 'Alien Science Specialist'));
                $skills = array_merge(
                    $this->engine->skillPrograms->selectSkills(2, $hero, $skillBonus, BonusTargets::communicationSkills(false), false),
                    $this->engine->skillPrograms->selectSkills(3, $hero, $skillBonus, BonusTargets::scienceSkills(false), false),
                    $this->engine->skillPrograms->selectSkills(2, $hero, $skillBonus, BonusTargets::medicalSkills(false), false),
                    $this->engine->skillPrograms->selectSkills(2, $hero, $skillBonus, BonusTargets::physicalSkills(false), false)
                );
                $secondarySkills = $this->engine->skillPrograms->selectSkills(5, $hero, $skillBonus, array_merge(BonusTargets::allSkills(5)), $skills);
                break;

            case Aliens::COMBAT_SPECIALIST:
                $skillBonus = 15;
                $secondarySkillBonus = 15;
                $handToHand = array_merge(
                    $this->engine->skillPrograms->selectSkills(1, $hero, $skillBonus, BonusTargets::handToHandSkills(false), false),
                    [BonusTargets::SKILL_FIRST_AID, ]
                );

                $skills = array_merge(
                    $handToHand,
                    $this->engine->skillPrograms->selectSkills(5, $hero, $skillBonus, BonusTargets::physicalSkills(false), $handToHand),
                    $this->engine->skillPrograms->selectSkills(6, $hero, $skillBonus, BonusTargets::weaponProficienciesSkills(false), $handToHand)
                );
                $secondarySkills = $this->engine->skillPrograms->selectSkills(6, $hero, $secondarySkillBonus, BonusTargets::allSkills(true), $skills);
                break;

            case Aliens::ENGINEER:
                $skillBonus = 20;
                $secondarySkillBonus = 0;

                $skills = $this->engine->skillPrograms->selectSkills(6, $hero, $skillBonus, array_merge(
                    BonusTargets::electricalSkills(false),
                    BonusTargets::mechanicalSkills(false),
                    BonusTargets::computerSkills(false)
                ), false);
                $skills = array_merge($skills, $this->engine->skillPrograms->selectSkills(2, $hero, $skillBonus, BonusTargets::scienceSkills(false), $skills));
                $skills = array_merge($skills, $this->engine->skillPrograms->selectSkills(1, $hero, $skillBonus, BonusTargets::communicationSkills(false), $skills));

                $secondarySkills = $this->engine->skillPrograms->selectSkills(8, $hero, $secondarySkillBonus, BonusTargets::allSkills(true), $skills);
                break;

            default:
                throw new \Exception('Unknown Alien Education');
        }


        $reason = "Alien Education: $educationLevel";
        $hero->educationLevel = $reason;
        foreach ($skills as $skill) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, $skill, 0, $reason));
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, $skill, $skillBonus, $reason));

            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, $secondarySkills, 0, $reason));
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, $skill, $secondarySkillBonus, $reason));
        }
    }

    private function rollSuperabilities(Hero &$hero)
    {
        $abilities = $this->engine->tableRoller->rollTable('Alien: Super Abilities', [
            new TableEntry(49, 'Super Abilities'),
            new TableEntry(60, 'Psionics'),
            new TableEntry(69, 'Experiment'),
            new TableEntry(79, 'Robotics'),
            new TableEntry(89, 'Mystic - wizard/spells only'),
            new TableEntry(100, 'Bionics'),
        ]);
        switch ($abilities) {
            case 'Super Abilities':
// TODO: echo "Alien superabilities: $abilities (pg 56)\n";
                break;
            default:
// TODO: echo "do alien abilities: $abilities";
        }
    }

    private function rollPhysiologicalModification(Hero &$hero)
    {
        // physiological modification
        $result = $this->engine->tableRoller->rollTable('Alien: Physiological', [
            new TableEntry(15, 'High Gravity'),
            new TableEntry(29, 'Low Gravity'),
            new TableEntry(44, 'High Radiation'),
            new TableEntry(58, 'Frozen World'),
            new TableEntry(73, 'Thermo World'),
            new TableEntry(88, 'Twilight Word'),
            new TableEntry(100, 'Abrasive Atmosphere'),
        ]);
        switch ($result) {
            case 'High Gravity':
                $this->physiologicalModification = 'High Gravity: The gravitational force of the alien\'s homeworld was considerably greater than Earth\'s. This has given the alien a greater mass and physical endurance, but he is much faster and lighter on our planet Earth than on his homeworld. Short in height.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, $this->engine->roller->rollDice(new Roll('Alien: High Gravity - SDC', 3, 4)) * 10, 'Alien: High Gravity'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Alien: High Gravity - PS', 2, 4), 'Alien: High Gravity'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::ATTRIBUTE_SPEED, 2, 'Alien: High Gravity'));
                break;

            case 'Low Gravity':
                $this->physiologicalModification = 'Low Gravity: The alien\'s homeworld had a much lighter gravity than Earth\'s. This has made the alien much taller than a typical human. Although the increased gravitational pull of our planet Earth slows the alien, it also provides him with somehwat greater mass.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, $this->engine->roller->rollDice(new Roll('Alien: Low Gravity - SDC', 1, 4)) * 10, 'Alien: Low Gravity'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Alien: Low Gravity - PS', 2, 4), 'Alien: Low Gravity'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::ATTRIBUTE_SPEED, .5, 'Alien: Low Gravity'));
                break;

            case 'High Radiation':
                $this->physiologicalModification = 'High Radiation: Constant exposure to radiation has made the alien impervious to the effects of radiation levels that would normally kill a human. Unfortunately, the alien radiates low levels of radioactivity that could harm humans if exposed to him for a few weeks. Consequently, the alien must wear a radiation proof suit to protect human allies. Tall in height.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, $this->engine->roller->rollDice(new Roll('Alien: High Radiation - SDC', 1, 4)) * 10, 'Alien: High Radiation'));
                $hero->addAbility(new Ability('See Ultraviolet', 'Can see in to the ultraviolet range of light.'));
                break;

            case 'Frozen World':
                $this->physiologicalModification = 'Frozen World: Extremely low temperatures and arctic conditions ravage this world. As a result, the alien can withstand deadly cold, ice, and harsh frozen environments. The alien can not tolerate war temperatures, like a steamy 35° Fahrenheit. Thus, he must always wear a protective insulated suit, with a special refrigerator unit.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 40, 'Alien: Frozen World'));
                $hero->addAbility(new Ability('Impervious: Cold', 'Impervious to even deadly cold.'));
                break;

            case 'Thermo World':
                $this->physiologicalModification = 'Thermo World: The alien\'s homeworld makes a sauna feel cool. Must wear a protective suit with a heating unit. The alien can not tolerate any temperature below 98° Fahrenheit.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Alien: ThermoWorld'));
                $hero->addAbility(new Ability('Impervious: Heat and Fire', 'Impervious to heat and fire.'));

                break;

            case 'Twilight Word':
                $this->physiologicalModification = 'Twilight World: An extremely dark, night-like world, which makes the alien extremely sensitive to light and dark. While the alien can see well in darkness, light more than 60 watts is considered bright and 100 watts blinding. Protective, photosensitive visor or goggles must be worn to see in the light. Very short in height.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 10, 'Alien: Twilight World'));
                $hero->addAbility(new Ability('Nightvision', 'Nightvision - 600ft. Sensitive hearing'));
                break;

            case 'Abrasive Atmosphere':
                $this->physiologicalModification = 'Abrasive Atmosphere: High scathing winds or corrosive atmosphere is this alien\'s natural environment. This being has developed a tough thick skin or leathery plating like a rhinoceros. Short in height';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, $this->engine->roller->rollDice(new Roll('Alien: Abrasive - SDC', 3, 6)) * 10, 'Alien: Abrasive Atmosphere'));
                $hero->setNaturalArmor(12);
                break;

            default:
                throw new \Exception("Unknown Physiological Modification: $result");
        }

    }

    private function appearanceHumanoid(Hero &$hero)
    {
        $this->appearance = 'Humanoid: ';

        $characteristic = $this->engine->tableRoller->rollTable('Alien Characteristic', [
            new TableEntry(16, 'Pointy larger than normal ears'),
            new TableEntry(39, 'Odd skin color'),
            new TableEntry(43, 'Ambidextrous'),
            new TableEntry(48, 'Odd hair color'),
            new TableEntry(53, 'Double-Jointed'),
            new TableEntry(58, 'Unusual Eyes'),
            new TableEntry(64, 'Extreme amount of body hair'),
            new TableEntry(68, 'Prehensile feet/toes'),
            new TableEntry(72, 'Scaly skin'),
            new TableEntry(76, 'No body hair'),
            new TableEntry(79, 'Small horns'),
            new TableEntry(84, 'Tough, lumpy skin'),
            new TableEntry(89, 'Prehensile tail'),
            new TableEntry(94, 'Retractable claws'),
            new TableEntry(100, 'Stocky'),
        ]);

        switch ($characteristic) {
            case 'Pointy, larger than normal ears':
                $this->appearance .= $characteristic;
                break;

            case 'Odd skin color':
                $color = $this->engine->tableRoller->rollTable('Characteristic: Skin Color', [
                    new TableEntry(10, 'Yellow'),
                    new TableEntry(20, 'Green'),
                    new TableEntry(30, 'Red'),
                    new TableEntry(40, 'Grey'),
                    new TableEntry(50, 'Light Blue'),
                    new TableEntry(60, 'Stark White'),
                    new TableEntry(70, 'Dark Blue'),
                    new TableEntry(80, 'Black (as in coal black)'),
                    new TableEntry(90, 'Purple'),
                    new TableEntry(100, 'Orange'),
                ]);
                $this->appearance .= "Odd skin color - $color";
                break;

            case 'Ambidextrous':
                $this->appearance .= "$characteristic - Can use the right and left hand with equal skill and dexterity.";
                $bonusReason = 'Alien: ambidextrous';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, $bonusReason));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, $bonusReason));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 10, $bonusReason));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_ESCAPE_ARTIST, 5, $bonusReason));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PICK_LOCKS, 5, $bonusReason));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_MECHANICAL_ENGINEERING, 5, $bonusReason));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_ELECTRICAL_ENGINEER, 5, $bonusReason));
                break;

            case 'Odd hair color':
                $color = $this->engine->tableRoller->rollTable('Characteristic: Hair Color', [
                    new TableEntry(10, 'Green'),
                    new TableEntry(20, 'Light Blue'),
                    new TableEntry(30, 'White Streaked'),
                    new TableEntry(40, 'Bright, Flame Red'),
                    new TableEntry(50, 'Stark White'),
                    new TableEntry(60, 'Bright Yellow'),
                    new TableEntry(70, 'Metallic Silver'),
                    new TableEntry(80, 'Dark Blue'),
                    new TableEntry(90, 'Purple'),
                    new TableEntry(100, 'Orange'),
                ]);
                $this->appearance .= "Odd hair color - $color";
                break;

            case 'Double-Jointed':
                $this->appearance .= 'Double-Jointed; Extremely limber bones and can twist and bend their bones in to normally impossible positions.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 2, 'Alien: Double-Jointed'));
                break;

            case 'Unusual Eyes':
                $color = $this->engine->tableRoller->rollTable('Characteristic: Unusual Eyes', [
                    new TableEntry(17, 'Very small'),
                    new TableEntry(34, 'Round'),
                    new TableEntry(55, 'Very large'),
                    new TableEntry(75, 'Odd color'),
                    new TableEntry(89, 'Very Elliptical'),
                    new TableEntry(100, 'Glowing'),
                ]);
                $this->appearance .= "Unusual Eyes - $color";
                break;

            case 'Extreme amount of body hair':
                $type = $this->engine->tableRoller->rollTable('Characteristic: Body Hair', [
                    new TableEntry(20, 'Very busy, full head of hair.'),
                    new TableEntry(40, 'Very hairy all over the boyd: head, arms, legs, chest, and back. Clearly human hair.'),
                    new TableEntry(60, 'Human hair all over the body, so thick that it resembles fur.'),
                    new TableEntry(80, 'Short fur covers most of body except face, feet, and hands'),
                    new TableEntry(100, 'Fur covers most of the body except face, bottom of feet, and palms of hands.'),
                ]);
                $this->appearance .= "Unusual Eyes - Extreme Body Hair: $type";
                break;

            case 'Prehensile feet/toes':
                $this->appearance .= 'Prehensile Feet/Toes: the feet greatly resemble a monkey\'s feet with long figer-like toes and thumb like appendage for grabbing and holding. The prehensile foot is not developed enough to throw an object or fire a gun but can easily pickup and hold/carry items, press buttons, untie rope, turn doorknobs, pull levers and even play the piano.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 30, 'Alien: Prehensile feet/toes'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 1, 'Alien: Prehensile feet/toes'));
                break;

            case 'Scaly skin':
                $this->appearance .= 'Scaly Skin: a tough, smooth, reptilian skin with small scales.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Alien: Prehensile feet/toes'));
                break;

            case 'No body hair':
                $this->appearance .= 'No body hair at all.';
                break;

            case 'Small horns':
                $this->appearance .= 'Small Horns protrude from forehead.';
                break;

            case 'Tough, lumpy skin':
                $this->appearance .= 'Tough, lumpy skin.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Alien: Tough Lumpy Skin'));
                break;

            case 'Prehensile tail':
                $this->appearance .= 'Prehensile Tail: Have grown an additional appendage: a tail. While it may be difficult to conceal it, it does have some advantages. Like the prehensile tail of a monkey it can seize and grasp. The tail cannot be sued to untie rope or string, nor fire a weapon. HOwever, it can be used to turn knobs, and press buttons. It is also possible to hold blunt objects and use them as a club. +1 to strike/parry with the tail.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 20, 'Prehensile Tail'));
                break;

            case 'Retractable claws':
                $this->appearance .= 'Retractable Claws: Claws like a cat in the fingers. The small claws do minimal damage (2D4 + Physical Strength).';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 10, 'Retractable Claws'));
                break;

            case 'Stocky':
                $this->appearance .= 'Stocky, exceptionally broad or husky person about twice as broad as a normal human.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Stocky: PS', 1, 4), 'Stocky'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Stocky: SDC', 4, 4), 'Stocky'));
                break;
        }
    }

    private function rollAppearance(Hero &$hero)
    {
        // appearance
        $appearance = $this->engine->tableRoller->rollTable('appearance', [
            new TableEntry(30, 'Human-Like'),
            new TableEntry(50, 'Humanoid'),
            new TableEntry(55, 'Insect Appearance'),
            new TableEntry(60, 'Humanoid Amphibian'),
            new TableEntry(65, 'Vegetation'),
            new TableEntry(70, 'Humanoid Reptilian'),
            new TableEntry(75, 'Humanoid Canine'),
            new TableEntry(80, 'Humanoid Avian'),
            new TableEntry(85, 'Humanoid Mineral'),
            new TableEntry(90, 'Humanoid Feline'),
            new TableEntry(95, 'Humanoid Ape'),
            new TableEntry(100, 'Humanoid Aquatic'),
        ]);

        switch ($appearance) {
            case 'Human-Like':
                $this->appearance = $appearance . ': A humanoid alien that so resembles humans as to be indistinguishable from Earth people.';
                break;

            case 'Humanoid':
                $this->appearanceHumanoid($hero);
                break;

            case 'Insect Appearance':
                $this->appearance = 'Insect Appearance: Large eyes, antennae, claw-like hands and feet, no body hair, exoskeleton. +1D6 Damage in Hand to Hand combat.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 100, 'Alien: Insect Appearance'));
                break;

            case 'Humanoid Amphibian':
                $this->appearance = 'Humanoid Amphibian: Soft, smooth skin; webbed hands and feet; semi-aquatic. Can hold breath up to 20 minutes. Skin color is green-brown-tan-yellow-blotchy.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_SWIMMING, 90, 'Alien: Humanoid Amphibian'));
                break;
            case 'Vegetation':
                $this->appearance = 'Vegetation: Composed of the same essence as earth plant-life. Various shades of green or yellow.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 40, 'Alien: Vegetation'));
                break;

            case 'Humanoid Reptilian':
                $this->appearance = 'Humanoid Reptilian: Lizard like features, leathery or scaly skin, little or no body hair, long fingers.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 40, 'Alien: Humanoid Reptilian'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 2, 'Alien: Humanoid Reptilian'));
                break;

            case 'Humanoid Canine':
                $this->appearance = 'Humanoid Canine: Dog-like features, body fur or extreme body hair, dark eyes.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Alien: Canine - PS', 1, 4), 'Alien: Humanoid Canine'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, new Roll('Alien: Canine - Speed', 1, 4), 'Alien: Humanoid Canine'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 10, 'Alien: Humanoid Canine'));
                break;

            case 'Humanoid Avian':
                $this->appearance = 'Humanoid Avian: Bird like features; large, round eyes, clawed feet and hands, feathers for hair, no or tiny useless wings (does 1d6 damage in hand to hand combat. Keen hearing.';
                break;

            case 'Humanoid Mineral':
                $this->appearance = 'Humanoid Mineral: Rocky or crystalline appearance. Natural body armor';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 180, 'Alien: Mineral'));
                break;

            case 'Humanoid Feline':
                $this->appearance = 'Humanoid Feline: Cat like features, bright oval eyes, fur covered body, pointy ears.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 2, 'Alien: Feline'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, 2, 'Alien: Feline'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 10, 'Alien: Feline'));
                break;

            case 'Humanoid Ape':
                $this->appearance = 'Humanoid Ape: Resembles an ape (no tail); long arms, fur covered or extremely hairy body';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Aline: Ape - PS', 1, 6), 'Alien: Ape'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 20, 'Alien: Ape'));
                break;

            case 'Humanoid Aquatic':
                $this->appearance = 'Humanoid Aquatic: Fish, dolphin, or whale; webbed feet and hands, smooth or scaly skin, blowhole or gills, no body hair, brightly colored.';
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_SWIMMING, 90, 'Alien: Aquatic'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 20, 'Alien: Aquatic'));
                break;

            default:
                throw new \Exception("Unknown Alien Appearance: $appearance");
        }

    }
}