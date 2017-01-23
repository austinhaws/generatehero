<?php
namespace Heroes\tables;

use Heroes\engine\Table;
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
            new Table(1, 30, 'First Born'),
            new Table(31, 44, 'Second Born'),
            new Table(45, 55, 'Third Born'),
            new Table(56, 65, 'Fourth Born'),
            new Table(66, 80, 'Last Born'),
            new Table(81, 90, 'First Born of Twins'),
            new Table(91, 100, 'Illegitimate'),
        ]);
    }

    private function weight(Hero &$hero)
    {
        $hero->weight = $this->engine->tableRoller->rollTable('weight', [
            new Table(1, 10, 'Skinny'),
            new Table(11, 30, 'Thin'),
            new Table(31, 55, 'Average'),
            new Table(56, 74, 'Husky'),
            new Table(75, 89, 'Pot-Belly'),
            new Table(90, 100, 'Obese'),
        ]);
    }

    private function height(Hero &$hero)
    {
        $hero->height = $this->engine->tableRoller->rollTable('height', [
            new Table(1, 30, 'Short'),
            new Table(31, 70, 'Average'),
            new Table(71, 100, 'Tall'),
        ]);
    }

    private function disposition(Hero &$hero)
    {
        $hero->disposition = $this->engine->tableRoller->rollTable('disposition', [
            new Table(1, 10, 'Mean, suspicious, vengeful'),
            new Table(11, 15, 'Shy, timid, tends to be a loner'),
            new Table(16, 20, 'Gung-ho, guts and glory type who sees himself as a hero; Likes combat'),
            new Table(21, 25, 'Worry wart, nervous, and cautious'),
            new Table(26, 37, 'Hot-head, quick-tempered, emotional, but basically nice'),
            new Table(38, 45, 'Schemer, gambler who likes to take chances'),
            new Table(46, 50, 'Blabber-mouth, nice guy, but too talkative'),
            new Table(51, 56, 'Wild man, cocky, overconfident, takes unnecessary risks'),
            new Table(57, 66, 'Nice guy, friendly, courteous, and hospitable'),
            new Table(67, 76, 'Snob, arrogant, feels superior to others'),
            new Table(77, 84, 'Tough guy, self-reliant, cocky, a lone wolf'),
            new Table(85, 89, 'Paternal, overbearing, overprotective of others, especially young characters'),
            new Table(90, 94, 'Complainer, constantly aggravated about something'),
            new Table(95, 100, 'Paranoid, trusts no one'),
        ]);
    }

    private function lifeSavings(Hero &$hero)
    {
        $hero->lifeSavings = $this->engine->tableRoller->rollTable('life savings', [
            new Table(1, 10, 1000),
            new Table(11, 20, 2000),
            new Table(21, 37, 3000),
            new Table(38, 59, 4000),
            new Table(60, 79, 5000),
            new Table(80, 90, 6000),
            new Table(91, 100, 10000),
        ]);
    }

    private function landOfOrigin(Hero &$hero)
    {
        $hero->landOfOrigin = $this->engine->tableRoller->rollTable('land of origin', [
            new Table(1, 10, 'Australia'),
            new Table(11, 20, 'Europe; Great Britain'),
            new Table(21, 51, 'United States'),
            new Table(52, 68, 'Canada'),
            new Table(69, 80, 'Europe; Non-English Speaking'),
            new Table(81, 90, 'South America'),
            new Table(91, 100, 'Asia/Middle East'),
        ]);
    }

    private function typeOfEnvironment(Hero &$hero)
    {
        $hero->environment = $this->engine->tableRoller->rollTable('environment', [
            new Table(1, 20, 'Agricultural/Farm Community'),
            new Table(21, 40, 'Countryside, small town, or village'),
            new Table(41, 60, 'Suburb, small city, or large town'),
            new Table(61, 85, 'Large City'),
            new Table(86, 100, 'Medium Size City'),
        ]);
    }

    private function socialEconomicBackground(Hero &$hero)
    {
        $hero->socialEconomic = $this->engine->tableRoller->rollTable('social/economic background', [
            new Table(1, 9, 'Military/Middle Class'),
            new Table(10, 19, 'Laborer/Poor'),
            new Table(20, 29, 'Laborer/Lower Class'),
            new Table(30, 59, 'Laborer/Middle Class'),
            new Table(60, 74, 'Skilled/Middle Class'),
            new Table(75, 84, 'Highly Skilled/Upper Middle to Upper Class'),
            new Table(85, 89, 'Political/Upper Middle Class'),
            new Table(90, 100, 'Wealthy'),
        ]);
    }

    private function whenManifested(Hero &$hero)
    {
        $hero->whenManifested = $this->engine->tableRoller->rollTable('when manifested', [
            new Table(1, 11, 'Child'),
            new Table(12, 29, 'Preteen'),
            new Table(30, 50, 'Early Teens'),
            new Table(51, 74, 'Late Teens'),
            new Table(75, 100, 'Recently'),
        ]);

    }

}