<?php

namespace Heroes\hero;


class Spell
{
    /** @var string title */
    public $title;
    /** @var string range */
    public $range;
    /** @var string duration */
    public $duration;
    /** @var string savingThrow */
    public $savingThrow;
    /** @var string description */
    public $description;

    function __construct($title, $range, $duration, $savingThrow, $description)
    {
        $this->title = $title;
        $this->range = $range;
        $this->duration = $duration;
        $this->savingThrow = $savingThrow;
        $this->description = $description;
    }
}

