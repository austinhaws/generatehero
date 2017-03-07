<?php
namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

class Bionics extends BaseClass
{
    // how much money the bionic had to spend on bionics
    public $startingBudget;

    // why was the character considered for bionic modification?
    public $conditions;

    public $sponsor;

    public $sponsorStatus;

    // array of Bionic class
    public $bionics;


    // what of this character is bionic? groups allow requirements for bionics to target a type of bionic location
    const BODY_GROUP_HAND = 'hand';
    const BODY_PART_HAND_LEFT = 'left hand';
    const BODY_PART_HAND_RIGHT = 'right hand';
    const BODY_PART_HAND_BOTH = 'both hands';

    const BODY_GROUP_ARM = 'arm';
    const BODY_PART_ARM_LEFT = 'left arm';
    const BODY_PART_ARM_RIGHT = 'right arm';

    const BODY_GROUP_LEG = 'leg';
    const BODY_PART_LEG_LEFT = 'left leg';
    const BODY_PART_LEG_RIGHT = 'right leg';

    const BODY_GROUP_EYE = 'eye';
    const BODY_PART_EYE_LEFT = 'left eye';
    const BODY_PART_EYE_RIGHT = 'right eye';

    const BODY_GROUP_EAR = 'ear';
    const BODY_PART_EAR_LEFT = 'left ear';
    const BODY_PART_EAR_RIGHT = 'right ear';

    const BODY_PART_CHEST_RIBS = 'chest/ribs';
    const BODY_PART_SKULL_FACE = 'skull/face';
    const BODY_PART_LUNGS = 'lungs';
    const BODY_PART_HEART = 'heart';
    const BODY_PART_KIDNEY = 'kidney';

    public $bodyParts = [
        Bionics::BODY_PART_HAND_LEFT => false,
        Bionics::BODY_PART_HAND_RIGHT => false,
        Bionics::BODY_PART_ARM_LEFT => false,
        Bionics::BODY_PART_ARM_RIGHT => false,
        Bionics::BODY_PART_LEG_LEFT => false,
        Bionics::BODY_PART_LEG_RIGHT => false,
        Bionics::BODY_PART_CHEST_RIBS => false,
        Bionics::BODY_PART_SKULL_FACE => false,
        Bionics::BODY_PART_EYE_LEFT => false,
        Bionics::BODY_PART_EYE_RIGHT => false,
        Bionics::BODY_PART_EAR_LEFT => false,
        Bionics::BODY_PART_EAR_RIGHT => false,
        Bionics::BODY_PART_LUNGS => false,
        Bionics::BODY_PART_HEART => false,
        Bionics::BODY_PART_KIDNEY => false,
    ];

    function imageName()
    {
        return 'bionics.png';
    }

    function create(Hero &$hero)
    {
        // all bionics have SDC of 30
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Bionic Base SDC'));

        // step 1 : attributes - already done by generator

        // step 2 : education - will be rolled after bionic created since bionic will not set educationLevel of hero

        // step 3 : budget
        $this->determineBudget();

        // step 4 : building the cyborg
        $this->chooseBionics();

        // step 5 : background information
        $this->backgroundInformation();

        // step 6 : money - starting wealth (not applied to bionics buying)
        $this->rollMoney($hero);

    }

