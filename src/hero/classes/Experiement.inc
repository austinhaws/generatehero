<?php
namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\TableInsanity;

class Experiement extends BaseClass
{
    public $experimentNature;
    public $experimentResults;
    public $sponsor;
    public $sponsorStatus;

    function create(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Experiment Base SDC'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Experiment starting money', 4, 4), 'Experiment Base SDC'));
        $this->hasCar($hero, 84);

        // step 1 : attributes - already done by generator

        // step 2 : education - will be rolled after class created since experiment will not set educationLevel of hero


        // step 3 : super powers
        super solider vs powers
        $this->pick powers
        $this->superSoldier

        // step 4 : experiment effects
        $this->experimentEffects($hero);

    }

    /**
     * @param Hero $hero the hero duh
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
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Chemical Resistance: An automatic savings throw against all chemicals/drugs/toxins. Unfortunately, this applies to good lifesaving chemicals/drugs as well as deadly toxins.', 'Experiment Side Effect'),
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