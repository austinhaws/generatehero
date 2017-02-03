<?php

namespace Heroes\tables\superabilities;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTypes;
use Heroes\hero\Ability;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;

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
     * @param $ability Ability the super ability description information
     * @param $abilityType string message to hero about why the bonus is applied
     * @return bool true = the ability was add
     */
    private function applyAbility(Hero &$hero, Ability $ability, $abilityType)
    {
        return $hero->addAbility($ability);
    }

    /**
     * randomly create a minor super power
     *
     * @return Ability
     */
    private function rollMinor()
    {
        return $this->engine->tableRoller->rollTable('Super Ability: Minor', [
            new TableEntry(3, new Ability('Super Vision: Advanced Sight', 'temp')),

            new TableEntry(6, new Ability('Extraordinary Mental Affinity', 'An aura of likability, confidence, and trust radiates from this character. He or she is so dynamic that they are often the center of attention and make the opposite sex swoon.'),
                [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTypes::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Extraordinary Mental Affinity', 2, 4), 'Extraordinary Mental Affinity'),
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTypes::ATTRIBUTE_MENTAL_AFFINITY, 24, 'Extraordinary Mental Affinity'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTypes::SKILL_GROUP_DECEPTION_SLEIGHT_OF_HAND, 10, 'Extraordinary Mental Affinity'),
                ]),

            new TableEntry(9, new Ability('Bend Light', 'The ability to bend light allows the character to manipulate light radiation like a prism. THis can produce a number of effects. 1 - Separate the colors bands of light to produce a colored light beam or radiate about 70 watts of colored light; Range: 100ft. 2 - Parries lasers and other light beams by bending the light around him, or a 10ft area, to deflect the beam. Roll just like a normal parry. 3 - Can see in to the infrared and ultraviolet light range; 100ft maximum distance.')),

            new TableEntry(12, new Ability('Flight: Glide', 'temp')),

            new TableEntry(15, new Ability('Heightened Sense of Taste', 'temp')),

            new TableEntry(18, new Ability('Energy Expulsion: Fire', 'Range: 60ft maximum (18.3m); Damage: 206 + I 06 for each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand; Bonuses: + 3 to strike if an aimed shot, +1 to strike if shooting wild; The character can emit a flamethrower-like blast from his hands. The severity of damage can be controlled in increments of 1D6. Remember, maximum damage is limited by the level of experience. Range is limited to 60ft.')),

            new TableEntry(21, new Ability('Super Vision: Nightvision', 'temp')),

            new TableEntry(24, new Ability('Extraordinary Physical Strength', 'temp')),

            new TableEntry(27, new Ability('Radar', 'temp')),

            new TableEntry(31, new Ability('Flight: Wingless', 'temp')),

            new TableEntry(34, new Ability('Heightened Sense of Hearing', 'temp')),

            new TableEntry(37, new Ability('Mental Stun', 'temp')),

            new TableEntry(40, new Ability('Extraordinary Speed', 'temp')),

            new TableEntry(43, new Ability('Energy Expulsion: Electricity', 'Range: 400ft maximum (122m); Damage: 3D6+1D6 for each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand; Bonuses: +3 to strike if an aimed shot, +1 to strike if shooting wild; Electrical energy bolts leap from the fingers of this living electrical generator. Can regulate the degree of damage by increments of 1D6.')),

            new TableEntry(47, new Ability('Adhesion', 'Able to attach themselves to any solid surface by their fingers, hands, toes, and feet. This means that hte person can walk on walls or ceilings, can climb any surface effortlessly, and is terrific at catching fly balls.'),
                // add bonus
                [
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTypes::SKILL_CLIMBING, 90, 'Adhesion'),
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTypes::SKILL_PROWL, 90, 'Adhesion'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTypes::SKILL_PICK_POCKETS, 30, 'Adhesion'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTypes::SKILL_PALMING, 30, 'Adhesion'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTypes::SKILL_CONCEALMENT, 30, 'Adhesion'),
                ]),

            new TableEntry(50, new Ability('Flight: Winged', 'temp')),

            new TableEntry(54, new Ability('Healing Factor', 'temp')),

            new TableEntry(57, new Ability('Super Vision: X-Ray', 'temp')),

            new TableEntry(60, new Ability('Extraordinary Physical Endurance', 'temp')),

            new TableEntry(64, new Ability('Energy Expulsion: Energy', 'Range: 600ft maximum (183m); Damage: 2D6 + 1D6 for each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand. Each blast counts as one hand to hand attack or action for that melee; Bonuses: + 3 to strike if an aimed shot, +1 to strike if shooting wild; The character can generate energy which can be released in directed pulses. The energy pulse or blast is fired from the fingertips, hand or eyes. Can regulate the strength of each blast in increments of 1D6.')),

            new TableEntry(67, new Ability('Heightened Sense of Smell', 'temp')),

            new TableEntry(70, new Ability('Extraordinary Mental Endurance', 'A very mentally stable and strong personality that is difficult to suppress or break. This guy has a will of iron.'),
                [
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTypes::ATTRIBUTE_MENTAL_ENDURANCE, 20, 'Extraordinary Mental Endurance'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTypes::ATTRIBUTE_MENTAL_ENDURANCE, new Roll('Extraordinary Mental Endurance', 2, 4), 'Extraordinary Mental Endurance'),
                ]),

            new TableEntry(73, new Ability('Impervious to Fire & Heat', 'temp')),

            new TableEntry(76, new Ability('Energy Expulsion: Electrical Field', 'Range: lOft area plus an additional 2ft per each level of experience; Damage: 4D6 for every 5 seconds within the energy field; Duration: One full melee (can be instantly renewed); Attacks Per Melee: One long continuous attack. No other attacks or actions can be made while the electrical field is up; Bonuses: + 2 to strike. No aimed shot is possible; area affect; This character can tum himself into a living dynamo, crackling with electrical energy. Standing stationary, the hero can generate a field of electricity around himself affecting everyone within a 12ft area (first level). Victims caught in the field will suffer a maximum of 4D6 damage for every FIVE seconds trapped in the field (equal to 3 attacks per melee). Can diminish the field\'s damage to as little as 1D6 per five seconds of exposure. While the field is up the character is impervious to electrical and energy attacks. Projectiles, bullets and thrown objects are minus -8 to strike, but do full damage if they hit. Fire is not hampered by the electrical field.')),

            new TableEntry(80, new Ability('Underwater', 'temp')),

            new TableEntry(84, new Ability('Energy Resistance', 'Range: Self; Duration: Constant; Attacks Per Melee: None; Bonuses: None; This power makes the character extremely resistant to all energy based attacks. No physical damage is sustained by the first 20 points of energy attacks in a melee round. Energy attacks beyond the 20 points do only half damage. The character\'s resistance to energy includes fue, electricity, lasers and pure energy. The person is completely invulnerable to stun-type energy weapons. Energy resistance is not effective against radiation damage.')),

            new TableEntry(87, new Ability('Heightened Sense of Touch', 'temp')),

            new TableEntry(90, new Ability('Super Vision: Ultraviolet & Infrared', 'temp')),

            new TableEntry(94, new Ability('Energy Expulsion: Light', 'Range: 600ft (183m); Damage: 2D6 + 1D6 per each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand; Bonuses: +3 to strike for aimed shot. +1 if shooting wild; The ability to draw on light energy/radiation and emit a highly concentrated bolt of light, not unlike a laser beam. The light bolt can only be fired in pulses from the fingers, hands or eyes. With experience (3rd level or higher), the character can regulate the amount of damage inflicted by the light bolt in increments of 1D6. The character can also radiate light like a human light bulb. Equal to about 100 watts, plus 25 watts per level of experience. Even at first level he can radiate enough to light up a 20 X 20ft room.')),

            new TableEntry(97, new Ability('Extraordinary Physical Beauty', 'temp')),

            new TableEntry(100, new Ability('Extraordinary Physical Prowess', 'temp')),
        ]);

    }

    /**
     * @return Ability the major ability to add to the hero
     */
    private function rollMajor()
    {
throw new \Exception('Rolling Major Super Ability need implemented');
//        $hero->addAbility($ability);
    }
}
