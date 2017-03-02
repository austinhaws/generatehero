<?php
namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

class Bionics extends BaseClass
{
    // how much money the bionic had to spend on bionics
    public $startingBudget;

    // why was the character considered for bionic modification?
    public $conditions;

    public $sponsor;

    public $sponsorStatus;

    public $bionics;

    function imageName()
    {
        return 'bionics.png';
    }

    function create(Hero &$hero)
    {
        // all bionics have SDC of 30
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Bionic Base SDC'));

        // step 1 : attributes - already done by generator

        // step 2 : education - will be rolled after bionic created since bionic will not set educationLevel of hero

        // step 3 : budget
        $this->determineBudget();

        // step 4 : building the cyborg
        $this->chooseBionics();

        // step 5 : background information
        $this->backgroundInformation();

        // step 6 : money
        $this->rollMoney($hero);

    }

    private function backgroundInformation()
    {
        $this->conditions = $this->engine->tableRoller->rollTable('Bionic: Conditions for Bionic Reconstruction', [
            new TableEntry(10, 'Healthy specimen; destitute. Deemed psychologically suitable.'),
            new TableEntry(20, 'Healthy specimen; fantastically motivated toward bionic research. Deemed psychologically suitable.'),

            new TableEntry(25, 'Lost legs to disease.'),
            new TableEntry(30, 'Lost legs to accident.'),
            new TableEntry(35, 'Lost both arms to disease.'),
            new TableEntry(40, 'Lost both arms to accident.'),

            new TableEntry(60, 'Paraplegic; no hope of recovery.'),

            new TableEntry(70, 'Deteriorating bone disease; no hope for recovery or normal life.'),
            new TableEntry(80, 'Deteriorating muscle disease; no hope for recovery or normal life.'),

            new TableEntry(100, 'Completely paralyzed no brain damage; no hope for recovery.'),
        ]);

        $this->sponsor = $this->engine->tableRoller->rollTable('Bionic: Sponsor', [
            new TableEntry(25, 'Medical research facility'),
            new TableEntry(50, 'Private industry'),
            new TableEntry(56, 'Secret organization: Medical'),
            new TableEntry(62, 'Secret organization: Criminal'),
            new TableEntry(68, 'Secret organization: Crime Fighting'),
            new TableEntry(75, 'Secret organization: Military'),
            new TableEntry(100, 'Military'),
        ]);

        $this->sponsorStatus = $this->engine->tableRoller->rollTable('Bionic: Sponsor Status', [
            new TableEntry(19, 'Allowed to leave; very good, friendly relationship.'),
            new TableEntry(41, 'Allowed to leave after a great antagonism/conflict. Not friendly, but may aid the character.'),
            new TableEntry(64, 'Thrown out of the program! All ties are permanently dissolved; very angry/hostile toward the character.'),
            new TableEntry(89, 'Ran away; secretly hunted by the organization. Hostile, but not necessarily deadly.'),
            new TableEntry(100, 'Ran away; considered to be a criminal and extremely dangerous. Hunted by law enforcement agencies and the sponsor.'),
        ]);
    }

    private function rollMoney(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Bionic Starting Wealth', 4, 4, 100), 'Bionic Starting Wealth'));

        if ($this->engine->roller->rollDice(new Roll('Bionic Has Car?', 1, 100)) <= 80) {
            $age = $this->engine->roller->rollDice(new Roll('Bionic Car Age', 1, 6));
            $years = 'year' . ($age > 1 ? 's' : '');
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, "Owns car that is $age $years old.", 'Bionic Starting Car'));
        }
    }

    private function determineBudget()
    {
        $this->startingBudget = $this->engine->tableRoller->rollTable('Bionic Budget', [
            new TableEntry(17, 6600000),
            new TableEntry(33, 7200000),
            new TableEntry(49, 8000000),
            new TableEntry(66, 8500000),
            new TableEntry(84, 9000000),
            new TableEntry(100, 9500000),
        ]);
    }

    private function chooseBionics()
    {
        echo 'CHoosing bionics needs implemented';
    }
}