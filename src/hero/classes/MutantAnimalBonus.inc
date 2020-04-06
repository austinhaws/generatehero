<?php
namespace Heroes\hero\classes;


use Heroes\hero\Bonus;
use RuntimeException;

class MutantAnimalBonus
{
    /** @var  String */
    public $name;
    /** @var  int */
    public $cost;
    /** @var  array */
    public $bonuses;

    public function __construct($name, $cost, $bonuses)
    {
        $this->name = $name;
        $this->cost = $cost;
        if ($bonuses === false) {
            $bonuses = [];
        }
        if ($bonuses instanceof Bonus) {
            $bonuses = [$bonuses];
        }
        if (!is_array($bonuses)) {
            var_dump($bonuses);
            throw new RuntimeException('MutantAnimalBonus->bonuses must be an array.');
        }
        $this->bonuses = $bonuses;
    }
}
