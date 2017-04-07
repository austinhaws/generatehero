<?php

namespace Heroes\tables;

use Heroes\hero\Spell;

class TableSpells
{
    static public function summonCircles()
    {
        return [
            new Spell(
                'Summoning Circle',
                '',
                '',
                '',
                'Summoning circles are the most dangerous because they can mystically teleport other-dimensional creatures into our world. Most of the other-dimensional monstrosities possess magic powers and have no regard for human life. The lack of concern, and often hatred, for humanity makes them the willing pawns of evil schemes or the demonic master. Within moments (1D6 minutes) a creature of magic will appear inside the open-V area of the circle. These creatures are almost always evil, hostile beings with a hatred for humankind. It\'s only the circle\'s area of protection that keeps the mage safe from the creature\'s ire. The circle maker is able 1o talk, question and negotiate with the entity, although there is no telling how cooperative the thing may be. This foul-hearted fiend is apt to agree to assist in any plan that is of extremely evil or destructive. Good causes w1ll only gain its disgust (it will not help).'
            ),
        ];
    }

    static public function powerCircles()
    {
        return [
            new Spell(
                'Force: Power Circle',
                'Circle area only',
                '15 melees per level of the circle maker',
                'None',
                'Creates an impenetrable enclosure of force that encompasses the Circle\'s entire radius (or all circles in a power matrix). The force can sustain an infinite amount of damage and prevents stenches, clouds, etc. from penetrating it. Psionic attacks, charms, and mesmerism are quite effective means of countering the force field. A dispel mag1c barriers will temporarily negate the circle of force, but the circle is +3 to save against that spell and will regenerate within six melees. The circle can be reactivated at any time by the invocation of the power words. If the circle of force has been previously activated for its entire duration it can not be reactivated for a two hour interval Components: Mystic symbol of directed power, the circle can be drawn in any substance, likewise the symbols. However, a white dove must be sacrificed while the power words arc recited. Power Words: Ya-ahk-met yin Ya-ahk-met'
            ),
            new Spell(
                'Invisibility: Power Circle',
                'The objects within the circle.',
                'Permanent; 10 minutes per level of circle maker',
                'Standard',
                'This circle will turn the circle maker and anyone entering the circle invisible for 10 minutes per level of the circle maker. This is an enchantment placed upon any who enter the circle and, as such, the invisibility can not be cancelled at will. The invisible person will remain so until the enchantment wears off. The circle of invisibility remains constantly active until the toad skeleton is removed. Components: Mystic symbol of directed power. The circle is drawn with powdered bones of toads, the symbols in clear wax. The complete and unbroken skeleton of a toad must also be placed within the circle\'s radius, but turns invisible once the circle is activated. Only the circle and symbols remain visible. Power Words: Acba yin Cherunbot-kyn'
            ),
            new Spell(
                'Knowledge: Power Circle',
                'Circle Radius',
                '15 melees per level of the circle maker',
                'None',
                'The circle of knowledge instills a temporary aura around the circle maker and/or anyone in the circle. Burning the tongue of an owl will provide the following enchanted abilities: + 10% on all skills and understand and speak all languages. Components; The mystic symbol of directed power. The circle is painted in yellow, the symbols in blue. A small brazier sits in the middle with hot coals to burn the tongue. It is the burning of the tongues and the invocation of the power words that activate the circle. Power Words: Lictalon yin Kym-nark-mar-Agu'
            ),

            new Spell(
                'Pain: Power Circle',
                'Special',
                '6 melees per level of the circle maker',
                'Save vs circle magic each melee',
                'Only those whose true names are inscribed in the circle are affected by a circle of pain. The circle maker first draws the circle then fashions a straw or cloth doll (human shape) symbolizing the victim. The hair, or nail clippings, or a personal article of the intended victim must be tied to the doll. Pins, needles, or nails are then driven through the effigy while the power words are chanted. The victim will receive sharp, stabbing pains corresponding to where the pins are driven in the doll. This circle is devised to inflict pain and suffering, not death. Consequently, only 1D4 hit points of damage are inflicted per melee. If a successful save is made there is only a slight twinge of pain and no damage is done. The loss of hit points can not go below 10. Components: Mystic symbol of force. The circle is drawn with the bodies of mangled spiders, the symbols are painted in black and the intended victim bound in the circle\'s center. Power Words: Netosa ym Tarn-kin-toe'
            ),
            new Spell(
                'Power: Power Circle',
                'The people within the circle, and projected power',
                'Active until circle maker leaves or cancels it',
                'Standard',
                'This circle confers great primal magic power to the people within it. It taps into and focuses magic energy upon the circle area, endowing those within it with unlimited power. The circle area seems to glow and undulate with light and color as if it were a cosmic prism. The rush of energy envelops the circle\'s occupants. Occupants are then + 5 on all savings throws, + 2 spell strength, bio-regeneration (1D6 points per melee), and enables them to create cast the following (doing 1D6 points per level of circle maker): ball of flame, call lightning, wall of fire. It also creates the following effects: (duration: as long as the circle remains active), charm, charismatic aura, weightlessness (area affect 20ft beyond the circle), mesmerism (area affect 20ft beyond the circle), animate/control dead (1D6 dead per level of the circle maker), control the beasts (1D6 animals per level of the circle maker), and metamorphosis (affects only those within the circle). The circle is activated and reactivated by invoking the proper power words and by wearing a helm fashioned from the skull of a tiger. Components: Mystic symbol of directed power; a tiger helm must be inscribed with the symbol of force. The circle and symbols must be drawn using a bone from a tiger. Silver must be used to draw the circle. Power Words: Xy yin Lo-kum-yin Kym-nark-mark'
            ),
            new Spell(
                'Power Leech: Power Circle',
                '30ft radius per level of the circle maker',
                'Active only while circle maker remains in the circle',
                '-2 to save vs circle magic',
                'The power leech drains all mystic energies within its radius of influence. Magic spells, including illusionary magic; other circles and nonphysical super abilities (excluding psionics), are all reduced to half their normal strength, power, and duration. Thus, a mage of sixth level experience will cast spells as if he were only third level. The power leech also absorbs all energy that is directed at it. If, for example, a lightning bolt, f1rc ball or laser were shot at the circle it will be completely absorbed, doing no damage to the circle or its occupants. Components: The mystic symbol of directed power must be inscribed in the circle while a helm fashioned from the skull of a tiger is inscribed with the symbol of force. The symbols arc painted in brown. The circle is created from the soft, mangled bodies of leeches; a light (candle, lantern, fire, etc.), is placed in the center, and two live leeches are applied to each arm of the circle maker. Should a leech drop off, the circle is canceled. The power leech circle can be reactivated, even if the leech bodies composing the circle have dried, as long as the helm is worn and the power words invoked. Power Words: Ya-ank-met yin Lictalon'
            ),
        ];
    }

