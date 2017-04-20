<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class MutantsTest extends BaseTestRunner
{
    public function mutant_unusual(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(112, 30, 'Mutant: unusual'),],
            [new TestRoll(112, 34, 'Mutant: unusual'),],
            [new TestRoll(112, 39, 'Mutant: unusual'),],
            [new TestRoll(112, 40, 'Mutant: unusual'),],
            [new TestRoll(112, 41, 'Mutant: unusual'),],
            [new TestRoll(112, 42, 'Mutant: unusual'),],
            [new TestRoll(112, 43, 'Mutant: unusual'),],
            [new TestRoll(112, 48, 'Mutant: unusual'),],
            [new TestRoll(112, 49, 'Mutant: unusual'),],
            [new TestRoll(112, 50, 'Mutant: unusual'),],
            [new TestRoll(112, 51, 'Mutant: unusual'),],
            [new TestRoll(112, 52, 'Mutant: unusual'),],
            [new TestRoll(112, 53, 'Mutant: unusual'),],
            [new TestRoll(112, 54, 'Mutant: unusual'),],
            [new TestRoll(112, 55, 'Mutant: unusual'),],
            [new TestRoll(112, 56, 'Mutant: unusual'),],
            [new TestRoll(112, 57, 'Mutant: unusual'),],
            [new TestRoll(112, 58, 'Mutant: unusual'),],
            [new TestRoll(112, 59, 'Mutant: unusual'),],
            [new TestRoll(112, 60, 'Mutant: unusual'),],
            [new TestRoll(112, 61, 'Mutant: unusual'),],
            [new TestRoll(112, 62, 'Mutant: unusual'),],
            [new TestRoll(112, 64, 'Mutant: unusual'),],
            [new TestRoll(112, 68, 'Mutant: unusual'),],
            [new TestRoll(112, 72, 'Mutant: unusual'),],
            [new TestRoll(112, 76, 'Mutant: unusual'),],
            [new TestRoll(112, 79, 'Mutant: unusual'),],
            [new TestRoll(112, 84, 'Mutant: unusual'),],
            [new TestRoll(112, 89, 'Mutant: unusual'),],
            [new TestRoll(112, 94, 'Mutant: unusual'),],
            [new TestRoll(112, 100, 'Mutant: unusual'),],
            [new TestRoll(112, 101, 'Mutant: unusual'),],
            [new TestRoll(112, 102, 'Mutant: unusual'),],
            [new TestRoll(112, 103, 'Mutant: unusual'),],
            [new TestRoll(112, 104, 'Mutant: unusual'),],
            [new TestRoll(112, 105, 'Mutant: unusual'),],
            [new TestRoll(112, 106, 'Mutant: unusual'),],
            [new TestRoll(112, 107, 'Mutant: unusual'),],
            [new TestRoll(112, 108, 'Mutant: unusual'),],
            [new TestRoll(112, 109, 'Mutant: unusual'),],
            [new TestRoll(112, 110, 'Mutant: unusual'),],
            [new TestRoll(112, 111, 'Mutant: unusual'),],
            [new TestRoll(112, 112, 'Mutant: unusual'),],
        ]);

    }
    public function mutant_cause(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 20, 'Mutant: cause'),],
            [new TestRoll(100, 40, 'Mutant: cause'),],
            [new TestRoll(100, 60, 'Mutant: cause'),],
            [new TestRoll(100, 80, 'Mutant: cause'),],
            [new TestRoll(100, 100, 'Mutant: cause'),],
        ]);
    }

    public function mutant_abilities(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(2, 2, 'Mutant Abilities'),],
            [new TestRoll(2, 1, 'Mutant Abilities'),],
        ]);
    }

    public function test_mutantHuman()
    {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $this->testArrayTools->rotation = $i + 1;
            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 50, 'power category'),
                new TestRoll(2, 1, 'Mutant Type'),
            ];

            $ended = $this->runIterationGroup([
                'mutant_cause',
                'mutant_unusual',
            ], $rolls, $i);

            $rolls[] = new TestRoll(100, 1, 'Has Car?');
            $rolls[] = new TestRoll(6, 3, 'Car Age');


            $ended = $this->runIterationGroup([
                'mutant_abilities',
            ], $rolls, $i) && $ended;

            $rolls[] = new TestRoll(false, false, 'Education Level', 1, true);

            $this->testRoller->setTestRolls($rolls);

            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();

            $this->assertTrue(strpos(get_class($hero->class), 'Mutants') !== false);

            if ($i === 2) {
                $this->assertTrue(count($hero->psionics) > 0);
            }
        }
    }
}
