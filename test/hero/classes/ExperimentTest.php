<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class ExperimentTest extends BaseTestRunner
{

    private function experimentResult($rolls, $i)
    {
        $ended = false;
        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 20, 'Experiment: result');
                break;
            case 1:
                $rolls[] = new TestRoll(100, 50, 'Experiment: result');
                break;
            case 2:
                $rolls[] = new TestRoll(100, 70, 'Experiment: result');
                break;
            case 3:
                $rolls[] = new TestRoll(100, 100, 'Experiment: result');
                break;

        }
        return [$ended, $rolls];
    }

    private function experimentNature($rolls, $i)
    {
        $ended = false;
        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 33, 'Experiment: nature');
                break;
            case 1:
                $rolls[] = new TestRoll(100, 67, 'Experiment: nature');
                break;
            case 2:
                $rolls[] = new TestRoll(100, 100, 'Experiment: nature');
                break;
        }
        return [$ended, $rolls];
    }


    /**
     * create rolls based on the iteration until all the iterations have been exercised
     */
    /**
     * @param $i int the current iteration
     * @return bool|array true if all the iterations of all the possibilities have been used or array of test rolls
     * @throws \Exception if $i% is invalid for a section
     */
    private function rollsIteration($i)
    {
        $rolls = [
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 10, 'power category'),
            (new TestRoll())->dontCareUntilAndGetNext('Experiment: nature'),
        ];

        $ended = $this->experimentNature($rolls, $i);
        $ended = $ended && $this->experimentResult($rolls, $i);

//        $rolls[] = (new TestRoll())->dontCareAnyMore();

        return $ended ? false : $rolls;
    }

    public function test_experiment()
    {
        $i = 0;
        while ($rolls = $this->rollsIteration($i++)) {
            $this->testRoller->setTestRolls($rolls);

            $this->heroGenerator->generate();

            $this->testRoller->verifyTestRolls();
        }
    }
}
