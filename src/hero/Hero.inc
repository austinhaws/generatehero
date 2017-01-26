<?php
namespace Heroes\hero;

class Hero {
    // abilities
    public $intelligenceQuotient;
    public $mentalEndurance;
    public $mentalAffinity;
    public $physicalStrength;
    public $physicalProwess;
    public $physicalEndurance;
    public $physicalBeauty;
    public $speed;

    // calculateds
    public $carryThrowWeight;
    public $liftWeight;
    public $iq;
    public $runsMilesPerHour;

    // health
    public $hitPoints;

    // optionals
    public $birthOrder;
    public $weight;
    public $height;
    public $disposition;
    public $lifeSavings;
    public $landOfOrigin;
    public $environment;
    public $socialEconomic;
    public $whenManifested;

    // false or a class of BaseCrazy type
    public $crazy = null;

    // logs tell how bonuses got applied to character for what reason
    // array of BonusesTypes
    public $bonuses = [];

    // if the character picks up an insanity it is loaded here (pg 24)
    public $insanities = [];

    /**
     * explain why a character got a certain bonus
     *
     * @param $bonusType String BonusTypes constant of the bonus
     * @param $value number/string how much the bonus is
     * @param $message string why they get this bonus
     */
    public function addBonus($bonusType, $value, $message) {
        $this->bonuses[] = new Bonus($bonusType, $value, $message);
    }

    /**
     * @return string the character information
     */
    public function outputCharacter() {
        return json_encode($this);
    }
}
