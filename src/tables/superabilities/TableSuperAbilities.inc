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
            new TableEntry(3, new Ability('Super Vision: Advanced Sight', 'Super sharp, crystal clear vision. Distancing vision is not unlike an eagle\'s. Although not telescopic, the vision is so sharp that the person can read a small sign or recognize a face/costume up to two miles away. Range: Two miles, plus one for every level of experience beyond level two.')),

            new TableEntry(6, new Ability('Extraordinary Mental Affinity', 'An aura of likability, confidence, and trust radiates from this character. He or she is so dynamic that they are often the center of attention and make the opposite sex swoon.',
                [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Extraordinary Mental Affinity', 2, 4), 'Extraordinary Mental Affinity'),
                    new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, 24, 'Extraordinary Mental Affinity'),
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_DECEPTION_SLEIGHT_OF_HAND, 10, 'Extraordinary Mental Affinity'),
                ])),

            new TableEntry(9, new Ability('Bend Light', 'Manipulate light radiation like a prism. THis can produce a number of effects. 1 - Separate the colors bands of light to produce a colored light beam or radiate about 70 watts of colored light; Range: 100ft. 2 - Parries lasers and other light beams by bending the light around him, or a 10ft area, to deflect the beam. Roll just like a normal parry. 3 - Can see in to the infrared and ultraviolet light range; 100ft maximum distance.')),

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
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_MAGIC_PSIONICS_TOXINS, 3, 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Recovers 3 SDC every 10 minutes (18 per hour)', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Recovers one hit point every 15 minutes (4 per hour)', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Special super healing: Can instantly regenerate 2D6 hit points two times per day (24 hour period)', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Does not fatigue', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Resistant to fire and cold; does half damage', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Resistant to drugs, toxins, poison; 1/2 as effective; 1/2 damage', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'No scarring when healed', 'Healing Factor'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Broken bones heal completely, without any sign of having ever been broken. Heals 10 times faster than normal', 'Healing Factor'),
            ])),

            new TableEntry(57, new Ability('Super Vision: X-Ray', 'See through most substances. Lead and lead alloys will block x-ray vision. It requires a few moments of concentration to see through various substances. Abilities: See through fabric or paper up to four inches thick instantly. See through up to one foot (.3m) of wood, plaster, fabric, paper, vegetation; requires one melee (15 seconds) per each foot of material. See through six inches of brick, stone, concrete or metal; requires two melees (30 seconds) per each six inches.')),

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

            new TableEntry(73, new Ability('Impervious to Fire & Heat', 'Totally impervious to fire, including magical fire, and heat. No damage.')),

            new TableEntry(76, new Ability('Energy Expulsion: Electrical Field', 'Range: lOft area plus an additional 2ft per each level of experience; Damage: 4D6 for every 5 seconds within the energy field; Duration: One full melee (can be instantly renewed); Attacks Per Melee: One long continuous attack. No other attacks or actions can be made while the electrical field is up; Bonuses: + 2 to strike. No aimed shot is possible; area affect; This character can tum himself into a living dynamo, crackling with electrical energy. Standing stationary, the hero can generate a field of electricity around himself affecting everyone within a 12ft area (first level). Victims caught in the field will suffer a maximum of 4D6 damage for every FIVE seconds trapped in the field (equal to 3 attacks per melee). Can diminish the field\'s damage to as little as 1D6 per five seconds of exposure. While the field is up the character is impervious to electrical and energy attacks. Projectiles, bullets and thrown objects are minus -8 to strike, but do full damage if they hit. Fire is not hampered by the electrical field.')),

            new TableEntry(80, new Ability('Underwater', 'This power enables the super being to function with incredible prowess underwater. Like a fish he can breathe underwater, swim, and so on. Abilities Include: Breathe Underwater, Swim with Amazing Skill, Extraordinary Strength, Extraordinary Speed. Breathe Underwater enables the character to breathe underwater as easily as he does on the surface. Only the super being possesses this power. Swimming abilities are automatic, enabling the character to swim with the skill proficiency of a competitive swimmer. ALL basic swimming techniques and styles are known. Extraordinary Strength: The character possesses incredible strength while underwater. The physical strength is increased to PS 24; if the character already has a natural PS of 20, or higher, add 4 to the P.S. The extra strength applies ONLY when submerged in water. On dry land the super being\'s strength is his normal, natural physical strength. SDC also increases underwater; add 100 S.D.C. points. On dry land the SDC reverts to normal. Extraordinary Speed: The character\'s speed attribute is tripled while underwater and applies to swimming. Bonuses Underwater: + 2 to strike, +4 to parry, +6 to dodge. Bonuses on Dry Land: +1 to strike. Add one extra attack per melee. Add 40 points to S.D.C. (Remember, the 100 SDC bonus underwater no longer applies)', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_SWIMMING, 89, 'Underwater'),
            ])),

            new TableEntry(84, new Ability('Energy Resistance', 'Range: Self; Duration: Constant; Attacks Per Melee: None; Bonuses: None; This power makes the character extremely resistant to all energy based attacks. No physical damage is sustained by the first 20 points of energy attacks in a melee round. Energy attacks beyond the 20 points do only half damage. The character\'s resistance to energy includes fue, electricity, lasers and pure energy. The person is completely invulnerable to stun-type energy weapons. Energy resistance is not effective against radiation damage.')),

            new TableEntry(87, new Ability('Heightened Sense of Touch', 'Superior tactile sense - can easily recognize very slight differences in textures by touch.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_DELICATE_TOUCH, 10, 'Heightened Sense of Touch'),
            ])),

            new TableEntry(90, new Ability('Super Vision: Ultraviolet & Infrared', 'See in the infrared and ultraviolet spectrum of light radiation. Both types of light are clearly visible to this person. Infrared also provides a hued type of nightvision allowing the character to see clearly in the dark.')),

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
        return $this->engine->tableRoller->rollTable('Super Ability: Major', [
            new TableEntry(1, new Ability('Animal Metamorphosis - Rodent', 'Completely transform into a rodent. As an animal, the person gets all the inherent abilities and defenses that animal form may offer, while retaining his own memory, IQ, SDC, hit points and ability to speak. All physical attributes change, up or down, as best fits the animal. The animal metamorphoser can change from humanoid to animal, and back again, at will. Each change counts as an action/attack per melee.', [
            ])),

            new TableEntry(2, new Ability('Animal Metamorphosis - Musteloid', 'Completely transform into a musteloid. As an animal, the person gets all the inherent abilities and defenses that animal form may offer, while retaining his own memory, IQ, SDC, hit points and ability to speak. All physical attributes change, up or down, as best fits the animal. The animal metamorphoser can change from humanoid to animal, and back again, at will. Each change counts as an action/attack per melee.', [
            ])),

            new TableEntry(4, new Ability('Chameleon', 'A truly unique power that allows the person to blend into and adapt to his environment. Chameleon is an ability that enables the person to change color and texture to blend into his environment. A sort of bio-aura surrounds the character so that even his clothes seem to change to adapt to the surrounding area. Movement destroys the effectiveness of the chameleon ability.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Adhesion: the ability to stick to surfaces.', 'Chameleon'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Hold Breath for up to 10 minutes.', 'Chameleon'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Feign Death by lowering one\'s body temperature and respiration.', 'Chameleon'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_PROWL, 65, 'Chameleon'),
            ])),

            new TableEntry(7, new Ability('Alter Physical Structure: Stone', 'Turns the person into living stone.', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::NATURAL_ARMOR_RATING, 16, 'Alter Physical Structure: Stone'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 600, 'Alter Physical Structure: Stone'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Alter Physical Structure: Stone - Physical Strength', 2, 6), 'Alter Physical Structure: Stone'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Impervious to cold.', 'Alter Physical Structure: Stone'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'The stone form is cool enough to avoid detection by infrared or heat sensors.', 'Alter Physical Structure: Stone'),
            ])),

            new TableEntry(9, new Ability('Control Elemental Force: Water', 'The power to manipulate and control aspects of water. To use any of these powers there must be a source of water within a 600ft radius. Without an ample source of water the super being can not use any of the powers. Water source can be a sewer, water pipe line, pond, lake, ocean, or even rain.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Calm Water - Reduce the intensity of water turbulence. The size of waves, their speed and potential damage are reduced by half. The calming effect can be repeated in the same radius only after the initial effect lapses or is cancelled.', 'Control Elemental Force: Water'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Create Waves - Manipulate large sources of water to create a variety of waves in water or on land. The size and speed of the waves can be controlled by the character.', 'Control Elemental Force: Water'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Water Slam - Create a small, but powerful, wave that rises up like a hand and slams down on one specific target. The water slam towers to about 16ft tall and 6ft wide. It can also be used on land if sufficient water is available; 200 gallons or more.', 'Control Elemental Force: Water'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Water Spout - This is the tricky technique of summoning up a spout-like wave. This will push its victim skyward, bouncing atop the water spout. A large body of water must be available.', 'Control Elemental Force: Water'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Wall of Water - Call up a wave which will suspend itself to create a wall. The wall can be up to 6ft thick, 30ft tall and 30ft long. It will slow and deflect bullets and lasers. Fire type attacks that pass through do 1/2 damage. The water can be molded to the shape of a wall, circle, or dome. Because of the vast amount of water it is impossible to see beyond the wall. This ability requires a vast amount of water, like a very large swimming pool, lake, river, etc.', 'Control Elemental Force: Water'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Whirlpool - Creates a huge, spinning whirlpool in any large body of water (lake, river, sea, etc.). This watery funnel pulls and sucks all objects in or on the water into its whirling center, crushing and dragging them down into the depths. Objects caught in the outer edge will be snagged in the pull and drawn toward its center in a spiraling circle. Victims in the water will become dizzy and disoriented, with a 28% chance of drowning. Victims can be pulled, flown, or levitated to safety. Boats and ships may be able to pull themselves away.', 'Control Elemental Force: Water'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Create Air Bubble (under water) - The hero can create an air bubble underwater, affecting a maximum radius of eight feet. The bubble can be created around oneself or up to 140ft away. The bubble can not be moved easily; normally floating along with the tide with a slight, upward drift. Through intense concentration the person who created the bubble can direct it. Controlling the bubble consumes most of the person\'s concentration, preventing him from using any other power unless he stops the bubble. The bubble can be punctured and destroyed by any type of attack.', 'Control Elemental Force: Water'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Walk on Water - The person is able to stand, walk, run, or float atop water.', 'Control Elemental Force: Water'),
            ])),

            new TableEntry(11, new Ability('Invisibility', 'The super being and anything he is wearing or carrying, up to 100lbs in weight, can be turned invisible at will. Neither normal vision nor nightvision can detect invisibility; however, infrared, heat sensors and motion detectors can easily locate an invisible interloper. Although the invisible character is imperceptible to the eye, he retains his physical mass, meaning that he can not go through walls nor do weapons pass through him. This also means he still makes noise (footsteps, breathing, bumps, knocks, etc.) and may be located by his noise if not careful. The character can automatically see the invisible.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Invisibility: SDC', 1, 4, 10), 'Invisibility'),
            ])),

            new TableEntry(13, new Ability('Energy Absorption', 'This character is a sort of living energy sponge that can soak-up, store, and harmlessly convert and release energy.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Impervious to heat, fire, laser blasts, electricity, and other forms of energy.', 'Energy Absorption'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Draining Touch - Drain the energy out of an item, like a car battery or energy pack, by touching it.', 'Energy Absorption'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Energy Discharge - Touch an electrical/energy conductor and send a power surge into the system, at least temporarily short-circuiting the system, if not frying it completely.', 'Energy Absorption'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Energy Flash - Discharge a sudden energy flash that will strike everyone within the area of the discharge. Unfortunately, the character can not control or direct the energy to strike a specific target.', 'Energy Absorption'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Glow - The storage of energy can be released as light. This character can glow with up to 500 watts of light. The light can be restricted to a specific part of the body, like a hand or arm, or the entire body.', 'Energy Absorption'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Shoot Light Beam - The light beam is completely harmless in that it does no damage. However. It is so bright that it can be used to temporarily blind an opponent if shot into the eyes. The beams can also be used as a beacon or searchlight. Maximum width of the beam is two feet if both hands are put together with fingers spread wide.', 'Energy Absorption'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Energy Absorption: SDC', 1, 6, 10), 'Energy Absorption'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Energy Absorption: PE', 1, 4), 'Energy Absorption'),
            ])),

            new TableEntry(16, new Ability('Control Others', 'This power affects any intelligent creature, or animals. It can temporarily bend the will of its victim so that they are under the complete control of the super being. The affected person will do absolutely anything the controller requests. All questions will be answered truthfully and in as much detail as requested. However, the controlled person will answer and obey only the person controlling him/her. Victims will remember their actions after being controlled.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_PSIONIC_MIND_CONTROL, 6, 'Control Others'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_CONTROL_OTHERS, 6, 'Control Others'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Control Others: MA', 2, 4), 'Control Others'),
            ])),

            new TableEntry(19, new Ability('Shape Change', 'Change all aspects of their physical appearance: height, weight, features, hair, eyes, skin color, etc. Voice imitation is not included. Large extra appendages, such as wings and extra limbs, can not be imitated; however, tails, horns, claws, fangs, etc., can all be grown. All changes are real physical changes, not just clever make-up. A shape-changer can transform into any humanoid creature including apes.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::IMITATE_VOICES, 15, 'Shape Change'),
            ])),

            new TableEntry(22, new Ability('Darkness Control', 'Create and manipulate darkness.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Create Darkness - Create an area of total darkness up to 140ft away. The darkness is so black that normal vision, nightvision, and light amplification optic systems are ineffective.', 'Darkness Control'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Shadow Mold - The ability to become invisible in shadows or darkness. The only requirement is that the shadow or area of darkness must be man-sized. Exposure to light will dispel the darkness/shadow and reveal the character.', 'Darkness Control'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision - 600ft (183m) in normal darkness; 30ft (9.1m) in his own, unnatural, darkness.', 'Darkness Control'),
            ])),

            new TableEntry(24, new Ability('Gravity Manipulation', 'The control and manipulation of gravity.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Reduce Gravity - Reduce gravity to a fraction. Carry up to 100 times his normal weight capacity. Leap two feet for each P.S. attribute point. Speed tripled. This effect can be placed on oneself, or others within the 120ft range, or on an area (20ft radius) up to 120ft away.', 'Gravity Manipulation'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Increase Gravity - This ability is the opposite of the reduce gravity effect, enabling the super being to create bone crushing gravitational conditions.', 'Gravity Manipulation'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Zero Gravity - Create an area with no gravity at all. Anything within the radius, or anything specifically affected, is completely weightless and will float about lOft above the ground.', 'Gravity Manipulation'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Antigravity Flight - Can hover or propel himself through the air', 'Gravity Manipulation'),
            ])),

            new TableEntry(27, new Ability('Alter Physical Structure: Ice', 'The startling ability to transform into a being of living ice, as well as manipulate and control aspects of cold. Snow and ice can be created by an extraordinary means of water condensation and freezing of moisture out of thin air. In this way the super being can create snow and ice. Abilities: Create snow and/or ice, create and hurl ice balls, create and hurl ice shards, ice wall or shield, encase in ice, and general ice.', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::NATURAL_ARMOR_RATING, 14, 'Alter Physical Structure: Ice'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 50, 'Alter Physical Structure: Ice'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Conventional weapons, like knives and guns, do one-half their normal damage.', 'Alter Physical Structure: Ice'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Lasers do no damage, reflecting and bouncing off the reflective surface of the ice.', 'Alter Physical Structure: Ice'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Explosives, including grenades, dynamite, nitro, and plastic explosives, all do 1/2 damage.', 'Alter Physical Structure: Ice'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Impervious to cold.', 'Alter Physical Structure: Ice'),
            ])),

            new TableEntry(30, new Ability('Intangibility', 'This power affects the bonding element of molecules, making the person and 20lbs (9kg) of additional material intangible. Intangibility means that sticks and stones, punches, bullets, lasers, and most conventional attacks pass right through; harmless, like a ghost. Electricity and sonic blasts, which stimulate and agitate molecules, do half damage. Psionic attacks have full effect. Gas attacks do full damage/effect. The intangible person can not touch, pick up or carry anything, but can speak and hear as normal. The character can walk through any substance, stone, steel, earth, machines, etc, without affecting it or himself. Although the character can not glide or float, falls or explosions can not harm him. Because of the intangible state, he can sink into the earth/ground up to his nose and walk on the dense molecules, effectively walking through the earth. Likewise, he can actually walk on the dense molecules of smoke and water.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Intangibility: MA', 1, 6), 'Intangibility'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Intangibility: SDC', 1, 4, 10), 'Intangibility'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PROWL, 20, 'Intangibility'),
            ])),

            new TableEntry(32, new Ability('Growth', 'The ability to greatly increase one\'s size and mass including SDC and Physical Strength.', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 14, 'Growth'),
            ])),

            new TableEntry(35, new Ability('Create Force Field', 'Create force field', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Create Force Field - Generate an invisible or semitransparent field of energy/force. The force field can be mentally shaped as a wall, circle, dome, box, or bubble.', 'Create Force Field'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Body Armor - Create a light force field that follows the contours of his body to create a sort of invisible body armor. Gases arc still effective (only the bubble closes out gases).', 'Create Force Field'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Bolts of Force - Create small, nearly invisible, bolts of force which can be f1red at an opponent.', 'Create Force Field'),
            ])),

            new TableEntry(38, new Ability('Control Elemental Force: Air', 'The power to manipulate and control aspects of air and atmospheric conditions.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Wind Rush - Create a short powerful wind gusting to 60mph (96kmph), and can direct it at a specific target or area. The wind is so powerful that it will stagger or knock people down, blow away all objects in its path weighing less than 30 pounds (13.6kg), and break ordinary window glass.', 'Control Elemental Force: Air'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Whirlwind - Create a rotating windstorm of limited intensity. Moving in an inward and upward spiral motion, the 75mph winds will suck, hurl, and dash to the ground anyone or anything within a 20ft (6.1m) area. Anyone caught in the wind can not attack or speak for one melee. They will be snatched up and hurled approximately 20ft, taking 4D6 points of damage. The wind will affect anything weighing less than 700lbs (315kg).', 'Control Elemental Force: Air'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Ride the Wind - Manipulate air currents and wind speed to carry himself and an additional 200lbs aloft. Riding the winds is not the ability to fly, but is, more accurately, the ability to hover, rise above the ground (up to 30ft per melee), and glide. The gliding is very limited and requires the concentration of the air controller. He can still use his other powers while aloft. If he is knocked unconscious or severely hurt he loses all control and plummets down to earth.', 'Control Elemental Force: Air'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Change Wind Direction - Change the direction of the wind in a small area by manipulating air currents.', 'Control Elemental Force: Air'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Stop Wind/Control (wind) Speed - Can completely stop the wind.', 'Control Elemental Force: Air'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Create Air Bubble - Create a bubble or pocket of air. This can be done underwater or in a place where there is at least a minute quantity of oxygen. The bubble offers protection from gases, foul odors, etc. Bubble Radius: 6ft; Speed: The bubble can be moved, but at a limited speed factor of 10.', 'Control Elemental Force: Air'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Call Lightning - Call down a lightning bolt to strike a specific target.', 'Control Elemental Force: Air'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Atmospheric Manipulation - Darken sky: heavy overcast, creating a dark, ominous sky; Cause a loud, eerie thunderclap; Increase or decrease the wind speed; Increase or decrease precipitation; Dispel a fog; Create a fog.', 'Control Elemental Force: Air'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Resistant to cold and electricity (does half damage).', 'Control Elemental Force: Air'),
            ])),

            new TableEntry(39, new Ability('Animal Abilities - Bear', 'This power gives humanoid characters the traits, abilities and instincts of a particular type of animaL It does not actually transform the person into an animal. The character can also control (to a limited degree) any animals that fall into his general type. Actual communication/dialog is impossible, but the character understands the general meanings of grunts, growls, whines, and facial and tail expressions. The animals Will look toward the super being as the leader of a pack and will follow his actions. Commands will be limited to stop, go, attack, wait, run, etc. Hands are thick, With heavy short fingers; ears are small The character is tough husky and bulky, yet nimble.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Cold does half damage.', 'Animal Abilities - Bear'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Animal Abilities - Bear: SDC', 2, 4, 10), 'Animal Abilities - Bear'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Animal Abilities - Bear: PS', 3, 6), 'Animal Abilities - Bear'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Animal Abilities - Bear: PE', 3, 6), 'Animal Abilities - Bear'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Extraordinary Sense of Smell - Detect very faint scent traces. Tracking by smell is possible (like a bloodhound) at a 40% + 5% per level of experience. Recognizing a person\'s scent is also possible, with a 48% effectiveness.', 'Animal Abilities - Bear'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Can control 2D4 bears or dogs.', 'Animal Abilities - Bear'),
            ])),

            new TableEntry(40, new Ability('Animal Abilities - Bird', 'This power gives humanoid characters the traits, abilities and instincts of a particular type of animaL It does not actually transform the person into an animal. The character can also control (to a limited degree) any animals that fall into his general type. Actual communication/dialog is impossible, but the character understands the general meanings of grunts, growls, whines, and facial and tail expressions. The animals Will look toward the super being as the leader of a pack and will follow his actions. Commands will be limited to stop, go, attack, wait, run, etc. Large, round eyes; tends to be thin, but muscular.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Glide: same power as teh minor super ability.', 'Animal Abilities - Bird'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, '180 degree arc of vision. It is extremely difficult to sneak up on this character.', 'Animal Abilities - Bird'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Extraordinary vision is approximately six times better than normal human\'s. That means an 18 inch (.4m) object can be seen clearly, in perfect detail, up to one mile (1.6km) away.', 'Animal Abilities - Bird'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 2, 'Animal Abilities - Bird'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Animal Abilities - Bird'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 1, 'Animal Abilities - Bird'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Can control 4D4 birds.', 'Animal Abilities - Bird'),
            ])),

            new TableEntry(41, new Ability('Animal Abilities - Reptile', 'Round eyes, small ears and minimal body hair.', [
                new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::ATTRIBUTE_SPEED, 2, 'Animal Abilities - Reptile'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Leap up to 8ft (2.4m) straight up and 15ft lengthwise (4.6m).', 'Animal Abilities - Reptile'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_CLIMBING, 82, 'Animal Abilities - Reptile'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::MAINTAIN_GRIP_HOLD_FOOTING, 72, 'Animal Abilities - Reptile'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::BALANCE_WALK_TIGHTROPE, 62, 'Animal Abilities - Reptile'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Animal Abilities - Reptile: SDC', 1, 4, 10), 'Animal Abilities - Reptile'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Animal Abilities - Reptile: PP', 1, 6), 'Animal Abilities - Reptile'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Can control up to 6D6 reptiles of any kind.', 'Animal Abilities - Reptile'),
            ])),

            new TableEntry(43, new Ability('Sonic Speed', 'The power to run at supersonic speeds. Run at the speed of sound, Mach One, or approximately 670mph (1078kmph). Has sharper vision, quicker reactions, and greater dexterity than normal humans.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 2, 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Sonic Speed: SDC', 4, 4, 10), 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Sonic Speed: PE', 1, 6), 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 6, 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 4, 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 6, 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 6, 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Leap ability - 60ft (18.3m) straight up and lOOft (30.5m) lengthwise.', 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Increased damage with physical attacks.', 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Superior vision about five times better than normal humans which means an 18 inch sign can be read a mile away.', 'Sonic Speed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision - 500ft (152.5m).', 'Sonic Speed'),
            ])),

            new TableEntry(46, new Ability('Alter Physical Structure: Fire', 'The ability to transform into a being of living fire, as well as manipulate and control aspects of fire. Abilities: Continuous bolt of flame, fire ball, create wall or circle of flame, radiate heat, and super nova.', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::NATURAL_ARMOR_RATING, 14, 'Alter Physical Structure: Fire'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'The natural protection extends to attacks by normal human beings. Unless protected in some way, attackers w1ll take 4D6 damage each time the person strikes the blazing hero.', 'Alter Physical Structure: Fire'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Impervious to fire and heat (does no damage). Note that electricity, lasers, and energy all do full damage.', 'Alter Physical Structure: Fire'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Flight is a possibility while in flame form.', 'Alter Physical Structure: Fire'),
            ])),

            new TableEntry(48, new Ability('Magnetism', 'The power to direct, control, and manipulate aspects of magnetic forces.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Attract Metal - Attract or pull up to 3000lbs (1350kg). To magnetically affect the object, it must have at least a 20% iron/steel composition. Can pull a metal item from up to 160ft away.', 'Magnetism'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Hurl or Repel Metal Objects - Repel objects which are at least 20% iron/steel composition. This can be focused against one specific item or to repel any metallic objects within a 160ft (48.8m) area. The hurled objects can make excellent weapons.', 'Magnetism'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Magnetic Field - By placing a magnetic field around himself, the character can stop or deflect metal objects. The magnetic field will also erase any magnetic tapes, disrupt electrical frequencies, and reduce electrical attacks by half damage. Can also use the field to propel character toward (or away from) any iron object that is at least equal to his own body weight.', 'Magnetism'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Magnetize Objects - Make an iron object temporarily magnetic. Magnetized items are much like the kind of magnets available in the commercial market. They are most suitable for attaching to iron or steel objects.', 'Magnetism'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Sense Iron - Sense the presence, and vague location, of iron or steel within a 25ft radius. The exact size of the items is impossible to discern. This ability can be used to detect objects beneath the ground.', 'Magnetism'),
            ])),

            new TableEntry(50, new Ability('Stretching', 'Character\'s body is super elastic and malleable, enabling him to distort and elongate limbs or the entire body.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Stretching - Neck: 4ft (I. 2m); Finger: 4ft (1.2m); Ann(s): 20ft each (6.lm); Leg(s): 35ft each (10. 7m); Body (maximum length): 150ft (45.7m)', 'Stretching'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Stretching Contortions - Flatten the entire body to as little as 2 inches thick but like clay flattened by a rolling pin, the rest of the body mass is pushed out four feet for every 601bs (27kg) of normal weight. Condense the entire body into a compact ball of one and a half feet/18 inches (.5m).', 'Stretching'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Bounceabilty - The character can puff himself up like a balloon and bounce. In this form, punches, kicks, collisions, explosive force and falls do no damage. The height of a bounce self-initiated from ground level is about six feet (1.8m) to twelve feet (3.4m). Propelling himself with his elongated arms and bouncing will triple his normal speed.', 'Stretching'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Stretching', 2, 4, 10), 'Stretching'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Stretching', 1, 6), 'Stretching'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, 'Stretching'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 2, 'Stretching'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, 'Stretching'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 3, 'Stretching'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Projectiles, such as bullets, arrows, thrown objects, punches, and kicks all do half damage.', 'Stretching'),
            ])),

            new TableEntry(53, new Ability('Invulnerability', 'An almost indestructible juggernaut. Most physical attacks do no damage whatsoever! Cold, fire, heat, electricity, lasers, other types of energy, bullets, punches, falls and so on, do no damage. Gases, drugs, chemicals, poisons, toxins and rad1at1on w1ll affect the invulnerable person, but are reduced to half the usual potency (half damage, duration, effect). The character is only vulnerable to psionics, illusionary and spell magic, and magic weapons.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Invulnerability: SDC', 4, 6, 10), 'Invulnerability'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Invulnerability: PE', 1, 6), 'Invulnerability'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Invulnerability: PS', 1, 4), 'Invulnerability'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_COMMA_DEATH, 20, 'Invulnerability'),
            ])),

            new TableEntry(56, new Ability('Alter Physical Structure: Electricity', 'An incredible transformation into a living electrical conduit, as well as the ability to manipulate and control aspects of electricity. Abilities: Fire Electrical Ray, Mini-Lightning Bolt, Lightning Bolt, Electric Flight, and Generate Electricity.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 40, 'Alter Physical Structure: Electricity'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Impervious to electrical attacks (do no damage).', 'Alter Physical Structure: Electricity'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Fire and energy attacks do half damage.', 'Alter Physical Structure: Electricity'),
            ])),

            new TableEntry(59, new Ability('Control Elemental Force: Earth', 'The power to manipulate and control aspects of the earth. To use any of these powers there must be a vast source of earth (stone, din, clay, sand) within a 600ft radius. The earth is molded and manipulated, not created.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Wall or Earth - Create a circle, dome, or straight wall that is 18ft long by 12ft high by 3ft thick.', 'Alter Physical Structure: Earth'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Tower of Earth - call forth a great mound of earth or stone that will shoot up, out of the ground, carrying anything under it skyward.', 'Alter Physical Structure: Earth'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Hurl Earth - Cause chunks of earth to raise up and hurl them at a target.', 'Alter Physical Structure: Earth'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Quicksand - Transform normal earth and stone into a pool of quicksand, up to 20ft deep.', 'Alter Physical Structure: Earth'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Rend Earth - The super being can split the earth like a mini-earthquake, creating a 15ft wide, 20ft deep, 40ft long crevice. Also enables creating openings in walls and buildings.', 'Alter Physical Structure: Earth'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Sand/Dust Storm - The dust or sand particles can be manipulated to fill the air in order to create a sand or dust storm. The storm can be created up to 180ft away and affects a 30ft radius. Victims are blinded while in the storm, all sense of direction is lost.', 'Alter Physical Structure: Earth'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Encase in Earth - A very powerful, but controlled, ability in which the super being can cause earth (din, clay, sand) or stone (including concrete) to rise from the ground to engulf an object or person. The character has absolute control over the earth and can encase just a foot or leg, or the entire body.', 'Alter Physical Structure: Earth'),
            ])),

            new TableEntry(62, new Ability('Sonic Flight', 'Fly at the speed of sound, Mach One. Gives the character superior vision, dexterity, and reflexes.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Sonic Flight'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Sonic Flight: SDC', 3, 4, 10), 'Sonic Flight'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Sonic Flight: PE', 1, 4), 'Sonic Flight'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 2, 'Sonic Flight'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, 'Sonic Flight'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 2, 'Sonic Flight'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 6, 'Sonic Flight'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Increased damage from physical Attacks when flying', 'Sonic Flight'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Extraordinary Vision - 10 times greater than a normal human\'s; An 18 inch object can be seen with perfect clarity two miles away.', 'Sonic Flight'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision - 1000ft (305m)', 'Sonic Flight'),
            ])),

            new TableEntry(64, new Ability('Teleport', 'temp')),

            new TableEntry(67, new Ability('Alter Physical Structure: Liquid', 'The weird power to transform into a being of living water-like liquid. Abilities: Water bolt, water behemoth, water merge, manipulate shape, and limited invulnerability.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 20, 'Alter Physical Structure: Liquid'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Radiates no heat when in water form; thus he can not be detected or tracked by infrared or heat sensors.', 'Alter Physical Structure: Liquid'),
            ])),

            new TableEntry(70, new Ability('Disruptive Touch', 'This lethal power actually disrupts the nervous system of the person who falls victim to it.', 'Disruptive Touch', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Disrupt Optic Nerves - temporarily blinds the person; Immobilizes the motor part of the brain causing temporary paralysis. Victims are completely incapacitated. The duration of the blindness and paralysis is 3D4 minutes.', 'Disruptive Touch'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Inflict Pain - 3D6 damage.', 'Disruptive Touch'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Death Touch - Causes 606 damage and shocks the nervous system, plunging the victim into a coma unless a successful savings throw of 15 or higher is made. The use of the Death Touch also takes its toll on the person inflicting the coma. The super being himself is drained each time he uses the Death Touch. Side effects from using the Death Touch: Reduce speed by half, -2 to strike, parry, dodge, and -2 for ALL savings throws for 2D6 melees. Side effects from multiple or continuous use of the Death Touch are cumulative.', 'Disruptive Touch'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Disruptive Touch: PE', 1, 6), 'Disruptive Touch'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Disruptive Touch: SDC', 1, 6, 10), 'Disruptive Touch'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_COMMA_DEATH, 10, 'Disruptive Touch'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Poisons, toxins, and drugs have only half their usual effects, damage, and duration.', 'Disruptive Touch'),
            ])),

            new TableEntry(73, new Ability('Alter Physical Structure: Metal', 'A power that transforms the character into a living juggernaut of metal.', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::NATURAL_ARMOR_RATING, 17, 'Alter Physical Structure: Metal'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 800, 'Alter Physical Structure: Metal'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Alter Physical Structure: Metal - Physical Strength', 3, 4), 'Alter Physical Structure: Metal'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Impervious to cold.', 'Alter Physical Structure: Metal'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'The metal form is cool enough to avoid detection by infrared or heat sensors.', 'Alter Physical Structure: Metal'),
            ])),

            new TableEntry(75, new Ability('Mechano-Link', 'Link with any kind of machine so that man and machine becomes one. This means that vehicles respond to a mere thought, adding to their mobility, and weapons become more precise.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_PILOTING, 20, 'Mechano-Link'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_PILOTING_RELATED, 20, 'Mechano-Link'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_COMPUTER_ELECTRICAL_MECHANICAL, 20, 'Mechano-Link'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 2, 'Mechano-Link'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::UNDERSTAND_OPERATE_ALIEN_MACHINES, 60, 'Mechano-Link'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::DESCRIPTION, 'Merge and communicate with any computer system regardless of preventative programs. The character has the ability to communicate directly with computer and computer-directed machinery. The link can be as direct as touching the machine itself, or can be remote if the machine has some kind of link. Once the link is established the character can examine any of the machine\'s data or programming and can completely reprogram the machine. Performing a mechano-link with a sentient machine, one that has reached the level of self-programming and self-awareness, will mean the psionic can communicate with the machine\'s intelligence. This does not include the ability to command machines.', 'Mechano-Link'),
            ])),

            new TableEntry(78, new Ability('Control Elemental Force: Fire', 'The power to manipulate and control aspects of fire.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Fire Blast - Create a fiery bolt or blast out of thin air and hurl it at a target.', 'Control Elemental Force: Fire'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Spontaneous Combustion - This ability causes any combustible material to ignite. Spontaneous combustion does not create a blazing fire, but only the spark to start a fire.', 'Control Elemental Force: Fire'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Fuel Flame - Quadruples the size of an existing flame or ignites a smoldering ember.', 'Control Elemental Force: Fire'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Create Flame Wall - Can control an existing fire (even a small one) to form a wall or circle.', 'Control Elemental Force: Fire'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Extinguish Fire - Permanently extinguishes any fires within a 90ft radius, up to 120ft away. The fire controller can also bend this power to pan or cut a swath through fire (10ft wide and 320ft long).', 'Control Elemental Force: Fire'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Create Smoke - Generate a dense, grey-black cloud of smoke. The cloud can be created from fiery material that is up 10 90ft away. The cloud is 30 X 30 X 30 ft, temporarily impairing the vision of everyone caught in it. Victims can not see beyond the smoky cloud.', 'Control Elemental Force: Fire'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Invulnerability to Fire - Impervious to ALL types of fire and heat.', 'Control Elemental Force: Fire'),
            ])),

            new TableEntry(81, new Ability('Mimic', 'Imitate or mimic another person\'s physical and mental attributes (not skills nor experience), psionics, abilities, and innate magic abilities (not spell knowledge; just magic power such as those gained from weapons, objects and bestowed). A mimic can not copy/absorb mechanical abilities like those gained through bionics or robotics; nor can he mimic skills, hardware, nor special training. Only the raw physical and/or extraordinary power can be imitated. Skills, education, memories, and experience can not be copied. The mimic can imitate a person by touching him/her or by being within close proximity; 60ft radius. If the person being copied should go beyond the 60ft radius, the imitated power will fade away.')),

            new TableEntry(83, new Ability('Karmic Power', 'Influence his luck and those around him via a sort of Karmic aura. Karma is an energy of positive or negative affect. Theoretically, it is an aspect of the constant struggle between good and evil; order and chaos.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 6, 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 2, 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 4, 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_POSITION_TOXINS_GASES, 6, 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_PSIONICS, 6, 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_MAGIC, 6, 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_COMMA_DEATH, 20, 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Death blows on this character do not kill; instead only stun the character.', 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Critical damage on this character does only normal damage.', 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'On natural 20 to strike, knocks opponent unconscious for 3D4 rounds.', 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_GROUP_ALL, 10, 'Karmic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Karmic Power: SDC', 1, 4, 10), 'Karmic Power'),
            ])),

            new TableEntry(86, new Ability('Sonic Power', 'Manipulate and control aspects of sound.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Hear Wider Spectrum of Sound - Can hear even a one decibel sound at a great distance (1OOOft). This enables him to: Estimate the distance of the sound - 6O%; Estimate speed of approach/departure - 50%; Recognize the type of sound - 6O%; Pinpoint the exact location of sound - 30%. Minuses to strike, parry and dodge in darkness or while blinded or attacking the invisible, are all reduced by half.', 'Sonic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Emit High-Pitched Whine - Will hurt, deafen, and distract all who fall prey to it. The only defense is to plug the ears. Plugging ears with fingers reduces damage and minuses by half, but also prevents any counterattacks except psionic. Ear plugs will prevent any damage and reduce minuses by half.', 'Sonic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Sonic Boom or Blast - Blast or bolt of concentrated sound waves.', 'Sonic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Sonar - Emitting of high-frequency sound waves which bounce off objects, returning and indicating the direction and distance of the reflecting objects. Interpreting shapes - 58%; Estimating Distance - 68%; Estimating Direction - 58; Estimating Exact Location - 42%.', 'Sonic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, 'Sonic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Sonic Power: SDC', 1, 4, 10), 'Sonic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Sonic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 1, 'Sonic Power'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::INITIATIVE, 2, 'Sonic Power'),
            ])),

            new TableEntry(89, new Ability('Vibration', 'temp')),

            new TableEntry(92, new Ability('Shrink', 'Greatly reduce his size and mass. The super being has total control over his shrinking power and can stop at any size. He can resume his normal size at any time.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 6, 'Shrink'),
            ])),

            new TableEntry(95, new Ability('Plant Control', 'Direct, manipulate, and grow plants at an astounding level.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Animate and Control Plants - Mentally manipulate all plant life within a 40ft radius around him. Thus, he can cause any vines, weeds, shrubs, or trees to trap and ensnare an animal, entangle someone, or cover something. He can also manipulate the larger plants to grab and hold something. Although the limbs of the plants can be made to move and function like hands and arms, they are still restricted to the fact that the plant is rooted in the soil.', 'Plant Control'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Grow Plants at an Unbelievable Rate - The character can grow most plants and shrubs, from seed to maturity, in 1D4 melees. Trees and large tree-size plants grow at a rate of 8ft (2.4m) per melee, up to 200ft (61m) tall. The growth is temporary, and the plants will return to their original size within 20 minutes or at the character\'s command.', 'Plant Control'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Alter Wood - The character can alter the strength of wood by increasing or decreasing its SDC.', 'Plant Control'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::RECOGNIZE_IDENTIFY_PLANTS, 88, 'Plant Control'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PROWL, 10, 'Plant Control'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_CLIMBING, 10, 'Plant Control'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Plant Control: SDC', 1, 4), 'Plant Control'),
            ])),

            new TableEntry(98, new Ability('Transferal/Possession', 'temp')),

            new TableEntry(100, new Ability('Weight Manipulation', 'temp')),

            new TableEntry(101, new Ability('Animal Abilities - Canine', 'This power gives humanoid characters the traits, abilities and instincts of a particular type of animaL It does not actually transform the person into an animal. The character can also control (to a limited degree) any animals that fall into his general type. Actual communication/dialog is impossible, but the character understands the general meanings of grunts, growls, whines, and facial and tail expressions. The animals Will look toward the super being as the leader of a pack and will follow his actions. Commands will be limited to stop, go, attack, wait, run, etc. Pointed ears; large, flat nose, and small, pointed, canine-like teeth.', [
                new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::ATTRIBUTE_SPEED, 2, 'Animal Abilities - Canine'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, 10, 'Animal Abilities - Canine'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Animal Abilities - Canine: SDC', 1, 4, 10), 'Animal Abilities - Canine'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Animal Abilities - Canine: PS', 1, 6), 'Animal Abilities - Canine'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Animal Abilities - Canine: PE', 1, 6), 'Animal Abilities - Canine'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Detect very faint scent traces. Tracking by smell, like a bloodhound, is possible at a skill proficiency of 50%+ 4% per level of experience. Recognizing a person by scent is also possible at a 56% effectiveness.', 'Animal Abilities - Canine'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Can control 3D4 dogs.', 'Animal Abilities - Bear'),
            ])),

            new TableEntry(102, new Ability('Animal Abilities - Cat: small, domesticated', 'This power gives humanoid characters the traits, abilities and instincts of a particular type of animal It does not actually transform the person into an animal. The character can also control (to a limited degree) any animals that fall into his general type. Actual communication/dialog is impossible, but the character understands the general meanings of grunts, growls, whines, and facial and tail expressions. The animals Will look toward the super being as the leader of a pack and will follow his actions. Commands will be limited to stop, go, attack, wait, run, etc. Large slanted eyes, and pointed ears.', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_CLIMBING, 50, 'Animal Abilities - Cat (domestic)'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_PROWL, 70, 'Animal Abilities - Cat (domestic)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::BALANCE_WALK_TIGHTROPE, 60, 'Animal Abilities - Cat (domestic)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 4, 'Animal Abilities - Cat (domestic)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Superior vision - See about twice as good as a normal human. Nightvision - 60ft.', 'Animal Abilities - Cat (domestic)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Animal Abilities - Cat (domestic): PP', 1, 6), 'Animal Abilities - Cat (domestic)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Leap up to 6ft straight up or across (1.8m).', 'Animal Abilities - Cat (domestic)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Can control 2d6 domestic cats.', 'Animal Abilities - Cat (domestic)'),
            ])),

            new TableEntry(103, new Ability('Animal Abilities - Cat: big wild predators', 'Large slanted eyes; large, pointed ears, and add 30 pounds to the weight (all muscle).', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_CLIMBING, 65, 'Animal Abilities - Cat (big)'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_PROWL, 55, 'Animal Abilities - Cat (big)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Animal Abilities - Cat (big)', 1, 6, 10), 'Animal Abilities - Cat (big)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Animal Abilities - Cat (big)', 1, 6), 'Animal Abilities - Cat (big)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Animal Abilities - Cat (big)', 2, 4), 'Animal Abilities - Cat (big)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Superior Vision  - See about two times better than a normal human. Nightvision 60ft.', 'Animal Abilities - Cat (big)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Extraordinary leaper: 20ft (6.1m) straight up and 40ft (12.2m) across/horizontally.', 'Animal Abilities - Cat (big)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Roar that can be heard up to a mile and a half(2km) away.', 'Animal Abilities - Cat (big)'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Can control 2d4 cats of any kind.', 'Animal Abilities - Cat (big)'),
            ])),

            new TableEntry(104, new Ability('Animal Abilities - Fish', 'Small ears, roundish eyes, pale complexion, and slightly webbed fingers and toes', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_SWIMMING, 98, 'Animal Abilities - Fish'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Breathe underwater indefinitely.', 'Animal Abilities - Fish'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Physical Strength (P.S.) becomes doubled when underwater only.', 'Animal Abilities - Fish'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision 60ft out of the water; 120ft in the water (18 or 48m).', 'Animal Abilities - Fish'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Animal Abilities - Fish: SDC', 1, 4, 10), 'Animal Abilities - Fish'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Animal Abilities - Fish: PP', 1, 4), 'Animal Abilities - Fish'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Can control 4D6 fish of any kind.', 'Animal Abilities - Fish'),
            ])),

            new TableEntry(105, new Ability('Animal Abilities - Hoofed', 'Including horse; and cloven, like deer, antelope, etc. Long face; powerful, muscular legs, and pointed ears', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Animal Abilities - Hoofed: SDC', 1, 6, 10), 'Animal Abilities - Hoofed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Animal Abilities - Hoofed: PE', 2, 6), 'Animal Abilities - Hoofed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, new Roll('Animal Abilities - Hoofed: PS', 2, 4), 'Animal Abilities - Hoofed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Keen sense of hearing, about double a normal human\'s.', 'Animal Abilities - Hoofed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Leap up to 6ft ( 1.8m) high and 15ft (4.6m) lengthwise.', 'Animal Abilities - Hoofed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Kick attack does 2D6 damage (plus P.S. damage bonus).', 'Animal Abilities - Hoofed'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Can control 2D6 of any hoofed animal.', 'Animal Abilities - Hoofed'),
            ])),

            new TableEntry(106, new Ability('Animal Abilities - Musteloid', 'Short in stature; small eyes; small, furry ears; husky build and clawed fingers.', [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_CLIMBING, 39, 'Animal Abilities - Musteloid'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Natural digging ability: This is the ability to dig through dirt, mud, or sand. Only the character\'s body moves through the earth; no tunnel is left behind.', 'Animal Abilities - Musteloid'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Tunneling is a digging process that leaves a passable tunnel. Tunnels near the surface can be used as pit traps.', 'Animal Abilities - Musteloid'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Excavation means being able to hollow out large, underground chambers. Characters with Excavation can also dig under buildings, roads, and other structures to weaken their foundations.', 'Animal Abilities - Musteloid'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Clawed fingers do 1D8 damage as weapons/punch', 'Animal Abilities - Musteloid'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 6, 'Animal Abilities - Musteloid'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision 60ft (18m)', 'Animal Abilities - Musteloid'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Animal Abilities - Musteloid: SDC', 1, 4, 10), 'Animal Abilities - Musteloid'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Animal Abilities - Musteloid: PS', 1, 6), 'Animal Abilities - Musteloid'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Can control 1D8 of any type of musteloids.', 'Animal Abilities - Musteloid'),
            ])),

            new TableEntry(107, new Ability('Animal Abilities - Nocturnal Animal', 'Large, round eyes.', [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Extraordinary vision approximately 10 times better than a normal human. This means the character can clearly see an 18 inch item up to two miles away (3.2km).', 'Animal Abilities - Nocturnal Animal'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision 600ft (183m).', 'Animal Abilities - Nocturnal Animal'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Extraordinary Sense of Smell - Detect very faint scent traces. Identify person by scent is a 48% chance.', 'Animal Abilities - Nocturnal Animal'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_TRACKING, 40, 'Animal Abilities - Nocturnal Animal'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_PROWL, 70, 'Animal Abilities - Nocturnal Animal'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 20, 'Animal Abilities - Nocturnal Animal'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Animal Abilities - Nocturnal Animal: PP', 1, 4), 'Animal Abilities - Nocturnal Animal'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Can control 1D8 of any type of nocturnal animal.', 'Animal Abilities - Nocturnal Animal'),
            ])),


            new TableEntry(108, new Ability('Animal Metamorphosis - Cat', 'Completely transform into a cat. As an animal, the person gets all the inherent abilities and defenses that animal form may offer, while retaining his own memory, IQ, SDC, hit points and ability to speak. All physical attributes change, up or down, as best fits the animal. The animal metamorphoser can change from humanoid to animal, and back again, at will. Each change counts as an action/attack per melee.', [
            ])),

            new TableEntry(109, new Ability('Animal Metamorphosis - Canine', 'Completely transform into a canine. As an animal, the person gets all the inherent abilities and defenses that animal form may offer, while retaining his own memory, IQ, SDC, hit points and ability to speak. All physical attributes change, up or down, as best fits the animal. The animal metamorphoser can change from humanoid to animal, and back again, at will. Each change counts as an action/attack per melee.', [
            ])),

            new TableEntry(110, new Ability('Animal Metamorphosis - Bird', 'Completely transform into a bird. As an animal, the person gets all the inherent abilities and defenses that animal form may offer, while retaining his own memory, IQ, SDC, hit points and ability to speak. All physical attributes change, up or down, as best fits the animal. The animal metamorphoser can change from humanoid to animal, and back again, at will. Each change counts as an action/attack per melee.', [
            ])),

            new TableEntry(111, new Ability('Animal Metamorphosis - Hoofed', 'Completely transform into a hoofed. As an animal, the person gets all the inherent abilities and defenses that animal form may offer, while retaining his own memory, IQ, SDC, hit points and ability to speak. All physical attributes change, up or down, as best fits the animal. The animal metamorphoser can change from humanoid to animal, and back again, at will. Each change counts as an action/attack per melee.', [
            ])),

            new TableEntry(112, new Ability('Animal Metamorphosis - Bear', 'Completely transform into a bear. As an animal, the person gets all the inherent abilities and defenses that animal form may offer, while retaining his own memory, IQ, SDC, hit points and ability to speak. All physical attributes change, up or down, as best fits the animal. The animal metamorphoser can change from humanoid to animal, and back again, at will. Each change counts as an action/attack per melee.', [
            ])),

            new TableEntry(113, new Ability('Animal Metamorphosis - Reptile', 'Completely transform into a reptile. As an animal, the person gets all the inherent abilities and defenses that animal form may offer, while retaining his own memory, IQ, SDC, hit points and ability to speak. All physical attributes change, up or down, as best fits the animal. The animal metamorphoser can change from humanoid to animal, and back again, at will. Each change counts as an action/attack per melee.', [
            ])),

            new TableEntry(114, new Ability('Animal Metamorphosis - Any and all animals', 'Completely transform into a any animal. As an animal, the person gets all the inherent abilities and defenses that animal form may offer, while retaining his own memory, IQ, SDC, hit points and ability to speak. All physical attributes change, up or down, as best fits the animal. The animal metamorphoser can change from humanoid to animal, and back again, at will. Each change counts as an action/attack per melee.', [
            ])),
        ]);
    }
}
