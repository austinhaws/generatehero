<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class SpecialTrainingHunterVigilanteTest extends BaseTestRunner
{
    public function test_creation() {

        $ended = false;
        $i = 0;
        while (!$ended && ++$i) {
            $this->engine->arrayTools->rotation = mt_rand(1, 100);

            $ended = true;
            $this->testArrayTools->rotation = $i + 1;

            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 42, 'power category'),
                new TestRoll(4, 1, 'Hunter Vigilante - PE'),
                new TestRoll(6, 3, 'Hunter Vigilante - Speed'),
            ];

            $ended = $this->iterationSubRolls($rolls, $i, [
                    [new TestRoll(100, 1, 'Hunter Vigilante - Hand to Hand'),],
                    [new TestRoll(100, 100, 'Hunter Vigilante - Hand to Hand'),],
                ]) && $ended;

            $rolls[] = new TestRoll(100, 5, 'Hunter Vigilante - experience');
            $rolls[] = new TestRoll(100, 3, 'Hunter Vigilante - money');
            $rolls[] = new TestRoll(100, 100, 'Has Car?');


            $rolls[] = new TestRoll(false, false, 'Alignment');
            $rolls[] = TestRoll::doNotCareAnyMore(true);

            $this->runGeneration($rolls);
        }
    }
}
