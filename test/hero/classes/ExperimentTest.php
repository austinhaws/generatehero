<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class ExperimentTest extends BaseTestRunner
{

    public function experimentResult(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 20, 'Experiment: result'),],
            [new TestRoll(100, 50, 'Experiment: result'),],
            [new TestRoll(100, 70, 'Experiment: result'),],
            [new TestRoll(100, 100, 'Experiment: result'),],
        ]);
    }

    public function experimentNature(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 33, 'Experiment: nature'),],
            [new TestRoll(100, 67, 'Experiment: nature'),],
            [new TestRoll(100, 100, 'Experiment: nature'),],
        ]);
    }

    public function experimentSideEffects(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new testRoll(100, 8, 'Experiment: Side Effects'),],
            [new testRoll(100, 10, 'Experiment: Side Effects'),],
            [new testRoll(100, 11, 'Experiment: Side Effects'),],
            [new testRoll(100, 13, 'Experiment: Side Effects'),],
            [new testRoll(100, 14, 'Experiment: Side Effects'),],
            [new testRoll(100, 16, 'Experiment: Side Effects'),],
            [new testRoll(100, 24, 'Experiment: Side Effects'),],
            [new testRoll(100, 33, 'Experiment: Side Effects'),],
            [new testRoll(100, 40, 'Experiment: Side Effects'),],
            [new testRoll(100, 47, 'Experiment: Side Effects'),],
            [new testRoll(100, 54, 'Experiment: Side Effects'),],
            [new testRoll(100, 63, 'Experiment: Side Effects'),],
            [new testRoll(100, 70, 'Experiment: Side Effects'),],
            [new testRoll(100, 77, 'Experiment: Side Effects'),],
            [new testRoll(100, 84, 'Experiment: Side Effects'),],
            [new testRoll(100, 93, 'Experiment: Side Effects'),],
            [
                new testRoll(100, 100, 'Experiment: Side Effects'),
                (new TestRoll())->dontCareUntilAndGetNext('Sponsoring Organization'),
            ],
        ]);
    }

    public function sponsoringOrganization(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 50, 'Sponsoring Organization'),],
            [new TestRoll(100, 75, 'Sponsoring Organization'),],
            [new TestRoll(100, 80, 'Sponsoring Organization'),],
            [new TestRoll(100, 87, 'Sponsoring Organization'),],
            [new TestRoll(100, 94, 'Sponsoring Organization'),],
            [new TestRoll(100, 100, 'Sponsoring Organization'),],
        ]);
    }

    public function sponsorStatus(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
           [new TestRoll(100, 21, 'Sponsor Status'),],
           [new TestRoll(100, 45, 'Sponsor Status'),],
           [new TestRoll(100, 58, 'Sponsor Status'),],
           [new TestRoll(100, 64, 'Sponsor Status'),],
           [new TestRoll(100, 77, 'Sponsor Status'),],
           [new TestRoll(100, 89, 'Sponsor Status'),],
           [new TestRoll(100, 100, 'Sponsor Status'),],
        ]);
    }

    public function powers(&$rolls, $i)
    {
        if ($i % 2) {
            $rolls[] = new TestRoll(100, 1, 'Experiment Power Type');
        } else {
            $rolls[] = new TestRoll(100, 100, 'Experiment Power Type');
        }
        $this->testArrayTools->rotation = $i;
        return true;
    }

    public function test_iteration()
    {
        $this->runIterations([
            'experimentNature',
            'experimentResult',
            'experimentSideEffects',
            'sponsoringOrganization',
            'sponsorStatus',
            'powers',
        ], [
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 10, 'power category'),
            (new TestRoll())->dontCareUntilAndGetNext('Experiment: nature'),
        ]);
    }
}
