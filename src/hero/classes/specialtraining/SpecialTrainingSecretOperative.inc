<?php

namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\enums\SkillPrograms;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\TableEducation;

class SpecialTrainingSecretOperative extends BaseClass
{
    /** @var string who sponsored this operative? */
    public $sponsoringOrganization;

    /** @var string relation ship with sponsoring organization */
    public $sponsoringOrganizationStatus;

    public function create(Hero &$hero, $options = false)
    {
        $this->modifyAttributes($hero);

        $this->applyEducation($hero);

        $this->giveSpecialEquipment($hero);

        $this->determineSponsor($hero);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 30, 'Secret Operative - SDC'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, new Roll('Secret Operative - SDC Bonus', 1, 6, 10), 'Secret Operative - SDC Bonus'));
    }

    private function modifyAttributes(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Secret Operative - PS', 1, 6), 'Secret Operative - PS'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Secret Operative - PP', 1, 4), 'Secret Operative - PP'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Secret Operative - PE', 1, 6), 'Secret Operative - PE'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Secret Operative - MA', 1, 6), 'Secret Operative - MA'));
    }

    private function applyEducation(Hero &$hero)
    {
        $hero->educationLevel = TableEducation::SECRET_OPERATIVE;

        $hero->addSkill(BonusTargets::SKILL_MATHEMATICS_BASIC, 'Secret Operative - education', 98);
        $hero->addSkill(BonusTargets::SKILL_PILOT_AUTOMOBILE, 'Secret Operative - education', 98);

        if ($this->engine->roller->rollPercent('Secret Operative - Hand to Hand') > 50) {
            $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_EXPERT, 'Secret Operative - Education');
        } else {
            $hero->addSkill(BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS, 'Secret Operative - Education');
        }

        $skillPrograms = new SkillPrograms($this->engine);
        $skills = $skillPrograms->selectSkills(9, $hero, 25, array_merge(BonusTargets::espionageSkills(false), BonusTargets::militarySkills(false)));
        $hero->addSkills($skills, 'Secret Operative - education', 25);

        $skills = $skillPrograms->selectSkills(4, $hero, 20, BonusTargets::physicalSkills(false));
        $hero->addSkills($skills, 'Secret Operative - education', 20);

        $skills = $skillPrograms->selectSkills(2, $hero, 20, BonusTargets::pilotAdvancedSkills(false));
        $hero->addSkills($skills, 'Secret Operative - education', 20);

        $skills = $skillPrograms->selectSkills(2, $hero, 25, BonusTargets::communicationSkills(false));
        $hero->addSkills($skills, 'Secret Operative - education', 25);

        $skills = $skillPrograms->selectSkills(2, $hero, 0, BonusTargets::wpAncientWeaponsSkills(false));
        $hero->addSkills($skills, 'Secret Operative - education', 0);

        $hero->addSkill(BonusTargets::SKILL_WP_ENERGY_PISTOL, 'Secret Operative - education');
        $hero->addSkill(BonusTargets::SKILL_WP_ENERGY_RIFLE, 'Secret Operative - education');

        $skills = $skillPrograms->selectSkills(3, $hero, 0, BonusTargets::wpModernWeaponsSkills(false));
        $hero->addSkills($skills, 'Secret Operative - education', 0);

        $skills = $skillPrograms->selectSkills(8, $hero, 0, BonusTargets::allSkills(true));
        $hero->addSkills($skills, 'Secret Operative - education', 0);
    }

    private function giveSpecialEquipment(Hero &$hero)
    {
        $bonuses = [
            'Lightly armored: AR 12, add 200 SDC',
            'Bullet-proof windshields: AR 16, SDC 200 each',
            'Souped-up turbo engine: 280mph maximum speed',
            'Mini-Radar: 5 mile (Skm) range',
            'Oxygen mask and air supply: 1 hour',
            'Retractable, rear scat dividing wall: AR 16, SDC 150',
            'Pilot controlled locks',
            'Knock-out gas: fills the car',
            'Concealed, front mounted 5.56mm machinegun',
            'Concealed, rear mounted 5.56mm machinegun',
            'Concealed, front mounter laser: 6D6 damage, Range: 3000ft',
            'Concealed, rear mounted laser',
            'Mini-Missile Launcher: four missiles - 1D4 x 10 damage each, Range: 4000ft (1200m)',
            'Flotation devices built in the under carriage so it will float',
            'Ejection scat',
        ];
        // pick 8
        $bonuses = array_slice($this->engine->arrayTools->shuffle($bonuses), 0, 8);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Souped-Up Car: ' . implode('; ', $bonuses), 'Secret Operative - Equipment'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, '2 Energy Weapons and six energy clips each', 'Secret Operative - Equipment'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, '12 hand grenades', 'Secret Operative - Equipment'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, '4 modern weapons', 'Secret Operative - Equipment'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Jet Pack: Speed 150mph, altitude 2000ft', 'Secret Operative - Equipment'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, '2 bionic implants', 'Secret Operative - Equipment'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Secrete Operative - money', 2, 4, 1000), 'Secret Operative - Equipment'));
    }

    private function determineSponsor(Hero &$hero)
    {
        $this->sponsoringOrganization = $this->engine->tableRoller->rollTable('Secret Operative - Organization', [
            new TableEntry(16, 'Criminal (intended for criminal activity)'),
            new TableEntry(36, 'Government (intended for any kind of needs)'),

            new TableEntry(44, 'Secret Organization or society - Altruistic'),
            new TableEntry(52, 'Secret Organization or society - Crime-fighting'),
            new TableEntry(60, 'Secret Organization or society - Revenge'),

            new TableEntry(63, 'Private Industry - Altruistic'),
            new TableEntry(67, 'Private Industry - Crime-fighting'),
            new TableEntry(71, 'Private Industry - Military prototypes (being field tested)'),
            new TableEntry(75, 'Private Industry - Public Relations'),

            new TableEntry(77, 'Foreign Government - Spy to study and observe the country'),
            new TableEntry(80, 'Foreign Government - Altruistic'),
            new TableEntry(83, 'Foreign Government - Military prototypes'),
            new TableEntry(86, 'Foreign Government - Alien Culture secretly studying and trying to help mankind'),

            new TableEntry(90, 'Independently wealthy tycoon worth nearly a billion dollars - For kicks, fun'),
            new TableEntry(95, 'Independently wealthy tycoon worth nearly a billion dollars - Altruistic'),
            new TableEntry(100, 'Independently wealthy tycoon worth nearly a billion dollars - Revenge'),
        ]);

        $this->sponsoringOrganizationStatus = $this->engine->tableRoller->rollTable('Secret Operative - Organization Status', [
            new TableEntry(17, 'Test Pilot: lent equipment for field testing. The use of the equipment is left up to the character'),

            new TableEntry(31, 'Special Federal Operative: sent in to a trouble spot to deal with crime in his own special way. Disliked by local lawmen'),
            new TableEntry(34, 'Special Federal Operative: sent in to a trouble spot to deal with crime in his own special way. Local authorities tolerate and assist'),

            new TableEntry(51, 'Freelance Spy Turned Vigilante'),
            new TableEntry(68, 'Rogue Agent: quit the organization'),
            new TableEntry(84, 'Sanctioned Agent: operates with full public support of sponsor'),
            new TableEntry(100, 'Rejected: thrown out of the program'),
        ]);
    }
}
