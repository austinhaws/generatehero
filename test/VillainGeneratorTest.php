<?php

namespace Heroes\test\utilities;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;
use Heroes\VillainGenerator;
use RuntimeException;

class VillainGeneratorTest extends BaseTestRunner
{
    public function test_easyRolls()
    {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $rolls = [
            ];

            $ended = $this->runIterationGroup([
                'iterationGender',
                'iterationLevel',
                'iterationAlignment',
                'iterationCriminalRecord',
            ], $rolls, $i);

            $rolls[] = TestRoll::doNotCareAnyMore(true);

            $this->testRoller->setTestRolls($rolls);

            $generator = new VillainGenerator($this->engine);
            $generator->generate();
            $this->testRoller->verifyTestRolls();
        }
    }

    public function iterationGender(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(2, 1, 'gender'),],
            [new TestRoll(2, 2, 'gender'),],
        ]);
    }

    public function iterationLevel(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 25, 'level'),],
            [new TestRoll(100, 50, 'level'),],
            [new TestRoll(100, 75, 'level'),],
            [new TestRoll(100, 100, 'level'),],
        ]);
    }

    public function iterationAlignment(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 20, 'alignment'),],
            [new TestRoll(100, 50, 'alignment'),],
            [new TestRoll(100, 82, 'alignment'),],
            [new TestRoll(100, 100, 'alignment'),],
        ]);
    }

    public function iterationCriminalRecord(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [TestRoll::doNotCareUntilAndRoll(100, 30, 'criminalRecord'),],
            [TestRoll::doNotCareUntilAndRoll(100, 40, 'criminalRecord'),],
            [TestRoll::doNotCareUntilAndRoll(100, 49, 'criminalRecord'),],
            [TestRoll::doNotCareUntilAndRoll(100, 69, 'criminalRecord'),],
            [TestRoll::doNotCareUntilAndRoll(100, 84, 'criminalRecord'),],
            [TestRoll::doNotCareUntilAndRoll(100, 100, 'criminalRecord'),],
        ]);
    }

    public function testThug()
    {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $rolls = [
                TestRoll::doNotCareUntilAndRoll(100, 50, 'Villain Type'),
            ];

            $ended = $this->runIterationGroup([
                'iterationThug',
            ], $rolls, $i);

            $rolls[] = new TestRoll(100, 100, 'Villain Super Powers');
            $rolls[] = TestRoll::doNotCareAnyMore();

            $this->testRoller->setTestRolls($rolls);

            $generator = new VillainGenerator($this->engine);
            $generator->generate();
            $this->testRoller->verifyTestRolls();
        }
    }

    public function iterationThug(&$rolls, $i)
    {
        switch ($i % 6) {
            case 0:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 25, 'Thug Type');
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 50, 'Thug - thief: WP');
                break;
            case 1:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 25, 'Thug Type');
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 100, 'Thug - thief: WP');
                break;
            case 2:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 50, 'Thug Type');
                $rolls[] = new TestRoll(100, 50, 'Thug - Muscle: Hand to Hand');
                $rolls[] = new TestRoll(100, 50, 'Thug - Muscle: Skill');
                break;
            case 3:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 50, 'Thug Type');
                $rolls[] = new TestRoll(100, 100, 'Thug - Muscle: Hand to Hand');
                $rolls[] = new TestRoll(100, 100, 'Thug - Muscle: Skill');
                break;
            case 4:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 75, 'Thug Type');
                break;
            case 5:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 100, 'Thug Type');
                break;
            default:
                throw new RuntimeException('Unknown thug iteration ' . $i);
        }

        return $i > 6;
    }

    public function testCriminalElite()
    {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $rolls = [
                TestRoll::doNotCareUntilAndRoll(100, 100, 'Villain Type'),
            ];

            $ended = $this->runIterationGroup([
                'iterationCriminalElite',
            ], $rolls, $i);

            $rolls[] = new TestRoll(100, 100, 'Villain Super Powers');
            $rolls[] = TestRoll::doNotCareAnyMore();

            $this->testRoller->setTestRolls($rolls);

            $generator = new VillainGenerator($this->engine);
            $generator->generate();
            $this->testRoller->verifyTestRolls();
        }
    }

    public function iterationCriminalElite(&$rolls, $i)
    {
        switch ($i % 6) {
            case 0:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 25, 'Criminal Elite Type');
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 50, 'Criminal Elite - Boss: Hand to Hand');
                break;
            case 1:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 25, 'Criminal Elite Type');
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 100, 'Criminal Elite - Boss: Hand to Hand');
                break;
            case 2:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 50, 'Criminal Elite Type');
                $rolls[] = new TestRoll(100, 50, 'Criminal Elite - Military Mercenary: Hand to Hand');
                break;
            case 3:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 50, 'Criminal Elite Type');
                $rolls[] = new TestRoll(100, 100, 'Criminal Elite - Military Mercenary: Hand to Hand');
                break;
            case 4:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 75, 'Criminal Elite Type');
                break;
            case 5:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 100, 'Criminal Elite Type');
                break;
            default:
                throw new RuntimeException('Unknown criminal elite iteration ' . $i);
        }

        return $i > 6;
    }

    public function testCriminalOrganization()
    {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $rolls = [];

            $ended = $this->runIterationGroup([
                'iterationCriminalOrganization',
            ], $rolls, $i);

            // could test sizes, but this will get tested since it's only got three options and it's rolling more than that many times on the table
            $rolls[] = TestRoll::doNotCareAnyMore(true);

            $this->testRoller->setTestRolls($rolls);

            $generator = new VillainGenerator($this->engine);
            $generator->generate();
            $this->testRoller->verifyTestRolls();
        }
    }

    public function iterationCriminalOrganization(&$rolls, $i)
    {
        switch ($i % 6) {
            case 0:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 17, 'Villain Criminal Organization');
                break;
            case 1:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 34, 'Villain Criminal Organization');
                break;
            case 2:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 55, 'Villain Criminal Organization');
                break;
            case 3:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 70, 'Villain Criminal Organization');
                break;
            case 4:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 84, 'Villain Criminal Organization');
                break;
            case 5:
                $rolls[] = TestRoll::doNotCareUntilAndRoll(100, 100, 'Villain Criminal Organization');
                break;
            default:
                throw new RuntimeException('Unknown criminal elite iteration ' . $i);
        }

        return $i > 6;
    }

    public function testSuperVillain()
    {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $rolls = [
                TestRoll::doNotCareUntilAndRoll(100, 1, 'Villain Super Powers'),
            ];

            $ended = $this->runIterationGroup([
                'iterationSuperPowers',
            ], $rolls, $i);

            $this->testRoller->setTestRolls($rolls);

            $generator = new VillainGenerator($this->engine);
            $generator->generate();
            $this->testRoller->verifyTestRolls();
        }
    }

    public function iterationSuperPowers(&$rolls, $i) {
        $ended = $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 10, 'power category'),],
            [new TestRoll(100, 20, 'power category'),],
            [new TestRoll(100, 30, 'power category'),],
            [new TestRoll(100, 40, 'power category'),],
            [new TestRoll(100, 42, 'power category'),],
            [new TestRoll(100, 44, 'power category'),],
            [new TestRoll(100, 46, 'power category'),],
            [new TestRoll(100, 48, 'power category'),],
            [new TestRoll(100, 50, 'power category'),],
            [new TestRoll(100, 60, 'power category'),],
            [new TestRoll(100, 70, 'power category'),],
            [new TestRoll(100, 80, 'power category'),],
            [new TestRoll(100, 90, 'power category'),],
            [new TestRoll(100, 100, 'power category'),],
        ]);

        // roll whatever you want at this point
        $rolls[] = TestRoll::doNotCareAnyMore();

        return $ended;
    }
}
