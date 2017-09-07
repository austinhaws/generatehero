<?php
namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\superabilities\TablePsionics;

class Psionics extends BaseClass
{
    /** @var int points for using psionics */
    public $ispPoints;

    public function postCreate(Hero &$hero)
    {
        parent::postCreate($hero);
        // this also happens for mutants and aliens that have psionics
        $this->ispPoints = $hero->physicalEndurance * 2 + $this->engine->roller->rollDice(new Roll('Psionic - ISP Points', 1, 20));
    }

    /**
     * create a character's class
     *
     * @param Hero $hero the hero
     * @throws \Exception ya ya, whatever
     */
    public function create(Hero &$hero, $options = false)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE, new Roll('Psionic - ME', 2, 4), 'Psionic'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Psionic - MA', 1, 4), 'Psionic'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC,30, 'Psionic'));
        $this->hasCar($hero, 89);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Psionic- Money', 4, 4, 100), 'Psionic'));

        (new TablePsionics($this->engine))->selectPowers($hero, 3, 6);
    }

    public function createMutantAlien(Hero &$hero) {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE, new Roll('Mutant/Alien Psionic - ME', 2, 4), 'Psionic'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Mutant/Alien Psionic - MA', 1, 4), 'Psionic'));
        (new TablePsionics($this->engine))->selectPowers($hero, 2, 4);
    }
}
