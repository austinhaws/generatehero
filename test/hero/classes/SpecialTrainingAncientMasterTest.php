<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class SpecialTrainingAncientMasterTest extends BaseTestRunner
{
    public function test_creation() {

        $ended = false;
        $i = 0;
        while (!$ended && ++$i) {
            $ended = true;
            $this->testArrayTools->rotation = $i + 1;

            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 40, 'power category'),
                TestRoll::doNotCareUntilAndRoll(6, 1, 'Ancient Master - MA'),
            ];

            $ended = $this->iterationSubRolls($rolls, $i, [
                [new TestRoll(100, 16, 'Ancient Master - Age'),],
                [new TestRoll(100, 33, 'Ancient Master - Age'),],
                [new TestRoll(100, 50, 'Ancient Master - Age'),],
                [new TestRoll(100, 67, 'Ancient Master - Age'),],
                [new TestRoll(100, 83, 'Ancient Master - Age'),],
                [new TestRoll(100, 100, 'Ancient Master - Age'),],
            ]) && $ended;

            $ended = $this->iterationSubRolls($rolls, $i, [
                [new TestRoll(100, 20, 'Ancient Master - Age Appearance'),],
                [new TestRoll(100, 42, 'Ancient Master - Age Appearance'),],
                [new TestRoll(100, 62, 'Ancient Master - Age Appearance'),],
                [new TestRoll(100, 78, 'Ancient Master - Age Appearance'),],
                [new TestRoll(100, 92, 'Ancient Master - Age Appearance'),],
                [new TestRoll(100, 100, 'Ancient Master - Age Appearance'),],
            ]) && $ended;


            $rolls[] = new TestRoll(false, false, 'Alignment');
            $rolls[] = TestRoll::doNotCareAnyMore(true);

            $this->runGeneration($rolls);
        }
    }
}
