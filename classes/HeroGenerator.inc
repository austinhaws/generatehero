<?php
require_once 'Hero.inc';
require_once 'Engine.inc';
require_once 'tables/TableAttributes.inc';

class HeroGenerator {
    private $engine;

    public function __construct() {
        $this->engine = new Engine();
    }

    public function generate() {
        $hero = new Hero();

        // step 1 - attributes (rolling/calculating them)
//        [ ] option 1 : roll
//        [ ] option 2 : roll extras, keep highest
//        [ ] option 3 : point buy?
//        [ ] option 4 ?? what other ways to generate scores for a generator


        // step 3 - determine super abilities
            // optional - crazy/multiple personality
        // step 4 - education / skills

        // step 2 - hit points / sdc : can't get HPs until scores are settled through super abilities/education... :(
        // rounding out character

        // after skills are determined, and all bonuses to abilities are gathered, then apply bonuses based on abilities
        (new TableAttributes($engine))->applyAttributeBonuses($hero);

        return $hero;
    }
}

