<?php
namespace Heroes\tests\tables\superabilities;

use Heroes\hero\Hero;
use Heroes\tables\superabilities\TableSuperAbilities;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class TableSuperAbilitiesMajorTest extends BaseTestRunner
{
    private $tableSuperAbilities;

    function __construct($name = NULL, array $data = array(), $dataName = '')
    {
        parent::__construct($name, $data, $dataName);

        $this->tableSuperAbilities = new TableSuperAbilities($this->engine);
    }

    /**
     * helper to run rolls for a major super ability
     *
     * @param $rolls array the rolls to use for the test
     * @return Hero the hero to which abilities were applied
     */
    private function majorSuperAbilityTest($rolls) {
        $this->engine->roller->setTestRolls($rolls);

        $hero = new Hero();
        $this->tableSuperAbilities->randomSuperAbilities($hero);

        $this->engine->roller->verifyTestRolls();

        return $hero;
    }

    public function testMajorSuperAbilities() {
        // rodent / musteloid
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 1, 'Super Ability: Major'),
            new TestRoll(114, 2, 'Super Ability: Major'),
        ]);

        // chameleon / stone
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 3, 'Super Ability: Major'),
            new TestRoll(114, 5, 'Super Ability: Major'),
        ]);

        // water / invisibility
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 9, 'Super Ability: Major'),
            new TestRoll(114, 11, 'Super Ability: Major'),
        ]);

        // energy / control
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 13, 'Super Ability: Major'),
            new TestRoll(114, 16, 'Super Ability: Major'),
        ]);

        // shape / darkness
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 19, 'Super Ability: Major'),
            new TestRoll(114, 22, 'Super Ability: Major'),
        ]);

        // gravity / ice
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 24, 'Super Ability: Major'),
            new TestRoll(114, 27, 'Super Ability: Major'),
        ]);

        // intangibility / growth
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 30, 'Super Ability: Major'),
            new TestRoll(114, 32, 'Super Ability: Major'),
        ]);

        // force / air
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 35, 'Super Ability: Major'),
            new TestRoll(114, 38, 'Super Ability: Major'),
        ]);

        // bear / bird
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 39, 'Super Ability: Major'),
            new TestRoll(114, 40, 'Super Ability: Major'),
        ]);

        // reptile / speed
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 41, 'Super Ability: Major'),
            new TestRoll(114, 43, 'Super Ability: Major'),
        ]);

        // fire / magnetism
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 46, 'Super Ability: Major'),
            new TestRoll(114, 48, 'Super Ability: Major'),
        ]);

        // stretching / invulnerability
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 50, 'Super Ability: Major'),
            new TestRoll(114, 53, 'Super Ability: Major'),
        ]);

        // electricity / earth
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 56, 'Super Ability: Major'),
            new TestRoll(114, 59, 'Super Ability: Major'),
        ]);

        // flight / teleport
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 62, 'Super Ability: Major'),
            new TestRoll(114, 64, 'Super Ability: Major'),
        ]);

        // liquid / touch
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 67, 'Super Ability: Major'),
            new TestRoll(114, 70, 'Super Ability: Major'),
        ]);

        // metal / mechano link
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 73, 'Super Ability: Major'),
            new TestRoll(114, 75, 'Super Ability: Major'),
        ]);

        // fire / mimic
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 78, 'Super Ability: Major'),
            new TestRoll(114, 81, 'Super Ability: Major'),
        ]);

        // karmic / sonic
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 83, 'Super Ability: Major'),
            new TestRoll(114, 86, 'Super Ability: Major'),
        ]);

        // vibration / shrink
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 89, 'Super Ability: Major'),
            new TestRoll(114, 92, 'Super Ability: Major'),
        ]);

        // plant / possession
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 95, 'Super Ability: Major'),
            new TestRoll(114, 98, 'Super Ability: Major'),
        ]);

        // weight / canine
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 100, 'Super Ability: Major'),
            new TestRoll(114, 101, 'Super Ability: Major'),
        ]);

        // cat / cat
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 102, 'Super Ability: Major'),
            new TestRoll(114, 103, 'Super Ability: Major'),
        ]);

        // fish / hoofed
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 104, 'Super Ability: Major'),
            new TestRoll(114, 105, 'Super Ability: Major'),
        ]);

        // musteloid / nocturnal
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 106, 'Super Ability: Major'),
            new TestRoll(114, 107, 'Super Ability: Major'),
        ]);

        // cat / canine
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 108, 'Super Ability: Major'),
            new TestRoll(114, 109, 'Super Ability: Major'),
        ]);

        // bird / hoofed
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 110, 'Super Ability: Major'),
            new TestRoll(114, 111, 'Super Ability: Major'),
        ]);

        // bear / reptile
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 112, 'Super Ability: Major'),
            new TestRoll(114, 113, 'Super Ability: Major'),
        ]);

        // bear / any
        $this->majorSuperAbilityTest([
            new TestRoll(100, 100, 'Super Abilities'),
            new TestRoll(114, 112, 'Super Ability: Major'),
            new TestRoll(114, 114, 'Super Ability: Major'),
        ]);
    }
}