    static public function protectionCircles()
    {
        return [
            new Spell(
                'Protection from Demonic Creatures (other-dimensional)',
                '',
                '',
                '',
                'Demonic beings can not enter the circle. Those within the circle are + 3 to save against any attack by demonic forces. Components: Drawn with holy water. Power Words: Acba yin Pein'
            ),
            new Spell(
                'Protection from Elemental Forces',
                '',
                '',
                '',
                'All elemental forces do half damage to those within the circie.  Components: Emeralds, onyx, topaz, sapphire; circle can be drawn in any substance. Power Words: Acba Lo-kum yin Tao-bo'
            ),
            new Spell(
                'Protection from Magic (Simple)',
                '',
                '',
                '',
                'Those within the circle arc + 2 to save against all magic attacks. Components: Can be drawn in any substance. Power Words: Kym-nark-mar yin acba'
            ),
            new Spell(
                'Protection from Magic (superior)',
                '',
                '',
                'g',
                'Those within the circle are +6 to save against all magic attacks. Components: Must be sealed with the blood of the circle maker. Power Words: Acba yin kym-nark-mar yin acba'
            ),
            new Spell(
                'Protection from the Undead',
                '',
                '',
                '',
                'Undead can not enter the circle.  Components: Silver cross, garlic clove; circle can be drawn in any substance.  Power Words: Pein yin Erva'
            ),
        ];
    }

