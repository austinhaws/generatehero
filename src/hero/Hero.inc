<?php
namespace Heroes\hero;

use Heroes\enums\BonusTypes;
use Heroes\enums\Skills;

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

    public $skills;

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

    function __construct()
    {
        $this->skills = [
            Skills::CLIMBING => 0,
            Skills::CONCEALMENT => 0,
            Skills::ELECTRICAL_REPAIR => 0,
            Skills::ESCAPE_ARTIST => 0,
            Skills::MECHANICAL_REPAIR => 0,
            Skills::PALMING => 0,
            Skills::PICK_LOCKS => 0,
            Skills::PICK_POCKET => 0,
            Skills::PROWL => 0,
            Skills::SWIMMING => 0,
        ];
    }

    /**
     * set a value instead of adding to it. keep the larger value
     *
     * @param $bonusType String BonusTypes constant of the bonus
     * @param $value number/string how much the bonus is
     * @param $message string why they get this bonus
     * @throws \Exception
     */
    public function setBonus($bonusType, $value, $message)
    {

    }

    /**
     * explain why a character got a certain bonus
     * apply that bonus
     *
     * @param $bonusType String BonusTypes constant of the bonus
     * @param $value number/string how much the bonus is
     * @param $message string why they get this bonus
     * @throws \Exception
     */
    public function addBonus($bonusType, $value, $message)
    {
        $this->bonuses[] = new Bonus($bonusType, $value, $message);

        switch ($bonusType) {
            case BonusTypes::SKILL:
                throw new \Exception('Skills should instead use addSkillBonus');

            case BonusTypes::INTELLIGENCE_QUOTIENT:
                $this->intelligenceQuotient += $value;
                break;

            case BonusTypes::MENTAL_ENDURANCE:
                $this->mentalEndurance += $value;
                break;

            case BonusTypes::MENTAL_AFFINITY:
                $this->mentalAffinity += $value;
                break;

            case BonusTypes::PHYSICAL_STRENGTH:
                $this->physicalStrength += $value;
                break;

            case BonusTypes::PHYSICAL_PROWESS:
                $this->physicalProwess += $value;
                break;

            case BonusTypes::PHYSICAL_ENDURANCE:
                $this->physicalEndurance += $value;
                break;

            case BonusTypes::PHYSICAL_BEAUTY:
                $this->physicalBeauty += $value;
                break;

            case BonusTypes::SPEED:
                $this->speed += $value;
                break;

            case BonusTypes::HIT_POINTS:
                $this->hitPoints += $value;
                break;

            case BonusTypes::SDC:
                $this->sdc += $value;
                break;

            case BonusTypes::ATTACKS_PER_MELEE:
                $this->attacksPerMelee += $value;
                break;

            case BonusTypes::PARRY:
                $this->parry += $value;
                break;

            case BonusTypes::ROLL:
                $this->roll += $value;
                break;

            case BonusTypes::DODGE:
                $this->dodge += $value;
                break;

            case BonusTypes::MONEY:
                $this->money += $value;
                break;

            default:
                throw new \Exception("How is this bonus applied? - $bonusType");
        }
    }

    /**
     * add a skill bonus
     *
     * @param $skill string (Skills enum) the skill
     * @param $value int how much of a bonus
     * @param $message string why this bonus was given
     * @throws \Exception
     */
    public function addSkillBonus($skill, $value, $message)
    {
        if (!isset($this->skills[$skill])) {
            throw new \Exception("Skill default not set: $skill");
        }

        $this->bonuses[] = new Bonus(BonusTypes::SKILL . ' - ' . $skill, $value, $message);

        $this->skills[$skill] += $value;
    }

    /**
     * sets skill to the max of current/new value
     *
     * @param $skill string the skill
     * @param $value int the value of the skill
     * @param $message string reason for setting the skill
     * @throws \Exception
     */
    public function setSkillBonus($skill, $value, $message)
    {
        if (!isset($this->skills[$skill])) {
            throw new \Exception("Skill default not set: $skill");
        }

        if ($this->skills[$skill] < $value) {
            $this->bonuses[] = new Bonus(BonusTypes::SKILL . ' (set) - ' . $skill, $value, $message);
            $this->skills[$skill] = $value;
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
        }
        return $found ? false : true;
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
