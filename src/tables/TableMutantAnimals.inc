<?php

namespace Heroes\tables;

use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\classes\MutantAnimal;
use Heroes\hero\classes\MutantAnimalBonus;

class TableMutantAnimals extends TableBase
{

    const BUILD_TYPE_SHORT = 'short';
    const BUILD_TYPE_MEDIUM = 'medium';
    const BUILD_TYPE_LONG = 'long';

    const POWER_CATEGORY_BIPED = 'Biped';
    const POWER_CATEGORY_FLIGHT = 'Flight';
    const POWER_CATEGORY_HANDS = 'Hands';
    const POWER_CATEGORY_LOOKS = 'Looks';
    const POWER_CATEGORY_NATURAL_BITE = 'Natural Bite';
    const POWER_CATEGORY_NATURAL_BODY_ARMOR = 'Natural Body Armor';
    const POWER_CATEGORY_NATURAL_CLAW = 'Natural Claw';
    const POWER_CATEGORY_NATURAL_HORN = 'Horns';
    const POWER_CATEGORY_NATURAL_TEETH = 'Natural Teeth';
    const POWER_CATEGORY_NATURAL_WEAPONS = 'Natural Weapons';
    const POWER_CATEGORY_POWERS = 'Powers';
    const POWER_CATEGORY_SPEECH = 'Speech';

    private function standardProgression()
    {
        return [
            new MutantAnimalBonus('None', 0, false),
            new MutantAnimalBonus('Partial', 5, false),
            new MutantAnimalBonus('Full', 10, false),
        ];
    }

