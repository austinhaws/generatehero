<?php

namespace Heroes\tables\superabilities;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTypes;
use Heroes\enums\Skills;
use Heroes\hero\Ability;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

class SuperAbilityTableResult
{
    public $ability;
    public $addBonus;
    public $setBonus;
    public $addSkill;
    public $setSkill;

    function __construct($ability, $addBonus, $setBonus, $addSkill, $setSkill)
    {
        $this->ability = $ability;
        $this->addBonus = $addBonus ? $addBonus : [];
        $this->setBonus = $setBonus ? $setBonus : [];
        $this->addSkill = $addSkill ? $addSkill : [];
        $this->setSkill = $setSkill ? $setSkill : [];
    }
}

class SuperAbilityBonus
{
    public $type;
    public $value;

    /**
     * SuperAbilityBonus constructor.
     *
     * @param $type string the type of the bonus
     * @param $value int|Roll the value or Roll of the bonus
     */
    function __construct($type, $value)
    {
        $this->type = $type;
        $this->value = $value;
    }

    /**
     * get the bonus value. does a roll if the value is a roll
     *
     * @param Engine $engine the engine to do rolling if needed
     * @return int the value or the roll result
     */
    function getValue(Engine $engine)
    {
        return $this->value instanceof Roll ? $engine->roller->rollDice($this->value) : $this->value;
    }
}

class TableSuperAbilities
{
    private $engine;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    public function randomSuperAbilities(Hero &$hero)
    {
        list($majors, $minors) = $this->engine->tableRoller->rollTable('Super Abilities', [
            new TableEntry(15, [1, 3]),
            new TableEntry(32, [0, 4]),
            new TableEntry(50, [1, 1]),
            new TableEntry(69, [1, 2]),
            new TableEntry(86, [0, 5]),
            new TableEntry(100, [2, 0]),
        ]);

        while ($majors || $minors) {
            if ($majors) {
                if ($this->applyAbility($hero, $this->rollMajor(), 'Major')) {
                    $majors--;
                }
            } else {
                if ($this->applyAbility($hero, $this->rollMinor(), 'Minor')) {
                    $minors--;
                }
            }
        }
    }

    /**
     * try to apply an ability to a hero, return false if the hero already has the ability
     *
     * @param Hero $hero the hero to which to try to apply the ability
     * @param $abilityEntry SuperAbilityTableResult the super ability description information
     * @param $abilityType string message to hero about why the bonus is applied
     * @return bool true = the ability was add
     */
    private function applyAbility(Hero &$hero, $abilityEntry, $abilityType)
    {
        $ability = $abilityEntry->ability;

        $added = $hero->addAbility($ability);

        // not added if already have this ability
        if ($added) {
            // "set" bonus/skill has to happen before add so that they get the max value and some bonuses are "set to N + 1d6"
            foreach ($abilityEntry->setBonus as $setBonus) {
                $hero->setBonus($setBonus->type, $setBonus->getValue($this->engine), "Super Ability: $abilityType - {$ability->title}");
            }
            foreach ($abilityEntry->setSkill as $setSkill) {
                $hero->setSkillBonus($setSkill->type, $setSkill->value, "Super Ability: $abilityType - {$ability->title}");
            }

            foreach ($abilityEntry->addBonus as $bonus) {
                $hero->addBonus($bonus->type, $bonus->value, "Super Ability: $abilityType - {$ability->title}");
            }
            foreach ($abilityEntry->addSkill as $addSkill) {
                $hero->addSkillBonus($addSkill->type, $addSkill->value, "Super Ability: $abilityType - {$ability->title}");
            }
        }
        return $added;
    }

