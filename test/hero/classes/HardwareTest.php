<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class HardwareTest extends BaseTestRunner
{
    public function test_experimentElectrical()
    {
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 90, 'power category'),
            (new TestRoll())->dontCareUntil('Hardware Power Type')->andRoll(3, 1, 'Hardware Power Type'),
            new TestRoll(100, 10, 'Hardware: Electrical - Equipment Budget'),
            new TestRoll(4, 1, 'Hardware: Electrical - Workshop Budget'),
            new TestRoll(4, 2, 'Hardware: Electrical - Workshop Budget'),
            new TestRoll(100, 1, 'Alignment'),
            (new TestRoll())->dontCareAnyMore(),
        ]);

        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();
        $this->assertTrue(strpos(get_class($hero->class), 'Hardware') !== false);
    }

    public function test_experimentMechanicalLowBudget()
    {
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 90, 'power category'),
            (new TestRoll())->dontCareUntil('Hardware Power Type')->andRoll(3, 2, 'Hardware Power Type'),

            new TestRoll(4, 1, 'Hardware: Mechanical - shop'),
            new TestRoll(4, 2, 'Hardware: Mechanical - shop'),
            new TestRoll(4, 3, 'Hardware: Mechanical - shop'),
            new TestRoll(100, 50, 'Hardware: Mechanical - Vehicle Budget'),

            new TestRoll(100, 1, 'Alignment'),
            (new TestRoll())->dontCareAnyMore(),
        ]);

        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();
        $this->assertTrue(strpos(get_class($hero->class), 'Hardware') !== false);

    }

    public function test_experimentMechanicalHighBudget()
    {
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 90, 'power category'),
            (new TestRoll())->dontCareUntil('Hardware Power Type')->andRoll(3, 2, 'Hardware Power Type'),

            new TestRoll(4, 1, 'Hardware: Mechanical - shop'),
            new TestRoll(4, 2, 'Hardware: Mechanical - shop'),
            new TestRoll(4, 3, 'Hardware: Mechanical - shop'),
            new TestRoll(100, 100, 'Hardware: Mechanical - Vehicle Budget'),
            new TestRoll(100, 55, 'Hardware: Mechanical - Sponsor Status'),

            new TestRoll(100, 1, 'Alignment'),
            (new TestRoll())->dontCareAnyMore(),
        ]);

        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();
        $this->assertTrue(strpos(get_class($hero->class), 'Hardware') !== false);

    }
}
