<?php

namespace Heroes\test;

use Heroes\engine\Roll;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class TestTestersTest extends \PHPUnit_Framework_TestCase
{

    public function testTestRoller() {
        $testRoller = new TestRoller();

        $testRoller->setTestRolls([
            new TestRoll(6, 6, 'first roll'),
            new TestRoll(8, 4, 'second roll'),
        ]);

        $this->assertEquals(6, $testRoller->rollDice(new Roll('first roll', 1, 6)));
        $this->assertEquals(4, $testRoller->rollDice(new Roll('second roll', 1, 8)));

        $testRoller->verifyTestRolls();
    }
}