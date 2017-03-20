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
        $result = 0;
        for ($x = 0; $x < $roll->numberDice; $x++) {
            $result += mt_rand(1, $roll->numberSides);
        }
        return $roll->result = $result * $roll->multiplier;
    }
}