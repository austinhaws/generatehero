<?php
namespace Heroes\hero;

use Heroes\engine\Engine;
use Heroes\enums\BonusTargets;

class Hero
{
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
    public $hitPoints = 0;
    public $sdc = 0;

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

    public $money = 0;

    public $alignment;

    // bonus to charm/impress rolls
    public $charmImpress;

    // alien/mutant/etc
    public $class;

    // combat
    public $attacksPerMelee = 2;
    public $parry;
    public $roll;
    public $dodge;
    // private because setting should keep the max and not be cumulative
    private $naturalArmor;

    // false or a class of BaseCrazy type
    public $crazy = null;

    // logs tell how bonuses got applied to character for what reason
    // array of BonusesTypes
    public $bonuses = [];

    // if the character picks up an insanity it is loaded here (pg 24)
    public $insanities = [];

    // abilities and super abilities of the hero; array of Ability classes
    public $abilities = [];

    // high school? college? alien? - if this is set then don't do education again
    public $educationLevel = false;

    // don't allow picking the same program more than once
    public $educationProgramsPicked = [];


    /**
     * add a bonus to the character; it will be applied later after all bonuses gathered
     *
     * @param Bonus|array $bonus the bonus to add
     */
    public function addBonus($bonus)
    {
        if (!is_array($bonus)) {
            $bonus = [$bonus];
        }
        foreach ($bonus as $b) {
            $this->bonuses[] = $b;
        }
    }


    /**
     * @return string the character information
     */
    public function outputCharacter()
    {
        return json_encode($this);
    }

    /**
     * ability or super ability of the hero
     *
     * @param Ability $ability new ability to try to add
     * @return boolean true if the ability was added, false if it already existed
     */
    public function addAbility(Ability $ability)
    {
        $found = count(array_filter($this->abilities, function (Ability $testAbility) use ($ability) {
            return $testAbility->title == $ability->title;
        }));
        if (!$found) {
            $this->abilities[] = $ability;

            // also add the bonuses of the ability for later adding to there character
            foreach ($ability->bonuses as $bonus) {
                $this->addBonus($bonus);
            }
        }
        return !$found;
    }

    /**
     * keep the max natural armor
     *
     * @param $naturalArmor int possible new natural armor value
     */
    public function setNaturalArmor($naturalArmor)
    {
        $this->naturalArmor = max($naturalArmor ? $naturalArmor : 0, $this->naturalArmor);
    }

    /**
     * check if hero already has a skill started, and if so that the percent is higher
     *
     * @param $skill string the skill for which to check BonusTargets::SKILL_...
     * @param $basePercent int the percent that this skill could be added at
     * @param Engine $engine so that rolls can be made if needed
     * @return true if a skill bonus set is found for the skill that has a percent >= the passed in percent
     */
    public function hasSkill($skill, $basePercent, Engine $engine)
    {
        $found = false;
        $isHandToHand = $this->skillIsHandToHand($skill);
        foreach ($this->bonuses as $bonus) {
            if ($bonus->bonusType == Bonus::BONUS_TYPE_SET
                && ($bonus->bonusTarget == $skill || ($isHandToHand && $this->skillIsHandToHand($bonus->bonusTarget)))
                && $bonus->getValue($engine) >= $basePercent) {
                $found = true;
                break;
            }
        }
        return $found;
    }

    /**
     * is the skill a hand-to-hand category skill?
     *
     * @param $skill string skill in question
     * @return bool true if it's a hand to hand skill (basic, expert, martial)
     */
    private function skillIsHandToHand($skill) {
        return $skill == BonusTargets::SKILL_HAND_TO_HAND_BASIC || $skill == BonusTargets::SKILL_HAND_TO_HAND_EXPERT || $skill == BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS;
    }
}
