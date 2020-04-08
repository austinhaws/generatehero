<?php
namespace Heroes\tables;

use Heroes\engine\Roll;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\classes\MutantAnimalPsionic;
use Heroes\hero\Hero;
use RuntimeException;

class TableMutantBioE extends TableBase
{

    /**
     * @return array list of psionics the mutant can pick from
     */
    public function psionicsList()
    {
        return [
            new MutantAnimalPsionic('Animal Control', 'Command creatures of character\'s own kind.', '50ft', '5 minutes', 'Standard', 10),
            new MutantAnimalPsionic('Animal Speech', 'Complete two-way communication with animals of the same kind as the character. The animal(s) will recognize the character as one of their own and assume that any human looks are just ugly deformities.', '150ft', '10 minutes', 'None', 5),

            new MutantAnimalPsionic('Bio-Manipulation - Blind', 'Knocks out the victim\'s optic nerves.', '160ft', '4D4 minutes', 'Standard', 20),
            new MutantAnimalPsionic('Bio-Manipulation - Deafness', 'Victims can not hear anything.', '160ft', '4D4 minutes', 'Standard', 20),
            new MutantAnimalPsionic('Bio-Manipulation - Mute', 'Impairs the victim\'s vocal cords making speech impossible..', '160ft', '4D4 minutes', 'Standard', 20),
            new MutantAnimalPsionic('Bio-Manipulation - Pain', 'The nerve centers are hit directly. 1 hp damage per minute.', '160ft', '4D4 minutes', 'Standard', 20),
            new MutantAnimalPsionic('Bio-Manipulation - Paralysis', 'Immobilizes the motor part of the brain causing arms and legs to stop working.', '160ft', '4D4 minutes', 'Standard', 20),
            new MutantAnimalPsionic('Bio-Manipulation - Slow', 'Victims lose one attack per melee, speed is halved.', '160ft', '4D4 minutes', 'Standard', 20),
            new MutantAnimalPsionic('Bio-Manipulation - Tissue Manipulation', 'Victim feels itchy, cold and hot.', '160ft', '4D4 minutes', 'Standard', 20),

            new MutantAnimalPsionic('Detect Psionics', 'This mental probe will detect psionics in others. There is a 75%
    chance that the psionic can be detected by any other psionics in the area.', '240ft', '2 minutes', 'None', 10),
            new MutantAnimalPsionic('Hypnotic Suggestion', 'Mental attack that requires eye contact and either verbal or telepathic reinforcement. The suggestion must be a reasonable one.', '12ft', '', 'Standard', 15),
            new MutantAnimalPsionic('Mind Trap', 'A psionic who successfully traps another mind can inflict whatever experience he likes onto that mind.', '6ft', '2D6 minutes', 'Standard', 25),
            new MutantAnimalPsionic('Mind Block', 'Prevents the penetration of all psionic attacks.', 'Self', '10 minutes', 'None', 15),
            new MutantAnimalPsionic('See Aura', 'See the alignment, estimated level of power, type of creature, and the physical condition of the creature in their aura.', '120ft', 'duration', 'None', 15),
            new MutantAnimalPsionic('Sixth Series', 'Intuition that can be protection for the character.', '90ft / self', '4 melees / 1 minute', 'None', 10),
            new MutantAnimalPsionic('Telepathic Transmission', 'Simple, mind-to-mind, speech substitute.', '150ft', 'Unlimited', 'None', 5),
        ];
    }

    /**
     * based on mutant's size, add attribute bonuses
     *
     * @param Hero $hero the hero
     * @param int $size how big the hero is
     * @param string $type short, medium, long
     */
    function applySize(Hero &$hero, $size, $type) {
        $bonuses = [
            1 => [-8, -12, -4, 7, 5],
            2 => [-6, -6, -2, 5, 10],
            3 => [-4, -3, -1, 3, 15],
            4 => [-2, -2, 0, 0, 20],
            5 => [0, -1, 0, 0, 25],
            6 => [0, 0, 0, 0, 30],
            7 => [0, 1, 0, 0, 30],
            8 => [0, 2, 0, 0, 35],
            9 => [0, 3, 1, 0, 35],
            10 => [0, 4, 2, 0, 35],
            11 => [0, 5, 3, -1, 40],
            12 => [0, 6, 4, -2, 40],
            13 => [0, 7, 5, -3, 45],
            14 => [0, 8, 6, -4, 50],
            15 => [0, 9, 7, -5, 55],
            16 => [0, 10, 8, -6, 60],
            17 => [0, 11, 9, -7, 65],
            19 => [0, 13, 11, -9, 75],
            20 => [0, 14, 12, -10, 80],
        ][$size];

        $targets = [
            BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT,
            BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH,
            BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE,
            BonusTargets::ATTRIBUTE_SPEED,
            BonusTargets::SDC,
        ];

        for ($x = 0; $x < count($bonuses); $x++) {
            if ($bonuses[$x]) {
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, $targets[$x], $bonuses[$x], "Mutant Size: $size"));
            }
        }

