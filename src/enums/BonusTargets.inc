<?php
namespace Heroes\enums;

abstract class BonusTargets
{
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
    const WEIGHT = 'Weight';

    // == COMBAT == //
    const ATTACKS_PER_MELEE = 'Attacks per melee';
    const DAMAGE = 'Damage';
    const DODGE = 'Dodge';
    const INITIATIVE = 'Initiative';
    const NATURAL_ARMOR_RATING = "Natural Armor Rating";
    const PARRY = 'Parry';
    const PHYSICAL_DAMAGE = 'Physical Damage';
    const PULL_PUNCH = "Pull Punch";
    // roll with fall/impact
    const ROLL = 'Roll';
    const SAVE_COMMA_DEATH = 'Save: comma/Death';

    // save against gases of all types
    const SAVE_GASES = 'Save: gases';
    // note that save magic/psionics/toxins is in addition to PE bonus
// TODO : break out psionics and toxins and the combo saves so that they target just one type
    const SAVE_MAGIC_PSIONICS_TOXINS = 'Save: Magic/Psionics/Toxins';
    const SAVE_POSITION_TOXINS_GASES = 'Save: Position/Toxins/Gases';
    const SAVE_TOXINS = 'Save: Toxins';
    const SAVE_CHEMICALS = 'Save: Chemicals';
    const SAVE_MAGIC = 'Save: Magic';
    const SAVE_PSIONICS = 'Save: Psionics';
    const SAVE_PSIONIC_ATTACK_INSANITY = 'Save: Psionic Attack/Insanity';
    const SAVE_PSIONIC_MIND_CONTROL = 'Save: Psionic Mind Control';
    const SAVE_POSSESSION = 'Save: Possession';
    const SAVE_CONTROL_OTHERS = 'Save: Control Others';
    const SAVE_MIND_ALTERING_EFFECTS = 'Save: Mind Altering Effects';
    const SAVE_ILLUSIONS = 'Save: Illusions';

    const TRUST_INTIMIDATE = 'Trust/Intimidate';
    const STRIKE = 'Strike';
    const SAVE_MAGIC_SPELLS_ENCHANTMENTS = 'Save: Magic/Spells/Enchantments';

    // == OTHER == //
    const MONEY = 'Money';
    const CHARM_IMPRESS = 'Charm/Impress';

    // one-off categories; if not set then don't show
    const BALANCE_WALK_TIGHTROPE = 'Balance/Walk Tightrope';
    const MAINTAIN_GRIP_HOLD_FOOTING = 'Maintain grip, hold, or footing';


    // == FLAGS == //
    // can carry and lift double the normal amount
    const FLAG_DOUBLE_CARRY = 'double carry';


    // == NON-NUMERIC BONUSES == //
    // description of some sort of bonus ability/attribute the character receives that has no numeric significance for the character
    const DESCRIPTION = 'Description';

    // == SPECIAL SKILLS == //
    // these are skills from classes and other things that are not in the normal education selection
    const SPECIAL_SKILL_HOT_WIRING = 'How Wiring';
    const SPECIAL_SKILL_COMPUTER_HACKING = 'Computer Hacking';
    const SPECIAL_ESTIMATE_ELECTRICAL_SYSTEMS = 'Estimate Electrical Systems';
    const SPECIAL_BUILDING_SUPER_VEHICLES = 'Building Super Vehicles';
    const SPECIAL_RECOGNIZE_VEHICLE_QUALITY = 'Recognize Vehicle Quality';
    const SPECIAL_MAKE_AND_MODIFY_WEAPONS = 'Make and Modify Weapons';
    const SPECIAL_RECOGNIZE_WEAPON_QUALITY = 'Recognize Weapon Quality';
    const SPECIAL_RECOGNIZE_MAGIC = 'Recognize Magic';
    const SPECIAL_SENSE_MAGIC = 'Sense Evil';
    const SPECIAL_MECHANICAL_AND_ELECTRICAL_REPAIR = 'Mechanical and Electrical Repair';


