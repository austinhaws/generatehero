<?php
namespace Heroes\test\engine;

use Heroes\engine\Engine;
use Heroes\engine\TableRoller;
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
            $this->engine->tableRoller->rollTable([]);
            $this->assertTrue(false, 'should have got exception about an empty table');
        } catch (\Exception $exception) {
            $this->assertTrue(strPos($exception->getMessage(), 'empty') !== false);
        }
    }

    public function testRollTable_Single()
    {
        $this->engine->roller->setTestRolls([['sides' => 20, 'roll' => 15]]);

        $this->assertEquals(1, $this->engine->tableRoller->rollTable([
            [TableRoller::MIN => 1, TableRoller::MAX => 20, TableRoller::RESULT => 1],
        ]));

        $this->engine->roller->verifyTestRolls();
    }

    public function testRollTable_Many()
    {
        $this->engine->roller->setTestRolls([['sides' => 80, 'roll' => 65]]);

        $this->assertEquals(4, $this->engine->tableRoller->rollTable([
            [TableRoller::MIN => 1, TableRoller::MAX => 20, TableRoller::RESULT => 1],
            [TableRoller::MIN => 21, TableRoller::MAX => 40, TableRoller::RESULT => 2],
            [TableRoller::MIN => 41, TableRoller::MAX => 60, TableRoller::RESULT => 3],
            [TableRoller::MIN => 61, TableRoller::MAX => 80, TableRoller::RESULT => 4],
        ]));

        $this->engine->roller->verifyTestRolls();
    }

    /**
     * roll on a table and run the result
     * note that the maximum possible value MUST be the max of the last item in the array
     *
     * @param $table array of range => [min, max], result => function
     */
    public function rollTable($table)
    {
        $min = $table[0]['min'];
        $max = $table[count($table) - 1]['max'];
        $roll = $this->engine->roller->rollDice($min, $max);

        for ($x = 0; $table[$x]['max'] < $roll; $x++) {
            // move to the next table entry
        }

        // call the function on the matched result
        $table[$x]['result']();
    }
}