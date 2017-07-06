<?php
namespace Heroes\engine;

class Roller
{
    /**
     * roll a dice roll
     *
     * @param Roll $roll the roll details
     * @return int the final result
     */
    public function rollDice(Roll $roll)
    {
        // !!!! if you change this then you may need to change TestRoller->rollDice() too !!!! //
        $roll->result = 0;
        for ($x = 0; $x < $roll->numberDice; $x++) {
            $roll->result += mt_rand(1, $roll->numberSides);
        }
        $roll->result *= $roll->multiplier;
        $roll->result += $roll->adder;
        return $roll->result;
    }
}