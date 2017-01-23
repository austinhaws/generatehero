<?php

namespace Heroes\tests\utilities;

class TestRoll
{
    public $sides;
    public $roll;
    public $name;

    function __construct($sides, $roll, $name)
    {
        $this->sides = $sides;
        $this->roll = $roll;
        $this->name = $name;
    }

    public function validate($numberSides, $name) {
        if ($this->sides != $numberSides) {
            throw new \Exception("test roll sides don't match ($name)! expected: '$numberSides'; got: '{$this->sides}'");
        }
        if ($this->name != $name) {
            throw new \Exception("test roll name doesn't match! expected: '$name'; got '{$this->name}'");
        }

    }
}
