<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestArrayTools;
use Heroes\tests\utilities\TestRoll;

class BionicsTest extends BaseTestRunner
{
    public function test_bionics()
    {
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 30, 'power category'),
            new TestRoll(100, 100, 'Bionic Budget'),
            new TestRoll(100, 100, 'Body Part Skinnable'),
            new TestRoll(100, 100, 'Body Part Skinnable: Type'),
            new TestRoll(100, 100, 'Bionic Location: Multiple Ors'),
            new TestRoll(100, 100, 'Bionic Location: Multiple Ors'),
            (new testRoll())->dontCareUntil('Bionic: Conditions for Bionic Reconstruction')->andRoll(100, 1, 'Bionic: Conditions for Bionic Reconstruction'),
            new TestRoll(100, 1, 'Bionic: Sponsor'),
            new TestRoll(100, 1, 'Bionic: Sponsor Status'),
            new TestRoll(100, 1, 'Bionic Has Car?'),
            new TestRoll(6, 3, 'Bionic Car Age'),
            (new TestRoll())->dontCareAnyMore(),
        ]);

        $hero = $this->heroGenerator->generate();

        $this->testRoller->verifyTestRolls();

        $this->assertTrue($hero->class->budgetRemaining < 8000, 'Should have spent as much as possible; no bionic costs less than this');
    }

    public function test_randomBionics()
    {
        // way tricky to run all possible bionics combinations, so just run through random cycles to check for problems... ya, sorry if this generates an error
        $this->testArrayTools = false;
        for ($x = 0; $x < 10; $x++) {
            $this->testRoller->setTestRolls([
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 30, 'power category'),
                (new TestRoll())->dontCareAnyMore(),
            ]);

            $hero = $this->heroGenerator->generate();

            $this->testRoller->verifyTestRolls();

            $this->assertTrue($hero->class->budgetRemaining < 8000, 'Should have spent as much as possible; no bionic costs less than this');
        }

        $this->testArrayTools = TestArrayTools::DEFAULT_ROTATION;
    }
}
