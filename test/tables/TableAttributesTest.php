<?php
namespace Heroes\tests\tables;

use Heroes\engine\Engine;
use Heroes\hero\Hero;
use Heroes\tables\TableAttributes;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class TableAttributesTest extends \PHPUnit_Framework_TestCase
{
    private $engine;
    private $tableAttributes;

    function __construct($name = NULL, array $data = array(), $dataName = '')
    {
        parent::__construct($name, $data, $dataName);

        $this->engine = new Engine();
        $this->engine->roller = new TestRoller();
        $this->tableAttributes = new TableAttributes($this->engine);
    }

    public function testApplyAttributeBonuses_applyIQ() {
        $this->engine->roller->setTestRolls([
            new TestRoll(6, 2, 'starting hps bonus'),
        ]);

        $hero = new Hero();
        $hero->intelligenceQuotient = 16;
        $this->tableAttributes->applyAttributeBonuses($hero);

        $this->engine->roller->verifyTestRolls();

        // this may not be right because it doesn't do the adds yet?
        $this->assertEquals(16, $hero->intelligenceQuotient);
        $this->assertEquals(2, $hero->hitPoints);

    }
}
