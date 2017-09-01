<?php

namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\TableEducation;

class SpecialTrainingAncientMaster extends BaseClass
{

    public function create(Hero &$hero)
    {
        $this->modifyAttributes($hero);

        $this->educate($hero);

        $this->addCombatSkills($hero);

        $this->specialAbilities($hero);

        $this->basics($hero);
    }

    private function modifyAttributes(Hero &$hero) {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 18, 'Ancient Master base PS'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 18, 'Ancient Master base PP'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 20, 'Ancient Master base PE'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Ancient Master - MA', 1, 6), 'Ancient Master base MA'));
    }

    private function educate(Hero &$hero) {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_MATHEMATICS_BASIC, 98, 'Ancient Master - education'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Pick a language', 'Ancient Master - education'));

        // 10 secondaries, excluding all physical skills
        (new TableEducation($this->engine))->pickSecondarySkills(10, $hero, false, 0, BonusTargets::physicalSkills(false));
    }

    private function addCombatSkills(Hero &$hero) {
        // set education so that it doesn't generate in normal character creation
        $hero->educationLevel = TableEducation::ANCIENT_MASTER;

        // HAND TO HAND: MARTIAL ARTS
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS, 0, 'Ancient Master - combat'));
        // Attacks Per Melee: 8 (includes the two melee attacks automatic to all heroes and one additional attack from boxing).
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTACKS_PER_MELEE, 6, 'Ancient Master - combat'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PULL_PUNCH, 3, 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 3, 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 2, 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 5, 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 5, 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DAMAGE, 4, 'Ancient Master - combat'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Death Blow - on natural 20', 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Knock Out/Stun - on natural 18, 19, or 20', 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Judo-style body throw - 1D6 damage and victim loses initiative and one melee attack', 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Karate-style kick - 1D8 damage', 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Jump Kick - 2D8 damage', 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Leap attack - critical does double damage', 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Paired Weapons', 'Ancient Master - combat'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Entangle', 'Ancient Master - combat'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Entangle', 'Ancient Master - combat'));

        // ANCIENT WEAPON PROFICIENCIES
        $hero->addSkills(BonusTargets::wpAncientWeaponsSkills(false), 'Ancient Master - combat', 0);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 3, 'Ancient Master - Ancient Weapons'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 3, 'Ancient Master - Ancient Weapons'));

        $hero->addSkill(BonusTargets::SKILL_BOXING, 'Ancient Master - combat');

        // Select 4 Physical Skills: Each is equal to lOth level proficiency.
        $this->engine->skillPrograms->selectSkills(4, $hero, 0, BonusTargets::physicalSkills(false));
    }

    private function specialAbilities(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Feign Death (96%) - Fall in to a death-like trance.', 'Ancient Master - abilities'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Cleansing Spirit (89%) - mentally will body to destroy disease, drugs or chemicals, and heal.', 'Ancient Master - abilities'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Positive Energy - instills the character with a super human, physical toughness: energy attacks halved; gases, poisons, drugs, and chemicals 1/2 damage; +5 vs magic, +3 vs psionics.', 'Ancient Master - abilities'));
    }

    private function basics(Hero &$hero)
    {
        $hero->age = $this->engine->tableRoller->rollTable('Ancient Master - Age', [
           new TableEntry(16, 40),
           new TableEntry(33, 50),
           new TableEntry(50, 60),
           new TableEntry(67, 70),
           new TableEntry(83, 80),
           new TableEntry(100, 90),
        ]);

        $ageAppearance = $this->engine->tableRoller->rollTable('Ancient Master - Age Appearance', [
           new TableEntry(20, '50ish'),
           new TableEntry(42, 'mid 40s'),
           new TableEntry(62, '40'),
           new TableEntry(78, 'mid 30s'),
           new TableEntry(92, '30'),
           new TableEntry(100, 'mid 20s'),
        ]);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, "Looks $ageAppearance", 'Ancient Master - Age Appearance'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Has 10 Blade Weapons (knives, swords), 6 Blunt Weapons, 6 Throwing Weapons, and 6 Other Weapons', 'Ancient Master'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Ancient Master - Money', 2, 6, 100), 'Ancient Master'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 50, 'Ancient Master'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Ancient Master - SDC', 2, 4, 10), 'Ancient Master'));
    }
}
