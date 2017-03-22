<?php
namespace Heroes\test\engine;

use Heroes\engine\TableEntry;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class TableRollerTest extends BaseTestRunner
{
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
            new TableEntry(20, 1),
        ]));

        $this->engine->roller->verifyTestRolls();
    }

    public function testRollTable_Many()
    {
        $this->engine->roller->setTestRolls([new TestRoll(80, 65, 'multiple entry test')]);

        $this->assertEquals(4, $this->engine->tableRoller->rollTable('multiple entry test', [
            new TableEntry(20, 1),
            new TableEntry(40, 2),
            new TableEntry(60, 3),
            new TableEntry(80, 4),
        ]));

        $this->engine->roller->verifyTestRolls();
    }
}