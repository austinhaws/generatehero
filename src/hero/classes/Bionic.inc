<?php

namespace Heroes\hero\classes;

class Bionic
{
    public $cost;
    public $bionicLocation;
    public $title;
    public $description;
    public $bonuses;

    /**
     * Bionic constructor.
     * @param $cost int how much
     * @param $bionicLocation BionicLocation information about where the bionic piece goes
     * @param $title string type of bionic
     * @param $description string descriptive description describing
     * @param $bonuses array bonus entries the character gets for this bionic (these bonuses get added to the characters bonuses list)
     */
    public function __construct($cost, BionicLocation $bionicLocation, $title, $description, $bonuses)
    {
        // location is filled in when the bionic is actually selected
        $this->location = false;
        $this->cost = $cost;
        $this->title = $title;
        $this->description = $description;
        $this->bionicLocation = $bionicLocation;
        $this->bonuses = $bonuses;
    }
}