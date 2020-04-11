<?php

namespace Heroes\tests\utilities\HeroVarsChecker;

use Exception;

class HeroFieldNotFoundException extends Exception
{
	public $notFoundHeroField = null;

	public function __construct($notFoundHeroField)
	{
		$this->notFoundHeroField = $notFoundHeroField;
		parent::__construct("'$notFoundHeroField' not found in KnownFields", 0, null);
	}
}
