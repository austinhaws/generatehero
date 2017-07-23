<?php
namespace Heroes\hero;

use Heroes\engine\Engine;
use Heroes\engine\Roll;

/**
 * Class Bonus
 * tracks a bonus given to the character; as the character gains abilities and powers they get more powerful, this tracks from where it all came
 */
class Bonus {
    // - ordered in order of operation - //
    // set a flag on the hero; like double carry weight
    const BONUS_TYPE_SET_FLAG = 'flag';

    // set the target to the value
    // Skills use "Set" to show that the skill is added to the character. the bonus will be 0, but just having the "set" means the character gets the skill
    const BONUS_TYPE_SET = 'set';

    // after all is said and done, the value must be at least this value
    const BONUS_TYPE_MINIMUM = 'minimum';

    // add the value to the target
    const BONUS_TYPE_ADD = 'add';

    // multiply the target by the value of the bonus; don't forget to floor the value
    const BONUS_TYPE_MULTIPLY = 'multiply';


    /** @var string use BONUS_TYPE constants */
    public $bonusType;

    /** @var string what attribute/skill/etc is being targeted for the bonus? use BonusTargets enum */
    public $bonusTarget;

    /** @var array|Roll|int the value of the bonus; can be a number or a Roll; use getValue() to get the value no matter if roll or not */
    public $value;

    /** @var string why are they getting this bonus? */
    public $explanation;

    /**
     * Bonus constructor.
     * @param $bonusType string - add or set?
     * @param $bonusTarget string - BonusTargets enum what type of bonus?
     * @param $value int|Roll|array - what is the benefit of this bonus? Roll objects are lazy rolled at the time they are needed; array of table entries rolled if needed
     * @param $explanation string - why did they get this bonus?
     */
    function __construct($bonusType, $bonusTarget, $value, $explanation)
    {
        $this->bonusType = $bonusType;
        $this->bonusTarget = $bonusTarget;
        $this->value = $value;
        $this->explanation = $explanation;
    }

    /**
     * if value is a roll, roll it, otherwise return the value
     * @param Engine $engine will use roller out of the engine
     * @return int|String the value of the bonus
     */
    public function getValue(Engine $engine) {
        if ($this->value instanceof Roll) {
            $this->value = $engine->roller->rollDice($this->value);
        }
        return $this->value;
    }
}