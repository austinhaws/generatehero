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

    function __construct($name, $numberDice, $numberSides)
    {
        $this->name = $name;
        $this->numberSides = $numberSides;
        $this->numberDice = $numberDice;
    }
}
