<?php

namespace Heroes\hero;


class Ability
{
    public $title;
    public $description;
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