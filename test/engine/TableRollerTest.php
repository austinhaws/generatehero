<?php
namespace Heroes\test\engine;

use Heroes\engine\Engine;
use Heroes\engine\TableEntry;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class TableRollerTest extends \PHPUnit_Framework_TestCase
{
    private $engine;

    public function __construct($name = NULL, array $data = array(), $dataName = '')
    {
        parent::__construct($name, $data, $dataName);

        $this->engine = new Engine();
        $this->engine->roller = new TestRoller();
    }

    public function testRollTable_None()
    {
        try {
            $this->engine->tableRoller->rollTable('no entries test', []);
            $this->assertTrue(false, 'should have got exception about an empty table');
        } catch (\Exception $exception) {
            $this->assertTrue(strPos($exception->getMessage(), 'empty') !== false);
        }
    }

    public function testRollTable_Single()
    {
        $this->engine->roller->setTestRolls([new TestRoll(20, 15, 'single entry test')]);

        $this->assertEquals(1, $this->engine->tableRoller->rollTable('single entry test', [
            new TableEntry(1, 20, 1),
        ]));

        $this->engine->roller->verifyTestRolls();
    }

    public function testRollTable_Many()
    {
        $this->engine->roller->setTestRolls([new TestRoll(80, 65, 'multiple entry test')]);

        $this->assertEquals(4, $this->engine->tableRoller->rollTable('multiple entry test', [
            new TableEntry(1, 20, 1),
            new TableEntry(21, 40, 2),
            new TableEntry(41, 60, 3),
            new TableEntry(61, 80, 4),
        ]));

        $this->engine->roller->verifyTestRolls();
    }
}