<?php

namespace Heroes\test\hero\crazy;

use Heroes\hero\crazy\Crazy;
use Heroes\hero\Hero;
use Heroes\HeroGenerator;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class CrazyTest extends \PHPUnit_Framework_TestCase
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

    public function testCrazy()
    {
        $crazy = new Crazy($this->heroGenerator->engine);

        $this->testRoller->setTestRolls([
            new TestRoll(100, 13, 'Insanity: Phobia'),
            new TestRoll(100, 13, 'Insanity: Phobia'),
            new TestRoll(2, 1, 'Obsession: love/hate'),
            new TestRoll(100, 56, 'Insanity: Obsession'),
        ]);
        $hero = new Hero();
        $crazy->create($hero);
        $this->testRoller->verifyTestRolls();

        $this->assertEquals(3, count($hero->insanities));
    }
}
