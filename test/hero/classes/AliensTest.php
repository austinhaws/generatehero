<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class AliensTest extends BaseTestRunner
{
    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool ended flag
     */
    public function alienPhysiological(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [
                new TestRoll(100, 15, 'Alien: Physiological'),
                new TestRoll(4, 1, 'Alien: High Gravity - SDC'),
                new TestRoll(4, 1, 'Alien: High Gravity - SDC'),
                new TestRoll(4, 1, 'Alien: High Gravity - SDC'),
            ],
            [
                new TestRoll(100, 29, 'Alien: Physiological'),
                new TestRoll(4, 1, 'Alien: Low Gravity - SDC'),
            ],
            [
                new TestRoll(100, 44, 'Alien: Physiological'),
                new TestRoll(4, 1, 'Alien: High Radiation - SDC'),
            ],
            [
                new TestRoll(100, 58, 'Alien: Physiological'),
            ],
            [
                new TestRoll(100, 73, 'Alien: Physiological'),
            ],
            [
                new TestRoll(100, 88, 'Alien: Physiological'),
            ],
            [
                new TestRoll(100, 100, 'Alien: Physiological'),
                new TestRoll(6, 1, 'Alien: Abrasive - SDC'),
                new TestRoll(6, 1, 'Alien: Abrasive - SDC'),
                new TestRoll(6, 1, 'Alien: Abrasive - SDC'),
            ],
        ]);
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool ended flag
     */
    public function alienEducation(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [
                (new TestRoll())->dontCareUntil('Alien Education')->andRoll(100, 20, 'Alien Education'),
            ],
            [
                (new TestRoll())->dontCareUntil('Alien Education')->andRoll(100, 40, 'Alien Education'),
                new TestRoll(20, 1, 'Alien Military Specialist Skill Bonus'),
            ],
            [
                (new TestRoll())->dontCareUntil('Alien Education')->andRoll(100, 60, 'Alien Education'),
                new TestRoll(20, 1, 'Alien Science Specialist Skill Bonus'),
            ],
            [
                (new TestRoll())->dontCareUntil('Alien Education')->andRoll(100, 80, 'Alien Education'),
            ],
            [
                (new TestRoll())->dontCareUntil('Alien Education')->andRoll(100, 100, 'Alien Education'),
            ],
        ]);
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool ended flag
     */
    public function reasonForComing(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [
                TestRoll::doNotCareUntilAndRoll(100, 19, 'Alien: Reason for Coming'),
                new TestRoll(100, 25, 'Alien: last of race'),
            ],
            [
                TestRoll::doNotCareUntilAndRoll(100, 38, 'Alien: Reason for Coming'),
                new TestRoll(100, 20, 'Alien: crash landed!'),
            ],

            [
                TestRoll::doNotCareUntilAndRoll(100, 55, 'Alien: Reason for Coming'),
                new TestRoll(100, 20, 'Alien: outcast'),
            ],
            [
                TestRoll::doNotCareUntilAndRoll(100, 55, 'Alien: Reason for Coming'),
                new TestRoll(100, 40, 'Alien: outcast'),
            ],
            [
                TestRoll::doNotCareUntilAndRoll(100, 55, 'Alien: Reason for Coming'),
                new TestRoll(100, 60, 'Alien: outcast'),
            ],
            [
                TestRoll::doNotCareUntilAndRoll(100, 55, 'Alien: Reason for Coming'),
                new TestRoll(100, 80, 'Alien: outcast'),
            ],
            [
                TestRoll::doNotCareUntilAndRoll(100, 55, 'Alien: Reason for Coming'),
                new TestRoll(100, 100, 'Alien: outcast'),
            ],

            [
                TestRoll::doNotCareUntilAndRoll(100, 70, 'Alien: Reason for Coming'),
                new TestRoll(100, 20, 'Alien: Champion'),
            ],
            [
                TestRoll::doNotCareUntilAndRoll(100, 70, 'Alien: Reason for Coming'),
                new TestRoll(100, 40, 'Alien: Champion'),
            ],
            [
                TestRoll::doNotCareUntilAndRoll(100, 70, 'Alien: Reason for Coming'),
                new TestRoll(100, 60, 'Alien: Champion'),
            ],
            [
                TestRoll::doNotCareUntilAndRoll(100, 70, 'Alien: Reason for Coming'),
                new TestRoll(100, 80, 'Alien: Champion'),
            ],
            [
                TestRoll::doNotCareUntilAndRoll(100, 70, 'Alien: Reason for Coming'),
                new TestRoll(100, 100, 'Alien: Champion'),
            ],

            [
                TestRoll::doNotCareUntilAndRoll(100, 85, 'Alien: Reason for Coming'),
            ],
            [
                TestRoll::doNotCareUntilAndRoll(100, 100, 'Alien: Reason for Coming'),
            ],
        ]);
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool ended flag
     */
    public function familiarity(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [
                new TestRoll(100, 20, 'Alien: Familiarity'),
            ],
            [
                new TestRoll(100, 60, 'Alien: Familiarity'),
            ],
            [
                new TestRoll(100, 100, 'Alien: Familiarity'),
            ],
        ]);
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool ended flag
     */
    public function equipment(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [
                new TestRoll(100, 40, 'Alien: equipment'),
            ],
            [
                new TestRoll(100, 90, 'Alien: equipment'),
            ],
        ]);
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool ended flag
     */
    public function specialWeapon(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [
                new TestRoll(100, 18, 'Alien: Special Weapon'),
            ],
            [
                new TestRoll(100, 29, 'Alien: Special Weapon'),
            ],
            [
                new TestRoll(100, 38, 'Alien: Special Weapon'),
            ],
            [
                new TestRoll(100, 49, 'Alien: Special Weapon'),
            ],
            [
                new TestRoll(100, 57, 'Alien: Special Weapon'),
            ],
            [
                new TestRoll(100, 67, 'Alien: Special Weapon'),
            ],
            [
                new TestRoll(100, 78, 'Alien: Special Weapon'),
            ],
            [
                new TestRoll(100, 89, 'Alien: Special Weapon'),
            ],
            [
                new TestRoll(100, 100, 'Alien: Special Weapon'),
            ],
        ]);
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool ended flag
     */
    public function vehicle(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [
                new TestRoll(100, 13, 'Alien: Vehicle'),
            ],
            [
                new TestRoll(100, 25, 'Alien: Vehicle'),
            ],
            [
                new TestRoll(100, 37, 'Alien: Vehicle'),
            ],
            [
                new TestRoll(100, 50, 'Alien: Vehicle'),
            ],
            [
                new TestRoll(100, 62, 'Alien: Vehicle'),
            ],
            [
                new TestRoll(100, 74, 'Alien: Vehicle'),
            ],
            [
                new TestRoll(100, 86, 'Alien: Vehicle'),
            ],
            [
                new TestRoll(100, 100, 'Alien: Vehicle'),
            ],
        ]);
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool ended flag
     */
    public function money(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [
                new TestRoll(100, 14, 'Alien: Money Category'),
                new TestRoll(4, 1, 'Alien: Money'),
            ],
            [
                new TestRoll(100, 29, 'Alien: Money Category'),
                new TestRoll(6, 1, 'Alien: Money'),
            ],
            [
                new TestRoll(100, 44, 'Alien: Money Category'),
                new TestRoll(4, 1, 'Alien: Money'),
                new TestRoll(4, 1, 'Alien: Money'),
            ],
            [
                new TestRoll(100, 59, 'Alien: Money Category'),
                new TestRoll(4, 1, 'Alien: Money'),
                new TestRoll(4, 1, 'Alien: Money'),
                new TestRoll(4, 1, 'Alien: Money'),
            ],
            [
                new TestRoll(100, 74, 'Alien: Money Category'),
                new TestRoll(4, 1, 'Alien: Money'),
                new TestRoll(4, 1, 'Alien: Money'),
                new TestRoll(4, 1, 'Alien: Money'),
                new TestRoll(4, 1, 'Alien: Money'),
            ],
            [
                new TestRoll(100, 88, 'Alien: Money Category'),
                new TestRoll(6, 1, 'Alien: Money'),
                new TestRoll(6, 1, 'Alien: Money'),
                new TestRoll(6, 1, 'Alien: Money'),
            ],
            [
                new TestRoll(100, 100, 'Alien: Money Category'),
                new TestRoll(6, 1, 'Alien: Money'),
                new TestRoll(6, 1, 'Alien: Money'),
                new TestRoll(6, 1, 'Alien: Money'),
                new TestRoll(6, 1, 'Alien: Money'),
                new TestRoll(6, 1, 'Alien: Money'),
                new TestRoll(6, 1, 'Alien: Money'),
            ],
        ]);
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool ended flag
     */
    public function superAbilities(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [
                new TestRoll(100, 49, 'Alien: Super Abilities'),
            ],
            [
                new TestRoll(100, 60, 'Alien: Super Abilities'),
            ],
            [
                new TestRoll(100, 69, 'Alien: Super Abilities'),
            ],
            [
                new TestRoll(100, 79, 'Alien: Super Abilities'),
            ],
            [
                new TestRoll(100, 89, 'Alien: Super Abilities'),
            ],
            [
                new TestRoll(100, 100, 'Alien: Super Abilities'),
            ],
        ]);
    }

    public function alienAppearance(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [
                new TestRoll(100, 30, 'appearance'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 16, 'Alien Characteristic'),
            ],

            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 39, 'Alien Characteristic'),
                new TestRoll(100, 10, 'Characteristic: Skin Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 39, 'Alien Characteristic'),
                new TestRoll(100, 20, 'Characteristic: Skin Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 39, 'Alien Characteristic'),
                new TestRoll(100, 30, 'Characteristic: Skin Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 39, 'Alien Characteristic'),
                new TestRoll(100, 40, 'Characteristic: Skin Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 39, 'Alien Characteristic'),
                new TestRoll(100, 50, 'Characteristic: Skin Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 39, 'Alien Characteristic'),
                new TestRoll(100, 60, 'Characteristic: Skin Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 39, 'Alien Characteristic'),
                new TestRoll(100, 70, 'Characteristic: Skin Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 39, 'Alien Characteristic'),
                new TestRoll(100, 80, 'Characteristic: Skin Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 39, 'Alien Characteristic'),
                new TestRoll(100, 90, 'Characteristic: Skin Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 39, 'Alien Characteristic'),
                new TestRoll(100, 100, 'Characteristic: Skin Color'),
            ],

            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 43, 'Alien Characteristic'),
            ],

            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 48, 'Alien Characteristic'),
                new TestRoll(100, 10, 'Characteristic: Hair Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 48, 'Alien Characteristic'),
                new TestRoll(100, 20, 'Characteristic: Hair Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 48, 'Alien Characteristic'),
                new TestRoll(100, 30, 'Characteristic: Hair Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 48, 'Alien Characteristic'),
                new TestRoll(100, 40, 'Characteristic: Hair Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 48, 'Alien Characteristic'),
                new TestRoll(100, 50, 'Characteristic: Hair Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 48, 'Alien Characteristic'),
                new TestRoll(100, 60, 'Characteristic: Hair Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 48, 'Alien Characteristic'),
                new TestRoll(100, 70, 'Characteristic: Hair Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 48, 'Alien Characteristic'),
                new TestRoll(100, 80, 'Characteristic: Hair Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 48, 'Alien Characteristic'),
                new TestRoll(100, 90, 'Characteristic: Hair Color'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 48, 'Alien Characteristic'),
                new TestRoll(100, 100, 'Characteristic: Hair Color'),
            ],

            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 53, 'Alien Characteristic'),
            ],

            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 58, 'Alien Characteristic'),
                new TestRoll(100, 17, 'Characteristic: Unusual Eyes'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 58, 'Alien Characteristic'),
                new TestRoll(100, 34, 'Characteristic: Unusual Eyes'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 58, 'Alien Characteristic'),
                new TestRoll(100, 55, 'Characteristic: Unusual Eyes'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 58, 'Alien Characteristic'),
                new TestRoll(100, 75, 'Characteristic: Unusual Eyes'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 58, 'Alien Characteristic'),
                new TestRoll(100, 89, 'Characteristic: Unusual Eyes'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 58, 'Alien Characteristic'),
                new TestRoll(100, 100, 'Characteristic: Unusual Eyes'),
            ],

            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 64, 'Alien Characteristic'),
                new TestRoll(100, 20, 'Characteristic: Body Hair'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 64, 'Alien Characteristic'),
                new TestRoll(100, 40, 'Characteristic: Body Hair'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 64, 'Alien Characteristic'),
                new TestRoll(100, 60, 'Characteristic: Body Hair'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 64, 'Alien Characteristic'),
                new TestRoll(100, 80, 'Characteristic: Body Hair'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 64, 'Alien Characteristic'),
                new TestRoll(100, 100, 'Characteristic: Body Hair'),
            ],

            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 68, 'Alien Characteristic'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 72, 'Alien Characteristic'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 76, 'Alien Characteristic'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 79, 'Alien Characteristic'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 84, 'Alien Characteristic'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 89, 'Alien Characteristic'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 94, 'Alien Characteristic'),
            ],
            [
                new TestRoll(100, 50, 'appearance'),
                new TestRoll(100, 100, 'Alien Characteristic'),
            ],
            [
                new TestRoll(100, 55, 'appearance'),
            ],
            [
                new TestRoll(100, 60, 'appearance'),
            ],
            [
                new TestRoll(100, 65, 'appearance'),
            ],
            [
                new TestRoll(100, 70, 'appearance'),
            ],
            [
                new TestRoll(100, 75, 'appearance'),
            ],
            [
                new TestRoll(100, 80, 'appearance'),
            ],
            [
                new TestRoll(100, 85, 'appearance'),
            ],
            [
                new TestRoll(100, 90, 'appearance'),
            ],
            [
                new TestRoll(100, 95, 'appearance'),
            ],
            [
                new TestRoll(100, 100, 'appearance'),
            ],
        ]);
    }

    public function test_alien()
    {
        $this->runIterations([
            'alienAppearance',
            'alienPhysiological',
            'superAbilities',
            'alienEducation',
            'reasonForComing',
            'familiarity',
            'equipment',
            'specialWeapon',
            'vehicle',
            'money',
        ], [
            TestRoll::doNotCareUntilAndRoll(100, 100, 'power category'),
            (new TestRoll())->dontCareUntilAndGetNext('appearance'),
        ]);
    }

    public function test_superAbilitiesSuperAbilities() {
        foreach ([49, 69] as $superAbility) {
            $rolls = [
                TestRoll::doNotCareUntilAndRoll(100, 100, 'power category'),
                TestRoll::doNotCareUntilAndRoll(100, $superAbility, 'Alien: Super Abilities'),
                new TestRoll(false, false, 'Super Abilities'),
                TestRoll::doNotCareUntilAndRoll(100, 1, 'Alien Education'),
                TestRoll::doNotCareAnyMore(),
            ];

            $this->runGeneration($rolls);
        }
    }

    public function test_superAbilitiesPsionics() {
        $rolls = [
            TestRoll::doNotCareUntilAndRoll(100, 100, 'power category'),
            TestRoll::doNotCareUntilAndRoll(100, 60, 'Alien: Super Abilities'),
            TestRoll::doNotCareUntilAndRoll(100, 1, 'Alien Education'),
            TestRoll::doNotCareAnyMore(),
        ];

        $hero = $this->runGeneration($rolls);
        $this->assertNotEmpty($hero->psionics);
        $this->assertNotEquals(0, $hero->class->isp);
    }

    public function test_superAbilitiesRobotics() {
        $rolls = [
            TestRoll::doNotCareUntilAndRoll(100, 100, 'power category'),
            TestRoll::doNotCareUntilAndRoll(100, 79, 'Alien: Super Abilities'),
            TestRoll::doNotCareUntilAndRoll(100, 1, 'Alien Education'),
            TestRoll::doNotCareAnyMore(),
        ];

        $hero = $this->runGeneration($rolls);
        $this->assertNotEmpty($hero->class->robotics);
    }

    public function test_superAbilitiesBionics() {
        $rolls = [
            TestRoll::doNotCareUntilAndRoll(100, 100, 'power category'),
            TestRoll::doNotCareUntilAndRoll(100, 100, 'Alien: Super Abilities'),
            TestRoll::doNotCareUntilAndRoll(100, 1, 'Alien Education'),
            TestRoll::doNotCareAnyMore(),
        ];

        $hero = $this->runGeneration($rolls);
        $this->assertNotEmpty($hero->class->bionics);
    }

    public function test_superAbilitiesMagic() {
        $rolls = [
            TestRoll::doNotCareUntilAndRoll(100, 100, 'power category'),
            TestRoll::doNotCareUntilAndRoll(100, 89, 'Alien: Super Abilities'),
            TestRoll::doNotCareUntilAndRoll(100, 1, 'Alien Education'),
            TestRoll::doNotCareAnyMore(),
        ];

        $hero = $this->runGeneration($rolls);
        $this->assertNotEmpty($hero->class->magic);
    }
}
