<?php
namespace Heroes\tables;

use Heroes\engine\Engine;

class TableBase
{
    /** @var Engine here I am baby */
    protected $engine;

    public function __construct(Engine $engine)
    {
        if (!$engine) {
            throw new Exception('Engine is required in constructor');
        }
        $this->engine = $engine;
    }

}