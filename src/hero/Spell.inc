<?php

namespace Heroes\hero;


class Spell
{
    public $title;
    public $range;
    public $duration;
    public $savingThrow;
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

