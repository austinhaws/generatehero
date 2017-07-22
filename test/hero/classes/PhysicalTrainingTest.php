<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class PhysicalTrainingTest extends BaseTestRunner
{
    public function test_physicalTraining() {
        $educationRolls = [
            9,  18, 27, 36, 45, 54,
            63, 72, 81, 90, 100,
        ];

        for ($i = 0; $i < 20; $i++) {
            $this->testArrayTools->rotation = $i + 1;
            
            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 70, 'power category'),
                (new TestRoll())->dontCareUntil('Education Level')
                    ->andRoll(100, $educationRolls[$i % count($educationRolls)], 'Education Level'),
                (new TestRoll())->dontCareUntil('Physical Training: Hand to Hand type')
                    ->andRoll(2, $i % 2 + 1, 'Physical Training: Hand to Hand type'),
                (new TestRoll())->dontCareUntil('Physical Training: Base SDC')->dontCareAnyMore(),
            ];

            $this->testRoller->setTestRolls($rolls);

            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();

            $this->assertTrue(strpos(get_class($hero->class), 'PhysicalTraining') !== false);
        }
    }
}