    // == SKILL GROUPS == //
    // deception/sleight-of-hand: concealment, disguise, escape artist, forgery, intelligence, impersonation, interrogation, palming, pick locks, pick pockets
    const SKILL_GROUP_DECEPTION_SLEIGHT_OF_HAND = 'group: deception/sleight of hand';
    // physical skills: skills requiring dexterity and prowess: acrobatics, archery, athletics, boxing, running, fencing, swimming, gymnastics, swimming, prowl
    const SKILL_GROUP_PHYSICAL = 'group: physical';
    // delicate light touch: demolitions, pick pocket, pick locks, palming, sewing, escape artist, forgery, first aid, medical doctor, paramedic, climbing, art, writing
    const SKILL_GROUP_DELICATE_TOUCH = 'group: delicate, light touch';
    // all skills
    const SKILL_GROUP_ALL = "group: all";
    const SKILL_GROUP_PILOTING = 'group: all piloting';
    const SKILL_GROUP_PILOTING_RELATED = 'group: all piloting related';
    const SKILL_GROUP_COMPUTER_ELECTRICAL_MECHANICAL = 'group: computer, electrical, and mechanical';
    // agility dexterity skills like acrobatics, pick locks, computer operation, etc
    const SKILL_GROUP_AGILITY_DEXTERITY = 'group: agility or dexterity';

    const UNDERSTAND_OPERATE_ALIEN_MACHINES = 'Understand and operate unknown or alien machines';
    const RECOGNIZE_IDENTIFY_PLANTS = 'Recognize and Identify Plants';
    const IMITATE_VOICES = 'Imitate Voices';

    // == SECONDARY SKILL CATEGORIES == //
    const SKILL_CATEGORY_COMPUTER = 'Computer';

    // == SKILLS == //
    // - COMMUNICATIONS - //
    const SKILL_CRYPTOGRAPHY = 'Cryptography';
    const SKILL_LASER = 'Laser';
    const SKILL_OPTIC_SYSTEMS = 'Optic Systems';
    const SKILL_RADIO_BASIC = 'Radio: Basic';
    const SKILL_RADIO_SCRAMBLER = 'Radio: Scrambler';
    const SKILL_RADIO_SATELLITE = 'Radio: Satellite';
    const SKILL_SURVEILLANCE = 'Surveillance Systems';
    const SKILL_TV_VIDEO = 'TV / Video';

    // - COMPUTER - //
    const SKILL_COMPUTER_OPERATION = 'Computer Operation';
    const SKILL_COMPUTER_PROGRAMMING = 'Computer Programming';

    // - DOMESTIC - //
    const SKILL_COOK = 'Cook';
    const SKILL_DANCE = 'Dance';
    const SKILL_FISH = 'Fish';
    const SKILL_SEW = 'Sew';
    const SKILL_SING = 'Sing';

    // - ELECTRICAL - //
    const SKILL_BASIC_ELECTRONICS = 'Basic Electronics';
    const SKILL_ELECTRICAL_ENGINEER = 'Electrical Engineer';
    const SKILL_ROBOT_ELECTRONICS = 'Robot Electronics';

    // - ESPIONAGE / MILITARY - //
    const SKILL_CONCEALMENT = 'Concealment';
    const SKILL_DETECT_AMBUSH = 'Detect Ambush';
    const SKILL_DETECT_CONCEALMENT = 'Detect Concealment';
    const SKILL_DISGUISE = 'Disguise';
    const SKILL_ESCAPE_ARTIST = 'Escape Artist';
    const SKILL_FORGERY = 'Forgery';
    const SKILL_INTELLIGENCE = 'Intelligence';
    const SKILL_IMPERSONATION = 'Impersonation';
    const SKILL_INTERROGATION = 'Interrogation';
    const SKILL_LAND_NAVIGATION = 'Land Navigation';
    const SKILL_PALMING = 'Palming';
    const SKILL_PICK_LOCKS = 'Pick Locks';
    const SKILL_PICK_POCKETS = 'Pick Pockets';
    const SKILL_SNIPER = 'Sniper';
    const SKILL_TRACKING = 'Tracking';
    const SKILL_WILDERNESS_SURVIVAL = 'Wilderness Survival';

    // - MECHANICAL - //
    const SKILL_AUTOMOTIVE_MECHANICS = 'Automotive Mechanics';
    const SKILL_AIRCRAFT_MECHANICS = 'Aircraft Mechanics';
    const SKILL_BASIC_MECHANICS = 'Basic Mechanics';
    const SKILL_COMPUTER_REPAIR = 'Computer Repair';
    const SKILL_LOCKSMITH = 'Locksmith';
    const SKILL_ROBOT_MECHANICS = 'Robot Mechanics';
    const SKILL_MECHANICAL_ENGINEERING = 'Mechanical Engineering';

