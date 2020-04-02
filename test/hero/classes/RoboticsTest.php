<?php

namespace Heroes\test\hero\classes;

use Heroes\engine\Roll;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class RoboticsTest extends BaseTestRunner
{
    public function test_robotType() {
        $ended = false;
        $i = 0;
        while (!$ended && ++$i) {

            $rolls = [(new TestRoll())->dontCareUntil('power category')->andRoll(100, 20, 'power category')];
            $ended = $this->iterationSubRolls($rolls, $i, [
                [new TestRoll(5, 1, 'Robot Type'),],
                [new TestRoll(5, 2, 'Robot Type'),],
                [new TestRoll(5, 3, 'Robot Type'),],
                [new TestRoll(5, 4, 'Robot Type'),],
                [new TestRoll(5, 5, 'Robot Type'),],
            ]);
            $rolls[] = (new TestRoll())->dontCareUntil('Education Level')->dontCareAnyMore();


            $this->testRoller->setTestRolls($rolls);

            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();

            $this->assertTrue(strpos(get_class($hero->class), 'Robotics') !== false);
        }
    }

    public function test_budgetType() {
        $ended = false;
        $i = 0;
        while (!$ended && ++$i) {
            $this->testArrayTools->rotation = $i + 1;

            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 20, 'power category'),
                (new TestRoll())->dontCareUntilAndGetNext('Robotics - budget'),
                ];
            $ended = $this->iterationSubRolls($rolls, $i, [
                [new TestRoll(100, 15, 'Robotics - budget'),],
                [new TestRoll(100, 30, 'Robotics - budget'),],
                [new TestRoll(100, 44, 'Robotics - budget'),],
                [new TestRoll(100, 59, 'Robotics - budget'),],
                [new TestRoll(100, 74, 'Robotics - budget'),],
                [new TestRoll(100, 89, 'Robotics - budget'),],
                [new TestRoll(100, 100, 'Robotics - budget'),],
            ]);

            $rolls[] = (new TestRoll())->dontCareUntil('Education Level')->dontCareAnyMore();


            $this->testRoller->setTestRolls($rolls);

            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();

            $this->assertTrue(strpos(get_class($hero->class), 'Robotics') !== false);
        }
    }

    /**
     * with so many possible combinations, just run a bunch of runs to see if anything breaks... ya, bad planning
     */
    public function test_lotsRotations() {
        foreach (range(1, 250) as $loop) {
            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 20, 'power category'),
                (new TestRoll())->dontCareAnyMore(),
            ];

            $this->testArrayTools->rotation = $loop;

            $this->testRoller->setTestRolls($rolls);
            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();
            $this->assertTrue(strpos(get_class($hero->class), 'Robotics') !== false);
        }
    }

    public function test_legs() {
        // make an animal body type
        // get max # of legs
        // find bonus that has "Number has $numberLegs leg"

        // sports car
        $this->testArrayTools->rotation = 1;
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 20, 'power category'),
            new TestRoll(5, 2, 'Robot Type'),
            (new TestRoll())->dontCareUntil('Robotics - budget')->andRoll(100, 100, 'Robotics - budget'),
            (new TestRoll())->dontCareUntil('Robotics - Legs: extras')->andRoll(100, 1, 'Robotics - Legs: extras'),
            (new TestRoll())->dontCareUntil('Robotics - Legs: extras')->andRoll(100, 1, 'Robotics - Legs: extras'),
            (new TestRoll())->dontCareUntil('Robotics - Legs: extras')->andRoll(100, 1, 'Robotics - Legs: extras'),
            (new TestRoll())->dontCareUntil('Education Level')->dontCareAnyMore(),
        ]);


        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();

        $this->assertTrue(strpos(get_class($hero->class), 'Robotics') !== false);
        $this->assertEquals(4, $hero->robotNumberLegs);
    }

    public function test_vehicleLocomotion() {
        // sports car
        $this->testArrayTools->rotation = 3;
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 20, 'power category'),
            new TestRoll(5, 2, 'Robot Type'),
            (new TestRoll())->dontCareUntil('Robotics - budget')->andRoll(100, 100, 'Robotics - budget'),
            (new TestRoll())->dontCareUntil('Education Level')->dontCareAnyMore(),
        ]);


        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();

        $this->assertTrue(strpos(get_class($hero->class), 'Robotics') !== false);
        $this->assertEquals('Jet Engine', $hero->robotEngine);
    }

    public function test_armsZero() {
        // animal
        $this->testArrayTools->rotation = 20;
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 20, 'power category'),
            new TestRoll(5, 2, 'Robot Type'),
            // max budget
            (new TestRoll())->dontCareUntil('Robotics - budget')->andRoll(100, 100, 'Robotics - budget'),
            // -- would've got an arms roll here if arms were rolled, so working without arms -- //
            new TestRoll(10, 10, 'Robot AI: Education'),
            TestRoll::doNotCareAnyMore(),
        ]);

        $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();
    }

    public function test_armsMulti1() {
        // large humanoid
        $this->testArrayTools->rotation = 2;
        $this->testRoller->setTestRolls([
            TestRoll::doNotCareUntilAndRoll(100, 20, 'power category'),
            new TestRoll(5, 2, 'Robot Type'),
            // max budget
            TestRoll::doNotCareUntilAndRoll(100, 100, 'Robotics - budget'),
            TestRoll::doNotCareUntilAndRoll(100, 1, 'Robotics - Arms: extras'),

            new TestRoll(100, 1, 'Robot arm - detachable remote'),

            new TestRoll(100, 100, 'Robot arm - detachable remote'),
            new TestRoll(100, 10, 'Robot arm - interchangeable'),
            new TestRoll(100, 1, 'Robot interchangeable arm: Electromagnetic Clamp'),
            new TestRoll(100, 1, 'Robot interchangeable arm: Buzz-Saw'),
            new TestRoll(100, 1, 'Robot interchangeable arm: High-Powered Drill'),
            new TestRoll(100, 1, 'Robot interchangeable arm: Police Style Lock Release Gun'),
            new TestRoll(100, 1, 'Robot interchangeable arm: Towline'),
            new TestRoll(100, 1, 'Robot interchangeable arm: Acetylene Torch'),
            new TestRoll(100, 1, 'Robot interchangeable arm: Weapon'),

            new TestRoll(false, false, 'Robotics: Sponsoring organization'),
            TestRoll::doNotCareAnyMore()
        ]);

        $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();
    }

    public function test_armsMulti2() {
        // large humanoid
        $this->testArrayTools->rotation = 2;
        $this->testRoller->setTestRolls([
            TestRoll::doNotCareUntilAndRoll(100, 20, 'power category'),
            new TestRoll(5, 2, 'Robot Type'),
            // max budget
            TestRoll::doNotCareUntilAndRoll(100, 100, 'Robotics - budget'),
            TestRoll::doNotCareUntilAndRoll(100, 1, 'Robotics - Arms: extras'),

            new TestRoll(100, 100, 'Robot arm - detachable remote'),
            new TestRoll(100, 100, 'Robot arm - interchangeable'),
            new TestRoll(100, 1, 'Robot Utility Arm'),
            new TestRoll(100, 1, 'Robot Utility Arm - concealed'),

            new TestRoll(100, 100, 'Robot arm - detachable remote'),
            new TestRoll(100, 100, 'Robot arm - interchangeable'),
            new TestRoll(100, 1, 'Robot Utility Arm'),
            new TestRoll(100, 51, 'Robot Utility Arm - concealed'),

            new TestRoll(false, false, 'Robotics: Sponsoring organization'),
            TestRoll::doNotCareAnyMore()
        ]);

        $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();
    }

    public function test_armsMulti3() {
        // large humanoid
        $this->testArrayTools->rotation = 2;
        $this->testRoller->setTestRolls([
            TestRoll::doNotCareUntilAndRoll(100, 20, 'power category'),
            new TestRoll(5, 2, 'Robot Type'),
            // max budget
            TestRoll::doNotCareUntilAndRoll(100, 100, 'Robotics - budget'),
            TestRoll::doNotCareUntilAndRoll(100, 1, 'Robotics - Arms: extras'),

            new TestRoll(100, 100, 'Robot arm - detachable remote'),
            new TestRoll(100, 100, 'Robot arm - interchangeable'),
            new TestRoll(100, 100, 'Robot Utility Arm'),
            new TestRoll(100, 1, 'Robot Tentacle Arm'),

            new TestRoll(100, 100, 'Robot arm - detachable remote'),
            new TestRoll(100, 100, 'Robot arm - interchangeable'),
            new TestRoll(100, 100, 'Robot Utility Arm'),
            new TestRoll(100, 100, 'Robot Tentacle Arm'),

            new TestRoll(false, false, 'Robotics: Sponsoring organization'),
            TestRoll::doNotCareAnyMore()
        ]);

        $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();
    }

    public function test_buyNovelties() {
        for ($i = 0; $i < 10; $i++) {
            $this->testRoller->setTestRolls([TestRoll::doNotCareAnyMore()]);
            $this->testArrayTools->rotation = $this->engine->roller->rollDice(new Roll('random rotation', 1, 100));

            $this->testRoller->setTestRolls([
                TestRoll::doNotCareUntilAndRoll(100, 20, 'power category'),
                new TestRoll(5, 2, 'Robot Type'),
                // max budget
                TestRoll::doNotCareUntilAndRoll(100, 100, 'Robotics - budget'),
                TestRoll::doNotCareAnyMore()
            ]);

            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();

            // make sure here got some robotics option added
			$this->assertTrue(count($hero->robotOptions) > 0);
        }
    }
}
