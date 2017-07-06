<?php
namespace Heroes\hero\classes;

class MutantAnimalPsionic
{
    /** @var  String what type of creature */
    public $name;
    /** @var  String animal definition */
    public $description;
    /** @var  String */
    public $range;
    /** @var  String */
    public $duration;
    /** @var  String */
    public $savingThrow;
    /** @var int */
    public $cost;

    public function __construct($name, $description, $range, $duration, $savingThrow, $cost)
    {
        $this->name = $name;
        $this->description = $description;
        $this->range = $range;
        $this->duration = $duration;
        $this->savingThrow = $savingThrow;
        $this->cost = $cost;
    }
}