    /**
     * randomly create a minor super power
     *
     * @return SuperAbilityTableResult
     */
    private function rollMinor()
    {
        return $this->engine->tableRoller->rollTable('Super Ability: Minor', [
            new TableEntry(3, new SuperAbilityTableResult(new Ability('Super Vision: Advanced Sight', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(6, new SuperAbilityTableResult(new Ability('Extraordinary Mental Affinity', 'An aura of likability, confidence, and trust radiates from this character. He or she is so dynamic that they are often the center of attention and make the opposite sex swoon.'),
                // add bonus
                [
                    new SuperAbilityBonus(BonusTypes::MENTAL_AFFINITY, new Roll('Extraordinary Mental Affinity Bonus', 2, 4)),
                ],
                // set bonus
                [
                    new SuperAbilityBonus(BonusTypes::MENTAL_AFFINITY, 24)
                ],
                // add skill
                [
                    add skills
    type for deception/sleight of hand
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(9, new SuperAbilityTableResult(new Ability('Bend Light', 'The ability to bend light allows the character to manipulate light radiation like a prism. THis can produce a number of effects. 1 - Separate the colors bands of light to produce a colored light beam or radiate about 70 watts of colored light; Range: 100ft. 2 - Parries lasers and other light beams by bending the light around him, or a 10ft area, to deflect the beam. Roll just like a normal parry. 3 - Can see in to the infrared and ultraviolet light range; 100ft maximum distance.'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(12, new SuperAbilityTableResult(new Ability('Flight: Glide', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(15, new SuperAbilityTableResult(new Ability('Heightened Sense of Taste', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(18, new SuperAbilityTableResult(new Ability('Energy Expulsion: Fire', 'Range: 60ft maximum (18.3m); Damage: 206 + I 06 for each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand; Bonuses: + 3 to strike if an aimed shot, +1 to strike if shooting wild; The character can emit a flamethrower-like blast from his hands. The severity of damage can be controlled in increments of 1D6. Remember, maximum damage is limited by the level of experience. Range is limited to 60ft.'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(21, new SuperAbilityTableResult(new Ability('Super Vision: Nightvision', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(24, new SuperAbilityTableResult(new Ability('Extraordinary Physical Strength', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(27, new SuperAbilityTableResult(new Ability('Radar', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(31, new SuperAbilityTableResult(new Ability('Flight: Wingless', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(34, new SuperAbilityTableResult(new Ability('Heightened Sense of Hearing', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(37, new SuperAbilityTableResult(new Ability('Mental Stun', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(40, new SuperAbilityTableResult(new Ability('Extraordinary Speed', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(43, new SuperAbilityTableResult(new Ability('Energy Expulsion: Electricity', 'Range: 400ft maximum (122m); Damage: 3D6+1D6 for each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand; Bonuses: +3 to strike if an aimed shot, +1 to strike if shooting wild; Electrical energy bolts leap from the fingers of this living electrical generator. Can regulate the degree of damage by increments of 1D6.'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(47, new SuperAbilityTableResult(
                new Ability('Adhesion', 'Able to attach themselves to any solid surface by their fingers, hands, toes, and feet. This means that hte person can walk on walls or ceilings, can climb any surface effortlessly, and is terrific at catching fly balls.'),
                // add bonus
                [
                    new SuperAbilityBonus(Skills::CLIMBING, 90),
                ],
                // set bonus
                [],
                // add skill
                [
                    new SuperAbilityBonus(Skills::PICK_POCKET, 30),
                    new SuperAbilityBonus(Skills::PALMING, 30),
                    new SuperAbilityBonus(Skills::CONCEALMENT, 30),
                ],
                // set skill
                [
                    new SuperAbilityBonus(Skills::PROWL, 90),
                ])
            ),

            new TableEntry(50, new SuperAbilityTableResult(new Ability('Flight: Winged', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(54, new SuperAbilityTableResult(new Ability('Healing Factor', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(57, new SuperAbilityTableResult(new Ability('Super Vision: X-Ray', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(60, new SuperAbilityTableResult(new Ability('Extraordinary Physical Endurance', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(64, new SuperAbilityTableResult(new Ability('Energy Expulsion: Energy', 'Range: 600ft maximum (183m); Damage: 2D6 + 1D6 for each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand. Each blast counts as one hand to hand attack or action for that melee; Bonuses: + 3 to strike if an aimed shot, +1 to strike if shooting wild; The character can generate energy which can be released in directed pulses. The energy pulse or blast is fired from the fingertips, hand or eyes. Can regulate the strength of each blast in increments of 1D6.'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(67, new SuperAbilityTableResult(new Ability('Heightened Sense of Smell', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(70, new SuperAbilityTableResult(new Ability('Extraordinary Mental ENdurance', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(73, new SuperAbilityTableResult(new Ability('Impervious to Fire & Heat', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(76, new SuperAbilityTableResult(new Ability('Energy Expulsion: Electrical Field', 'Range: lOft area plus an additional 2ft per each level of experience; Damage: 4D6 for every 5 seconds within the energy field; Duration: One full melee (can be instantly renewed); Attacks Per Melee: One long continuous attack. No other attacks or actions can be made while the electrical field is up; Bonuses: + 2 to strike. No aimed shot is possible; area affect; This character can tum himself into a living dynamo, crackling with electrical energy. Standing stationary, the hero can generate a field of electricity around himself affecting everyone within a 12ft area (first level). Victims caught in the field will suffer a maximum of 4D6 damage for every FIVE seconds trapped in the field (equal to 3 attacks per melee). Can diminish the field\'s damage to as little as 1D6 per five seconds of exposure. While the field is up the character is impervious to electrical and energy attacks. Projectiles, bullets and thrown objects are minus -8 to strike, but do full damage if they hit. Fire is not hampered by the electrical field.'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(80, new SuperAbilityTableResult(new Ability('Underwater', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(84, new SuperAbilityTableResult(new Ability('Energy Resistance', 'Range: Self; Duration: Constant; Attacks Per Melee: None; Bonuses: None; This power makes the character extremely resistant to all energy based attacks. No physical damage is sustained by the first 20 points of energy attacks in a melee round. Energy attacks beyond the 20 points do only half damage. The character\'s resistance to energy includes fue, electricity, lasers and pure energy. The person is completely invulnerable to stun-type energy weapons. Energy resistance is not effective against radiation damage.'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(87, new SuperAbilityTableResult(new Ability('Heightened Sense of Touch', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(90, new SuperAbilityTableResult(new Ability('Super Vision: Ultraviolet & Infrared', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(94, new SuperAbilityTableResult(new Ability('Energy Expulsion: Light', 'Range: 600ft (183m); Damage: 2D6 + 1D6 per each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand; Bonuses: +3 to strike for aimed shot. +1 if shooting wild; The ability to draw on light energy/radiation and emit a highly concentrated bolt of light, not unlike a laser beam. The light bolt can only be fired in pulses from the fingers, hands or eyes. With experience (3rd level or higher), the character can regulate the amount of damage inflicted by the light bolt in increments of 1D6. The character can also radiate light like a human light bulb. Equal to about 100 watts, plus 25 watts per level of experience. Even at first level he can radiate enough to light up a 20 X 20ft room.'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(97, new SuperAbilityTableResult(new Ability('Extraordinary Physical Beauty', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),

            new TableEntry(100, new SuperAbilityTableResult(new Ability('Extraordinary Physical Prowess', 'temp'),
                // add bonus
                [
                ],
                // set bonus
                [
                ],
                // add skill
                [
                ],
                // set skill
                [
                ]
            )),
        ]);

    }

    /**
     * @return SuperAbilityTableResult Ability the major ability to add to the hero
     */
    private function rollMajor()
    {

//        $hero->addAbility($ability);
    }
}
