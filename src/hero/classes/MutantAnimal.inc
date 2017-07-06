<?php
namespace Heroes\hero\classes;


class MutantAnimal
{
    /** @var  String what type of creature */
    public $name;
    /** @var  String animal definition */
    public $description;
    /** @var  int their starting size level */
    public $initialSize;
    /** @var  String - long, short, medium, uses TableMutantAnimals.BUILD_TYPE_... constants */
    public $buildType;
    /** @var  int how many points to start with */
    public $startingBioE;
    /** @var  array of Bonus character gets all these bonuses no matter what */
    public $bonuses;
    /** @var  array associates locations with MutantAnimalBonus options: powers is the one category that can have multiple choices; uses TableMutantAnimals.POWER_CATEGORY_... constants*/
    public $buyableFeatures;

    public function __construct($name, $description, $initialSize, $buildType, $startingBioE, $bonuses, $buyableFeatures)
    {
        $this->name = $name;
        $this->description = $description;
        $this->initialSize = $initialSize;
        $this->buildType = $buildType;
        $this->buyableFeatures = $buyableFeatures;
        $this->startingBioE = $startingBioE;
        $this->bonuses = $bonuses;
    }
}