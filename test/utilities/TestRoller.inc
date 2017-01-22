<?php
namespace Heroes\tests\utilities;

use Heroes\engine\Roller;

class TestRoller extends Roller
{
    private $testRolls;

    /**
     * override original roller to do preentered rolls
     *
     * @param $numberDice int how many dice to roll
     * @param $numberSides int how many sides on each dice
     * @return int total of all the rolls
     */
    public function rollDice($numberDice, $numberSides)
    {
        $roll = 0;
        for ($x = 0; $x < $numberDice; $x++) {
            $roll += $this->getRoll($numberSides);
        }
        return $roll;
    }

    /**
     * get a roll from the pre-determined rolls list
     *
     * @param $numberSides int how many sides the roll should ahve
     * @return int the pre-determined roll value
     * @throws \Exception if roll doesn't match then exception throws
     */
    private function getRoll($numberSides) {
        if (!count($this->testRolls)) {
            throw new \Exception('out of rolls');
        }

        $roll = array_shift($this->testRolls);

        if ($roll['sides'] != $numberSides) {
            throw new \Exception("test roll sides don't match; expected: {$numberSides}; got: {$roll->sides}");
        }
        return $roll['roll'];
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
     *
     * @return bool true if there are no rolls left
     */
    public function verifyTestRolls() {
        return !count($this->testRolls);
    }
}