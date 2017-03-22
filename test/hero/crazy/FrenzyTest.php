<?php

namespace Heroes\test\hero\crazy;

use Heroes\hero\crazy\Frenzy;
use Heroes\hero\Hero;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class FrenzyTest extends BaseTestRunner
{

    public function testFrenzy()
    {
        $frenzy = new Frenzy($this->heroGenerator->engine);

        $this->testRoller->setTestRolls([
            new TestRoll(100, 10, 'Frenzy: condition'),
        ]);
        $hero = new Hero();
        $frenzy->create($hero);
        $this->testRoller->verifyTestRolls();

        $this->assertEquals('Intense Frustration', $frenzy->condition);
    }
}
