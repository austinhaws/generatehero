<?php

namespace Heroes\test\hero\crazy;

use Heroes\hero\crazy\Association;
use Heroes\hero\Hero;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class AssociationTest extends BaseTestRunner
{

    public function testAssociation_notPopey()
    {
        $hero = new Hero();
        $association = new Association($this->heroGenerator->engine);

        $this->testRoller->setTestRolls([
            new TestRoll(100, 100, 'Association: association'),
        ]);
        $association->create($hero);
        $this->testRoller->verifyTestRolls();

        $this->assertEquals('Solar Syndrome', $association->association);
        $this->assertEquals(false, $association->popeye);
    }

    public function testAssociation_popey()
    {
        $association = new Association($this->heroGenerator->engine);

        $this->testRoller->setTestRolls([
            new TestRoll(100, 31, 'Association: association'),
            new TestRoll(100, 100, 'Popeye: power food'),
        ]);
        $hero = new Hero();
        $association->create($hero);
        $this->testRoller->verifyTestRolls();

        $this->assertEquals('Popeye Syndrome', $association->association);
        $this->assertEquals('Twinkies', $association->popeye);

    }
}
