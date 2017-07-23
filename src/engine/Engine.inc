<?php
namespace Heroes\engine;
use Heroes\enums\SkillPrograms;
use Heroes\tests\utilities\TestRoller;

/**
 * Class Engine
 *
 * contains the guts of the engine that tables/rolling/everything can use to get the job done
 */
class Engine
{
    /** @var  Roller|TestRoller rolls dice */
    public $roller;
    /** @var TableRoller rolls on a table of possible results */
    public $tableRoller;
    /** @var SkillPrograms groups skills */
    public $skillPrograms;
    /** @var ArrayTools shuffling and list picking */
    public $arrayTools;

    public function __construct()
    {
        $this->roller = new Roller();
        $this->tableRoller = new TableRoller($this);
        $this->skillPrograms = new SkillPrograms($this);
        $this->arrayTools = new ArrayTools($this);
    }
}