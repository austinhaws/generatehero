<?php
namespace Heroes\engine;

class TableRoller {
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
     * @throws \Exception if result isn't in the table
     */
    public function rollTable($name, $table) {
        if (!count($table)) {
            throw new \Exception('empty table');
        }

        $min = $table[0]->min;
        $max = $table[count($table) - 1]->max;
        $roll = $this->engine->roller->rollDice("$name", $min, $max);

        for ($x = 0; $x < count($table) && $table[$x]->max < $roll; $x++) {
            // move to the next table entry
        }

        // check that the reuslt is in bounds
        if ($x >= count($table)) {
            throw new \Exception("table location out of bounds: $x, {count($table)}");
        }

        // return the matched value
        return $table[$x]->result;
    }
}