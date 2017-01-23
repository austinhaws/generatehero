<?php
namespace Heroes\tests\utilities;

use Heroes\engine\Roller;

class TestRoller extends Roller
{
    private $testRolls;

    /**
     * override original roller to do preentered rolls
     *
     * @param $name string name for debugging/informational
     * @param $numberDice int how many dice to roll
     * @param $numberSides int how many sides on each dice
     * @return int total of all the rolls
     */
    public function rollDice($name, $numberDice, $numberSides)
    {
        $roll = 0;
        for ($x = 0; $x < $numberDice; $x++) {
            $roll += $this->getRoll($name, $numberSides);
        }
        return $roll;
    }

    /**
     * get a roll from the pre-determined rolls list
     *
     * @param $name string informational name of why this roll is being made
     * @param $numberSides int how many sides the roll should ahve
     * @return int the pre-determined roll value
     * @throws \Exception if roll doesn't match then exception throws
     */
    private function getRoll($name, $numberSides) {
        if (!count($this->testRolls)) {
            throw new \Exception("out of rolls for ($name): ${numberSides}");
        }

        $roll = array_shift($this->testRolls);

        $roll->validate($numberSides, $name);

        return $roll->roll;
    }


    /**
     * preload with expected dice to roll and the result for each one. must be in order of rolling
     *
     * @param $testRolls array the rolls used for testing; 'sides' => {dice sides}, 'roll' => result
     */
    public function setTestRolls($testRolls)
    {
        $this->testRolls =& $testRolls;
    }

    /**
     * make sure all the rolls were used
     * @return bool true if there are no rolls left
     * @throws \Exception if there are rolls not yet used then throws exception
     */
    public function verifyTestRolls() {
        if (count($this->testRolls)) {
            throw new \Exception('there are unused test rolls');
        }
    }
}