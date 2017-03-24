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
    public $budgetRemaining;

    // why was the character considered for bionic modification?
    public $conditions;

    public $sponsor;

    public $sponsorStatus;

    // array of Bionic class
    /** @var Bionic[] bionics */
    public $bionics;
    // map of string (BionicLocation::enum) => bool; true means the location is bionic
    public $bionicBody;

    function create(Hero &$hero)
    {
        // all bionics have SDC of 30
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Bionic Base SDC'));

        // step 1 : attributes - already done by generator

        // step 2 : education - will be rolled after bionic created since bionic will not set educationLevel of hero

        // step 3 : budget
        $this->determineBudget();

        // step 4 : building the cyborg
        $this->chooseBionics($hero);

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

        $this->hasCar($hero, 80);
    }

    private function determineBudget()
    {
        $this->budgetRemaining = $this->startingBudget = $this->engine->tableRoller->rollTable('Bionic Budget', [
            new TableEntry(17, 6600000),
            new TableEntry(33, 7200000),
            new TableEntry(49, 8000000),
            new TableEntry(66, 8500000),
            new TableEntry(84, 9000000),
            new TableEntry(100, 9500000),
        ]);
    }

    private function chooseBionics(Hero &$hero)
    {
        // put all possible bionics in to array
        $possibles = [
            // BIONIC EAR SPECIAL FEATURES
            new Bionic(350000, new BionicLocation(false, [BionicLocation::BODY_PART_EAR_LEFT, BionicLocation::BODY_PART_EAR_RIGHT], false, false),
                'Amplified Hearing', 'Range: 360ft radius (109.8m) Heightened hearing enables the character to hear tiny, almost inaudible, sounds several hundred feet away. Other Abilities Include: Estimating the distance of the sound at a 60% + 5% per level proficiency; estimating the speed of the sound\'s approach or departure at 50%+ 5% per level of experience; recognize a voice or sound through intense concentration at 40% + 5% per level of experience; and imitate a voice at a 35% + 5% per level of experience',
                [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Amplified Hearing'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, 'Amplified Hearing'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 6, 'Amplified Hearing'),
                ]),
            new Bionic(50000, new BionicLocation(false, [BionicLocation::BODY_PART_EAR_LEFT, BionicLocation::BODY_PART_EAR_RIGHT], false, false),
                'Ear Microphone, Radio Receiver, and Transmitter', 'Enables the character to pick up and relay radio transmissions just like a hand-held radio. It is so effective that the character can transmit a whisper, or the voices of other people within 6ft (1.8m) of him. Range: 3 miles.', []),
            new Bionic(70000, new BionicLocation(false, [BionicLocation::BODY_PART_EAR_LEFT, BionicLocation::BODY_PART_EAR_RIGHT], false, false),
                'Receive Wide-Band Radio Transmission', 'Including commercial radio (AM & FM), citizen bands (CB), police bands, and common communications frequencies. Range: 6 miles', []),
            new Bionic(10000, new BionicLocation(false, [BionicLocation::BODY_PART_EAR_LEFT, BionicLocation::BODY_PART_EAR_RIGHT], false, false),
                'Bug Detector', 'An implant that picks up radio signals from listening devices (bugs). Range: 20ft(6.1m)', []),
            new Bionic(10000, new BionicLocation(false, [BionicLocation::BODY_PART_EAR_LEFT, BionicLocation::BODY_PART_EAR_RIGHT], false, false),
                'Radar Signal Detector', 'A tiny radio receiver which softly pings in the character\'s ear when he\'s being scanned by radar.', []),

            // BIONIC EYE SPECIAL OPTICS AND SENSORS
            new Bionic(60000, new BionicLocation(false, [BionicLocation::BODY_PART_EYE_LEFT, BionicLocation::BODY_PART_EYE_RIGHT], false, false),
                'Infrared Vision', 'The eye emits a pencil-thin beam of infrared light (invisible to the human eye, but a beacon to another infrared optic system) to illuminate its target in darkness. The narrowness of the beam limits the scope of vision to about 7ft (2m). Range: 600ft (180m).', []),
            new Bionic(80000, new BionicLocation(false, [BionicLocation::BODY_PART_EYE_LEFT, BionicLocation::BODY_PART_EYE_RIGHT], false, false),
                'Night Sight', 'A passive image intensifier that electronically amplifies existing ambient light to provide a visible picture without emitting any light of its own. Range: 600ft (180m).', []),
            new Bionic(120000, new BionicLocation(false, [BionicLocation::BODY_PART_EYE_LEFT, BionicLocation::BODY_PART_EYE_RIGHT], false, false),
                'Thermo-Imager', 'An optical heat sensor that converts the infrared radiation of warm objects into a visible image. This device allows its operator to see in darkness, shadows and through smoke. Range: 600ft (180m).', []),
            new Bionic(35000, new BionicLocation(false, [BionicLocation::BODY_PART_EYE_LEFT, BionicLocation::BODY_PART_EYE_RIGHT], false, false),
                'Telescopic Vision', 'Magnifies an image area like a gun scope. Automatic, self-focusing. Range: 1200ft (360m), 1Oft (3m) image area.', []),
            new Bionic(50000, new BionicLocation(false, [BionicLocation::BODY_PART_EYE_LEFT, BionicLocation::BODY_PART_EYE_RIGHT], false, false),
                'Targeting Sight', 'A special system that superimposes target cross hairs.', [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, 'Targeting Sight'),
                ]),
            new Bionic(30000, new BionicLocation(false, [BionicLocation::BODY_PART_EYE_LEFT, BionicLocation::BODY_PART_EYE_RIGHT], false, false),
                'Ultraviolet Sight', 'Enables the character to see ultraviolet light (often used in security systems). Range: 600ft (180m).', []),
            new Bionic(50000, new BionicLocation(false, [BionicLocation::BODY_PART_EYE_LEFT, BionicLocation::BODY_PART_EYE_RIGHT], false, false),
                'Micro-Video Camera', 'A zoom lens allows the photographing/taping of documents or images up to 300ft away.', []),

            // SENSORS
            new Bionic(200000, new BionicLocation(false, false, false, false), 'Bio-Scan', 'Indicates the character\'s vital statistics, such as respiration, blood pressure, blood loss, body temperature, pulse rate, etc.', []),
            new Bionic(50000, new BionicLocation(false, false, false, false), 'Motion Detector', 'Registers vibrations in the air indicating movement. A collision warning system will sound an alert to warn the cyborg of an impending collision/impact. Range: 60ft.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 1, 'Motion Detector'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Motion Detector'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, 'Motion Detector'),
            ]),
            new Bionic(250000, new BionicLocation(false, false, false, false), 'Radar', 'A super sophisticated, micro radar system that can identify up to 15 targets and simultaneously track six. Rate of travel, direction, and location are all indicated on the readout. Range: One mile (1.6km).', []),
            new Bionic(50000, new BionicLocation(false, false, false, false), 'Radiation Detector', 'Registers and pinpoints radioactivity. Range: 60ft (18.3m)', []),
            new Bionic(400000, new BionicLocation(false, false, false, false), 'Mini-Computer', 'Actually a glorified calculator. Data can be displayed via a bionic overlay.', []),

            // BIONIC EYE WEAPONS
            new Bionic(400000, new BionicLocation(false, [BionicLocation::BODY_PART_EYE_LEFT, BionicLocation::BODY_PART_EYE_RIGHT], true, true),
                'Eye Laser', 'They eye can emit a laser beam activated by verbal code, or command, or by pressing a trigger stud implant underneath the skin near the temple. Range: 220ft (67.1m); Damage: 2D6 ; Energy Capacity: 10 blasts per hour maximum; Rate or Fire: 3 per melee; Bonus: + 3 to strike', []),
            new Bionic(250000, new BionicLocation(false, [BionicLocation::BODY_PART_EYE_LEFT, BionicLocation::BODY_PART_EYE_RIGHT], true, true),
                'Eye Ion Blaster', 'The eye fires an ion energy pulse activated by a verbal code/command or by pressing a trigger mechanically implanted underneath the skin. Range: 110ft (33.5m); Damage: 204;  Energy Capacity: 12 shots per hour maximum.; Rate or Fire: 4 per melee; Bonus: + 3 to strike', []),
            new Bionic(20000, new BionicLocation(false, [BionicLocation::BODY_PART_EYE_LEFT, BionicLocation::BODY_PART_EYE_RIGHT], true, true),
                'Eye Light Beam', 'A harmless beam of light that can be used as a flashlight or beacon. Range: 220ft (67.lm)', []),

            // BIONIC HAND WEAPONS
            new Bionic(50000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Knuckle Spikes', 'Spikes can be fired from the four knuckles where the fingers join the hand. The trigger mechanism can be a stud concealed in the palm, or in the first finger where the thumb can press it. Range: 120ft (36.6m); Damage: 1D4 each; Rate or Fire: One at a time or in volleys of two, three four, or eight.; Payload: 12 total per hand; easy reload cartridges can be carried and concealed, but take 2 melees (30 seconds) to load.; Bonus: + 2 to strike', []),
            new Bionic(30000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Wrist, or Palm Spikes', 'Needle-like spikes fired from the wrist or palm. Range: 90ft (27 .4m); Damage: 1D4 each; Rate of Fire: Volleys of 2, 4, or 6; Payload: 6 total; reload takes 2 melees (30 seconds); Bonus: + I to strike', []),
            new Bionic(10000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Finger Gun', 'One finger fires a small calibre cartridge. Range: 90ft (27 .4m);  Damage: 2D6 - normal bullet (.38) or 4D6 - exploding shell. Rate or Fire: 1 per melee; Payload: One; reload takes 1 melee (15 seconds). Bonus: + 2 to strike', []),
            new Bionic(80000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Finger Blaster', 'Fires ion beams. Range: 11Oft (33.5m); Damage: 2D4; Energy Capacity: 4 shots per hour maximum; Rate of Fire: 4 per melee; Bonus: + 2 to strike', []),
            new Bionic(300000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Wrist Blaster', 'Ion beams are used instead of lasers because they requires less energy per blast, giving it a greater payload. Range: 660ft (195m); Damage: 3D6; Energy Capacity: 24 blasts per hour maximum; Rate or Fire: 4 per melee; Bonus: +1 to strike.', []),
            new Bionic(50000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Electrical Discharge', 'An electrical discharge erupts from the hand. Range: 12ft (3.6m); Damage: 3D6; Energy Capacity: 4 blasts per hour maximum; Rate of Fire: 2 per melee; Bonus: + 2 to strike.', []),
            new Bionic(40000, new BionicLocation(false, [BionicLocation::BODY_PART_ARM_LEFT, BionicLocation::BODY_PART_ARM_RIGHT], true, true),
                'Spike and Towline', 'The line has a 1000lbs (453.6kg) test strength and a 120ft length. A rewind device can recoil the line, but only has a 500lb (226kg) weight limit. The spike is usually fired from the wrist/forearm. A grappling hook can be fitted in place of the spike, but can not be concealed. Range: 120ft (36.6m); Damage as a Weapon: 1D6', []),

            // - claws plain
            new Bionic(6000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Razor Sharp Fingernails', 'The four fingers have razor sharp blades for fingernails. Can be used as a slashing or clawing attack rather than punch. Damage: 1D6', []),
            new Bionic(40000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Retractable Claws', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6', []),
            new Bionic(50000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Retractable Finger Blades', 'Three to four inch long, double-edged blades retract from the fingers. Damage: 1D8.', []),
            new Bionic(90000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Retractable Blades (Large)', 'These are extremely long blades that are contained in the forearm until extended. The blades extend out of an access portal on the top of the hand. No more than two or three blades can be used per each hand. Damage: 3D6;  Length: One foot (0.3m)', []),

            // - claws paralysis
            new Bionic(56000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Razor Sharp Fingernails - Paralysis', 'The four fingers have razor sharp blades for fingernails. Can be used as a slashing or clawing attack rather than punch. Damage: 1D6; Paralysis: Victims are -6 to parry, dodge, and strike for the first two melees that the toxin begins to take effect and then become completely paralyzed/immobile; duration: 4D4 minutes; Saving throw 14 or higher.', []),
            new Bionic(90000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Retractable Claws - Paralysis', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6; Paralysis: Victims are -6 to parry, dodge, and strike for the first two melees that the toxin begins to take effect and then become completely paralyzed/immobile; duration: 4D4 minutes; Saving throw 14 or higher.', []),
            new Bionic(100000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Retractable Finger Blades - Paralysis', 'Three to four inch long, double-edged blades retract from the fingers. Damage: 1D8; Paralysis: Victims are -6 to parry, dodge, and strike for the first two melees that the toxin begins to take effect and then become completely paralyzed/immobile; duration: 4D4 minutes; Saving throw 14 or higher.', []),
            new Bionic(140000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Retractable Blades (Large) - Paralysis', 'These are extremely long blades that are contained in the forearm until extended. The blades extend out of an access portal on the top of the hand. No more than two or three blades can be used per each hand. Damage: 3D6;  Length: One foot (0.3m; Paralysis: Victims are -6 to parry, dodge, and strike for the first two melees that the toxin begins to take effect and then become completely paralyzed/immobile; duration: 4D4 minutes; Saving throw 14 or higher.)', []),

            // - claws convulsive
            new Bionic(46000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Razor Sharp Fingernails - Convulsive', 'The four fingers have razor sharp blades for fingernails. Can be used as a slashing or clawing attack rather than punch. Damage: 1D6; Convulsive: Victims are wracked with nausea and stomach cramps, -6 to strike, parry, dodge, and on initiative; Duration: 4D4; Saving throw 14 or higher.', []),
            new Bionic(80000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Retractable Claws - Convulsive', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6; Convulsive: Victims are wracked with nausea and stomach cramps, -6 to strike, parry, dodge, and on initiative; Duration: 4D4; Saving throw 14 or higher.', []),
            new Bionic(90000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Retractable Finger Blades - Convulsive', 'Three to four inch long, double-edged blades retract from the fingers. Damage: 1D8; Convulsive: Victims are wracked with nausea and stomach cramps, -6 to strike, parry, dodge, and on initiative; Duration: 4D4; Saving throw 14 or higher.', []),
            new Bionic(130000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Retractable Blades (Large) - Convulsive', 'These are extremely long blades that are contained in the forearm until extended. The blades extend out of an access portal on the top of the hand. No more than two or three blades can be used per each hand. Damage: 3D6;  Length: One foot (0.3m); Convulsive: Victims are wracked with nausea and stomach cramps, -6 to strike, parry, dodge, and on initiative; Duration: 4D4; Saving throw 14 or higher.', []),

            // - claws poison
            new Bionic(56000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Razor Sharp Fingernails - Poison', 'The four fingers have razor sharp blades for fingernails. Can be used as a slashing or clawing attack rather than punch. Damage: 1D6; Poison: Victims take 2D6 points of damage every melee for 1D6 melees; Saving throw 14 or higher.', []),
            new Bionic(90000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Retractable Claws - Poison', 'Five razor sharp, one or two inch long claws that can be extended or retracted at will, like a cat. Slashing or clawing attacks. Damage: 1D6; Poison: Victims take 2D6 points of damage every melee for 1D6 melees; Saving throw 14 or higher.', []),
            new Bionic(100000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Retractable Finger Blades - Poison', 'Three to four inch long, double-edged blades retract from the fingers. Damage: 1D8; Poison: Victims take 2D6 points of damage every melee for 1D6 melees; Saving throw 14 or higher.', []),
            new Bionic(140000, new BionicLocation([BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], false, false, true),
                'Retractable Blades (Large) - Poison', 'These are extremely long blades that are contained in the forearm until extended. The blades extend out of an access portal on the top of the hand. No more than two or three blades can be used per each hand. Damage: 3D6;  Length: One foot (0.3m); Poison: Victims take 2D6 points of damage every melee for 1D6 melees; Saving throw 14 or higher.', []),

            new Bionic(70000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Chemical Spray - Blind', 'This mace-like spray temporarily blinds its victims for 3D4 melees. Range: 10ft (3m); Bonus: +1 to strike', []),
            new Bionic(70000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Chemical Spray - Tear Gas', 'This gas causes impairment of vision, difficulty in breathing, and skin irritation. Victims are -10 to parry, and dodge. Duration: 4D6 melees; Range: 10ft (3m); Bonus: +1 to strike', []),
            new Bionic(70000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Chemical Spray - Burning Vapor', 'This is caused by a mild acid, doing 1D6 damage, extreme skin irritation, and great for shock value. Victims are -6 to strike, parry, and dodge. Range: 10ft (3m); Bonus: +1 to strike', []),
            new Bionic(70000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Chemical Spray - C02 Foam', 'This concentrate can be sprayed to put out small fires. Range: 10ft (3m); Bonus: +1 to strike', []),
            new Bionic(1800, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_LEFT, BionicLocation::BODY_PART_HAND_RIGHT], true, true),
                'Explosive Finger Joints', 'One finger on each bionic hand is really detachable (three segmented) grenades. Range: Thrown about 60ft (18.3m); too small and light to throw farther. Damage: 4D6; Blast Area: 6ft', []),

            // OTHER BIONICS
            new Bionic(450000, new BionicLocation(false, [BionicLocation::BODY_PART_LEG_LEFT, BionicLocation::BODY_PART_LEG_RIGHT, BionicLocation::BODY_PART_ARM_LEFT, BionicLocation::BODY_PART_ARM_RIGHT], true, true),
                'Ion Rod - Concealed', 'A tube-like device that is a foot and a half to two feet long (0.6m) and fires an energy charge. The rod is concealed in a hidden compartment inside the limb. When needed, the rod extends out of the concealed compartment. Range 300ft (91.5m); Damage: 3D6; Rate of fire: 4 per melee; Bonus: +2 strike', []),
            new Bionic(350000, new BionicLocation(false, [BionicLocation::BODY_PART_LEG_LEFT, BionicLocation::BODY_PART_LEG_RIGHT, BionicLocation::BODY_PART_ARM_LEFT, BionicLocation::BODY_PART_ARM_RIGHT], true, true),
                'Ion Rod - External', 'A tube-like device that is a foot and a half to two feet long (0.6m) and fires an energy charge. Range 300ft (91.5m); Damage: 3D6; Rate of fire: 4 per melee; Bonus: +2 strike', []),

            new Bionic(500000, new BionicLocation(false, [BionicLocation::BODY_PART_ARM_LEFT, BionicLocation::BODY_PART_ARM_RIGHT, BionicLocation::BODY_PART_LEG_LEFT, BionicLocation::BODY_PART_LEG_RIGHT], true, true),
                'Laser Rod - Concealed', 'A tube-like device that is a foot and a half to two feet long (0.6m) and fires a laser pulse. The rod is concealed in a hidden compartment inside the limb. When needed, the rod extends out of the concealed compartment. Range 600ft (91.5m); Damage: 4D6; Rate of fire: 4 per melee; Bonus: +2 strike', []),
            new Bionic(400000, new BionicLocation(false, [BionicLocation::BODY_PART_ARM_LEFT, BionicLocation::BODY_PART_ARM_RIGHT, BionicLocation::BODY_PART_LEG_LEFT, BionicLocation::BODY_PART_LEG_RIGHT], true, true),
                'Laser Rod - External', 'A tube-like device that is a foot and a half to two feet long (0.6m) and fires a laser pulse. Range 600ft (91.5m); Damage: 4D6; Rate of fire: 4 per melee; Bonus: +2 strike', []),

            new Bionic(200000, new BionicLocation(false, BionicLocation::ALL_LOCATIONS(), true, false),
                'Mini Laser', 'A miniature laser that can be easily concealed in a secret compartment inside a bionic arm, leg, hip, chest, etc. The mini-laser is only slightly larger and bulkier than a pen flashlight, measuring about six or seven inches long and two inches wide. Range: 60ft (18. 3m); Damage: 2D4; Rate of Fire: 4 per melee; Bonus: +1 to strike.', []),
            new Bionic(30000, new BionicLocation([BionicLocation::BODY_PART_CHEST_RIBS], false, false, true),
                'Flame Thrower', 'A small unit with a retractable nozzle and hose. Range: 16ft (4.9m); Damage: 306 plus, a 60% chance of setting combustibles ablaze. Rate of Fire: 5 short bursts per melee, each counts as one melee attack.', []),

            // LUNG SPECIAL FEATURES
            new Bionic(40000, new BionicLocation([BionicLocation::BODY_PART_LUNGS], false, false, false),
                'Independent Oxygen Supply', 'Built in to the chest and lung cavity, increasing the time the cyborg can hold his breath to 15 minutes.', []),
            new Bionic(100000, new BionicLocation([BionicLocation::BODY_PART_LUNGS], false, false, false),
                'Gas Filtration System', 'A miniature air filtration system that purifies impurities from the air. When exposed to gaseous toxins the system attempts to filter them out.', [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_GASES, 6, 'Gas Filtration System'),
                ]),

            // MOUTH AND THROAT FEATURES
            new Bionic(150000, new BionicLocation([BionicLocation::BODY_PART_MOUTH_THROAT], false, false, false),
                'Modulating Voice Synthesizer', 'Allows the character to change/disguise his voice by altering tone, base, pitch, etc.', [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::IMITATE_VOICES, 10, 'Modulating Voice Synthesizer'),
                ]),
            new Bionic(80000, new BionicLocation([BionicLocation::BODY_PART_MOUTH_THROAT], false, false, false),
                'Inaudible Frequency Range', 'Emit sound frequencies inaudible to the human ear, like a dog whistle.', []),
            new Bionic(40000, new BionicLocation([BionicLocation::BODY_PART_MOUTH_THROAT], false, false, false),
                'Built-In Loudspeaker', 'Amplify the loudness of his voice like a bull horn.', []),
            new Bionic(150000, new BionicLocation([BionicLocation::BODY_PART_MOUTH_THROAT], false, false, false),
                'Built-In Radio Scrambler', 'Have security coded and decoded conversations over the radio and telephone. Note that the person on the other end must have a scrambling system to decode received messages and to transmit coded ones.', []),

            // EXOSKELETONS
            new Bionic(1000000, new BionicLocation([BionicLocation::BODY_PART_CHEST_RIBS], false, false, false),
                'Exoskeleton - Spine and Shoulders', '', [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 50, 'Exoskeleton - Spine and Shoulders'),
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ROLL, 1, 'Exoskeleton - Spine and Shoulders'),
                ]),
            new Bionic(1000000, new BionicLocation([BionicLocation::BODY_PART_ARM_LEFT, BionicLocation::BODY_PART_ARM_RIGHT], false, false, false), 'Exoskeleton - Arms and Shoulders', '', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Exoskeleton - Arms and Shoulders'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ROLL, 1, 'Exoskeleton - Arms and Shoulders'),
            ]),
            new Bionic(200000, new BionicLocation(false, [BionicLocation::BODY_PART_HAND_RIGHT, BionicLocation::BODY_PART_HAND_LEFT], true, false), 'Exoskeleton - Hands and Wrist', '', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 10, 'Exoskeleton - Hand and Wrist'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ROLL, 1, 'Exoskeleton - Hand and Wrist'),
            ]),
            new Bionic(1000000, new BionicLocation([BionicLocation::BODY_PART_LEG_LEFT, BionicLocation::BODY_PART_LEG_RIGHT], false, false, false), 'Exoskeleton - Legs and Hips', '', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Exoskeleton - Leg and Hip'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ROLL, 1, 'Exoskeleton - Leg and Hip'),
            ]),
            new Bionic(100000, new BionicLocation(false, [BionicLocation::BODY_PART_FOOT_LEFT, BionicLocation::BODY_PART_FOOT_RIGHT], true, false), 'Exoskeleton - foot and ankle', '', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 5, 'Exoskeleton - Foot and ankle'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ROLL, 1, 'Exoskeleton - Foot and ankle'),
            ]),

            // BIONIC BODY ARMOR
            new Bionic(350000, new BionicLocation(false, false, false, false), 'Full Body Armor', 'AR: 18; SDC: 900; Weight: 120lbs (54.46kg)', []),
            new Bionic(250000, new BionicLocation(false, false, false, false), '3/4 Body Armor', 'Covers chest, abdomen, arms, hips, and legs. AR: 16; SDC: 600; Weight: 90lbs (40kg)', []),
            new Bionic(150000, new BionicLocation(false, false, false, false), '1/2 Body Armor', 'Covers chest, abdomen, and hips. AR: 14; SDC: 500; Weight: 80lbs (36kg)', []),
            new Bionic(75000, new BionicLocation(false, false, false, false), 'Half Suit Armor', 'Covers chest and  abdomen. AR: 11; SDC: 250; Weight: 50lbs (22kg)', []),
            new Bionic(60000, new BionicLocation(false, false, false, false), 'Hip and Leg Armor', 'AR: 9; SDC: 200; Weight: 45lbs (21kg)', []),
            new Bionic(60000, new BionicLocation(false, false, false, false), 'Neck, Head, and Shoulders Armor', 'AR: 7; SDC: 150; Weight: 30lbs (13kg)', []),

            new Bionic(8000, new BionicLocation(false, false, false, false), 'Small Secret Compartment', 'Holds small tools or weapons.', []),
        ];

        // keep picking bionics until out of budget
        while (count($possibles)) {
            $possibles = array_filter($possibles, function ($bionic) {
                return $bionic->cost <= $this->budgetRemaining;
            });
            if (count($possibles)) {
                $this->engine->arrayTools->shuffle($possibles);
                $bionic = array_shift($possibles);
                if ($bionic->bionicLocation->orLocations) {
                    $this->orLocations($bionic, $hero);
                } else {
                    $this->andLocations($bionic, $hero);
                }

                // can have multiple secret compartments
                if ($bionic->title == 'Small Secret Compartment') {
                    $possibles[] = $bionic;
                }
            }
        }
    }

    /**
     * @param Hero $hero
     * @param $bionic Bionic the bionic to add to the character if the price isn't too much
     * @param $addOppositeLimb bool should the matching limb also be made bionic? for legs, both legs have to be bionic to get the speed bonus
     * @param $skinnable bool can the area maybe have synthetic skin?
     * @param $increasePP bool should the pp be increased
     * @param $increasePS bool should the ps be increased
     * @param $increaseSpeed bool should speed be increased
     * @return bool true if the location was made bionic
     */
    private function addBionicBody(Hero &$hero, $bionic, $addOppositeLimb, $skinnable, $increasePP, $increasePS, $increaseSpeed)
    {
        $FULL_SKIN_AREA = 22;

        $added = false;

        // can the bionic part be afforded?
        if ($this->budgetRemaining >= $bionic->cost) {
            // add the bionic
            $added = true;
            $this->budgetRemaining -= $bionic->cost;
            $this->bionics[] = $bionic;
            $this->bionicBody[$bionic->bionicLocation->andLocations[0]] = true;

            // artificial skin on body part?
            if ($skinnable && $this->engine->roller->rollDice(new Roll('Body Part Skinnable', 1, 100)) > 50) {
                $cost = ceil($FULL_SKIN_AREA * $skinnable);
                if ($this->engine->roller->rollDice(new Roll('Body Part Skinnable: Type', 1, 100)) > 50) {
                    $cost *= 1000;
                    if ($cost <= $this->budgetRemaining) {
                        $bionic->title .= ' - Synthetic Plastic Skin';
                        $bionic->description .= ' Synthetic Plastic Skin looks and feels like real human flesh. Although slightly tougher than human skin, it does not provide an additional protection.';
                        $this->budgetRemaining -= $cost;
                    }
                } else {
                    $cost *= 500;
                    if ($cost <= $this->budgetRemaining) {
                        $bionic->title .= ' - Hard Plastic Skin';
                        $bionic->description .= 'Hard Plastic Skin resembles human flesh. It does not feel anything like real skin. Normal weapons such as knives, clubs, and low calibre bullets (.22, .25) do half damage.';
                        $bionic->bonuses[] = new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 15, $bionic->title);
                        $this->budgetRemaining -= $cost;
                    }
                }
            }

            // also try to add the other leg when increasing speed since both legs have to match in order for speed to increase overall
            $otherLegBionic = false;
            if ($increaseSpeed && $addOppositeLimb) {
                // check if the other leg can be made bionic (so speed can be on both legs)
                $otherLegLocation = $this->bionicBody[BionicLocation::BODY_PART_LEG_LEFT] ? BionicLocation::BODY_PART_LEG_RIGHT : BionicLocation::BODY_PART_LEG_LEFT;
                if ($this->budgetRemaining >= $bionic->cost) {
                    // make the other leg bionic too
                    $otherLegBionic = new Bionic($bionic->cost, new BionicLocation([$otherLegLocation], false, false, false), $otherLegLocation, '', []);
                    if (!$this->addBionicBody($hero, $otherLegBionic, false, $skinnable, false, false, false)) {
                        $otherLegBionic = false;
                    }
                }

                // no use adding speed if both legs aren't bionic
                if ($otherLegBionic) {
                    // 10000 per point above 10 for a pair of legs
                    // 220 max (base 10 + 210 bonus)
                    $costPerPoint = 10000;
                    $maxBonus = min(floor($this->budgetRemaining / $costPerPoint), 210);
                    if ($maxBonus > 0) {
                        $bonus = $this->engine->roller->rollDice(new Roll('Bionic Leg Speed Bonus', 1, $maxBonus));
                        $this->budgetRemaining -= $costPerPoint * $bonus;
                        $bonus += 10;
                        $bonusDescription = " Speed: $bonus";

                        // character's speed increased!
                        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_SPEED, $bonus, 'Bionic Legs'));

                        // both bionics say their bonus
                        $bionic->description .= $bonusDescription;
                        $otherLegBionic->description .= $bonusDescription;
                    }

                }
            }
            if ($increasePS) {
                $costPerPoint = 2000;
                // 24 max (base 10 + 14 bonus)
                $maxBonus = min(floor($this->budgetRemaining / $costPerPoint), 14);
                if ($maxBonus > 0) {
                    $bonus = $this->engine->roller->rollDice(new Roll('Bionic PS Bonus', 1, $maxBonus));
                    $this->budgetRemaining -= $costPerPoint * $bonus;
                    $bonus += 10;
                    $bionic->description .= " PS: $bonus";
                    // not added to character since both limbs have to match to have the character get the bonus and that calc is not worth it
                }
            }
            if ($increasePP) {
                $costPerPoint = 10000;
                // 23 max (base 10 + 13 bonus)
                $maxBonus = min(floor($this->budgetRemaining / $costPerPoint), 13);
                if ($maxBonus > 0) {
                    $bonus = $this->engine->roller->rollDice(new Roll('Bionic PP Bonus', 1, $maxBonus));
                    $this->budgetRemaining -= $costPerPoint * $bonus;
                    $bonus += 10;
                    $bionic->description .= " PP: $bonus";
                    // not added to character since both limbs have to match to have the character get the bonus and that calc is not worth it
                }
            }
        }
        return $added;
    }

    /**
     * check if the location can be made bionic: cost
     *
     * @param $bionicLocation string
     * @param Hero $hero
     * @return bool
     * @throws \Exception
     */
    private function makeLocationBionic($bionicLocation, Hero &$hero)
    {
        // loop through bionics and find one that matches the title
        $added = true;
        if (!$this->bionicBody[$bionicLocation]) {
            // MAJOR BODY PARTS
            $bionic = false;

            // true if the part could have artificial skin on it; full body is 22 square feet (http://www.exrx.net/Kinesiology/Segments.html)
            $ARM_PERCENT = 4.76;
            $EAR_PERCENT = 2.0;
            $FOOT_PERCENT = 1.38;

            $skinnable = false;
            $increasePP = false;
            $increasePS = false;
            $increaseSpeed = false;

            $location = new BionicLocation([$bionicLocation], false, false, false);
            switch ($bionicLocation) {
                case BionicLocation::BODY_PART_ARM_LEFT:
                case BionicLocation::BODY_PART_ARM_RIGHT:
                    $bionic = new Bionic(700000, $location, $bionicLocation, '', []);
                    $skinnable = $ARM_PERCENT;
                    $increasePP = true;
                    $increasePS = true;
                    break;

                case BionicLocation::BODY_PART_CHEST_RIBS:
                    $bionic = new Bionic(500000, $location, $bionicLocation, '', [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 50, 'Bionic Chest/Ribs')]);
                    $skinnable = 54.15;
                    break;

                case BionicLocation::BODY_PART_EAR_LEFT:
                case BionicLocation::BODY_PART_EAR_RIGHT:
                    $bionic = new Bionic(100000, $location, $bionicLocation, 'simulates normal ear/hearing', []);
                    $skinnable = $EAR_PERCENT;
                    break;

                case BionicLocation::BODY_PART_EYE_LEFT:
                case BionicLocation::BODY_PART_EYE_RIGHT:
                    $bionic = new Bionic(50000, $location, $bionicLocation, 'simulates normal eye in appearance', []);
                    break;

                case BionicLocation::BODY_PART_FOOT_LEFT:
                case BionicLocation::BODY_PART_FOOT_RIGHT:
                    // foot not in rules
                    $bionic = new Bionic(150000, $location, $bionicLocation, '', []);
                    $skinnable = $FOOT_PERCENT;
                    break;

                case BionicLocation::BODY_PART_HAND_LEFT:
                case BionicLocation::BODY_PART_HAND_RIGHT:
                    $bionic = new Bionic(300000, $location, $bionicLocation, '', []);
                    $skinnable = true;
                    $increasePP = true;
                    $increasePS = true;
                    break;

                case BionicLocation::BODY_PART_HEART:
                    $bionic = new Bionic(1000000, $location, $bionicLocation, 'functions like the real thing', []);
                    break;

                case BionicLocation::BODY_PART_KIDNEY:
                    $bionic = new Bionic(1500000, $location, $bionicLocation, 'functions like the real organ.', []);
                    break;

                case BionicLocation::BODY_PART_LEG_LEFT:
                case BionicLocation::BODY_PART_LEG_RIGHT:
                    $bionic = new Bionic(1000000, $location, $bionicLocation, '', []);
                    $skinnable = true;
                    $increasePS = true;
                    $increaseSpeed = true;
                    break;

                case BionicLocation::BODY_PART_LUNGS:
                    $bionic = new Bionic(75000, $location, $bionicLocation, 'simulate normal respiratory system. Can capture and regulate air much more precisely, enabling the character to hold his breath for five minutes.', []);
                    break;

                case BionicLocation::BODY_PART_MOUTH_THROAT:
                    $bionic = new Bionic(250000, $location, $bionicLocation, 'voice synthesizer to simulate a normal human voice', []);
                    break;

                case BionicLocation::BODY_PART_SKULL_FACE:
                    $bionic = new Bionic(500000, $location, $bionicLocation, '', [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Bionic Skull/Face')]);
                    $skinnable = true;
                    break;

                default:
                    throw new \Exception("Unknown bionic location: " . $bionicLocation);
            }

            $added = $this->addBionicBody($hero, $bionic, true, $skinnable, $increasePP, $increasePS, $increaseSpeed);
        }

        return $added;
    }

    /**
     * bionic has "or" locations so figure out the first one and if it could have multiples check if it should also add to the other possible locations
     *
     * @param Bionic $bionic the part to add
     * @param Hero $hero
     */
    private function orLocations(Bionic $bionic, Hero &$hero)
    {
        // get the or locations as a copy so they don't get lost
        $locations = $bionic->bionicLocation->orLocations;

        // shuffle them
        $this->engine->arrayTools->shuffle($locations);

        // remember multiple possible flag
        $multiplePossible = $bionic->bionicLocation->orMultiplePossible;

        // start with 25% of picking multiples (50 / 2)
        $chance = 50;

        do {
            // setup definitive bionic location
            $bionic->bionicLocation = new BionicLocation([array_shift($locations)], false, false, $bionic->bionicLocation->fillsLocation);

            // make a copy
            $this->andLocations(unserialize(serialize($bionic)), $hero);

            // decrease chance of choosing another multiple
            $chance /= 2;
        } while ($multiplePossible && count($locations) && $this->engine->roller->rollDice(new Roll('Bionic Location: Multiple Ors', 1, 100)) < $chance);
    }

    /**
     * check if the location is already filled with a bionic or not (some bionics don't allow any other bionics with them)
     *
     * @param $location string the location to check
     * @param $tryingToFill bool is the new item trying to fill the location
     * @return bool true if the location is open for placement, false if it is already filled
     */
    private function locationNotFilled($location, $tryingToFill)
    {
        $result = true;
        foreach ($this->bionics as $bionic) {
            // find something existing at this location; some bionics don't have a location
            if ($bionic->bionicLocation->andLocations && array_search($location, $bionic->bionicLocation->andLocations) !== false) {
                // base parts like bionic arm / bionic face don't count towards fillable stipulations
                $ignoreFillable = strpos($bionic->title, $location) !== false;

                if ($tryingToFill) {
                    // want to fill this location but anything existing here must be ignored (if there are any other bionics here then can't place here)
                    $result = $result && $ignoreFillable;
                } else {
                    // don't want to fill this location but anything already filling this location prevents from adding this
                    $result = $result && !$bionic->bionicLocation->fillsLocation;
                }
            }
        }
        return $result;
    }

    /**
     * the bionic fills all the locations. check that the locations are available or bionicable and add the part
     *
     * @param $bionic Bionic  part to add
     * @param Hero $hero
     */
    private function andLocations(Bionic $bionic, Hero &$hero)
    {

        // remove cost from budget (will put it back if couldn't place it); this is so further calculations can just go on budget
        $this->budgetRemaining -= $bionic->cost;

        $placed = true;

        // try to make all locations bionic; yes, this makes the location bionic even when filled prevents adding the bionic part. oh well.
        // if the location is bionic then test for the "fills location" flag for that location .
        // if it already has a bionic at that location then cant do "fills location" bionics at that location .
        // motion detector and things that don't have a body location don't require a bionic body part
        if ($bionic->bionicLocation->andLocations) {
            // has to be an "and" location by this point
            foreach ($bionic->bionicLocation->andLocations as $location) {
                // make location bionic and test if the location for the bionic is available
                $placed = $placed && $this->makeLocationBionic($location, $hero)
                    && $this->locationNotFilled($location, $bionic->bionicLocation->fillsLocation);
            }
        }


        // location is ready for business! add the bionic to it
        if ($placed) {
            $this->bionics[] = $bionic;
        } else {
            // not going to work so put its cost back in the budget; yes, the location may have been made bionic but not going to undo that
            $this->budgetRemaining += $bionic->cost;
        }
    }
}