<?php
namespace Heroes\enums;

abstract class BonusTypes {
    // == ATTRIBUTES == //
    const ATTRIBUTE_INTELLIGENCE_QUOTIENT = 'IQ';
    const ATTRIBUTE_MENTAL_ENDURANCE = 'Mental Endurance';
    const ATTRIBUTE_MENTAL_AFFINITY = 'Mental Affinity';
    const ATTRIBUTE_PHYSICAL_STRENGTH = 'Physical Strength';
    const ATTRIBUTE_PHYSICAL_PROWESS = 'Physical Prowess';
    const ATTRIBUTE_PHYSICAL_ENDURANCE = 'Physical Endurance';
    const ATTRIBUTE_PHYSICAL_BEAUTY = 'Physical Beauty';
    const ATTRIBUTE_SPEED = 'Speed';

    // == HEALTH == //
    const HIT_POINTS = 'Hit Points';
    const SDC = 'SDC';

    // == COMBAT == //
    const ATTACKS_PER_MELEE = 'Attacks per melee';
    const PARRY = 'Parry';
    const ROLL = 'Roll';
    const DODGE = 'Dodge';

    // == OTHER == //
    const MONEY = 'Money';



    // == SKILLS == //
    const SKILL_CLIMBING = 'Climbing';
    const SKILL_CONCEALMENT = 'Concealment';
    const SKILL_ELECTRICAL_REPAIR = 'Electrical Repair';
    const SKILL_ESCAPE_ARTIST = 'Escape Artist';
    const SKILL_LANGUAGE = 'Language';
    const SKILL_MECHANICAL_REPAIR = 'Mechanical Repair';
    const SKILL_PALMING = 'Palming';
    const SKILL_PICK_LOCKS = 'Pick Locks';
    const SKILL_PICK_POCKET = 'Pick Pocket';
    const SKILL_PROWL = 'Prowl';
    const SKILL_SWIMMING = 'Swimming';
}
