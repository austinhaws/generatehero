<?php
namespace Heroes\hero;

/**
 * Class Bonus
 * tracks a bonus given to the character; as the character gains abilities and powers they get more powerful, this tracks from where it all came
 */
class Bonus {
    public $bonusType;
    public $value;
    public $explanation;

    /**
     * Bonus constructor.
     * @param $bonusType String - BonusTypes enum what type of bonus?
     * @param $value int/string - what is the benefit of this bonus
     * @param $explanation string - why did they get this bonus?
     */
    function __construct($bonusType, $value, $explanation)
    {
        $this->bonusType = $bonusType;
        $this->value = $value;
        $this->explanation = $explanation;
    }
}