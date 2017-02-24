<?php
namespace Heroes\engine;
use Heroes\enums\SkillPrograms;

/**
 * Class Engine
 *
 * contains the guts of the engine that tables/rolling/everything can use to get the job done
 */
class Engine
{
    public $roller;
    public $tableRoller;
    public $skillPrograms;

    public function __construct()
    {
        $this->roller = new Roller();
        $this->tableRoller = new TableRoller($this);
        $this->skillPrograms = new SkillPrograms($this);
    }
}