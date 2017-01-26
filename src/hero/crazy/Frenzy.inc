<?php
namespace Heroes\hero\crazy;

use Heroes\engine\TableEntry;
use Heroes\hero\Hero;

class Frenzy extends BaseCrazy
{
    public $condition;

    function create(Hero &$hero)
    {
        $this->condition = $this->engine->tableRoller->rollTable('Frenzy: condition', [
           new TableEntry(20, 'Intense Frustration'),
           new TableEntry(50, 'Intense Anger'),
           new TableEntry(80, 'Intense Pain'),
           new TableEntry(100, 'Extreme Tension'),
        ]);
    }

    // while frenzied: +1 attack per melee, +30 SDC, +1d6 damage, +1 strie/parry/dodge. speed +30%. lasts 15 seconds * Physical Endurance.
}
