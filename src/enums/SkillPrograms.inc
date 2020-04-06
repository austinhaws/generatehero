<?php
namespace Heroes\enums;

use Heroes\engine\Engine;
use Heroes\engine\TableEntry;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\TableEducation;
use RuntimeException;

class SkillPrograms
{
    const COMMUNICATIONS = 'Communications';
    const COMPUTER = 'Computer';
    const DOMESTIC = 'Domestic';
    const ELECTRICAL = 'Electrical';
    const ESPIONAGE = 'Espionage';
    const JOURNALIST_INVESTIGATION = 'Journalist/Investigation';
    const LANGUAGE = 'Language';
    const MECHANICAL = 'Mechanical';
    const MEDICAL = 'Medical';
    const MILITARY = 'Military';
    const PHYSICAL = 'Physical';
    const PILOT_ADVANCED = 'Pilot Advanced';
    const SCIENCE = 'Science';
    const TECHNICAL = 'Technical';
    const WP_ANCIENT_WEAPONS = 'WP Ancient Weapons';
    const WP_MODERN_WEAPONS = 'WP Modern Weapons';

    // categories, not programs
    const PILOT = 'Pilot';
    const PILOT_RELATED_SKILLS = 'Pilot Related Skills';
    const WP_ENERGY_WEAPONS = 'WP Energy Weapons';
    const WEAPON_PROFICIENCIES = 'Weapon Proficiencies';
    const COLLEGE = "College";
    const HIGH_SCHOOL = "High School";
    const ALL_SKILLS = "All Skills";

    /** @var Engine one engine to rule them all */
    private $engine;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * given a possible list of skills, shuffle, and pick ones the character does not yet have
     *
     * @param $numberSkills int how many to select
     * @param $hero Hero the hero
     * @param $percentBonus int how much to set starting bonus, can add skills if their starting percent is less than this
     * @param $possibles array possible skill list
     * @param $impossibles array|bool skills that can't be selected (probably already selected or rules disallow); this is in addition to the skills already BONUS_SET in the hero's bonus list
     * @return array skills selected
     */
    public function selectSkills($numberSkills, $hero, $percentBonus, $possibles, $impossibles = false)
    {
        $this->engine->arrayTools->shuffle($possibles);

        $skills = [];
        while (count($possibles) && count($skills) < $numberSkills) {
            $skill = array_pop($possibles);
            if (!$hero->hasSkill($skill, $percentBonus, $this->engine) && (!$impossibles || false === array_search($skill, $impossibles))) {
                $skills[] = $skill;
            }
        }

        return $skills;
    }

