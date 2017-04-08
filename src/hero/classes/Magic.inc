<?php
namespace Heroes\hero\classes;

use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\superabilities\TableSuperAbilities;
use Heroes\tables\TableSpells;

class Magic extends BaseClass
{

    // what type of magician are you?
    public $magicType;

    // == Enchanted Weapon == //
    public $enchantedWeaponDamage;
    public $enchantedWeaponType;

    // == Enchanted Object == //
    // array of spells that the enchanted object provides
    public $objectSpells;
    public $objectSpellLevel;
    public $objectSpellsPerDay;

    // == Mystic == //
    public $spellsPerDay;
    public $spellsKnown;

    /**
     * create a character's class
     *
     * @param Hero $hero the hero
     * @throws \Exception ya ya, whatever
     */
    public function create(Hero &$hero)
    {
        // step 1 : attributes - already done by generator
        // step 2 : education - normal education

        // step 3 : determine type of magic
        list($this->magicType, $function) = $this->engine->tableRoller->rollTable('Magic Type', [
            new TableEntry(25, ['Enchanted Weapon', 'weapon']),
            new TableEntry(50, ['Enchanted Object', 'object']),
            new TableEntry(63, ['Mystic Study - Wizard', 'studyWizard']),
            new TableEntry(75, ['Mystic Study - Magician', 'studyMagician']),
            new TableEntry(100, ['Bestowed', 'bestowed']),
        ]);
        $this->$function($hero);
    }

