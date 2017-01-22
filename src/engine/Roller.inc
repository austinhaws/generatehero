<?php
namespace Heroes\engine;

class Roller
{
    public function rollDice($numberDice, $numberSides)
    {
        $roll = 0;
        for ($x = 0; $x < $numberDice; $x++) {
            $roll += mt_rand(1, $numberSides);
        }
        return $roll;
    }
}