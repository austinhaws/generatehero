<?php

namespace Heroes\hero;


class Ability
{
    /** @var string title */
    public $title;
    /** @var string description */
    public $description;
    /** @var array bonuses for having this ability */
    public $bonuses;

    /**
     * Ability constructor.
     * @param $title string the name of the ability
     * @param $description string technicalities of the ability
     * @param $bonuses array of Bonus objects; some abilities give bonuses to the character's abilities, skills, etc
     */
    function __construct($title, $description, $bonuses = [])
    {
        $this->title = $title;
        $this->description = $description;
        $this->bonuses = $bonuses;
    }
}