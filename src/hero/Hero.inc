<?php
namespace Heroes\hero;

use Exception;
use Heroes\engine\Engine;
use Heroes\enums\BonusTargets;
use Heroes\hero\classes\BaseClass;
use Heroes\hero\insanity\Insanity;

class Hero
{
    // abilities
    /** @var int iq */
    public $intelligenceQuotient;
    /** @var int me */
    public $mentalEndurance;
    /** @var int ma */
    public $mentalAffinity;
    /** @var int ps */
    public $physicalStrength;
    /** @var int pp */
    public $physicalProwess;
    /** @var int pe */
    public $physicalEndurance;
    /** @var int pb */
    public $physicalBeauty;
    /** @var int speed */
    public $speed;

    // calculateds
    /** @var int */
    public $carryThrowWeight;
    /** @var int */
    public $liftWeight;
    /** @var int */
    public $iq;
    /** @var int */
    public $runsMilesPerHour;

    // health
    /** @var int */
    public $hitPoints = 0;
    /** @var int */
    public $sdc = 0;
    /** @var boolean some classes (mutant animals) calculate SDC differently so they won't have the end calculation */
    public $SDCCalculated = false;

    // optionals
    /** @var int */
    public $birthOrder;
    /** @var int */
    public $weight;
    /** @var int */
    public $height;
    /** @var string */
    public $disposition;
    /** @var int */
    public $lifeSavings;
    /** @var string */
    public $landOfOrigin;
    /** @var string */
    public $environment;
    /** @var string */
    public $socialEconomic;
    /** @var string */
    public $whenManifested;

    /** @var int */
    public $money = 0;

    /** @var string */
    public $alignment;

    // bonus to charm/impress rolls
    /** @var int */
    public $charmImpress;

    // alien/mutant/etc
    /** @var BaseClass */
    public $class;

    // combat
    /** @var int */
    public $attacksPerMelee = 2;
    /** @var int */
    public $parry;
    /** @var int */
    public $roll;
    /** @var int */
    public $dodge;
    /** @var int private because setting should keep the max and not be cumulative */
    private $naturalArmor;

    /** @var boolean|BaseClass */
    public $crazy = null;

    // logs tell how bonuses got applied to character for what reason
    /** @var Bonus[] bonuses that the character has amassed to be tallied at end of generation */
    public $bonuses = [];

    /** @var Insanity[] if the character picks up an insanity it is loaded here (pg 24) */
    public $insanities = [];

    /** @var Ability[] abilities and super abilities of the hero */
    public $abilities = [];
    /** @var Psionic[] Psionics of the hero */
    public $psionics = [];

    /** @var bool|string high school? college? alien? - if this is set then don't do education again */
    public $educationLevel = false;

    /** @var string[] don't allow picking the same program more than once */
    public $educationProgramsPicked = [];

    // how old are you? is there a randomizer for this? some classes set it (mystic bestowed: old age physical limitation)
    /** @var int */
    public $age;


    public function __construct()
    {
        // if not false, then it's already set, so don't recalculate it (mutants set height/weight outside of normal setting rules)
        $this->weight = false;
        $this->height = false;
    }


    /**
     * add a bonus to the character; it will be applied later after all bonuses gathered
     *
     * @param Bonus|array $bonus the bonus to add
     */
    public function addBonus($bonus)
    {
        if ($bonus) {
            if (!is_array($bonus)) {
                $bonus = [$bonus];
            }
            foreach ($bonus as $b) {
                $this->bonuses[] = $b;
            }
        }
    }

    /**
     * add a skill to the hero. same as adding a bonus but now it's clear what it's doing
     *
     * @param string $skill the string name of the skill to add BonusTargets::SKILL_... constants
     * @param string $reason why the skill is being added
     * @param int $skillBonus what bonus to give the skill
     */
    public function addSkill($skill, $reason, $skillBonus = 0)
    {
        $this->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, $skill, $skillBonus, $reason));
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
            return $testAbility->title === $ability->title;
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
     * add a psionic to a hero, checking if it's already added
     *
     * @param Psionic $psionic the psionic
     * @return bool true if it was added, false if not added
     */
    public function addPsionic(Psionic $psionic) {
        $found = count(array_filter($this->psionics, function (Psionic $testAbility) use ($psionic) {
            return $testAbility->title === $psionic->title;
        }));
        if (!$found) {
            $this->psionics[] = $psionic;
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
     * @throws Exception
     */
    public function hasSkill($skill, $basePercent, Engine $engine)
    {
        $found = false;
        $isHandToHand = $this->skillIsHandToHand($skill);
        foreach ($this->bonuses as $bonus) {
            $bonus->bonusTarget;
            $bonus->getValue($engine);
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

    /**
     * @param $skills string[] the skills to add
     * @param $reason string why is this skill being added?
     * @param $bonus int base starting percent (0 to just add the skill)
     */
    public function addSkills($skills, $reason, $bonus)
    {
        foreach ($skills as $skill) {
            $this->addSkill($skill, $reason, $bonus);
        }
    }
}
