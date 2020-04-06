<?php
namespace Heroes\tables;

use Heroes\engine\Engine;
use RuntimeException;

class TableBase
{
    /** @var Engine here I am baby */
    protected $engine;

    public function __construct(Engine $engine)
    {
        if (!$engine) {
            throw new RuntimeException('Engine is required in constructor');
        }
        $this->engine = $engine;
    }

}
