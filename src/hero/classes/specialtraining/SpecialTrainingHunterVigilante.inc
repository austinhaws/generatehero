<?php

namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\enums\SkillPrograms;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\TableEducation;

class SpecialTrainingHunterVigilante extends BaseClass
{

    public function create(Hero &$hero)
    {
        $this->modifyAttributes($hero);

        $this->education($hero);

        $this->specialSkills($hero);

        $this->otherStuff($hero);
    }

    private function modifyAttributes(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Hunter Vigilante - PE', 1, 4), 'Hunter Vigilante - PE'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, new Roll('Hunter Vigilante - Speed', 1, 6), 'Hunter Vigilante - Speed'));
    }

    private function education(Hero &$hero)
    {
        $hero->educationLevel = TableEducation::HUNTER_VIGILANTE;

        $hero->addSkill(BonusTargets::SKILL_MATHEMATICS_BASIC, 'Hunter Vigilante - Education', 98);

        $tableEducation = new TableEducation($this->engine);
        $tableEducation->pickPrograms(15, 2, $hero, [SkillPrograms::ESPIONAGE, SkillPrograms::MILITARY]);

        $skillPrograms = new SkillPrograms($this->engine);
        $skills = $skillPrograms->selectSkills(2, $hero, 0, BonusTargets::wpAncientWeaponsSkills(false));
        $hero->addSkills($skills, 'Hunter Vigilante - education', 0);

        $skills = $skillPrograms->selectSkills(3, $hero, 0, BonusTargets::wpModernWeaponsSkills(false));
        $hero->addSkills($skills, 'Hunter Vigilante - education', 0);

        $hero->addSkill(BonusTargets::SKILL_WILDERNESS_SURVIVAL, 'Hunter Vigilante - Education', 30);
        $hero->addSkill(BonusTargets::SKILL_LAND_NAVIGATION, 'Hunter Vigilante - Education', 30);
        $hero->addSkill(BonusTargets::SKILL_TRACKING, 'Hunter Vigilante - Education', 35);
        $hero->addSkill(BonusTargets::SKILL_WP_RIFLE, 'Hunter Vigilante - Education');

        if ($this->engine->roller->rollPercent('Hunter Vigilante - Hand to Hand') > 50) {
            $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_EXPERT, 'Hunter Vigilante - Education');
        } else {
            $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS, 'Hunter Vigilante - Education');
        }

        $tableEducation->pickPrograms(10, 1, $hero, [SkillPrograms::ESPIONAGE, SkillPrograms::MILITARY]);

        // Select 8 Secondary Skills.
        $skills = $skillPrograms->selectSkills(8, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Hunter Vigilante - education', 0);


        $skills = $skillPrograms->selectSkills(7, $hero, 20, [
            BonusTargets::SKILL_ARCHERY,
            BonusTargets::SKILL_BIOLOGY,
            BonusTargets::SKILL_CLIMBING,
            BonusTargets::SKILL_DETECT_AMBUSH,
            BonusTargets::SKILL_DETECT_CONCEALMENT,
            BonusTargets::SKILL_FIRST_AID,
            BonusTargets::SKILL_FISH,
            BonusTargets::SKILL_INTELLIGENCE,
            BonusTargets::SKILL_PROWL,
            BonusTargets::SKILL_RADIO_BASIC,
            BonusTargets::SKILL_SNIPER,
            BonusTargets::SKILL_SWIMMING,
            BonusTargets::SKILL_SWIMMING_ADVANCED,
            BonusTargets::SKILL_PILOT_BOATS_SAIL,
            BonusTargets::SKILL_PILOT_BOATS_MOTOR,
            BonusTargets::SKILL_PILOT_TRUCK,
        ]);
        $hero->addSkills($skills, 'Hunter Vigilante - education', 20);
    }

    private function specialSkills(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Disguise Scent (82%) - Disguise one\'s own scent by making it smell like something else.', 'Hunter Vigilante - Special Skill'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Recognize and Identify Plants (88%)', 'Hunter Vigilante - Special Skill'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Trap/Snare Animals (80%)', 'Hunter Vigilante - Special Skill'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Modify Weapon Cartridges - Create dumdums, hollow points, full metal jacketed, and other special cartridges', 'Hunter Vigilante - Special Skill'));
    }

    private function otherStuff(Hero &$hero)
    {
        $years = $this->engine->tableRoller->rollTable('Hunter Vigilante - experience', [
            new TableEntry(17, 6),
            new TableEntry(35, 8),
            new TableEntry(52, 10),
            new TableEntry(69, 12),
            new TableEntry(86, 14),
            new TableEntry(100, 16),
        ]);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, "$years years of experience as Hunter/Vigilante", 'Hunter Vigilante - experience'));

        $money = $this->engine->tableRoller->rollTable('Hunter Vigilante - money', [
           new TableEntry(15, 8000),
           new TableEntry(29, 10000),
           new TableEntry(45, 12000),
           new TableEntry(60, 14000),
           new TableEntry(75, 16000),
           new TableEntry(89, 18000),
           new TableEntry(100, 20000),
        ]);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, $money, 'Hunter Vigilante - money'));

        $this->hasCar($hero, 88);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 50, 'Hunter Vigilante - Starting SDC'));
    }
}
