<?php

namespace Heroes\test\hero\crazy;

use Heroes\HeroGenerator;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class AliensTest extends \PHPUnit_Framework_TestCase
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

    public function testAssociation_alien()
    {
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 100, 'power category'),
            (new TestRoll())->dontCareUntil('appearance')->andRoll(100, 1, 'appearance'),
        ]);

        $this->heroGenerator->generate();

        $this->testRoller->verifyTestRolls();
    }
}