    // - MEDICAL - //
    const SKILL_CRIMINAL_SCIENCE_FORENSICS = 'Criminal Science/Forensics';
    const SKILL_FIRST_AID = 'First Aid';
    const SKILL_MEDICAL_DOCTOR = 'Medical Doctor';
    const SKILL_PARAMEDIC = 'Paramedic';
    const SKILL_PATHOLOGY = 'Pathology';

    // - MILITARY - //
    const SKILL_DEMOLITIONS = 'Demolitions';
    const SKILL_DEMOLITIONS_DISPOSAL = 'Demolitions Disposal';
    const SKILL_PILOT_TANK = 'Pilot Tank';

    // - PHYSICAL - //
    const SKILL_HAND_TO_HAND_BASIC = 'Hand to Hand - Basic';
    const SKILL_HAND_TO_HAND_EXPERT = 'Hand to Hand - Expert';
    const SKILL_HAND_TO_HAND_MARTIAL_ARTS = 'Hand to Hand - Martial Arts';
    const SKILL_ACROBATICS = 'Acrobatics';
    const SKILL_ARCHERY = 'Archery';
    const SKILL_ATHLETICS = 'Athletics (general)';
    const SKILL_BODY_BUILDING = 'Body Building';
    const SKILL_BOXING = 'Boxing';
    const SKILL_CLIMBING = 'Climbing';
    const SKILL_RUNNING = 'Running';
    const SKILL_FENCING = 'Fencing';
    const SKILL_SWIMMING = 'Swimming';
    const SKILL_GYMNASTICS = 'Gymnastics';
    const SKILL_SWIMMING_ADVANCED = 'Swimming Advanced';
    const SKILL_PROWL = 'Prowl';
    const SKILL_WRESTLING = 'Wrestling';

    // - Pilot basic (ground, air, and water) (secondary skills) - //
    const SKILL_PILOT_AUTOMOBILE = 'Automobile';
    const SKILL_PILOT_RACE_CAR = 'Race Car';
    const SKILL_PILOT_MOTORCYCLE = 'Motorcycle';
    const SKILL_PILOT_TRUCK = 'Truck';
    const SKILL_PILOT_AIRPLANE_OLD_STYLE = 'Airplane - old style';
    const SKILL_PILOT_BOATS_SAIL = 'Boats: Sail';
    const SKILL_PILOT_BOATS_MOTOR = 'Boats: Motor';
    const SKILL_PILOT_PILOT_ADVANCED = 'Pilot: Advanced';
    const SKILL_PILOT_HELICOPTER_BASIC = 'Helicopter: Basic';
    const SKILL_PILOT_HELICOPTER_COMBAT = 'Helicopter: Combat';
    const SKILL_PILOT_JET_COMMERCIAL = 'Jet Commercial';
    const SKILL_PILOT_JET_FIGHTER = 'Jet Fighter';
    const SKILL_PILOT_SPACE_SHUTTLE = 'Space Shuttle';

    // - Pilot related skills - //
    const SKILL_NAVIGATION = 'Navigation (air, land, water)';
    const SKILL_NAVIGATION_SPACE = 'Navigation: Space';
    const SKILL_READ_SENSORY_INSTRUMENTS = 'Read Sensory Instruments';
    const SKILL_WEAPON_SYSTEMS = 'Weapon Systems (missiles, lasers, etc.)';

    // - SCIENCE - //
    const SKILL_ASTROPHYSICS = 'Astrophysics';
    const SKILL_BIOLOGY = 'Biology';
    const SKILL_BOTANY = 'Botany';
    const SKILL_CHEMISTRY_BASIC = 'Chemistry: Basic';
    const SKILL_CHEMISTRY_ANALYTICAL = 'Chemistry: Analytical';
    const SKILL_MATHEMATICS_BASIC = 'Mathematics: Basic';
    const SKILL_MATHEMATICS_ADVANCED = 'Mathematics: Advanced';

    // - TECHNICAL - //
    const SKILL_ART = 'Art';
    const SKILL_LANGUAGE = 'Language';
    const SKILL_PHOTOGRAPHY = 'Photography';
    const SKILL_WRITING = 'Writing';

