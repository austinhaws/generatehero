<?php

namespace Heroes\test\hero\classes;

use Heroes\enums\UrlParameters;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class UrlParamPowerCategoryTest extends BaseTestRunner
{
    public function test_urlParamPowerCategory() {
        $rolls = [
            TestRoll::doNotCareAnyMore(),
        ];

        $hero = $this->runGeneration($rolls, [UrlParameters::POWER_CATEGORY => 'Aliens']);
        $this->assertEquals($hero->class->classType, 'Alien');
    }
}
