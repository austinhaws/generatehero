<?php

namespace Heroes\tables\superabilities;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
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
            new TableEntry(3, new Ability('Super Vision: Advanced Sight', 'This is a power that gives the character super sharp, crystal clear vision. Distancing vision is not unlike an eagle\'s. Although not telescopic, the vision is so sharp that the person can read a small sign or recognize a face/costume up to two miles away. Range: Two miles, plus one for every level of experience beyond level two.')),

            new TableEntry(6, new Ability('Extraordinary Mental Affinity', 'An aura of likability, confidence, and trust radiates from this character. He or she is so dynamic that they are often the center of attention and make the opposite sex swoon.',
                [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Extraordinary Mental Affinity', 2, 4), 'Extraordinary Mental Affinity'),
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, 24, 'Extraordinary Mental Affinity'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_DECEPTION_SLEIGHT_OF_HAND, 10, 'Extraordinary Mental Affinity'),
                ])),

            new TableEntry(9, new Ability('Bend Light', 'The ability to bend light allows the character to manipulate light radiation like a prism. THis can produce a number of effects. 1 - Separate the colors bands of light to produce a colored light beam or radiate about 70 watts of colored light; Range: 100ft. 2 - Parries lasers and other light beams by bending the light around him, or a 10ft area, to deflect the beam. Roll just like a normal parry. 3 - Can see in to the infrared and ultraviolet light range; 100ft maximum distance.')),

            new TableEntry(12, new Ability('Flight: Glide', 'This power allows the super being to ride air currents and hover. Maximum gliding speed outdoors, with a strong wind or from a great height (jumping out of an airplane or skyscraper\'s rooftop), is 120mph (192kmph). However, a typical speed is more likely 10 be 40 to 50mph (64 10 80kmph). Gliding indoors is more difficult, with a maximum speed of 40mph (64kmph) and an average speed of 15mph (24km).',
                [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 2, 'Flight: Glide'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 2, 'Flight: Glide'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, 'Flight: Glide'),
                ])),

            new TableEntry(15, new Ability('Heightened Sense of Taste', 'Having a heightened sense of taste means being able to exactly identify the components in anything tasted. The presence of drugs or chemicals in food will be immediately apparent, although identifying the particular drug or chemical depends on the character\'s skill in pharmaceutical or chemistry. Characters with heightened sense of taste will tend to be very particular about what they eat or drink. With practice, they can exactly identify the components and source of any food or drink. Recognize common items, such as sugar, salt, pepper, spices, gasoline, and similar, at a proficiency of 70% + 4% per level of experience. Recognize exotic tastes such as chemicals, toxins and poisons at a proficiency of 30% + 5% per level of experience.')),

            new TableEntry(18, new Ability('Energy Expulsion: Fire', 'Range: 60ft maximum (18.3m); Damage: 206 + I 06 for each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand; Bonuses: + 3 to strike if an aimed shot, +1 to strike if shooting wild; The character can emit a flamethrower-like blast from his hands. The severity of damage can be controlled in increments of 1D6. Remember, maximum damage is limited by the level of experience. Range is limited to 60ft.')),

            new TableEntry(21, new Ability('Super Vision: Nightvision', 'The ability to see clearly in darkness. This includes total darkness.')),

            new TableEntry(24, new Ability('Extraordinary Physical Strength', 'This character possesses astounding physical strength',
                [
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 20, 'Extraordinary Physical Strength'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Extraordinary Physical Strength', 1, 6), 'Extraordinary Physical Strength'),
                    new Bonus(Bonus::BONUS_TYPE_SET_FLAG, BonusTargets::FLAG_DOUBLE_CARRY, true, 'Extraordinary Physical Strength'),
                ])),

            new TableEntry(27, new Ability('Radar', 'Range: 400ft+ lOOft per level of experience. The radar super ability sends out high-frequency radio waves which bounce off objects, returning and indicating the direction and distance of the reflecting objects. This power provides the super being with a crude type of see in the dark ability, enabling him to know/sense the location of objects and movements. Abilities Include: Interpreting Shapes: 50%+ 8% per level of experience. Estimating Distance: 60% + 8% per level of experience. Estimating Direction: 60% + 8% per level of experience. Estimating Speed: 40% + 8% per level of experience Estimating exact location: 40% + 8% per level of experience. No minuses apply when blinded or in darkness. Note: Radar does not go through cloth, wood or people. Consequently, the character can not see or sense through walls or doors. Likewise, while he may sense a car, estimate its speed, direction and distance, he can not tell how many people are in the vehicle. This ability is especially useful in the dark, long distances, and combat (providing relatively full view of the combat area). Disadvantages: Radar is totally fouled in the rain, snow, dust or sandstorms, and by similar multiple, obscuring, images. NO BONUSES apply under these conditions, including no additional attacks per melee. If these conditions exist at night/dark or while blinded the radar is ineffective and the character is blind and suffers with all the minuses that usually apply. Smoke also fouls radar, but not as severely as the aforementioned conditions. All the abilities to estimate speed, direction, distance, shape and location are -30%. All bonuses are reduced by half.', [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 4, 'Radar'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 2, 'Radar'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, 'Radar'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 3, 'Radar'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Radar'),
                ])),

            new TableEntry(31, new Ability('Flight: Wingless', 'The impressive ability to fly without any apparent means of propulsion.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Flight: Wingless'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 2, 'Flight: Wingless'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 2, 'Flight: Wingless'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 4, 'Flight: Wingless'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PHYSICAL_DAMAGE, 4, 'Flight: Wingless'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 40, 'Flight: Wingless'),
            ])),

            new TableEntry(34, new Ability('Heightened Sense of Hearing', 'Range: 360ft radius (109.8m) Heightened hearing enables the character to hear tiny, almost inaudible, sounds several hundred feet away. Other Abilities Include: Estimating the distance of the sound at a 60% + 5% per level proficiency; estimating the speed of the sound\'s approach or departure at 50%+ 5% per level of experience; recognize a voice or sound through intense concentration at 40% + 5% per level of experience; and imitate a voice at a 35% + 5% per level of experience', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Heightened Sense of Hearing'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, 'Heightened Sense of Hearing'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 6, 'Heightened Sense of Hearing'),
            ])),

            new TableEntry(37, new Ability('Mental Stun', 'Range: 60ft ( 18.3m); Duration: 2 melees; Attacks Per Melee: Equal to half the number of hand to hand attacks. Each mental attack counts as one attack.  Savings Throw: 14 or higher is needed to save. M.E. bonuses vs psionics can be applied. A power that attacks the balance mechanism of the brain. Victims feel light-headed, dizzy and out of sync. Effects: Lose one attack per melee. - 3 to strike. - 3 to parry and dodge. -6 to roll with punch, fall or impact. Note: Each attack can only be directed at one person at a time, not an entire crowd at once.')),

            new TableEntry(40, new Ability('Extraordinary Speed', 'The ability to move and run faster than most vehicles without tiring.',
                [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Extraordinary Speed'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 50, 'Extraordinary Speed'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 2, 'Extraordinary Speed'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 2, 'Extraordinary Speed'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 6, 'Extraordinary Speed'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 6, 'Extraordinary Speed'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 6, 'Extraordinary Speed'),
                ])),

            new TableEntry(43, new Ability('Energy Expulsion: Electricity', 'Range: 400ft maximum (122m); Damage: 3D6+1D6 for each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand; Bonuses: +3 to strike if an aimed shot, +1 to strike if shooting wild; Electrical energy bolts leap from the fingers of this living electrical generator. Can regulate the degree of damage by increments of 1D6.')),

            new TableEntry(47, new Ability('Adhesion', 'Able to attach themselves to any solid surface by their fingers, hands, toes, and feet. This means that hte person can walk on walls or ceilings, can climb any surface effortlessly, and is terrific at catching fly balls.',
                // add bonus
                [
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_CLIMBING, 90, 'Adhesion'),
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_PROWL, 90, 'Adhesion'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PICK_POCKETS, 30, 'Adhesion'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PALMING, 30, 'Adhesion'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CONCEALMENT, 30, 'Adhesion'),
                ])),

            new TableEntry(50, new Ability('Flight: Winged', 'This super being has physical wings that give him the power of flight. Unfortunately, wings are difficult to conceal. This can make a secret identity a bit of a problem. However, wings can be carefully folded, tucked, and restrained with minimal discomfort. Wings that are pulled back and strapped in place impairs the characters mobility.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Flight: Winged'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 2, 'Flight: Winged'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 2, 'Flight: Winged'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 4, 'Flight: Winged'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PHYSICAL_DAMAGE, 4, 'Flight: Winged'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 40, 'Flight: Winged'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, [
                    new TableEntry(35, 'Leather Wings'),
                    new TableEntry(70, 'Feather Wings'),
                    new TableEntry(100, 'Insect Wings'),
                ], 'Flight: Winged')
            ])),

            new TableEntry(54, new Ability('Healing Factor', 'This power provides incredible recuperative abilities and immunity to disease and toxins.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Healing Factor: PE', 2, 4), 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 25, 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_COMMA_DEATH, 20, 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_MAGIC_PSIONICS_TOXINS , 3, 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Recovers 3 SDC every 10 minutes (18 per hour)', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Recovers one hit point every 15 minutes (4 per hour)', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Special super healing: Can instantly regenerate 2D6 hit points two times per day (24 hour period)', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Does not fatigue', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Resistant to fire and cold; does half damage', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Resistant to drugs, toxins, poison; 1/2 as effective; 1/2 damage', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'No scarring when healed', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Broken bones heal completely, without any sign of having ever been broken. Heals 10 times faster than normal', 'Healing Factor'),
            ])),

            new TableEntry(57, new Ability('Super Vision: X-Ray', 'A power that enables the character to see through most substances. Lead and lead alloys will block x-ray vision. It requires a few moments of concentration to see through various substances. Abilities: See through fabric or paper up to four inches thick instantly. See through up to one foot (.3m) of wood, plaster, fabric, paper, vegetation; requires one melee (15 seconds) per each foot of material. See through six inches of brick, stone, concrete or metal; requires two melees (30 seconds) per each six inches.')),

            new TableEntry(60, new Ability('Extraordinary Physical Endurance', 'An extremely tough individual who can withstand a great amount of physical strain or punishment.',
                [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Extraordinary Physical Endurance', 2, 6), 'Extraordinary Physical Endurance'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Extraordinary Physical Endurance: SDC', 4, 4, 10), 'Extraordinary Physical Endurance'),
                ])),

            new TableEntry(64, new Ability('Energy Expulsion: Energy', 'Range: 600ft maximum (183m); Damage: 2D6 + 1D6 for each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand. Each blast counts as one hand to hand attack or action for that melee; Bonuses: + 3 to strike if an aimed shot, +1 to strike if shooting wild; The character can generate energy which can be released in directed pulses. The energy pulse or blast is fired from the fingertips, hand or eyes. Can regulate the strength of each blast in increments of 1D6.')),

            new TableEntry(67, new Ability('Heightened Sense of Smell', 'Range: 90ft; An exceptional sense of smell that can identify any smell within 90ft (27.4m) of the character. Abilities: Recognize/identify specific odors: 70% + 4% per level of experience. Recognize a person by scent alone: 50% + 5% per level of experience. Recognize poisons and toxins: 50% + 5% per level of experience. Note: Some poison gases are odorless/tasteless/colorless. Track by smell: 40% + 5% per level of experience. Reduce by 10% in the city. Roll for every 200 yards.')),

            new TableEntry(70, new Ability('Extraordinary Mental Endurance', 'A very mentally stable and strong personality that is difficult to suppress or break. This guy has a will of iron.',
                [
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE, 20, 'Extraordinary Mental Endurance'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE, new Roll('Extraordinary Mental Endurance', 2, 4), 'Extraordinary Mental Endurance'),
                ])),

            new TableEntry(73, new Ability('Impervious to Fire & Heat', 'This power makes the character totally impervious to fire, including magical fire, and heat. No damage.')),

            new TableEntry(76, new Ability('Energy Expulsion: Electrical Field', 'Range: lOft area plus an additional 2ft per each level of experience; Damage: 4D6 for every 5 seconds within the energy field; Duration: One full melee (can be instantly renewed); Attacks Per Melee: One long continuous attack. No other attacks or actions can be made while the electrical field is up; Bonuses: + 2 to strike. No aimed shot is possible; area affect; This character can tum himself into a living dynamo, crackling with electrical energy. Standing stationary, the hero can generate a field of electricity around himself affecting everyone within a 12ft area (first level). Victims caught in the field will suffer a maximum of 4D6 damage for every FIVE seconds trapped in the field (equal to 3 attacks per melee). Can diminish the field\'s damage to as little as 1D6 per five seconds of exposure. While the field is up the character is impervious to electrical and energy attacks. Projectiles, bullets and thrown objects are minus -8 to strike, but do full damage if they hit. Fire is not hampered by the electrical field.')),

            new TableEntry(80, new Ability('Underwater', 'This power enables the super being to function with incredible prowess underwater. Like a fish he can breathe underwater, swim, and so on. Abilities Include: Breathe Underwater, Swim with Amazing Skill, Extraordinary Strength, Extraordinary Speed. Breathe Underwater enables the character to breathe underwater as easily as he does on the surface. Only the super being possesses this power. Swimming abilities are automatic, enabling the character to swim with the skill proficiency of a competitive swimmer. ALL basic swimming techniques and styles are known. Extraordinary Strength: The character possesses incredible strength while underwater. The physical strength is increased to PS 24; if the character already has a natural PS of 20, or higher, add 4 to the P.S. The extra strength applies ONLY when submerged in water. On dry land the super being\'s strength is his normal, natural physical strength. SDC also increases underwater; add 100 S.D.C. points. On dry land the SDC reverts to normal. Extraordinary Speed: The character\'s speed attribute is tripled while underwater and applies to swimming. Bonuses Underwater: + 2 to strike, +4 to parry, +6 to dodge. Bonuses on Dry Land: +1 to strike. Add one extra attack per melee. Add 40 points to S.D.C. (Remember, the 100 SDC bonus underwater no longer applies)', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_SWIMMING, 89, 'Underwater'),
            ])),

            new TableEntry(84, new Ability('Energy Resistance', 'Range: Self; Duration: Constant; Attacks Per Melee: None; Bonuses: None; This power makes the character extremely resistant to all energy based attacks. No physical damage is sustained by the first 20 points of energy attacks in a melee round. Energy attacks beyond the 20 points do only half damage. The character\'s resistance to energy includes fue, electricity, lasers and pure energy. The person is completely invulnerable to stun-type energy weapons. Energy resistance is not effective against radiation damage.')),

            new TableEntry(87, new Ability('Heightened Sense of Touch', 'The character has a superior tactile sense. He can easily recognize very slight differences in textures by touch.', [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_DELICATE_TOUCH, 10, 'Heightened Sense of Touch'),
                ])),

            new TableEntry(90, new Ability('Super Vision: Ultraviolet & Infrared', 'This power enables the character to see in the infrared and ultraviolet spectrum of light radiation. Both types of light are clearly visible to this person. Infrared also provides a hued type of nightvision allowing the character to see clearly in the dark.')),

            new TableEntry(94, new Ability('Energy Expulsion: Light', 'Range: 600ft (183m); Damage: 2D6 + 1D6 per each level of experience; Duration: Instant; Attacks Per Melee: Same as hand to hand; Bonuses: +3 to strike for aimed shot. +1 if shooting wild; The ability to draw on light energy/radiation and emit a highly concentrated bolt of light, not unlike a laser beam. The light bolt can only be fired in pulses from the fingers, hands or eyes. With experience (3rd level or higher), the character can regulate the amount of damage inflicted by the light bolt in increments of 1D6. The character can also radiate light like a human light bulb. Equal to about 100 watts, plus 25 watts per level of experience. Even at first level he can radiate enough to light up a 20 X 20ft room.')),

            new TableEntry(97, new Ability('Extraordinary Physical Beauty', 'An extremely attractive individual whose beauty is truly exceptional. Members of the opposite sex are particularly vulnerable to this character\'s charm.',
                [
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_PHYSICAL_BEAUTY, 20, 'Extraordinary Physical Beauty'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_BEAUTY, new Roll('Extraordinary Physical Beauty', 2, 4), 'Extraordinary Physical Beauty'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_INTERROGATION, 10, 'Extraordinary Physical Beauty'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PICK_POCKETS, 10, 'Extraordinary Physical Beauty'),
                ])),

            new TableEntry(100, new Ability('Extraordinary Physical Prowess', 'A greatly heightened physical prowess providing increased speed and agility',
                [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Extraordinary Physical Prowess', 2, 4), 'Extraordinary Physical Prowess'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, new Roll('Extraordinary Physical Prowess: Speed', 3, 4), 'Extraordinary Physical Prowess'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Extraordinary Physical Prowess'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_PHYSICAL, 10, 'Extraordinary Physical Prowess'),
                ])),
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
