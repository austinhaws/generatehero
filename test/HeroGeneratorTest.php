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

    public function testGenerate()
    {
        $this->testRoller->setTestRolls([
            new TestRoll(6, 3, 'intelligenceQuotient'),
            new TestRoll(6, 1, 'intelligenceQuotient'),
            new TestRoll(6, 2, 'intelligenceQuotient'),

            new TestRoll(6, 3, 'mentalEndurance'),
            new TestRoll(6, 1, 'mentalEndurance'),
            new TestRoll(6, 2, 'mentalEndurance'),

            new TestRoll(6, 3, 'mentalAffinity'),
            new TestRoll(6, 1, 'mentalAffinity'),
            new TestRoll(6, 2, 'mentalAffinity'),

            new TestRoll(6, 3, 'physicalStrength'),
            new TestRoll(6, 1, 'physicalStrength'),
            new TestRoll(6, 2, 'physicalStrength'),

            new TestRoll(6, 3, 'physicalProwess'),
            new TestRoll(6, 1, 'physicalProwess'),
            new TestRoll(6, 2, 'physicalProwess'),

            new TestRoll(6, 3, 'physicalEndurance'),
            new TestRoll(6, 1, 'physicalEndurance'),
            new TestRoll(6, 2, 'physicalEndurance'),

            new TestRoll(6, 3, 'physicalBeauty'),
            new TestRoll(6, 1, 'physicalBeauty'),
            new TestRoll(6, 2, 'physicalBeauty'),

            new TestRoll(6, 3, 'speed'),
            new TestRoll(6, 1, 'speed'),
            new TestRoll(6, 2, 'speed'),

            new TestRoll(100, 1, 'is crazy?'),
            new TestRoll(100, 100, 'power category'),

            // -- skip alien stuff -- //

            (new TestRoll())->dontCareUntil('Alignment')->andRoll(100, 1, 'Alignment'),

            new TestRoll(100, 30, 'birth order'),
            new TestRoll(100, 30, 'weight'),
            new TestRoll(100, 30, 'height'),
            new TestRoll(100, 30, 'disposition'),
            new TestRoll(100, 30, 'life savings'),
            new TestRoll(100, 30, 'land of origin'),
            new TestRoll(100, 30, 'environment'),
            new TestRoll(100, 30, 'social/economic background'),
            new TestRoll(100, 30, 'when manifested'),

            new TestRoll(6, 2, 'starting hps bonus'),
        ]);
        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();
    }

    public function testGenerate_isCrazy_frenzy()
    {
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('is crazy?')->andRoll(100, 100, 'is crazy?'),
            new TestRoll(100, 1, 'crazy element'),
            new TestRoll(100, 12, 'Frenzy: condition'),

            // all done being crazy
            new TestRoll(100, 100, 'power category'),
            (new TestRoll())->dontCareUntil(true),
        ]);

        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();

        $this->assertNotNull($hero->crazy);
        $this->assertTrue($hero->crazy instanceof Frenzy);
    }

    public function testGenerate_isCrazy_association() {
        $this->testRoller->setTestRolls([
            (new TestRoll())->dontCareUntil('is crazy?')->andRoll(100, 100, 'is crazy?'),
            new TestRoll(100, 60, 'crazy element'),
            new TestRoll(100, 31, 'Association: association'),
            new TestRoll(100, 1, 'Popeye: power food'),

            // all done being crazy
            new TestRoll(100, 100, 'power category'),
            (new TestRoll())->dontCareUntil(true),
        ]);

        $hero = $this->heroGenerator->generate();
        $this->testRoller->verifyTestRolls();

        $this->assertNotNull($hero->crazy);
        $this->assertEquals('Garlic', $hero->crazy->popeye);
    }
}
