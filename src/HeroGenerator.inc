<?php

namespace Heroes;

use Heroes\engine\Engine;
use Heroes\engine\TableEntry;
use Heroes\hero\Hero;
use Heroes\tables\CharacterBasics;
use Heroes\tables\TableAttributes;
use Heroes\hero\crazy\Frenzy;

class HeroGenerator
{
    public $engine;

    public function __construct()
    {
        $this->engine = new Engine();
    }

    public function generate()
    {
        $hero = new Hero();

        // step 1 - attributes (rolling/calculating them)
//        [ ] option 1 : roll
//        [ ] option 2 : roll extras, keep highest
//        [ ] option 3 : point buy?
//        [ ] option 4 ?? what other ways to generate scores for a generator

        if ($this->engine->roller->rollDice('is crazy?', 1, 100) == 100) {
            $crazy = $this->engine->tableRoller->rollTable('crazy element', [
                new TableEntry(1, 30, 'Frenzy'),
                new TableEntry(31, 60, 'Association'),
                new TableEntry(61, 85, 'Personalities'),
                new TableEntry(86, 100, 'Crazy'),
            ]);
            $crazy = "Heroes\\hero\\crazy\\$crazy";
            $hero->crazy = new $crazy($this->engine);
        }


        // step 3 - determine super abilities
        $this->generatePowerCategory($hero);

        // step 4 - education / skills

        // step 5 - alignment

        // step 6 - character start

        $characterBasics = new CharacterBasics($this->engine);
        $characterBasics->generateCharacterBasics($hero);

        // step 2 - hit points / sdc : can't get HPs until scores are settled through super abilities/education... :(
        // rounding out character

        // after skills are determined, and all bonuses to abilities are gathered, then apply bonuses based on abilities
        (new TableAttributes($this->engine))->applyAttributeBonuses($hero);

        return $hero;
    }

    /**
     * determine a power category for the hero
     * apply that category using its class
     *
     * @param Hero $hero the hero
     */
    private function generatePowerCategory(Hero &$hero)
    {
        $class = $this->engine->tableRoller->rollTable('power category', [
           new TableEntry(1, 10, 'experiment'),
           new TableEntry(11, 20, 'robotics'),
           new TableEntry(21, 30, 'bionics/implants'),
           new TableEntry(31, 40, 'special training'),
           new TableEntry(41, 50, 'mutants'),
           new TableEntry(51, 60, 'psionics'),
           new TableEntry(61, 70, 'physical training'),
           new TableEntry(71, 80, 'magic'),
           new TableEntry(81, 90, 'hardware'),
           new TableEntry(91, 100, 'aliens'),
        ]);

        // TODO: hook up powers
        echo "chosen class is: $class\n";
    }
}
