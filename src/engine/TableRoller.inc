<?php
namespace Heroes\engine;

use RuntimeException;

class TableRoller {
    /** @var Engine the engine! */
    private $engine;

    public function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * roll on a table and run the result
     * note that the maximum possible value MUST be the max of the last item in the array
     *
     * @param $name string name of the table being rolled for testing, informational, and debug purposes
     * @param $table array of Table class
     * @return mixed table's specified RESULT
     */
    public function rollTable($name, $table) {
        if (!count($table)) {
            throw new RuntimeException('empty table');
        }

        $max = $table[count($table) - 1]->max;
        $roll = $this->engine->roller->rollDice(new Roll("$name", 1, $max));

        for ($x = 0; $x < count($table) && $table[$x]->max < $roll; $x++) {
            // move to the next table entry
        }

        // check that the reuslt is in bounds
        if ($x >= count($table)) {
            throw new RuntimeException("table location out of bounds: $x, {count($table)}");
        }

        // return the matched value
        return $table[$x]->result;
    }
}
