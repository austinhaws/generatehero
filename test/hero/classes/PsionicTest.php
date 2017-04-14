<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class PsionicTest extends BaseTestRunner
{
    public function test_psionic()
    {
        for ($i = 0; $i < 50; $i++) {
            $this->engine->arrayTools->rotation = $i + 1;
            $this->testArrayTools->rotation = $i + 1;
            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 60, 'power category'),
                new TestRoll(false, false, 'Education Level', 1, true)
            ];

            $this->testRoller->setTestRolls($rolls);

            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();

            $this->assertTrue(strpos(get_class($hero->class), 'Psionics') !== false);

            $this->assertEquals(9, count($hero->psionics));
        }
    }
}
