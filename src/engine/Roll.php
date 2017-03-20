<?php
namespace Heroes\engine;

class Roll
{
    // for testing and debugging, what is the name of this roll?
    public $name;

    // how many sides on each dice
    public $numberSides;

    // how many dice
    public $numberDice;

    // how much to times the result roll by
    public $multiplier;

    // what was the result of the roll?
    public $result;

    function __construct($name, $numberDice, $numberSides, $multiplier = 1)
    {
        $this->name = $name;
        $this->numberSides = $numberSides;
        $this->numberDice = $numberDice;
        $this->multiplier = $multiplier;
    }
}
