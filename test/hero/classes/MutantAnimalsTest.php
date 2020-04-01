<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class MutantAnimalsTest extends BaseTestRunner
{

    public function test_mutantAnimal()
    {
        // this is a random test, but with so many options there's not much else to do
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $this->testArrayTools->rotation = $i + 1;
            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 50, 'power category'),
                new TestRoll(2, 2, 'Mutant Type'),
            ];

            $ended = $this->runIterationGroup([
                'mutantAnimalType',
            ], $rolls, $i);

            $rolls[] = (new TestRoll())->dontCareAnyMore();

            $this->testRoller->setTestRolls($rolls);

            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();

            $this->assertTrue(strpos(get_class($hero->class), 'Mutants') !== false);
			$this->assertNotEquals($hero->class->animal, false);
            // should have gotten some mutant animal bonuses
        }

    }

    public function test_mutantAnimal_single()
    {
        $rolls = [
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 50, 'power category'),
            new TestRoll(2, 2, 'Mutant Type'),
            (new TestRoll())->dontCareUntil('Mutant animal type')->andRoll(300, 50, 'Mutant animal type'),

            new TestRoll(3, 1, 'Mutant Animal Feature'),
            new TestRoll(2, 1, 'Mutant Animal Feature'),
            new TestRoll(3, 1, 'Mutant Animal Feature'),
            new TestRoll(3, 1, 'Mutant Animal Feature'),
            new TestRoll(2, 1, 'Mutant Animal Feature'),
            new TestRoll(2, 1, 'Mutant Animal Feature'),
            new TestRoll(2, 1, 'Mutant Animal - Pick Power'),
            new TestRoll(2, 2, 'Mutant Animal - Pick Power'),
            new TestRoll(81, 81, 'Mutant Animal Number Psionics'),
            new TestRoll(false, false, 'Alignment', 1, true),
        ];

        $this->testRoller->setTestRolls($rolls);

        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();

        $this->assertTrue(strpos(get_class($hero->class), 'Mutants') !== false);

        // should have gotten some mutant animal bonuses
    }

    protected function mutantAnimalType(&$rolls, $i)
    {
        $rolls[] = (new TestRoll())->dontCareUntilAndGetNext('Mutant animal type');
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(300, 25, 'Mutant animal type'),],
            [new TestRoll(300, 31, 'Mutant animal type'),],
            [new TestRoll(300, 37, 'Mutant animal type'),],
            [new TestRoll(300, 43, 'Mutant animal type'),],
            [new TestRoll(300, 50, 'Mutant animal type'),],
            [new TestRoll(300, 62, 'Mutant animal type'),],
            [new TestRoll(300, 75, 'Mutant animal type'),],
            [new TestRoll(300, 100, 'Mutant animal type'),],
            [new TestRoll(300, 125, 'Mutant animal type'),],
            [new TestRoll(300, 150, 'Mutant animal type'),],
            [new TestRoll(300, 151, 'Mutant animal type'),],
            [new TestRoll(300, 152, 'Mutant animal type'),],
            [new TestRoll(300, 153, 'Mutant animal type'),],
            [new TestRoll(300, 154, 'Mutant animal type'),],
            [new TestRoll(300, 155, 'Mutant animal type'),],
            [new TestRoll(300, 156, 'Mutant animal type'),],
            [new TestRoll(300, 157, 'Mutant animal type'),],
            [new TestRoll(300, 158, 'Mutant animal type'),],
            [new TestRoll(300, 159, 'Mutant animal type'),],
            [new TestRoll(300, 160, 'Mutant animal type'),],
            [new TestRoll(300, 161, 'Mutant animal type'),],
            [new TestRoll(300, 162, 'Mutant animal type'),],
            [new TestRoll(300, 163, 'Mutant animal type'),],
            [new TestRoll(300, 164, 'Mutant animal type'),],
            [new TestRoll(300, 165, 'Mutant animal type'),],
            [new TestRoll(300, 166, 'Mutant animal type'),],
            [new TestRoll(300, 167, 'Mutant animal type'),],
            [new TestRoll(300, 168, 'Mutant animal type'),],
            [new TestRoll(300, 169, 'Mutant animal type'),],
            [new TestRoll(300, 170, 'Mutant animal type'),],
            [new TestRoll(300, 171, 'Mutant animal type'),],
            [new TestRoll(300, 175, 'Mutant animal type'),],
            [new TestRoll(300, 200, 'Mutant animal type'),],
            [new TestRoll(300, 225, 'Mutant animal type'),],
            [new TestRoll(300, 230, 'Mutant animal type'),],
            [new TestRoll(300, 235, 'Mutant animal type'),],
            [new TestRoll(300, 240, 'Mutant animal type'),],
            [new TestRoll(300, 245, 'Mutant animal type'),],
            [new TestRoll(300, 250, 'Mutant animal type'),],
            [new TestRoll(300, 275, 'Mutant animal type'),],
            [new TestRoll(300, 281, 'Mutant animal type'),],
            [new TestRoll(300, 287, 'Mutant animal type'),],
            [new TestRoll(300, 293, 'Mutant animal type'),],
            [new TestRoll(300, 300, 'Mutant animal type'),],
        ]);
    }

    public function test_mutantAnimal0Psionics() {
        $rolls = [
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 50, 'power category'),
            new TestRoll(2, 2, 'Mutant Type'),
            (new TestRoll())->dontCareUntil('Mutant animal type')->andRoll(300, 50, 'Mutant animal type'),

            new TestRoll(3, 1, 'Mutant Animal Feature'),
            new TestRoll(2, 1, 'Mutant Animal Feature'),
            new TestRoll(3, 1, 'Mutant Animal Feature'),
            new TestRoll(3, 1, 'Mutant Animal Feature'),
            new TestRoll(2, 1, 'Mutant Animal Feature'),
            new TestRoll(2, 1, 'Mutant Animal Feature'),
            new TestRoll(2, 1, 'Mutant Animal - Pick Power'),
            new TestRoll(2, 2, 'Mutant Animal - Pick Power'),
            new TestRoll(81, 0, 'Mutant Animal Number Psionics'),
            new TestRoll(false, false, 'Alignment', 1, true),
        ];

        $this->testRoller->setTestRolls($rolls);

        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();

        $this->assertTrue(strpos(get_class($hero->class), 'Mutants') !== false);
		$this->assertNotEquals($hero->class->animal, false);

		// test: gained powers are added to abilities list
		$this->assertEquals(count($hero->abilities), 1);
	}

    public function test_mutantAnimalSmall() {
        $rolls = [
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 50, 'power category'),
            new TestRoll(2, 2, 'Mutant Type'),

            // wild bird
            (new TestRoll())->dontCareUntil('Mutant animal type')->andRoll(300, 75, 'Mutant animal type'),
            new TestRoll(4, 4, 'Mutant Animal Feature'),
            new TestRoll(1, 1, 'Mutant Animal Feature'),
            new TestRoll(3, 3, 'Mutant Animal Feature'),
            new TestRoll(3, 3, 'Mutant Animal Feature'),
            new TestRoll(2, 2, 'Mutant Animal Feature'),
            new TestRoll(81, 81, 'Mutant Animal Number Psionics'),

            (new TestRoll())->dontCareUntil('Mutant animal type')->andRoll(300, 75, 'Mutant animal type'),
            new TestRoll(4, 4, 'Mutant Animal Feature'),
            new TestRoll(1, 1, 'Mutant Animal Feature'),
            new TestRoll(3, 3, 'Mutant Animal Feature'),
            new TestRoll(3, 3, 'Mutant Animal Feature'),
            new TestRoll(2, 2, 'Mutant Animal Feature'),
            new TestRoll(81, 0, 'Mutant Animal Number Psionics'),

            new TestRoll(false, false, 'Alignment'),
            new TestRoll(false, false, false, 1, true),
        ];

        $this->testRoller->setTestRolls($rolls);

        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();

        $this->assertTrue(strpos(get_class($hero->class), 'Mutants') !== false);
    }

    public function test_mutantAnimalOrgRelation() {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $this->testArrayTools->rotation = $i + 1;

            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 50, 'power category'),
                new TestRoll(2, 2, 'Mutant Type'),
            ];


            $ended = $this->runIterationGroup([
                'mutantAnimalCause',
            ], $rolls, $i);

            $rolls = array_merge($rolls, [
                (new TestRoll())->dontCareUntil('Mutant animal type')->andRoll(false, false, 'Mutant animal type'),
                new TestRoll(false, false, false, 1, true),
            ]);

            $this->testRoller->setTestRolls($rolls);

            $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();
        }
    }

    public function test_mutantAnimalOrgRelationship() {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $this->testArrayTools->rotation = $i + 1;

            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 50, 'power category'),
                new TestRoll(2, 2, 'Mutant Type'),
                new TestRoll(100, 100, 'Mutant Animal: Cause'),

            ];


            $ended = $this->runIterationGroup([
                'mutantAnimalOrgRelationship',
            ], $rolls, $i);

            $rolls = array_merge($rolls, [
                (new TestRoll())->dontCareUntil('Mutant animal type')->andRoll(false, false, 'Mutant animal type'),
                new TestRoll(false, false, false, 1, true),
            ]);

            $this->testRoller->setTestRolls($rolls);

            $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();
        }
    }

    public function test_mutantAnimalWildEducation() {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $this->testArrayTools->rotation = $i + 1;

            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 50, 'power category'),
                new TestRoll(2, 2, 'Mutant Type'),
                new TestRoll(100, 1, 'Mutant Animal: Cause'),

            ];


            $ended = $this->runIterationGroup([
                'mutantAnimalWildEducation',
            ], $rolls, $i);

            $rolls = array_merge($rolls, [
                (new TestRoll())->dontCareUntil('Mutant animal type')->andRoll(false, false, 'Mutant animal type'),
                new TestRoll(false, false, false, 1, true),
            ]);

            $this->testRoller->setTestRolls($rolls);

            $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();
        }
    }

    public function test_mutantAnimalAnimalOrganization() {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $this->testArrayTools->rotation = $i + 1;

            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 50, 'power category'),
                new TestRoll(2, 2, 'Mutant Type'),
            ];

            $ended = $this->runIterationGroup([
                'mutantAnimalOrganization',
            ], $rolls, $i);

            $rolls = array_merge($rolls, [
                (new TestRoll())->dontCareUntil('Mutant animal type')->andRoll(false, false, 'Mutant animal type'),
                new TestRoll(false, false, false, 1, true),
            ]);

            $this->testRoller->setTestRolls($rolls);

            $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();
        }
    }

    protected function mutantAnimalOrgRelationship(&$rolls, $i)
    {
        $rollName = 'Mutant Animal: organization relationship';
        $rolls[] = (new TestRoll())->dontCareUntilAndGetNext($rollName);
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 10, $rollName),],
            [new TestRoll(100, 20, $rollName),],
            [new TestRoll(100, 30, $rollName),],
            [new TestRoll(100, 40, $rollName),],
            [new TestRoll(100, 50, $rollName),],
            [new TestRoll(100, 60, $rollName),],
            [new TestRoll(100, 70, $rollName),],
            [new TestRoll(100, 80, $rollName),],
            [new TestRoll(100, 90, $rollName),],
            [new TestRoll(100, 100, $rollName),],
        ]);
    }

    protected function mutantAnimalCause(&$rolls, $i)
    {
        $rolls[] = (new TestRoll())->dontCareUntilAndGetNext('Mutant Animal: Cause');
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 14, 'Mutant Animal: Cause'),],
            [new TestRoll(100, 60, 'Mutant Animal: Cause'),],
            [new TestRoll(100, 100, 'Mutant Animal: Cause'),],
        ]);
    }

    protected function mutantAnimalWildEducation(&$rolls, $i)
    {
        $rolls[] = (new TestRoll())->dontCareUntilAndGetNext('Mutant Animal: Wild Education');
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 20, 'Mutant Animal: Wild Education'),],
            [new TestRoll(100, 40, 'Mutant Animal: Wild Education'),],
            [new TestRoll(100, 90, 'Mutant Animal: Wild Education'),],
            [new TestRoll(100, 100, 'Mutant Animal: Wild Education'),],
        ]);
    }
    protected function mutantAnimalOrganization(&$rolls, $i)
    {
        $rollName = 'Mutant Animal: Organization';
        $rolls[] = (new TestRoll())->dontCareUntilAndGetNext($rollName);
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 25, $rollName),],
            [new TestRoll(100, 45, $rollName),],
            [new TestRoll(100, 50, $rollName),],
            [new TestRoll(100, 55, $rollName),],
            [new TestRoll(100, 60, $rollName),],
            [new TestRoll(100, 65, $rollName),],
            [new TestRoll(100, 70, $rollName),],
            [new TestRoll(100, 75, $rollName),],
            [new TestRoll(100, 100, $rollName),],
        ]);
    }

}
