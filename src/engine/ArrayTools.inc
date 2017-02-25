<?php
namespace Heroes\engine;

class ArrayTools
{
    private $engine;

    public function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * unit tests will want to control shuffling so putting this as an object so that it can be overridden
     * @param $array array the array to shuffle
     */
    public function shuffle(&$array)
    {
        shuffle($array);
    }
}