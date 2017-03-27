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
     * @param string $startCaringAt what is the first roll that will start being iterated on
     * @param int $i current iteration of rolls
     * @return array|bool false if done with all iterations, rolls array otherwise
     */
    private function rollsIteration($methods, $startCaringAt, $i)
    {
        $rolls = [
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 100, 'power category'),
            (new TestRoll())->dontCareUntilAndGetNext($startCaringAt),
        ];

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
     * @param string $startCaringAt what is the first roll that will start being iterated on
     */
    protected function runIterations($methods, $startCaringAt)
    {
        $i = 0;
        while ($rolls = $this->rollsIteration($methods, $startCaringAt, $i++)) {
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
}
