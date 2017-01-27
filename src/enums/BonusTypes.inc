<?php
namespace Heroes\enums;

abstract class BonusTypes {
    // attributes
    const INTELLIGENCE_QUOTIENT = 'IQ';
    const MENTAL_ENDURANCE = 'Mental Endurance';
    const MENTAL_AFFINITY = 'Mental Affinity';
    const PHYSICAL_STRENGTH = 'Physical Strength';
    const PHYSICAL_PROWESS = 'Physical Prowess';
    const PHYSICAL_ENDURANCE = 'Physical Endurance';
    const PHYSICAL_BEAUTY = 'Physical Beauty';
    const SPEED = 'Speed';

    // health
    const HIT_POINTS = 'Hit Points';
    const SDC = 'SDC';

    // combat
    const ATTACKS_PER_MELEE = 'Attacks per melee';
    const PARRY = 'Parry';
    const ROLL = 'Roll';
    const SKILL = 'Skill';
}
