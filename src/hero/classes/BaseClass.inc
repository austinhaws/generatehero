<?php
namespace Heroes\hero\classes;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

abstract class BaseClass
{
    protected $engine;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * create this class for this character
     *
     * @param Hero $hero the hero to which this class is attached (done automatically)
     */
    abstract function create(Hero &$hero);

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
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, "Owns car that is $age $years old.", 'Starting Car'));
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
}
