<?php

namespace Heroes\hero\classes;

use Heroes\hero\Bonus;

class RoboticsBody
{
    const TYPE_HUMANOID = 'Humanoid';
    const TYPE_VEHICLE = 'Vehicle';
    const TYPE_ANIMAL = 'Animal';

    /** @var string name of the body type */
    public $name;
    /** @var int how much to buy this body */
    public $cost;
    /** @var boolean|[] key/value of RobiticsAddOn[]; each key is a set of which one bonus must be chosen */
    public $addOns;
    /** @var boolean does this robot use legs? if not then it's a vehicle */
    public $usesLegs;
    /** @var boolean animals and humanoids need arms. vehicles could have arms if they want. if needs arms then has to have 2 but could have more */
    public $needsArms;
    /** @var string what type of bod is this: use TYPE_... constants */
    public $type;

    public function __construct($name, $cost, $addOns, $useLegs, $needsArms, $type)
    {
        $this->name = $name;
        $this->cost = $cost;
        $this->addOns = $addOns ? $addOns : [];
        $this->usesLegs = $useLegs;
        $this->needsArms = $needsArms;
        $this->type = $type;
    }
}
