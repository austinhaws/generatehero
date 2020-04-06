<?php

namespace Heroes\hero\classes;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\enums\SkillPrograms;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\TableEducation;

class SpecialTrainingSuperSleuth extends BaseClass
{
    public function __construct(Engine &$engine)
    {
        parent::__construct($engine, 'Special Training');
        $this->classSubtype = 'Super Sleuth';
    }

    /**
     * @param Hero $hero
     * @param bool $options
     */
    public function create(Hero &$hero, $options = false)
    {
        $this->modifyAttributes($hero);

        $this->pickEducation($hero);

        $this->giveSuperSkills($hero);

        $this->earnMoney($hero);
    }

    private function modifyAttributes(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE, new Roll('Super Sleuth - ME', 1, 6), 'Super Sleuth - ME'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Super Sleuth - MA', 1, 4), 'Super Sleuth - MA'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT, 14, 'Super Sleuth - IQ'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 40, 'Super Sleuth - SDC'));
    }

    private function pickEducation(Hero &$hero)
    {
        $hero->educationLevel = TableEducation::SUPER_SLEUTH;

        $tableEducation = new TableEducation($this->engine);
        $tableEducation->pickPrograms(15, 2, $hero, [SkillPrograms::ESPIONAGE, SkillPrograms::MILITARY]);

        $hero->addSkill(BonusTargets::SKILL_COMPUTER_OPERATION, 'Super Sleuth - Education', 98);
        $hero->addSkill(BonusTargets::SKILL_COMPUTER_PROGRAMMING, 'Super Sleuth - Education', 96);
        $hero->addSkill(BonusTargets::SKILL_MATHEMATICS_BASIC, 'Super Sleuth - Education', 98);
        $hero->addSkill(BonusTargets::SKILL_MATHEMATICS_ADVANCED, 'Super Sleuth - Education', 98);
        $hero->addSkill(BonusTargets::SKILL_LANGUAGE, 'Super Sleuth - Education', 98);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Pick a language', 'Super Sleuth - Education'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Pick a language', 'Super Sleuth - Education'));

        if ($this->engine->roller->rollPercent('Super Sleuth - pilot') > 50) {
            $hero->addSkill(BonusTargets::SKILL_PILOT_AUTOMOBILE, 'Super Sleuth - Education', 96);
        } else {
            $hero->addSkill(BonusTargets::SKILL_PILOT_MOTORCYCLE, 'Super Sleuth - Education', 96);
        }

        $skillPrograms = new SkillPrograms($this->engine);
        $skills = $skillPrograms->selectSkills(7, $hero, 25, [
            BonusTargets::SKILL_CHEMISTRY_BASIC,
            BonusTargets::SKILL_CHEMISTRY_ANALYTICAL,
            BonusTargets::SKILL_CRYPTOGRAPHY,
            BonusTargets::SKILL_CRIMINAL_SCIENCE_FORENSICS,
            BonusTargets::SKILL_DISGUISE,
            BonusTargets::SKILL_FORGERY,
            BonusTargets::SKILL_INTELLIGENCE,
            BonusTargets::SKILL_INTERROGATION,
            BonusTargets::SKILL_IMPERSONATION,
            BonusTargets::SKILL_PARAMEDIC,
            BonusTargets::SKILL_PATHOLOGY,
            BonusTargets::SKILL_PICK_LOCKS,
            BonusTargets::SKILL_SURVEILLANCE,
            BonusTargets::SKILL_BASIC_ELECTRONICS,
        ]);
        $hero->addSkills($skills, 'Super Sleuth - Education', 25);

        $skills = $skillPrograms->selectSkills(8, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Super Sleuth - Education', 0);
    }

    private function giveSuperSkills(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Computer Hacking (96%)', 'Super Sleuth - Super Skill'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'See through Disguise and Forgery (50%)', 'Super Sleuth - Super Skill'));
    }

    /**
     * @param Hero $hero
     */
    private function earnMoney(Hero &$hero)
    {
        $money = $this->engine->tableRoller->rollTable('Super Sleuth - money', [
            new TableEntry(15, 8000),
            new TableEntry(29, 10000),
            new TableEntry(45, 12000),
            new TableEntry(60, 14000),
            new TableEntry(75, 16000),
            new TableEntry(89, 18000),
            new TableEntry(100, 20000),
        ]);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, $money, 'Super Sleuth - Money'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Has ' . $this->engine->roller->rollDice(new Roll('Super Sleuth - Crime Lab', 2, 4, 10000)) . ' dollars to equip crime lab.', 'Super Sleuth - Crime Lab'));
        $this->hasCar($hero, 100);
    }
}
