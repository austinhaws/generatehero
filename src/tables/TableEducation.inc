<?php
namespace Heroes\tables;

use Heroes\engine\Engine;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\enums\SkillPrograms;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

class TableEducation
{
    const HIGH_SCHOOL_GRADUATE = 'High School Graduate';
    const MILITARY = 'Military';
    const TRADE_SCHOOL = 'Trade School';
    const ONE_YEAR_OF_COLLEGE = 'One Year of College';
    const TWO_YEARS_OF_COLLEGE = 'Two Years of College';
    const THREE_YEARS_OF_COLLEGE = 'Three Years of College';
    const FOUR_YEARS_OF_COLLEGE = 'Four Years of College';
    const MILITARY_SPECIALIST = 'Military Specialist';
    const BACHELOR_DEGREE = 'Bachelor\'s Degree (College)';
    const MASTER_DEGREE = 'Master\'s Degree (College)';
    const DOCTORATE_DEGREE = 'Doctorate or PhD (College)';


    private $engine;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * add skill program(s) to hero;
     *
     * @param $percentBonus int how much of a bonus to give all skills selected for this program
     * @param $numberPrograms int how many to choose
     * @param $hero Hero here he is to save the day
     */
    private function pickPrograms($percentBonus, $numberPrograms, Hero &$hero)
    {
        if ($hero->educationLevel == TableEducation::HIGH_SCHOOL_GRADUATE) {
            $programs = [
                SkillPrograms::COMPUTER,
                SkillPrograms::DOMESTIC,
                SkillPrograms::PHYSICAL,
                SkillPrograms::LANGUAGE,
                SkillPrograms::TECHNICAL,
                SkillPrograms::WP_ANCIENT_WEAPONS,
            ];
        } else {
            // possible programs
            $programs = [
                SkillPrograms::COMMUNICATIONS,
                SkillPrograms::COMPUTER,
                SkillPrograms::DOMESTIC,
                SkillPrograms::ELECTRICAL,
                SkillPrograms::ESPIONAGE,
                SkillPrograms::JOURNALIST_INVESTIGATION,
                SkillPrograms::LANGUAGE,
                SkillPrograms::MECHANICAL,
                SkillPrograms::MEDICAL,
                SkillPrograms::MILITARY,
                SkillPrograms::PHYSICAL,
                SkillPrograms::SCIENCE,
                SkillPrograms::TECHNICAL,
                SkillPrograms::WP_ANCIENT_WEAPONS,
                SkillPrograms::WP_MODERN_WEAPONS,
            ];

            // advanced pilot
            switch ($hero->educationLevel) {
                case TableEducation::MILITARY:
                case TableEducation::MILITARY_SPECIALIST:
                case TableEducation::TRADE_SCHOOL:
                case TableEducation::DOCTORATE_DEGREE:
                    $programs[] = SkillPrograms::PILOT_ADVANCED;
                break;

                default:
                    // nope, don't get it
                    break;
            }

            // military
            switch ($hero->educationLevel) {
                case TableEducation::MILITARY:
                case TableEducation::MILITARY_SPECIALIST:
                case TableEducation::TRADE_SCHOOL:
                    $programs[] = SkillPrograms::MILITARY;
                break;

                default:
                    // nope, don't get it
                    break;
            }
        }

        $this->engine->arrayTools->shuffle($programs);

        // don't double pick a program
        $numberPicked = 0;
        while (count($programs) && $numberPicked < $numberPrograms) {
            $program = array_pop($programs);
            if (!in_array($program, $hero->educationProgramsPicked)) {
                $this->engine->skillPrograms->addSkillsForProgram($program, $percentBonus, $hero);
                $numberPicked++;
                $hero->educationProgramsPicked[] = $program;
            }
        }
    }


