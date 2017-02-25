<?php
namespace Heroes\tests\tables;

use Heroes\engine\Engine;
use Heroes\enums\BonusTargets;
use Heroes\hero\Hero;
use Heroes\tables\TableEducation;
use Heroes\tests\utilities\TestRoll;
use Heroes\tests\utilities\TestRoller;

class TableEducationTest extends \PHPUnit_Framework_TestCase
{
    private $engine;
    private $tableEducation;

    function __construct($name = NULL, array $data = array(), $dataName = '')
    {
        parent::__construct($name, $data, $dataName);

        $this->engine = new Engine();
        $this->engine->roller = new TestRoller();
        $this->tableEducation = new TableEducation($this->engine);
    }

    /**
     * test that the hero has at least one skill
     * @param $hero Hero the hero
     * @param $minimumNumberSkills int how many skills the character must at least have
     */
    private function checkHeroHasSkills($hero, $minimumNumberSkills)
    {
        $count = 0;
        $allSkills = BonusTargets::allSkills();
        foreach ($hero->bonuses as $bonus) {
            if (array_search($bonus->bonusTarget, $allSkills) !== false) {
                $count++;
            }
        }
        $this->assertTrue($count >= $minimumNumberSkills, "hero has at least minimum skill count $count >= $minimumNumberSkills");
    }

    /**
     * @param $educationLevel string expected education level for the roll
     * @param $educationLevelRoll int roll needed to get education level
     * @param $numberPrograms int programs for the education level
     * @param $minimumNumberSkills int minimum # skills this education level will get
     */
    private function checkEducationLevel($educationLevel, $educationLevelRoll, $numberPrograms, $minimumNumberSkills)
    {
        $this->engine->roller->setTestRolls([
            new TestRoll(100, $educationLevelRoll, 'Education Level', 0),
            (new TestRoll())->dontCareUntil(),
        ]);

        $hero = new Hero();

        $this->tableEducation->rollEducationLevel($hero);

        $this->engine->roller->verifyTestRolls();

        $this->assertEquals($educationLevel, $hero->educationLevel);
        $this->assertEquals($numberPrograms, count($hero->educationProgramsPicked));

        $this->checkHeroHasSkills($hero, $minimumNumberSkills);
    }

    public function test_rollEducationLevel_oneYearCollege()
    {
        foreach ([
                     [TableEducation::HIGH_SCHOOL_GRADUATE, 1, 2, 12],
                     [TableEducation::MILITARY, 18, 2, 12],
                     [TableEducation::TRADE_SCHOOL, 19, 2, 10],
                     [TableEducation::ONE_YEAR_OF_COLLEGE, 30, 2, 10],
                     [TableEducation::TWO_YEARS_OF_COLLEGE, 45, 2, 10],
                     [TableEducation::THREE_YEARS_OF_COLLEGE, 54, 3, 11],
                     [TableEducation::FOUR_YEARS_OF_COLLEGE, 63, 3, 13],
                     [TableEducation::MILITARY_SPECIALIST, 72, 1, 19],
                     [TableEducation::BACHELOR_DEGREE, 81, 3, 13],
                     [TableEducation::MASTER_DEGREE, 90, 3, 13],
                     [TableEducation::DOCTORATE_DEGREE, 100, 4, 14],
                 ] as $test) {
            $this->checkEducationLevel(...$test);

        }
    }
}
