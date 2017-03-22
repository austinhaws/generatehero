<?php

namespace Heroes\tests;

use Heroes\engine\Engine;
use Heroes\HeroGenerator;
use Heroes\tests\utilities\TestArrayTools;
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
}