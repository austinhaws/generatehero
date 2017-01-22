<?php
namespace Heroes\engine;

class TableRoller {
    private $engine;

    const RESULT = 'result';
    const MIN = 'min';
    const MAX = 'max';

    public function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * roll on a table and run the result
     * note that the maximum possible value MUST be the max of the last item in the array
     *
     * @param $table array of range => [min, max], result => function
     * @return mixed table's specified RESULT
     * @throws \Exception if result isn't in the table
     */
    public function rollTable($table) {
        if (!count($table)) {
            throw new \Exception('empty table');
        }

        $min = $table[0][TableRoller::MIN];
        $max = $table[count($table) - 1][TableRoller::MAX];
        $roll = $this->engine->roller->rollDice($min, $max);

        for ($x = 0; $x < count($table) && $table[$x][TableRoller::MAX] < $roll; $x++) {
            // move to the next table entry
        }

        // call the function on the matched result
        if ($x >= count($table)) {
            throw new \Exception("table location out of bounds: $x, {count($table)}");
        }

        return $table[$x][TableRoller::RESULT];
    }
}