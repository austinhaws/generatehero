<?php
namespace Heroes\tests\utilities;

use Heroes\engine\ArrayTools;

class TestArrayTools extends ArrayTools
{
    const DEFAULT_ROTATION = 1;

    /** @var int how much to rotate the array; move front to back this many times */
    // this pretends to shuffle but does so in an organized way so as to allow unit testing repeatable scenarios
    // set to falsey value to have it do a natural shuffle (tests should probably never do that)
    public $rotation = TestArrayTools::DEFAULT_ROTATION;

    /**
     * @param array $array array to pseudo shuffle
     * @return array the shuffled array, but since it's an addressed parameter it can be used directly instead of the returned result
     */
    public function shuffle(&$array)
    {
        if ($this->rotation) {
            for ($x = 0; $x < $this->rotation; $x++) {
                array_push($array, array_shift($array));
            }
        } else {
            parent::shuffle($array);
        }
        return $array;
    }
}
