<?php
namespace Heroes\tests\utilities;

use Heroes\engine\Roll;
use Heroes\engine\Roller;

class TestRoller extends Roller
{
    private $testRolls;
    private $rollIndex;

    /**
     * override original roller to do preentered rolls
     *
     * @param $roll Roll the roll to roll
     * @return int total of all the rolls
     */
    public function rollDice(Roll $roll)
    {
        $result = 0;
        for ($x = 0; $x < $roll->numberDice; $x++) {
            $result += $this->getRoll($roll->name, $roll->numberSides);
        }
        return $result;
    }

    /**
     * get a roll from the pre-determined rolls list
     *
     * @param $name string informational name of why this roll is being made
     * @param $numberSides int how many sides the roll should have
     * @return int the pre-determined roll value
     * @throws \Exception if roll doesn't match then exception throws
     */
    private function getRoll($name, $numberSides) {
        if (!count($this->testRolls)) {
            throw new \Exception("out of rolls for ($name): ${numberSides}");
        }

        $roll = array_shift($this->testRolls);

        if (!$roll) {
            throw new \Exception("Test Roll does not exist for: $name ($numberSides)");
        }
        if ($roll->dontCareUntil && $roll->dontCareUntil !== $name) {
            // not going to use it, so put it back on the front
            array_unshift($this->testRolls, $roll);
            $result = mt_rand(1, $numberSides);
        } else {
            $this->rollIndex++;
            $roll->validate($numberSides, $name, $this->rollIndex);
            $result = $roll->roll;
        }
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
     * make sure all the rolls were used
     * @return bool true if there are no rolls left
     * @throws \Exception if there are rolls not yet used then throws exception
     */
    public function verifyTestRolls() {
        $count = count($this->testRolls);
        if ($count && ($count != 1 || !$this->testRolls[0]->dontCareUntil)) {
            throw new \Exception("Only used {$this->rollIndex} rolls and there are unused test rolls");
        }
    }
}