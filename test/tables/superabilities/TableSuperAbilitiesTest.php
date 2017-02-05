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

    public function testSuperAbilities_firstFour() {
        $this->engine->roller->setTestRolls([
            new TestRoll(100, 32, 'Super Abilities'),
            new TestRoll(100, 3, 'Super Ability: Minor'),
            new TestRoll(100, 3, 'Super Ability: Minor'),
            new TestRoll(100, 6, 'Super Ability: Minor'),
            new TestRoll(100, 9, 'Super Ability: Minor'),
            new TestRoll(100, 12, 'Super Ability: Minor'),
        ]);

        $hero = new Hero();
        $this->tableSuperAbilities->randomSuperAbilities($hero);

        $this->engine->roller->verifyTestRolls();
    }

    public function testSuperAbilities_secondFour() {
        $this->engine->roller->setTestRolls([
            new TestRoll(100, 32, 'Super Abilities'),
            new TestRoll(100, 15, 'Super Ability: Minor'),
            new TestRoll(100, 18, 'Super Ability: Minor'),
            new TestRoll(100, 21, 'Super Ability: Minor'),
            new TestRoll(100, 24, 'Super Ability: Minor'),
        ]);

        $hero = new Hero();
        $this->tableSuperAbilities->randomSuperAbilities($hero);

        $this->engine->roller->verifyTestRolls();
    }

    public function testSuperAbilities_thirdFour() {
        $this->engine->roller->setTestRolls([
            new TestRoll(100, 32, 'Super Abilities'),
            new TestRoll(100, 27, 'Super Ability: Minor'),
            new TestRoll(100, 31, 'Super Ability: Minor'),
            new TestRoll(100, 34, 'Super Ability: Minor'),
            new TestRoll(100, 37, 'Super Ability: Minor'),
        ]);

        $hero = new Hero();
        $this->tableSuperAbilities->randomSuperAbilities($hero);

        $this->engine->roller->verifyTestRolls();
    }

    public function testSuperAbilities_fourthFour() {
        $this->engine->roller->setTestRolls([
            new TestRoll(100, 32, 'Super Abilities'),
            new TestRoll(100, 40, 'Super Ability: Minor'),
            new TestRoll(100, 43, 'Super Ability: Minor'),
            new TestRoll(100, 47, 'Super Ability: Minor'),
            new TestRoll(100, 50, 'Super Ability: Minor'),
        ]);

        $hero = new Hero();
        $this->tableSuperAbilities->randomSuperAbilities($hero);

        $this->engine->roller->verifyTestRolls();
    }
}
