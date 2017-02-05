<?php
namespace Heroes\enums;

abstract class BonusTargets {
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
    const DODGE = 'Dodge';
    const INITIATIVE = 'Initiative';
    const PARRY = 'Parry';
    const PHYSICAL_DAMAGE = 'Physical Damage';
    const ROLL = 'Roll';
    const SAVE_COMMA_DEATH = 'Save: comma/Death';
    // note that save magic/psionics/toxins is in addition to PE bonus
    const SAVE_MAGIC_PSIONICS_TOXINS = 'Save: Magic/Psionics/Toxins';
    const STRIKE = 'Strike';

    // == OTHER == //
    const MONEY = 'Money';


    // == FLAGS == //
    // can carry and lift double the normal amount
    const FLAG_DOUBLE_CARRY = 'double carry';


    // == NON-NUMERIC BONUSES == //
    // description of some sort of bonus ability/attribute the character receives that has no numeric significance for the character
    const DESCRIPTION = 'Description';


    // == SKILL GROUPS == //
    // deception/sleight-of-hand: concealment, disguise, escape artist, forgery, intelligence, impersonation, interrogation, palming, pick locks, pick pockets
    const SKILL_GROUP_DECEPTION_SLEIGHT_OF_HAND = 'group: deception/sleight of hand';
    // physical skills: skills requiring dexterity and prowess: acrobatics, archery, athletics, boxing, running, fencing, swimming, gymnastics, swimming, prowl
    const SKILL_GROUP_PHYSICAL = 'group: physical';
    // delicate light touch: demolitions, pick pocket, pick locks, palming, sewing, escape artist, forgery, first aid, medical doctor, paramedic, climbing, art, writing
    const SKILL_GROUP_DELICATE_TOUCH = 'group: delicate, light touch';
    // all skills
    const SKILL_GROUP_ALL = "group: all";


    // == SKILLS == //
    // - COMMUNICATIONS - //
    const SKILL_CRYPTOGRAPHY = 'Cryptography';
    const SKILL_LASER = 'Laser';
    const SKILL_OPTIC_SYSTEMS = 'Optic systems';
    const SKILL_RADIO_BASIC = 'Radio: basic';
    const SKILL_RADIO_SCRAMBLER = 'Radio: scrambler';
    const SKILL_RADIO_SATELLITE = 'Radio: satellite';
    const SKILL_SURVEILLANCE = 'Surveillance';
    const SKILL_TV_VIDEO = 'TV / Video';

    // - COMPUTER - //
    const SKILL_COMPUTER_OPERATION = 'Computer operation';

    // - DOMESTIC - //
    const SKILL_COOK = 'Cook';
    const SKILL_DANCE = 'Dance';
    const SKILL_FISH = 'Fish';
    const SKILL_SEW = 'Sew';
    const SKILL_SING = 'Sing';

    // - ELECTRICAL - //
    const SKILL_BASIC_ELECTRONICS = 'Basic electronics';
    const SKILL_ELECTRICAL_ENGINEER = 'Electrical engineer';
    const SKILL_ROBOT_ELECTRONICS = 'Robot electronics';

    // - ESPIONAGE / MILITARY - //
    const SKILL_CONCEALMENT = 'Concealment';
    const SKILL_DETECT_AMBUSH = 'Detect ambush';
    const SKILL_DETECT_CONCEALMENT = 'Detect concealment';
    const SKILL_DISGUISE = 'Disguise';
    const SKILL_ESCAPE_ARTIST = 'Escape artist';
    const SKILL_FORGERY = 'Forgery';
    const SKILL_INTELLIGENCE = 'Intelligence';
    const SKILL_IMPERSONATION = 'Impersonation';
    const SKILL_INTERROGATION = 'Interrogation';
    const SKILL_LAND_NAVIGATION = 'Land navigation';
    const SKILL_PALMING = 'Palming';
    const SKILL_PICK_LOCKS = 'Pick locks';
    const SKILL_PICK_POCKETS = 'Pick pockets';
    const SKILL_SNIPER = 'Sniper';
    const SKILL_TRACKING = 'Tracking';
    const SKILL_WILDERNESS_SURVIVAL = 'Wilderness survival';

    // - MECHANICAL - //
    const SKILL_AUTOMOTIVE_MECHANICS = 'Automotive mechanics';
    const SKILL_AIRCRAFT_MECHANICS = 'Aircraft mechanics';
    const SKILL_BASIC_MECHANICS = 'Basic mechanics';
    const SKILL_COMPUTER_REPAIR = 'Computer repair';
    const SKILL_LOCKSMITH = 'Locksmith';
    const SKILL_ROBOT_MECHANICS = 'Robot mechanics';
    const SKILL_MECHANICAL_ENGINEERING = 'Mechanical engineering';

    // - MEDICAL - //
    const SKILL_CRIMINAL_SCIENCE_FORENSICS = 'Criminal science/forensics';
    const SKILL_FIRST_AID = 'First aid';
    const SKILL_MEDICAL_DOCTOR = 'Medical doctor';
    const SKILL_PARAMEDIC = 'Paramedic';
    const SKILL_PATHOLOGY = 'Pathology';

