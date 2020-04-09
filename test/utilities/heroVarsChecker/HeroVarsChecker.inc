<?php

namespace Heroes\tests\utilities\HeroVarsChecker;

use Heroes\hero\Hero;

class HeroVarsChecker
{
	/**
	 * override original generator to track all found fields
	 *
	 * @param Hero $hero
	 */
	public function checkVars(Hero $hero)
	{
		try {
			$this->checkValue($hero, '');
		} catch (HeroFieldNotFoundException $re) {
			// print_r($hero);
			var_dump($re->getMessage());
		}

	}

	/**
	 * @param $basePath
	 * @param $newPath
	 * @return string
	 */
	private function addToPath($basePath, $newPath)
	{
		return ($basePath ? "$basePath." : '') . $newPath;
	}

	/**
	 * @param $fullPath
	 * @return bool
	 */
	private function pathPartIsStarred($fullPath)
	{
		$knownFields = KnownFields::fields();
		$testPath = '';
		$pathParts = explode('.', $fullPath);
		$result = false;
		foreach ($pathParts as $part) {
			$testPath = $this->addToPath($testPath, $part);
			if ($result = in_array($testPath . '.*', $knownFields)) {
				$result = true;
				break;
			}
		}

		return $result;
	}

	/**
	 * @param $fullPath
	 * @throws HeroFieldNotFoundException
	 */
	private function checkKeyExists($fullPath)
	{
		$knownFields = KnownFields::fields();

		if (
			!in_array($fullPath, $knownFields) &&
			!$this->pathPartIsStarred($fullPath)
		) {
			throw new HeroFieldNotFoundException($fullPath);
		}

	}

	/**
	 * @param $value
	 * @param $basePath
	 * @throws HeroFieldNotFoundException
	 */
	private function checkValue($value, $basePath)
	{
		if (is_array($value)) {
			foreach ($value as $item) {
				$this->checkValue($item, $basePath);
			}
		} else if (is_object($value)) {
			$objectFields = get_object_vars($value);

			foreach ($objectFields as $objectField => $objectValue) {
				$newPath = $this->addToPath($basePath, $objectField);
				$this->checkKeyExists($newPath);
				$this->checkValue($objectValue, $newPath);
			}
		} else {
			// just a string or intrinsic value, so don't need to do anything; already checked
			$this->checkKeyExists($basePath);
		}
	}
}
