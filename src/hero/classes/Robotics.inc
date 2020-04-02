<?php

namespace Heroes\hero\classes;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\classes\robotics\RoboticsBodies;
use Heroes\hero\classes\robotics\RoboticsEducation;
use Heroes\hero\Hero;

class Robotics extends BaseClass
{

    const ROBOT_TYPE_MECHANICAL = 'Mechanical';
    const ROBOT_TYPE_ROBOT = 'Robot';
    const ROBOT_TYPE_EXOSKELETON = 'Exoskeleton';
    const ROBOT_TYPE_ANDROID = 'Android';

    /** @var Hero the robot being constructed, null if the hero IS the robot */
    public $robot;
    /** @var bool true if someone has to fly/drive/pilot the robot; false if an artifical intelligence is required */
	public $requiresPilot;
    /** @var bool true if this robot needs an artifical intelligence */
	public $requiresAI;
    /** @var string sponsor */
	public $sponsoringOrganization;
    /** @var string Superiority of the Robot System */
	public $robotSuperiority;
    /** @var string Status With the Sponsoring Organization */
	public $sponsorStatus;

    public function __construct(Engine &$engine)
    {
        parent::__construct($engine, 'Robotic');
    }

    /**
     * create a character's class
     *
     * @param Hero $hero the hero
     * @param bool|array $options 'isAlien' means to not do class bonuses, just build a robot
     * @throws \Exception ya ya, whatever
     */
    public function create(Hero &$hero, $options = false)
    {
        list($this->classSubtype, $this->requiresPilot, $this->requiresAI) = $this->engine->tableRoller->rollTable('Robot Type', [
            new TableEntry(1, [Robotics::ROBOT_TYPE_MECHANICAL, true, false]),
            new TableEntry(2, [Robotics::ROBOT_TYPE_ROBOT, false, true]),
            new TableEntry(3, [Robotics::ROBOT_TYPE_ROBOT, true, true]),
            new TableEntry(4, [Robotics::ROBOT_TYPE_EXOSKELETON, true, false]),
            new TableEntry(5, [Robotics::ROBOT_TYPE_ANDROID, false, true]),
        ]);

        if ($this->requiresPilot) {
            $this->robot = new Hero();
            $useRobot = &$this->robot;

            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Robotics: personal cash', 4, 4, 100), 'Robotics: personal cash'));
            $this->hasCar($hero, 86);
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 20, 'Robotics: base SDC'));
        } else {
            $useRobot = &$hero;
        }

        // Step one: budget
        $budget = $this->determineBudget();
        // Step two: intelligence
        if ($this->requiresAI) {
            $this->pickIntelligence($useRobot, $budget);
        }

        // Step three: select body
        $robotBody = (new RoboticsBodies($this->engine))->addRobotBody($useRobot, $budget, $this->classSubtype, $this->requiresPilot);
        // Step four: construct robot
        // Selection A - body types
            // done with body building

        // Selection B - power supply
        $this->pickPowerSupply($useRobot, $budget);

        // Selection C - legs/locomotion
        if ($robotBody->usesLegs) {
            $this->pickLegs($useRobot, $budget, $robotBody);
        } else {
            $this->pickVehicleLocomotion($useRobot, $budget);
        }

        // Selection D - arms/hands
        $this->pickArmsHands($useRobot, $budget, $robotBody);

        switch ($robotBody->type) {
            case RoboticsBody::TYPE_VEHICLE:
                $baseSDC = 400;
                break;
            case RoboticsBody::TYPE_HUMANOID:
            case RoboticsBody::TYPE_ANIMAL:
                $baseSDC = 200;
                break;
            default:
                var_dump($robotBody);
                throw new \Exception('Unknown robotBody type: ' . $robotBody->type);
        }

        $useRobot->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, $baseSDC, 'Robotics: Base SDC'));
        $useRobot->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::NATURAL_ARMOR_RATING, 6, 'Robotics: Base Armor Rating'));

        // blow rest of money on these categories
        $this->buyNovelties($useRobot, $robotBody, $budget);

        // Step five: artificial intelligence
            // done in step 2

        if (!$this->optionValue($options, 'isAlien')) {
            // Step six: background data
            $this->backgroundData();

            // Step seven: human pilot stuff
            if ($this->requiresPilot) {
                $this->humanPilotStuff($hero);
            }
        }
    }

    /**
     * @throws \Exception
     */
    private function backgroundData()
    {
        $this->sponsoringOrganization = $this->engine->tableRoller->rollTable('Robotics: Sponsoring organization', [
           new TableEntry(39, 'Private Industry'),
           new TableEntry(48, 'Secret Organization: Private experimentation to further the study of robotics'),
           new TableEntry(57, 'Secret Organization: Criminal'),
           new TableEntry(66, 'Secret Organization: Crime-fighting'),
           new TableEntry(75, 'Secret Organization: Military'),
           new TableEntry(100, 'Military'),
        ]);

        $this->robotSuperiority = $this->engine->tableRoller->rollTable('Robotics: Superiority', [
           new TableEntry(20, 'Experimental Model: Laboratory tests unfinished, but field test has been pushed ahead as the result of budget cuts.'),
           new TableEntry(40, 'Prototype: The only one in existence. Lab tests completed; field testing required.'),
           new TableEntry(65, 'Project abandoned due to lack of finances. The only existing, working model has been salvaged and is being used for personal motives (crime-fighting, crime, etc.). Officially, does not exist.'),
           new TableEntry(86, 'Unauthorized field use of advanced model. A quality working system.'),
           new TableEntry(100, 'Unauthorized use of final, advanced field perfect, finished robot with flawless operations.'),
        ]);

        $this->sponsorStatus = $this->engine->tableRoller->rollTable('Robotics: Sponsor Status', [
           new TableEntry(19, 'Allowed to leave; very good, friendly relationship.'),
           new TableEntry(41, 'Allowed to leave after a great antagonism/conflict. Not friendly, but may aid the character.'),
           new TableEntry(64, 'Thrown out of the program. All ties are permanently dissolved; very angry/hostile toward the character.'),
           new TableEntry(89, 'Ran away; secretly hunted by the organization. Hostile but not necessarily deadly.'),
           new TableEntry(100, 'Ran away; considered to be a criminal and/or extremely dangerous. Hunted by law enforcement agencies and the organization'),
        ]);
    }

    /**
     * @return int budget for building the robot
     * @throws \Exception
     */
    private function determineBudget() {
        return $this->engine->tableRoller->rollTable('Robotics - budget', [
            new TableEntry(15, 1500000),
            new TableEntry(30, 8500000),
            new TableEntry(44, 9000000),
            new TableEntry(59, 9500000),
            new TableEntry(74, 10000000),
            new TableEntry(89, 11000000),
            new TableEntry(100, 12000000),
        ]);
    }

    /**
     * @param Hero $robot the hero/robot to which to add an AI
     * @param int $budget how much money available; how much money left when function is done
     * @throws \Exception
     */
    private function pickIntelligence(Hero &$robot, &$budget)
    {
        // get available AI types
        $aiTypes = array_filter([
            new TableEntry(1, [185000, 'Standard AI', 'Computer brain with a limited scope of intelligence. Act very natural, human, and intelligent.']),
            new TableEntry(2, [2250000, 'Advanced AI', 'Almost human. Formulate ideas, conjecture, and theory.']),
            new TableEntry(3, [1200000, 'Transferred AI', 'Human intellect/consciousness transferred out of the human body and in to a robot.']),
        ], function(TableEntry $tableEntry) use ($budget) {
            return $tableEntry->result[0] <= $budget;
        });
        $this->engine->arrayTools->shuffle($aiTypes);

        // select an AI type
        list($cost, $title, $description) = array_pop($aiTypes)->result;

        // record the selection
		$robot->robotAI = $title;
		$robot->robotAIDescription = $description;

        // education
        $robot->addSkill(BonusTargets::SKILL_MATHEMATICS_BASIC, 'Robot AI', 98);
        $robot->addSkill(BonusTargets::SKILL_MATHEMATICS_ADVANCED, 'Robot AI', 98);
        (new RoboticsEducation($this->engine))->create($robot);

        $personality = $this->engine->tableRoller->rollTable('Robot AI: Personality', [
            new TableEntry(10, 'Strong quiet type; loyal, confident, friendly, but a robot of few words.'),
            new TableEntry(18, 'Snide, arrogant, feels superior; snob.'),
            new TableEntry(27, 'Paternal, friendly, but overly protective of humans.'),
            new TableEntry(36, 'Gung-ho, friendly, dynamic, cheerful; quick to act.'),
            new TableEntry(45, 'Complainer and worry-wan; has an annoying whining tone in its voice most of the time.'),
            new TableEntry(54, 'Street urchin, gruff, street-wise type; uses much slang in its vocabulary.'),
            new TableEntry(63, 'Mr. Protocol; letter perfect in appearance, manner, language and demeanor. English accent optional.'),
            new TableEntry(72, 'Smart-mouth, cocky, wisecracker, sarcastic.'),
            new TableEntry(81, 'Easy-going, laid back; trusts almost anyone until they are proven unworthy of trust.'),
            new TableEntry(90, 'Braggart, cocky, exaggerates, usually cheerful, but annoying.'),
            new TableEntry(100, 'Friendly, courteous, hospitable.'),
        ]);
        $robot->robotAIPersonality = $personality;

        $budget -= $cost;
    }

    /**
     * @param Hero $hero load 'im up
     */
    private function humanPilotStuff(Hero &$hero)
    {
        // 4d4*100 dollars
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Robotics: Bonus Money', 4, 6, 100), 'Robotics: Bonus Money'));

        // 84% car
        $this->hasCar($hero, 84);

        // 20 base SDC
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 20, 'Robotics: Base SDC'));
    }

    /**
     * @param $useRobot Hero the robot to which to add a power supply
     * @param $budget int how much money the is left to spend
     */
    private function pickPowerSupply(Hero &$useRobot, &$budget)
    {
        $supplies = array_filter([
            [250000, 'Liquid Fuel - Uses a consumable fuel that must be continually replaced'],
            [1000000, 'Super Solar Energy - Collects sunlight'],
            [2500000, 'Fusion Power System - Never needs refueling'],
            [3200000, 'Micro-Fusion Power System - Fusion that fits in the smallest robot'],
        ], function ($powerSupply) use ($budget) {
            return $powerSupply[0] <= $budget;
        });

        if (count($supplies)) {
            $this->engine->arrayTools->shuffle($supplies);
            $powerSupply = array_pop($supplies);
            $budget -= $powerSupply[0];
            $useRobot->robotPowerSupply = $powerSupply[1];
        } else {
        	$useRobot->robotPowerSupply = null;
		}
    }

    /**
     * @param $useRobot Hero the robot to which to add legs
     * @param $budget int how much money can be spent (gets updated with money left)
     * @param $robotBody RoboticsBody the body of the robot
     * @throws \Exception you suck!
     */
    private function pickLegs(Hero &$useRobot, &$budget, $robotBody)
    {
        switch ($robotBody->type) {
            case RoboticsBody::TYPE_HUMANOID:
                $numberLegs = 2;
                $anotherLegOdds = 10;
                break;
            case RoboticsBody::TYPE_ANIMAL:
                $numberLegs = 4;
                $anotherLegOdds = 15;
                break;
            case RoboticsBody::TYPE_VEHICLE:
                $numberLegs = 0;
                $anotherLegOdds = 5;
                break;
            default:
                var_dump($robotBody);
                throw new \Exception('Unknown robot body type' . $robotBody->type);
        }

        // just doing average 250000 per leg otherwise it gets really weird
        $legCost = 250000;
        while (($budget >= (($numberLegs + 1) * $legCost)) &&
            ($this->engine->roller->rollDice(new Roll('Robotics - Legs: extras', 1, 100)) <= $anotherLegOdds)) {
            $numberLegs++;
            $anotherLegOdds -= 5;
        }
        $numberLegs = min($numberLegs, floor($budget / $legCost));
		$useRobot->robotNumberLegs = $numberLegs;
		$budget -= $numberLegs * $legCost;
    }

    /**
     * A power supply gives power to the engine, the engine is what makes the vehicle go
     *
     * @param Hero $useRobot the robot to which to add a propulsion
     * @param int $budget how much money is left to spend
     */
    private function pickVehicleLocomotion(Hero &$useRobot, &$budget)
    {
        $possibles = array_filter([
            [25000, 'Standard Engine'],
            [50000, 'Turbo Engine'],
            [250000, 'Jet Engine'],
            [250000, 'Small Hover Jet'],
            [1000000, 'Concealed Micro Hover System'],
            [500000, 'Hover Jet'],
            [700000, 'Concealed Hover Jet'],
            [340000, 'Concealed Helicopter VTOL System'],
        ], function ($engine) use ($budget) {
            return $engine[0] <= $budget;
        });

        if (count($possibles)) {
            $this->engine->arrayTools->shuffle($possibles);
            $engine = array_pop($possibles);
            $budget -= $engine[0];
            $useRobot->robotEngine = $engine[1];
        } else {
            $useRobot->robotEngine = null;
		}
    }

    /**
     * @param Hero $useRobot gimme some arms, baby
     * @param int $budget how much money is available to spend
     * @param RoboticsBody $robotBody the body information
     * @throws \Exception bad news
     */
    private function pickArmsHands(Hero &$useRobot, &$budget, $robotBody)
    {
        switch ($robotBody->type) {
            case RoboticsBody::TYPE_HUMANOID:
                $numberArms = 2;
                $anotherArmOdds = 0;
                break;
            case RoboticsBody::TYPE_ANIMAL:
                $numberArms = 0;
                $anotherArmOdds = 10;
                break;
            case RoboticsBody::TYPE_VEHICLE:
                $anotherArmOdds = 25;
                $numberArms = 0;
                break;
            default:
                var_dump($robotBody);
                throw new \Exception('Unknown robot body type' . $robotBody->type);
        }

        $armCost = 150000;
        $numberArms = min($numberArms, $budget / $armCost);
		while (($numberArms + 1) * $armCost <= $budget &&
			$this->engine->roller->rollDice(new Roll('Robotics - Arms: extras', 1, 100)) <= $anotherArmOdds) {
			$numberArms++;
		}
        if ($numberArms) {
            $budget -= $armCost * $numberArms;
			$useRobot->robotArms = [];
			$useRobot->robotArmsInterchangeableHands = [];
			while ($numberArms-- > 0) {
                $this->addArm($useRobot, $budget);
            }
        }
    }

    /**
     * robot does want an arm so give it an arm and see if it can be supped up a bit
     *
     * @param Hero $useRobot the robot to which to add the arm
     * @param int $budget how much money is available, how much is left after function is called
     */
    private function addArm(Hero &$useRobot, &$budget)
    {
        // Detachable Remote Controlled Limb
        if ($budget >= 100000 && 10 >= $this->engine->roller->rollPercent('Robot arm - detachable remote')) {
        	$useRobot->robotArms[] = 'Detachable Remote Controlled Limb - flies via hover system';
            $budget -= 100000;

            // Interchangeable Hand
        } else if ($budget >= 100000 && 10 >= $this->engine->roller->rollPercent('Robot arm - interchangeable')) {
        	$useRobot->robotArms[] = 'Arm with interchangeable hands';

            $interchangeableOdds = 33;
            // electromagnetic clamp
            if ($interchangeableOdds >= $this->engine->roller->rollPercent('Robot interchangeable arm: Electromagnetic Clamp')) {
				$useRobot->robotArmsInterchangeableHands[] = 'Electromagnetic Clamp via a two finger claw';
                $budget -= 90000;
            }

            // buzz - saw
            if ($interchangeableOdds >= $this->engine->roller->rollPercent('Robot interchangeable arm: Buzz-Saw')) {
				$useRobot->robotArmsInterchangeableHands[] = 'Buzz-Saw does 2D6 damage';
                $budget -= 10000;
            }

            // high-powered drill
            if ($interchangeableOdds >= $this->engine->roller->rollPercent('Robot interchangeable arm: High-Powered Drill')) {
				$useRobot->robotArmsInterchangeableHands[] = 'High-Powered Drill with 40 different bits. Does 1D8 damage';
                $budget -= 10000;
            }

            // police style lock release gun
            if ($interchangeableOdds >= $this->engine->roller->rollPercent('Robot interchangeable arm: Police Style Lock Release Gun')) {
				$useRobot->robotArmsInterchangeableHands[] = 'Police Style Lock Release Gun';
                $budget -= 150000;
            }

            // towline
            if ($interchangeableOdds >= $this->engine->roller->rollPercent('Robot interchangeable arm: Towline')) {
				$useRobot->robotArmsInterchangeableHands[] = 'Towline and grappling hook launcher';
                $budget -= 25000;
            }

            // acetylene torch
            if ($interchangeableOdds >= $this->engine->roller->rollPercent('Robot interchangeable arm: Acetylene Torch')) {
				$useRobot->robotArmsInterchangeableHands[] = 'Acetylene Torch does 1D6 damage';
                $budget -= 20000;
            }

            // weapon
            if ($interchangeableOdds >= $this->engine->roller->rollPercent('Robot interchangeable arm: Weapon')) {
				$useRobot->robotArmsInterchangeableHands[] = 'Weapon mounted in place of a hand';
                $budget -= 20000;
            }

        // utility arms
        } else if ($budget >= 100000 && 50 >= $this->engine->roller->rollPercent('Robot Utility Arm')) {
            $budget -= 100000;
            if ($budget >= 25000 && 50 >= $this->engine->roller->rollPercent('Robot Utility Arm - concealed')) {
            	$useRobot->robotArms[] = 'Concealed Utility (small, retractable, concealed)';
                $budget -= 25000;
            } else {
            	$useRobot->robotArms[] = 'Utility (small, retractable)';
                $budget -= 25000;
            }
        } else if (10 >= $this->engine->roller->rollPercent('Robot Tentacle Arm')) {
			$useRobot->robotArms[] = 'Tentacle';
            $budget -= 100000;
        } else {
			$useRobot->robotArms[] = 'Standard Arm';
        }
    }

    private function pickSensors()
    {
        return [
            new RoboticsAddOn('Advanced Audio System - stereo, amplified hearing, wide-band radio receiver, inaudible frequency ranges', 390000, true),
            new RoboticsAddOn('Basic Listening System - Human-like Stereo Hearing, narrow-band radio receiver', 120000, true),
            new RoboticsAddOn('Bug Detector', 5000, true),
            new RoboticsAddOn('Radar Signal Detector', 10000, true),
            new RoboticsAddOn('Wide-Band Radio Receiver and Transmitter', 50000, true),
            new RoboticsAddOn('Radio Signal Scrambler System', 10000, true),
            new RoboticsAddOn('External Audio Pick-Up - amplifies sound', 10000, true),
            new RoboticsAddOn('Audio Recorder', 5000, true),
            new RoboticsAddOn('Loud Speaker', 5000, true),
            new RoboticsAddOn('Single Voice Synthesizer - robot has human sounding voice', 30000, true),
            new RoboticsAddOn('Modulating Voice Synthesizer - robot can imitate voices', 100000, true),
            new RoboticsAddOn('Sound Analysis Computer - listen, recognize, and analyze sounds', 475000, true),
            new RoboticsAddOn('Inaudible Frequency Transmission', 80000, true),
        ];
    }

    private function pickOptics(RoboticsBody $robotBody)
    {
        $options = [
            new RoboticsAddOn('Basic Optic System - Color sight with analysis', 300000, true),
            new RoboticsAddOn('Advanced Optic System - Color vision, analysis, nightsight, infrared, and ultraviolet', 425000, true),
            new RoboticsAddOn('Infrared Vision', 70000, true),
            new RoboticsAddOn('Night Sight', 90000, true),
            new RoboticsAddOn('Laser Targeting System - +3 strike with distance weapons', 300000, true),
            new RoboticsAddOn('Targeting Sight - +1 to strike', 50000, true),
            new RoboticsAddOn('Telescopic Vision', 35000, true),
            new RoboticsAddOn('Thermo-Imager', 180000, true),
            new RoboticsAddOn('Ultraviolet Sight', 30000, true),
            new RoboticsAddOn('External Video and Audio Surveillance', 40000, true),
            new RoboticsAddOn('Video Receiver and Transmitter - Receive and send video and TV transmissions', 80000, true),
            new RoboticsAddOn('Searchlight', 30000, true),
        ];
        if ($robotBody->type === RoboticsBody::TYPE_ANIMAL || $robotBody->type === RoboticsBody::TYPE_HUMANOID) {
            $options = array_merge($options, [
                new RoboticsAddOn('Camera Eye', 3500, true),
                new RoboticsAddOn('Spotlight Eye Beam', 40000, true),
            ]);
        }
        return $options;
    }

    private function pickWeapons($robotBody)
    {
        $weapons = [];

        // eye weapons
        if ($robotBody->type === RoboticsBody::TYPE_ANIMAL || $robotBody->type === RoboticsBody::TYPE_HUMANOID) {
            $weapons = array_merge($weapons, [
                new RoboticsAddOn('Eye Laser - 2D6 damage', 400000, false),
                new RoboticsAddOn('Eye Ion Blaster - 2D4 damage', 400000, false),
                new RoboticsAddOn('Eye Light Beam - harmless flashlight', 400000, false),
            ]);
        }

        // humanoid
        if ($robotBody->type === RoboticsBody::TYPE_HUMANOID) {
            $weapons = array_merge($weapons, [
                new RoboticsAddOn('Knuckle Spikes - can be fired from the four knuckles - 1D4 damage', 50000, true),
                new RoboticsAddOn('Wrist or Palm Spikes - Needle-like spikes fired from wrist or palm - 1D4 damage', 30000, true),
                new RoboticsAddOn('Finger Gun - 2D6 damage', 10000, true),
                new RoboticsAddOn('Finger Blaster - 2D4 damage', 100000, true),
                new RoboticsAddOn('Wrist Blaster - 3D6 damage', 300000, true),
                new RoboticsAddOn('Electrical Discharge - 4D6 damage', 50000, false),
                new RoboticsAddOn('Spike and Towline', 40000, true),
                new RoboticsAddOn('Large Retractable Blades - 3D6 damage', 90000, true),
                new RoboticsAddOn('Ion Rod - 3D6 damage', 350000, false),
                new RoboticsAddOn('Concealed Ion Rod - 3D6 damage', 400000, false),
                new RoboticsAddOn('Laser Rod - 4D6 damage', 400000, false),
                new RoboticsAddOn('Concealed Laser Rod - 4D6 damage', 500000, false),
                new RoboticsAddOn('Mini-Laser - 2D4 damage', 200000, false),
                new RoboticsAddOn('Flame Thrower - 3D6 damage; 60% combusting', 50000, false),

                new RoboticsAddOn('Chemical Spray - Blind: 3D4 melees', 70000, true),
                new RoboticsAddOn('Chemical Spray - Tear Gas: 4D6 melees', 70000, true),
                new RoboticsAddOn('Chemical Spray - Burning Vapor: 1D4 damage', 70000, true),
                new RoboticsAddOn('Chemical Spray - CO2 Foam: extinguish fires', 70000, true),
            ]);
        }

        // vehicle weapons
        if ($robotBody->type === RoboticsBody::TYPE_VEHICLE) {
            $weapons = array_merge($weapons, [
                new RoboticsAddOn('7.62mm Machinegun; 5D6 damage', 3000, false),
                new RoboticsAddOn('.50 Calibre Machinegun; 7D6 damage', 10000, false),
                new RoboticsAddOn('40mm Grenade Launcher; 3D4X10 damage', 40000, false),

                new RoboticsAddOn('Missile Launcher Pod - High Explosive; 2D6 X 10', 301000, true),
                new RoboticsAddOn('Missile Launcher Pod - Fragmentation; 2D6 X 10', 301000, true),
                new RoboticsAddOn('Missile Launcher Pod - Armor Piercing; 1D6 X 10', 301000, true),
                new RoboticsAddOn('Missile Launcher Pod - Napalm; 1D6 X 10', 301000, true),
                new RoboticsAddOn('Missile Launcher Pod - Tear Gas', 301000, true),
                new RoboticsAddOn('Missile Launcher Pod - Knock-Out Gas', 301000, true),
                new RoboticsAddOn('Missile Launcher Pod - Smoke', 301000, true),
                new RoboticsAddOn('Missile Launcher Pod - Fire Retardant', 301000, true),

                new RoboticsAddOn('Mini-Laser - 3D6', 400000, true),
                new RoboticsAddOn('Heavy-Duty Laser Blaster - 6D6', 850000, true),
                new RoboticsAddOn('Heavy-Duty Ion Blaster - 5D6', 700000, true),
                new RoboticsAddOn('Particle Beam Blaster - 2D4X10', 1500000, true),
            ]);
        }

        // animal features
        if ($robotBody->type === RoboticsBody::TYPE_VEHICLE) {
            $weapons = array_merge($weapons, [
                new RoboticsAddOn('Claws - 1D6 damage', 10000, true),
                new RoboticsAddOn('Retractable Claws - 1D6 damage', 20000, true),
                new RoboticsAddOn('Fangs - 1D6 + 4 damage', 8000, true),
                new RoboticsAddOn('Prehensile Tail', 100000, true),
            ]);
        }

        return $weapons;
    }

    private function pickPilotOperatedSystems($requiresPilot)
    {
        return array_merge([
            new RoboticsAddOn('Radiation Shielding', 50000, true),
            new RoboticsAddOn('Underwater Capabilities', 300000, true),
            new RoboticsAddOn('Flotation Device', 150000, true),
            new RoboticsAddOn('Refrigerator', 1000, true),
            new RoboticsAddOn('Electric Grill', 1000, true),
            new RoboticsAddOn('Microwave Oven', 1000, true),
            new RoboticsAddOn('Provisions Storage', 2000, true),
            new RoboticsAddOn('Stereo System', 1200, true),
        ],
            $requiresPilot ? [
                new RoboticsAddOn('Reinforced Pilot\'s Compartment', 100000, true),
                new RoboticsAddOn('Escape Capsule', 500000, true),
                new RoboticsAddOn('Pressurized Cabin', 200000, true),
                new RoboticsAddOn('Life Support Unit', 100000, true),
            ] : []);
    }

    private function pickOtherAvailableFeatures()
    {
        return [
            new RoboticsAddOn('Body Armor - +10 SDC', 10000, false, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 10, 'Robotics: SDC')),
            new RoboticsAddOn('Armor Rating - +1 AR', 100000, false, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::NATURAL_ARMOR_RATING, 1, 'Robotics: Armor Rating')),
        ];
    }

    private function pickMiscellaneous($robotBody)
    {
        return array_merge([
            new RoboticsAddOn('Remote Probe - concealed and launched when needed', 10000, true),
            new RoboticsAddOn('Secret Compartments', 8000, true),
            new RoboticsAddOn('Touch Sensing Systems - Closely simulates teh human sense of touch', 1000000, true),
        ],
            $robotBody->type !== RoboticsBody::TYPE_VEHICLE ? [
                new RoboticsAddOn('Locking Joints', 20000, true),
                new RoboticsAddOn('360 Degree Rotating Body Segment', 40000, true),
                new RoboticsAddOn('Artificual Blood System', 500000, true),
                new RoboticsAddOn('Cosmetic Enhancement - Realistic Skin', 250000, true),
                new RoboticsAddOn('Cosmetic Enhancement - Real Head Hair Implanted', 5000, true),
                new RoboticsAddOn('Cosmetic Enhancement - Real Body Hair', 40000, true),
                new RoboticsAddOn('Cosmetic Enhancement - Real Fur', 25000, true),
                new RoboticsAddOn('Cosmetic Enhancement - Realistic Eyes', 50000, true),
                new RoboticsAddOn('Sculpted Facial Features', 150000, true),
                new RoboticsAddOn('Minor Body Characteristics - Nails, fangs, beard stubble, moles, pimples, scars, etc', 8000, true),
            ] : []);
    }

    /**
     * @param Hero $useRobot add items to this robot
     * @param RoboticsBody $robotBody what type of body the robot has
     * @param int $budget how much omney is available to spend; how much is left when function is done
     */
    private function buyNovelties(Hero &$useRobot, RoboticsBody $robotBody, &$budget)
    {
        /** @var RoboticsAddOn[] $options */
        $options = array_merge(
        // Selection E - sensors/optics
            $this->pickSensors(),
            $this->pickOptics($robotBody),

            // Selection F - weapons
            $this->pickWeapons($robotBody),

            // other available features
            $this->pickOtherAvailableFeatures(),

            // pilot operated systems
            $this->requiresPilot ? $this->pickPilotOperatedSystems($this->requiresPilot) : [],

            // miscellaneous
            $this->pickMiscellaneous($robotBody)
        );

        $this->engine->arrayTools->shuffle($options);
        do {
            $option = array_pop($options);
            if ($option->cost <= $budget) {
                // add option to robot
                $budget -= $option->cost;
                $useRobot->robotOptions[] = $option->name;
                if ($option->bonus) {
                    $useRobot->addBonus($option->bonus);
                }

                // if can buy this option again then put it back in the list
                if (!$option->onlyOne) {
                    array_push($options, $option);
                    $this->engine->arrayTools->shuffle($options);
                }
            }
        } while (count($options) && $budget > 0);
    }
}
