<?php
namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\TableEducation;

class Hardware extends BaseClass
{
    // electrical, mechanical, weapons
    public $hardwareType;

    public $workshopBudget;
    public $equipmentBudget;

    public $mechanicalSponsorStatus;

    /**
     * create a experiment character
     *
     * @param Hero $hero the hero
     * @throws \Exception ya ya, whatever
     */
    public function create(Hero &$hero)
    {
        // step 1 : attributes - already done by generator; IQ must be at least 9
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, 9, BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT, 'Hardware Base IQ'));


        // step 2 : education - normal education but with one less skill program
        (new TableEducation($this->engine))->rollEducationLevel($hero, -1);

        // step 3 : hardware type
        $roll = $this->engine->roller->rollDice(new Roll('Hardware Power Type', 1, 3));
        switch ($roll) {
            case 1:
                $this->hardwareType = 'Electrical';
                break;
            case 2:
                $this->hardwareType = 'Mechanical';
                break;
            case 3:
                $this->hardwareType = 'Weapons';
                break;
            default:
                throw new \Exception("Unknown hardware power type: $roll");
        }

        // step 4 : experiment effects
        $method = $this->hardwareType;
        $this->$method($hero);
    }

    /**
     * make an electrical hardware character
     *
     * @param Hero $hero the hero
     */
    private function electrical(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_ELECTRICAL_ENGINEER, 30, 'Hardware: Electrical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS, 20, 'Hardware: Electrical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_MATHEMATICS_ADVANCED, 20, 'Hardware: Electrical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_COMPUTER_OPERATION, 30, 'Hardware: Electrical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_COMPUTER_PROGRAMMING, 30, 'Hardware: Electrical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_BASIC_MECHANICS, 10, 'Hardware: Electrical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_SURVEILLANCE, 30, 'Hardware: Electrical'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Hot Wiring: In addition to hot wiring cars, the character can electrically by-pass alarms, telephone lines, and electrical circuits.', 'Hardware: Electrical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SPECIAL_SKILL_HOT_WIRING, 92, 'Hardware: Electrical'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Computer Hacking or Hacker: This is a slang term for a computer operator who gains access to other computers, and breaks their security code to plunder their data. This skill includes an in depth knowledge of computer programs useful in pirating computer information.', 'Hardware: Electrical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SPECIAL_SKILL_COMPUTER_HACKING, 82, 'Hardware: Electrical'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Recognize Quality And Complexity Of Electrical Systems: Accurately estimate the level of complexity, specific aspects of difficulty, and time required to do the job (repair, by-pass, etc.).', 'Hardware: Electrical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SPECIAL_ESTIMATE_ELECTRICAL_SYSTEMS, 55, 'Hardware: Electrical'));

        // determine electrical equipment
        $this->equipmentBudget = $this->engine->tableRoller->rollTable('Hardware: Electrical - Equipment Budget', [
           new TableEntry(15, 8000),
           new TableEntry(29, 10000),
           new TableEntry(45, 12000),
           new TableEntry(60, 15000),
           new TableEntry(75, 18000),
           new TableEntry(89, 21000),
           new TableEntry(100, 24000),
        ]);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, '$' . $this->equipmentBudget . ' available to spend on electrical equipment and supplies.', 'Hardware: Electrical'));

        $this->workshopBudget = $this->engine->roller->rollDice(new Roll('Hardware: Electrical - Workshop Budget', 2, 4, 10000));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 35, 'Hardware: Electrical'));
    }

    private function mechanical(Hero &$hero)
    {
        $skills = BonusTargets::mechanicalSkills(false);
        $skills[] = BonusTargets::SKILL_MECHANICAL_ENGINEERING;

        $bonuses = [];
        foreach ($skills as $skill) {
            $bonuses[] = new Bonus(Bonus::BONUS_TYPE_ADD, $skill, 30, 'Hardware: Mechanical');
        }
        $bonuses[] = new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS, 25, 'Hardware: Mechanical');
        $bonuses[] = new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_WEAPON_SYSTEMS, 20, 'Hardware: Mechanical');
        $bonuses[] = new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_MATHEMATICS_ADVANCED, 24, 'Hardware: Mechanical');

        $this->engine->arrayTools->shuffle($bonuses);

        // pick 3 skills from options
        for ($x = 0; $x < 3; $x++) {
            $hero->addBonus(array_pop($bonuses));
        }

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_BASIC_ELECTRONICS, 30, 'Hardware: Mechanical'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SPECIAL_BUILDING_SUPER_VEHICLES, 94, 'Hardware: Mechanical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SPECIAL_RECOGNIZE_VEHICLE_QUALITY, 55, 'Hardware: Mechanical'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_LOCKSMITH, 5, 'Hardware: Mechanical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_LAND_NAVIGATION, 5, 'Hardware: Mechanical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_NAVIGATION, 5, 'Hardware: Mechanical'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_NAVIGATION_SPACE, 5, 'Hardware: Mechanical'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_PILOTING, 5, 'Hardware: Mechanical'));

        $this->workshopBudget = $this->engine->roller->rollDice(new Roll('Hardware: Mechanical - shop', 3, 4, 10000));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 35, 'Hardware: Mechanical'));

        $this->equipmentBudget = $this->engine->tableRoller->rollTable('Hardware: Mechanical - Vehicle Budget', [
            new TableEntry(15, 70000),
            new TableEntry(26, 120000),
            new TableEntry(38, 250000),
            new TableEntry(50, 500000),
            new TableEntry(60, 1100000),
            new TableEntry(70, 2000000),
            new TableEntry(81, 4000000),
            new TableEntry(90, 8000000),
            new TableEntry(100, 12000000),
        ]);

        if ($this->equipmentBudget > 500000) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Sponsor provides funds for super vehicle', 'Hardware: Mechanical'));
            $this->mechanicalSponsorStatus = $this->engine->tableRoller->rollTable('Hardware: Mechanical - Sponsor Status', [
                new TableEntry(19, 'Allowed to leave; very good, friendly relationship'),
                new TableEntry(41, 'Allowed to leave after a great antagonism/conflict; Not friendly, but may aid the character'),
                new TableEntry(64, 'Thrown out of the program, all ties are permanently dissolved; Very angry/hostile toward the character'),
                new TableEntry(89, 'Ran away; Secretly hunted by the organization; Hostile, but not necessarily deadly'),
                new TableEntry(100, 'Ran away; Considered to be a criminal and extremely dangerous; Hunted by law enforcement agencies and the organization'),
            ]);
        }
    }

    private function weapons(Hero &$hero)
    {
        // Select 2 Ancient WP
        $skills = BonusTargets::wpAncientWeaponsSkills(false);
        $this->engine->arrayTools->shuffle($skills);
        foreach (array_slice($skills, 0, 2) as $skill) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, $skill, 0, 'Hardware: Weapons'));
        }

        // 4 Modern WP
        $skills = BonusTargets::wpModernWeaponsSkills(false);
        $this->engine->arrayTools->shuffle($skills);
        foreach (array_slice($skills, 0, 4) as $skill) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, $skill, 0, 'Hardware: Weapons'));
        }

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_DEMOLITIONS, 24, 'Hardware: Weapons'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_DEMOLITIONS_DISPOSAL, 24, 'Hardware: Weapons'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_SNIPER, 0, 'Hardware: Weapons'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_BASIC_ELECTRONICS, 10, 'Hardware: Weapons'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_BASIC_MECHANICS, 20, 'Hardware: Weapons'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SPECIAL_MAKE_AND_MODIFY_WEAPONS, 92, 'Hardware: Weapons'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SPECIAL_RECOGNIZE_WEAPON_QUALITY, 55, 'Hardware: Weapons'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::STRIKE, 1, 'Hardware: Weapons'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, '+2 to strike and parry with one very specific type of weapon (ie, such as a bastard sword, rather than swords in general, or a Model 61 Skorpion (7.65mm) rather than automatic pistols in general)', 'Hardware: Weapons'));


        $this->workshopBudget = $this->engine->roller->rollDice(new Roll('Hardware: Weapons - shop', 2, 4, 10000));

        $this->equipmentBudget = $this->engine->tableRoller->rollTable('Hardware: Weapons - Budget', [
            new TableEntry(15, 8000),
            new TableEntry(29, 10000),
            new TableEntry(45, 12000),
            new TableEntry(60, 15000),
            new TableEntry(75, 18000),
            new TableEntry(88, 20000),
            new TableEntry(100, 23000),
        ]);
    }
}