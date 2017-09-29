<?php

namespace Heroes\test\utilities;

use Heroes\hero\Hero;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class HeroGeneratorSkillsTest extends BaseTestRunner
{
    public function testApplySet()
    {
        $this->testRoller->setTestRolls([
            new TestRoll(6, 1, 'intelligenceQuotient'),
            new TestRoll(6, 1, 'intelligenceQuotient'),
            new TestRoll(6, 1, 'intelligenceQuotient'),
            TestRoll::doNotCareUntilAndRoll(100, 90, 'power category'),
            TestRoll::doNotCareAnyMore(),
        ]);


        /** @var Hero $hero */
        $hero = $this->heroGenerator->generate();

        // gets ATTRIBUTE_INTELLIGENCE_QUOTIENT set to 9
        $this->assertEquals($hero->intelligenceQuotient, 9);

    }

    public function testApplySetBigger()
    {
        $this->testRoller->setTestRolls([
            new TestRoll(6, 6, 'intelligenceQuotient'),
            new TestRoll(6, 3, 'intelligenceQuotient'),
            new TestRoll(6, 3, 'intelligenceQuotient'),
            TestRoll::doNotCareUntilAndRoll(100, 90, 'power category'),
            TestRoll::doNotCareAnyMore(),
        ]);


        /** @var Hero $hero */
        $hero = $this->heroGenerator->generate();

        // gets ATTRIBUTE_INTELLIGENCE_QUOTIENT set to 9
        $this->assertEquals($hero->intelligenceQuotient, 12);

    }
}
