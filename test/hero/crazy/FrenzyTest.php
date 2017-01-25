<?php

namespace Heroes\test\hero\crazy;

use Heroes\hero\crazy\Frenzy;
use Heroes\HeroGenerator;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class FrenzyTest extends \PHPUnit_Framework_TestCase
{
    private $heroGenerator;
    private $testRoller;

    function __construct($name = NULL, array $data = array(), $dataName = '')
    {
        parent::__construct($name, $data, $dataName);

        $this->heroGenerator = new HeroGenerator();
        $this->testRoller = new TestRoller();
        $this->heroGenerator->engine->roller = $this->testRoller;
    }

    public function testFrenzy()
    {
        $frenzy = new Frenzy($this->heroGenerator->engine);

        $this->testRoller->setTestRolls([
            new TestRoll(100, 10, 'Frenzy: condition'),
        ]);
        $frenzy->create();
        $this->testRoller->verifyTestRolls();

        $this->assertEquals('Intense Frustration', $frenzy->condition);
    }
}
