<?php
namespace Heroes\hero\classes;


use Heroes\hero\Bonus;

class RoboticsAddOn
{
    /** @var string name of the addOn */
    public $name;
    /** @var int how much to buy this */
    public $cost;
    /** @var boolean can this only be selected once? */
    public $onlyOne;
    /** @var Bonus if selected, add this bonus to the robot */
    public $bonus;

    public function __construct($name, $cost, $onlyOne = false, Bonus $bonus = null)
    {
        $this->name = $name;
        $this->cost = $cost;
        $this->onlyOne = $onlyOne;
        $this->bonus = $bonus;
    }
}