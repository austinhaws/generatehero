<?php

namespace Heroes\engine;

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

    public function setRoller(Roller $roller) {
        $this->roller = $roller;
    }
}