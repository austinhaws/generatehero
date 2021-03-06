<?php

namespace Heroes\engine;

class ArrayTools
{
    /** @var  Engine engineering engineers energetically */
    private $engine;

    public function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * unit tests will want to control shuffling so putting this as an object so that it can be overridden
     *
     * @param $array array the array to shuffle
     * @return array for chaining
     */
    public function shuffle(&$array)
    {
        shuffle($array);
        return $array;
    }

    /**
     * shuffle and pick from a list, list is shrunk by the item picked
     *
     * @param array $list items from which to choose
     * @return mixed the result from the list
     */
    public function pickFromList(&$list)
    {
        $this->shuffle($list);
        return array_pop($list);
    }
}