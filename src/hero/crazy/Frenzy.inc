<?php
namespace Heroes\hero\crazy;

use Heroes\engine\Engine;
use Heroes\engine\TableEntry;

class Frenzy implements BaseCrazy
{
    public $engine;

    public $condition;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    function create()
    {
        $this->condition = $this->engine->tableRoller->rollTable('Frenzy: condition', [
           new TableEntry(1, 20, 'Intense Frustration'),
           new TableEntry(21, 50, 'Intense Anger'),
           new TableEntry(51, 80, 'Intense Pain'),
           new TableEntry(81, 100, 'Extreme Tension'),
        ]);
    }

    // while frenzied: +1 attack per melee, +30 SDC, +1d6 damage, +1 strie/parry/dodge. speed +30%. lasts 15 seconds * Physical Endurance.
}
