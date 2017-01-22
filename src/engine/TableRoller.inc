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
     * @param $table array of range => [min, max], result => function
     */
    public function rollTable($table) {
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