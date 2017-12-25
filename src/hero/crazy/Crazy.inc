<?php
namespace Heroes\hero\crazy;

use Heroes\engine\Engine;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\classes\BaseClass;
use Heroes\hero\Hero;
use Heroes\tables\TableInsanity;

class Crazy extends BaseClass
{

    public function __construct(Engine &$engine)
    {
        parent::__construct($engine, 'Crazy');
    }

    /**
     * @param Hero $hero
     * @param bool $options
     * @throws \Exception
     */
    function create(Hero &$hero, $options = false)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Wild, flamboyant, and jocular. Zany, dynamic, caustic, and hyper. This guys in the wisecracking daredevil who seems to be as coky and carefree leaping in to the jaws of death as he is at a tea party. He will batter his opponent with sarcastic quips, bad jokes, and silly observations while he is socking it out with him or facing hte barrel of a gun.', 'Crazy'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PROWL, 10, 'Crazy'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 10, 'Crazy'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_SWIMMING, 10, 'Crazy'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GYMNASTICS, 10, 'Crazy'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_DANCE, 10, 'Crazy'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 4, 'Crazy'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 1, 'Crazy'));

        $skills = BonusTargets::allSkills(false);
        $except = array_merge(
            BonusTargets::physicalSkills(false),
            BonusTargets::pilotAdvancedSkills(false),
            BonusTargets::pilotBasicSkills(false),
            BonusTargets::pilotRelatedSkills(false),
            BonusTargets::weaponProficienciesSkills(false)
        );
        foreach ($skills as $skill) {
            if (array_search($skill, $except) === false) {
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, $skill, -10, 'Crazy'));
            }
        }

        // pg 24, give some quirks
        $tableInsanity = new TableInsanity($this->engine);
        $tableInsanity->rollInsanity($hero, TableInsanity::PHOBIA);
        $tableInsanity->rollInsanity($hero, TableInsanity::PHOBIA);
        $tableInsanity->rollInsanity($hero, TableInsanity::OBSESSION);
    }
}
