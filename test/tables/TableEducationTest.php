<?php
namespace Heroes\tests\tables;

use Heroes\enums\BonusTargets;
use Heroes\enums\SkillPrograms;
use Heroes\hero\Hero;
use Heroes\tables\TableEducation;
use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestArrayTools;
use Heroes\tests\utilities\TestRoll;

class TableEducationTest extends BaseTestRunner
{
    private $tableEducation;

    function __construct($name = NULL, array $data = array(), $dataName = '')
    {
        parent::__construct($name, $data, $dataName);

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
        $allSkills = BonusTargets::allSkills(false);
        foreach ($hero->bonuses as $bonus) {
            if (array_search($bonus->bonusTarget, $allSkills) !== false) {
                $count++;
            }
        }
        $programs = implode(',', $hero->educationProgramsPicked);

        // language adds 3 new languages as descriptions bonus descriptions instead of skills so it throws the count off
        if (array_search(SkillPrograms::LANGUAGE, $hero->educationProgramsPicked) !== false) {
            $minimumNumberSkills -= 3;
        }
        $this->assertTrue($count >= $minimumNumberSkills, "hero has at least minimum skill count $count >= $minimumNumberSkills for {$hero->educationLevel} ($programs)");
    }

    /**
     * @param $educationLevel string expected education level for the roll
     * @param $educationLevelRoll int roll needed to get education level
     * @param $numberPrograms int programs for the education level
     * @param $minimumNumberSkills int minimum # skills this education level will get
     * @return Hero look at what i did!
     */
    private function checkEducationLevel($educationLevel, $educationLevelRoll, $numberPrograms, $minimumNumberSkills)
    {
        $hero = new Hero();

        $this->engine->roller->setTestRolls([
            new TestRoll(100, $educationLevelRoll, 'Education Level', 0),
            TestRoll::doNotCareAnyMore(true),
        ]);
        $this->tableEducation->rollEducationLevel($hero);

        $this->engine->roller->verifyTestRolls();

        $this->assertEquals($educationLevel, $hero->educationLevel);
        $this->assertEquals($numberPrograms, count($hero->educationProgramsPicked));
        $this->checkHeroHasSkills($hero, $minimumNumberSkills);

        return $hero;
    }

    public function test_rollEducationLevels()
    {
        // let it shuffle naturally for random testing
        $this->engine->arrayTools->rotation = false;
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
        $this->engine->arrayTools->rotation = TestArrayTools::DEFAULT_ROTATION;
    }

    public function test_skillCountRotate11_HS()
    {
        // Reproduction error: hero has at least minimum skill count 10 >= 12 for High School Graduate (Technical,Language)
        $this->engine->roller->setTestRollsString("Education Level,1,100,1,1");
        $this->engine->arrayTools->rotation = 11;
        $this->checkEducationLevel(TableEducation::HIGH_SCHOOL_GRADUATE, 1, 2, 12);
    }

    public function test_skillCountRotate11_MS()
    {
        // Reproduction error: hero has at least minimum skill count 18 >= 19 for Military Specialist (Physical)
        $this->engine->roller->setTestRollsString("Education Level,1,100,1,72");
        $this->engine->arrayTools->rotation = 11;
        $this->checkEducationLevel(TableEducation::MILITARY_SPECIALIST, 72, 1, 19);
    }
}
