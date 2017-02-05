<?php
namespace Heroes\tests\tables\superabilities;

use Heroes\engine\Engine;
use Heroes\hero\Hero;
use Heroes\tables\superabilities\TableSuperAbilities;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class TableSuperAbilitiesTest extends \PHPUnit_Framework_TestCase
{
    private $engine;
    private $tableSuperAbilities;

    function __construct($name = NULL, array $data = array(), $dataName = '')
    {
        parent::__construct($name, $data, $dataName);

        $this->engine = new Engine();
        $this->engine->roller = new TestRoller();
        $this->tableSuperAbilities = new TableSuperAbilities($this->engine);
    }

    public function testSuperAbilities_AdvancedSight() {
        $this->engine->roller->setTestRolls([
            new TestRoll(100, 32, 'Super Abilities'),
            new TestRoll(100, 100, 'power category'),

            (new TestRoll())->dontCareUntil('Super Ability: Minor')->andRoll(100, 1, 'Super Ability: Minor'),
        ]);

        $hero = new Hero();
        $this->tableSuperAbilities->randomSuperAbilities($hero);
    }
}
