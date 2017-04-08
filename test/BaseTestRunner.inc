<?php

namespace Heroes\tests;

use Heroes\engine\Engine;
use Heroes\HeroGenerator;
use Heroes\tests\utilities\TestArrayTools;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

abstract class BaseTestRunner extends \PHPUnit_Framework_TestCase
{
    protected $engine;
    protected $testRoller;
    protected $testArrayTools;
    protected $heroGenerator;

    function __construct($name = NULL, array $data = array(), $dataName = '')
    {
        parent::__construct($name, $data, $dataName);


        $this->engine = new Engine();

        $this->testRoller = new TestRoller();
        $this->engine->roller = $this->testRoller;

        $this->testArrayTools = new TestArrayTools($this->engine);
        $this->engine->arrayTools = $this->testArrayTools;

        $this->heroGenerator = new HeroGenerator($this->engine);
    }

    /**
     * iterate through roll lists until they have all been gone through at least once
     *
     * @param array $methods names of methods on "this" that setup rolls for iterating
     * @param array $firstRolls rolls to get to the section being tested (ie pick ability class, skip general setup, start rolling class information)
     * @param int $i current iteration of rolls
     * @return array|bool false if done with all iterations, rolls array otherwise
     */
    private function rollsIteration($methods, $firstRolls, $i)
    {
        $rolls = $firstRolls;

        $allEnded = true;
        foreach ($methods as $method) {
            $allEnded = $this->$method($rolls, $i) && $allEnded;
        }
        $rolls[] = (new TestRoll())->dontCareAnyMore();

        // if all are "ended" then return false, otherwise return the rolls
        return $allEnded ? false : $rolls;
    }

    /**
     *
     * test through iterations of possible rolls
     *
     * @param array $methods names of methods on "this" that setup rolls for iterating
     * @param array $firstRolls setup rolls that don't change for each iteration that lead to the class
     */
    protected function runIterations($methods, $firstRolls)
    {
        $i = 0;
        while ($rolls = $this->rollsIteration($methods, $firstRolls, $i++)) {
            $this->testRoller->setTestRolls($rolls);
            $this->heroGenerator->generate();

            $this->testRoller->verifyTestRolls();
        }
    }

    /**
     * grab rolls from an iteration, reporting ended and using first rolls if at end of iteratable items
     *
     * @param array $rolls array of rolls to use for this iteration of testing
     * @param int $i which iteration to use
     * @param array $subRolls array of array of test rolls; each sub array is a group of rolls for an interation
     * @return bool ended flag
     */
    protected function iterationSubRolls(&$rolls, $i, $subRolls)
    {
        $ended = false;
        if ($i >= count($subRolls)) {
            $ended = true;
            $i = 0;
        }
        $subRoll = $subRolls[$i];
        array_push($rolls, ...$subRoll);
        return $ended;
    }

    /**
     * runIterations is if there are only pre-rolls; but if you custom rolls mixed throughout sequence around the iterations
     * then this is the function for you!
     *
     * @param $methods array of string names of the methods to run on "this" (must all be public)
     * @param $rolls array rolls array to which to add the results of the iterations
     * @param $i int current iteration #
     * @return bool true if all the iterations report as ended
     */
    protected function runIterationGroup($methods, &$rolls, $i)
    {
        $endeds = [];
        foreach ($methods as $method) {
            $endeds[] = $this->$method($rolls, $i);
        }
        // if any are not ended then report not ended
        return array_reduce($endeds, function ($result, $ended) {
            return $result && $ended;
        }, true);
    }
}
