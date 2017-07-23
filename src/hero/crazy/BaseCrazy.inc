<?php
namespace Heroes\hero\crazy;

use Heroes\engine\Engine;
use Heroes\hero\Hero;

abstract class BaseCrazy
{
    /** @var Engine engage. */
    protected $engine;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    abstract function create(Hero &$hero);
}
