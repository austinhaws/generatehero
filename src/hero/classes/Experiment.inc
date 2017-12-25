<?php
namespace Heroes\hero\classes;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\superabilities\TableSuperAbilities;
use Heroes\tables\TableInsanity;

class SuperSoldierChoice
{
    /** @var string what they were attempting to do */
    public $attempt;
    /** @var Bonus[] bonuses to apply if this attempt was selected */
    public $bonuses;

    function __construct($attempt, $bonuses)
    {
        $this->attempt = $attempt;
        $this->bonuses = $bonuses;
    }
}

class Experiment extends BaseClass
{
    /** @var string nature of the experiment */
    public $experimentNature;
    /** @var string results of the experiment */
    public $experimentResults;
    /** @var string who sponsored the experiment */
    public $sponsor;
    /** @var string how the sponsor feels about the Experiement */
    public $sponsorStatus;


    public function __construct(Engine &$engine)
    {
        parent::__construct($engine, 'Experiment');
    }


    /**
     * create a experiment character
     *
     * @param Hero $hero the hero
     * @throws \Exception
     */
    function create(Hero &$hero, $options = false)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Experiment Base SDC'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Experiment starting money', 4, 4), 'Experiment Base SDC'));
        $this->hasCar($hero, 84);

        // step 1 : attributes - already done by generator

        // step 2 : education - will be rolled after class created since experiment will not set educationLevel of hero

        // step 4 : experiment effects
        $this->experimentEffects($hero);

        // step 3 : super powers
        if ($this->engine->roller->rollDice(new Roll('Experiment Power Type', 1, 100)) > 50) {
            $this->createSuperSoldier($hero);
        } else {
            $this->pickPowers($hero);
        }
    }

    /**
     * pick the hero's powers
     *
     * @param Hero $hero the hero
     * @throws \Exception
     */
    private function pickPowers(Hero &$hero)
    {
        list($numberMajor, $numberMinor) = $this->engine->tableRoller->rollTable('Experiment: Pick Powers', [
            // percent, # major, # minor
            new TableEntry(15, [1, 3]),
            new TableEntry(32, [0, 4]),
            new TableEntry(50, [1, 1]),
            new TableEntry(69, [1, 2]),
            new TableEntry(86, [0, 5]),
            new TableEntry(100, [2, 0]),
        ]);

        (new TableSuperAbilities($this->engine))->randomSuperAbilities($hero, $numberMajor, $numberMinor);
    }

    /**
     * @param Hero $hero the hero
     * @throws \Exception
     */
    private function createSuperSoldier(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Experiment - Super Soldier: The super-soldier is a catch phrase that refers to the experiment\'s intent to create a superior human killing machine.', 'Experiment'));

        // one minor super power
        (new TableSuperAbilities($this->engine))->randomSuperAbilities($hero, 0, 1);


        // 3 of the following super soldier options
        $choices = [
            // 1
            new SuperSoldierChoice('Attempted to make the character invulnerable.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::WEIGHT, 80, 'Super Soldier: Invulnerable'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::NATURAL_ARMOR_RATING, 14, 'Super Soldier: Invulnerable'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Super Soldier - Invulnerable: SDC', 4, 6), 'Super Soldier: Invulnerable'),
            ]),
            // 2
            new SuperSoldierChoice('Attempted to increase physical agility and dexterity.', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 20, 'Super Solder: PP'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_AGILITY_DEXTERITY, 5, 'Super Soldier: PP'),
            ]),
            // 3
            new SuperSoldierChoice('Attempted to Increase Physical Speed.', [
                new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::ATTRIBUTE_SPEED, 3, 'Super Soldier: Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Hyperactive and has trouble relaxing and sleeping', 'Super Soldier: Speed'),
            ]),
            // 4
            new SuperSoldierChoice('Mind and Body are more attuned to each other, increasing reaction time and alertness.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Super Soldier: Mind/Body'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 2, 'Super Soldier: Mind/Body'),
            ]),
            // 5
            new SuperSoldierChoice('Bionic implants in the head stimulates brain chemicals and glandular activity.', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 18, 'Super Soldier: Bionics'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Super Soldier - Bionics: PS', 1, 4), 'Super Soldier: Bionics'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, new Roll('Super Soldier - Bionics: Speed', 1, 6), 'Super Soldier: Bionics'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'The character is not affected by physical exhaustion/fatigue for the first two hours of strenuous activity. However, the character suffers from chronic headaches and eats four times as much as normal without gaining weight, because the higher metabolism burns up the calories.', 'Super Soldier: Bionics'),
            ]),
            // 6
            new SuperSoldierChoice('Brain Boost', [
               new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT, 14, 'Brain Boost'),
            ]),
            // 7
            new SuperSoldierChoice('Physical Transformation: The character is physically altered, with fat becoming lean muscles, bones strengthening, hair filling out, and physical impairments such as poor vision and poor hearing improved.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Super Soldier - Physical Transformation: PS', 1, 4), 'Super Soldier: Physical Transformation'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_BEAUTY, new Roll('Super soldier - Physical Transformation: PB', 2, 4), 'Super Soldier: Physical Transformation'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, new Roll('Super Soldier - Physical Transformation: Speed', 1, 6), 'Super Soldier: Physical Transformation'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Super Soldier - Physical Transformation: SDC', 4, 6), 'Super Soldier: Physical Transformation'),
            ]),
            // 8
            new SuperSoldierChoice('A bionic weapon system is built in to one of the character\'s hand and arm. This is not an artificial limb, but a bionic implant. The weapon responds to bio-electric impulses from teh brain and is under the complete control of the character. Unfortunately the power system is limited to a maximum of 10 blasts per hour.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Electrical Discharge: Does 1D6, 2D6 or 4D6 damage (character can adjust the degree of damage). Range: 50ft (15.3m).', 'Super Soldier: Bionic Weapon System'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Energy Blast: A concentrated bolt of energy, doing 1D6 or 2D6 damage. Range: 150ft (45.7m).', 'Super Soldier: Bionic Weapon System'),
            ]),
            // 9
            new SuperSoldierChoice('Bionic Sensor System built in to one of the character\'s hand and arm. This is not an artificial limb, but a bionic implant. The sensor alert the character to certain dangers or conditions.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Electronic Bug Detector: Range: 20ft (6.1m).', 'Super Soldier: Bionic Sensor System'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Explosives Detector: Range: 8ft (2.4m).', 'Super Soldier: Bionic Sensor System'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Heat Sensor: Picks up and measures heat, Range: 30ft (9.1m).', 'Super Soldier: Bionic Sensor System'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Radiation Detector: Picks up, pinpoints, and measures the degree of radioactivity.', 'Super Soldier: Bionic Sensor System'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Radio Scrambler: Will distort or "scramble" outgoing radio signals, preventing interception and interpretation by the enemy. The character must be using the radio.', 'Super Soldier: Bionic Sensor System'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Radio Meter: Picks up radio signals and registers them. Range: 40ft.', 'Super Soldier: Bionic Sensor System'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Infrared Warning System: Alerts the character whenever infrared light is placed on him.', 'Super Soldier: Bionic Sensor System'),
            ]),
        ];

        $this->engine->arrayTools->shuffle($choices);

        for ($x = 0; $x < 3; $x++) {
            $choice = array_shift($choices);
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, $choice->attempt, 'Experiment: Super Soldier'));
            foreach ($choice->bonuses as $bonus) {
                $hero->addBonus($bonus);
            }
        }
    }

    /**
     * @param Hero $hero the hero duh
     * @throws \Exception
     */
    private function experimentEffects(Hero &$hero)
    {
        // A: THE NATURE OF THE EXPERIMENT
        $this->experimentNature = $this->engine->tableRoller->rollTable('Experiment: nature', [
            new TableEntry(33, 'Chemical.'),
            new TableEntry(67, 'Radiation.'),
            new TableEntry(100, 'Chemical and radiation combined.'),
        ]);

        // B: THE RESULTS OF EXPERIMENT
        $this->experimentResults = $this->engine->tableRoller->rollTable('Experiment: result', [
            new TableEntry(20, 'Experiment to create a super being is a total success, but can not be duplicated'),
            new TableEntry(50, 'Accident: super ability completely unintentional'),
            new TableEntry(70, 'Unexpected side-effect of an experiment'),
            new TableEntry(100, 'Experiment to alter or improve the human body: an unknown x-factor has produced staggering results. Can not be duplicated at this time; requires further analysis.'),
        ]);

        // C: THE NUMBER OF SUPER ABILITIES
        // rolled elsewhere

        // D: SIDE-EFFECTS (Permanent)
        $bonus = $this->engine->tableRoller->rollTable('Experiment: Side Effects', [
            new TableEntry(8, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Hair Growth Stimulated; all body hair tripled.', 'Experiment Side Effect')),

            new TableEntry(10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Odd Skin Pigmentation: Light Green.', 'Experiment Side Effect')),
            new TableEntry(11, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Odd Skin Pigmentation: Pale Bluish White.', 'Experiment Side Effect')),
            new TableEntry(13, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Odd Skin Pigmentation: Light Grey.', 'Experiment Side Effect')),
            new TableEntry(14, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Odd Skin Pigmentation: Pale White.', 'Experiment Side Effect')),
            new TableEntry(16, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Odd Skin Pigmentation: Dark Brown.', 'Experiment Side Effect')),

            new TableEntry(24, [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Odd Skin Texture detracts from physical beauty.', 'Experiment Side Effect'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_BEAUTY, -2, 'Odd Skin Texture'),
            ]),
            new TableEntry(33, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Whole Body Glows faintly in the dark; makes a great target at night.', 'Experiment Side Effect')),
            new TableEntry(40, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Vulnerable to Radioactivity (even the tiniest levels). Reduce all physical attributes by half while exposed to radioactivity.', 'Experiment Side Effect')),
            new TableEntry(47, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Must Physically Transform every time power is used. Add 1D4 feet to height, add 3D4 x 10 to weight, skin color changes. On the good side, it adds 204 x 10 SDC and +2 to damage.', 'Experiment Side Effect')),
            new TableEntry(54, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Requires Energy for Nourishment: Can not eat or drink normal food; must absorb energy such as electrical or heat energy (not organic life energies). Must have 200,000 volts per day. On the good side, the character never gets hungry nor does he tire in sunlight/heat and is resistant to energy weapons. Electrical blasts do half damage.', 'Experiment Side Effect')),
            new TableEntry(63, [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Increased Mass: Physical proportions unchanged, but mass/weight increased.', 'Experiment Side Effect'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::WEIGHT, new Roll('Increased Mass: Weight', 2, 4, 10), 'Increased Mass'),
                new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::ATTRIBUTE_SPEED, 0.8, 'Increased Mass'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Increased Mass: SDC', 1, 6, 10), 'Increased Mass'),
            ]),
            new TableEntry(70, [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Chemical Resistance: An automatic saving throw against all chemicals/drugs/toxins. Unfortunately, this applies to good lifesaving chemicals/drugs as well as deadly toxins.', 'Experiment Side Effect'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_TOXINS, 5, 'Chemical Resistance'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_CHEMICALS, 5, 'Chemical Resistance'),
            ]),
            new TableEntry(77, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Breathe Without Air: Character does not seem to breathe, but still functions normally, even in an airless environments. Impervious to gases. On the down side the character has no sense of smell or taste. None!', 'Experiment Side Effect')),
            new TableEntry(84, [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Chronic Pain', 'Experiment Side Effect'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, -1, 'Chronic Pain'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, -1, 'Chronic Pain'),
            ]),
            new TableEntry(93, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Hair Permanently Falls Out: All hair on the head and face falls out.', 'Experiment Side Effect')),
            new TableEntry(100, [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'No Facial Features: (including facial hair) Except for a slit for a mouth, two tiny holes for nostrils, a slight ridge just above what was once eye sockets, and button sized ears, the face is featureless. Despite this physical deformity, the character can breathe. hear, speak, and see as good, or better than ever. Vision: Perfect 20/20 vision, even if the person needed eyeglasses before. Can naturally see in the infrared and ultraviolet range (600ft/ 183m). Sense of Hearing and Smell is much sharper. The character can also discern between sounds much more clearly.', 'Experiment Side Effect'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 2, 'No Facial features'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::IMITATE_VOICES, 20, 'No Facial features'),
                new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::ATTRIBUTE_PHYSICAL_BEAUTY, .5, 'No Facial features'),
            ]),
        ]);

        // No Facial features: Also, roll on the random insanity table resulting from trauma
        if (is_array($bonus) && $bonus[1]->explanation == 'No Facial features') {
            (new TableInsanity($this->engine))->rollInsanity($hero);
        }

        // bonus may be an array
        if (is_array($bonus)) {
            foreach ($bonus as $b) {
                $hero->addBonus($b);
            }
        } else {
            $hero->addBonus($bonus);
        }

        // TABLE E: THE SPONSORING ORGANIZATION
        $this->sponsor = $this->engine->tableRoller->rollTable('Sponsoring Organization', [
            new TableEntry(24, 'Private Industry'),
            new TableEntry(50, 'Medical Research Facility'),
            new TableEntry(75, 'Military'),
            new TableEntry(80, 'Secret Organization: Medical'),
            new TableEntry(87, 'Secret Organization: Criminal'),
            new TableEntry(94, 'Secret Organization: Crime Fighting'),
            new TableEntry(100, 'Secret Organization: Military'),
        ]);

        // TABLE F: STATUS WITH SPONSORING ORGANIZATION
        $this->sponsorStatus = $this->engine->tableRoller->rollTable('Sponsor Status', [
            new TableEntry(21, 'Allowed to leave, very good, friendly relationship.'),
            new TableEntry(45, 'The power is unknown to the organization; manifested itself long after the experiment/incident.'),
            new TableEntry(58, 'Allowed to leave after a great antagonism/conflict. Not friendly, but may deal with the super being occasionally.'),
            new TableEntry(64, 'Ran away; secretly hunted by the organization. Hostile but not deadly; wants the super being for further experimentation/research.'),
            new TableEntry(77, 'Thrown out of the program. All ties are permanently dissolved; Very angry/hostile toward the character.'),
            new TableEntry(89, 'Ran away; considered to be a criminal and/or dangerous. Hunted by law enforcement agencies and the organization.'),
            new TableEntry(100, 'Currently employed by the organization. Double the usual income for that position.'),
        ]);
    }
}