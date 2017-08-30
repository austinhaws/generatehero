<?php

namespace Heroes\tests\utilities;

class TestRoll
{
    public $sides;
    public $roll;
    public $name;
    public $multiplier;

    // if not caring and then find the not cared for roll then get the next roll to test for the found roll
    public $useNextRoll = false;

    // don't care about rolls until getting a roll with this name; if this is set to true then don't care ever again so just roll away
    public $dontCareUntil;
    // if not caring, make sure it does get to that roll
    public $dontCareUntilReached;

    function __construct($sides = false, $roll = false, $name = false, $multiplier = 1, $dontCareAnymore = false)
    {
        $this->dontCareUntil = $dontCareAnymore;
        $this->dontCareUntilReached = false;
        $this->andRoll($sides, $roll, $name, $multiplier);
    }

    /**
     * better named function for not caring ever again
     *
     * @return TestRoll for chaining
     */
    public function dontCareAnyMore()
    {
        return $this->dontCareUntil(true);
    }

    /**
     * static version for cleaner usage
     *
     * @return TestRoll
     */
    public static function doNotCareAnyMore() {
        return (new TestRoll())->dontCareAnyMore();
    }

    /**
     * this roll is a place holder until the test cares again
     *
     * @param $until boolean|string true = forever, string = until that roll comes up
     * @return TestRoll this for chaining
     */
    public function dontCareUntil($until)
    {
        $this->dontCareUntil = $until;
        return $this;
    }


    /**
     * ease of use static function for not caring until a roll comes
     *
     * @param $sides int dice's sides
     * @param $roll int roll for the dice
     * @param $name string name of the roll
     * @return TestRoll
     */
    public static function doNotCareUntilAndRoll($sides, $roll, $name) {
        return (new TestRoll())->dontCareUntil($name)->andRoll($sides, $roll, $name);
    }


    /**
     * skip rolls until a certain roll and then use the next roll for that roll.
     * dontCareUntil() will skip until it finds a matching roll and ignore it and then start checking rolls where as this will check the target roll
     *
     * @param $until string the roll name
     * @return $this
     */
    public function dontCareUntilAndGetNext($until)
    {
        $this->dontCareUntil = $until;
        $this->useNextRoll = true;
        return $this;
    }

    /**
     * @param $sides int how many sides on the dice
     * @param $roll int result of the roll
     * @param $name string name of the roll
     * @param int $multiplier how much to multiply the roll result value
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
            throw new \Exception("test roll name doesn't match! rolling: '$name'; test roll has: '{$this->name}'  =(index: $index)=; sides={$numberSides}");
        }
        if (false !== $this->sides && $this->sides != $numberSides) {
            throw new \Exception("test roll sides don't match ($name)! expected: '$numberSides'; got: '{$this->sides}'  =(index: $index)=");
        }
        return $this;
    }

    /**
     * if a roll is left over and not rolled then it has to be a "dont care until" type of roll AND it's dontcareuntil roll has to have been found
     * if it's not a dontcareuntil then it's bad that it wasn't rolled
     *
     * @return bool
     */
    public function verifyLeftoverRoll() {
       return $this->dontCareUntil && $this->dontCareUntilReached;
    }
}