    private function backgroundInformation()
    {
        $this->conditions = $this->engine->tableRoller->rollTable('Bionic: Conditions for Bionic Reconstruction', [
            new TableEntry(10, 'Healthy specimen; destitute. Deemed psychologically suitable.'),
            new TableEntry(20, 'Healthy specimen; fantastically motivated toward bionic research. Deemed psychologically suitable.'),

            new TableEntry(25, 'Lost legs to disease.'),
            new TableEntry(30, 'Lost legs to accident.'),
            new TableEntry(35, 'Lost both arms to disease.'),
            new TableEntry(40, 'Lost both arms to accident.'),

            new TableEntry(60, 'Paraplegic; no hope of recovery.'),

            new TableEntry(70, 'Deteriorating bone disease; no hope for recovery or normal life.'),
            new TableEntry(80, 'Deteriorating muscle disease; no hope for recovery or normal life.'),

            new TableEntry(100, 'Completely paralyzed no brain damage; no hope for recovery.'),
        ]);

        $this->sponsor = $this->engine->tableRoller->rollTable('Bionic: Sponsor', [
            new TableEntry(25, 'Medical research facility'),
            new TableEntry(50, 'Private industry'),
            new TableEntry(56, 'Secret organization: Medical'),
            new TableEntry(62, 'Secret organization: Criminal'),
            new TableEntry(68, 'Secret organization: Crime Fighting'),
            new TableEntry(75, 'Secret organization: Military'),
            new TableEntry(100, 'Military'),
        ]);

        $this->sponsorStatus = $this->engine->tableRoller->rollTable('Bionic: Sponsor Status', [
            new TableEntry(19, 'Allowed to leave; very good, friendly relationship.'),
            new TableEntry(41, 'Allowed to leave after a great antagonism/conflict. Not friendly, but may aid the character.'),
            new TableEntry(64, 'Thrown out of the program! All ties are permanently dissolved; very angry/hostile toward the character.'),
            new TableEntry(89, 'Ran away; secretly hunted by the organization. Hostile, but not necessarily deadly.'),
            new TableEntry(100, 'Ran away; considered to be a criminal and extremely dangerous. Hunted by law enforcement agencies and the sponsor.'),
        ]);
    }