        // height (inches) / weight (lbs)
        $heightWeight = [
            [
                new Roll('weight - 1', 3, 6, 1/16),
                new Roll('height: short - 1', 1, 6),
                new Roll('height: medium - 1', 2, 6),
                new Roll('height: long - 1', 3, 6),
            ],
            [
                new Roll('weight - 2', 1, 6),
                new Roll('height: short - 2', 3, 6),
                new Roll('height: medium - 2', 1, 6, 1, false, 12),
                new Roll('height: long - 2', 2, 6, 1, false, 12),
            ],
            [
                new Roll('weight - 3', 1, 6, 1, false, 4),
                new Roll('height: short - 3', 1, 6, 1, false, 12),
                new Roll('height: medium - 3', 2, 6, 1, false, 12),
                new Roll('height: long - 3', 3, 6, 1, false, 12),
            ],
            [
                new Roll('weight - 4', 2, 6, 1, false, 10),
                new Roll('height: short - 4', 3, 6, 1, false, 12),
                new Roll('height: medium - 4', 2, 6, 1, false, 24),
                new Roll('height: long - 4', 3, 6, 1, false, 24),
            ],
            [
                new Roll('weight - 5', 4, 6, 1, false, 20),
                new Roll('height: short - 5', 1, 6, 1, false, 24),
                new Roll('height: medium - 5', 2, 6, 1, false, 36),
                new Roll('height: long - 5', 3, 6, 1, false, 36),
            ],
            [
                new Roll('weight - 6', 6, 6, 1, false, 40),
                new Roll('height: short - 6', 2, 6, 1, false, 24),
                new Roll('height: medium - 6', 1, 6, 1, false, 48),
                new Roll('height: long - 6', 3, 6, 1, false, 48),
            ],
            [
                new Roll('weight - 7', 3, 10, 1, false, 75),
                new Roll('height: short - 7', 3, 6, 1, false, 24),
                new Roll('height: medium - 7', 1, 6, 1, false, 60),
                new Roll('height: long - 7', 2, 6, 1, false, 60),
            ],
            [
                new Roll('weight - 8', 6, 10, 1, false, 100),
                new Roll('height: short - 8', 1, 6, 1, false, 36),
                new Roll('height: medium - 8', 1, 6, 1, false, 60),
                new Roll('height: long - 8', 3, 6, 1, false, 60),
            ],
            [
                new Roll('weight - 9', 3, 10, 1, false, 150),
                new Roll('height: short - 9', 2, 6, 1, false, 36),
                new Roll('height: medium - 9', 2, 6, 1, false, 60),
                new Roll('height: long - 9', 2, 6, 1, false, 72),
            ],
            [
                new Roll('weight - 10', 3, 10, 1, false, 175),
                new Roll('height: short - 10', 3, 6, 1, false, 36),
                new Roll('height: medium - 10', 3, 6, 1, false, 60),
                new Roll('height: long - 10', 3, 6, 1, false, 72),
            ],
            [
                new Roll('weight - 11', 6, 10, 1, false, 200),
                new Roll('height: short - 11', 1, 6, 1, false, 48),
                new Roll('height: medium - 11', 1, 6, 1, false, 72),
                new Roll('height: long - 11', 2, 6, 1, false, 84),
            ],
            [
                new Roll('weight - 12', 6, 10, 1, false, 250),
                new Roll('height: short - 12', 2, 6, 1, false, 48),
                new Roll('height: medium - 12', 2, 6, 1, false, 72),
                new Roll('height: long - 12', 3, 6, 1, false, 84),
            ],
            [
                new Roll('weight - 13', 6, 10, 1, false, 300),
                new Roll('height: short - 13', 3, 6, 1, false, 48),
                new Roll('height: medium - 13', 3, 6, 1, false, 72),
                new Roll('height: long - 13', 2, 6, 1, false, 96),
            ],
            [
                new Roll('weight - 14', 6, 10, 1, false, 350),
                new Roll('height: short - 14', 1, 6, 1, false, 60),
                new Roll('height: medium - 14', 1, 6, 1, false, 84),
                new Roll('height: long - 14', 3, 6, 1, false, 96),
            ],
            [
                new Roll('weight - 15', 1, 100, 1, false, 400),
                new Roll('height: short - 15', 2, 6, 1, false, 60),
                new Roll('height: medium - 15', 2, 6, 1, false, 84),
                new Roll('height: long - 15', 2, 6, 1, false, 108),
            ],
            [
                new Roll('weight - 16', 1, 100, 1, false, 500),
                new Roll('height: short - 16', 3, 6, 1, false, 60),
                new Roll('height: medium - 16', 3, 6, 1, false, 84),
                new Roll('height: long - 16', 3, 6, 1, false, 108),
            ],
            [
                new Roll('weight - 17', 2, 100, 1, false, 600),
                new Roll('height: short - 17', 1, 6, 1, false, 72),
                new Roll('height: medium - 17', 1, 6, 1, false, 96),
                new Roll('height: long - 17', 2, 6, 1, false, 120),
            ],
            [
                new Roll('weight - 18', 2, 100, 1, false, 800),
                new Roll('height: short - 18', 2, 6, 1, false, 72),
                new Roll('height: medium - 18', 2, 6, 1, false, 96),
                new Roll('height: long - 18', 3, 6, 1, false, 120),
            ],
            [
                new Roll('weight - 19', 5, 100, 1, false, 1000),
                new Roll('height: short - 19', 3, 6, 1, false, 72),
                new Roll('height: medium - 19', 3, 6, 1, false, 96),
                new Roll('height: long - 19', 2, 6, 1, false, 132),
            ],
            [
                new Roll('weight - 20', 1, 100, 1000, false, 1500),
                new Roll('height: short - 20', 4, 6, 1, false, 72),
                new Roll('height: medium - 20', 3, 6, 1, false, 132),
                new Roll('height: long - 20', 3, 6, 1, false, 148),
            ],
        ][$size - 1];

        // set to character and flag character not to generate height/weight
        switch ($type) {
            case 'short':
                $heightRollIdx = 0;
                break;
            case 'medium':
                $heightRollIdx = 1;
                break;
            case 'long':
                $heightRollIdx = 2;
                break;
            default:
                throw new RuntimeException("Invalid size type:'$type'");
        }
        $hero->weight = $this->engine->roller->rollDice($heightWeight[0]);
        $hero->height = $this->engine->roller->rollDice($heightWeight[$heightRollIdx]);
    }

}
