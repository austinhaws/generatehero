<?php

namespace Heroes\tests\utilities;

class TestRoll
{
    public $sides;
    public $roll;
    public $name;

    // don't care about rolls until getting a roll with this name; if this is set to true then don't care ever again so just roll away
    public $dontCareUntil;

    // defaults are only for if using dontcareuntil
    function __construct($sides = false, $roll = false, $name = false)
    {
        $this->sides = $sides;
        $this->roll = $roll;
        $this->name = $name;
        $this->dontCareUntil = false;
    }

    /**
     * this roll is a place holder until the test cares again
     *
     * @param $until true = forever, string = until that roll comes up
     * @return TestRoll this for chaining
     */
    public function dontCareUntil($until)
    {
        $this->dontCareUntil = $until;
        return $this;
    }

    public function validate($numberSides, $name, $index)
    {
        if ($this->sides != $numberSides) {
            throw new \Exception("test roll sides don't match ($name)! expected: '$numberSides'; got: '{$this->sides}'  =(index: $index)=");
        }
        if ($this->name != $name) {
            throw new \Exception("test roll name doesn't match! rolling: '$name'; test roll has: '{$this->name}'  =(index: $index)=");
        }

    }
}
