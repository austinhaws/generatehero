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

    function __construct($name, $numberDice, $numberSides, $multiplier = 1, $result = false)
    {
        $this->name = $name;
        $this->numberSides = $numberSides;
        $this->numberDice = $numberDice;
        $this->multiplier = $multiplier;
        $this->result = $result;
    }

    /**
     * @return string debug string of what the roll looks like
     */
    function toString()
    {
        return $this->name . ': ' . $this->numberDice . 'D' . $this->numberSides . ' X ' . $this->multiplier . ' = ' . $this->result;
    }

    /**
     * @return string comma delimited values for testing
     */
    function csv()
    {
        return implode(',', [
            $this->name,
            $this->numberDice,
            $this->numberSides,
            $this->multiplier,
            $this->result,
        ]);
    }
}
