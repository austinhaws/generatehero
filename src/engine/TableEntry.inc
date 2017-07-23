<?php
namespace Heroes\engine;

class TableEntry {
    // max = 14, result = 'oh ya'
    // if a die roll for the table is greater than the previous entry and less than 14 then the result is 'oh ya'

    /** @var int what is the max possible value for this entry; sequencing maxes of each entry creates ranges of values for an entry */
    public $max;
    /** @var mixed what to return if this table entry is selected */
    public $result;

    /**
     * TableEntry constructor.
     * @param int $max usually on a roll of d100, what is the max value that this table entry's range works on. so if one entry was 1-12 and this one was 13-20 then max is 20 for this entry
     * @param mixed $result anything that you want to return if this result is rolled
     */
    public function __construct($max, $result)
    {
        $this->max = $max;
        $this->result = $result;
    }
}