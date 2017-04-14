<?php

namespace Heroes;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\hero\Hero;
use Heroes\tables\CharacterBasics;
use Heroes\tables\TableAttributes;
use Heroes\tables\TableEducation;

// these "use" statements ARE needed because they are dynamically named class creations

class HeroGenerator
{
    public $engine;

    /**
     * HeroGenerator constructor.
     * @param Engine $engine allows testing to override engine
     */
    public function __construct(Engine $engine = null)
    {
        $this->engine = $engine ? $engine : new Engine();
    }

    /**
     * create a hero!
     *
     * @return Hero the hero
     */
    public function generate()
    {
        $hero = new Hero();

        /**
         * this process accomplishes the following
         *  - rolling attributes
         *  - possible crazy hero
         *  - determine super ability type and apply it
         *  - roll education (if super ability type hasn't already determined it)
         *  - alignment
         *  - extra info (weight/originland/etc)
         *  - and tallying all bonuses and calculations
         */

        // step 1 - attributes (3d6; +1d6 if >= 16)
        $attributes = ['intelligenceQuotient', 'mentalEndurance', 'mentalAffinity', 'physicalStrength', 'physicalProwess', 'physicalEndurance', 'physicalBeauty', 'speed'];
        foreach ($attributes as $attribute) {
            $hero->$attribute = $this->engine->roller->rollDice(new Roll($attribute, 3, 6));
            if ($hero->$attribute >= 16) {
                $hero->$attribute += $this->engine->roller->rollDice(new Roll('=16 attribute bonus', 1, 6));
            }
        }


        // is the hero crazy?
        if ($this->engine->roller->rollDice(new Roll('is crazy?', 1, 100)) == 100) {
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
        if (!$hero->educationLevel) {
            (new TableEducation($this->engine))->rollEducationLevel($hero);
        }

        // step 5 - alignment
        $hero->alignment = $this->engine->tableRoller->rollTable('Alignment', [
           new TableEntry(35, 'Principled: Strong, moral character with the highest regard for other\'s lives and well-being, truth, and honor. Will always attempt to work within the law.'),
           new TableEntry(70, 'Scrupulous: Value life and freedom above all else, and despise those who would deprive others of them. Forced to work beyond hte law, yet for the law, and the greater good of the people.'),
           new TableEntry(85, 'Unprincipled: Selfish, greedy, and holds his personal freedom and welfare above almost everything else. Dislikes confining laws, self-discipline, and distrusts authority.'),

           new TableEntry(92, 'Anarchist: Indulges in everything. Insurgent, con-man, gambler, and high roller. Uncommitted freebooter who is more likely to be a crimefighter because he enjoys the thrill of danger and excitement than any cause.'),

           new TableEntry(95, 'Miscreant: Self-serving, unscrupulous, out only for himself. Power, glory, wealth, position, and anything that will make his life more comfortable or pleasurable is his goal. Will lie, cheat, and hurt anyone to attain his personal goals.'),
           new TableEntry(98, 'Aberrant: Driven to attain his goals through force, power, and intimidation. Has own personal code of ethics. He expects loyalty from his minions, punishing disloyalty and treachery with a swift, merciful death. Always keeps his word of honor and uphold any bargains.'),
           new TableEntry(100, 'Diabolic: Megalomaniacs, violent, and most despicable. Cruel, brutal killer who trusts no one and has no value for any life other than his own. Will lie, cheat, use and abuse anyone not more powerful than themselves.'),
        ]);

        // step 6 - character start

        $characterBasics = new CharacterBasics($this->engine);
        $characterBasics->generateCharacterBasics($hero);


        // after skills are determined, and all bonuses to abilities are gathered, then apply bonuses based on abilities
// TODO: echo "skills use a bonus 'SET' to show that they are added. Skills give bonuses and have a base start, so need to figure those out\n";
// TODO: echo "apply all heroes bonuses (saved until end so that \"set\" bonuses can get the biggest value and then apply all the bonuses on top of that)\n";
// set a flag that bonuses have been applied so that when bonuses are added by attribute bonuses they get applied immediately; if a "set" bonus is added after bonuses are calculated, then throw exception?


        // now that attributes are determined, determine their bonuses
        (new TableAttributes($this->engine))->applyAttributeBonuses($hero);

        // step 2 - hit points / sdc : can't get HPs until scores are settled through super abilities/education... :(
        // rounding out character


        // all done, give class one last crack at computing
        $hero->class->postCreate($hero);

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
           new TableEntry(10, 'Experiment'),
           new TableEntry(20, 'Robotics'),
           new TableEntry(30, 'Bionics'),
           new TableEntry(40, 'SpecialTraining'),
           new TableEntry(50, 'Mutants'),
           new TableEntry(60, 'Psionics'),
           new TableEntry(70, 'PhysicalTraining'),
           new TableEntry(80, 'Magic'),
           new TableEntry(90, 'Hardware'),
           new TableEntry(100, 'Aliens'),
        ]);

        $class = "Heroes\\hero\\classes\\$class";
        $hero->class = (new $class($this->engine));
        $hero->class->create($hero);
    }
}