    // - WEAPON PROFICIENCIES - //
    // -- Ancient Weapons -- //
    const SKILL_WP_BLUNT = 'WP: Blunt';
    const SKILL_WP_CHAIN = 'WP: Chain';
    const SKILL_WP_KNIFE = 'WP: Knife';
    const SKILL_WP_SWORD = 'WP: Sword';
    const SKILL_WP_STAFF = 'WP: Staff';
    const SKILL_WP_TARGET = 'WP: Target';
    const SKILL_WP_PAIRED_WEAPONS = 'WP: Paired Weapons';
    // -- Modern Weapons -- //
    const SKILL_WP_REVOLVER = 'WP: Revolver';
    const SKILL_WP_RIFLE = 'WP: Rifle';
    const SKILL_WP_AUTOMATIC_PISTOL = 'WP: Automatic Pistol';
    const SKILL_WP_SUB_MACHINEGUN = 'WP: Sub Machinegun';
    const SKILL_WP_AUTOMATIC_RIFLE = 'WP: Semi & Fully Automatic Rifle';
    const SKILL_WP_HEAVY = 'WP: Heavy';
    // -- Energy Weapons -- //
    const SKILL_WP_ENERGY_PISTOL = 'WP: Energy Pistol';
    const SKILL_WP_ENERGY_RIFLE = 'WP: Energy Rifle';

    public static function communicationSkills($justSecondary)
    {
        return $justSecondary ? []
        : [
            BonusTargets::SKILL_CRYPTOGRAPHY,
            BonusTargets::SKILL_LASER,
            BonusTargets::SKILL_OPTIC_SYSTEMS,
            BonusTargets::SKILL_RADIO_BASIC,
            BonusTargets::SKILL_RADIO_SCRAMBLER,
            BonusTargets::SKILL_RADIO_SATELLITE,
            BonusTargets::SKILL_SURVEILLANCE,
            BonusTargets::SKILL_TV_VIDEO,
        ];
    }

    public static function computerSkills($justSecondary)
    {
        return $justSecondary ? [
            BonusTargets::SKILL_COMPUTER_OPERATION,
        ] : [
            BonusTargets::SKILL_COMPUTER_OPERATION,
            BonusTargets::SKILL_COMPUTER_PROGRAMMING,
        ];
    }

    public static function domesticSkills($justSecondary)
    {
        return [
            BonusTargets::SKILL_COOK,
            BonusTargets::SKILL_DANCE,
            BonusTargets::SKILL_FISH,
            BonusTargets::SKILL_SEW,
            BonusTargets::SKILL_SING,
        ];
    }

    public static function electricalSkills($justSecondary)
    {
        return $justSecondary ? [
            BonusTargets::SKILL_BASIC_ELECTRONICS,
        ] : [
            BonusTargets::SKILL_BASIC_ELECTRONICS,
            BonusTargets::SKILL_ELECTRICAL_ENGINEER,
            BonusTargets::SKILL_ROBOT_ELECTRONICS,
        ];
    }

    public static function espionageSkills($justSecondary)
    {
        return $justSecondary ? [
            BonusTargets::SKILL_ESCAPE_ARTIST,
            BonusTargets::SKILL_FORGERY,
            BonusTargets::SKILL_LAND_NAVIGATION,
            BonusTargets::SKILL_PICK_LOCKS,
            BonusTargets::SKILL_PICK_POCKETS,
            BonusTargets::SKILL_WILDERNESS_SURVIVAL,
        ] : [
            BonusTargets::SKILL_ESCAPE_ARTIST,
            BonusTargets::SKILL_FORGERY,
            BonusTargets::SKILL_LAND_NAVIGATION,
            BonusTargets::SKILL_PICK_LOCKS,
            BonusTargets::SKILL_PICK_POCKETS,
            BonusTargets::SKILL_WILDERNESS_SURVIVAL,
            BonusTargets::SKILL_CONCEALMENT,
            BonusTargets::SKILL_DETECT_AMBUSH,
            BonusTargets::SKILL_DETECT_CONCEALMENT,
            BonusTargets::SKILL_DISGUISE,
            BonusTargets::SKILL_INTELLIGENCE,
            BonusTargets::SKILL_IMPERSONATION,
            BonusTargets::SKILL_INTERROGATION,
            BonusTargets::SKILL_PALMING,
            BonusTargets::SKILL_SNIPER,
            BonusTargets::SKILL_TRACKING,
        ];
    }

    public static function mechanicalSkills($justSecondary)
    {
        return $justSecondary ? [
            BonusTargets::SKILL_AUTOMOTIVE_MECHANICS,
            BonusTargets::SKILL_BASIC_MECHANICS,
        ] : [
            BonusTargets::SKILL_AUTOMOTIVE_MECHANICS,
            BonusTargets::SKILL_AIRCRAFT_MECHANICS,
            BonusTargets::SKILL_BASIC_MECHANICS,
            BonusTargets::SKILL_COMPUTER_REPAIR,
            BonusTargets::SKILL_LOCKSMITH,
            BonusTargets::SKILL_ROBOT_MECHANICS,
            BonusTargets::SKILL_MECHANICAL_ENGINEERING,
        ];
    }

