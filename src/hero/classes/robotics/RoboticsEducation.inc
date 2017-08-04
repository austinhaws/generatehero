<?php

namespace Heroes\hero\classes\robotics;

use Heroes\engine\Engine;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\classes\BaseClass;
use Heroes\hero\Hero;
use Heroes\tables\TableEducation;

class RoboticsEducation extends BaseClass
{

    /** @var TableEducation for rolling education information */
    private $tableEducation;

    public function __construct(Engine $engine)
    {
        parent::__construct($engine);
        $this->tableEducation = new TableEducation($engine);
    }

    /**
     * create this class for this character
     *
     * @param Hero $robot the robot AI to which to add education
     * @throws \Exception neener neener you lose
     */
    public function create(Hero &$robot)
    {
        $educationFunction = $this->engine->tableRoller->rollTable('Robot AI: Education', [
            new TableEntry(1, 'combatProgram'),
            new TableEntry(2, 'communicationsProgram'),
            new TableEntry(3, 'domesticProgram'),
            new TableEntry(4, 'electricalProgram'),
            new TableEntry(5, 'espionageProgram'),
            new TableEntry(6, 'investigativeProgram'),
            new TableEntry(7, 'pilotProgram'),
            new TableEntry(8, 'scienceProgram'),
            new TableEntry(9, 'socialScienceProgram'),
            new TableEntry(10, 'physicalScienceProgram'),
        ]);
        $this->$educationFunction($robot);
    }

