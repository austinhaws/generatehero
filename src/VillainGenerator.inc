<?php

namespace Heroes;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

class VillainGenerator
{
    /** @var Engine drive me */
    public $engine;

    /**
     * HeroGenerator constructor.
     * @param Engine $engine allows testing to override engine
     */
    public function __construct(Engine $engine = null)
    {
        $this->engine = $engine ? $engine : new Engine();
    }

    /**
     * create a villain!
     *
     * @return Hero the villain
     */
    public function generate()
    {
        $hero = new Hero();

        // gender
        $hero->gender = $this->engine->tableRoller->rollTable('gender', [
            new TableEntry(1, 'Male'),
            new TableEntry(2, 'Female'),
        ]);

        // level
        $level = $this->engine->tableRoller->rollTable('level', [
            new TableEntry(25, '1'),
            new TableEntry(50, '2'),
            new TableEntry(75, '3'),
            new TableEntry(100, '4'),
        ]);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Level: ' . $level, 'Villain level'));

        // alignment
        $hero->alignment = $this->engine->tableRoller->rollTable('level', [
            new TableEntry(20, 'Aberrant'),
            new TableEntry(50, 'Miscreant'),
            new TableEntry(82, 'Anarchist'),
            new TableEntry(100, 'Diabolic'),
        ]);

        // criminal record
        $record = $this->engine->tableRoller->rollTable('level', [
            new TableEntry(30, 'None'),
            new TableEntry(40, 'A few misdemeanors'),
            new TableEntry(49, 'A few misdemeanors. ' . $this->engine->roller->rollDice(new Roll('Villain felonies - misdemeanors', 2, 8)) . ' felonies. Time Served'),
            new TableEntry(69, 'Criminal record a mile long, but not currently wanted'),
            new TableEntry(84, 'Long criminal record, wanted on ' . $this->engine->roller->rollDice(new Roll('Villain felonies - long record', 1, 6)) . ' felony charges'),
            new TableEntry(100, 'Suspected on several felony charges, but no evidence to make the charges stick'),
        ]);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Criminal Record: ' . $record, 'Villain criminal record'));


        if ($this->engine->roller->rollPercent('Villain Type') <= 50) {
            $this->thug($hero);
        } else {
            $this->criminalElite($hero);
        }

        return $hero;
    }

    /**
     * give thug bonuses
     *
     * @param Hero $hero the thug
     */
    private function thug(Hero &$hero) {
        $hero->intelligenceQuotient = $this->engine->roller->rollDice(new Roll('thug - IQ', 3, 4));
        $hero->physicalStrength = $this->engine->roller->rollDice(new Roll('thug - PS', 4, 4));
        $hero->physicalProwess = $this->engine->roller->rollDice(new Roll('Thug - PP', 4, 4));

        // 3d6 for the rest of them
        $hero->physicalEndurance = $this->engine->roller->rollDice(new Roll('Thug - PE', 3, 6));
        $hero->physicalBeauty = $this->engine->roller->rollDice(new Roll('Thug - PB', 3, 6));
        $hero->mentalEndurance = $this->engine->roller->rollDice(new Roll('Thug - ME', 3, 6));
        $hero->mentalAffinity = $this->engine->roller->rollDice(new Roll('Thug - MA', 3, 6));
        $hero->speed = $this->engine->roller->rollDice(new Roll('Thug - Speed', 3, 6));

        // determine type
        $thugType = $this->engine->tableRoller->rollTable('Thug Type', [
            new TableEntry(25, 'thief'),
            new TableEntry(25, 'muscleBodyguard'),
            new TableEntry(25, 'punk2BitHood'),
            new TableEntry(25, 'conMan'),
        ]);
        $this->$thugType($hero);
    }

