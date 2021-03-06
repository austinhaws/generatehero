<?php
namespace Heroes\hero\classes;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

abstract class BaseClass
{
    /** @var Engine only your engine can save you */
    protected $engine;
    /** @var string the title for the class */
    public $classType;
    /** @var string subtype of the class */
    public $classSubtype = false;

    /**
     * BaseClass constructor.
     * @param Engine $engine engine for running the randomness
     * @param string $classType the title of the class
     */
    function __construct(Engine &$engine, $classType)
    {
        $this->engine = $engine;
        $this->classType = $classType;
    }

    /**
     * create this class for this character
     *
     * @param Hero $hero the hero to which this class is attached (done automatically)
     * @param array|bool $options key/value pairs of options to pass around as needed (probably sparingly)
     */
    abstract function create(Hero &$hero, $options = false);

    /**
     * some classes duplicate this check for owning a car
     *
     * @param Hero $hero the hero to which a car may belong
     * @param int $percentChance chance that the character owns a car
     */
    protected function hasCar(Hero &$hero, $percentChance)
    {
        if ($this->engine->roller->rollDice(new Roll('Has Car?', 1, 100)) <= $percentChance) {
            $age = $this->engine->roller->rollDice(new Roll('Car Age', 1, 6));
            $years = 'year' . ($age > 1 ? 's' : '');
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, "Owns car that is $age $years old", 'Starting Car'));
        }
    }

    /**
     * after character is created, this function gets called; psionics needs the final ME for ISP Points
     *
     * @param Hero $hero
     */
    public function postCreate(Hero &$hero)
    {
        // default to do nothing
    }

    /**
     * @param bool|array $options options passed to create function
     * @param string $field the field to pull out of the options
     * @return null|object|bool|string|int whatever the value is in the option
     */
    protected function optionValue($options, $field) {
        return ($options && isset($options[$field])) ? $options[$field] : null;
    }
}
