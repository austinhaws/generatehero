<?php

namespace Heroes\test\hero\crazy;

use Heroes\hero\crazy\Personalities;
use Heroes\hero\Hero;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class PersonalitiesTest extends BaseTestRunner
{

    public function testAssociation_notPopey()
    {
        $personalities = new Personalities($this->heroGenerator->engine);
        $hero = new Hero();

        $this->testRoller->setTestRolls([
            // 3 personalities
            new TestRoll(100, 65, 'Personalities: total'),

            // principled
            new TestRoll(100, 20, 'Personality: Alignment'),

            // normal
            new TestRoll(100, 60, 'Quirk Good'),

            // unprincipled
            new TestRoll(100, 50, 'Personality: Alignment'),

            // selfish
            new TestRoll(2, 1, 'Personality: selfish'),

            // opposite sex
            new TestRoll(100, 80, 'Quirk Evil'),

            // selfish
            new TestRoll(100, 100, 'Personality: Alignment'),

            // hypochondriac
            new TestRoll(100, 81, 'Quirk Evil'),

			new TestRoll(100, 100, 'Personality: Alignment'),
            new TestRoll(100, 81, 'Quirk Evil'),
        ]);
        $personalities->create($hero);
        $this->testRoller->verifyTestRolls();

        $this->assertEquals(4, count($personalities->personalities));
    }
}
