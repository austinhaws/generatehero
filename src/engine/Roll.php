<?php
namespace Heroes\engine;

class Roll
{
    /** @var string for testing and debugging, what is the name of this roll? */
    public $name;

    /** @var int how many sides on each dice */
    public $numberSides;

    /** @var  int how many dice */
    public $numberDice;

    /** @var int how much to times the result roll by */
    public $multiplier;

    /** @var int how much to add to the result of this roll */
    public $adder;

    /** @var bool|int what was the result of the roll? (false for the roll not yet being rolled) */
    public $result;

    function __construct($name, $numberDice, $numberSides, $multiplier = 1, $result = false, $adder = 0)
    {
        $this->name = $name;
        $this->numberSides = $numberSides;
        $this->numberDice = $numberDice;
        $this->multiplier = $multiplier;
        $this->result = $result;
        $this->adder = $adder;
    }

    /**
     * @return string debug string of what the roll looks like
     */
    function toString()
    {
        return $this->name . ': ' . $this->numberDice . 'D' . $this->numberSides . ' X ' . $this->multiplier . ' + ' . $this->adder . ' = ' . $this->result;
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
            $this->adder,
            $this->result,
        ]);
    }
}
