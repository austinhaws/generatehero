<?php
namespace Heroes\hero;

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
    const BONUS_TYPE_SET = 'set';

    // add the value to the target
    const BONUS_TYPE_ADD = 'add';

    // multiply the target by the value of the bonus; don't forget to floor the value
    const BONUS_TYPE_MULTIPLY = 'multiply';

    // just a bonus something that is not numeric that the character gains
    const BONUS_TYPE_STRING = 'string';




    // use BONUS_TYPE constants
    public $bonusType;

    // what attribute/skill/etc is being targeted for the bonus? use BonusTargets enum
    public $bonusTarget;

    // the value of the bonus; can be a number or a Roll
    public $value;

    // why are they getting this bonus?
    public $explanation;

    /**
     * Bonus constructor.
     * @param $bonusType string - add or set?
     * @param $bonusTarget string - BonusTargets enum what type of bonus?
     * @param $value int|Roll - what is the benefit of this bonus? Roll objects are lazy rolled at the time they are needed
     * @param $explanation string - why did they get this bonus?
     */
    function __construct($bonusType, $bonusTarget, $value, $explanation)
    {
        $this->bonusType = $bonusType;
        $this->bonusTarget = $bonusTarget;
        $this->value = $value;
        $this->explanation = $explanation;
    }
}