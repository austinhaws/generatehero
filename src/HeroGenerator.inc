<?php

namespace Heroes;

use Heroes\engine\Engine;
use Heroes\hero\Hero;
use Heroes\tables\CharacterBasics;

class HeroGenerator
{
    private $engine;
    private $characterBasics;

    public function __construct()
    {
        $this->engine = new Engine();
        $this->characterBasics = new CharacterBasics();
    }

    public function generate()
    {
        $hero = new Hero();

        // step 1 - attributes (rolling/calculating them)
//        [ ] option 1 : roll
//        [ ] option 2 : roll extras, keep highest
//        [ ] option 3 : point buy?
//        [ ] option 4 ?? what other ways to generate scores for a generator


        // step 3 - determine super abilities
        $this->generatePowerCategory($hero);


        // step 4 - education / skills

        // step 5 - alignment

        // step 6 - character start
        $this->characterBasics->generateCharacterBasics($hero);

        // step 2 - hit points / sdc : can't get HPs until scores are settled through super abilities/education... :(
        // rounding out character

        // after skills are determined, and all bonuses to abilities are gathered, then apply bonuses based on abilities
        (new TableAttributes($this->engine))->applyAttributeBonuses($hero);

        return $hero->outputCharacter();
    }

    /**
     * determine a power category for the hero
     * apply that category using its class
     *
     * @param Hero $hero the hero
     */
    private function generatePowerCategory(Hero &$hero)
    {
        $roll = $this->engine->roller->rollDice('power category', 1, 102);

// use table roller, have result be a class name string to use to create the new class
        if ($roll <= 10) {
            throw new \Exception('experiment');
        } else if ($roll <= 20) {
            throw new \Exception('robotics');
        } else if ($roll <= 30) {
            throw new \Exception('bionics/implants');
        } else if ($roll <= 40) {
            throw new \Exception('special training');
        } else if ($roll <= 50) {
            throw new \Exception('mutants');
        } else if ($roll <= 60) {
            throw new \Exception('psionics');
        } else if ($roll <= 70) {
            throw new \Exception('physical training');
        } else if ($roll <= 80) {
            throw new \Exception('magic');
        } else if ($roll <= 90) {
            throw new \Exception('hardware');
        } else if ($roll <= 100) {
            throw new \Exception('aliens');
        } else if ($roll <= 101) {
            throw new \Exception('insane');
        } else if ($roll <= 102) {
            throw new \Exception('multiple personality');
        }
    }
}
