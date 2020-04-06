<?php

namespace Heroes\tests\utilities\HeroVarsChecker;

use Exception;

class HeroFieldNotFoundException extends Exception
{
	public function __construct($notFoundHeroField)
	{
		parent::__construct("'$notFoundHeroField' not found in KnownFields", 0, null);
	}
}
