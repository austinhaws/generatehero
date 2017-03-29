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
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ESTIMATE_ELECTRICAL_SYSTEMS, 55, 'Hardware: Electrical'));

        // determine electrical equipment
        $equipmentBudget = $this->engine->tableRoller->rollTable('Hardware: Electrical - Equipment Budget', [
           new TableEntry(15, 8000),
           new TableEntry(29, 10000),
           new TableEntry(45, 12000),
           new TableEntry(60, 15000),
           new TableEntry(75, 18000),
           new TableEntry(89, 21000),
           new TableEntry(100, 24000),
        ]);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, '$' . $equipmentBudget . ' available to spend on electrical equipment and supplies.', 'Hardware: Electrical'));

        $workshopBudget = $this->engine->roller->rollDice(new Roll('Hardware: Electrical - Workshop Budget', 2, 4, 10000));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, '$' . $workshopBudget . ' spent on outfitting workshop, equipping it with all the tools and necessary equipment of the trade.', 'Hardware: Electrical'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 35, 'Hardware: Electrical'));
    }

    private function mechanical(Hero &$hero)
    {
        throw new \Exception("mechanical needs implemented");
    }

    private function weapons(Hero &$hero)
    {
        throw new \Exception("weapons needs implemented");
    }
}