<?php
namespace Heroes\engine;

class Roller
{
    /**
     * roll a dice
     *
     * @param $name string name of the roll for testing purposes and informational
     * @param $numberDice int number of dice to roll
     * @param $numberSides int maximum number on the dice
     * @return int result of the roll
     */
    public function rollDice($name, $numberDice, $numberSides)
    {
        $roll = 0;
        for ($x = 0; $x < $numberDice; $x++) {
            $roll += mt_rand(1, $numberSides);
        }
        return $roll;
    }
}