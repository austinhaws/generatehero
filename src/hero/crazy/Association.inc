<?php
namespace Heroes\hero\crazy;

use Heroes\engine\TableEntry;
use Heroes\hero\classes\BaseClass;
use Heroes\hero\Hero;

class Association extends BaseClass
{
    /** @var string what is the power associated with */
    public $association;
    /** @var string what food triggers power */
    public $popeye;

    function create(Hero &$hero, $options = false)
    {
        $this->association = $this->engine->tableRoller->rollTable('Association: association', [
            new TableEntry(16, 'Daytime Complex'),
            new TableEntry(30, 'Nighttime Complex'),
            new TableEntry(50, 'Popeye Syndrome'),
            new TableEntry(70, 'Magic Object'),
            new TableEntry(85, 'Power Words'),
            new TableEntry(100, 'Solar Syndrome'),
        ]);

        // daytime: character believes powers are only active during daytime.
        // nighttime: character believes powers are only active during nighttime.
        // popeye: one handful equals 3 hours
        // magic object: magic object bestows powers
        // power words: must speak words to gain super powers
        // solar syndrome: charges powers with solar energy; in full sunlight +10SDC, +5% skills
            // in shadow: abilities are 1/2 and skills -5%; in darkness/night: no super powers, skills -20%

        if ($this->association == 'Popeye Syndrome') {
            $this->popeye = $this->engine->tableRoller->rollTable('Popeye: power food', [
                new TableEntry(5, 'Garlic'),
                new TableEntry(10, 'Asparagus dipped in vanilla yogurt'),
                new TableEntry(14, 'Raw Rhubarb'),
                new TableEntry(19, 'Granola Bar'),
                new TableEntry(23, 'Chicken Livers'),
                new TableEntry(27, 'Raw Brown Rice'),
                new TableEntry(32, "Pig's Ear"),
                new TableEntry(36, 'Parsnips and Pumpkin Seeds'),
                new TableEntry(40, 'Dogfish Croquettes'),
                new TableEntry(45, 'Corn Husks'),
                new TableEntry(49, 'Marinated Eel'),
                new TableEntry(53, 'Fresh Chives and Parsley'),
                new TableEntry(57, 'Anchovy Stuffed Grape Leaves'),
                new TableEntry(62, 'Oxtail'),
                new TableEntry(66, 'Carrot Juice'),
                new TableEntry(70, 'Apple Cores'),
                new TableEntry(75, 'Cabbage Quiche'),
                new TableEntry(79, 'Pickled Herring'),
                new TableEntry(83, 'Instant Breakfast Mix'),
                new TableEntry(88, 'Collard Greens'),
                new TableEntry(92, 'Walnuts and Bay Leaves'),
                new TableEntry(96, 'Raw Eggs and Bean Sprouts'),
                new TableEntry(100, 'Twinkies'),
            ]);
        }
    }
}