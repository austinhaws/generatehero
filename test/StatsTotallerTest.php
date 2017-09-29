<?php

namespace Heroes\test\utilities;

use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\StatsTotaller;
use Heroes\tests\BaseTestRunner;

class StatsTotallerTest extends BaseTestRunner
{
    public function testApplySet()
    {
        // create a hero
        /** @var Hero $hero */
        $hero = new Hero();

        // give hero some bonuses
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 3, 'test A'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_ALL, 13, 'test A'));

        // run totaller
        $statsTotaller = new StatsTotaller($this->engine);
        $statsTotaller->calculateNonAttributeTotals($hero);

        // should have given skill a start value of 3 and then added 13, but not added any other sklils
        $this->assertEquals($hero->skillTotals[BonusTargets::SKILL_CLIMBING], 16);
        $this->assertFalse(isset($hero->skillTotals[BonusTargets::SKILL_FORGERY]));
    }

    public function testMultiplyBonus() {
        // create a hero
        /** @var Hero $hero */
        $hero = new Hero();

        // give hero some bonuses
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 3, 'test A'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::SKILL_CLIMBING, 4, 'test A'));

        // run totaller
        $statsTotaller = new StatsTotaller($this->engine);
        $statsTotaller->calculateNonAttributeTotals($hero);

        $this->assertEquals($hero->skillTotals[BonusTargets::SKILL_CLIMBING], 12);
    }

    public function testMinimumNo() {
        // minimum occurs at end while set works at beginning of stats calculation

        // create a hero
        /** @var Hero $hero */
        $hero = new Hero();

        // give hero some bonuses
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 5, 'test A'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_MINIMUM, BonusTargets::SKILL_CLIMBING, 4, 'test B'));

        // run totaller
        $statsTotaller = new StatsTotaller($this->engine);
        $statsTotaller->calculateNonAttributeTotals($hero);

        $this->assertEquals($hero->skillTotals[BonusTargets::SKILL_CLIMBING], 5);
    }

    public function testMinimumYes() {
        // minimum occurs at end while set works at beginning of stats calculation

        // create a hero
        /** @var Hero $hero */
        $hero = new Hero();

        // give hero some bonuses
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 5, 'test A'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_MINIMUM, BonusTargets::SKILL_CLIMBING, 6, 'test B'));

        // run totaller
        $statsTotaller = new StatsTotaller($this->engine);
        $statsTotaller->calculateNonAttributeTotals($hero);

        // should have given skill a start value of 3 and then added 13, but not added any other sklils
        $this->assertEquals($hero->skillTotals[BonusTargets::SKILL_CLIMBING], 6);
    }
}
