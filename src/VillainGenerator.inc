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
    public $heroGenerator;

    /**
     * VillainGenerator constructor.
     * @param Engine $engine allows testing to override engine
     */
    public function __construct(Engine $engine = null)
    {
        $this->engine = $engine ? $engine : new Engine();
        $this->heroGenerator = new HeroGenerator($this->engine);
    }

    /**
     * create a villain!
     *
     * @return Hero the villain
     */
    public function generate()
    {
        $villain = new Hero();

        // gender
        $villain->gender = $this->engine->tableRoller->rollTable('gender', [
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
        $villain->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Level: ' . $level, 'Villain level'));

        // alignment
        $villain->alignment = $this->engine->tableRoller->rollTable('alignment', [
            new TableEntry(20, 'Aberrant'),
            new TableEntry(50, 'Miscreant'),
            new TableEntry(82, 'Anarchist'),
            new TableEntry(100, 'Diabolic'),
        ]);

        // criminal record
        $record = $this->engine->tableRoller->rollTable('criminalRecord', [
            new TableEntry(30, 'None'),
            new TableEntry(40, 'A few misdemeanors'),
            new TableEntry(49, 'A few misdemeanors. ' . $this->engine->roller->rollDice(new Roll('Villain felonies - misdemeanors', 2, 8)) . ' felonies. Time Served'),
            new TableEntry(69, 'Criminal record a mile long, but not currently wanted'),
            new TableEntry(84, 'Long criminal record, wanted on ' . $this->engine->roller->rollDice(new Roll('Villain felonies - long record', 1, 6)) . ' felony charges'),
            new TableEntry(100, 'Suspected on several felony charges, but no evidence to make the charges stick'),
        ]);
        $villain->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Criminal Record: ' . $record, 'Villain criminal record'));


        if ($this->engine->roller->rollPercent('Villain Type') <= 50) {
            $this->thug($villain);
        } else {
            $this->criminalElite($villain);
        }

        // if super villain, then roll on super abilities chart and give super abilities
        if ($this->engine->roller->rollPercent('Villain Super Powers') <= 10) {
            $this->heroGenerator->generatePowerCategory($villain);
        }

        $this->criminalOrganization($villain);

        $this->heroGenerator->totalHero($villain);

        return $villain;
    }

    /**
     * the hero to turn in to a villain
     *
     * @param Hero $hero the criminal elite
     */
    private function criminalElite(Hero &$hero)
    {

        $hero->intelligenceQuotient = $this->engine->roller->rollDice(new Roll('Criminal Elite - IQ', 5, 4));
        $hero->physicalStrength = $this->engine->roller->rollDice(new Roll('Criminal Elite - PS', 4, 4));
        $hero->physicalProwess = $this->engine->roller->rollDice(new Roll('Criminal Elite - PP', 4, 4));

        // 3d6 for the rest of them
        $hero->physicalEndurance = $this->engine->roller->rollDice(new Roll('Criminal Elite - PE', 3, 6));
        $hero->physicalBeauty = $this->engine->roller->rollDice(new Roll('Criminal Elite - PB', 3, 6));
        $hero->mentalEndurance = $this->engine->roller->rollDice(new Roll('Criminal Elite - ME', 3, 6));
        $hero->mentalAffinity = $this->engine->roller->rollDice(new Roll('Criminal Elite - MA', 3, 6));
        $hero->speed = $this->engine->roller->rollDice(new Roll('Criminal Elite - Speed', 3, 6));

        // determine type
        $criminalEliteType = $this->engine->tableRoller->rollTable('Criminal Elite Type', [
            new TableEntry(25, 'boss'),
            new TableEntry(50, 'militaryMercenary'),
            new TableEntry(75, 'hitMan'),
            new TableEntry(100, 'surveillanceSpecialist'),
        ]);
        $this->$criminalEliteType($hero);
    }

    private function boss(Hero &$hero)
    {
        if ($this->engine->roller->rollPercent('Criminal Elite - Boss: Hand to Hand') > 50) {
            $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_EXPERT, 'Criminal Elite - Boss', 0);
        } else {
            $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS, 'Criminal Elite - Boss', 0);
        }

        $skills = $this->engine->skillPrograms->selectSkills(2, $hero, 0, BonusTargets::espionageSkills(false));
        $hero->addSkills($skills, 'Criminal Elite - Boss', 0);

        $skills = $this->engine->skillPrograms->selectSkills(3, $hero, 0, BonusTargets::physicalSkills(false));
        $hero->addSkills($skills, 'Criminal Elite - Boss', 0);

        $skills = $this->engine->skillPrograms->selectSkills(3, $hero, 0, BonusTargets::weaponProficienciesSkills(false));
        $hero->addSkills($skills, 'Criminal Elite - Boss', 0);

        $skills = $this->engine->skillPrograms->selectSkills(6, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Criminal Elite - Boss', 0);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 30, 'Criminal Elite - Boss'));
    }

    private function militaryMercenary(Hero &$hero)
    {
        if ($this->engine->roller->rollPercent('Criminal Elite - Military Mercenary: Hand to Hand') > 50) {
            $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_EXPERT, 'Criminal Elite - Military Mercenary', 0);
        } else {
            $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS, 'Criminal Elite - Military Mercenary', 0);
        }

        $hero->addSkill(BonusTargets::SKILL_DEMOLITIONS, 'Criminal Elite - Military Mercenary', 10);

        $skills = $this->engine->skillPrograms->selectSkills(3, $hero, 0, BonusTargets::espionageSkills(false));
        $hero->addSkills($skills, 'Criminal Elite - Military Mercenary', 0);

        $skills = $this->engine->skillPrograms->selectSkills(3, $hero, 0, BonusTargets::physicalSkills(false));
        $hero->addSkills($skills, 'Criminal Elite - Military Mercenary', 0);

        $skills = $this->engine->skillPrograms->selectSkills(4, $hero, 0, BonusTargets::weaponProficienciesSkills(false));
        $hero->addSkills($skills, 'Criminal Elite - Military Mercenary', 0);

        $skills = $this->engine->skillPrograms->selectSkills(3, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Criminal Elite - Military Mercenary', 0);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 40, 'Criminal Elite - Military Mercenary'));
    }

    private function hitMan(Hero &$hero)
    {
        $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_ASSASSIN, 'Criminal Elite - Hit Man', 0);

        $hero->addSkill(BonusTargets::SKILL_DETECT_AMBUSH, 'Criminal Elite - Hit Man', 10);
        $hero->addSkill(BonusTargets::SKILL_PROWL, 'Criminal Elite - Hit Man', 10);
        $hero->addSkill(BonusTargets::SKILL_DEMOLITIONS, 'Criminal Elite - Hit Man', 10);
        $hero->addSkill(BonusTargets::SKILL_DEMOLITIONS_DISPOSAL, 'Criminal Elite - Hit Man', 5);
        $hero->addSkill(BonusTargets::SKILL_SNIPER, 'Criminal Elite - Hit Man');
        $hero->addSkill(BonusTargets::SKILL_WP_RIFLE, 'Criminal Elite - Hit Man');
        $hero->addSkill(BonusTargets::SKILL_WP_AUTOMATIC_PISTOL, 'Criminal Elite - Hit Man');

        $skills = $this->engine->skillPrograms->selectSkills(3, $hero, 0, BonusTargets::weaponProficienciesSkills(false));
        $hero->addSkills($skills, 'Criminal Elite - Hit Man', 0);

        $skills = $this->engine->skillPrograms->selectSkills(1, $hero, 0, BonusTargets::physicalSkills(false));
        $hero->addSkills($skills, 'Criminal Elite - Hit Man', 0);

        $skills = $this->engine->skillPrograms->selectSkills(3, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Criminal Elite - Hit Man', 0);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 30, 'Criminal Elite - Hit Man'));
    }

    private function surveillanceSpecialist(Hero &$hero)
    {
        $hero->addSkill(BonusTargets::SKILL_SURVEILLANCE, 'Criminal Elite - Surveillance Specialist', 20);
        $hero->addSkill(BonusTargets::SKILL_CRYPTOGRAPHY, 'Criminal Elite - Surveillance Specialist', 5);
        $hero->addSkill(BonusTargets::SKILL_OPTIC_SYSTEMS, 'Criminal Elite - Surveillance Specialist', 10);
        $hero->addSkill(BonusTargets::SKILL_TV_VIDEO, 'Criminal Elite - Surveillance Specialist', 10);
        $hero->addSkill(BonusTargets::SKILL_PHOTOGRAPHY, 'Criminal Elite - Surveillance Specialist', 15);
        $hero->addSkill(BonusTargets::SKILL_RADIO_BASIC, 'Criminal Elite - Surveillance Specialist', 20);
        $hero->addSkill(BonusTargets::SKILL_RADIO_SCRAMBLER, 'Criminal Elite - Surveillance Specialist', 5);
        $hero->addSkill(BonusTargets::SKILL_BASIC_ELECTRONICS, 'Criminal Elite - Surveillance Specialist', 10);
        $hero->addSkill(BonusTargets::SKILL_PICK_LOCKS, 'Criminal Elite - Surveillance Specialist');

        $skills = $this->engine->skillPrograms->selectSkills(2, $hero, 0, BonusTargets::weaponProficienciesSkills(false));
        $hero->addSkills($skills, 'Criminal Elite - Surveillance Specialist', 0);

        $skills = $this->engine->skillPrograms->selectSkills(2, $hero, 0, BonusTargets::physicalSkills(false));
        $hero->addSkills($skills, 'Criminal Elite - Surveillance Specialist', 0);

        $skills = $this->engine->skillPrograms->selectSkills(2, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Criminal Elite - Surveillance Specialist', 0);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 20, 'Criminal Elite - Surveillance Specialist'));
    }

    /**
     * give thug bonuses
     *
     * @param Hero $hero the thug
     */
    private function thug(Hero &$hero)
    {
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
            new TableEntry(50, 'muscleBodyguard'),
            new TableEntry(75, 'punk2BitHood'),
            new TableEntry(100, 'conMan'),
        ]);
        $this->$thugType($hero);
    }

    private function thief(Hero &$hero)
    {
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

    private function muscleBodyguard(Hero &$hero)
    {
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

    private function punk2BitHood(Hero &$hero)
    {
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

    private function conMan(Hero &$hero)
    {
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

    private function criminalOrganizationSize()
    {
        return $this->engine->tableRoller->rollTable('Villain Criminal Organization - Size', [
            new TableEntry(40, 'Local: ' . $this->engine->roller->rollDice(new Roll('Villain Criminal Organization - size: local', 2, 4, 10)) . ' million dollars'),
            new TableEntry(80, 'National: ' . $this->engine->roller->rollDice(new Roll('Villain Criminal Organization - size: national', 1, 4)) . ' billion dollars'),
            new TableEntry(100, 'International: ' . $this->engine->roller->rollDice(new Roll('Villain Criminal Organization - size: international', 2, 4, 10)) . ' billion dollars'),
        ]);
    }

    private function criminalOrganization(Hero &$hero)
    {
        $roll = $this->engine->roller->rollPercent('Villain Criminal Organization');
        if ($roll <= 17) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Drug Smuggler; ' . $this->criminalOrganizationSize(), 'Criminal Organization - Drug Smugglers'));
        } else if ($roll <= 34) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Criminal Fence: deals in precious gems, gold, art treasures, high technology (components and plans), and occasionally heavy weapons and military vehicles.'
                . $this->engine->roller->rollDice(new Roll('Villain Criminal Organization - fence: size', 4, 6, 10)) . ' billion dollars', 'Villain Criminal Organization - fence'));
        } else if ($roll <= 55) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Criminal - Conducts all manner of illegal activity; ' . $this->criminalOrganizationSize(), 'Criminal Organization - Criminal'));
        } else if ($roll <= 70) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Mercenary Organization; ' . $this->criminalOrganizationSize(), 'Criminal Organization - Mercenary Organization'));
        } else if ($roll <= 84) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Secret Organization - A power crazed organization bent on world domination;' . $this->criminalOrganizationSize(), 'Criminal Organization - Secret Organization'));
        } else {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Criminal Scientific;' . $this->criminalOrganizationSize(), 'Criminal Organization - Criminal Scientific'));
        }
    }
}
