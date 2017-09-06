<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class SpecialTrainingSuperSleuthTest extends BaseTestRunner
{
    public function test_creation() {

        $ended = false;
        $i = 0;
        while (!$ended && ++$i) {
            $this->engine->arrayTools->rotation = mt_rand(1, 100);

            $ended = true;
            $this->testArrayTools->rotation = $i + 1;

            $rolls = [
                TestRoll::doNotCareUntilAndRoll(100, 48, 'power category'),
                TestRoll::doNotCareUntilAndRoll(100, 48, 'Super Sleuth - pilot'),
                TestRoll::doNotCareUntilAndRoll(100, 48, 'Has Car?'),
                new TestRoll(6, 1, 'Car Age'),
            ];

            $rolls[] = new TestRoll(false, false, 'Alignment');
            $rolls[] = TestRoll::doNotCareAnyMore(true);

            $this->runGeneration($rolls);
        }
    }
}
