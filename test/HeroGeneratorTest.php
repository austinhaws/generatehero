<?php

namespace Heroes\test;

use Heroes\hero\crazy\Frenzy;
use Heroes\HeroGenerator;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class HeroGeneratorTest extends \PHPUnit_Framework_TestCase
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

    public function testGenerate_isCrazy_frenzy()
    {
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('is crazy?'),
            new TestRoll(100, 100, 'is crazy?'),
            new TestRoll(100, 1, 'crazy element'),
            new TestRoll(100, 12, 'Frenzy: condition'),

            // all done being crazy
            new TestRoll(100, 1, 'power category'),
            (new TestRoll())->dontCareUntil(true),
        ]);

        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();

        $this->assertNotNull($hero->crazy);
        $this->assertTrue($hero->crazy instanceof Frenzy);
    }

    public function testGenerate_isCrazy_association() {
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('is crazy?'),
            new TestRoll(100, 100, 'is crazy?'),
            new TestRoll(100, 60, 'crazy element'),
            new TestRoll(100, 31, 'Association: association'),
            new TestRoll(100, 1, 'Popeye: power food'),

            // all done being crazy
            new TestRoll(100, 1, 'power category'),
            (new TestRoll())->dontCareUntil(true),
        ]);

        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();

        $this->assertNotNull($hero->crazy);
        $this->assertEquals('Garlic', $hero->crazy->popeye);
    }
}