    /**
     * get a list of skills for a program
     *
     * @param $program string the program, use SkillPrograms::... constants
     * @param $hero Hero the hero
     * @param int $percentBonus what bonus the skills will be at. when checking if a character has a skill, if the skill is a lower starting value then this would trump it
     * @return array skills available from the program
     */
    public function skillsForProgram($program, $hero, $percentBonus = 0) {
        switch ($program) {
            case SkillPrograms::COMMUNICATIONS:
                $skills = [
                    BonusTargets::SKILL_CRYPTOGRAPHY, BonusTargets::SKILL_LASER, BonusTargets::SKILL_OPTIC_SYSTEMS, BonusTargets::SKILL_RADIO_BASIC,
                    BonusTargets::SKILL_RADIO_SCRAMBLER, BonusTargets::SKILL_RADIO_SATELLITE, BonusTargets::SKILL_TV_VIDEO, BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS,];
                break;

            case SkillPrograms::COMPUTER:
                $skills = [BonusTargets::SKILL_COMPUTER_OPERATION, BonusTargets::SKILL_COMPUTER_PROGRAMMING,];
                break;

            case SkillPrograms::DOMESTIC:
                $skills = [BonusTargets::SKILL_COOK, BonusTargets::SKILL_DANCE, BonusTargets::SKILL_FISH, BonusTargets::SKILL_SEW, BonusTargets::SKILL_SING,];
                break;

            case SkillPrograms::ELECTRICAL:
                $skills = [BonusTargets::SKILL_ELECTRICAL_ENGINEER, BonusTargets::SKILL_SURVEILLANCE, BonusTargets::SKILL_COMPUTER_REPAIR, BonusTargets::SKILL_ROBOT_ELECTRONICS];
                break;

            case SkillPrograms::ESPIONAGE:
                $skills = [
                    BonusTargets::SKILL_CONCEALMENT, BonusTargets::SKILL_DETECT_AMBUSH, BonusTargets::SKILL_DETECT_CONCEALMENT, BonusTargets::SKILL_DISGUISE,
                    BonusTargets::SKILL_ESCAPE_ARTIST, BonusTargets::SKILL_FORGERY, BonusTargets::SKILL_INTELLIGENCE, BonusTargets::SKILL_IMPERSONATION,
                    BonusTargets::SKILL_INTERROGATION, BonusTargets::SKILL_LAND_NAVIGATION, BonusTargets::SKILL_PALMING, BonusTargets::SKILL_PICK_LOCKS,
                    BonusTargets::SKILL_PICK_POCKETS, BonusTargets::SKILL_SNIPER, BonusTargets::SKILL_TRACKING, BonusTargets::SKILL_WILDERNESS_SURVIVAL,
                ];
                break;

            case SkillPrograms::JOURNALIST_INVESTIGATION:
                $skills = [BonusTargets::SKILL_COMPUTER_OPERATION, BonusTargets::SKILL_INTELLIGENCE, BonusTargets::SKILL_PHOTOGRAPHY, BonusTargets::SKILL_WRITING,];
                break;

            case SkillPrograms::LANGUAGE:
                $skills = [];
                break;

            case SkillPrograms::MECHANICAL:
                $skills = [BonusTargets::SKILL_MECHANICAL_ENGINEERING, BonusTargets::SKILL_LOCKSMITH, BonusTargets::SKILL_ROBOT_MECHANICS,
                    $this->engine->tableRoller->rollTable('Mechanical Program Skills', [
                        new TableEntry(1, BonusTargets::SKILL_AUTOMOTIVE_MECHANICS),
                        new TableEntry(2, BonusTargets::SKILL_AIRCRAFT_MECHANICS),
                        new TableEntry(3, BonusTargets::SKILL_COMPUTER_REPAIR),
                    ])
                ];
                break;

            case SkillPrograms::MEDICAL:
                $skills = [BonusTargets::SKILL_CRIMINAL_SCIENCE_FORENSICS, BonusTargets::SKILL_PARAMEDIC, BonusTargets::SKILL_PATHOLOGY,];
                if ($hero->educationLevel == TableEducation::MASTER_DEGREE || $hero->educationLevel == TableEducation::DOCTORATE_DEGREE) {
                    $skills[] = BonusTargets::SKILL_MEDICAL_DOCTOR;
                }
                break;

            case SkillPrograms::MILITARY:
                $skills = [BonusTargets::SKILL_HAND_TO_HAND_BASIC, BonusTargets::SKILL_DEMOLITIONS, BonusTargets::SKILL_DEMOLITIONS_DISPOSAL, BonusTargets::SKILL_PILOT_TANK,
                    BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS,];
                break;

            case SkillPrograms::PILOT_ADVANCED:
                $skills1 = [BonusTargets::SKILL_NAVIGATION_SPACE, BonusTargets::SKILL_NAVIGATION, BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS, BonusTargets::SKILL_WEAPON_SYSTEMS,];
                $skills2 = $this->selectSkills(2, $hero, $percentBonus, [
                    BonusTargets::SKILL_PILOT_HELICOPTER_BASIC, BonusTargets::SKILL_PILOT_HELICOPTER_COMBAT, BonusTargets::SKILL_PILOT_JET_COMMERCIAL,
                    BonusTargets::SKILL_PILOT_JET_FIGHTER, BonusTargets::SKILL_PILOT_SPACE_SHUTTLE,
                ], false);
                $skills = array_merge($skills1, $skills2);
                break;

            case SkillPrograms::PHYSICAL:
                $skills = $this->selectSkills(4, $hero, $percentBonus, [
                    BonusTargets::SKILL_HAND_TO_HAND_BASIC, BonusTargets::SKILL_HAND_TO_HAND_EXPERT, BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS,
                    BonusTargets::SKILL_ACROBATICS, BonusTargets::SKILL_ARCHERY, BonusTargets::SKILL_ATHLETICS, BonusTargets::SKILL_BODY_BUILDING,
                    BonusTargets::SKILL_BOXING, BonusTargets::SKILL_CLIMBING, BonusTargets::SKILL_RUNNING, BonusTargets::SKILL_FENCING, BonusTargets::SKILL_SWIMMING,
                    BonusTargets::SKILL_GYMNASTICS, BonusTargets::SKILL_SWIMMING_ADVANCED, BonusTargets::SKILL_PROWL, BonusTargets::SKILL_WRESTLING,
                ], false);
                break;

            case SkillPrograms::SCIENCE:
                $skills = $this->selectSkills(4, $hero, $percentBonus, [
                    BonusTargets::SKILL_ASTROPHYSICS, BonusTargets::SKILL_BIOLOGY, BonusTargets::SKILL_BOTANY, BonusTargets::SKILL_CHEMISTRY_BASIC,
                    BonusTargets::SKILL_CHEMISTRY_ANALYTICAL, BonusTargets::SKILL_MATHEMATICS_BASIC, BonusTargets::SKILL_MATHEMATICS_ADVANCED,
                ], false);
                $skills[] = BonusTargets::SKILL_COMPUTER_OPERATION;
                break;

            case SkillPrograms::TECHNICAL:
                $skills = [BonusTargets::SKILL_ART, BonusTargets::SKILL_PHOTOGRAPHY, BonusTargets::SKILL_WRITING,];
                break;

            case SkillPrograms::WP_ANCIENT_WEAPONS:
                $skills = $this->selectSkills(3, $hero, 0, [
                    BonusTargets::SKILL_WP_BLUNT, BonusTargets::SKILL_WP_CHAIN, BonusTargets::SKILL_WP_KNIFE, BonusTargets::SKILL_WP_SWORD,
                    BonusTargets::SKILL_WP_STAFF, BonusTargets::SKILL_WP_TARGET, BonusTargets::SKILL_WP_PAIRED_WEAPONS,
                ], false);
                break;

            case SkillPrograms::WP_MODERN_WEAPONS:
                $skills = $this->selectSkills(3, $hero, 0, [
                    BonusTargets::SKILL_WP_REVOLVER, BonusTargets::SKILL_WP_RIFLE, BonusTargets::SKILL_WP_AUTOMATIC_PISTOL,
                    BonusTargets::SKILL_WP_SUB_MACHINEGUN, BonusTargets::SKILL_WP_AUTOMATIC_RIFLE, BonusTargets::SKILL_WP_HEAVY,
                ], false);
                break;

            case SkillPrograms::WP_ENERGY_WEAPONS:
                $skills = [
                    BonusTargets::SKILL_WP_ENERGY_PISTOL,
                    BonusTargets::SKILL_WP_ENERGY_RIFLE,
                ];
                break;

            case SkillPrograms::WEAPON_PROFICIENCIES:
                $skills = array_merge(
                    $this->skillsForProgram(SkillPrograms::WP_ANCIENT_WEAPONS, $hero),
                    $this->skillsForProgram(SkillPrograms::WP_ENERGY_WEAPONS, $hero),
                    $this->skillsForProgram(SkillPrograms::WP_MODERN_WEAPONS, $hero)
                );
                break;

            case SkillPrograms::HIGH_SCHOOL:
                $skills = array_merge(
                    $this->skillsForProgram(SkillPrograms::COMPUTER, $hero),
                    $this->skillsForProgram(SkillPrograms::DOMESTIC, $hero),
                    $this->skillsForProgram(SkillPrograms::PHYSICAL, $hero),
                    $this->skillsForProgram(SkillPrograms::LANGUAGE, $hero),
                    $this->skillsForProgram(SkillPrograms::TECHNICAL, $hero),
                    $this->skillsForProgram(SkillPrograms::WP_ANCIENT_WEAPONS, $hero)
                );
                break;

            case SkillPrograms::COLLEGE:
                // what are "college" skills? just get all
            case SkillPrograms::ALL_SKILLS:
                $skills = BonusTargets::allSkills(false);
                break;

            default:
                throw new RuntimeException("Unknown skill program: $program");
        }
        return $skills;
    }

