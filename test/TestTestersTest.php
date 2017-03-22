<?php

namespace Heroes\test;

use Heroes\engine\Roll;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class TestTestersTest extends BaseTestRunner
{

    public function testTestRoller() {

        $this->testRoller->setTestRolls([
            new TestRoll(6, 6, 'first roll'),
            new TestRoll(8, 4, 'second roll'),
        ]);

        $this->assertEquals(6, $this->testRoller->rollDice(new Roll('first roll', 1, 6)));
        $this->assertEquals(4, $this->testRoller->rollDice(new Roll('second roll', 1, 8)));

        $this->testRoller->verifyTestRolls();
    }
}