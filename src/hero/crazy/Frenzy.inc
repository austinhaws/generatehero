<?php
namespace Heroes\hero\crazy;

use Heroes\engine\Engine;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\classes\BaseClass;
use Heroes\hero\Hero;

class Frenzy extends BaseClass
{
    /** @var string what triggers the frenzy */
    public $condition;

    public function __construct(Engine &$engine)
    {
        parent::__construct($engine, 'Crazy');
        $this->classSubtype = 'Frenzy';
        $this->crazyDescription = 'Appears normal most of the time, but will fly into a wild, uncontrolled rage under certain, high pressure, conditions.';
    }

    /**
     * @param Hero $hero
     * @param bool $options
     */
    function create(Hero &$hero, $options = false)
    {
        $this->condition = $this->engine->tableRoller->rollTable('Frenzy: condition', [
           new TableEntry(20, 'Intense Frustration'),
           new TableEntry(50, 'Intense Anger'),
           new TableEntry(80, 'Intense Pain'),
           new TableEntry(100, 'Extreme Tension'),
        ]);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, "while frenzied: +1 attack per melee, +30 SDC, +1d6 damage, +1 strie/parry/dodge. speed +30%. lasts 15 seconds * Physical Endurance.", "Crazy - Frenzy"));
    }
}
