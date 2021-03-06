<?php
namespace Heroes\tests\utilities;

use Heroes\engine\Roll;
use Heroes\engine\Roller;
use RuntimeException;

class TestRoller extends Roller
{
    /** @var TestRoll[] the expected rolls and what to roll for them to complete the test */
    private $testRolls;
    /** @var int which test roll is being rolled */
    private $rollIndex;

    /** @var Roll[] what was really rolled */
    private $realRolls = [];

    /**
     * override original roller to do pre-entered rolls
     *
     * @param $roll Roll the roll to roll
     * @return int total of all the rolls
     */
    public function rollDice(Roll $roll)
    {
        // !!!! if you change this then you may need to change Roller->rollDice() too !!!! //
        $roll->result = 0;
        for ($x = 0; $x < $roll->numberDice; $x++) {
            $roll->result += $this->getRoll($roll->name, $roll->numberSides);
        }
        $roll->result *= $roll->multiplier;
        $roll->result += $roll->adder;

        return $roll->result;
    }

    /**
     * get a roll from the pre-determined rolls list
     *
     * @param $name string informational name of why this roll is being made
     * @param $numberSides int how many sides the roll should have
     * @return int the pre-determined roll value
     */
    private function getRoll($name, $numberSides) {
        if (!count($this->testRolls)) {
            throw new RuntimeException("out of rolls: ($name); sides: ${numberSides}");
        }

        $roll = array_shift($this->testRolls);

        if (!$roll) {
            throw new RuntimeException("Test Roll does not exist for: $name ($numberSides)");
        }
        // the roll was expected & found
        if ($roll->dontCareUntil === $name || $roll->dontCareUntil === true) {
            $roll->dontCareUntilReached = true;
        }
        if ($roll->dontCareUntil && $roll->dontCareUntil !== $name) {
            // not going to use it, so put it back on the front
            array_unshift($this->testRolls, $roll);
            $result = mt_rand(1, $numberSides);
        } else {
            // remember that the roll was found as expected
            $this->rollIndex++;
            if ($roll->useNextRoll) {
                $this->rollIndex++;
                $roll = array_shift($this->testRolls);
            }
            $roll->validate($numberSides, $name, $this->rollIndex);
            if ($roll->roll === false) {
                $result = parent::rollDice(new Roll($name, 1, $numberSides));
            } else {
                $result = $roll->roll;
            }
        }
        $roll->result = $result;
        $this->realRolls[] = new Roll($name, 1, $numberSides, 1, $result);
        return $result;
    }


    /**
     * preload with expected dice to roll and the result for each one. must be in order of rolling
     *
     * @param $testRolls array the rolls used for testing; 'sides' => {dice sides}, 'roll' => result
     */
    public function setTestRolls($testRolls)
    {
        $this->rollIndex = 0;
        $this->testRolls =& $testRolls;
    }

    /**
     * csv string of the rolled roll for replicating a failed test sequence exactly
     * ie "Education Level,1,100,1,1;Education Level,1,100,1,18"
     *
     * @param $rollsString string semicolon line separated csv data
     */
    public function setTestRollsString($rollsString)
    {
        $testRolls = [];
        foreach (explode(';', $rollsString) as $line) {
            $parts = explode(',', $line);
            $testRolls[] = new TestRoll($parts[2], $parts[3], $parts[0], $parts[3]);
        }
        $this->setTestRolls($testRolls);
    }

    /**
     * make sure all the rolls were used
     * @param bool $showRolls show what the rolls where; useful for seeing what was rolled
     */
    public function verifyTestRolls($showRolls = false) {
        $count = count($this->testRolls ?? []);
        if ($count && ($count != 1 || !$this->testRolls[0]->verifyLeftoverRoll())) {
            $testRoll = $this->testRolls[0];
            if ($count === 1 && $testRoll->dontCareUntil && !$testRoll->dontCareUntilReached) {
                var_dump($testRoll);
                throw new RuntimeException("'Don't care until' did not find the roll to not care about causing it to spoof all rolls unconditionally: '{$testRoll->name}'");
            } else {
                throw new RuntimeException("Only used {$this->rollIndex} rolls and there are $count unused test rolls");
            }
        }

        if ($showRolls) {
            var_dump('Rolled rolls: ' . implode(";", array_map(function (Roll $roll) {
                return $roll->csv();
            }, $this->realRolls)));
            $this->realRolls = [];
        }
    }
}
