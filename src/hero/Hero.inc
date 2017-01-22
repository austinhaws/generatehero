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

    // logs tell how bonuses got applied to character for what reason
    // array of BonusesTypes
    public $bonuses = [];

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
