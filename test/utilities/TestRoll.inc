<?php

namespace Heroes\tests\utilities;

class TestRoll
{
    public $sides;
    public $roll;
    public $name;
    public $multiplier;

    // don't care about rolls until getting a roll with this name; if this is set to true then don't care ever again so just roll away
    public $dontCareUntil;

    // defaults are only for if using dontcareuntil
    function __construct($sides = false, $roll = false, $name = false, $multiplier = 1)
    {
        $this->dontCareUntil = false;
        $this->andRoll($sides, $roll, $name, $multiplier);
    }

    /**
     * this roll is a place holder until the test cares again
     *
     * @param $until boolean|string true = forever, string = until that roll comes up
     * @return TestRoll this for chaining
     */
    public function dontCareUntil($until = true)
    {
        $this->dontCareUntil = $until;
        return $this;
    }

    /**
     * @param $sides int how many sides on the dice
     * @param $roll int result of the roll
     * @param $name string name of the roll
     * @return $this TestRoll the TestRoll for chaining
     */
    public function andRoll($sides, $roll, $name, $multiplier = 1)
    {
        $this->sides = $sides;
        $this->roll = $roll;
        $this->name = $name;
        $this->multiplier = $multiplier;
        return $this;
    }

    /**
     * @param $numberSides int number or sides requested
     * @param $name string name of the expected roll
     * @param $index int index of roll in the test rolls
     * @return $this TestRoll the roll being rolled for chaining
     * @throws \Exception if doesn't validate then gets exception
     */
    public function validate($numberSides, $name, $index)
    {
        if ($this->name != $name) {
            throw new \Exception("test roll name doesn't match! rolling: '$name'; test roll has: '{$this->name}'  =(index: $index)=");
        }
        if ($this->sides != $numberSides) {
            throw new \Exception("test roll sides don't match ($name)! expected: '$numberSides'; got: '{$this->sides}'  =(index: $index)=");
        }
        return $this;
    }
}
