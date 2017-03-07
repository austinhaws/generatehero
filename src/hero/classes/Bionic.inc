<?php

namespace Heroes\hero\classes;


class Bionic
{
    public $cost;
    public $location;
    public $title;
    public $description;
    public $requiredBionic;
    public $bonuses;

    // if true then no other bionic that also fills the location can be added to this location
    public $fillsLocation;

    /**
     * Bionic constructor.
     * @param $cost int how much
     * @param $requiredBionic string|bool uses BIonics::BODY... constants to tell which part of the body must be bionic for this bionic to be installed
     * @param $fillsLocation string|bool false = other bionics allowed at this location; true = no other bionic at this location; string (body_... constants) = no other bionic of this same string type at this location (ie can't have multiple claws in a single hand)
     * @param $title string type of bionic
     * @param $description string descriptive description describing
     * @param $bonuses array bonus entries the character gets for this bionic (these bonuses get added to the characters bonuses list)
     */
    public function __construct($cost, $requiredBionic, $fillsLocation, $title, $description, $bonuses)
    {
        // location is filled in when the bionic is actually selected
        $this->location = false;
        $this->cost = $cost;
        $this->title = $title;
        $this->description = $description;
        $this->requiredBionic = $requiredBionic;
        $this->bonuses = $bonuses;
    }


}