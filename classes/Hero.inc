<?php
require_once 'enums/BonusTypes.inc';
require_once 'classes/Bonus.inc';

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

    public function outputCharacter() {
        throw new Exception('did you cover all this stuff?');
/*
 * Other calculations
 *  [ ] Spd - spd * 20 = # of yards ran per minute (turn this to miles per hour or a football 4x40 stat)
 *
 *
 * rolling attributes:
 *  [ ] attributes of 16 or higher get a one time bonus of 1d6
 *
 *
 */
    }
}
