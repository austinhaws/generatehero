<?php

namespace Heroes;

use Heroes\engine\Engine;
use Heroes\engine\TableEntry;
use Heroes\hero\Hero;
use Heroes\tables\CharacterBasics;
use Heroes\tables\TableAttributes;
use Heroes\hero\crazy\Association;
use Heroes\hero\crazy\Crazy;
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

        // step 1 - attributes (3d6; +1d6 if >= 16)
        $attributes = ['intelligenceQuotient', 'mentalEndurance', 'mentalAffinity', 'physicalStrength', 'physicalProwess', 'physicalEndurance', 'physicalBeauty', 'speed'];
        foreach ($attributes as $attribute) {
            $hero->$attribute = $this->engine->roller->rollDice($attribute, 3, 6);
            if ($hero->$attribute >= 16) {
                $hero->$attribute += $this->engine->roller->rollDice('=16 attribute bonus', 1, 6);
            }
        }


        // is the hero crazy?
        if ($this->engine->roller->rollDice('is crazy?', 1, 100) == 100) {
            $crazy = $this->engine->tableRoller->rollTable('crazy element', [
                new TableEntry(30, 'Frenzy'),
                new TableEntry(60, 'Association'),
                new TableEntry(85, 'Personalities'),
                new TableEntry(100, 'Crazy'),
            ]);
            $crazy = "Heroes\\hero\\crazy\\$crazy";
            $hero->crazy = new $crazy($this->engine);
            $hero->crazy->create($hero);
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
           new TableEntry(10, 'experiment'),
           new TableEntry(20, 'robotics'),
           new TableEntry(30, 'bionics/implants'),
           new TableEntry(40, 'special training'),
           new TableEntry(50, 'mutants'),
           new TableEntry(60, 'psionics'),
           new TableEntry(70, 'physical training'),
           new TableEntry(80, 'magic'),
           new TableEntry(90, 'hardware'),
           new TableEntry(100, 'aliens'),
        ]);
    }
}
