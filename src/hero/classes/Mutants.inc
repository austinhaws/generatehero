<?php
namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\superabilities\TablePsionics;
use Heroes\tables\superabilities\TableSuperAbilities;

class Mutants extends BaseClass
{
    // has psionics?
    public $psionics;
    // how many isp points does I have?
    public $isp;

    // cause of mutation
    public $cause;
    // what makes me weird
    public $characteristics;

    public function postCreate(Hero &$hero)
    {
        parent::postCreate($hero);
        if ($this->psionics) {
            $this->isp = (new TablePsionics($this->engine))->mutantAlienISP($hero, $this->engine);
        }
    }


    /**
     * create a character's class
     *
     * @param Hero $hero the hero
     * @throws \Exception ya ya, whatever
     */
    public function create(Hero &$hero)
    {

        if ($this->engine->roller->rollDice(new Roll('Mutant Type', 1, 2)) === 1) {
            $this->createMutant($hero);
        } else {
            $this->createAnimalMutant($hero);
        }
    }

    private function createAnimalMutant(Hero &$hero) {

    }

    private function createMutant(Hero &$hero) {
        // step 1 : attributes - already done by generator; education - normal education

        // step 2 : THE CAUSE OF THE MUTATION
        $this->cause();

        // step 3: UNUSUAL PHYSICAL CHARACTERISTICS
        $this->unusualCharacteristics();


        // mutants starting SDC & Cash
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Mutant'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Mutant - Starting Money', 4, 4, 100), 'Mutant'));
        $this->hasCar($hero, 88);

        // determine super abilities / psionics
        if ($this->engine->roller->rollDice(new Roll('Mutant Abilities', 1, 2)) === 1) {
            (new TableSuperAbilities($this->engine))->randomSuperAbilities($hero);
        } else {
            $this->psionics = true;
            (new Psionics($this->engine))->createMutantAlien($hero);
        }
    }

    private function cause() {
        $this->cause = $this->engine->tableRoller->rollTable('Mutant: cause', [
            new TableEntry(20, 'An unknown, random element. A complete mystery.'),
            new TableEntry(40, 'Accidental encounter with \'strange stuff\'. This can be almost anything: industrial waste, chemicals, radiation, alien sub-stance, energy, or other strangeness.'),
            new TableEntry(60, 'Genetic aberration. Mutant gene structure (a million in one chance of fate) is responsible for the mutation and powers.'),
            new TableEntry(80, 'Deliberate Experimentation. Some kind of laboratory experiment that purposely mutates the individual.'),
            new TableEntry(100, 'Radiation. An unexplainable mutant transformation caused by exposure to some type of radiation (usually accidental). It is likely that the radiation itself is not the direct cause of the mutation, but triggers a mutating agent (probably genetic) which has laid dormant within the individual.'),
        ]);
    }

    private function unusualCharacteristics()
    {
        list($this->characteristics, $bonuses) = $this->engine->tableRoller->rollTable('Mutant: unusual', [
            new TableEntry(34, ['No unusual physical traits.', false]),
            new TableEntry(30, ['Pointy or larger than normal ears.', false]),
            new TableEntry(39, ['Odd skin color: yellow', false]),
            new TableEntry(40, ['Odd skin color: green', false]),
            new TableEntry(41, ['Odd skin color: red', false]),
            new TableEntry(42, ['Odd skin color: grey', false]),
            new TableEntry(43, ['Ambidextrous: Use the right and left hand with equal skill and dexterity.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Mutant: ambidextrous'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Mutant: ambidextrous'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 10, 'Mutant: ambidextrous'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_ESCAPE_ARTIST, 5, 'Mutant: ambidextrous'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PICK_LOCKS, 5, 'Mutant: ambidextrous'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SPECIAL_MECHANICAL_AND_ELECTRICAL_REPAIR, 5, 'Mutant: ambidextrous'),
            ]]),
            new TableEntry(48, ['Odd hair color: green', false]),
            new TableEntry(49, ['Odd hair color: light blue', false]),
            new TableEntry(50, ['Odd hair color: white streaked', false]),
            new TableEntry(51, ['Odd hair color: bright flame red', false]),
            new TableEntry(52, ['Odd hair color: stark white', false]),
            new TableEntry(53, ['Double-Jointed - has extremely limber joints and can twist and bend their bones into normally impossible positions. These contortions enable the character to collapse the bones in his hands to easily slip out of handcuffs or manacles, temporarily and painlessly dislocate joints to wiggle out of ropes, slip through small openings and fit into small areas.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 2, 'Mutant: Double-jointed'),
            ]]),

            new TableEntry(54, ['Unusual eyes: very small', false]),
            new TableEntry(55, ['Unusual eyes: round', false]),
            new TableEntry(56, ['Unusual eyes: very large', false]),
            new TableEntry(57, ['Unusual eyes: odd color', false]),
            new TableEntry(58, ['Unusual eyes: very elliptical', false]),
            
            new TableEntry(59, ['Extreme amount of body hair: very bushy, full head of hair', false]),
            new TableEntry(60, ['Extreme amount of body hair: very hairy all over the body', false]),
            new TableEntry(61, ['Extreme amount of body hair: human hair all over the body, so thick that it resembles fur', false]),
            new TableEntry(62, ['Extreme amount of body hair: fur; short, half inch length, covers most of body except face, feet, and hands', false]),
            new TableEntry(64, ['Extreme amount of body hair: fur covers most of the boyd except face, bottom of feet, and palms of hands', false]),

            new TableEntry(68, 'Prehensile Feet/Toes: The feet greatly resemble a monkey\'s feet, with long, finger-like toes, and thumb-like appendage for grabbing and holding.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 30, 'Mutant - Prehensile feet/toes'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 1, 'Mutant - Prehensile feet/toes'),
            ]),

            new TableEntry(72, ['Scaly Skin: A tough, smooth, reptilian skin with small scales', [new Bonus(Bonus::ADD, BonusTargets::SDC, 30, 'Mutant: Scaly Skin')]]),
            new TableEntry(76, ['No body hair', false]),
            new TableEntry(79, ['Small horns 1D4 inches long protruding from forehead', false]),
            new TableEntry(84, ['Tough lumpy skin', [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Mutant: tough lumpy skin')]]),
            new TableEntry(89, ['Prehensile tail - The tail could be monkey-like, devil-like, furry, flat, or anything the player or game master feels appropriate. The tail can seize and grasp.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Mutant: prehensile tail'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Mutant: prehensile tail'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 20, 'Mutant: prehensile tail'),
            ]]),

            new TableEntry(94, ['Retractable Claws, like a cat, in the fingers. The small claws do minimal damage; about equal to a knife 2D4 per each swipe.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 10, 'Mutant: Retractable Claws'),
            ]]),

            new TableEntry(100, ['Stocky, exceptionally broad or husky.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::WEIGHT, 50, 'Mutant: Stocky'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Mutant: Stocky - PS', 1, 4), 'Mutant: Stocky'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Mutant: Stocky - SDC', 4, 4), 'Mutant: Stocky'),
            ]]),

            new TableEntry(101, ['Odd skin color: light blue', false]),
            new TableEntry(102, ['Odd skin color: stark white', false]),
            new TableEntry(103, ['Odd skin color: dark blue', false]),
            new TableEntry(104, ['Odd skin color: coal black', false]),
            new TableEntry(105, ['Odd skin color: purple', false]),
            new TableEntry(106, ['Odd skin color: orange', false]),

            new TableEntry(107, ['Unusual eyes: glowing', false]),

            new TableEntry(108, ['Odd hair color: bright yellow', false]),
            new TableEntry(109, ['Odd hair color: metallic silver', false]),
            new TableEntry(110, ['Odd hair color: dark blue', false]),
            new TableEntry(111, ['Odd hair color: purple', false]),
            new TableEntry(112, ['Odd hair color: orange', false]),
        ]);
    }
}