    public static function medicalSkills($justSecondary)
    {
        return $justSecondary ? [
            BonusTargets::SKILL_FIRST_AID,
        ] : [
            BonusTargets::SKILL_CRIMINAL_SCIENCE_FORENSICS,
            BonusTargets::SKILL_FIRST_AID,
            BonusTargets::SKILL_MEDICAL_DOCTOR,
            BonusTargets::SKILL_PARAMEDIC,
            BonusTargets::SKILL_PATHOLOGY,
        ];
    }

    public static function militarySkills($justSecondary)
    {
        return $justSecondary ? [
        ] : [
            BonusTargets::SKILL_DEMOLITIONS,
            BonusTargets::SKILL_DEMOLITIONS_DISPOSAL,
            BonusTargets::SKILL_PILOT_TANK,
        ];

    }

    public static function handToHandSkills($justSecondary) {
        return $justSecondary ? [
            BonusTargets::SKILL_HAND_TO_HAND_BASIC,
            BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS,
        ] : [
            BonusTargets::SKILL_HAND_TO_HAND_BASIC,
            BonusTargets::SKILL_HAND_TO_HAND_EXPERT,
            BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS,
        ];
    }

    public static function physicalSkills($justSecondary)
    {
        return array_merge(BonusTargets::handToHandSkills($justSecondary), $justSecondary ? [
            BonusTargets::SKILL_ATHLETICS,
            BonusTargets::SKILL_BODY_BUILDING,
            BonusTargets::SKILL_CLIMBING,
            BonusTargets::SKILL_PROWL,
            BonusTargets::SKILL_RUNNING,
            BonusTargets::SKILL_SWIMMING,
        ] : [
            BonusTargets::SKILL_ACROBATICS,
            BonusTargets::SKILL_ARCHERY,
            BonusTargets::SKILL_ATHLETICS,
            BonusTargets::SKILL_BODY_BUILDING,
            BonusTargets::SKILL_BOXING,
            BonusTargets::SKILL_CLIMBING,
            BonusTargets::SKILL_FENCING,
            BonusTargets::SKILL_GYMNASTICS,
            BonusTargets::SKILL_PROWL,
            BonusTargets::SKILL_RUNNING,
            BonusTargets::SKILL_SWIMMING,
            BonusTargets::SKILL_SWIMMING_ADVANCED,
            BonusTargets::SKILL_WRESTLING,
        ]);
    }

    public static function pilotBasicSkills($justSecondary)
    {
        return $justSecondary ? [
            BonusTargets::SKILL_PILOT_AUTOMOBILE,
            BonusTargets::SKILL_PILOT_RACE_CAR,
            BonusTargets::SKILL_PILOT_TRUCK,
            BonusTargets::SKILL_PILOT_MOTORCYCLE,
            BonusTargets::SKILL_PILOT_AIRPLANE_OLD_STYLE,
            BonusTargets::SKILL_PILOT_BOATS_SAIL,
            BonusTargets::SKILL_PILOT_BOATS_MOTOR,
            BonusTargets::SKILL_PILOT_HELICOPTER_BASIC,
        ] : [
            BonusTargets::SKILL_PILOT_AUTOMOBILE,
            BonusTargets::SKILL_PILOT_RACE_CAR,
            BonusTargets::SKILL_PILOT_MOTORCYCLE,
            BonusTargets::SKILL_PILOT_TRUCK,
            BonusTargets::SKILL_PILOT_AIRPLANE_OLD_STYLE,
            BonusTargets::SKILL_PILOT_BOATS_SAIL,
            BonusTargets::SKILL_PILOT_BOATS_MOTOR,
            BonusTargets::SKILL_PILOT_PILOT_ADVANCED,
            BonusTargets::SKILL_PILOT_HELICOPTER_BASIC,
            BonusTargets::SKILL_PILOT_HELICOPTER_COMBAT,
            BonusTargets::SKILL_PILOT_JET_COMMERCIAL,
            BonusTargets::SKILL_PILOT_JET_FIGHTER,
            BonusTargets::SKILL_PILOT_SPACE_SHUTTLE,
        ];
    }

