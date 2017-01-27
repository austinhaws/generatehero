<?php
namespace Heroes\hero\classes;

use Heroes\engine\TableEntry;
use Heroes\enums\BonusTypes;
use Heroes\enums\Skills;
use Heroes\hero\Hero;

class Aliens extends BaseClass
{
    public $appearance;

    function imageName()
    {
        return 'aliens.png';
    }

    function create(Hero &$hero)
    {
        // appearance
        $appearance = $this->engine->tableRoller->rollTable('appearance', [
            new TableEntry(30, 'Human-Like'),
            new TableEntry(50, 'Humanoid'),
            new TableEntry(55, 'Insect Appearance'),
            new TableEntry(60, 'Humanoid Amphibian'),
            new TableEntry(65, 'Vegetation'),
            new TableEntry(70, 'Humanoid Reptilian'),
            new TableEntry(75, 'Humanoid Canine'),
            new TableEntry(80, 'Humanoid Avian'),
            new TableEntry(85, 'Humanoid Mineral'),
            new TableEntry(90, 'Humanoid Feline'),
            new TableEntry(95, 'Humanoid Ape'),
            new TableEntry(100, 'Humanoid Aquatic'),
        ]);

        switch ($appearance) {
            case 'Human-Like':
                $this->appearance = $appearance . ': A humanoid alien that so resembles humans as to be indistinguishable from Earth people.';
                break;
            case 'Humanoid':
                $this->appearance_humanoid($hero);
                break;
            case 'Insect Appearance':
                break;
            case 'Humanoid Amphibian':
                break;
            case 'Vegetation':
                break;
            case 'Humanoid Reptilian':
                break;
            case 'Humanoid Canine':
                break;
            case 'Humanoid Avian':
                break;
            case 'Humanoid Mineral':
                break;
            case 'Humanoid Feline':
                break;
            case 'Humanoid Ape':
                break;
            case 'Humanoid Aquatic':
                break;
        }

        // physiological modification

        // super ability

        // education

        // coming to earth

        // familiarity

        // equipment

        // vehicle

        // money

        // other stuff

    }

    private function appearance_humanoid(Hero &$hero)
    {
        $this->appearance = 'Humanoid: ';

        $characteristic = $this->engine->tableRoller->rollTable('Alien Characteristic', [
            new TableEntry(16, 'Pointy larger than normal ears'),
            new TableEntry(39, 'Odd skin color'),
            new TableEntry(43, 'Ambidextrous'),
            new TableEntry(48, 'Odd hair color'),
            new TableEntry(53, 'Double-Jointed'),
            new TableEntry(58, 'Unusual Eyes'),
            new TableEntry(64, 'Extreme amount of body hair'),
            new TableEntry(68, 'Prehensile feet/toes'),
            new TableEntry(72, 'Scaly skin'),
            new TableEntry(76, 'No body hair'),
            new TableEntry(79, 'Small horns'),
            new TableEntry(84, 'Tough, lumpy skin'),
            new TableEntry(89, 'Prehensile tail'),
            new TableEntry(94, 'Retractable claws'),
            new TableEntry(100, 'Stocky'),
        ]);

        switch ($characteristic) {
            case 'Pointy, larger than normal ears':
                $this->appearance .= $characteristic;
                break;

            case 'Odd skin color':
                $color = $this->engine->tableRoller->rollTable('Characteristic: Skin Color', [
                   new TableEntry(10, 'Yellow'),
                   new TableEntry(20, 'Green'),
                   new TableEntry(30, 'Red'),
                   new TableEntry(40, 'Grey'),
                   new TableEntry(50, 'Light Blue'),
                   new TableEntry(60, 'Stark White'),
                   new TableEntry(70, 'Dark Blue'),
                   new TableEntry(80, 'Black (as in coal black)'),
                   new TableEntry(90, 'Purple'),
                   new TableEntry(100, 'Orange'),
                ]);
                $this->appearance .= "Odd skin color - $color";
                break;

            case 'Ambidextrous':
                $this->appearance .= "$characteristic - Can use the right and left hand with equal skill and dexterity.";
                $bonusReason = 'Alien: ambidextrous';
                $hero->addBonus(BonusTypes::ATTACKS_PER_MELEE, 1, $bonusReason);
                $hero->addBonus(BonusTypes::PARRY, 1, $bonusReason);
                $hero->addSkillBonus(Skills::CLIMBING, 10, $bonusReason);
                $hero->addSkillBonus(Skills::ESCAPE_ARTIST, 5, $bonusReason);
                $hero->addSkillBonus(Skills::PICK_LOCKS, 5, $bonusReason);
                $hero->addSkillBonus(Skills::MECHANICAL_REPAIR, 5, $bonusReason);
                $hero->addSkillBonus(Skills::ELECTRICAL_REPAIR, 5, $bonusReason);
                break;

            case 'Odd hair color':
                $color = $this->engine->tableRoller->rollTable('Characteristic: Hair Color', [
                   new TableEntry(10, 'Green'),
                   new TableEntry(20, 'Light Blue'),
                   new TableEntry(30, 'White Streaked'),
                   new TableEntry(40, 'Bright, Flame Red'),
                   new TableEntry(50, 'Stark White'),
                   new TableEntry(60, 'Bright Yellow'),
                   new TableEntry(70, 'Metallic Silver'),
                   new TableEntry(80, 'Dark Blue'),
                   new TableEntry(90, 'Purple'),
                   new TableEntry(100, 'Orange'),
                ]);
                $this->appearance .= "Odd hair color - $color";
                break;

            case 'Double-Jointed':
                $this->appearance .= 'Alien: Double-Jointed; Extremely limber bones and can twist and bend their bones in to normally impossible positions.';
                $hero->addBonus(BonusTypes::ROLL, 2, 'Alien: Double-Jointed');
                break;

            case 'Unusual Eyes':
                $color = $this->engine->tableRoller->rollTable('Characteristic: Unusual Eyes', [
                    new TableEntry(17, 'Very small'),
                    new TableEntry(34, 'Round'),
                    new TableEntry(55, 'Very large'),
                    new TableEntry(75, 'Odd color'),
                    new TableEntry(89, 'Very Elliptical'),
                    new TableEntry(100, 'Glowing'),
                ]);
                $this->appearance .= "Unusual Eyes - $color";
                break;

            case 'Extreme amount of body hair':
                break;

            case 'Prehensile feet/toes':
                break;

            case 'Scaly skin':
                break;

            case 'No body hair':
                break;

            case 'Small horns':
                break;

            case 'Tough, lumpy skin':
                break;

            case 'Prehensile tail':
                break;

            case 'Retractable claws':
                break;

            case 'Stocky':
                break;
        }
    }
}