    private function rollMoney(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Bionic Starting Wealth', 4, 4, 100), 'Bionic Starting Wealth'));

        if ($this->engine->roller->rollDice(new Roll('Bionic Has Car?', 1, 100)) <= 80) {
            $age = $this->engine->roller->rollDice(new Roll('Bionic Car Age', 1, 6));
            $years = 'year' . ($age > 1 ? 's' : '');
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, "Owns car that is $age $years old.", 'Bionic Starting Car'));
        }
    }

    private function determineBudget()
    {
        $this->startingBudget = $this->engine->tableRoller->rollTable('Bionic Budget', [
            new TableEntry(17, 6600000),
            new TableEntry(33, 7200000),
            new TableEntry(49, 8000000),
            new TableEntry(66, 8500000),
            new TableEntry(84, 9000000),
            new TableEntry(100, 9500000),
        ]);
    }

    private function chooseBionics()
    {
        // put all possible bionics in to array
            // MAJOR BODY PARTS
        requirements will use these if a chosen bionic part has a requirement
            new Bionic(300000, 'One Hand', 'P.S. 10, P.P. 10', [], []),
            new Bionic(700000, 'One Arm', 'P.S. 10, P.P. 10', [], []),
            new Bionic(1000000, 'One Leg', 'P.S. 10, Spd. 10', [], []),
            new Bionic(500000, 'Chest and/or Partial Ribs', '', [], []),
            new Bionic(500000, 'Skull and/or Face', '', [], []),
            new Bionic(50000, 'Eye (basic)', 'simulates normal eye in appearance', [], []),
            new Bionic(100000, 'Ear (basic)', 'simulates normal ear/hearing', [], []),
            new Bionic(250000, 'Ear (basic)', 'Mouth/throat with voice synthesizer to simulate a normal human voice', [], []),
            new Bionic(75000, 'Lungs', 'simulate normal respiratory system', [], []),
            new Bionic(1000000, 'Heart', 'functions like the real thing', [], []),
            new Bionic(1500000, 'Kidney', 'functions like the real organ', [], []),

        $possibles = [
            // BIONIC EAR SPECIAL FEATURES
            new Bionic(350000, 'Amplified Hearing', 'Range: 360ft radius (109.8m) Heightened hearing enables the character to hear tiny, almost inaudible, sounds several hundred feet away. Other Abilities Include: Estimating the distance of the sound at a 60% + 5% per level proficiency; estimating the speed of the sound\'s approach or departure at 50%+ 5% per level of experience; recognize a voice or sound through intense concentration at 40% + 5% per level of experience; and imitate a voice at a 35% + 5% per level of experience',
                Bionics::BODY_GROUP_EAR, false, [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Amplified Hearing'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, 'Amplified Hearing'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 6, 'Amplified Hearing'),
            ]),
            new Bionic(50000, Bionics::BODY_GROUP_EAR, false, 'Ear Microphone, Radio Receiver, and Transmitter', 'Enables the character to pick up and relay radio transmissions just like a hand-held radio. It is so effective that the character can transmit a whisper, or the voices of other people within 6ft (1.8m) of him. Range: 3 miles.', []),
            new Bionic(70000, Bionics::BODY_GROUP_EAR, false, 'Receive Wide-Band Radio Transmission', 'Including commercial radio (AM & FM), citizen bands (CB), police bands, and common communications frequencies. Range: 6 miles', []),
            new Bionic(10000, Bionics::BODY_GROUP_EAR, false, 'Bug Detector', 'An implant that picks up radio signals from listening devices (bugs). Range: 20ft(6.1m)', []),
            new Bionic(10000, Bionics::BODY_GROUP_EAR, false, 'Radar Signal Detector', 'A tiny radio receiver which softly pings in the character\'s ear when he\'s being scanned by radar.', []),

            // BIONIC EYE SPECIAL OPTICS AND SENSORS
            new Bionic(60000, Bionics::BODY_GROUP_EYE, false, 'Infrared Vision', 'The eye emits a pencil-thin beam of infrared light (invisible to the human eye, but a beacon to another infrared optic system) to illuminate its target in darkness. The narrowness of the beam limits the scope of vision to about 7ft (2m). Range: 600ft (180m).', []),
            new Bionic(80000, Bionics::BODY_GROUP_EYE, false, 'Night Sight', 'A passive image intensifier that electronically amplifies existing ambient light to provide a visible picture without emitting any light of its own. Range: 600ft (180m).', []),
            new Bionic(120000, Bionics::BODY_GROUP_EYE, false, 'Thermo-Imager', 'An optical heat sensor that converts the infrared radiation of warm objects into a visible image. This device allows its operator to see in darkness, shadows and through smoke. Range: 600ft (180m).', []),
            new Bionic(35000, Bionics::BODY_GROUP_EYE, false, 'Telescopic Vision', 'Magnifies an image area like a gun scope. Automatic, self-focusing. Range: 1200ft (360m), 1Oft (3m) image area.', []),
            new Bionic(50000, Bionics::BODY_GROUP_EYE, false, 'Targeting Sight', 'A special system that superimposes target cross hairs.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, 'Targeting Sight'),
            ]),
            new Bionic(30000, Bionics::BODY_GROUP_EYE, false, 'Ultraviolet Sight', 'Enables the character to see ultraviolet light (often used in security systems). Range: 600ft (180m).', []),
            new Bionic(50000, Bionics::BODY_GROUP_EYE, false, 'Micro-Video Camera', 'A zoom lens allows the photographing/taping of documents or images up to 300ft away.', []),

            // SENSORS
            new Bionic(200000, false, false, 'Bio-Scan', 'Indicates the character\'s vital statistics, such as respiration, blood pressure, blood loss, body temperature, pulse rate, etc.', []),
            new Bionic(50000, false, false, 'Motion Detector', 'Registers vibrations in the air indicating movement. A collision warning system will sound an alert to warn the cyborg of an impending collision/impact. Range: 60ft.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 1, 'Motion Detector'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Motion Detector'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, 'Motion Detector'),
            ]),
            new Bionic(250000, false, false, 'Radar', 'A super sophisticated, micro radar system that can identify up to 15 targets and simultaneously track six. Rate of travel, direction, and location are all indicated on the readout. Range: One mile (1.6km).', []),
            new Bionic(50000, false, false, 'Radiation Detector', 'Registers and pinpoints radioactivity. Range: 60ft (18.3m)', []),
            new Bionic(400000, false, false, 'Mini-Computer', 'Actually a glorified calculator. Data can be displayed via a bionic overlay.', []),

            // BIONIC EYE WEAPONS
            new Bionic(400000, Bionics::BODY_GROUP_EYE, Bionics::BODY_GROUP_EYE, 'Eye Laser', 'They eye can emit a laser beam activated by verbal code, or command, or by pressing a trigger stud implant underneath the skin near the temple. Range: 220ft (67.1m); Damage: 2D6 ; Energy Capacity: 10 blasts per hour maximum; Rate or Fire: 3 per melee; Bonus: + 3 to strike', []),
            new Bionic(250000, Bionics::BODY_GROUP_EYE,  Bionics::BODY_GROUP_EYE,'Eye Ion Blaster', 'The eye fires an ion energy pulse activated by a verbal code/command or by pressing a trigger mechanically implanted underneath the skin. Range: 110ft (33.5m); Damage: 204;  Energy Capacity: 12 shots per hour maximum.; Rate or Fire: 4 per melee; Bonus: + 3 to strike', []),
            new Bionic(20000, Bionics::BODY_GROUP_EYE,  Bionics::BODY_GROUP_EYE,'Eye Light Beam', 'A harmless beam of light that can be used as a flashlight or beacon. Range: 220ft (67.lm)', []),

            // BIONIC HAND WEAPONS
            new Bionic(50000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Knuckle Spikes', 'Spikes can be fired from the four knuckles where the fingers join the hand. The trigger mechanism can be a stud concealed in the palm, or in the first finger where the thumb can press it. Range: 120ft (36.6m); Damage: 1D4 each; Rate or Fire: One at a time or in volleys of two, three four, or eight.; Payload: 12 total per hand; easy reload cartridges can be carried and concealed, but take 2 melees (30 seconds) to load.; Bonus: + 2 to strike', []),
            new Bionic(30000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Wrist, or Palm Spikes', 'Needle-like spikes fired from the wrist or palm. Range: 90ft (27 .4m); Damage: 1D4 each; Rate of Fire: Volleys of 2, 4, or 6; Payload: 6 total; reload takes 2 melees (30 seconds); Bonus: + I to strike', []),
            new Bionic(10000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Finger Gun', 'One finger fires a small calibre cartridge. Range: 90ft (27 .4m);  Damage: 2D6 - normal bullet (.38) or 4D6 - exploding shell. Rate or Fire: 1 per melee; Payload: One; reload takes 1 melee (15 seconds). Bonus: + 2 to strike', []),
            new Bionic(80000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Finger Blaster', 'Fires ion beams. Range: 11Oft (33.5m); Damage: 2D4; Energy Capacity: 4 shots per hour maximum; Rate of Fire: 4 per melee; Bonus: + 2 to strike', []),
            new Bionic(300000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Wrist Blaster', 'Ion beams are used instead of lasers because they requires less energy per blast, giving it a greater payload. Range: 660ft (195m); Damage: 3D6; Energy Capacity: 24 blasts per hour maximum; Rate or Fire: 4 per melee; Bonus: +1 to strike.', []),
            new Bionic(50000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Electrical Discharge', 'An electrical discharge erupts from the hand. Range: 12ft (3.6m); Damage: 3D6; Energy Capacity: 4 blasts per hour maximum; Rate of Fire: 2 per melee; Bonus: + 2 to strike.', []),
            new Bionic(40000, Bionics::BODY_GROUP_ARM, Bionics::BODY_GROUP_HAND, 'Spike and Towline', 'The line has a 1000lbs (453.6kg) test strength and a 120ft length. A rewind device can recoil the line, but only has a 500lb (226kg) weight limit. The spike is usually fired from the wrist/forearm. A grappling hook can be fitted in place of the spike, but can not be concealed. Range: 120ft (36.6m); Damage as a Weapon: 1D6', []),

            // - claws plain
            new Bionic(6000, Bionics::BODY_PART_HAND_BOTH, Bionics::BODY_GROUP_HAND, 'Razor Sharp Fingernails', 'The four fingers have razor sharp blades for fingernails. Can be used as a slashing or clawing attack rather than punch. Damage: 1D6', []),
            new Bionic(40000, Bionics::BODY_PART_HAND_LEFT, Bionics::BODY_GROUP_HAND, 'Retractable Claws', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6', []),
            new Bionic(40000, Bionics::BODY_PART_HAND_RIGHT, Bionics::BODY_GROUP_HAND, 'Retractable Claws', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6', []),
            new Bionic(50000, Bionics::BODY_PART_HAND_BOTH, Bionics::BODY_GROUP_HAND, 'Retractable Finger Blades', 'Three to four inch long, double-edged blades retract from the fingers. Damage: 1D8.', []),
            new Bionic(90000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Retractable Blades (Large)', 'These are extremely long blades that are contained in the forearm until extended. The blades extend out of an access portal on the top of the hand. No more than two or three blades can be used per each hand. Damage: 3D6;  Length: One foot (0.3m)', []),

            // - claws paralysis
            new Bionic(14000, Bionics::BODY_PART_HAND_BOTH, Bionics::BODY_GROUP_HAND, 'Razor Sharp Fingernails - Paralysis', 'The four fingers have razor sharp blades for fingernails. Can be used as a slashing or clawing attack rather than punch. Damage: 1D6; Paralysis: Victims are -6 to parry, dodge, and strike for the first two melees that the toxin begins to take effect and then become completely paralyzed/immobile; duration: 4D4 minutes; Saving throw 14 or higher.', []),
            new Bionic(48000, Bionics::BODY_PART_HAND_LEFT, Bionics::BODY_GROUP_HAND, 'Retractable Claws - Paralysis', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6; Paralysis: Victims are -6 to parry, dodge, and strike for the first two melees that the toxin begins to take effect and then become completely paralyzed/immobile; duration: 4D4 minutes; Saving throw 14 or higher.', []),
            new Bionic(48000, Bionics::BODY_PART_HAND_RIGHT, Bionics::BODY_GROUP_HAND, 'Retractable Claws - Paralysis', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6; Paralysis: Victims are -6 to parry, dodge, and strike for the first two melees that the toxin begins to take effect and then become completely paralyzed/immobile; duration: 4D4 minutes; Saving throw 14 or higher.', []),
            new Bionic(58000, Bionics::BODY_PART_HAND_BOTH, Bionics::BODY_GROUP_HAND, 'Retractable Finger Blades - Paralysis', 'Three to four inch long, double-edged blades retract from the fingers. Damage: 1D8; Paralysis: Victims are -6 to parry, dodge, and strike for the first two melees that the toxin begins to take effect and then become completely paralyzed/immobile; duration: 4D4 minutes; Saving throw 14 or higher.', []),
            new Bionic(98000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Retractable Blades (Large) - Paralysis', 'These are extremely long blades that are contained in the forearm until extended. The blades extend out of an access portal on the top of the hand. No more than two or three blades can be used per each hand. Damage: 3D6;  Length: One foot (0.3m; Paralysis: Victims are -6 to parry, dodge, and strike for the first two melees that the toxin begins to take effect and then become completely paralyzed/immobile; duration: 4D4 minutes; Saving throw 14 or higher.)', []),

            // - claws convulsive
            new Bionic(6000, Bionics::BODY_PART_HAND_BOTH, Bionics::BODY_GROUP_HAND, 'Razor Sharp Fingernails - Convulsive', 'The four fingers have razor sharp blades for fingernails. Can be used as a slashing or clawing attack rather than punch. Damage: 1D6; Convulsive: Victims are wracked with nausea and stomach cramps, -6 to strike, parry, dodge, and on initiative; Duration: 4D4; Saving throw 14 or higher.', []),
            new Bionic(40000, Bionics::BODY_PART_HAND_LEFT, Bionics::BODY_GROUP_HAND, 'Retractable Claws - Convulsive', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6; Convulsive: Victims are wracked with nausea and stomach cramps, -6 to strike, parry, dodge, and on initiative; Duration: 4D4; Saving throw 14 or higher.', []),
            new Bionic(40000, Bionics::BODY_PART_HAND_RIGHT, Bionics::BODY_GROUP_HAND, 'Retractable Claws - Convulsive', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6; Convulsive: Victims are wracked with nausea and stomach cramps, -6 to strike, parry, dodge, and on initiative; Duration: 4D4; Saving throw 14 or higher.', []),
            new Bionic(50000, Bionics::BODY_PART_HAND_BOTH, Bionics::BODY_GROUP_HAND, 'Retractable Finger Blades - Convulsive', 'Three to four inch long, double-edged blades retract from the fingers. Damage: 1D8; Convulsive: Victims are wracked with nausea and stomach cramps, -6 to strike, parry, dodge, and on initiative; Duration: 4D4; Saving throw 14 or higher.', []),
            new Bionic(90000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Retractable Blades (Large) - Convulsive', 'These are extremely long blades that are contained in the forearm until extended. The blades extend out of an access portal on the top of the hand. No more than two or three blades can be used per each hand. Damage: 3D6;  Length: One foot (0.3m); Convulsive: Victims are wracked with nausea and stomach cramps, -6 to strike, parry, dodge, and on initiative; Duration: 4D4; Saving throw 14 or higher.', []),

            // - claws poison
            new Bionic(6000, Bionics::BODY_PART_HAND_BOTH, Bionics::BODY_GROUP_HAND, 'Razor Sharp Fingernails - Poison', 'The four fingers have razor sharp blades for fingernails. Can be used as a slashing or clawing attack rather than punch. Damage: 1D6; Poison: Victims take 2D6 points of damage every melee for 1D6 melees; Saving throw 14 or higher.', []),
            new Bionic(40000, Bionics::BODY_PART_HAND_LEFT, Bionics::BODY_GROUP_HAND, 'Retractable Claws - Poison', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6; Poison: Victims take 2D6 points of damage every melee for 1D6 melees; Saving throw 14 or higher.', []),
            new Bionic(40000, Bionics::BODY_PART_HAND_RIGHT, Bionics::BODY_GROUP_HAND, 'Retractable Claws - Poison', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6; Poison: Victims take 2D6 points of damage every melee for 1D6 melees; Saving throw 14 or higher.', []),
            new Bionic(50000, Bionics::BODY_PART_HAND_BOTH, Bionics::BODY_GROUP_HAND, 'Retractable Finger Blades - Poison', 'Three to four inch long, double-edged blades retract from the fingers. Damage: 1D8; Poison: Victims take 2D6 points of damage every melee for 1D6 melees; Saving throw 14 or higher.', []),
            new Bionic(90000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Retractable Blades (Large) - Poison', 'These are extremely long blades that are contained in the forearm until extended. The blades extend out of an access portal on the top of the hand. No more than two or three blades can be used per each hand. Damage: 3D6;  Length: One foot (0.3m); Poison: Victims take 2D6 points of damage every melee for 1D6 melees; Saving throw 14 or higher.', []),

            new Bionic(70000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Chemical Spray - Blind', 'This mace-like spray temporarily blinds its victims for 3D4 melees. Range: 10ft (3m); Bonus: +1 to strike', []),
            new Bionic(70000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Chemical Spray - Tear Gas', 'This gas causes impairment of vision, difficulty in breathing, and skin irritation. Victims are -10 to parry, and dodge. Duration: 4D6 melees; Range: 10ft (3m); Bonus: +1 to strike', []),
            new Bionic(70000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Chemical Spray - Burning Vapor', 'This is caused by a mild acid, doing 1D6 damage, extreme skin irritation, and great for shock value. Victims are -6 to strike, parry, and dodge. Range: 10ft (3m); Bonus: +1 to strike', []),
            new Bionic(70000, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Chemical Spray - C02 Foam', 'This concentrate can be sprayed to put out small fires. Range: 10ft (3m); Bonus: +1 to strike', []),
            new Bionic(1800, Bionics::BODY_GROUP_HAND, Bionics::BODY_GROUP_HAND, 'Explosive Finger Joints', 'One finger on each bionic hand is really detachable (three segmented) grenades. Range: Thrown about 60ft (18.3m); too small and light to throw farther. Damage: 4D6; Blast Area: 6ft', []),

        ];


        // filter out by cost

        // randomly choose one
        // if it has a required body location being bionic, try to install that part
            // if the required bod location is already bionic then good to go
            // if required location has two options then randomly choose one to make bionic
            // if required location has two options and one is already bionic randomly determine if the other location should be made bionic (low chance of this)
            // if other location should be made bionic but costs too much then just use the current bionic location
        // if requirement too expensive then remove this chosen item from the list

        // keep going until the list is empty
        need to add increased pp/speed when gaining an artificial limb(s) (pg 61) - probably after gaining an extra arm, legs, or hand, check if it should gain extra pp/ps/speed

    }
}