    // - MILITARY - //
    const SKILL_DEMOLITIONS = 'Demolitions';
    const SKILL_DEMOLITIONS_DISPOSAL = 'Demolitions disposal';
    const SKILL_PILOT_TANK = 'Pilot tank';

    // - PHYSICAL - //
    const SKILL_HAND_TO_HAND_BASIC = 'Hand to hand - basic';
    const SKILL_HAND_TO_HAND_EXPERT = 'Hand to hand - expert';
    const SKILL_HAND_TO_HAND_MARTIAL_ARTS = 'Hand to hand - martial arts';
    const SKILL_ACROBATICS = 'Acrobatics';
    const SKILL_ARCHERY = 'Archery';
    const SKILL_ATHLETICS = 'Athletics (general)';
    const SKILL_BODY_BUILDING = 'Body building';
    const SKILL_BOXING = 'Boxing';
    const SKILL_CLIMBING = 'Climbing';
    const SKILL_RUNNING = 'Running';
    const SKILL_FENCING = 'Fencing';
    const SKILL_SWIMMING = 'Swimming';
    const SKILL_GYMNASTICS = 'Gymnastics';
    const SKILL_SWIMMING_ADVANCED = 'Swimming advanced';
    const SKILL_PROWL = 'Prowl';
    const SKILL_WRESTLING = 'Wrestling';

    // - Pilot basic (ground, air, and water) (secondary skills) - //
    const SKILL_PILOT_AUTOMOBILE = 'Automobile';
    const SKILL_PILOT_RACE_CAR = 'Race car';
    const SKILL_PILOT_MOTORCYCLE = 'Motorcycle';
    const SKILL_PILOT_TRUCK = 'Truck';
    const SKILL_PILOT_AIRPLANE_OLD_STYLE = 'Airplane - old style';
    const SKILL_PILOT_BOATS_SAIL = 'Boats: sail';
    const SKILL_PILOT_BOATS_MOTOR = 'Boats: motor';
    const SKILL_PILOT_PILOT_ADVANCED = 'Pilot, advanced';
    const SKILL_PILOT_HELICOPTER_BASIC = 'Helicopter, basic';
    const SKILL_PILOT_HELICOPTER_COMBAT = 'Helicopter, combat';
    const SKILL_PILOT_JET_COMMERCIAL = 'Jet commercial';
    const SKILL_PILOT_JET_FIGHTER = 'Jet fighter';
    const SKILL_PILOT_SPACE_SHUTTLE = 'Space shuttle';

    // - Pilot related skills - //
    const SKILL_NAVIGATION = 'Navigation (air, land, water)';
    const SKILL_NAVIGATION_SPACE = 'Navigation: space';
    const SKILL_READ_SENSORY_INSTRUMENTS = 'Read_sensory instruments';
    const SKILL_WEAPON_SYSTEMS = 'Weapon systems (missiles, lasers, etc.)';

    // - SCIENCE - //
    const SKILL_ASTROPHYSICS = 'Astrophysics';
    const SKILL_BIOLOGY = 'Biology';
    const SKILL_BOTANY = 'Botany';
    const SKILL_CHEMISTRY_BASIC = 'Chemistry: basic';
    const SKILL_CHEMISTRY_ANALYTICAL = 'Chemistry: analytical';
    const SKILL_MATHEMATICS_BASIC = 'Mathematics: basic';
    const SKILL_MATHEMATICS_ADVANCED = 'Mathematics: advanced';

    // - TECHNICAL - //
    const SKILL_ART = 'Art';
    const SKILL_LANGUAGE = 'Language';
    const SKILL_PHOTOGRAPHY = 'Photography';
    const SKILL_WRITING = 'Writing';

    // - WEAPON PROFICIENCIES - //
    // -- Ancient Weapons -- //
    const SKILL_WP_BLUNT = 'WP blunt';
    const SKILL_WP_CHAIN = 'WP chain';
    const SKILL_WP_KNIFE = 'WP knife';
    const SKILL_WP_SWORD = 'WP sword';
    const SKILL_WP_STAFF = 'WP staff';
    const SKILL_WP_TARGET = 'WP target';
    const SKILL_WP_PAIRED_WEAPONS = 'WP paired weapons';
    // -- Modern Weapons -- //
    const SKILL_WP_REVOLVER = 'WP revolver';
    const SKILL_WP_RIFLE = 'WP rifle';
    const SKILL_WP_AUTOMATIC_PISTOL = 'WP automatic pistol';
    const SKILL_WP_SUB_MACHINEGUN = 'WP sub machinegun';
    const SKILL_WP_AUTOMATIC_RIFLE = 'WP semi & fully automatic rifle';
    const SKILL_WP_HEAVY = 'WP heavy';
    // -- Energy Weapons -- //
    const SKILL_WP_ENERGY_PISTOL = 'WP energy pistol';
    const SKILL_WP_ENERGY_RIFLE = 'WP energy rifle';
}
