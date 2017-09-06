<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class SpecialTrainingStageMagicianTest extends BaseTestRunner
{
    public function test_creation() {

        $ended = false;
        $i = 0;
        while (!$ended && ++$i) {
            $this->engine->arrayTools->rotation = mt_rand(1, 100);

            $ended = true;
            $this->testArrayTools->rotation = $i + 1;

            $rolls = [
                TestRoll::doNotCareUntilAndRoll(100, 46, 'power category'),
                TestRoll::doNotCareUntilAndRoll(6, 1, 'Stage Magician - MA'),
                new TestRoll(6, 1, 'Stage Magician - PP'),
                new TestRoll(4, 1, 'Stage Magician - PB'),
            ];

            $ended = $this->iterationSubRolls($rolls, $i, [
                    [new TestRoll(100, 12, 'Stage Magician - Gimmick Money'),],
                    [new TestRoll(100, 24, 'Stage Magician - Gimmick Money'),],
                    [new TestRoll(100, 38, 'Stage Magician - Gimmick Money'),],
                    [new TestRoll(100, 52, 'Stage Magician - Gimmick Money'),],
                    [new TestRoll(100, 65, 'Stage Magician - Gimmick Money'),],
                    [new TestRoll(100, 78, 'Stage Magician - Gimmick Money'),],
                    [new TestRoll(100, 90, 'Stage Magician - Gimmick Money'),],
                    [new TestRoll(100, 100, 'Stage Magician - Gimmick Money'),],
                ]) && $ended;

            $rolls[] = new TestRoll(100, 3, 'Has Car?');
            $rolls[] = new TestRoll(6, 3, 'Car Age');




            $rolls[] = new TestRoll(false, false, 'Alignment');
            $rolls[] = TestRoll::doNotCareAnyMore(true);

            $this->runGeneration($rolls);
        }
    }
}