    /**
     * @param int $numberSkills many secondary skills to add
     * @param Hero $hero
     * @param string|bool $category limit to a specific category or falsey to allow any category
     * @throws \Exception unknown category
     */
    private function pickSecondarySkills($numberSkills, Hero &$hero, $category = false)
    {
        if ($category) {
            switch ($category) {
                case SkillPrograms::COMPUTER:
                    $skills = [BonusTargets::SKILL_COMPUTER_OPERATION,];
                    break;
                case SkillPrograms::DOMESTIC:
                    $skills = [
                        BonusTargets::SKILL_COOK,
                        BonusTargets::SKILL_DANCE,
                        BonusTargets::SKILL_FISH,
                        BonusTargets::SKILL_SEW,
                        BonusTargets::SKILL_SING,
                    ];
                    break;
                case SkillPrograms::ELECTRICAL:
                    $skills = [
                        BonusTargets::SKILL_BASIC_ELECTRONICS,
                    ];
                    break;
                case SkillPrograms::ESPIONAGE:
                    $skills = [
                        BonusTargets::SKILL_ESCAPE_ARTIST,
                        BonusTargets::SKILL_FORGERY,
                        BonusTargets::SKILL_LAND_NAVIGATION,
                        BonusTargets::SKILL_PICK_LOCKS,
                        BonusTargets::SKILL_PICK_POCKETS,
                        BonusTargets::SKILL_WILDERNESS_SURVIVAL,
                    ];
                    break;
                case SkillPrograms::MECHANICAL:
                    $skills = [
                        BonusTargets::SKILL_BASIC_MECHANICS,
                        BonusTargets::SKILL_AUTOMOTIVE_MECHANICS,
                    ];
                    break;
                case SkillPrograms::MEDICAL:
                    $skills = [
                        BonusTargets::SKILL_FIRST_AID,
                    ];
                    break;
                case SkillPrograms::PHYSICAL:
                    $skills = [
                        BonusTargets::SKILL_HAND_TO_HAND_BASIC,
                        BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS,
                        BonusTargets::SKILL_ATHLETICS,
                        BonusTargets::SKILL_BODY_BUILDING,
                        BonusTargets::SKILL_CLIMBING,
                        BonusTargets::SKILL_PROWL,
                        BonusTargets::SKILL_RUNNING,
                        BonusTargets::SKILL_SWIMMING,
                    ];
                    break;
                case SkillPrograms::PILOT:
                    $skills = [
                        BonusTargets::SKILL_PILOT_AUTOMOBILE,
                        BonusTargets::SKILL_PILOT_RACE_CAR,
                        BonusTargets::SKILL_PILOT_TRUCK,
                        BonusTargets::SKILL_PILOT_MOTORCYCLE,
                        BonusTargets::SKILL_PILOT_AIRPLANE_OLD_STYLE,
                        BonusTargets::SKILL_PILOT_HELICOPTER_BASIC,
                        BonusTargets::SKILL_PILOT_BOATS_MOTOR,
                        BonusTargets::SKILL_PILOT_BOATS_SAIL,
                    ];
                    break;
                case SkillPrograms::PILOT_RELATED_SKILLS:
                    $skills = [
                        BonusTargets::SKILL_NAVIGATION,
                        BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS,
                    ];
                    break;
                case SkillPrograms::SCIENCE:
                    $skills = [
                        BonusTargets::SKILL_MATHEMATICS_ADVANCED,
                    ];
                    break;
                case SkillPrograms::TECHNICAL:
                    $skills = [
                        BonusTargets::SKILL_ART,
                        BonusTargets::SKILL_LANGUAGE,
                        BonusTargets::SKILL_PHOTOGRAPHY,
                        BonusTargets::SKILL_WRITING,
                    ];
                    break;
                case SkillPrograms::WP_ANCIENT_WEAPONS:
                    $skills = [
                        BonusTargets::SKILL_WP_BLUNT,
                        BonusTargets::SKILL_WP_CHAIN,
                        BonusTargets::SKILL_WP_KNIFE,
                    ];
                    break;
                case SkillPrograms::WP_MODERN_WEAPONS:
                    $skills = [
                        BonusTargets::SKILL_WP_REVOLVER,
                        BonusTargets::SKILL_WP_AUTOMATIC_PISTOL,
                        BonusTargets::SKILL_WP_AUTOMATIC_RIFLE,
                        BonusTargets::SKILL_WP_SUB_MACHINEGUN,
                    ];
                    break;
                default:
                    throw new \Exception("Unknown skill category: $category");
            }
        } else {
            $skills = [
                BonusTargets::SKILL_COMPUTER_OPERATION,

                BonusTargets::SKILL_COOK,
                BonusTargets::SKILL_DANCE,
                BonusTargets::SKILL_FISH,
                BonusTargets::SKILL_SEW,
                BonusTargets::SKILL_SING,

                BonusTargets::SKILL_BASIC_ELECTRONICS,

                BonusTargets::SKILL_ESCAPE_ARTIST,
                BonusTargets::SKILL_FORGERY,
                BonusTargets::SKILL_LAND_NAVIGATION,
                BonusTargets::SKILL_PICK_LOCKS,
                BonusTargets::SKILL_PICK_POCKETS,
                BonusTargets::SKILL_WILDERNESS_SURVIVAL,

                BonusTargets::SKILL_BASIC_MECHANICS,
                BonusTargets::SKILL_AUTOMOTIVE_MECHANICS,

                BonusTargets::SKILL_FIRST_AID,

                BonusTargets::SKILL_HAND_TO_HAND_BASIC,
                BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS,
                BonusTargets::SKILL_ATHLETICS,
                BonusTargets::SKILL_BODY_BUILDING,
                BonusTargets::SKILL_CLIMBING,
                BonusTargets::SKILL_PROWL,
                BonusTargets::SKILL_RUNNING,
                BonusTargets::SKILL_SWIMMING,

                BonusTargets::SKILL_PILOT_AUTOMOBILE,
                BonusTargets::SKILL_PILOT_RACE_CAR,
                BonusTargets::SKILL_PILOT_TRUCK,
                BonusTargets::SKILL_PILOT_MOTORCYCLE,
                BonusTargets::SKILL_PILOT_AIRPLANE_OLD_STYLE,
                BonusTargets::SKILL_PILOT_HELICOPTER_BASIC,
                BonusTargets::SKILL_PILOT_BOATS_MOTOR,
                BonusTargets::SKILL_PILOT_BOATS_SAIL,

                BonusTargets::SKILL_NAVIGATION,
                BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS,

                BonusTargets::SKILL_MATHEMATICS_ADVANCED,

                BonusTargets::SKILL_ART,
                BonusTargets::SKILL_LANGUAGE,
                BonusTargets::SKILL_PHOTOGRAPHY,
                BonusTargets::SKILL_WRITING,

                BonusTargets::SKILL_WP_BLUNT,
                BonusTargets::SKILL_WP_CHAIN,
                BonusTargets::SKILL_WP_KNIFE,

                BonusTargets::SKILL_WP_REVOLVER,
                BonusTargets::SKILL_WP_AUTOMATIC_PISTOL,
                BonusTargets::SKILL_WP_AUTOMATIC_RIFLE,
                BonusTargets::SKILL_WP_SUB_MACHINEGUN,
            ];
        }

        $skills = $this->engine->skillPrograms->selectSkills($numberSkills, $hero, 0, $skills, false);
        foreach ($skills as $skill) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, $skill, 0, 'Secondary Skill'));
        }
    }

    /**
     * @param Hero $hero roll for and add education level (pg 27)
     * @throws \Exception if hero's education level is invalid
     */
    public function rollEducationLevel(Hero &$hero)
    {
        $hero->educationLevel = $this->engine->tableRoller->rollTable('Education Level', [
            new TableEntry(9, TableEducation::HIGH_SCHOOL_GRADUATE),
            new TableEntry(18, TableEducation::MILITARY),
            new TableEntry(27, TableEducation::TRADE_SCHOOL),
            new TableEntry(36, TableEducation::ONE_YEAR_OF_COLLEGE),
            new TableEntry(45, TableEducation::TWO_YEARS_OF_COLLEGE),
            new TableEntry(54, TableEducation::THREE_YEARS_OF_COLLEGE),
            new TableEntry(63, TableEducation::FOUR_YEARS_OF_COLLEGE),
            new TableEntry(72, TableEducation::MILITARY_SPECIALIST),
            new TableEntry(81, TableEducation::BACHELOR_DEGREE),
            new TableEntry(90, TableEducation::MASTER_DEGREE),
            new TableEntry(100, TableEducation::DOCTORATE_DEGREE),
        ]);

        // bonus is a one time bonus to skills taken from the programs
        switch ($hero->educationLevel) {
            case TableEducation::HIGH_SCHOOL_GRADUATE:
                $this->pickPrograms(5, 2, $hero);
                $this->pickSecondarySkills(10, $hero);
                break;

            case TableEducation::MILITARY:
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_WP_AUTOMATIC_RIFLE, 0, "{$hero->educationLevel} program"));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_HAND_TO_HAND_BASIC, 0, "{$hero->educationLevel} program"));

                $this->pickPrograms(10, 2, $hero);
                $this->pickSecondarySkills(8, $hero);
                break;

            case TableEducation::TRADE_SCHOOL:
                $this->pickPrograms(20, 2, $hero);
                $this->pickSecondarySkills(8, $hero);
                break;

            case TableEducation::ONE_YEAR_OF_COLLEGE:
                $this->pickPrograms(10, 2, $hero);
                $this->pickSecondarySkills(8, $hero);
                break;

            case TableEducation::TWO_YEARS_OF_COLLEGE:
                $this->pickPrograms(15, 2, $hero);
                $this->pickSecondarySkills(8, $hero);
                break;

            case TableEducation::THREE_YEARS_OF_COLLEGE:
                $this->pickPrograms(15, 3, $hero);
                $this->pickSecondarySkills(8, $hero);
                break;

            case TableEducation::FOUR_YEARS_OF_COLLEGE:
                $this->pickPrograms(20, 3, $hero);
                $this->pickSecondarySkills(10, $hero);
                break;

            case TableEducation::MILITARY_SPECIALIST:
                $this->pickPrograms(20, 1, $hero);

                // 20% bonus, pick skills from those lists
                $skills = array_merge(
                    $this->engine->skillPrograms->selectSkills(6, $hero, 20, BonusTargets::espionageSkills(false), false),
                    $this->engine->skillPrograms->selectSkills(4, $hero, 20, BonusTargets::weaponProficienciesSkills(false), false)
                );
                foreach ($skills as $skill) {
                    $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, $skill, 20, 'Secondary Skill'));
                }

                $this->pickSecondarySkills(8, $hero);
                break;

            case TableEducation::BACHELOR_DEGREE:
                $this->pickPrograms(25, 3, $hero);
                $this->pickSecondarySkills(10, $hero);
                break;

            case TableEducation::MASTER_DEGREE:
                $this->pickPrograms(30, 3, $hero);
                $this->pickSecondarySkills(10, $hero);
                break;

            case TableEducation::DOCTORATE_DEGREE:
                $this->pickPrograms(35, 4, $hero);
                $this->pickSecondarySkills(10, $hero);
                break;

            default:
                throw new \Exception("Unknown education level: {$hero->educationLevel}");
        }
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Education Level: ' . $hero->educationLevel, 'Education'));
    }
}