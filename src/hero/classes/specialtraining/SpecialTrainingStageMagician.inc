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

class SpecialTrainingStageMagician extends BaseClass
{
    /** @var string who sponsored this operative? */
    public $sponsoringOrganization;

    /** @var string relation ship with sponsoring organization */
    public $sponsoringOrganizationStatus;

    public function __construct(Engine &$engine)
    {
        parent::__construct($engine, 'Special Training');
        $this->classSubtype = 'Stage Magician';
    }

    public function create(Hero &$hero, $options = false)
    {
        $this->modifyAttributes($hero);

        $this->applyEducation($hero);

        $this->givSpecialSkills($hero);

        $this->pickGimmicks($hero);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 40, 'Stage Magician - SDC'));

        $this->hasCar($hero, 86);
    }

    private function modifyAttributes(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Stage Magician - MA', 1, 6), 'Stage Magician - MA'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Stage Magician - PP', 1, 6), 'Stage Magician - PP'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_BEAUTY, new Roll('Stage Magician - PB', 1, 4), 'Stage Magician - PB'));
    }

    private function applyEducation(Hero &$hero)
    {
        $hero->educationLevel = TableEducation::SECRET_OPERATIVE;

        $tableEducation = new TableEducation($this->engine);
        $tableEducation->pickPrograms(10, 1, $hero, [SkillPrograms::MILITARY, SkillPrograms::ESPIONAGE]);


        $skillPrograms = new SkillPrograms($this->engine);
        $skills = $skillPrograms->selectSkills(8, $hero, 25, [
            BonusTargets::SKILL_CLIMBING,
            BonusTargets::SKILL_CONCEALMENT,
            BonusTargets::SKILL_DETECT_CONCEALMENT,
            BonusTargets::SKILL_DISGUISE,
            BonusTargets::SKILL_ESCAPE_ARTIST,
            BonusTargets::SKILL_FORGERY,
            BonusTargets::SKILL_IMPERSONATION,
            BonusTargets::SKILL_PALMING,
            BonusTargets::SKILL_PICK_LOCKS,
            BonusTargets::SKILL_PICK_POCKETS,
            BonusTargets::SKILL_PROWL,
            BonusTargets::SKILL_OPTIC_SYSTEMS,
            BonusTargets::SKILL_SURVEILLANCE,
            BonusTargets::SKILL_TV_VIDEO,
        ]);
        $hero->addSkills($skills, 'Stage Magician - Education', 25);

        $skills = $skillPrograms->selectSkills(10, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Stage Magician - Education', 0);
    }

    private function givSpecialSkills(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PALMING, 5, 'Stage Magician - Sleight of Hand'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PICK_POCKETS, 5, 'Stage Magician - Sleight of Hand'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_ESCAPE_ARTIST, 10, 'Stage Magician - Sleight of Hand'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CONCEALMENT, 6, 'Stage Magician - Sleight of Hand'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_ESCAPE_ARTIST, 5, 'Stage Magician - Contortionist'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 2, 'Stage Magician - Contortionist'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Juggling (55%): 5 attacks w/ thrown weapons, +1 strike w/ thrown weapons, up to six items + 1/lvl', 'Stage Magician - Special Skills'));

    
    
    }

    /**
     * @param Hero $hero
     */
    private function pickGimmicks(Hero &$hero)
    {
        // roll for loot
        $money = $this->engine->tableRoller->rollTable('Stage Magician - Gimmick Money', [
            new TableEntry(12, 6500),
            new TableEntry(24, 7000),
            new TableEntry(38, 8200),
            new TableEntry(52, 10000),
            new TableEntry(65, 12000),
            new TableEntry(78, 14000),
            new TableEntry(90, 16000),
            new TableEntry(100, 18000),
        ]);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, $money, 'Stage Magician - Gimmick Gear'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Tailor-Made Clothing with secret pockets', 'Stage Magician - Gimmicks'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Belt buckle compartment', 'Stage Magician - Gimmicks'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Belt with secret lining', 'Stage Magician - Gimmicks'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Flash powder: blinding flash', 'Stage Magician - Gimmicks'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Itching powder', 'Stage Magician - Gimmicks'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Goblin dust: blinds opponent', 'Stage Magician - Gimmicks'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Mini-smoke bomb', 'Stage Magician - Gimmicks'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Mini-stink bomb', 'Stage Magician - Gimmicks'));
    }
}
