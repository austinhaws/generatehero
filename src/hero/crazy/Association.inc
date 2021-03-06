<?php
namespace Heroes\hero\crazy;

use Heroes\engine\Engine;
use Heroes\engine\TableEntry;
use Heroes\hero\classes\BaseClass;
use Heroes\hero\Hero;

class Association extends BaseClass
{
    /** @var string what is the power associated with */
    public $association;
    /** @var string what food triggers power */
    public $popeye;

    public function __construct(Engine &$engine)
    {
        parent::__construct($engine, 'Crazy');
        $this->classSubtype = 'Association';
        $this->crazyDescription = 'The character is convinced that he gains his strength, skills or powers from some sort of object or other worldly source.';
    }

    /**
     * @param Hero $hero
     * @param bool $options
     */
    function create(Hero &$hero, $options = false)
    {
        $this->association = $this->engine->tableRoller->rollTable('Association: association', [
            new TableEntry(16, 'Daytime Complex: character believes powers are only active during daytime'),
            new TableEntry(30, 'Nighttime Complex: character believes powers are only active during nighttime'),
            new TableEntry(50, 'Popeye Syndrome: one handful equals 3 hours'),
            new TableEntry(70, 'Magic Object: magic object bestows powers'),
            new TableEntry(85, 'Power Words: must speak words to gain super powers'),
            new TableEntry(100, 'Solar Syndrome: charges powers with solar energy'),
        ]);

        // daytime: character believes powers are only active during daytime.
        // nighttime: character believes powers are only active during nighttime.
        // popeye: one handful equals 3 hours
        // magic object: magic object bestows powers
        // power words: must speak words to gain super powers
        // solar syndrome: charges powers with solar energy; in full sunlight +10SDC, +5% skills
            // in shadow: abilities are 1/2 and skills -5%; in darkness/night: no super powers, skills -20%

        if ($this->association == 'Popeye Syndrome: one handful equals 3 hours') {
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
