<?php
namespace Heroes\tables;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

/**
 * Class TableAttributes
 * apply attribute bonuses
 * "Attribute Bonus Chart" pg 4
 */
class TableAttributes extends TableBase
{
    /** @var int at what point do you start getting extra bonuses */
    private $bonusesBegin = 17;

    /**
     * skills must have run before this
     *
     * @param Hero $hero the hero to which to apply attribute bonuses
     */
    public function applyAttributeBonuses(Hero &$hero)
    {
        $this->applyAttributeBonus_IQ($hero);
        $this->applyAttributeBonus_MentalEndurance($hero);
        $this->applyAttributeBonus_MentalAffinity($hero);
        $this->applyAttributeBonus_PhysicalStrength($hero);
        $this->applyAttributeBonus_PhysicalProwess($hero);
        $this->applyAttributeBonus_PhysicalEndurance($hero);
        $this->applyAttributeBonus_PhysicalBeauty($hero);
        $this->applyAttributeBonus_Speed($hero);

        $this->calculateHitPoints($hero);
    }

    private function calculateHitPoints(Hero &$hero)
    {
        // physical endurance + 1d6
        $hpBonus = $this->engine->roller->rollDice(new Roll('starting hps bonus', 1, 6));
        $hero->hitPoints = $hero->physicalEndurance + $hpBonus;
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::HIT_POINTS, $hpBonus, 'Starting character bonus hit points'));

    }

    private function applyAttributeBonus_IQ(Hero &$hero)
    {
        if ($hero->intelligenceQuotient >= $this->bonusesBegin) {
            // one time bonus to all skills
            $bonus = $hero->intelligenceQuotient - 14;
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_ALL, $bonus, 'IQ Skill Bonus'));
        }

        $hero->iq = $hero->intelligenceQuotient * 10;
    }

    private function applyAttributeBonus_MentalEndurance(Hero &$hero)
    {
        if ($hero->mentalEndurance >= $this->bonusesBegin) {
            // psionic attack / insanity save bonus
            $bonus = 1 + floor(($hero->mentalEndurance - 16) / 2);
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_PSIONIC_ATTACK_INSANITY, $bonus, 'Mental Endurance'));
        }
    }

    private function applyAttributeBonus_MentalAffinity(Hero &$hero)
    {
        if ($hero->mentalAffinity >= $this->bonusesBegin) {
            switch ($hero->mentalAffinity) {
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                    $bonus = 45 + ($hero->mentalAffinity - 17) * 5;
                    break;
                case 25:
                case 26:
                case 27:
                    $bonus = 84 + ($hero->mentalAffinity - 25) * 4;
                    break;
                case 28:
                    $bonus = 94;
                    break;
                case 29:
                    $bonus = 96;
                    break;
                default:
                    $bonus = 97 + $hero->mentalAffinity - 30;
                    break;
            }
            // MA trust/intimidate
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::TRUST_INTIMIDATE, $bonus, 'Mental Affinity'));
        }
    }

    private function applyAttributeBonus_PhysicalStrength(Hero &$hero)
    {
        if ($hero->physicalStrength >= $this->bonusesBegin) {
            $bonus = $hero->physicalStrength - 15;
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PHYSICAL_DAMAGE, $bonus, 'Physical Strength'));
        }

        // carry/lift/throw weights
        if ($hero->physicalStrength <= 14) {
            $carryWeight = 10 * $hero->physicalStrength;
        } else if ($hero->physicalStrength <= 20) {
            $carryWeight = 20 * $hero->physicalStrength;
        } else {
            $carryWeight = 50 * $hero->physicalStrength;
        }

        $hero->carryThrowWeight = $carryWeight;
        $hero->liftWeight = $carryWeight * 2;
    }

    private function applyAttributeBonus_PhysicalProwess(Hero &$hero)
    {
        if ($hero->physicalProwess >= $this->bonusesBegin) {
            $bonus = 1 + floor(($hero->physicalProwess - 16) / 2);
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, $bonus, 'Physical Prowess Bonus'));
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, $bonus, 'Physical Prowess Bonus'));
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, $bonus, 'Physical Prowess Bonus'));
        }
    }

    private function applyAttributeBonus_PhysicalEndurance(Hero &$hero)
    {
        if ($hero->physicalEndurance >= $this->bonusesBegin) {
            $i = $hero->physicalEndurance;
            if ($i == 17) {
                $bonus = 5;
            } else {
                $bonus = 6 + ($hero->physicalEndurance - 18) * 2;
            }
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_COMMA_DEATH, $bonus, 'Physical Endurance Bonus'));

            $bonus = 1 + floor(($hero->physicalEndurance - 16) / 2);
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_MAGIC_PSIONICS_TOXINS, $bonus, 'Physical Endurance Bonus'));
        }
    }

    private function applyAttributeBonus_PhysicalBeauty(Hero &$hero)
    {
        $bonus = false;
        if ($hero->physicalBeauty >= 31) {
            $bonus = 92 + $hero->physicalBeauty - 30;
        } else if ($hero->physicalBeauty >= 17) {
            $bonus = [35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 83, 86, 90, 92][$hero->physicalBeauty - 17];
        }
        if ($bonus) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::CHARM_IMPRESS, $bonus, 'Physical Beauty'));
        }
    }

    private function applyAttributeBonus_Speed(Hero &$hero)
    {
        $hero->runsMilesPerHour = $hero->speed * 0.6818;
    }
}
