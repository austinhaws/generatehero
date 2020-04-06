<?php

namespace Heroes\tests\utilities;

use Heroes\engine\Engine;
use Heroes\hero\Hero;
use Heroes\HeroGenerator;
use Heroes\tests\utilities\HeroVarsChecker\HeroVarsChecker;

class TestHeroGenerator extends HeroGenerator
{
	/** @var HeroVarsChecker  */
	private $heroVarsChecker;

	public function __construct(Engine $engine = null)
	{
		parent::__construct($engine);

		$this->heroVarsChecker = new HeroVarsChecker();
	}

	/**
	 * check for unhandled hero fields
	 * @param array $urlParams
	 * @return Hero
	 */
	public function generate($urlParams = [])
	{
		$hero = parent::generate($urlParams);

		$this->heroVarsChecker->checkVars($hero);

		return $hero;
	}
}
