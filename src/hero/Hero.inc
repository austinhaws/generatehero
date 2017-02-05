<?php
namespace Heroes\hero;

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

    public $skills = [];

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

    /**
     * add a bonus to the character; it will be applied later after all bonuses gathered
     *
     * @param Bonus $bonus the bonus to add
     */
    public function addBonus(Bonus $bonus)
    {
        $this->bonuses[] = $bonus;
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
}
