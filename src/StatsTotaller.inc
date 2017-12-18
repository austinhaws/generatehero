<?php

namespace Heroes;

use Heroes\engine\Engine;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

class StatsTotaller
{
    /** @var Engine drive me */
    public $engine;

    /**
     * HeroGenerator constructor.
     * @param Engine $engine allows testing to override engine
     */
    public function __construct(Engine $engine = null)
    {
        $this->engine = $engine ? $engine : new Engine();
    }


    /**
     * attributes are already totaled, so skip those
     * 
     * @param Hero $hero the hero on which to total non-attribute stats
     */
    public function calculateNonAttributeTotals(Hero &$hero)
    {
        // do all skills
        $this->calculateBonusGroup($hero, BonusTargets::allSkills(false));

        // then do skill groups
        $this->calculateBonusGroup($hero, [
            BonusTargets::SKILL_GROUP_DECEPTION_SLEIGHT_OF_HAND,
            BonusTargets::SKILL_GROUP_PHYSICAL,
            BonusTargets::SKILL_GROUP_DELICATE_TOUCH,
            BonusTargets::SKILL_GROUP_PILOTING,
            BonusTargets::SKILL_GROUP_PILOTING_RELATED,
            BonusTargets::SKILL_GROUP_COMPUTER_ELECTRICAL_MECHANICAL,
            BonusTargets::SKILL_GROUP_AGILITY_DEXTERITY,
        ]);

        // then do skill group ALL - the ALL group needs to go last because it adds to taken skills but doesn't actually take skills
        $this->calculateBonusGroup($hero, [BonusTargets::SKILL_GROUP_ALL]);

        // apply any bonuses not yet applied
        foreach ($hero->bonuses as $bonus) {
            if (!$bonus->isApplied) {
                $this->applyBonus($hero, $bonus);
            }
        }
    }

    /**
     * applies a bonus value to a field in the hero
     *
     * @param Bonus $bonus the bonus to apply
     * @param string|int $field the field to update
     * @throws \Exception
     */
    private function applyBonusToField(Bonus $bonus, &$field)
    {
        if (!$field && $field !== false && $field !== 0 && $field !== 0.0 && $field !== '') {
            var_dump(['field' => $field, 'bonus' => $bonus]);
            throw new \Exception('Field should have a starting value: "' . $bonus->bonusTarget . '" : "' . $field . '" - ' . $bonus->getValue($this->engine));
        }

        // the value of the bonus
        $bonusValue = $bonus->getValue($this->engine);

        switch ($bonus->bonusType) {
            case Bonus::BONUS_TYPE_MINIMUM:
            case Bonus::BONUS_TYPE_SET:
                // keep higher value
                if ($field < $bonusValue) {
                    $field = $bonusValue;
                }
                break;

            case Bonus::BONUS_TYPE_ADD:
                // some fields are set to false to show that they were not set
                if ($field === false) {
                    $field = 0;
                }
                $field += $bonusValue;
                break;

            case Bonus::BONUS_TYPE_MULTIPLY:
                $field *= $bonusValue;
                break;

            default:
                var_dump($bonus);
                throw new \Exception('Bonus has unknown bonus type:' . $bonus->bonusType);
        }
    }

