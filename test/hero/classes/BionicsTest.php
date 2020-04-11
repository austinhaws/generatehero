<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestArrayTools;
use Heroes\tests\utilities\TestRoll;

class BionicsTest extends BaseTestRunner
{
	public function test_bionics()
	{
		$this->testRoller->setTestRolls([
			(new TestRoll())->dontCareUntil('power category')->andRoll(100, 30, 'power category'),
			new TestRoll(100, 100, 'Bionic Budget'),
			new TestRoll(100, 100, 'Body Part Skinnable'),
			new TestRoll(100, 100, 'Body Part Skinnable: Type'),
			new TestRoll(100, 100, 'Bionic Location: Multiple Ors'),
			new TestRoll(100, 100, 'Bionic Location: Multiple Ors'),
			(new testRoll())->dontCareUntil('Bionic: Conditions for Bionic Reconstruction')->andRoll(100, 1, 'Bionic: Conditions for Bionic Reconstruction'),
			new TestRoll(100, 1, 'Bionic: Sponsor'),
			new TestRoll(100, 1, 'Bionic: Sponsor Status'),
			new TestRoll(100, 1, 'Has Car?'),
			new TestRoll(6, 3, 'Car Age'),
			(new TestRoll())->dontCareAnyMore(),
		]);

		$hero = $this->heroGenerator->generate();

		$this->testRoller->verifyTestRolls();

		$this->assertTrue($hero->class->budgetRemaining < 8000, 'Should have spent as much as possible; no bionic costs less than this');

		// make sure bonuses from bionic parts are added to overall bonuses list
		$this->assertTrue(count(array_filter($hero->bonuses, function ($bonus) {
			return strpos($bonus->explanation, 'Bionic: ') !== false;
			})) > 0);
	}

	public function test_randomBionics()
	{
		// way tricky to run all possible bionics combinations, so just run through random cycles to check for problems... ya, sorry if this generates an error
		$this->testArrayTools = false;
		for ($x = 0; $x < 10; $x++) {
			$this->testRoller->setTestRolls([
				(new TestRoll())->dontCareUntil('power category')->andRoll(100, 30, 'power category'),
				(new TestRoll())->dontCareAnyMore(),
			]);

			$hero = $this->heroGenerator->generate();

			$this->testRoller->verifyTestRolls();

			$this->assertTrue($hero->class->budgetRemaining < 8000, 'Should have spent as much as possible; no bionic costs less than this');
		}

		$this->testArrayTools = TestArrayTools::DEFAULT_ROTATION;
	}

	public function test_bionicPartBonusesApplied()
	{
		// generate a bionic that gets a targeting sight
		// make sure the targeting sight's +1 is showing in bonuses and adding to final value

		$this->testArrayTools->rotation = 9;

		$this->testRoller->setTestRolls([
			(new TestRoll())->dontCareUntil('power category')->andRoll(100, 30, 'power category'),
			new TestRoll(100, 100, 'Bionic Budget'),
			(new TestRoll())->dontCareAnyMore(),
		]);

		$hero = $this->heroGenerator->generate();

		$this->testRoller->verifyTestRolls();

		$targetingSight = current(array_filter($hero->class->bionics, function ($bionic) {
			return strcmp($bionic->title, 'Targeting Sight') === 0;
		}));

		// verify targeting sight bonus is in hero's bonuses list
		$bonusTargetingSight = array_filter($hero->bonuses, function ($bonus) use ($targetingSight) {
			return 0 === strcmp($bonus->explanation, $targetingSight->bonuses[0]->explanation);
		});
		$this->assertNotNull($bonusTargetingSight);
		$this->assertGreaterThan(0, $hero->strike, 'Should have had targeting bonus added');
	}
}