    public static function pilotRelatedSkills($justSecondary)
    {
        return $justSecondary ? [
            BonusTargets::SKILL_NAVIGATION,
            BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS,
        ] : [
            BonusTargets::SKILL_NAVIGATION,
            BonusTargets::SKILL_NAVIGATION_SPACE,
            BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS,
            BonusTargets::SKILL_WEAPON_SYSTEMS,
        ];
    }

    public static function scienceSkills($justSecondary)
    {
        return $justSecondary ? [
            BonusTargets::SKILL_MATHEMATICS_ADVANCED,
        ] : [
            BonusTargets::SKILL_ASTROPHYSICS,
            BonusTargets::SKILL_BIOLOGY,
            BonusTargets::SKILL_BOTANY,
            BonusTargets::SKILL_CHEMISTRY_BASIC,
            BonusTargets::SKILL_CHEMISTRY_ANALYTICAL,
            BonusTargets::SKILL_MATHEMATICS_BASIC,
            BonusTargets::SKILL_MATHEMATICS_ADVANCED,
    ];
    }

    public static function technicalSkills($justSecondary)
    {
        return [
            BonusTargets::SKILL_ART,
            BonusTargets::SKILL_LANGUAGE,
            BonusTargets::SKILL_PHOTOGRAPHY,
            BonusTargets::SKILL_WRITING,
        ];
    }


    public static function wpAncientWeaponsSkills($justSecondary)
    {
        return $justSecondary ? [
            BonusTargets::SKILL_WP_BLUNT,
            BonusTargets::SKILL_WP_CHAIN,
            BonusTargets::SKILL_WP_KNIFE,
        ] : [
            BonusTargets::SKILL_WP_BLUNT,
            BonusTargets::SKILL_WP_CHAIN,
            BonusTargets::SKILL_WP_KNIFE,
            BonusTargets::SKILL_WP_SWORD,
            BonusTargets::SKILL_WP_STAFF,
            BonusTargets::SKILL_WP_TARGET,
            BonusTargets::SKILL_WP_PAIRED_WEAPONS,
        ];
    }


    public static function wpModernWeaponsSkills($justSecondary)
    {
        return $justSecondary ? [
            BonusTargets::SKILL_WP_REVOLVER,
            BonusTargets::SKILL_WP_AUTOMATIC_PISTOL,
            BonusTargets::SKILL_WP_RIFLE,
            BonusTargets::SKILL_WP_SUB_MACHINEGUN,
        ] : [
            BonusTargets::SKILL_WP_REVOLVER,
            BonusTargets::SKILL_WP_RIFLE,
            BonusTargets::SKILL_WP_AUTOMATIC_PISTOL,
            BonusTargets::SKILL_WP_SUB_MACHINEGUN,
            BonusTargets::SKILL_WP_AUTOMATIC_RIFLE,
            BonusTargets::SKILL_WP_HEAVY,
        ];
    }

    // -- Modern Weapons -- //

    public static function wpEnergyWeaponsSkills($justSecondary)
    {
        return $justSecondary ? [
        ] : [
            BonusTargets::SKILL_WP_ENERGY_PISTOL,
            BonusTargets::SKILL_WP_ENERGY_RIFLE,
        ];
    }

    public static function weaponProficienciesSkills($justSecondary)
    {
        return array_merge(BonusTargets::wpAncientWeaponsSkills($justSecondary), BonusTargets::wpEnergyWeaponsSkills($justSecondary), BonusTargets::wpModernWeaponsSkills($justSecondary));
    }

    public static function allSkills($justSecondary)
    {
        return array_merge(
            BonusTargets::communicationSkills($justSecondary),
            BonusTargets::computerSkills($justSecondary),
            BonusTargets::domesticSkills($justSecondary),
            BonusTargets::electricalSkills($justSecondary),
            BonusTargets::espionageSkills($justSecondary),
            BonusTargets::mechanicalSkills($justSecondary),
            BonusTargets::medicalSkills($justSecondary),
            BonusTargets::militarySkills($justSecondary),
            BonusTargets::physicalSkills($justSecondary),
            BonusTargets::pilotBasicSkills($justSecondary),
            BonusTargets::pilotRelatedSkills($justSecondary),
            BonusTargets::scienceSkills($justSecondary),
            BonusTargets::technicalSkills($justSecondary),
            BonusTargets::weaponProficienciesSkills($justSecondary)
        );
    }
}
