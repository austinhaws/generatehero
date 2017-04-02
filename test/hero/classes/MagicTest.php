<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class MagicTest extends BaseTestRunner
{
    private function enchantedWeapon_weaponType(&$rolls, $i) {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 10, 'Enchanted Weapon Type'),],
            [new TestRoll(100, 20, 'Enchanted Weapon Type'),],
            [new TestRoll(100, 32, 'Enchanted Weapon Type'),],
            [new TestRoll(100, 45, 'Enchanted Weapon Type'),],
            [new TestRoll(100, 58, 'Enchanted Weapon Type'),],
            [new TestRoll(100, 70, 'Enchanted Weapon Type'),],
            [new TestRoll(100, 80, 'Enchanted Weapon Type'),],
            [new TestRoll(100, 90, 'Enchanted Weapon Type'),],
            [new TestRoll(100, 100, 'Enchanted Weapon Type'),],
        ]);
    }

    private function enchantedWeapon_weaponDamage(&$rolls, $i) {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 25, 'Enchanted Weapon Damage'),],
            [new TestRoll(100, 50, 'Enchanted Weapon Damage'),],
            [new TestRoll(100, 75, 'Enchanted Weapon Damage'),],
            [new TestRoll(100, 100, 'Enchanted Weapon Damage'),],
        ]);
    }

    public function test_magicEnchantedWeapon()
    {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $endeds = [];
            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 80, 'power category'),
                (new TestRoll())->dontCareUntil('Magic Type')->andRoll(100, 25, 'Magic Type'),
            ];

            $endeds[] = $this->enchantedWeapon_weaponType($rolls, $i);
            $endeds[] = $this->enchantedWeapon_weaponDamage($rolls, $i);

            $rolls[] = new TestRoll(false, false, 'Education Level');
            $rolls[] = (new TestRoll())->dontCareAnyMore();

            $this->testRoller->setTestRolls($rolls);

            $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();

            $ended = count(array_filter($endeds, function ($e) { return !$e;})) > 0;
        }
    }
}
