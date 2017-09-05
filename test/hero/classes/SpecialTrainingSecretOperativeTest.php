<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class SpecialTrainingSecretOperativeTest extends BaseTestRunner
{
    public function test_creation() {

        $ended = false;
        $i = 0;
        while (!$ended && ++$i) {
            $this->engine->arrayTools->rotation = mt_rand(1, 100);

            $ended = true;
            $this->testArrayTools->rotation = $i + 1;

            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 44, 'power category'),
            ];

            $ended = $this->iterationSubRolls($rolls, $i, [
                    [new TestRoll(100, 1, 'Secret Operative - Hand to Hand'),],
                    [new TestRoll(100, 100, 'Secret Operative - Hand to Hand'),],
                ]) && $ended;

            $rolls[] = new TestRoll(6, 3, 'Secret Operative - PS');
            $rolls[] = new TestRoll(4, 3, 'Secret Operative - PP');
            $rolls[] = new TestRoll(6, 3, 'Secret Operative - PE');
            $rolls[] = new TestRoll(6, 3, 'Secret Operative - MA');

            $ended = $this->iterationSubRolls($rolls, $i, [
                    [new TestRoll(100, 16, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 36, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 44, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 52, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 60, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 63, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 67, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 71, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 75, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 77, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 80, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 83, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 86, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 90, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 95, 'Secret Operative - Organization'),],
                    [new TestRoll(100, 100, 'Secret Operative - Organization'),],
                ]) && $ended;

            $ended = $this->iterationSubRolls($rolls, $i, [
                    [new TestRoll(100, 17, 'Secret Operative - Organization Status'),],
                    [new TestRoll(100, 31, 'Secret Operative - Organization Status'),],
                    [new TestRoll(100, 34, 'Secret Operative - Organization Status'),],
                    [new TestRoll(100, 51, 'Secret Operative - Organization Status'),],
                    [new TestRoll(100, 68, 'Secret Operative - Organization Status'),],
                    [new TestRoll(100, 84, 'Secret Operative - Organization Status'),],
                    [new TestRoll(100, 100, 'Secret Operative - Organization Status'),],
                ]) && $ended;


            $rolls[] = new TestRoll(false, false, 'Alignment');
            $rolls[] = TestRoll::doNotCareAnyMore(true);

            $this->runGeneration($rolls);
        }
    }
}
