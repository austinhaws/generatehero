<?php
namespace Heroes\hero\crazy;

use Heroes\engine\Engine;

abstract class BaseCrazy
{
    protected $engine;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    abstract function create();
}
