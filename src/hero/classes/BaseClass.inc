<?php
namespace Heroes\hero\classes;

use Heroes\engine\Engine;
use Heroes\hero\Hero;

abstract class BaseClass
{
    protected $engine;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * @return string name of the image for this class
     */
    abstract function imageName();

    /**
     * create this class for this character
     *
     * @param Hero $hero the hero to which this class is attached (done automatically)
     */
    abstract function create(Hero &$hero);
}
