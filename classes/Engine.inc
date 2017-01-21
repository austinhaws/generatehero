<?php

require_once 'classes/Roller.inc';

/**
 * Class Engine
 *
 * contains the guts of the engine that tables/rolling/everything can use to get the job done
 */
class Engine {
    public $roller;

    public function __construct()
    {
        $this->roller = new Roller();
    }
}