    private function studyMagician(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Magic: Mystic Study - Magician'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Sense Evil: Sense the presence of truly strong evil. Range: lOOft (305m)', 'Magic: Mystic Study - Magician'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SPECIAL_SENSE_MAGIC, 28, 'Magic: Mystic Study - Magician'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_ILLUSIONS, 2, 'Magic: Mystic Study - Magician'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_MIND_ALTERING_EFFECTS, 2, 'Magic: Mystic Study - Magician'));

        $this->spellsPerDay = 7;
        $this->spellsKnown = [];
        $this->selectSpells($this->spellsKnown, TableSpells::illusionarySpells(), 10);
    }

    private function studyWizard(Hero &$hero)
    {
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 30, 'Magic: Mystic Study - Wizard'));

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Astral Projection: When a person astral projects, his physical body falls into a death-like trance. The astral body enters the vast plane of the astral world. It is a pleasant world of rolling clouds and endless yellow sky. In this dimension the astral body is free to fly great distances in mere moments, and gaze from the astral plane into the world containing its physical body. Only psionic presence sense can detect an astral bod and only psionic attacks (from both the physical and astral planes) can harm the astral body. The astral body can be killed psionically by being prevented from returning to its physical body. Psionic hypnotic suggestion,  stun, sleep, mind wipe, dispel spirits, and possession are all powerful weapons against the astral traveler.', 'Magic: Mystic Study - Wizard'));

        // not doing familiar because it starts at level 3 and all these characters are level 1

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SPECIAL_RECOGNIZE_MAGIC, 68, 'Magic: Mystic Study - Wizard'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Sense Evil: Sense the presence of truly strong evil. Range: lOOft (305m)', 'Magic: Mystic Study - Wizard'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SPECIAL_SENSE_MAGIC, 28, 'Magic: Mystic Study - Wizard'));

        $this->spellsPerDay = 8;
        $this->spellsKnown = [];
        $this->selectSpells($this->spellsKnown, TableSpells::allSpells(), 14);
    }

    private function object(Hero &$hero)
    {
        $this->objectSpellLevel = $this->engine->tableRoller->rollTable('Magic: Enchanted Object - Spell Level', [
            new TableEntry(25, 3),
            new TableEntry(50, 4),
            new TableEntry(75, 5),
            new TableEntry(100, 6),
        ]);

        $this->objectSpellsPerDay = $this->engine->tableRoller->rollTable('Magic: Enchanted Object - Spells per Day', [
            new TableEntry(11, 7),
            new TableEntry(21, 8),
            new TableEntry(33, 9),
            new TableEntry(55, 10),
            new TableEntry(67, 11),
            new TableEntry(89, 12),
            new TableEntry(100, 13),
        ]);

        list($numIllusion, $numMagic, $numMajor, $numMinor) = $this->engine->tableRoller->rollTable('Magic: Enchanted Object - Powers', [
            new TableEntry(14, [10, 0, 0, 0]),
            new TableEntry(30, [0, 8, 0, 0]), // wizard only?
            new TableEntry(50, [5, 3, 0, 0]),
            new TableEntry(70, [6, 2, 0, 0]),
            new TableEntry(85, [3, 5, 0, 0]),
            new TableEntry(100, [0, 0, 1, 1]),
        ]);
        if ($numIllusion || $numMagic) {
            $this->objectSpells = [];
        }
        if ($numIllusion) {
            $this->selectSpells($this->objectSpells, TableSpells::illusionarySpells(), $numIllusion);
        }

        if ($numMagic) {
            $this->selectSpells($this->objectSpells, TableSpells::magicSpells(), $numMagic);
        }

        $tableSuperAbilities = new TableSuperAbilities($this->engine);
        while ($numMajor || $numMinor) {
            if ($numMajor) {
                $ability = $tableSuperAbilities->rollMajor();
                if ($ability) {
                    $ability->description = 'Magic: Enchanted Weapon - ' . $ability->description;
                    if ($hero->addAbility($ability)) {
                        $numMajor--;
                    }
                }
            }
            if ($numMinor) {
                $ability = $tableSuperAbilities->rollMinor();
                if ($ability) {
                    $ability->description = 'Magic: Enchanted Weapon - ' . $ability->description;
                    if ($hero->addAbility($ability)) {
                        $numMinor--;
                    }
                }
            }
        }

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_MAGIC, 2, 'Magic: Enchanted Object'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 10, 'Magic: Enchanted Object'));

        $bonuses = $this->engine->tableRoller->rollTable('Magic: Enchanted Object - Other Abilities', [
            new TableEntry(20, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Impervious to fire.', 'Magic: Enchanted Object')),
            new TableEntry(40, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Invisibility at will.', 'Magic: Enchanted Object')),
            new TableEntry(50, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Fly', 'Magic: Enchanted Object')),
            new TableEntry(60, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Impervious to poison', 'Magic: Enchanted Object')),
            new TableEntry(70, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Shoot fire bolt from hand; range: 40ft (12.2m); damage: 3d6.', 'Magic: Enchanted Object')),
            new TableEntry(79, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_PSIONICS, 1, 'Magic: Enchanted Object')),

            // + d4 to one attribute
            new TableEntry(89, new Bonus(Bonus::BONUS_TYPE_ADD, $this->engine->tableRoller->rollTable(
                'Magic: Enchanted Object - attribute', [
                    new TableEntry(1, BonusTargets::ATTRIBUTE_SPEED),
                    new TableEntry(2, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE),
                    new TableEntry(3, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH),
                    new TableEntry(4, BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT),
                    new TableEntry(5, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY),
                    new TableEntry(6, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE),
                    new TableEntry(7, BonusTargets::ATTRIBUTE_PHYSICAL_BEAUTY),
                    new TableEntry(8, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS),
                ]
            ), new Roll('Magic: Enchanted Object - attribute bonus', 1, 4), 'Magic: Enchanted Object')),

            // Impervious to magic, and hps & sdc divided by half
            new TableEntry(100,[
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Impervious to magic', 'Magic: Enchanted Object'),
                new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::HIT_POINTS, .5, 'Magic: Enchanted Object'),
                new Bonus(Bonus::BONUS_TYPE_MULTIPLY, BonusTargets::SDC, .5, 'Magic: Enchanted Object'),
            ]),
        ]);
        $hero->addBonus($bonuses);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 35, 'Magic: Enchanted Weapon'));
    }

    /**
     * @param $spellList array already taken spells, add spells to this list
     * @param $spells array possible spells
     * @param $numSpells int number to select
     */
    private function selectSpells(&$spellList, $spells, $numSpells)
    {
        $this->engine->arrayTools->shuffle($spells);
        for ($x = 0; $x < $numSpells; $x++) {
            // lists may have the same spell on them, both magic and illusion have see the invisible.
            $spell = array_pop($spells);

            // see if spell already taken
            $found = false;
            foreach ($spellList as $objectSpell) {
                if ($found = 0 === strcmp($objectSpell->title, $spell->title)) {
                    break;
                }
            }
            if ($found) {
                // already taken so get another
                $numSpells++;
            } else {
                // not already taken so add it
                $spellList[] = $spell;
            }
        }
    }

    private function weapon(Hero &$hero)
    {
        $this->enchantedWeaponType = $this->engine->tableRoller->rollTable('Enchanted Weapon Type', [
           new TableEntry(10, 'Battle Axe'),
           new TableEntry(20, 'Spear'),
           new TableEntry(32, 'Short Sword'),
           new TableEntry(45, 'Large Sword'),
           new TableEntry(58, 'Staff'),
           new TableEntry(70, 'Mace'),
           new TableEntry(80, 'War Hammer'),
           new TableEntry(90, 'Ball and Chain'),
           new TableEntry(100, 'Morning Star'),
        ]);
        $this->enchantedWeaponDamage = $this->engine->tableRoller->rollTable('Enchanted Weapon Damage', [
            new TableEntry(25, '3d6'),
            new TableEntry(50, '4d6'),
            new TableEntry(75, '5d6'),
            new TableEntry(100, '6d6'),
        ]);
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Magical ' . $this->enchantedWeaponType . ' that is totally indestructible. Made of black, grey, blue-grey, dark red or bright gold or silver colored metal and lined with rune symbols from tip to handle. Deals ' . $this->enchantedWeaponDamage . ' damage. Affects/damages all creatures of magic, including animated dead, zombies, vampires, werewolves, demon, etc. Provides resistance against fire and cold (does half damage). Creates a costume or battle dress out of thin air for combat. Activated when the wielder speaks its name.', 'Magic: Enchanted Weapon'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, 'Magic: Enchanted Weapon'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, 'Magic: Enchanted Weapon'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_MAGIC_SPELLS_ENCHANTMENTS, 3, 'Magic: Enchanted Weapon'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Magic Weapon: SDC', 1, 6, 10), 'Magic: Enchanted Weapon'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'See Invisible', 'Magic: Enchanted Weapon'));

        // select 5 powers out of the following (combining chaos and order for simplicity)
        $powers = [
            // powers of order
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Healing Touch: Restores 3D6 hit points or SDC and heals burns. The magical healing leaves no scars. The healing touch can be used 10 times per day (24 hours). The weapon must touch the person to be healed.', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DAMAGE, 6, 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Spits Lightning Bolt: Can be used as often as once every melee. Damage: 4D6, Range: 300ft (91.5m).', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Spits Fire Ball: Can be used as often as once every melee. Damage: 5D6, Range: 200ft (61m).', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Returns to Wielder When Thrown: Returns immediately after striking the target. Range: 120ft (36m), counts as two attacks/actions.', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Turns itself and the wielder invisible.', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Impervious to Fire: As long as the hero holds the weapon he/she is impervious to fire (including magic fire).', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Levitation at will: Can levitate the weapon, wielder and up to 1OOlbs additional, up and down. Levitation does not allow movement from side to side. Range: 300ft high - maximum (91.5m).', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Sense Magic: The ability to sense the presence of magic other than your own. Unfortunately, the sense can not pinpoint the source of magic or identify how many. The best it can do in identifying the number of other magic sources is: a couple, a few, and many. Range: within a 300ft (91.5m) area.', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Fly: The ability to fly like a bird at will. Maximum speed is 50mph. The normal bonuses to dodge and parry apply.', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision: See clearly in the dark much like passive nightvision light amplification goggles. Range: 300ft (91.5m).', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Mystic Shield: Creates a mystic shield or enclosure to protect the weapon wielder and up to six normal size people within five feet of the weapon. The shield has a total of 200 S.D.C. and is effective against all types of attacks Range: Covers up to a 5ft area (1.5m). Can be created around the weapon wielder or around others up to 60ft away (18.3m).', 'Magic: Enchanted Weapon'),
            [
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 24, 'Magic: Enchanted Weapon - Super Strength'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::DAMAGE, 9, 'Magic: Enchanted Weapon - Super Strength'),
                new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, new Roll('Magic: Enchanted Weapon - Super Strength: SDC', 1, 4, 10), 'Magic: Enchanted Weapon - Super Strength'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Super Strength:  There is no time limit as to how long the strength lasts; however, the hero must invoke the weapon\'s name and carry it/use it.', 'Magic: Enchanted Weapon - Super Strength'),
            ],
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Tongues: The ability to understand and speak any language at will.', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Words of Truth: The being affected by this enchantment is compelled to answer all questions truthfully. The being affected must be within 5 feet and can be asked two questions per melee. It is wise to keep questions simple and clear to avoid confusion. Saving Throw: The person makes a saving throw for each question asked. Saving throw requirements: Standard; affected being does not have to answer if successful.', 'Magic: Enchanted Weapon'),

            // powers of chaos
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Fever Touch: A debilitating touch that harms; rather than cures. If an injured person is touched by the weapon his/her condition worsens, receiving 1D6 damage and fever. The fever impairs sleep, eating, strength, and thought. The victim is -3 to strike, parry, dodge, and roll. Skills are -10%. Duration of the fever is 2D4 hours. A magical healing touch will cure a fever touch, but restores no hit points. The fever touch can be used 10 times per day (24 hours).', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Power Bolt: A pitch-black bolt of icy cold can be fired as often as once per melee. Damage: 4D6, Range: 200ft (61m).', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Animate and Control the Dead: This macabre power enables the weapon wielder to animate and control skeletons and corpses. These zombie like automatons have no will of their own, nor any intelligence. They will obey any simple command, such as "protect me," "slay him," and so on. They obey only the weapon wielder. Limitations: 20 is the most that can be controlled at a time. The control of the dead counts as two of the weapon wielder\'s attacks per melee.', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Unnatural Darkness: An inky blackness so dark that a person can not see beyond two feet ahead. Only the creator of the darkness and those with magical nightvision can see clearly in the blackness. Very intense light (solar), dispel magic, dispel magic barrier, and the weapon wielder can dispel the darkness. The darkness can cover a 100ft area (30m).', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Circle of Flame: Creates a circle of towering flame (10 to 20ft tall and 3 to 5ft thick). Anyone passing through the flame takes 4D6 + 4 damage. Range: Around oneself or around others up to 90ft away. The maximum circumference of the circle is 30ft.', 'Magic: Enchanted Weapon'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Portal of Fear: First a large, elliptical patch of blackness appears. Seconds later, huge, black tentacles with grey blotches seem to grow out of the expanding black patch. The black patch grows to ten feet long and the 4-24 (4D6) tentacles stretch an astounding 30ft. Tactically, the most effective use of the Portal of Fear is to place it where it blocks a passageway. Each tentacle is easily large enough to snare one man. Once snared, the character must roll to save vs magic (12 or higher). A failed roll means fear and panic, reducing attacks per melee to one. A successful save means the hero is unaffected and can continue to struggle free. Within two melees the snared person is pulled screaming into the portal. Another roll to save vs magic must be made (this time a 16 or higher must be rolled). Whether the save is successful or not, the individual is immediately spit out about 20ft (6m). If the save vs magic failed, the character is wracked with fear and can do nothing but cringe in terror for 4D4 melees. No attacks or actions are possible. If successful the character is not affected and is free to continue his/her fight. The tentacles are not alive, but ectoplasmic apparitions. Each has one attack per melee, +2 to strike and 50 SDC. If one tentacle is destroyed it will release its victim from its iron grip, but another will try to scoop him up in its place. The thing disappears when all the tentacles are destroyed or a dispel magic barrier spell is cast or when !he weapon wielder dispels it himself. Limitations: Only one Portal of Fear can be created at a time and restricted to three times per day (24 hours).', 'Magic: Enchanted Weapon'),
            [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Power of Darkness: Impervious to poisons and toxic gases.', 'Magic: Enchanted Weapon - Power of Darkness'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 2, 'Magic: Enchanted Weapon - Power of Darkness'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, 6, 'Magic: Enchanted Weapon - Power of Darkness'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_PROWL, 10, 'Magic: Enchanted Weapon - Power of Darkness'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Magic: Enchanted Weapon - Power of Darkness', 1, 4, 10), 'Magic: Enchanted Weapon - Power of Darkness'),
            ],
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Cloud of Smoke: Create a cloud of dense, black smoke (30ft X 30ft x 30ft maximum size) up to ninety feet away. Victims caught in the cloud will be unable to see anything beyond the cloud and the impaired vision allows them to see no more than three feet in the cloud (and that is only a blurry shape). While in the cloud, victims will be -5 to strike, parry, and dodge.', 'Magic: Enchanted Weapon'),
        ];

        $this->engine->arrayTools->shuffle($powers);

        for ($x = 0; $x < 5; $x++) {
            $power = array_pop($powers);
            if (!is_array($power)) {
                $power = [$power];
            }
            foreach ($power as $singlePower) {
                $hero->addBonus($singlePower);
            }
        }

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 20, 'Magic: Enchanted Weapon'));
    }

    private function study(Hero &$hero)
    {
        throw new \Exception('Needs implemented');
    }

    private function bestowed(Hero &$hero)
    {
        throw new \Exception('Needs implemented');
    }

}