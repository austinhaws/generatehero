<?php
namespace Heroes\tables;

use Heroes\engine\TableEntry;
use Heroes\hero\Hero;

class CharacterBasics extends TableBase
{
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
            new TableEntry(30, 'First Born'),
            new TableEntry(44, 'Second Born'),
            new TableEntry(55, 'Third Born'),
            new TableEntry(65, 'Fourth Born'),
            new TableEntry(80, 'Last Born'),
            new TableEntry(90, 'First Born of Twins'),
            new TableEntry(100, 'Illegitimate'),
        ]);
    }

    private function weight(Hero &$hero)
    {
        if ($hero->weight === false) {
            $hero->weightDescription = $this->engine->tableRoller->rollTable('weight', [
                new TableEntry(10, 'Skinny'),
                new TableEntry(30, 'Thin'),
                new TableEntry(55, 'Average'),
                new TableEntry(74, 'Husky'),
                new TableEntry(89, 'Pot-Belly'),
                new TableEntry(100, 'Obese'),
            ]);
        }
    }

    private function height(Hero &$hero)
    {
        if ($hero->height === false) {
            $hero->height = $this->engine->tableRoller->rollTable('height', [
                new TableEntry(30, 'Short'),
                new TableEntry(70, 'Average'),
                new TableEntry(100, 'Tall'),
            ]);
        }
    }

    private function disposition(Hero &$hero)
    {
        $hero->disposition = $this->engine->tableRoller->rollTable('disposition', [
            new TableEntry(10, 'Mean, suspicious, vengeful'),
            new TableEntry(15, 'Shy, timid, tends to be a loner'),
            new TableEntry(20, 'Gung-ho, guts and glory type who sees himself as a hero; Likes combat'),
            new TableEntry(25, 'Worry wart, nervous, and cautious'),
            new TableEntry(37, 'Hot-head, quick-tempered, emotional, but basically nice'),
            new TableEntry(45, 'Schemer, gambler who likes to take chances'),
            new TableEntry(50, 'Blabber-mouth, nice guy, but too talkative'),
            new TableEntry(56, 'Wild man, cocky, overconfident, takes unnecessary risks'),
            new TableEntry(66, 'Nice guy, friendly, courteous, and hospitable'),
            new TableEntry(76, 'Snob, arrogant, feels superior to others'),
            new TableEntry(84, 'Tough guy, self-reliant, cocky, a lone wolf'),
            new TableEntry(89, 'Paternal, overbearing, overprotective of others, especially young characters'),
            new TableEntry(94, 'Complainer, constantly aggravated about something'),
            new TableEntry(100, 'Paranoid, trusts no one'),
        ]);
    }

    private function lifeSavings(Hero &$hero)
    {
        $hero->lifeSavings = $this->engine->tableRoller->rollTable('life savings', [
            new TableEntry(10, 1000),
            new TableEntry(20, 2000),
            new TableEntry(37, 3000),
            new TableEntry(59, 4000),
            new TableEntry(79, 5000),
            new TableEntry(90, 6000),
            new TableEntry(100, 10000),
        ]);
    }

    private function landOfOrigin(Hero &$hero)
    {
        $hero->landOfOrigin = $this->engine->tableRoller->rollTable('land of origin', [
            new TableEntry(10, 'Australia'),
            new TableEntry(20, 'Europe; Great Britain'),
            new TableEntry(51, 'United States'),
            new TableEntry(68, 'Canada'),
            new TableEntry(80, 'Europe; Non-English Speaking'),
            new TableEntry(90, 'South America'),
            new TableEntry(100, 'Asia/Middle East'),
        ]);
    }

    private function typeOfEnvironment(Hero &$hero)
    {
        $hero->environment = $this->engine->tableRoller->rollTable('environment', [
            new TableEntry(20, 'Agricultural/Farm Community'),
            new TableEntry(40, 'Countryside, small town, or village'),
            new TableEntry(60, 'Suburb, small city, or large town'),
            new TableEntry(85, 'Large City'),
            new TableEntry(100, 'Medium Size City'),
        ]);
    }

    private function socialEconomicBackground(Hero &$hero)
    {
        $hero->socialEconomic = $this->engine->tableRoller->rollTable('social/economic background', [
            new TableEntry(9, 'Military/Middle Class'),
            new TableEntry(19, 'Laborer/Poor'),
            new TableEntry(29, 'Laborer/Lower Class'),
            new TableEntry(59, 'Laborer/Middle Class'),
            new TableEntry(74, 'Skilled/Middle Class'),
            new TableEntry(84, 'Highly Skilled/Upper Middle to Upper Class'),
            new TableEntry(89, 'Political/Upper Middle Class'),
            new TableEntry(100, 'Wealthy'),
        ]);
    }

    private function whenManifested(Hero &$hero)
    {
        $hero->whenManifested = $this->engine->tableRoller->rollTable('when manifested', [
            new TableEntry(11, 'Child'),
            new TableEntry(29, 'Preteen'),
            new TableEntry(50, 'Early Teens'),
            new TableEntry(74, 'Late Teens'),
            new TableEntry(100, 'Recently'),
        ]);

    }

}