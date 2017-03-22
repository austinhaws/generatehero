<?php

namespace Heroes\test\hero\crazy;

use Heroes\hero\crazy\Crazy;
use Heroes\hero\Hero;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class CrazyTest extends BaseTestRunner
{
    public function testCrazy()
    {
        $crazy = new Crazy($this->heroGenerator->engine);

        $this->testRoller->setTestRolls([
            new TestRoll(100, 13, 'Insanity: Phobia'),
            new TestRoll(100, 13, 'Insanity: Phobia'),
            new TestRoll(2, 1, 'Obsession: love/hate'),
            new TestRoll(100, 56, 'Insanity: Obsession'),
        ]);
        $hero = new Hero();
        $crazy->create($hero);
        $this->testRoller->verifyTestRolls();

        $this->assertEquals(3, count($hero->insanities));
    }
}