    private function combatProgram(Hero &$robot)
    {
        $educationTitle = 'Robot AI Education - Combat Program';
        $robot->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, $educationTitle, $educationTitle));
        $robot->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, $educationTitle));
        $robot->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, $educationTitle));
        $robot->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, $educationTitle));
        $robot->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, $educationTitle));
        $robot->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 3, $educationTitle));

        $this->tableEducation->addSkillsToHero(4, BonusTargets::allSkills(false), $robot, $educationTitle, 0);

        $robot->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Military background data; includes all branches of the military, their uniforms, ranks, procedures, major installations, standard infantry weapons and equipment, and complete stats on 48 common assault vehicles.', $educationTitle));
    }

    private function communicationsProgram(Hero &$robot)
    {
        $educationTitle = 'Robot AI Education - Communications Program';
        $skillLevel = 94;

        $robot->addSkill(BonusTargets::SKILL_RADIO_BASIC, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_COMPUTER_OPERATION, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_BASIC_ELECTRONICS, $educationTitle, $skillLevel);

        $this->tableEducation->addSkillsToHero(5, BonusTargets::communicationSkills(false), $robot, $educationTitle, 0);
        $this->tableEducation->addSkillsToHero(4, BonusTargets::allSkills(true), $robot, $educationTitle, $skillLevel);
    }

    private function domesticProgram(Hero &$robot)
    {
        $educationTitle = 'Robot AI Education - Domestic Program';
        $skillLevel = 82;

        $robot->addSkill(BonusTargets::SKILL_COMPUTER_OPERATION, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_COOK, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_DANCE, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_FIRST_AID, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_PILOT_AUTOMOBILE, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_SEW, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_SWIMMING, $educationTitle, $skillLevel);

        $this->tableEducation->addSkillsToHero(5, BonusTargets::allSkills(true), $robot, $educationTitle, $skillLevel);
    }

    private function electricalProgram(Hero &$robot)
    {
        $educationTitle = 'Robot AI Education - Electrical Program';
        $skillLevel = 90;

        $robot->addSkill(BonusTargets::SKILL_COMPUTER_OPERATION, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_ELECTRICAL_ENGINEER, $educationTitle, $skillLevel);
        $this->tableEducation->addSkillsToHero(2, BonusTargets::communicationSkills(false), $robot, $educationTitle, 0);
        $skills = array_filter(BonusTargets::mechanicalSkills(false), function ($skill) {
            return BonusTargets::SKILL_MECHANICAL_ENGINEERING !== $skill;
        });
        $this->tableEducation->addSkillsToHero(2, $skills, $robot, $educationTitle, 0);
        $this->tableEducation->addSkillsToHero(4, BonusTargets::allSkills(true), $robot, $educationTitle, $skillLevel);
    }

    private function espionageProgram(Hero &$robot)
    {
        $educationTitle = 'Robot AI Education - Espionage Program';
        $skillLevel = 90;

        // Select 5 Espionage and/or Military Skills.
        $robot->addSkill(BonusTargets::SKILL_COMPUTER_OPERATION, $educationTitle, $skillLevel);
        $this->tableEducation->addSkillsToHero(
            5,
            array_merge(BonusTargets::espionageSkills(false), BonusTargets::militarySkills(false)),
            $robot, $educationTitle, $skillLevel);

        // Select 2 W.P. from ancient and/or modem.
        $this->tableEducation->addSkillsToHero(
            2,
            array_merge(BonusTargets::wpAncientWeaponsSkills(false), BonusTargets::wpModernWeaponsSkills(false)),
            $robot, $educationTitle, $skillLevel);

        // Select 3 Pilot Skills and/or Pilot Related.
        $this->tableEducation->addSkillsToHero(
            3,
            array_merge(BonusTargets::pilotBasicSkills(false), BonusTargets::pilotRelatedSkills(false)),
            $robot, $educationTitle, $skillLevel);

        // Select 2 Secondary Skills.
        $this->tableEducation->addSkillsToHero(2, BonusTargets::allSkills(true), $robot, $educationTitle, $skillLevel);
    }

    private function investigativeProgram(Hero &$robot)
    {
        $educationTitle = 'Robot AI Education - Investigative Program';
        $skillLevel = 88;

        $robot->addSkill(BonusTargets::SKILL_CRIMINAL_SCIENCE_FORENSICS, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_COMPUTER_OPERATION, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_INTELLIGENCE, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_INTERROGATION, $educationTitle, $skillLevel);

        $this->tableEducation->addSkillsToHero(2, BonusTargets::communicationSkills(false), $robot, $educationTitle, $skillLevel);

        // Select 3 Pilot Skills and/or Pilot Related.
        $this->tableEducation->addSkillsToHero(
            3,
            array_merge(BonusTargets::pilotBasicSkills(false), BonusTargets::pilotRelatedSkills(false)),
            $robot, $educationTitle, $skillLevel);

        // Select 3 Secondary Skills.
        $this->tableEducation->addSkillsToHero(3, BonusTargets::allSkills(true), $robot, $educationTitle, $skillLevel);
    }

    private function pilotProgram(Hero &$robot)
    {
        $educationTitle = 'Robot AI Education - Pilot Program';
        $skillLevel = 92;

        $robot->addSkill(BonusTargets::SKILL_AUTOMOTIVE_MECHANICS, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_AIRCRAFT_MECHANICS, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_BASIC_MECHANICS, $educationTitle, $skillLevel);

        $this->tableEducation->addSkillsToHero(6, BonusTargets::pilotBasicSkills(false), $robot, $educationTitle, $skillLevel);
        $this->tableEducation->addSkillsToHero(2, BonusTargets::pilotRelatedSkills(false), $robot, $educationTitle, $skillLevel);
        $this->tableEducation->addSkillsToHero(3, BonusTargets::allSkills(true), $robot, $educationTitle, $skillLevel);
    }

    private function scienceProgram(Hero &$robot)
    {
        $educationTitle = 'Robot AI Education - Science Program';
        $skillLevel = 90;

        $robot->addSkill(BonusTargets::SKILL_CATEGORY_COMPUTER, $educationTitle, $skillLevel);
        $robot->addSkill(BonusTargets::SKILL_COMPUTER_PROGRAMMING, $educationTitle, $skillLevel);

        // Select 6 Science and/or Medical Skills*
        $this->tableEducation->addSkillsToHero(
            6,
            array_merge(BonusTargets::scienceSkills(false), BonusTargets::medicalSkills(false)),
            $robot, $educationTitle, $skillLevel);

        // Select 5 Secondary Skills - ignoring that medical doctor counts 2 - bonus skill for character! WOOT! WOOT!
        $this->tableEducation->addSkillsToHero(5, BonusTargets::allSkills(true), $robot, $educationTitle, $skillLevel);
    }

    private function socialScienceProgram(Hero &$robot)
    {
        $educationTitle = 'Robot AI Education - Social Science Program';
        $skillLevel = 92;

        // Select 5 Languages
        for ($i = 0; $i < 5; $i++) {
            $robot->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_LANGUAGE, $skillLevel, $educationTitle));
        }

        // Select 1 Technical Skill.
        $this->tableEducation->addSkillsToHero(1, BonusTargets::technicalSkills(false), $robot, $educationTitle, $skillLevel);

        // Select 1 Communications Skill.
        $this->tableEducation->addSkillsToHero(1, BonusTargets::communicationSkills(false), $robot, $educationTitle, $skillLevel);

        // Select 2 Domestic Skills.
        $this->tableEducation->addSkillsToHero(2, BonusTargets::domesticSkills(false), $robot, $educationTitle, $skillLevel);

        // Select 4 Secondary Skills.
        $this->tableEducation->addSkillsToHero(2, BonusTargets::allSkills(true), $robot, $educationTitle, $skillLevel);
    }

    private function physicalScienceProgram(Hero &$robot)
    {
        $educationTitle = 'Robot AI Education - Physical Science Program';
        $skillLevel = 80;

        $robot->addSkill(BonusTargets::SKILL_BIOLOGY, $educationTitle, $skillLevel);
        $this->tableEducation->addSkillsToHero(4, [
            BonusTargets::SKILL_ARCHERY, BonusTargets::SKILL_BOXING, BonusTargets::SKILL_CLIMBING, BonusTargets::SKILL_FENCING, BonusTargets::SKILL_GYMNASTICS,
            BonusTargets::SKILL_PROWL, BonusTargets::SKILL_SWIMMING, BonusTargets::SKILL_SWIMMING_ADVANCED, BonusTargets::SKILL_WRESTLING,
        ], $robot, $educationTitle, $skillLevel);

        $this->tableEducation->addSkillsToHero(3, BonusTargets::wpAncientWeaponsSkills(false), $robot, $educationTitle, $skillLevel);

        $this->tableEducation->addSkillsToHero(4, BonusTargets::allSkills(true), $robot, $educationTitle, $skillLevel);
    }
}
