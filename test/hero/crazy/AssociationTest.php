<?php

namespace Heroes\test\hero\crazy;

use Heroes\hero\crazy\Association;
use Heroes\HeroGenerator;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class AssociationTest extends \PHPUnit_Framework_TestCase
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

    public function testAssociation_notPopey()
    {
        $association = new Association($this->heroGenerator->engine);

        $this->testRoller->setTestRolls([
            new TestRoll(100, 100, 'Association: association'),
        ]);
        $association->create();
        $this->testRoller->verifyTestRolls();

        $this->assertEquals('Solar Syndrome', $association->association);
        $this->assertEquals(false, $association->popeye);
    }

    public function testAssociation_popey()
    {
        $association = new Association($this->heroGenerator->engine);

        $this->testRoller->setTestRolls([
            new TestRoll(100, 31, 'Association: association'),
            new TestRoll(100, 100, 'Popeye: power food'),
        ]);
        $association->create();
        $this->testRoller->verifyTestRolls();

        $this->assertEquals('Popeye Syndrome', $association->association);
        $this->assertEquals('Twinkies', $association->popeye);

    }
}
