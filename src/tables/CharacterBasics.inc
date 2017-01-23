<?php
namespace Heroes\tables;

use Heroes\engine\TableEntry;
use Heroes\hero\Hero;
use Heroes\engine\Engine;

class CharacterBasics
{
    private $engine;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * basics from page 18
     *
     * @param Hero $hero the hero
     */
    public function generateCharacterBasics(Hero &$hero)
    {
        $this->birthOrder($hero);
        $this->weight($hero);
        $this->height($hero);
        $this->disposition($hero);
        $this->lifeSavings($hero);
        $this->landOfOrigin($hero);
        $this->typeOfEnvironment($hero);
        $this->socialEconomicBackground($hero);
        $this->whenManifested($hero);
    }

    private function birthOrder(Hero &$hero)
    {
        $hero->birthOrder = $this->engine->tableRoller->rollTable('birth order', [
            new TableEntry(1, 30, 'First Born'),
            new TableEntry(31, 44, 'Second Born'),
            new TableEntry(45, 55, 'Third Born'),
            new TableEntry(56, 65, 'Fourth Born'),
            new TableEntry(66, 80, 'Last Born'),
            new TableEntry(81, 90, 'First Born of Twins'),
            new TableEntry(91, 100, 'Illegitimate'),
        ]);
    }

    private function weight(Hero &$hero)
    {
        $hero->weight = $this->engine->tableRoller->rollTable('weight', [
            new TableEntry(1, 10, 'Skinny'),
            new TableEntry(11, 30, 'Thin'),
            new TableEntry(31, 55, 'Average'),
            new TableEntry(56, 74, 'Husky'),
            new TableEntry(75, 89, 'Pot-Belly'),
            new TableEntry(90, 100, 'Obese'),
        ]);
    }

    private function height(Hero &$hero)
    {
        $hero->height = $this->engine->tableRoller->rollTable('height', [
            new TableEntry(1, 30, 'Short'),
            new TableEntry(31, 70, 'Average'),
            new TableEntry(71, 100, 'Tall'),
        ]);
    }

    private function disposition(Hero &$hero)
    {
        $hero->disposition = $this->engine->tableRoller->rollTable('disposition', [
            new TableEntry(1, 10, 'Mean, suspicious, vengeful'),
            new TableEntry(11, 15, 'Shy, timid, tends to be a loner'),
            new TableEntry(16, 20, 'Gung-ho, guts and glory type who sees himself as a hero; Likes combat'),
            new TableEntry(21, 25, 'Worry wart, nervous, and cautious'),
            new TableEntry(26, 37, 'Hot-head, quick-tempered, emotional, but basically nice'),
            new TableEntry(38, 45, 'Schemer, gambler who likes to take chances'),
            new TableEntry(46, 50, 'Blabber-mouth, nice guy, but too talkative'),
            new TableEntry(51, 56, 'Wild man, cocky, overconfident, takes unnecessary risks'),
            new TableEntry(57, 66, 'Nice guy, friendly, courteous, and hospitable'),
            new TableEntry(67, 76, 'Snob, arrogant, feels superior to others'),
            new TableEntry(77, 84, 'Tough guy, self-reliant, cocky, a lone wolf'),
            new TableEntry(85, 89, 'Paternal, overbearing, overprotective of others, especially young characters'),
            new TableEntry(90, 94, 'Complainer, constantly aggravated about something'),
            new TableEntry(95, 100, 'Paranoid, trusts no one'),
        ]);
    }

    private function lifeSavings(Hero &$hero)
    {
        $hero->lifeSavings = $this->engine->tableRoller->rollTable('life savings', [
            new TableEntry(1, 10, 1000),
            new TableEntry(11, 20, 2000),
            new TableEntry(21, 37, 3000),
            new TableEntry(38, 59, 4000),
            new TableEntry(60, 79, 5000),
            new TableEntry(80, 90, 6000),
            new TableEntry(91, 100, 10000),
        ]);
    }

    private function landOfOrigin(Hero &$hero)
    {
        $hero->landOfOrigin = $this->engine->tableRoller->rollTable('land of origin', [
            new TableEntry(1, 10, 'Australia'),
            new TableEntry(11, 20, 'Europe; Great Britain'),
            new TableEntry(21, 51, 'United States'),
            new TableEntry(52, 68, 'Canada'),
            new TableEntry(69, 80, 'Europe; Non-English Speaking'),
            new TableEntry(81, 90, 'South America'),
            new TableEntry(91, 100, 'Asia/Middle East'),
        ]);
    }

    private function typeOfEnvironment(Hero &$hero)
    {
        $hero->environment = $this->engine->tableRoller->rollTable('environment', [
            new TableEntry(1, 20, 'Agricultural/Farm Community'),
            new TableEntry(21, 40, 'Countryside, small town, or village'),
            new TableEntry(41, 60, 'Suburb, small city, or large town'),
            new TableEntry(61, 85, 'Large City'),
            new TableEntry(86, 100, 'Medium Size City'),
        ]);
    }

    private function socialEconomicBackground(Hero &$hero)
    {
        $hero->socialEconomic = $this->engine->tableRoller->rollTable('social/economic background', [
            new TableEntry(1, 9, 'Military/Middle Class'),
            new TableEntry(10, 19, 'Laborer/Poor'),
            new TableEntry(20, 29, 'Laborer/Lower Class'),
            new TableEntry(30, 59, 'Laborer/Middle Class'),
            new TableEntry(60, 74, 'Skilled/Middle Class'),
            new TableEntry(75, 84, 'Highly Skilled/Upper Middle to Upper Class'),
            new TableEntry(85, 89, 'Political/Upper Middle Class'),
            new TableEntry(90, 100, 'Wealthy'),
        ]);
    }

    private function whenManifested(Hero &$hero)
    {
        $hero->whenManifested = $this->engine->tableRoller->rollTable('when manifested', [
            new TableEntry(1, 11, 'Child'),
            new TableEntry(12, 29, 'Preteen'),
            new TableEntry(30, 50, 'Early Teens'),
            new TableEntry(51, 74, 'Late Teens'),
            new TableEntry(75, 100, 'Recently'),
        ]);

    }

}