    static public function illusionarySpells()
    {
        return [
            new Spell(
                'Age',
                '90ft',
                '3 melees per level of the spell caster.',
                'Standard',
                'Accelerates a person\'s or animal\'s aging process instantly, transforming them to the limit of their natural age. Aliens and other races which may age much slower than humans are also affected. Only supernatural creatures, such as demons, are not affected by this spell.'
            ),
            new Spell(
                'Blinding Flash',
                '10ft radius',
                'Instant',
                'Standard',
                'This spell creates a sudden burst of intense white light, temporarily blinding everyone in its ten foot radius for 1D4 melees.'
            ),
            new Spell(
                'Charismatic Aura',
                '60ft radius',
                '6 melees per level of spell caster.',
                'Standard',
                'Instantly enhances that person\'s physical beauty by eight. Affects everybody in a 60 foot radius, emanating from the person with the charismatic aura.'
            ),
            new Spell(
                'Chameleon',
                'Self or others by touch',
                '18 melees per level of spell caster',
                'None',
                'Alter the color and patterns of clothes and physical body, enabling to blend into the surrounding environment. Movement destroys the effectiveness of this magic.'
            ),
            new Spell(
                'Cloud Of Smoke',
                '90ft',
                '4 melees per level of spell caster',
                'None',
                'Creates a cloud of dense, black smoke (30ft X 30ft x 30ft maximum size). Victims caught tn the cloud will be unable to see anything beyond the cloud  and the impaired vision allows them to see no more than 3ft in the cloud.'
            ),
            new Spell(
                'Darkness',
                '5ft radius per level of the spell caster',
                '10 melees per level of spell caster.',
                'None',
                'This is an unnatural darkness which can not be dispelled by normal flames. Nightvision is cut to half.'
            ),
            new Spell(
                'Death Trance',
                'Self',
                '10 melees per level of spell caster',
                'None',
                'Slows the spell caster\'s metabolism so low that it creates the appearance of death. While in the trance, the spell caster is helpless. He is only vaguely aware of what is happening around him.'
            ),
            new Spell(
                'Fingers of the Wind',
                '90ft',
                '3 melees per level of spell caster',
                'None',
                'Conjure a wind and manipulate it to touch, tap,  bump, or press against a penon or object. It can also put out candles,  slam doors shut, or move or knock over small items weighing less than 10 pounds.'
            ),
            new Spell(
                'Float in Air',
                'Self or others within 30ft',
                '10 melees per level of spell caster',
                'None',
                'Air currents which hold a penon or object aloft,  hovering about one foot above the ground. It can be used to slow someone\'s descent from a fall or used to float on top of water.'
            ),
            new Spell(
                'Fool\'s Gold',
                '5ft',
                '20 melees per level of spell caster',
                'Standard',
                'Cause any object to appear to be made of gold. Close examination, by those who can recognize precious metals, see that it is not gold.'
            ),
            new Spell(
                'Heavy Breathing',
                '60ft',
                '5 melees per level of the spell caster',
                'Standard',
                'Conjure a mysterious, frightful sound of heavy, labored breathing as if something invisible was lurking about.  The breathing can be heard in a six foot radius.'
            ),
            new Spell(
                'Mask of Deceit',
                'Self or other',
                '20 melees per level of the spell caster',
                'Save vs Magic at -5',
                'description'
            ),
            new Spell(
                'Magic Pigeon',
                'Immediate Area',
                '2 months per level of spell caster',
                'None',
                'Create a mystic facsimile of a pigeon able to deliver a spoken (30 words or less) or written message to anyone, anyplace in this world (in the same dimension). Normal weapons can not harm or capture the pigeon, but magic spells of entrapment can capture it. Only a dispel magic spell can destroy it.'
            ),
            new Spell(
                'Multiple Image',
                'Self or 30ft',
                '5 melees per level of spell caster',
                'Save vs Magic at -6',
                'Creates 1D6 identical images which mimic the spell caster\'s every movement exactly. If the false image is touched, pierced, or struck, that particular one will disappear.'
            ),
            new Spell(
                'Mystic Illusion',
                '90ft',
                '2 melees per level of spell caster.',
                'Save vs Illusion at 14',
                'Conjures forth an image or illusion of anything the spell caster would like. Anyone not making his savings throw will believe the image to be true and respond accordingly. Image can be of anything as large as 20 by 20 by 20ft. it has no audio, only visual effects. The illusion is immediately dispelled when touched by metal.'
            ),
            new Spell(
                'See the Invisible',
                'Self or Others',
                '10 melees per level of spell caster',
                'None',
                'Enables a person to see any invisible object or being clearly and distinctly within his line of vision for up to 60ft.'
            ),
            new Spell(
                'Sense Evil',
                'Self',
                '1 melee per level of spell caster',
                'None',
                'Indicate to the spell caster whether any person, creature, object, or place within a 30ft radius is evil. The impression is immediate, but somewhat vague, since it simply indicates the presence of evil and not actual alignments or location.'
            ),
            new Spell(
                'Shadow Walk',
                'Self or other',
                '2 melees per level of spell caster',
                'None',
                'Step in to shadows, becoming totally invisible even to a See the Invisible spell (a psionic presence sense will detect the presence of someone in the shadow). While in the shadow the spell caster can not be seen or harmed by weapons or most magic (only charms and sleep are effective; but all psionic attacks are still applicable). The person in the shadow can talk and cast spells, but can not use a physical attack unless he steps out from the protective shadows.'
            ),
            new Spell(
                'Spontaneous Combustion',
                '40ft',
                'Instant',
                'None',
                'This spell causes combustible items to smolder and burn. The spell\'s initial effect is to instantly create the spark to start combustibles burning. It takes 1D6 melees for a fire to really begin to burn. The success ratio for each attempt at spontaneous combustion is 75%.'
            ),
            new Spell(
                'Swirling Lights',
                '10ft radius',
                '4 melees per level of spell caster',
                'Standard',
                'Conjures forth a dazzling display of swirling, flickering lights which stun/bedazzle all who see them. If attacked/struck, the victim will be roused from the enchantment but will move at one-half speed and have half as many attacks as normal as long as the swirling lights spell is in effect.'
            ),
            new Spell(
                'Sword to Snakes',
                '60ft',
                '6 melees per level of spell caster',
                'None',
                'Not only does this spell transform swords (large or small, including guns, daggers, and other small, hand held, non-energy weapons) to snakes, but the snakes are extremely hostile and biting whoever holds them, doing 1D4 damage each bite (one attack per melee). The snakes will not change back into swords until the spell elapses.'
            ),
            new Spell(
                'Tongues',
                'Self or Others',
                '10 melees per level of spell caster',
                'None',
                'Understand and speak all languages limited to the spoken word.'
            ),
            new Spell(
                'Turn Self to Mist',
                'Self',
                '5 melees per level of the spell caster',
                'None',
                'While in this form the spell caster can not speak, cast spells, or carry anything, but he can hear and think. Only the physical body is affected, not any possessions, weapons, or clothes. No weapons can hit or cut a mist and pass harmlessly through.'
            ),
            new Spell(
                'Water to Wine',
                '12ft',
                'Instant/permanent',
                'None',
                'Change ordinary fresh water into wine, affecting ten gallons per level of the spell caster\'s experience. Tbe wine is of fair to average quality, with the quality increasing by 5% per each level of his experience.'
            ),
            new Spell(
                'Wisps of Confusion',
                '90ft',
                '5 melees per level of the spell caster',
                'Standard',
                'Wisps cause up to 8 people/creatures to become confused and disoriented.'
            ),
        ];
    }