    /**
     * add a set of skills to a hero
     *
     * @param Hero $hero the hero
     * @param array $skills the skills to add
     * @param int $percentBonus bonus for the skill
     * @param string $reason why they get this skill?
     */
    public function addSkills($hero, $skills, $percentBonus, $reason) {
        foreach ($skills as $skill) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, $skill, $percentBonus, $reason));
        }
    }

    /**
     * add skills for a program to a character
     *
     * @param String $program which program
     * @param int $percentBonus how much of a bonus to give to the program skills
     * @param Hero $hero the hero for which to pick a program (some programs select skills so select ones that aren't yet selected)
     * @param bool|String[] $disallowSkills which skills are not pickable
     */
    public function addSkillsForProgram($program, $percentBonus, Hero &$hero, $disallowSkills = false)
    {
        switch ($program) {
            case SkillPrograms::COMMUNICATIONS:
            case SkillPrograms::COMPUTER:
            case SkillPrograms::DOMESTIC:
            case SkillPrograms::ESPIONAGE:
            case SkillPrograms::JOURNALIST_INVESTIGATION:
            case SkillPrograms::MEDICAL:
            case SkillPrograms::MILITARY:
            case SkillPrograms::PILOT_ADVANCED:
            case SkillPrograms::PHYSICAL:
            case SkillPrograms::SCIENCE:
            case SkillPrograms::TECHNICAL:
            case SkillPrograms::WP_ANCIENT_WEAPONS:
            case SkillPrograms::WP_MODERN_WEAPONS:
                break;

            case SkillPrograms::ELECTRICAL:
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_ROBOT_ELECTRONICS, -40, SkillPrograms::ELECTRICAL . ' Program'));
                break;

            case SkillPrograms::LANGUAGE:
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Pick a language', $program . 'Program'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Pick a language', $program . 'Program'));
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Pick a language', $program . 'Program'));
                break;

            case SkillPrograms::MECHANICAL:
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_ROBOT_ELECTRONICS, -40, SkillPrograms::MECHANICAL . ' Program'));
                break;

            default:
                throw new RuntimeException("Unknown skill program: $program");
        }

        // now that all skills are gathered, apply them
        $skills = $this->skillsForProgram($program, $hero, $percentBonus);
        foreach ($skills as $skill) {
            if (!$disallowSkills || false === array_search($skill, $disallowSkills)) {
                $this->addSkills($hero, $skills, $percentBonus, $program . ' Program');
            }
        }
    }
}