    private function thief(Hero &$hero) {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 25, 'Thug - Thief'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_PICK_POCKETS, 20, 'Thug - Thief'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_PICK_LOCKS, 20, 'Thug - Thief'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_PROWL, 20, 'Thug - Thief'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_CLIMBING, 15, 'Thug - Thief'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_BASIC_ELECTRONICS, 10, 'Thug - Thief'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_PILOT_AUTOMOBILE, 25, 'Thug - Thief'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_PILOT_MOTORCYCLE, 25, 'Thug - Thief'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_HAND_TO_HAND_BASIC, 0, 'Thug - Thief'));
        if ($this->engine->roller->rollPercent('Thug - thief: WP') > 50) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_WP_KNIFE, 0, 'Thug - Thief'));
        } else {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_WP_AUTOMATIC_PISTOL, 0, 'Thug - Thief'));
        }

        $hero->addSkills(BonusTargets::allSkills(true), 'Thug - Thief', 25);
    }

    private function muscleBodyguard(Hero &$hero) {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 40, 'Thug - Muscle / Body Guard'));

        if ($this->engine->roller->rollPercent('Thug - Muscle: Hand to Hand') > 50) {
            $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_EXPERT, 'Thug - Muscle / Body Guard', 0);
        } else {
            $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS, 'Thug - Muscle / Body Guard', 0);
        }

        if ($this->engine->roller->rollPercent('Thug - Muscle: Skill') > 50) {
            $hero->addSkill(BonusTargets::SKILL_WRESTLING, 'Thug - Muscle / Body Guard', 0);
        } else {
            $hero->addSkill(BonusTargets::SKILL_BOXING, 'Thug - Muscle / Body Guard', 0);
        }
        $hero->addSkill(BonusTargets::SKILL_BODY_BUILDING, 'Thug - Muscle / Body Guard', 0);
        $hero->addSkill(BonusTargets::SKILL_WP_REVOLVER, 'Thug - Muscle / Body Guard', 0);

        $skills = $this->engine->skillPrograms->selectSkills(2, $hero, 0, BonusTargets::weaponProficienciesSkills(false));
        $hero->addSkills($skills, 'Thug - Muscle / Body Guard', 0);

        $skills = $this->engine->skillPrograms->selectSkills(3, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Thug - Muscle / Body Guard', 0);
    }

    private function punk2BitHood(Hero &$hero) {
        $hero->addSkills([
            BonusTargets::SKILL_HAND_TO_HAND_BASIC,
            BonusTargets::SKILL_RUNNING,
            BonusTargets::SKILL_WP_KNIFE,
            BonusTargets::SKILL_WP_CHAIN,
            BonusTargets::SKILL_WP_REVOLVER,
            BonusTargets::SKILL_WP_AUTOMATIC_PISTOL,
        ], 'Thug: Punk/2-Bit Hood', 0);
        $skills = $this->engine->skillPrograms->selectSkills(4, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Thug: Punk/2-Bit Hood', 0);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 10, 'Thug: Punk/2-Bit Hood'));
    }

    private function conMan(Hero &$hero) {
        $hero->addSkill(BonusTargets::SKILL_PICK_POCKETS, 'Thug: Con Man', 10);
        $hero->addSkill(BonusTargets::SKILL_FORGERY, 'Thug: Con Man', 15);
        $hero->addSkill(BonusTargets::SKILL_DISGUISE, 'Thug: Con Man', 5);
        $hero->addSkill(BonusTargets::SKILL_PALMING, 'Thug: Con Man', 15);
        $hero->addSkill(BonusTargets::SKILL_CONCEALMENT, 'Thug: Con Man', 10);
        $hero->addSkill(BonusTargets::SKILL_BASIC_ELECTRONICS, 'Thug: Con Man');
        $hero->addSkill(BonusTargets::SKILL_COMPUTER_OPERATION, 'Thug: Con Man');
        $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_BASIC, 'Thug: Con Man');

        $skills = $this->engine->skillPrograms->selectSkills(1, $hero, 0, BonusTargets::weaponProficienciesSkills(false));
        $hero->addSkills($skills, 'Thug: Con Man', 0);

        $skills = $this->engine->skillPrograms->selectSkills(4, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Thug: Con Man', 0);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 10, 'Thug: Con Man'));
    }
}