    private function alligator()
    {
        return new MutantAnimal(
            'Alligator',
            'Alligators arc the largest reptiles in North America. They are dangerous, swamp-dwelling carnivores. Their horny scales provide extra protection. Long jaws filled with conical teeth arc designed for grasping and tearing apart prey',
            9, TableMutantAnimals::BUILD_TYPE_LONG,
            40,
            [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 3, 'Mutant: Alligator'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 1, 'Mutant: Alligator'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, 1, 'Mutant: Alligator'),
            ],
            [
                TableMutantAnimals::POWER_CATEGORY_HANDS => $this->standardProgression(),
                TableMutantAnimals::POWER_CATEGORY_BIPED => $this->standardProgression(),
                TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
                TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                    new MutantAnimalBonus('None', 0, [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Large snout, no external ears, large scales and an elongated body.', 'Mutant: Alligator')
                    ]),
                    new MutantAnimalBonus('Partial', 5, [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Definite snout, no external ears, noticeable scales, and a long body.', 'Mutant: Alligator')
                    ]),
                    new MutantAnimalBonus('Full', 10, [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Lumpy features, hairless, small ears and pointed teeth.', 'Mutant: Alligator')
                    ]),
                ],
                TableMutantAnimals::POWER_CATEGORY_NATURAL_WEAPONS => [
                    new MutantAnimalBonus('Teeth', 5, [
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Teeth that can do 1D8 damage', 'Mutant: Animal')
                    ]),
                ],
                TableMutantAnimals::POWER_CATEGORY_NATURAL_BODY_ARMOR => [
                    new MutantAnimalBonus('Light Natural Body Armor', 15, [
                        new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::NATURAL_ARMOR_RATING, 6, 'Mutant: Alligator - Light Natural Body Armor'),
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 20, 'Mutant: Alligator - Light Natural Body Armor'),
                    ]),
                    new MutantAnimalBonus('Medium Natural Body Armor', 30, [
                        new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::NATURAL_ARMOR_RATING, 8, 'Mutant: Alligator - Medium Natural Body Armor'),
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 40, 'Mutant: Alligator - Medium Natural Body Armor'),
                    ]),
                    new MutantAnimalBonus('Heavy Natural Body Armor', 45, [
                        new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::NATURAL_ARMOR_RATING, 10, 'Mutant: Alligator - Heavy Natural Body Armor'),
                        new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 60, 'Mutant: Alligator - Heavy Natural Body Armor'),
                    ]),
                ],
            ]
        );
    }

    private function bearBonuses($kind)
    {
        $bearType = "Mutant: Bear ($kind)";
        return [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 6, $bearType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 1, $bearType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, 4, $bearType),
        ];
    }

    private function bearFeatures($kind)
    {
        $bearType = "Mutant: Bear ($kind)";
        return [
            TableMutantAnimals::POWER_CATEGORY_HANDS => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_BIPED => [
                new MutantAnimalBonus('Partial', 0, false),
                new MutantAnimalBonus('Full', 5, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('None', 0, [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Large, round, snouted head, small eyes, furry ears on top of head, thick fur, short legs and large arms, a small furry tail.', $bearType)
                ]),
                new MutantAnimalBonus('Partial', 5, [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Definite snout, large head, heavy fur, massive build.', $bearType)
                ]),
                new MutantAnimalBonus('Full', 10, [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Dark circles around eyes, thick beard, head and body hair, powerful build.', $bearType)
                ]),
            ],
            TableMutantAnimals::POWER_CATEGORY_NATURAL_BITE => [
                new MutantAnimalBonus('Bite', 5, [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Teeth that can do 1D6 damage', $bearType)
                ]),
                new MutantAnimalBonus('Bite', 10, [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Teeth that can do 1D10 damage', $bearType)
                ]),
            ],
            TableMutantAnimals::POWER_CATEGORY_NATURAL_CLAW => [
                new MutantAnimalBonus('Claw', 5, [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Claws that can do 1D8 damage', $bearType)
                ]),
                new MutantAnimalBonus('Claw', 10, [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Claws that can do 2d6 damage', $bearType)
                ]),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Advanced Hearing', 5, [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced Hearing', $bearType)]),
                new MutantAnimalBonus('Advanced Smell', 15, [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced Smell', $bearType)]),
            ],
        ];
    }

    private function bear($type, $description, $initialSize, $startingBio)
    {
        return new MutantAnimal(
            "$type Bear",
            $description,
            $initialSize,
            TableMutantAnimals::BUILD_TYPE_SHORT,
            $startingBio,
            $this->bearBonuses($type),
            $this->bearFeatures($type)
        );
    }

    private function wildPredatoryBirds()
    {
        return new MutantAnimal(
            'Hawk/Falcon/Eagle',
            'All these predatory birds share curved beaks (for ripping prey), sharp talons, keen eyesight and the ability to dive directly onto their prey.',
            3,
            TableMutantAnimals::BUILD_TYPE_MEDIUM,
            70,
            [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 3, 'Mutant: Predatory Bird'),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, 2, 'Mutant: Predatory Bird'),
            ], [
                TableMutantAnimals::POWER_CATEGORY_HANDS => [
                    new MutantAnimalBonus('None', 0, false),
                    new MutantAnimalBonus('Partial', 5, false),
                    new MutantAnimalBonus('Full', 10, false),
                    new MutantAnimalBonus('Extra limbs with human hands', 20, false),
                ],
                TableMutantAnimals::POWER_CATEGORY_BIPED => [
                    new MutantAnimalBonus('Full', 0, false),
                ],
                TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
                TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                    new MutantAnimalBonus('Sharp, curved beak, eyes on the side of the head, feathers (with color and pattern of the original bird), long body with tail feathers, skinny legs with taloned feet.', 0, false),
                    new MutantAnimalBonus('Small beak, large eyes, feathered body, bird-like legs and feet.', 5, false),
                    new MutantAnimalBonus('Sharp features, very thin hair, powerful upper body, thin legs.', 10, false),
                ],
                TableMutantAnimals::POWER_CATEGORY_POWERS => [
                    new MutantAnimalBonus('Talons', 5, [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Talons on feet that do 1D8 damage', 'Mutant: Predatory Bird')]),
                    new MutantAnimalBonus('Talons', 10, [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Beak that does 1D10 damage', 'Mutant: Predatory Bird')]),
                ],
                TableMutantAnimals::POWER_CATEGORY_FLIGHT => [
                    new MutantAnimalBonus('Glide', 10, [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Ability to glide', 'Mutant: Predatory Bird')]),
                    new MutantAnimalBonus('Flight', 20, [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Ability to fly', 'Mutant: Predatory Bird')]),
                ],
                TableMutantAnimals::POWER_CATEGORY_POWERS => [
                    new MutantAnimalBonus('Enhanced Vision', 5, [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Enhanced Vision', 'Mutant: Predatory Bird')]),
                ],
            ]

        );
    }

    private function wildBirds()
    {
        return new MutantAnimal('Wild Bird', 'Wild birds are the common seed and insect eaters in North American forests. Included are Blue Jays, Cardinals, Robins and a host of other small birds.', 2, TableMutantAnimals::BUILD_TYPE_MEDIUM, 85, false, [
            TableMutantAnimals::POWER_CATEGORY_HANDS => [
                new MutantAnimalBonus('None', 0, false),
                new MutantAnimalBonus('Partial', 5, false),
                new MutantAnimalBonus('Full', 10, false),
                new MutantAnimalBonus('Extra limbs with human hands', 20, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_BIPED => [
                new MutantAnimalBonus('Full', 0, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('Full beaked head, full feathered plumage (color and pattern to match the original bird), skinny, scaly legs and clawed, bird-like feet.', 0, false),
                new MutantAnimalBonus('Prominent beak, feathers instead of hair, round body with thin legs.', 5, false),
                new MutantAnimalBonus('Large eyes and lips, small ears, very sparse hair, long thin legs, large feet.', 10, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_FLIGHT => [
                new MutantAnimalBonus('Glide', 10, [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Ability to glide', 'Mutant: Wild Bird')]),
                new MutantAnimalBonus('Flight', 20, [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Ability to fly', 'Mutant: Wild Bird')]),
            ],
        ]);
    }

    private function buffalo()
    {
        return new MutantAnimal('Buffalo', 'These huge grazing animals were virtually exterminated by hunters in the west.', 19, TableMutantAnimals::BUILD_TYPE_MEDIUM, 0, false, [
            TableMutantAnimals::POWER_CATEGORY_HANDS => [
                new MutantAnimalBonus('None', 0, false),
                new MutantAnimalBonus('Partial', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Two bony fingers and a thumb.', 'Mutant: Buffalo')),
                new MutantAnimalBonus('Full', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Two fingers and a thumb.', 'Mutant: Buffalo')),
            ],
            TableMutantAnimals::POWER_CATEGORY_BIPED => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('Huge head with small eyes on the sides, heavy black hair on neck and shoulders, small arms and legs, and a huge body.', 0, false),
                new MutantAnimalBonus('Very large head with small eyes and thick neck, large body with heavy upper body hair.', 5, false),
                new MutantAnimalBonus('Big head, well-developed shoulders, neck and arms, heavy body hair.', 10, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Horns', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Horns that do 1D8 damage', 'Mutant: Buffalo')),
                new MutantAnimalBonus('Advanced Hearing', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced hearing', 'Mutant: Buffalo')),
                new MutantAnimalBonus('Advanced Hearing', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 10, 'Mutant: Buffalo')),
            ],
        ]);
    }

    private function wildCanineBonuses($type)
    {
        return [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT, 4, "Mutant: Wild Canine ($type)"),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE, 2, "Mutant: Wild Canine ($type)"),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 2, "Mutant: Wild Canine ($type)"),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, 2, "Mutant: Wild Canine ($type)"),
        ];
    }

    private function wildCaninePowers($type)
    {
        return [
            TableMutantAnimals::POWER_CATEGORY_HANDS => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_BIPED => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('Full snout, pointed ears on top of head, clawed feet and hands, long tail and heavy fur.', 0, false),
                new MutantAnimalBonus('Prominent snout, pointed ears, fur; powerful, squat build.', 5, false),
                new MutantAnimalBonus('Slightly pointed ears, large features, thick hair and beard, powerful build.', 10, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_NATURAL_TEETH => [
                new MutantAnimalBonus('Teeth', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Teeth deal damage of 1d8', "Mutant: Wild Canine ($type)")),
                new MutantAnimalBonus('Teeth', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Teeth deal damage of 2D6', "Mutant: Wild Canine ($type)")),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Claws', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Claws deal damage of 1D6', "Mutant: Wild Canine ($type)")),
                new MutantAnimalBonus('Advanced Smell', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced Smell', "Mutant: Wild Canine ($type)")),
            ],
        ];
    }

    private function domesticDog($type, $size)
    {
        $dogType = "Mutant: Domestic Dog ($type)";
        return new MutantAnimal("Domestic Dog: $type", 'Domestic dog', $size, TableMutantAnimals::BUILD_TYPE_MEDIUM, 60 - ($size > 5 ? (10 * ($size - 5)) : 0), $size <= 5 ? [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT, 2, $dogType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE, 1, $dogType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 1, $dogType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 1, $dogType),
        ] : [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT, 2, $dogType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 2, $dogType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 2, $dogType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 2, $dogType),
        ], [
            TableMutantAnimals::POWER_CATEGORY_HANDS => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_BIPED => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_SPEECH => [
                new MutantAnimalBonus('More similar to a dog than a human.', 0, false),
                new MutantAnimalBonus('Hard to distinguish if dog or human.', 5, false),
                new MutantAnimalBonus('More similar to a human than a dog.', 10, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Teeth', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Teeth do 1D6 damage', $dogType)),
                new MutantAnimalBonus('Claws', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Claws do 1D4 damage', $dogType)),
                new MutantAnimalBonus('Advanced Smell', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced Smell', $dogType)),
            ],
        ]);
    }

    private function wildCanine($type, $size, $startingBioE)
    {
        return new MutantAnimal($type, 'Carnivores who hunt in highly organized packs. They are intelligent and very social.', $size, TableMutantAnimals::BUILD_TYPE_LONG, $startingBioE, $this->wildCanineBonuses($type), $this->wildCaninePowers($type));
    }

    public function deer()
    {
        return new MutantAnimal('Deer', 'Woodland grazing animal whose primary defense against predators is speed. There are a large variety of deer, all of which roughly the same characteristics.', 13, TableMutantAnimals::BUILD_TYPE_MEDIUM, 20, [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 1, 'Mutant: Deer'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 1, 'Mutant: Deer'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, 3, 'Mutant: Deer'),
        ], [
            TableMutantAnimals::POWER_CATEGORY_HANDS => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_BIPED => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('Triangular head with large ears at the upper comers, widely spaced eyes, thick neck, powerful body with long, thin arms.', 0, false),
                new MutantAnimalBonus('Muzzled head, large ears, thick body with thin arms and legs.', 5, false),
                new MutantAnimalBonus('Large, fluid eyes; large ears, thick neck, powerful build.', 10, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_NATURAL_HORN => [
                new MutantAnimalBonus('Small Antlers', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Small antlers do 1D6 damage', 'Mutant Deer')),
                new MutantAnimalBonus('Large Antlers', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Large antlers do 2D6 damage', 'Mutant Deer')),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Advanced Hearing', 5, [new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced Hearing', 'Mutant: Deer')]),
            ],
        ]);
    }

    private function elephant()
    {
        return new MutantAnimal('Elephant', 'This is the world\'s largest land animal. The elephant is used as a circus performer throughout the world. It is a useful worker with tremendous strength and a trunk that serves as a flexible (partial) human hand.', 20, TableMutantAnimals::BUILD_TYPE_SHORT, 0, [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 1, 'Mutant: Elephant'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, 3, 'Mutant: Elephant'),
        ], [
            TableMutantAnimals::POWER_CATEGORY_HANDS => [
                new MutantAnimalBonus('None', 0, false),
                new MutantAnimalBonus('Partial', 10, false),
                new MutantAnimalBonus('Full', 15, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_BIPED => [
                new MutantAnimalBonus('None', 0, false),
                new MutantAnimalBonus('Partial', 10, false),
                new MutantAnimalBonus('Full', 15, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_SPEECH => [
                new MutantAnimalBonus('None', 0, false),
                new MutantAnimalBonus('Partial', 10, false),
                new MutantAnimalBonus('Full', 15, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('Huge head with prominent lumps on top, small eyes. Huge floppy ears; loose, leathery skin with sparse hair; massive body, trunk-like arms and legs, skinny tail.', 0, false),
                new MutantAnimalBonus('Huge head with a nose that will hang below the chin; wrinkled, leathery skin that sags over most of the body; bald, powerful body and limbs.', 5, false),
                new MutantAnimalBonus('Large head with bone ridge over the eyes, very large nose, large ears, bald, prominent facial wrinkles, thick neck and body, powerful arms and legs', 10, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_NATURAL_WEAPONS => [
                new MutantAnimalBonus('Tusks', 10, [
                    new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Tusks that do 2D6 damage', 'Mutant: Animal')
                ]),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Prehensile Trunk', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Prehensile Trunk that can serve as an additional (partial) hand. This trunk will be long enough for the character to touch the ground without bending.', 'Mutant: Elephant')),
                new MutantAnimalBonus('Advanced Hearing', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced Hearing', 'Mutant: Elephant')),
                new MutantAnimalBonus('Thick Skin', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 20, 'Mutant: Elephant')),
            ],
        ]);
    }

    private function felines($type, $description, $size, $bioe)
    {
        $felineType = "Mutant: Feline ($type)";
        return new MutantAnimal("Feline ($type)", $description, $size, TableMutantAnimals::BUILD_TYPE_MEDIUM, $bioe, [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, $type === 'Tiger' ? 4 : 2, $felineType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 6, $felineType),
        ], [
            TableMutantAnimals::POWER_CATEGORY_HANDS => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_BIPED => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('Large, wide head with massive jaw, broad nose, wide-set eyes, and ears on top; thick fur (with original animal markings); long, lean body; long, furred tail; powerful arms and legs.', 0, false),
                new MutantAnimalBonus('Muzzled face, whiskers, thick fur; long, flexible body; short, furry tail; powerful arms and legs.', 5, false),
                new MutantAnimalBonus('Wide, flat nose; widely spaced eyes, powerful jaw; short, thick hair. lean, muscular build with large Hands and feet.', 10, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_NATURAL_CLAW => [
                new MutantAnimalBonus('Retractable Claws', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Retractable Claws deal 1D8 damage', $felineType)),
                new MutantAnimalBonus('Retractable Claws', 15, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Retractable Claws deal 2D6 damage', $felineType)),
            ],
            TableMutantAnimals::POWER_CATEGORY_NATURAL_TEETH => [
                new MutantAnimalBonus('Teeth', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Teeth do 1D8 damage', $felineType)),
                new MutantAnimalBonus('Teeth', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Teeth do 2D6 damage', $felineType)),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Advanced Hearing', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced Hearing', $felineType)),
                new MutantAnimalBonus('Nightvision (60ft)', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision (60ft)', $felineType)),
                new MutantAnimalBonus('Feline Swimming', 10, new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SKILL_SWIMMING, 60, $felineType)),
            ],
        ]);
    }

    private function mountainLion()
    {
        return new MutantAnimal('Mountain Lion', 'Found throughout North America, Mountain Lions have been called Cougars, Panthers, Pumas and other names. While smaller than lions and tigers, they are very agile and bring down deer and other prey much larger than themselves. A typical Mountain Lion will kill a deer every week.', 9, TableMutantAnimals::BUILD_TYPE_LONG, 40, [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 3, 'Mutant: Mountain Lion'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, 2, 'Mutant: Mountain Lion'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 2, 'Mutant: Mountain Lion'),
        ], [
            TableMutantAnimals::POWER_CATEGORY_HANDS => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_BIPED => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('Small head with large ears on top, chubby muzzle and large eyes, long fur, heavy thighs; long, furry tail; long, lean body.', 0, false),
                new MutantAnimalBonus('Large ears on top of head, large eyes, prominent whiskers, fur, small tail, large legs, clawed hands and feet.', 5, false),
                new MutantAnimalBonus('Large eyes and ears, broad nose, thick hair, slim, powerful build.', 10, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Nightvision (50ft)', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision (50ft)', 'Mutant: Mountain Lion')),
                new MutantAnimalBonus('Advanced Hearing', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced Hearing', 'Mutant: Mountain Lion')),
                new MutantAnimalBonus('Advanced Smell', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced Smell', 'Mutant: Mountain Lion')),
            ],
        ]);
    }

    public function domesticCat()
    {
        return new MutantAnimal('Domestic Cat', 'There are a wide variety of cat breeds, but all have roughly the same characteristics. Cat characters can have spotted, striped, persian or calico body markings.', 3, TableMutantAnimals::BUILD_TYPE_MEDIUM, 70, [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE, 2, 'Mutant: Domestic Cat'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 3, 'Mutant: Domestic Cat'),
        ], [
            TableMutantAnimals::POWER_CATEGORY_HANDS => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_BIPED => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('Cat-like head with ears on top and large slit eyes; long fur, heavy thighs, long furry tail.', 0, false),
                new MutantAnimalBonus('Large ears on top of head; large, slit eyes, prominent whiskers, fur, small tail, large thighs, narrow shoulders, slim build.', 5, false),
                new MutantAnimalBonus('Full; large eyes and ears, thick hair, large thighs, narrow shoulders, slim build.', 10, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_NATURAL_CLAW => [
                new MutantAnimalBonus('Retractable Claws', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Retractable claws do 1D8 damage', 'Mutant: Domestic Cat')),
                new MutantAnimalBonus('Retractable Claws', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Retractable claws do 2D6 damage', 'Mutant: Domestic Cat')),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Teeth', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Teeth do 1D8 damage', 'Mutant: Domestic Cat')),
                new MutantAnimalBonus('Nightvision (50ft)', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision (50ft)', 'Mutant: Domestic Cat')),
            ],
        ]);
    }

    private function frog()
    {
        return new MutantAnimal('Frog', 'There are hundreds of different kinds of frogs in North America alone. Some are purely aquatic, but others have adapted to living on the ground or in trees. Most are insect eaters who rely on their sticky tongue.', 2, TableMutantAnimals::BUILD_TYPE_MEDIUM, 80, [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 1, 'Mutant: Frog'),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, 2, 'Mutant: Frog'),
        ], [
            TableMutantAnimals::POWER_CATEGORY_HANDS => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_BIPED => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('Huge, bulbous eyes at the top of the head; short, thick neck; naked, greenish, smooth skin; round body, long, thin arms and legs; three long fingers on each limb.', 0, false),
                new MutantAnimalBonus('Bulging eyes at the top of the head, wide mouth, smooth skin, round body with long, thin arms and legs.', 0, false),
                new MutantAnimalBonus('Bulging eyes, bald, smooth skin, flat nose and ears, short neck, powerful body with skinny arms and legs, three fingered hands and three toed feet.', 0, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Nightvision (25ft)', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Nightvision (25ft)', 'Mutant: Frog')),
                new MutantAnimalBonus('Leaping', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Leaping ability that doubles normal distance for jumps and leaps', 'Mutant: Frog')),
                new MutantAnimalBonus('Frog Swimming', 15, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_SWIMMING_ADVANCED, 80, 'Mutant: Frog')),
                new MutantAnimalBonus('Hold Breath', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Hold Breath', 'Mutant: Frog')),
            ]
        ]);
    }

    private function rodent($type, $size, $startingBio)
    {
        $mutantType = "Mutant: Rodent ($type)";
        return new MutantAnimal($mutantType, 'Good scavengers and spend a lot of time underground.', $size, TableMutantAnimals::BUILD_TYPE_MEDIUM, $startingBio, [
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_INTELLIGENCE_QUOTIENT, 2, $mutantType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE, 1, $mutantType),
            new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, 1, $mutantType),
        ], [
            TableMutantAnimals::POWER_CATEGORY_HANDS => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_BIPED => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_SPEECH => $this->standardProgression(),
            TableMutantAnimals::POWER_CATEGORY_LOOKS => [
                new MutantAnimalBonus('Muzzled head with pointed nose, widely spaced eyes, round ears on top of head, thick fur; long, naked tail; thick body with short arms and legs.', 0, false),
                new MutantAnimalBonus('Slightly muzzled head, ears on top of head, thick neck and body with short tail.', 5, false),
                new MutantAnimalBonus('Sharp nose and protruding ears, thick hair, rounded body.', 10, false),
            ],
            TableMutantAnimals::POWER_CATEGORY_POWERS => [
                new MutantAnimalBonus('Claws', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Claws do 1D6 damage', $mutantType)),
                new MutantAnimalBonus('Teeth', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Teeth do 1D4 damage', $mutantType)),
                new MutantAnimalBonus('Digging', 10, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Digging', $mutantType)),
                new MutantAnimalBonus('Advanced Hearing', 5, new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Advanced Hearing', $mutantType)),
            ],
        ]);
    }

    /**
     * gives an array of all the possible animals
     * @return MutantAnimal
     */
    public function pickAnimal()
    {
        return $this->engine->tableRoller->rollTable('Mutant animal type', [
            new TableEntry(25, $this->alligator()),


            new TableEntry(31, $this->bear('Black', 'Smallest of the bears are black bears found all over North America', 14, 5)),
            new TableEntry(37, $this->bear('Grizzly', 'Grizzly bears are larger than black bears', 16, 0)),
            new TableEntry(43, $this->bear('Brown', 'Brown bears of alaska (sometimes called Kodiak) are larger than grizzly bears', 17, 0)),
            new TableEntry(50, $this->bear('Polar', 'Polar bears are the largest of the bears', 18, 0)),

            new TableEntry(62, $this->wildPredatoryBirds()),
            new TableEntry(75, $this->wildBirds()),

            new TableEntry(100, $this->buffalo()),

            new TableEntry(125, $this->wildCanine('Coyote', 5, 55)),
            new TableEntry(150, $this->wildCanine('Wolf', 6, 50)),

            new TableEntry(151, $this->domesticDog('Afghan Hound', 6)),
            new TableEntry(152, $this->domesticDog('Beagle', 5)),
            new TableEntry(153, $this->domesticDog('Bloodhound', 5)),
            new TableEntry(154, $this->domesticDog('Dachshund', 3)),
            new TableEntry(155, $this->domesticDog('Elkhound', 6)),
            new TableEntry(156, $this->domesticDog('German Shepherd', 6)),
            new TableEntry(157, $this->domesticDog('Greyhound', 5)),
            new TableEntry(158, $this->domesticDog('Spaniel', 4)),
            new TableEntry(159, $this->domesticDog('Cocker Spaniel', 4)),
            new TableEntry(160, $this->domesticDog('Terrier', 4)),
            new TableEntry(161, $this->domesticDog('Terrier', 4)),
            new TableEntry(162, $this->domesticDog('Bulldog', 5)),
            new TableEntry(163, $this->domesticDog('Poodle', 4)),
            new TableEntry(164, $this->domesticDog('Collie', 5)),
            new TableEntry(165, $this->domesticDog('Doberman', 6)),
            new TableEntry(166, $this->domesticDog('Great Dane', 7)),
            new TableEntry(167, $this->domesticDog('Mastiff', 6)),
            new TableEntry(168, $this->domesticDog('Husky', 5)),
            new TableEntry(169, $this->domesticDog('St. Bernard', 8)),
            new TableEntry(170, $this->domesticDog('Chihuahua', 2)),
            new TableEntry(171, $this->domesticDog('Pekingese', 2)),
            new TableEntry(175, $this->domesticDog('Mongrel', 5)),

            new TableEntry(200, $this->deer()),

            new TableEntry(225, $this->elephant()),

            new TableEntry(230, $this->felines('Jaguar', 'American Jaguars and African Leopards are roughly the same size and have the same characteristics.', 12, 20)),
            new TableEntry(235, $this->felines('Lion', 'The second largest felines are Lions who are social hunters.', 14, 10)),
            new TableEntry(240, $this->felines('Tiger', 'Tigers are the largest and are solitary hunters.', 15, 5)),
            new TableEntry(245, $this->mountainLion()),
            new TableEntry(250, $this->domesticCat()),

            new TableEntry(275, $this->frog()),

            new TableEntry(281, $this->rodent('Mouse', 1, 80)),
            new TableEntry(287, $this->rodent('Hamster', 1, 80)),
            new TableEntry(293, $this->rodent('Rat', 2, 75)),
            new TableEntry(300, $this->rodent('Guinea Pig', 2, 75)),
        ]);
    }
}