    /**
     * get target field and apploy bonus to it
     *
     * @param Hero $hero the hero to update
     * @param Bonus $bonus the bonus to apply to the here
     * @throws \Exception yep, you'll get this
     */
    private function applyBonus(Hero &$hero, Bonus &$bonus)
    {
        
        if ($bonus->isApplied) {
            var_dump($bonus);
            throw new \Exception('Bonus already applied');
        }
        
        switch ($bonus->bonusTarget) {
            case BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT:
                $this->applyBonusToField($bonus, $hero->intelligenceQuotient);
                break;
            case BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE:
                $this->applyBonusToField($bonus, $hero->mentalEndurance);
                break;
            case BonusTargets::ATTRIBUTE_MENTAL_AFFINITY:
                $this->applyBonusToField($bonus, $hero->mentalAffinity);
                break;
            case BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH:
                $this->applyBonusToField($bonus, $hero->physicalStrength);
                break;
            case BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS:
                $this->applyBonusToField($bonus, $hero->physicalProwess);
                break;
            case BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE:
                $this->applyBonusToField($bonus, $hero->physicalEndurance);
                break;
            case BonusTargets::ATTRIBUTE_PHYSICAL_BEAUTY:
                $this->applyBonusToField($bonus, $hero->physicalBeauty);
                break;
            case BonusTargets::ATTRIBUTE_SPEED:
                $this->applyBonusToField($bonus, $hero->speed);
                break;

            case BonusTargets::HIT_POINTS:
                $this->applyBonusToField($bonus, $hero->hitPoints);
                break;
            case BonusTargets::SDC:
                $this->applyBonusToField($bonus, $hero->sdc);
                break;
            case BonusTargets::WEIGHT:
                $this->applyBonusToField($bonus, $hero->weight);
                break;
            case BonusTargets::MONEY:
                $this->applyBonusToField($bonus, $hero->money);
                break;

            case BonusTargets::STRIKE:
                $this->applyBonusToField($bonus, $hero->strike);
                break;
            case BonusTargets::ATTACKS_PER_MELEE:
                $this->applyBonusToField($bonus, $hero->attacksPerMelee);
                break;
            case BonusTargets::PHYSICAL_DAMAGE:
            case BonusTargets::DAMAGE:
                $this->applyBonusToField($bonus, $hero->damageBonus);
                break;
            case BonusTargets::DODGE:
                $this->applyBonusToField($bonus, $hero->dodge);
                break;
            case BonusTargets::INITIATIVE:
                $this->applyBonusToField($bonus, $hero->initiativeBonus);
                break;
            case BonusTargets::NATURAL_ARMOR_RATING:
                $this->applyBonusToField($bonus, $hero->naturalArmor);
                break;
            case BonusTargets::PARRY:
                $this->applyBonusToField($bonus, $hero->parry);
                break;
            case BonusTargets::PULL_PUNCH:
                $this->applyBonusToField($bonus, $hero->pullPunch);
                break;
            case BonusTargets::ROLL:
                $this->applyBonusToField($bonus, $hero->rollWithPunch);
                break;

            case BonusTargets::SAVE_COMMA:
                $this->applyBonusToField($bonus, $hero->saveComma);
                break;
            case BonusTargets::SAVE_DEATH:
                $this->applyBonusToField($bonus, $hero->saveDeath);
                break;
            case BonusTargets::SAVE_GASES:
                $this->applyBonusToField($bonus, $hero->saveGases);
                break;
            case BonusTargets::SAVE_CHEMICALS:
                $this->applyBonusToField($bonus, $hero->saveChemicals);
                break;
            case BonusTargets::SAVE_CONTROL_OTHERS:
                $this->applyBonusToField($bonus, $hero->saveControlOthers);
                break;
            case BonusTargets::SAVE_ILLUSIONS:
                $this->applyBonusToField($bonus, $hero->saveIllusions);
                break;
            case BonusTargets::SAVE_MAGIC:
                $this->applyBonusToField($bonus, $hero->saveMagic);
                break;
            case BonusTargets::SAVE_SPELLS:
                $this->applyBonusToField($bonus, $hero->saveSpells);
                break;
            case BonusTargets::SAVE_ENCHANTMENTS:
                $this->applyBonusToField($bonus, $hero->saveEnchantments);
                break;
            case BonusTargets::SAVE_MIND_ALTERING_EFFECTS:
                $this->applyBonusToField($bonus, $hero->saveMindAlteringEffects);
                break;
            case BonusTargets::SAVE_POISON:
                $this->applyBonusToField($bonus, $hero->savePoison);
                break;
            case BonusTargets::SAVE_POSSESSION:
                $this->applyBonusToField($bonus, $hero->savePossession);
                break;
            case BonusTargets::SAVE_PSIONICS:
                $this->applyBonusToField($bonus, $hero->savePsionics);
                break;
            case BonusTargets::SAVE_PSIONIC_ATTACK_INSANITY:
                $this->applyBonusToField($bonus, $hero->savePsionicAttackInsanity);
                break;
            case BonusTargets::SAVE_TOXINS:
                $this->applyBonusToField($bonus, $hero->saveToxins);
                break;

            case BonusTargets::TRUST_INTIMIDATE:
                $this->applyBonusToField($bonus, $hero->trustIntimidate);
                break;
            case BonusTargets::CHARM_IMPRESS:
                $this->applyBonusToField($bonus, $hero->charmImpress);
                break;
            case BonusTargets::BALANCE_WALK_TIGHTROPE:
                $this->applyBonusToField($bonus, $hero->balanceWalkTightrope);
                break;
            case BonusTargets::MAINTAIN_GRIP_HOLD_FOOTING:
                $this->applyBonusToField($bonus, $hero->maintainGripHoldFooting);
                break;
            case BonusTargets::CARRY_WEIGHT:
                $this->applyBonusToField($bonus, $hero->carryThrowWeight);
                break;

            case BonusTargets::UNDERSTAND_OPERATE_ALIEN_MACHINES:
                $this->applyBonusToField($bonus, $hero->understandOperateAlienMachines);
                break;
            case BonusTargets::RECOGNIZE_IDENTIFY_PLANTS:
                $this->applyBonusToField($bonus, $hero->recognizeIdentifyPlants);
                break;
            case BonusTargets::IMITATE_VOICES:
                $this->applyBonusToField($bonus, $hero->imitateVoices);
                break;

            case BonusTargets::DESCRIPTION:
                // make an array of all the descriptions
                $hero->descriptions[] = $bonus->value;
                break;

            case BonusTargets::SPECIAL_SKILL_HOT_WIRING:
            case BonusTargets::SPECIAL_SKILL_COMPUTER_HACKING:
            case BonusTargets::SPECIAL_ESTIMATE_ELECTRICAL_SYSTEMS:
            case BonusTargets::SPECIAL_BUILDING_SUPER_VEHICLES:
            case BonusTargets::SPECIAL_RECOGNIZE_VEHICLE_QUALITY:
            case BonusTargets::SPECIAL_MAKE_AND_MODIFY_WEAPONS:
            case BonusTargets::SPECIAL_RECOGNIZE_WEAPON_QUALITY:
            case BonusTargets::SPECIAL_RECOGNIZE_MAGIC:
            case BonusTargets::SPECIAL_SENSE_MAGIC:
            case BonusTargets::SPECIAL_MECHANICAL_AND_ELECTRICAL_REPAIR:

            case BonusTargets::SKILL_CATEGORY_COMPUTER:
            case BonusTargets::SKILL_CRYPTOGRAPHY:
            case BonusTargets::SKILL_LASER:
            case BonusTargets::SKILL_OPTIC_SYSTEMS:
            case BonusTargets::SKILL_RADIO_BASIC:
            case BonusTargets::SKILL_RADIO_SCRAMBLER:
            case BonusTargets::SKILL_RADIO_SATELLITE:
            case BonusTargets::SKILL_SURVEILLANCE:
            case BonusTargets::SKILL_TV_VIDEO:
            case BonusTargets::SKILL_COMPUTER_OPERATION:
            case BonusTargets::SKILL_COMPUTER_PROGRAMMING:
            case BonusTargets::SKILL_COOK:
            case BonusTargets::SKILL_DANCE:
            case BonusTargets::SKILL_FISH:
            case BonusTargets::SKILL_SEW:
            case BonusTargets::SKILL_SING:
            case BonusTargets::SKILL_BASIC_ELECTRONICS:
            case BonusTargets::SKILL_ELECTRICAL_ENGINEER:
            case BonusTargets::SKILL_ROBOT_ELECTRONICS:
            case BonusTargets::SKILL_CONCEALMENT:
            case BonusTargets::SKILL_DETECT_AMBUSH:
            case BonusTargets::SKILL_DETECT_CONCEALMENT:
            case BonusTargets::SKILL_DISGUISE:
            case BonusTargets::SKILL_ESCAPE_ARTIST:
            case BonusTargets::SKILL_FORGERY:
            case BonusTargets::SKILL_INTELLIGENCE:
            case BonusTargets::SKILL_IMPERSONATION:
            case BonusTargets::SKILL_INTERROGATION:
            case BonusTargets::SKILL_LAND_NAVIGATION:
            case BonusTargets::SKILL_PALMING:
            case BonusTargets::SKILL_PICK_LOCKS:
            case BonusTargets::SKILL_PICK_POCKETS:
            case BonusTargets::SKILL_SNIPER:
            case BonusTargets::SKILL_TRACKING:
            case BonusTargets::SKILL_WILDERNESS_SURVIVAL:
            case BonusTargets::SKILL_AUTOMOTIVE_MECHANICS:
            case BonusTargets::SKILL_AIRCRAFT_MECHANICS:
            case BonusTargets::SKILL_BASIC_MECHANICS:
            case BonusTargets::SKILL_COMPUTER_REPAIR:
            case BonusTargets::SKILL_LOCKSMITH:
            case BonusTargets::SKILL_ROBOT_MECHANICS:
            case BonusTargets::SKILL_MECHANICAL_ENGINEERING:
            case BonusTargets::SKILL_CRIMINAL_SCIENCE_FORENSICS:
            case BonusTargets::SKILL_FIRST_AID:
            case BonusTargets::SKILL_MEDICAL_DOCTOR:
            case BonusTargets::SKILL_PARAMEDIC:
            case BonusTargets::SKILL_PATHOLOGY:
            case BonusTargets::SKILL_DEMOLITIONS:
            case BonusTargets::SKILL_DEMOLITIONS_DISPOSAL:
            case BonusTargets::SKILL_PILOT_TANK:
            case BonusTargets::SKILL_HAND_TO_HAND_BASIC:
            case BonusTargets::SKILL_HAND_TO_HAND_EXPERT:
            case BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS:
            case BonusTargets::SKILL_HAND_TO_HAND_ASSASSIN:
            case BonusTargets::SKILL_ACROBATICS:
            case BonusTargets::SKILL_ARCHERY:
            case BonusTargets::SKILL_ATHLETICS:
            case BonusTargets::SKILL_BODY_BUILDING:
            case BonusTargets::SKILL_BOXING:
            case BonusTargets::SKILL_CLIMBING:
            case BonusTargets::SKILL_RUNNING:
            case BonusTargets::SKILL_FENCING:
            case BonusTargets::SKILL_SWIMMING:
            case BonusTargets::SKILL_GYMNASTICS:
            case BonusTargets::SKILL_SWIMMING_ADVANCED:
            case BonusTargets::SKILL_PROWL:
            case BonusTargets::SKILL_WRESTLING:
            case BonusTargets::SKILL_PILOT_AUTOMOBILE:
            case BonusTargets::SKILL_PILOT_RACE_CAR:
            case BonusTargets::SKILL_PILOT_MOTORCYCLE:
            case BonusTargets::SKILL_PILOT_TRUCK:
            case BonusTargets::SKILL_PILOT_AIRPLANE_OLD_STYLE:
            case BonusTargets::SKILL_PILOT_BOATS_SAIL:
            case BonusTargets::SKILL_PILOT_BOATS_MOTOR:
            case BonusTargets::SKILL_PILOT_HELICOPTER_BASIC:
            case BonusTargets::SKILL_PILOT_HELICOPTER_COMBAT:
            case BonusTargets::SKILL_PILOT_JET_COMMERCIAL:
            case BonusTargets::SKILL_PILOT_JET_FIGHTER:
            case BonusTargets::SKILL_PILOT_SPACE_SHUTTLE:
            case BonusTargets::SKILL_NAVIGATION:
            case BonusTargets::SKILL_NAVIGATION_SPACE:
            case BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS:
            case BonusTargets::SKILL_WEAPON_SYSTEMS:
            case BonusTargets::SKILL_ASTROPHYSICS:
            case BonusTargets::SKILL_BIOLOGY:
            case BonusTargets::SKILL_BOTANY:
            case BonusTargets::SKILL_CHEMISTRY_BASIC:
            case BonusTargets::SKILL_CHEMISTRY_ANALYTICAL:
            case BonusTargets::SKILL_MATHEMATICS_BASIC:
            case BonusTargets::SKILL_MATHEMATICS_ADVANCED:
            case BonusTargets::SKILL_ART:
            case BonusTargets::SKILL_LANGUAGE:
            case BonusTargets::SKILL_PHOTOGRAPHY:
            case BonusTargets::SKILL_WRITING:
            case BonusTargets::SKILL_WP_BLUNT:
            case BonusTargets::SKILL_WP_CHAIN:
            case BonusTargets::SKILL_WP_KNIFE:
            case BonusTargets::SKILL_WP_SWORD:
            case BonusTargets::SKILL_WP_STAFF:
            case BonusTargets::SKILL_WP_TARGET:
            case BonusTargets::SKILL_WP_PAIRED_WEAPONS:
            case BonusTargets::SKILL_WP_REVOLVER:
            case BonusTargets::SKILL_WP_RIFLE:
            case BonusTargets::SKILL_WP_AUTOMATIC_PISTOL:
            case BonusTargets::SKILL_WP_SUB_MACHINEGUN:
            case BonusTargets::SKILL_WP_AUTOMATIC_RIFLE:
            case BonusTargets::SKILL_WP_HEAVY:
            case BonusTargets::SKILL_WP_ENERGY_PISTOL:
            case BonusTargets::SKILL_WP_ENERGY_RIFLE:
                $this->applyBonusToSkill($bonus, $hero, true);
                break;



            case BonusTargets::SKILL_GROUP_DECEPTION_SLEIGHT_OF_HAND:
                $this->applyBonusToSkills($bonus, $hero, [
                    BonusTargets::SKILL_CONCEALMENT,
                    BonusTargets::SKILL_DISGUISE,
                    BonusTargets::SKILL_ESCAPE_ARTIST,
                    BonusTargets::SKILL_FORGERY,
                    BonusTargets::SKILL_INTELLIGENCE,
                    BonusTargets::SKILL_IMPERSONATION,
                    BonusTargets::SKILL_INTERROGATION,
                    BonusTargets::SKILL_PALMING,
                    BonusTargets::SKILL_PICK_LOCKS,
                    BonusTargets::SKILL_PICK_POCKETS,
                ], true);
                break;
            case BonusTargets::SKILL_GROUP_PHYSICAL:
                $this->applyBonusToSkills($bonus, $hero, [
                    BonusTargets::SKILL_ACROBATICS,
                    BonusTargets::SKILL_ARCHERY,
                    BonusTargets::SKILL_ATHLETICS,
                    BonusTargets::SKILL_BOXING,
                    BonusTargets::SKILL_RUNNING,
                    BonusTargets::SKILL_FENCING,
                    BonusTargets::SKILL_SWIMMING,
                    BonusTargets::SKILL_GYMNASTICS,
                    BonusTargets::SKILL_SWIMMING_ADVANCED,
                    BonusTargets::SKILL_PROWL,
                ], true);
                break;
            case BonusTargets::SKILL_GROUP_DELICATE_TOUCH:
                // delicate light touch: demolitions, pick pocket, pick locks, palming, sewing, escape artist, forgery, first aid, medical doctor, paramedic, climbing, art, writing
                $this->applyBonusToSkills($bonus, $hero, [
                    BonusTargets::SKILL_DEMOLITIONS,
                    BonusTargets::SKILL_PICK_POCKETS,
                    BonusTargets::SKILL_PICK_LOCKS,
                    BonusTargets::SKILL_PALMING,
                    BonusTargets::SKILL_SEW,
                    BonusTargets::SKILL_ESCAPE_ARTIST,
                    BonusTargets::SKILL_FORGERY,
                    BonusTargets::SKILL_FIRST_AID,
                    BonusTargets::SKILL_MEDICAL_DOCTOR,
                    BonusTargets::SKILL_PARAMEDIC,
                    BonusTargets::SKILL_CLIMBING,
                    BonusTargets::SKILL_ART,
                    BonusTargets::SKILL_WRITING,
                ], true);
                break;
            case BonusTargets::SKILL_GROUP_ALL:
                // only adds bonus to skills that have been taken
                $this->applyBonusToSkills($bonus, $hero, BonusTargets::allSkills(false), false);
                break;
            case BonusTargets::SKILL_GROUP_PILOTING:
                $this->applyBonusToSkills($bonus, $hero, array_merge(BonusTargets::pilotBasicSkills(false), BonusTargets::pilotAdvancedSkills(false)), true);
                break;
            case BonusTargets::SKILL_GROUP_PILOTING_RELATED:
                $this->applyBonusToSkills($bonus, $hero, BonusTargets::pilotRelatedSkills(false), true);
                break;
            case BonusTargets::SKILL_GROUP_COMPUTER_ELECTRICAL_MECHANICAL:
                $this->applyBonusToSkills($bonus, $hero, [
                    BonusTargets::SKILL_COMPUTER_REPAIR,
                    BonusTargets::SKILL_COMPUTER_PROGRAMMING,
                    BonusTargets::SKILL_COMPUTER_OPERATION,
                    BonusTargets::SKILL_ELECTRICAL_ENGINEER,
                    BonusTargets::SKILL_MECHANICAL_ENGINEERING,
                    BonusTargets::SKILL_ROBOT_MECHANICS,
                    BonusTargets::SKILL_BASIC_MECHANICS,
                    BonusTargets::SKILL_AIRCRAFT_MECHANICS,
                    BonusTargets::SKILL_AUTOMOTIVE_MECHANICS,
                ], true);
                break;
            case BonusTargets::SKILL_GROUP_AGILITY_DEXTERITY:
                // agility dexterity skills like acrobatics, pick locks, computer operation, etc
                $this->applyBonusToSkills($bonus, $hero, array_merge([
                    BonusTargets::SKILL_ACROBATICS,
                    BonusTargets::SKILL_PICK_LOCKS,
                    BonusTargets::SKILL_PICK_POCKETS,
                    BonusTargets::SKILL_COMPUTER_OPERATION,
                    BonusTargets::SKILL_OPTIC_SYSTEMS,
                    BonusTargets::SKILL_DANCE,
                    BonusTargets::SKILL_BASIC_ELECTRONICS,
                    BonusTargets::SKILL_DISGUISE,
                    BonusTargets::SKILL_FORGERY,
                    BonusTargets::SKILL_PALMING,
                    BonusTargets::SKILL_BASIC_MECHANICS,
                    BonusTargets::SKILL_LOCKSMITH,
                    BonusTargets::SKILL_MEDICAL_DOCTOR,
                    BonusTargets::SKILL_PARAMEDIC,
                    BonusTargets::SKILL_DEMOLITIONS,
                    BonusTargets::SKILL_DEMOLITIONS_DISPOSAL,
                    BonusTargets::SKILL_ARCHERY,
                    BonusTargets::SKILL_CLIMBING,
                    BonusTargets::SKILL_FENCING,
                    BonusTargets::SKILL_PROWL,
                    BonusTargets::SKILL_ART,
                ], BonusTargets::pilotBasicSkills(false)
                    , BonusTargets::pilotAdvancedSkills(false)), true);
                break;

            default:
                var_dump($bonus);
                throw new \Exception('Unknown Bonus Target: ' . $bonus->bonusTarget);
        }
        
        // mark bonus as applied so it doesn't get doubled up
        $bonus->isApplied = true;
    }

