<?php

namespace Heroes\hero\classes\robotics;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\classes\RoboticsAddOn;
use Heroes\hero\classes\Robotics;
use Heroes\hero\classes\RoboticsBody;
use Heroes\hero\Hero;

class RoboticsBodies
{
    /** @var Engine the engine for engineering the greatest creations known to man! */
    private $engine;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * pick a body and add the body to the robot
     * @param Hero $robot
     * @param int $budget how much is left to spend on this robot
     * @param string $robotType Robotics::ROBOT_TYPE_... constant for type of robot
     * @param $hasPilot boolean true if the robot requires a pilot
     * @return RoboticsBody the selected body
     */
    public function addRobotBody(Hero $robot, &$budget, $robotType, $hasPilot)
    {
        $possibleBodies = $this->possibleBodies($robotType, $hasPilot);
        $bodies = array_filter($possibleBodies, function($body) use ($budget) {
            // filter out bodies that cost too much
            return $body->cost <= $budget;
        });
        // pick a body
        $this->engine->arrayTools->shuffle($bodies);

        $body = array_pop($bodies);
        $budget -= $body->cost;
        $robot->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, $body->name, 'Robotic: body'));


        // pick optional addons
        foreach ($body->addOns as $addOnGroup) {
            // one or none from each category (if category has a $0 option then MUST choose an option)
            $containsFreeby = 0 !== count(array_filter($addOnGroup, function ($addOn) {
                return $addOn->cost === 0;
            }));

            if ($containsFreeby || 1 === $this->engine->roller->rollDice(new Roll('Robotics get addon', 1, 2))) {
                // filter optional addons by remaining budget
                $possibles = array_filter($addOnGroup, function ($addOn) use ($budget) {
                    return $addOn->cost <= $budget;
                });
                $this->engine->arrayTools->shuffle($possibles);
                $addOn = array_pop($possibles);
                $budget -= $addOn->cost;
                $robot->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, $addOn->name, 'Robotics - Body Add On'));
            }
        }

        return $body;
    }

    /**
     * @param $robotType string Robotics::ROBOT_TYPE_... constant for type of robot to filter what bodies are available
     * @return RoboticsBody[] bodies to choose from
     * @param $hasPilot boolean true if the robot requires a pilot
     */
    private function possibleBodies($robotType, $hasPilot)
    {
        $possibleBodies = [];

        // Type 1: Mechanical Body
        // Type 2: Robot
        // Type 3: Exoskeleton
        // Type 4: Android


        // !!!!! Note, names are important because they determine how many legs in Robotics.inc !!!! //

        // ==== Humanoid ==== //
        if ($robotType !== Robotics::ROBOT_TYPE_MECHANICAL) {
            $possibleBodies[] = new RoboticsBody('Basic Humanoid', 250000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 150000),
                ],
            ], true, true, RoboticsBody::TYPE_HUMANOID);
        }

        if ($robotType === Robotics::ROBOT_TYPE_MECHANICAL || $robotType === Robotics::ROBOT_TYPE_ROBOT) {
            $possibleBodies[] = new RoboticsBody('Large Humanoid', 500000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 500000),
                ],
                'seats' => [
                    new RoboticsAddOn('1 person', 0),
                    new RoboticsAddOn('2 persons', 10000),
                    new RoboticsAddOn('3 persons', 30000),
                    new RoboticsAddOn('4 persons', 60000),
                    new RoboticsAddOn('5 persons', 90000),
                ],
            ], true, true, RoboticsBody::TYPE_HUMANOID);

            // ==== Vehicles ==== //
            // compact auto
            $possibleBodies[] = new RoboticsBody('Compact Automobile', 6000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 4000),
                ],
            ], false, false, RoboticsBody::TYPE_VEHICLE);

            // sports car
            $possibleBodies[] = new RoboticsBody('Sports Car', 50000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 5000),
                ],
                'unique' => [
                    new RoboticsAddOn('Unique Design', 80000),
                ]
            ], false, false, RoboticsBody::TYPE_VEHICLE);

            // mid-size sedan
            $possibleBodies[] = new RoboticsBody('Mid-Size Sedan', 8000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 5000),
                ],
                'unique' => [
                    new RoboticsAddOn('Unique Design', 50000),
                ]
            ], false, false, RoboticsBody::TYPE_VEHICLE);

            // jeep
            $possibleBodies[] = new RoboticsBody('Jeep', 12000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 6000),
                ],
                'unique' => [
                    new RoboticsAddOn('Unique Design', 50000),
                ]
            ], false, false, RoboticsBody::TYPE_VEHICLE);

            // mini van
            $possibleBodies[] = new RoboticsBody('Mini Van', 10000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 6000),
                ],
                'unique' => [
                    new RoboticsAddOn('Unique Design', 60000),
                ]
            ], false, false, RoboticsBody::TYPE_VEHICLE);

            // full size van
            $possibleBodies[] = new RoboticsBody('Full-Size Van', 12000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 10000),
                ],
                'unique' => [
                    new RoboticsAddOn('Unique Design', 50000),
                ]
            ], false, false, RoboticsBody::TYPE_VEHICLE);

            // tank
            $possibleBodies[] = new RoboticsBody('Tank', 500000, [
                'unique' => [
                    new RoboticsAddOn('Unique Design', 70000),
                ]
            ], false, false, RoboticsBody::TYPE_VEHICLE);

            // light motorcycle
            $possibleBodies[] = new RoboticsBody('Light Motorcycle', 1000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 2000),
                ],
                'unique' => [
                    new RoboticsAddOn('Unique Design', 30000),
                ]
            ], false, false, RoboticsBody::TYPE_VEHICLE);

            // spherical
            $useLegs = 1 === $this->engine->roller->rollDice(new Roll('Robot uses legs', 1, 2));
            $possibleBodies[] = new RoboticsBody('Basic Spherical Style (ball)', 8000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 6000),
                ],
            ], $useLegs, false, RoboticsBody::TYPE_VEHICLE);
            $possibleBodies[] = new RoboticsBody('Large Spherical Style (ball)', 16000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 12000),
                ],
            ], $useLegs, false, RoboticsBody::TYPE_VEHICLE);

            // cylindrical
            $possibleBodies[] = new RoboticsBody('Basic Cylindrical Style (ie submarine or jet)', 12000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 8000),
                ],
            ], $useLegs, false, RoboticsBody::TYPE_VEHICLE);
            $possibleBodies[] = new RoboticsBody('Large Cylindrical Style (ie submarine or jet)', 20000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 15000),
                ],
            ], $useLegs, false, RoboticsBody::TYPE_VEHICLE);

            // tapered
            $possibleBodies[] = new RoboticsBody('Basic Tapered Cylinder Style', 15000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 9000),
                ],
            ], $useLegs, false, RoboticsBody::TYPE_VEHICLE);
            $possibleBodies[] = new RoboticsBody('Large Tapered Cylinder Style', 24000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 16000),
                ],
            ], $useLegs, false, RoboticsBody::TYPE_VEHICLE);

            // jet
            $possibleBodies[] = new RoboticsBody('Jet Style', 90000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 25000),
                ],
                'unique' => [
                    new RoboticsAddOn('Unique Design', 80000),
                ]
            ], false, false, RoboticsBody::TYPE_VEHICLE);

            // ==== Animals ==== //
            // giant animal: canine
            $possibleBodies[] = new RoboticsBody('Giant Animal: Canine', 100000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 30000),
                ],
            ], true, true, RoboticsBody::TYPE_ANIMAL);

            // giant animal: feline
            $possibleBodies[] = new RoboticsBody('Giant Animal: Feline', 100000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 32000),
                ],
            ], true, true, RoboticsBody::TYPE_ANIMAL);

        }

        if (!$hasPilot) {
            // animals - life like
            $possibleBodies[] = new RoboticsBody('Life like Animal', 125000, [
                'frame' => [
                    new RoboticsAddOn('Light Frame', 0),
                    new RoboticsAddOn('Reinforced Frame', 100000),
                ],
            ], true, true, RoboticsBody::TYPE_ANIMAL);
        }
        return $possibleBodies;
    }
}
