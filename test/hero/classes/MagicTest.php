<?php

namespace Heroes\test\hero\classes;

use Heroes\tests\BaseTestRunner;
use Heroes\tests\utilities\TestRoll;

class MagicTest extends BaseTestRunner
{
    public function enchantedWeapon_weaponType(&$rolls, $i)
    {
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

    public function enchantedWeapon_weaponDamage(&$rolls, $i)
    {
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
            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 80, 'power category'),
                (new TestRoll())->dontCareUntil('Magic Type')->andRoll(100, 25, 'Magic Type'),
            ];

            $ended = $this->runIterationGroup([
                'enchantedWeapon_weaponType',
                'enchantedWeapon_weaponDamage',
            ], $rolls, $i);

            $rolls[] = new TestRoll(false, false, 'Education Level');
            $rolls[] = (new TestRoll())->dontCareAnyMore();

            $this->testRoller->setTestRolls($rolls);

            $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();
        }
    }


    public function enchantedObject_powers(&$rolls, $i)
    {
        $ended = $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 14, 'Magic: Enchanted Object - Powers'),],
            [new TestRoll(100, 30, 'Magic: Enchanted Object - Powers'),],
            [new TestRoll(100, 50, 'Magic: Enchanted Object - Powers'),],
            [new TestRoll(100, 70, 'Magic: Enchanted Object - Powers'),],
            [new TestRoll(100, 85, 'Magic: Enchanted Object - Powers'),],
            [new TestRoll(100, 100, 'Magic: Enchanted Object - Powers'),],
        ]);

        if ($i === 5) {
            $rolls[] = new TestRoll(false, false, 'Super Ability: Major');
            $rolls[] = new TestRoll(false, false, 'Super Ability: Minor');
        }

        return $ended;
    }

    public function enchantedObject_spellLevel(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 25, 'Magic: Enchanted Object - Spell Level'),],
            [new TestRoll(100, 50, 'Magic: Enchanted Object - Spell Level'),],
            [new TestRoll(100, 75, 'Magic: Enchanted Object - Spell Level'),],
            [new TestRoll(100, 100, 'Magic: Enchanted Object - Spell Level'),],
        ]);
    }

    public function enchantedObject_spellsPerDay(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 11, 'Magic: Enchanted Object - Spells per Day'),],
            [new TestRoll(100, 21, 'Magic: Enchanted Object - Spells per Day'),],
            [new TestRoll(100, 33, 'Magic: Enchanted Object - Spells per Day'),],
            [new TestRoll(100, 55, 'Magic: Enchanted Object - Spells per Day'),],
            [new TestRoll(100, 67, 'Magic: Enchanted Object - Spells per Day'),],
            [new TestRoll(100, 89, 'Magic: Enchanted Object - Spells per Day'),],
            [new TestRoll(100, 100, 'Magic: Enchanted Object - Spells per Day'),],
        ]);
    }

    public function enchantedObject_attribute(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(8, 1, 'Magic: Enchanted Object - attribute'),],
            [new TestRoll(8, 2, 'Magic: Enchanted Object - attribute'),],
            [new TestRoll(8, 3, 'Magic: Enchanted Object - attribute'),],
            [new TestRoll(8, 4, 'Magic: Enchanted Object - attribute'),],
            [new TestRoll(8, 5, 'Magic: Enchanted Object - attribute'),],
            [new TestRoll(8, 6, 'Magic: Enchanted Object - attribute'),],
            [new TestRoll(8, 7, 'Magic: Enchanted Object - attribute'),],
            [new TestRoll(8, 8, 'Magic: Enchanted Object - attribute'),],
        ]);
    }

    public function enchantedObject_otherAbilities(&$rolls, $i)
    {
        return $this->iterationSubRolls($rolls, $i, [
            [new TestRoll(100, 20, 'Magic: Enchanted Object - Other Abilities'),],
            [new TestRoll(100, 40, 'Magic: Enchanted Object - Other Abilities'),],
            [new TestRoll(100, 50, 'Magic: Enchanted Object - Other Abilities'),],
            [new TestRoll(100, 60, 'Magic: Enchanted Object - Other Abilities'),],
            [new TestRoll(100, 70, 'Magic: Enchanted Object - Other Abilities'),],
            [new TestRoll(100, 79, 'Magic: Enchanted Object - Other Abilities'),],
            [new TestRoll(100, 89, 'Magic: Enchanted Object - Other Abilities'),],
            [new TestRoll(100, 100, 'Magic: Enchanted Object - Other Abilities'),],
        ]);
    }


    public function test_enchantedObject()
    {
        $ended = false;
        for ($i = 0; !$ended; $i++) {
            $this->testArrayTools->rotation = $i + 1;
            $rolls = [
                (new TestRoll())->dontCareUntil('power category')->andRoll(100, 80, 'power category'),
                (new TestRoll())->dontCareUntil('Magic Type')->andRoll(100, 50, 'Magic Type'),
            ];

            $ended = $this->runIterationGroup([
                'enchantedObject_spellLevel',
                'enchantedObject_spellsPerDay',
                'enchantedObject_powers',
                'enchantedObject_attribute',
                'enchantedObject_otherAbilities',
            ], $rolls, $i);

            $rolls[] = new TestRoll(false, false, 'Education Level');
            $rolls[] = (new TestRoll())->dontCareAnyMore();

            $this->testRoller->setTestRolls($rolls);

            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();

            $this->assertTrue(strpos(get_class($hero->class), 'Magic') !== false);
            if ($i < 5) {
                $magic = $hero->class;
                $this->assertNotNull($magic->objectSpells);
                $this->assertNotNull($magic->objectSpellLevel);
                $this->assertNotNull($magic->objectSpellsPerDay);
            }
        }
    }

    public function test_mysticWizard()
    {
        $rolls = [
            (new TestRoll())->dontCareUntil('power category')->andRoll(100, 80, 'power category'),
            (new TestRoll())->dontCareUntil('Magic Type')->andRoll(100, 63, 'Magic Type'),
             new TestRoll(false, false, 'Education Level'),
            (new TestRoll())->dontCareAnyMore(),
        ];
        for ($x = 0; $x < 50; $x++) {
            $this->testRoller->setTestRolls($rolls);
            $this->testArrayTools->rotation = $x + 1;
            $hero = $this->heroGenerator->generate();
            $this->testRoller->verifyTestRolls();


            $this->assertTrue(strpos(get_class($hero->class), 'Magic') !== false);
            $this->assertEquals(14, count($hero->class->spellsKnown));
            $this->assertEquals(8, $hero->class->spellsPerDay);
        }
    }
}