    /**
     * apply a set of bonuses to a hero
     *
     * @param Hero $hero the hero
     * @param string[] $bonusTargets which BonusTarget::... constants to search for and apply to the hero
     */
    public function calculateBonusGroup(Hero &$hero, $bonusTargets)
    {
        foreach ([Bonus::BONUS_TYPE_SET, Bonus::BONUS_TYPE_ADD, Bonus::BONUS_TYPE_MINIMUM, Bonus::BONUS_TYPE_MULTIPLY] as $bonusType) {
            foreach ($hero->bonuses as $key => $dontuse) {
                // run through hero's bonuses and find any that are for attributes and sum up the attribute scores
                $bonus = &$hero->bonuses[$key];
                if ($bonus->bonusType === $bonusType && false !== array_search($bonus->bonusTarget, $bonusTargets)) {
                    $this->applyBonus($hero, $bonus);
                }
            }
        }
    }

    /**
     * find all
     *
     * @param Hero $hero the hero on which to total attributes
     */
    public function calculateAttributeTotals(Hero &$hero)
    {
        $this->calculateBonusGroup($hero, [
            BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT,
            BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE,
            BonusTargets::ATTRIBUTE_MENTAL_AFFINITY,
            BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH,
            BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS,
            BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE,
            BonusTargets::ATTRIBUTE_PHYSICAL_BEAUTY,
            BonusTargets::ATTRIBUTE_SPEED,
        ]);
    }

