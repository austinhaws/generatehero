<?php
namespace Heroes\engine;

class TableEntry {
    // min = 3, max = 14, result = 'oh ya'
    // if a die roll for the table is between 3 and 14 then the result is 'oh ya'
    public $min;
    public $max;
    public $result;

    public function __construct($min, $max, $result)
    {
        $this->min = $min;
        $this->max = $max;
        $this->result = $result;
    }
}