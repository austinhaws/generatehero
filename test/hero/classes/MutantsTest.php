<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class MutantsTest extends BaseTestRunner
{
    private $iterationOrgRelationEnded = false;

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

    public function test_mutantAnimal() {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $this->testArrayTools->rotation = $i + 1;
            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 50, 'power category'),
                new TestRoll(2, 2, 'Mutant Type'),
            ];

            $ended = $this->runIterationGroup([
                'animalMutantCause',
                'animalMutantEducation',
            ], $rolls, $i);

            if ($i === 7 || $i === 8) {
                $rolls[] = new TestRoll(3, 1, 'Mechanical Program Skills');
            }

            if ($i < 12) {
                $ended = $this->runIterationGroup([
                        'animalMutantOrganization',
                    ], $rolls, $i) && $ended;
            }

            $rolls[] = new TestRoll(false, false, 'Alignment', false, true);

            $this->testRoller->setTestRolls($rolls);

            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();

            $this->assertTrue(strpos(get_class($hero->class), 'Mutants') !== false);
        }
    }

    public function animalMutantCause(&$rolls, $i)
    {
        $ended = [
            $this->iterationSubRolls($rolls, $i, [
                // do 10 experiments so that can test all organization relationships
                [new TestRoll(100, 100, 'Mutant Animal: Cause'),],
                [new TestRoll(100, 100, 'Mutant Animal: Cause'),],
                [new TestRoll(100, 100, 'Mutant Animal: Cause'),],
                [new TestRoll(100, 100, 'Mutant Animal: Cause'),],
                [new TestRoll(100, 100, 'Mutant Animal: Cause'),],
                [new TestRoll(100, 100, 'Mutant Animal: Cause'),],
                [new TestRoll(100, 100, 'Mutant Animal: Cause'),],
                [new TestRoll(100, 100, 'Mutant Animal: Cause'),],
                [new TestRoll(100, 100, 'Mutant Animal: Cause'),],
                [new TestRoll(100, 100, 'Mutant Animal: Cause'),],

                // wild educations
                [new TestRoll(100, 14, 'Mutant Animal: Cause'),],
                [new TestRoll(100, 60, 'Mutant Animal: Cause'),],
            ])
        ];

        // experiment
        if ($i < 10) {
            $ended[] = $this->runIterationGroup([
                'animalMutantOrganizationRelationship',
            ], $rolls, $i);
            // only gets to this test once, so only going to be able to test one of them, sorry
            $this->iterationOrgRelationEnded = true;
        } else {
            $ended[] = $this->iterationOrgRelationEnded;
        }
        // all have to be ended in order to be ended
        return array_reduce($ended, function ($result, $end) {
            return $result && $end;
        }, true);

    }

    public function animalMutantEducation(&$rolls, $i)
    {
        if ($i < 12 && ($i >= 10 || $i === 2 || $i === 4)) {
            $ended = $this->iterationSubRolls($rolls, $i, [
                [new TestRoll(100, 20, 'Mutant Animal: Wild Education'),],
                [new TestRoll(100, 40, 'Mutant Animal: Wild Education'),],
                [new TestRoll(100, 90, 'Mutant Animal: Wild Education'),],
                [new TestRoll(100, 100, 'Mutant Animal: Wild Education'),],
            ]);
        } else {
            $ended = $i >= 12;
        }

        return $ended;
    }

    public function animalMutantOrganization(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 25, 'Mutant Animal: Organization'),],
            [new TestRoll(100, 45, 'Mutant Animal: Organization'),],
            [new TestRoll(100, 50, 'Mutant Animal: Organization'),],
            [new TestRoll(100, 55, 'Mutant Animal: Organization'),],
            [new TestRoll(100, 60, 'Mutant Animal: Organization'),],
            [new TestRoll(100, 65, 'Mutant Animal: Organization'),],
            [new TestRoll(100, 70, 'Mutant Animal: Organization'),],
            [new TestRoll(100, 75, 'Mutant Animal: Organization'),],
            [new TestRoll(100, 100, 'Mutant Animal: Organization'),],
        ]);
    }

    public function animalMutantOrganizationRelationship(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 10, 'Mutant Animal: organization relationship'),],
            [new TestRoll(100, 20, 'Mutant Animal: organization relationship'),],
            [new TestRoll(100, 30, 'Mutant Animal: organization relationship'),],
            [new TestRoll(100, 40, 'Mutant Animal: organization relationship'),],
            [new TestRoll(100, 50, 'Mutant Animal: organization relationship'),],
            [new TestRoll(100, 60, 'Mutant Animal: organization relationship'),],
            [new TestRoll(100, 70, 'Mutant Animal: organization relationship'),],
            [new TestRoll(100, 80, 'Mutant Animal: organization relationship'),],
            [new TestRoll(100, 90, 'Mutant Animal: organization relationship'),],
            [new TestRoll(100, 100, 'Mutant Animal: organization relationship'),],
        ]);
    }
}