    /**
     * apply bonus to a skill; creates the skill if it doesn't exist
     *
     * @param Bonus $bonus the bonus to apply
     * @param Hero $hero the hero who should get the skill bonus
     * @param bool $includeUnset if true then adds missing skills, if false then only gives bonus if the skill exists
     */
    private function applyBonusToSkill(Bonus $bonus, Hero &$hero, $includeUnset)
    {
        // check if the skill already exists
        $isset = isset($hero->skillTotals[$bonus->bonusTarget]);

        // start at default if doesn't exist and including unset skills
        if (!$isset && $includeUnset) {
            $hero->skillTotals[$bonus->bonusTarget] = 0;
        }

        // add bonus to skill if it already existed or got added
        if ($isset || $includeUnset) {
            $this->applyBonusToField($bonus, $hero->skillTotals[$bonus->bonusTarget]);
        }
    }

    /**
     * apply bonus to a group of skills
     *
     * @param Bonus $bonus the bonus value and type to apply
     * @param Hero $hero the hero to which to give the skill
     * @param String[] $skills the skills to which to apply the bonus
     * @param bool $includeUnset if true then adds missing skills, if false then only gives bonus if the skill exists
     */
    private function applyBonusToSkills(Bonus $bonus, Hero &$hero, $skills, $includeUnset) {
        // save actual target
        $bonusTarget = $bonus->bonusTarget;
        foreach ($skills as $skill) {
            $bonus->bonusTarget = $skill;
            $this->applyBonusToSkill($bonus, $hero, $includeUnset);
        }
        // put target back to what it was
        $bonus->bonusTarget = $bonusTarget;
    }
}