    static public function magicSpells()
    {
        return [
            new Spell(
                'Anti-Magic Cloud',
                '1OOft (30.5m) radius per level of the spell caster',
                '20 melees per level of the spell caster',
                'Only an 18 to 20 saves against the cloud; on success, magic reduced to half strength.',
                'Creates an ominous, dark grey-brown cloud large enough to hang over an entire town. It can not be dispelled magically or by manipulating elemental/atmospheric conditions. The cloud negates all magic!'
            ),
            new Spell(
                'Armor of Ithan',
                'Self or Touched Other',
                '4 melees per level of the spell caster',
                'None',
                'Creates an invisible, weightless, noiseless, full suit of mystic armor instantly upon the spell caster. Armor Rating (AR) of 18; SDC of 200; fire, lightning, and cold do one-half damage.'
            ),
            new Spell(
                'Blind',
                '90ft',
                '5 melees per level of spell caster',
                'Standard',
                'Temporarily blind anyone it is cast upon, but can be directed against only one person at a time.'
            ),
            new Spell(
                'Breathe Without Air',
                'Self or Others by touch',
                '10 melees per level of the spell caster',
                'None',
                'Function totally without air. '
            ),
            new Spell(
                'Call Lightning',
                '300ft',
                'Instant',
                'None',
                'The lightning bolt shoots down from the sky, hitting the desired target. The lightning bolt does one 6 sided die of damage per level of spell caster.'
            ),
            new Spell(
                'Chameleon',
                '18 Self or Others by Touch',
                '18 melees per level of spell caster',
                'None',
                'Alter the color and pattern of clothes and physical body, enabling to blend into the surrounding environment. Movement lowers the effectiveness of this magic.'
            ),
            new Spell(
                'Carpet of Adhesion',
                '30ft per level of the spell caster',
                '10 melees per level of spell caster',
                'Save vs Magic: pull free in 2d6 melees',
                'Create a sticky carpet, up to 10ft wide by 20ft long, that will adhere firmly to anyone who touches it. The spell caster can create this super flypaper up to 90ft away.'
            ),
            new Spell(
                'Decipher Magic',
                'Self',
                '10 melees per level of spell caster',
                'None',
                'Read (decipher) any magic book, scroll, inscription, text, rune or symbol.'
            ),
            new Spell(
                'Dimensional Teleport',
                'Another dimension',
                'Instant',
                'None',
                'Transports the spell caster, and a maximum of 4000 pounds (1814kg), into another dimension. The spell caster and fellow travelers wlll appear in any location known to the person casting the spell. If no locations are known the location will be completely random. The success ratio of dimensional teleponation is 10% per level of the spell caster.'
            ),
            new Spell(
                'Diminish Others',
                '100ft (30.5m)',
                '10 melees per level of spell caster',
                'Standard',
                'This spell will affect any living creature; it will not affect devils, demons, elementals, golems, nor skeletons. This spell will reduce any one target/person to six inches in height, so long as that person is within the spell caster\'s line of vision and within range.'
            ),
            new Spell(
                'Dispel Magic Barriers',
                '100ft (30.5m)',
                'Instant',
                'The magic spell being attacked automatically gets
a standard savings throw (12) as if it were a person.',
                'Negates/dispels all magic barriers of any kind.'
            ),
            new Spell(
                'Exorcism',
                '60ft radius',
                'Instant',
                'None',
                '60% chance of successfully Cxorcising/repelling supernatural creatures. The exorcised being(s) will not return to the place it was exorcised from for 1-6 days. This spell affects 2-12 beings per level of the spell caster.'
            ),
            new Spell(
                'Expel Demons and Devils',
                '15ft radius (4.6m)',
                '15 melees per level of the spell caster',
                'Lesser demons must roll an 18 or higher to save vs spell magic; greater demons/devils only have to roll the standard 12 or higher to save.',
                'Repel all demons and devils, forcing them to leave the area and not return for 1D4 days.'
            ),
            new Spell(
                'Extinguish Fire',
                '20ft per each level or the spell caster',
                '4 melees per level of the spell caster/permanent',
                'None',
                'This spell will permanently extinguish any fires within the area of effect. Does not work on magic fires.'
            ),
            new Spell(
                'Eyes of the Wolf',
                'Self or other',
                '20 melees per level of spell caster',
                'None',
                'Nightvision - 60ft; See the invisible- 75%; Identify plants/fruits - 70%; Identify tracks - 85%; Track- 50%; Recognize poison - 65%'
            ),
            new Spell(
                'Fire Ball',
                '90ft',
                'Instant',
                'None except dodge, but the victim must know the
attack is coming and must roll an 18 or higher',
                'Creates a large fire ball which hurls at its target at an awesome speed, inflicting 1D6 points of damage per each level of the spell caster.'
            ),
            new Spell(
                'Fly as the Eagle',
                'Self or others up to 100ft (30.5m) away',
                '20 minutes per level of the spell caster',
                'None',
                'The power of flight is bestowed upon the spell caster or person it is cast upon. Maximum Speed: 50mph. Bonuses while in flight: +1 to parry, +2 to dodge and +2 to damage on a diving attack.'
            ),
            new Spell(
                'Globe of Daylight',
                'Radius of one foot per level of the spell caster',
                '10 melees per level of the spell caster',
                'None',
                'Creates a small sphere or globe of true daylight. This light is bright enough to light up a twelve foot radius per level of the spell caster. The spell caster can mentally move the globe along with him or send it up to thirty feet away.'
            ),
            new Spell(
                'Globe of Silence',
                '90ft',
                '6 melees per level of caster',
                'None',
                'Creates an invisible, 10ft radius globe which stops all sound. The globe can be fixed in a stationary area or mentally moved and manipulated by the spell caster.'
            ),
            new Spell(
                'Impenetrable Wall of Force',
                '100ft (30.5m)',
                '5 melees per level of the spell caster',
                'None',
                'Creates a shimmering wall of light that no creature, weapon, or object may penetrate. The wall of force can measure up to 20 x 20 feet per level of experience. The wall can be cast up to 100ft away.'
            ),
            new Spell(
                'Invisibility (self)',
                'Self',
                '15 melees per level of the spell caster',
                'None',
                'The spell caster and anything he was wearing or carrying are turned completely invisible. Any object picked up after becoming invisible remains visible.'
            ),
            new Spell(
                'Levitate',
                '60ft (18.3m)',
                '8 melees per level of spell caster',
                'None',
                'This spell enables the spell caster to raise himself or others into the air. The spell weaver can raise an object or person 30ft per level of his experience. Weight limitation is 350lbs per level of the spell caster.'
            ),
            new Spell(
                'Magic Net',
                '60ft (18. 3m)',
                '2 melees per level of the spell caster',
                'Dodge being snared by rolling a 16 or higher',
                'This spell create a net composed of magic fibers which will snare 1D6 human sized victims within a 10ft area. Normal weapons can not cut through the net; only weapons of superior quality, magic weapons, energy bolts or magic can effect this net.'
            ),
            new Spell(
                'Mesmerism',
                '6ft (1.8m)',
                '5 melees per level of spell caster',
                'Standard',
                'Enables the spell caster to induce simple hypnotic suggestions upon any intelligent being.'
            ),
            new Spell(
                'Mute',
                '30ft',
                '20 melees per level of spell caster',
                'Standard',
                'Temporarily affects the voice box and vocal cords, preventing any voice or sounds to be uttered.'
            ),
            new Spell(
                'Mystic Alarm',
                '12ft (one object)',
                'One year per level of the spell caster',
                'None',
                'Invisible ward-like symobls appear on any one object. If this object is touched/disturbed in any way, an instant, silent alarm will buzz in the spell caster\'s head. Once disturbed, the alarms disappear. The mystic alarm has a limited spell life of one year per level of spell caster.'
            ),
            new Spell(
                'Mystic Portal',
                '20ft (6.1m); 10ft wide by 20ft tall portal/opening',
                '4 melees per level of the spell caster',
                'None',
                'Creates a dimensional rift in the fabric of space allowing the spell caster to use it in the following ways: Pass through soUd walls. The portal can create a 12ft (3.6m) deep passage per each level of the spell caster in any substance. Teleportation: Teleports someone to another location instantly, as well as flawlessly. Range: 300 miles. Dimensional gateway: The portal can be used to get to another dimension  or plane of existence. The greatest limitation is that the spell caster must be familiar with the other dimension by having actually been there at least once.'
            ),
            new Spell(
                'Mystic Shield',
                'Self or to protect others up to 100ft (30.5m) away',
                'Until destroyed, dispelled or willed away by the spell caster.',
                'None',
                'A magic shield or enclosure can be created instantly to protect the spell caster and up to six normal size people. The shield is effective against all manner of physical attack, from energy bolts to an explosion. The shield can be molded to appear as a semi-transparent, floating disc, wall, dome or bubble. SDC: 120 per level of the spell caster.'
            ),
            new Spell(
                'Negate Magic',
                '100ft (30.5m)',
                'Instant',
                'Special',
                'This spell negates only spell magic and is useless against circles,  illusions (other than spells), psionics, magic weapons, powders, and potions. Roll contest of magic users.'
            ),
            new Spell(
                'Paralysis Bolt',
                '30ft (9m) per level of experience',
                'Instant',
                'Standard',
                'This mystic energy bolt short circuits the victim\'s motor parts of the brain, rendering him totally paralyzed. The victim can not move or speak, but can breathe, hear, and think. Paralysis lasts for 6 melees per level of spell caster. The bolt hits automatically, leaping from the spell caster\'s hand or eye in a flash. Only a dodge of 19 or 20 can evade the mystic bolt (parry docs not apply) and a mystic shield or force field can block. Does not affect robots or bionics.'
            ),
            new Spell(
                'Reduce Self (6 Inches)',
                'Self',
                '10 melees per level of spell caster',
                'None',
                'This spell instantly shrinks the spell caster, his clothes and possessions to six inches tall. Note that reduced weapons do virtually no damage.  Weapons that normally inflict 6D6, or more, damage do a mere one point of damage. All others just sting for a moment.'
            ),
            new Spell(
                'Resist Fire',
                'Self or Others',
                '20 melees per level of spell caster',
                'None',
                'Heat has no ill effect and fire, normal  and mystic, does half damage. The spell can be cast up to 60ft.'
            ),
            new Spell(
                'Restoration',
                '6ft (1.8m)',
                'One melee/Permanent',
                'None',
                'Restore or regenerate a missing limb, such as an arm or leg or restore someone back to complete health. Permanently drains the spell caster of one PE point each time it is cast.'
            ),
            new Spell(
                'Sanctuary',
                '50ft radius per level of spell caster',
                '1D4 years per level of spell caster',
                'None',
                'Prevents all acts of aggression or hostility within its radius. Any creature that attempts to attack or harm any other creature within its radius is instantly struck down, becoming temporarily paralyzed or rendered unconscious. Only the spell caster of the sanctuary is not subject to its effects. The spell can only be cast in the mage\'s home or secret domicile.'
            ),
            new Spell(
                'See the Invisible',
                'Self or Others',
                '10 melees per level of spell caster',
                'None',
                'Enables a person to see any invisible object or being clearly and distinctly within his line of vision for up to 60ft.'
            ),
            new Spell(
                'Shadow Beast',
                'Immediate',
                'duration',
                'None',
                'Summons a creature not of this world to do the bidding of the spell caster. Shadow beasts are large, vicious predators of some other, strange world. They stand 9 to 12ft tall, with sharp claws and wicked fangs. Deadliest of all is their ability to completely merge into the smallest shadow, becoming completely invisible. While hidden in shadows they are undetectable, even by a See the Invisible spell. There is a 15% chance that the shadow beast will not return to its own dimension and will no longer obey the spell caster who summoned it. If this happens, it will remain in our world wreaking havoc and killing innocent people for food and pleasure. Likewise, it will kill any who try to send it back.
'
            ),
            new Spell(
                'Sphere of Invisibility',
                '15ft radius',
                '15 melees per level of spell caster',
                'None',
                'Create a sphere or bubble of invisibility in which everyone within the radius is invisible. The spell caster can alter the radius up to the maximum of fifteen feet. He can also mentally move the sphere, or place it in a stationary area, or cast it around something up to 30 feet away.'
            ),
            new Spell(
                'Speed or the Snail',
                '60ft',
                '2 melees per level of the spell caster',
                'Standard',
                'This spell reduces the physical prowess, speed, and mobility of its victims to one-third their normal ability. Speed, attacks per melee, dodge, and parry are all reduced to one-third. Spell casting is not reduced. This spell can be cast upon 1D6 persons up to 60ft away (18.3m), but within the spell caster\'s line of vision.'
            ),
            new Spell(
                'The Sorcerer\'s Seal',
                '10ft',
                'Conditional',
                'None',
                'The sorcerer\'s seal can permanently seal/lock a door, chamber, box, compartment, etc. Once the seal is cast, no amount of brute strength, beating, or assault by weapons will break the seal nor will fire, lightning, cold, energy weapons, or magic affect it. Not even a superhuman being can open such a mystic seal. Only a Dispel Magic Barrier spell has any chance of penetrating/dispelling it. Before the seal can be cast, the object (door, portal, etc.), must be completely scaled in wax. Only after all openings, cracks, and crevices are sealed/filled with melted wax can the spell be placed upon it. Once sealed in wax and the spell invoked, nothing can open it, including the mage who cast the spell. Only a Dispel Magic Barrier may open it.'
            ),
            new Spell(
                'Stone to Flesh',
                '12ft',
                'Instant/Permanent',
                'None',
                'This spell transforms stone to nesh and can restore people who have been turned to stone back to normal. The spell caster can change 50 pounds of stone per level of experience.'
            ),
            new Spell(
                'Swim as a Fish',
                'Self or 1-2 Others',
                '40 Melees per level of spell caster',
                'None',
                'The enchanted persons are then able to breath underwater and swim expertly (at a speed of 20).'
            ),
            new Spell(
                'Teleport (self)',
                'Self',
                'Instant',
                'None',
                'Transports the spell caster from one location to another in the blink of an eye (maximum distance - 5 miles). The spell caster can also teleport an additional 100 pounds per level of experience, so long as be is maintaining some kind of physical contact with it. This spell could teleport another person if they fall under the weight limitation, but there is a 26% chance of shock rendering both the spell caster and the passenger unconscious for 1D6 hours.'
            ),
            new Spell(
                'Teleport (Superior)',
                '300 miles',
                'Instant',
                'None',
                'Transport the spell caster and up to 1000 pounds per level of experience, a maximum of 300 miles away.'
            ),
            new Spell(
                'Tongues',
                'Self or Others',
                '10 melees per level of spell caster',
                'None',
                'Understand and speak all languages limited to the spoken word.'
            ),
            new Spell(
                'Turn Dead',
                '60ft',
                'Instant',
                'Standard',
                'Turn/repel 1D6 dead per level of the spell caster. The dead turned will not come back for 24 hours.'
            ),
            new Spell(
                'Wall of Flame',
                '90ft',
                '10 melees per level of spell caster',
                'None',
                'Creates a raging wall of flame that is 10ft high by 15ft long by 5ft wide per each level of the spell caster. Anyone touching or running through the wall takes 4D8 points of damage for each five feet of width.'
            ),
            new Spell(
                'Wind Rush',
                '120ft',
                'One melee',
                '18 to 20 saves one from losing one\'s balance.',
                'This spell creates a short, powerful wind gusting at 60mph.'
            ),
            new Spell(
                'Words of Truth',
                'Self',
                '5 melees per level of the spell caster',
                'Each question',
                'The being affected by this enchantment is compelled to answer all questions truthfully. The spell caster must be within 5 feet and can ask two questions per melee.'
            ),
        ];
    }
}
