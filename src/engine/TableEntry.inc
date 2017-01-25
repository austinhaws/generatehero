<?php
namespace Heroes\engine;

class TableEntry {
    // max = 14, result = 'oh ya'
    // if a die roll for the table is greater than the previous and entry and less than 14 then the result is 'oh ya'
    public $max;
    public $result;

    public function __construct($max, $result)
    {
        $this->max = $max;
        $this->result = $result;
    }
}