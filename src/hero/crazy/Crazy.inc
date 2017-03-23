<?php
namespace Heroes\hero\crazy;

use Heroes\hero\Hero;
use Heroes\tables\TableInsanity;

class Crazy extends BaseCrazy
{
    function create(Hero &$hero)
    {
        'Wild, flamboyant, and jocular. Zany, dynamic, caustic, and hyper. This guys in the wisecracking daredevil who seems to be as coky and carefree leaping in to the jaws of death as he is at a tea party. He will batter his opponent with sarcastic quips, bad jokes, and silly observations while he is socking it out with him or facing hte barrel of a gun.';
        '-10% on all skills other than phsyical, piloting, and weapon proficiencies. +10% prowl, climbing, swimming, gymanstics, and dancing. +4 roll, fall, and explosion. +1 dodge.';


        // pg 24, give some quirks
        $tableInsanity = new TableInsanity($this->engine);
        $tableInsanity->rollInsanity($hero, TableInsanity::PHOBIA);
        $tableInsanity->rollInsanity($hero, TableInsanity::PHOBIA);
        $tableInsanity->rollInsanity($hero, TableInsanity::OBSESSION);
    }
}
