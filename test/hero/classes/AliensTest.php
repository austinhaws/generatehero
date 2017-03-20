<?php

namespace Heroes\test\hero\crazy;

use Heroes\HeroGenerator;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class AliensTest extends \PHPUnit_Framework_TestCase
{
    private $heroGenerator;
    private $testRoller;

    function __construct($name = NULL, array $data = array(), $dataName = '')
    {
        parent::__construct($name, $data, $dataName);

        $this->heroGenerator = new HeroGenerator();
        $this->testRoller = new TestRoller();
        $this->heroGenerator->engine->roller = $this->testRoller;
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool true if past end of rolls
     */
    private function alienPhysiological(&$rolls, $i)
    {
        $ended = false;
        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 15, 'Alien: Physiological');
                $rolls[] = new TestRoll(4, 1, 'Alien: High Gravity - SDC');
                $rolls[] = new TestRoll(4, 1, 'Alien: High Gravity - SDC');
                $rolls[] = new TestRoll(4, 1, 'Alien: High Gravity - SDC');
                break;

            case 1:
                $rolls[] = new TestRoll(100, 29, 'Alien: Physiological');
                break;

            case 2:
                $rolls[] = new TestRoll(100, 44, 'Alien: Physiological');
                break;

            case 3:
                $rolls[] = new TestRoll(100, 58, 'Alien: Physiological');
                break;

            case 4:
                $rolls[] = new TestRoll(100, 73, 'Alien: Physiological');
                break;

            case 5:
                $rolls[] = new TestRoll(100, 88, 'Alien: Physiological');
                break;

            case 6:
                $rolls[] = new TestRoll(100, 100, 'Alien: Physiological');
                break;
        }

        return $ended;
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool true if past end of rolls
     */
    private function alienEducation(&$rolls, $i)
    {
        $ended = false;
        switch ($i & 5) {
            default:
                $ended = true;
            case 0:
                $rolls[] = (new TestRoll())->dontCareUntil('Alien Education')->andRoll(100, 20, 'Alien Education');
                break;

            case 1:
                $rolls[] = (new TestRoll())->dontCareUntil('Alien Education')->andRoll(100, 40, 'Alien Education');
                break;

            case 2:
                $rolls[] = (new TestRoll())->dontCareUntil('Alien Education')->andRoll(100, 60, 'Alien Education');
                break;

            case 3:
                $rolls[] = (new TestRoll())->dontCareUntil('Alien Education')->andRoll(100, 80, 'Alien Education');
                break;

            case 4:
                $rolls[] = (new TestRoll())->dontCareUntil('Alien Education')->andRoll(100, 100, 'Alien Education');
                break;
        }
        return $ended;
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool true if past end of rolls
     */
    private function reasonForComing(&$rolls, $i)
    {
        $ended = false;
        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 19, 'Alien: Reason for Coming');
                $rolls[] = new TestRoll(100, 25, 'Alien: last of race');
                break;

            case 1:
                $rolls[] = new TestRoll(100, 38, 'Alien: Reason for Coming');
                break;

            case 2:
                $rolls[] = new TestRoll(100, 55, 'Alien: Reason for Coming');
                break;

            case 3:
                $rolls[] = new TestRoll(100, 70, 'Alien: Reason for Coming');
                break;

            case 4:
                $rolls[] = new TestRoll(100, 85, 'Alien: Reason for Coming');
                break;

            case 5:
                $rolls[] = new TestRoll(100, 100, 'Alien: Reason for Coming');
                break;
        }
        return $ended;
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool true if past end of rolls
     */
    private function familiarity(&$rolls, $i)
    {
        $ended = false;
        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 20, 'Alien: Familiarity');
                break;

            case 1:
                $rolls[] = new TestRoll(100, 60, 'Alien: Familiarity');
                break;

            case 2:
                $rolls[] = new TestRoll(100, 100, 'Alien: Familiarity');
                break;
        }
        return $ended;
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool true if past end of rolls
     */
    private function equipment(&$rolls, $i)
    {
        $ended = false;
        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 40, 'Alien: equipment');
                break;

            case 1:
                $rolls[] = new TestRoll(100, 90, 'Alien: equipment');
                break;

        }

        return $ended;
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool true if past end of rolls
     */
    private function specialWeapon(&$rolls, $i)
    {
        $ended = false;
        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 18, 'Alien: Special Weapon');
                break;

            case 1:
                $rolls[] = new TestRoll(100, 29, 'Alien: Special Weapon');
                break;

            case 2:
                $rolls[] = new TestRoll(100, 38, 'Alien: Special Weapon');
                break;

            case 3:
                $rolls[] = new TestRoll(100, 49, 'Alien: Special Weapon');
                break;

            case 4:
                $rolls[] = new TestRoll(100, 57, 'Alien: Special Weapon');
                break;

            case 5:
                $rolls[] = new TestRoll(100, 67, 'Alien: Special Weapon');
                break;

            case 6:
                $rolls[] = new TestRoll(100, 78, 'Alien: Special Weapon');
                break;

            case 7:
                $rolls[] = new TestRoll(100, 89, 'Alien: Special Weapon');
                break;

            case 8:
                $rolls[] = new TestRoll(100, 100, 'Alien: Special Weapon');
                break;
        }
        return $ended;
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool true if past end of rolls
     */
    private function vehicle(&$rolls, $i)
    {
        $ended = false;
        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 13, 'Alien: Vehicle');
                break;

            case 1:
                $rolls[] = new TestRoll(100, 25, 'Alien: Vehicle');
                break;

            case 2:
                $rolls[] = new TestRoll(100, 37, 'Alien: Vehicle');
                break;

            case 3:
                $rolls[] = new TestRoll(100, 50, 'Alien: Vehicle');
                break;

            case 4:
                $rolls[] = new TestRoll(100, 62, 'Alien: Vehicle');
                break;

            case 5:
                $rolls[] = new TestRoll(100, 74, 'Alien: Vehicle');
                break;

            case 6:
                $rolls[] = new TestRoll(100, 86, 'Alien: Vehicle');
                break;

            case 7:
                $rolls[] = new TestRoll(100, 100, 'Alien: Vehicle');
                break;
        }
        return $ended;
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool true if past end of rolls
     */
    private function money(&$rolls, $i)
    {
        $ended = false;
        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 14, 'Alien: Money Category');
                $rolls[] = new TestRoll(4, 1, 'Alien: Money');
                break;

            case 1:
                $rolls[] = new TestRoll(100, 29, 'Alien: Money Category');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                break;

            case 2:
                $rolls[] = new TestRoll(100, 44, 'Alien: Money Category');
                $rolls[] = new TestRoll(4, 1, 'Alien: Money');
                $rolls[] = new TestRoll(4, 1, 'Alien: Money');
                break;

            case 3:
                $rolls[] = new TestRoll(100, 59, 'Alien: Money Category');
                $rolls[] = new TestRoll(4, 1, 'Alien: Money');
                $rolls[] = new TestRoll(4, 1, 'Alien: Money');
                $rolls[] = new TestRoll(4, 1, 'Alien: Money');
                break;

            case 4:
                $rolls[] = new TestRoll(100, 74, 'Alien: Money Category');
                $rolls[] = new TestRoll(4, 1, 'Alien: Money');
                $rolls[] = new TestRoll(4, 1, 'Alien: Money');
                $rolls[] = new TestRoll(4, 1, 'Alien: Money');
                $rolls[] = new TestRoll(4, 1, 'Alien: Money');
                break;

            case 5:
                $rolls[] = new TestRoll(100, 88, 'Alien: Money Category');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                break;

            case 6:
                $rolls[] = new TestRoll(100, 100, 'Alien: Money Category');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                $rolls[] = new TestRoll(6, 1, 'Alien: Money');
                break;
        }
        return $ended;
    }

    /**
     * @param $rolls array rolls to roll for this section for this time through
     * @param $i int which loop
     * @return bool true if past end of rolls
     */
    private function superAbilities(&$rolls, $i)
    {
        $ended = false;

        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 49, 'Alien: Super Abilities');
                break;

            case 1:
                $rolls[] = new TestRoll(100, 60, 'Alien: Super Abilities');
                break;

            case 2:
                $rolls[] = new TestRoll(100, 69, 'Alien: Super Abilities');
                break;

            case 3:
                $rolls[] = new TestRoll(100, 79, 'Alien: Super Abilities');
                break;

            case 4:
                $rolls[] = new TestRoll(100, 89, 'Alien: Super Abilities');
                break;

            case 5:
                $rolls[] = new TestRoll(100, 100, 'Alien: Super Abilities');
                break;
        }
        return $ended;
    }

    private function alienAppearance(&$rolls, $i)
    {
        $ended = false;
        switch ($i) {
            default:
                $ended = true;
            case 0:
                $rolls[] = new TestRoll(100, 16, 'appearance');
                break;
            case 1:
                $rolls[] = new TestRoll(100, 39, 'appearance');
                break;
            case 2:
                $rolls[] = new TestRoll(100, 43, 'appearance');
                break;
            case 3:
                $rolls[] = new TestRoll(100, 48, 'appearance');
                break;
            case 4:
                $rolls[] = new TestRoll(100, 53, 'appearance');
                break;
            case 5:
                $rolls[] = new TestRoll(100, 58, 'appearance');
                break;
            case 6:
                $rolls[] = new TestRoll(100, 64, 'appearance');
                break;
            case 7:
                $rolls[] = new TestRoll(100, 68, 'appearance');
                break;
            case 8:
                $rolls[] = new TestRoll(100, 72, 'appearance');
                break;
            case 9:
                $rolls[] = new TestRoll(100, 76, 'appearance');
                break;
            case 10:
                $rolls[] = new TestRoll(100, 79, 'appearance');
                break;
            case 11:
                $rolls[] = new TestRoll(100, 84, 'appearance');
                break;
            case 12:
                $rolls[] = new TestRoll(100, 89, 'appearance');
                break;
            case 13:
                $rolls[] = new TestRoll(100, 94, 'appearance');
                break;
            case 14:
                $rolls[] = new TestRoll(100, 100, 'appearance');
                break;
        }
        return $ended;
    }

    /**
     * create rolls based on the iteration until all the iterations have been exercised
     */
    /**
     * @param $i int the current iteration
     * @return bool|array true if all the iterations of all the possibilities have been used or array of test rolls
     * @throws \Exception if $i% is invalid for a section
     */
    private function rollsIteration($i)
    {
        $rolls = [
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 100, 'power category'),
            (new TestRoll())->dontCareUntilAndGetNext('appearance'),
        ];

        $ended = $this->alienAppearance($rolls, $i);

        $ended = $ended && $this->alienPhysiological($rolls, $i);
        $ended = $ended && $this->superAbilities($rolls, $i);
        $ended = $ended && $this->alienEducation($rolls, $i);
        $ended = $ended && $this->reasonForComing($rolls, $i);
        $ended = $ended && $this->familiarity($rolls, $i);
        $ended = $ended && $this->equipment($rolls, $i);
        $ended = $ended && $this->specialWeapon($rolls, $i);
        $ended = $ended && $this->vehicle($rolls, $i);
        $ended = $ended && $this->money($rolls, $i);

        $rolls[] = (new TestRoll())->dontCareAnyMore();
        return $ended ? false : $rolls;
    }

    public function test_alien()
    {
        $i = 0;
        while ($rolls = $this->rollsIteration($i++)) {
            $this->testRoller->setTestRolls($rolls);

            $this->heroGenerator->generate();

            $this->testRoller->verifyTestRolls();
        }
    }
}
