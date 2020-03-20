<?php

namespace Heroes\tables\superabilities;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\enums\BonusTargets;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\hero\Psionic;
use Heroes\tables\TableBase;

class TablePsionics extends TableBase
{
    /**
     * add some psionics to a hero
     *
     * @param Hero $hero the hero
     * @param int $numMajor how many majors
     * @param int $numMinor how many minors
     */
    public function selectPowers(Hero &$hero, $numMajor, $numMinor)
    {
        if ($numMajor) {
            $pickers = TablePsionics::majorPowers();
            while ($numMajor && count($pickers)) {
                if ($hero->addPsionic($this->engine->arrayTools->pickFromList($pickers))) {
                    $numMajor--;
                }
            }
        }
        if ($numMinor) {
            $pickers = TablePsionics::minorPowers();
            while ($numMinor && count($pickers)) {
                if ($hero->addPsionic($this->engine->arrayTools->pickFromList($pickers))) {
                    $numMinor--;
                }
            }
        }
    }

    private function minorPowers()
    {
        return [
            new Psionic(
                'Alter Aura',
                'Self',
                '20 minutes per level of the psionic',
                '4',
                'None',
                'Can disguise his aura so that another psionic could not see his lrue aura. In this way the psionic can appear another much weaker, or less experienced than he really is.'
            ),
            new Psionic(
                'Detect Psionics',
                '620 yards (610m)',
                '2 minutes',
                '2',
                'None',
                'This mental probe will detect psionics in others.'
            ),
            new Psionic(
                'Death Trance',
                'Self',
                '10 minutes',
                '2',
                'None',
                'Creates a temporary state of suspended animation, simulating death.'
            ),
            new Psionic(
                'Hypnotic Suggestion',
                '12ft (3.6m)',
                'Unknown',
                '2 per each suggestion',
                'Standard',
                'Induce his will upon another through the power of suggestion. This is a subversive mental attack that requires eye contact and verbal suggestion. The verbal suggestion should be weaved into a conversation and take the form of a simple request or demand.'
            ),
            new Psionic(
                'Mind Block',
                'Self',
                '10 minutes',
                '4',
                'None',
                'Create a mental wall that prevents the penetration of telepathy, empathy, empathic transfer, and detect psionics.'
            ),
            new Psionic(
                'Resist Cold',
                'Self',
                '4 hours',
                '2',
                'None',
                'Suffer no ill effects or discomfort from prolonged exposure to cold conditions.'
            ),
            new Psionic(
                'Resist Fatigue',
                'Self',
                '4 hours',
                '2',
                'None',
                'Operate normally, even under taxing conditions.'
            ),
            new Psionic(
                'Resist Hunger',
                'Self',
                '8 hours',
                '2',
                'None',
                'Function normally even if dying of malnutrition. It does not negate the physical damage of starvation.'
            ),
            new Psionic(
                'Resist Thirst',
                'Self',
                '8 hours',
                '2',
                'None',
                'Allows the psionic to suspend any desire for water. It does not negate the physical dehydration of the body.'
            ),
            new Psionic(
                'See Aura',
                '120ft (36m)',
                '4 melees/1 minute',
                '4',
                'None',
                'Seeing an aura will indicate the following: general alignment, estimated level, human/mutant/alien, presence of super power, and overall health.'
            ),
            new Psionic(
                'Sixth Sense',
                '90 ft/Self',
                '2 melees',
                '2',
                'None',
                'Alert the psionic to any potential danger.'
            ),
            new Psionic(
                'Speed Reading',
                'Self',
                '10 minutes',
                '4',
                'None',
                'Speed of reading is 30 pages per minute.'
            ),
            new Psionic(
                'Summon Inner Strength',
                'Self',
                '20 minutes',
                '6',
                'None',
                'Temporarily alters the psionic\'s physical body by making it tougher, adding 10 SDC per every 6 ISP.'
            ),
            new Psionic(
                'Total Recall',
                'Self',
                '20 minutes',
                '5',
                'None',
                'Remember small blocks of information in absolute detail.'
            ),
        ];
    }

    private function majorPowers()
    {
        return [
            new Psionic(
                'Astral Projection',
                'Self',
                '4 minutes per level of psionic',
                '8',
                'None',
                'The physical body falls inlo a death-like trance while the astral body enters the vast plane of the astral world. The astral world seems to be an infinite world of rolling clouds and yellow sky. No up, no down, just endless sky. While in the astral world the person can fly great distances in the blink of an eye. The astral traveler has a SO% chance of being able to sense locations of the physical world, parallel them in the astral plane, stop, and peer into the physical. In doing so the astral traveler, can see and hear everything that\'s going on in a room. The usual visual and audio limitations apply while in the astral plane, so a character can not hear or see any farther than he could in the physical dimension. However. he can hover above or at any angle to literally get a bird\'s eye view .'
            ),
            new Psionic(
                'Bio-Manipulation',
                '160ft (48.8m)',
                '4D4 minutes',
                '12',
                'Standard',
                'Intended victims must be within line of vision or their exact location known to the psionic. Each costs 12 ISP to inflict. The duration can be extended 4D4 minutes per additional 6 ISP. Blind: Temporarily knocks out the victim\'s optic nerves, rendering that person quite helpless; Deafness: Can be caused by manipulating the eardrum; Mute: Impairs the victim\'s vocal cords, making speech impossible; Pain: By manipulating the nerve centers the psionic can induce terrible pain shooting throughout the body; Paralysis: Immobilizes the motor part of the brain causing legs and arms to stop functioning; Stun: This attack disorients and confuses its victims; Tissue Manipulation: Affects the tissue connecting nerve fibers which can cause a variety of effect.'
            ),
            new Psionic(
                'Bio-Regeneration',
                'Self',
                'Permanent',
                '6',
                'None',
                'Heal oneself of disease, poison, or physical damage. Restore 2D6 hit points, or 3D6 SDC points per melee.'
            ),
            new Psionic(
                'Ectoplasmic Arm',
                '30ft (9.1m)',
                'duration4 minutes per level of psionic',
                '8',
                'Dodge or parry',
                'Create a vaporous, luminous substance in the shape of a hand and arm. Weight limitation of the arm is 40lbs per each of the psionic\'s experience levels.'
            ),
            new Psionic(
                'Empathy',
                '160ft (48.8m) or line of vision',
                '8 melees',
                '8',
                'Standard',
                'Allows the psionic to read other peoples\' emotions.'
            ),
            new Psionic(
                'Empathic Transfer',
                '120ft',
                '2d6 minutes',
                '6',
                'Standard',
                'Project false emotions into one individual. By increasing the ISP to 12 he can influence as many as six characters. The duration can also be extended 2D6 minutes by expending another 6 ISP. Despair or Sorrow: Invokes great emotional upheaval, deep sorrow and a sense of loss; Confusion: Disorients the person so badly that he has no sense of direction, time, or of what is exactly going on.; Fear: Invokes unreasoning terror in all those affected; Hate or Anger: Will prompt those affected to act rashly, charge, attack, argue violently, etc; Love or Peacefulness: Will induce a deep feeling of serenity, dispelling anger, hatred, sorrow, and so on; Trust: Will make its victims believe everything the psionic tells them, but only while under the empathic influence.'
            ),
            new Psionic(
                'Hydrokinesis',
                'Variable',
                'Variable',
                'Variable',
                'Variable',
                'Create a Fog: By manipulating the moisture in the air the psionic can create a fog; Area affected: 80ft radius; Range: 300ft away per each level of the psionic; Duration: 5 minutes per level of the psionic; ISP: 6; Savings Throw: None. Create Water: Super-condense moisture from the air to create water as a sudden concentrated downpour. 2 to 60ft radius. A maximum of 300 gallons. Range:  120ft away; Duration: one melee for under 100 gallons, three melees for all 300 gallons. The water remains until it dries up. ISP: 6; Saving Throw: Dodge; Damage: None. Water Slam or Giant Wave: Create and/or control water, making it rise-up like a towering hand or wall and slam down on a specific target.Can create and control 300 gallons which does 6D6 damage. Range: 60ft; Area Affected: Individual or 12ft radius; ISP: 6; Saving Throw: dodge. Waterspout: Creating or controlling water to suddenly spout up from underneath someone or something like a geyser. Area Affected: Is a maximum of 6ft; Duration: 6 melees per level of the psionic or until cancelled by the psionic; ISP: 4; Height of Spout: 10ft per level of the psionic; Weight Limitation: 250lbs per level of the psionic; Saving Throw: Dodge Water Wall: A wall suspended in air. The wall will slow and deflect bullets and laser attacks. Fire-type blasts that pass through the water wall are diffused and reduced to one third strength. The wall also obscures vision, making it extremely difficult to see figures or discern movement clearly. Range: up to 140ft away; Duration: 8 melees per level of the psionic; ISP: 4; Saving Throw: None. Water Walk: Stand and even walk across water or any liquid substance. Range: Self; Duration: 10 minutes per level of the psionic, or as long as ISP are continually renewed @ ISP: 4.'
            ),
            new Psionic(
                'Hypnosis',
                '60ft (18.3m)',
                '8 melees/2 minutes per level of psionic',
                '2 per suggestion/command',
                'Standard',
                'Implant commands and suggestions in another person\'s mind. The psionic can make two commands or suggestions each melee, and can repeat a command if the opponent saves against it the first or second time. As the psionic develops his hypnotic powers he can influence more than one mind at a time; one per each level of experience.'
            ),
            new Psionic(
                'Levitation',
                'Self or other person/object up to 90ft (27.4m) away',
                '6 minutes per level of psionic',
                '4',
                'None',
                'Lift himself, an object, or another person into the air. Levitation is limited to moving straight up and down, and should not be construed as a limited flying ability. Height Limitation: 15ft per each level of the psionic. Weight Limitation: 250lbs per each level of the psionic.'
            ),
            new Psionic(
                'Mind Bolt',
                '140ft (32.7m)',
                'Instant',
                '4',
                'Dodge',
                'Fire an energy bolt capable of inflicting 2D6 points of damage. The target must be within the psionic\'s line of vision.'
            ),
            new Psionic(
                'Mind Bond',
                'Touch',
                'Special',
                '10',
                'Standard',
                'Creates an instant mind link between the psionic and the victim. Each will learn everything there is to know about the other. This includes scholastic and secondary skills, secret identities, phobias, etc. In both cases the memory is complete for only 3D4 hours.'
            ),
            new Psionic(
                'Mind Control',
                '40ft (12.2m)',
                '5 minutes per level of the psionic',
                '6',
                'Standard',
                'The affected person will fall under the complete control of the psionic. Victims of mind control will obey the psionic without question and answer all questions truthfully. They can even be made to combat friends and allies, although the controlled person\'s reactions and reflexes are somewhat impaired. The psionic can control two people at third level, another at fifth level, and one at every other level thereafter.'
            ),
            new Psionic(
                'Mind Wipe',
                'Touch',
                'Special',
                'Special',
                'Standard',
                'The psionic touches his victim\'s temples to erase whatever he desires by verbal suggestion and can erase any past event, knowledge, skill, and so on. The process takes about three minutes to complete. The loss of memory is temporary, lasting 1D4 days for every 10 ISP expended. The memory can be permanently erased if the psionic exerts 50 ISP at once. A psionic can also permanently wipe a mind completely blank by expending 50 ISP and four Mental Endurance (ME) points. This is an extremely grueling process for the psionic and the loss of the four M.E. points is permanent, even if the opponent successfully saves against the wipe and is not affected.'
            ),
            new Psionic(
                'Object Read',
                'Touch',
                'Instant',
                '4',
                'Standard',
                'By holding the object and concentrating on the owner or history of the object, the psionic will instantly receive impressions and images revealing bits of information, such as whether the previous owner is dead or alive, or in danger, ciC. In addition to impressions, the psionic will actually see images of isolated events which have happened in the past.'
            ),
            new Psionic(
                'Presence Sense',
                '120ft (36m) radius',
                '8 melees/2 minutes',
                '4',
                'None',
                'Detect the presence of any corporeal or non-corporeal entity. It will only indicate the general location of the invisible person.'
            ),
            new Psionic(
                'Pyrokinesis',
                '30 to 90ft',
                'Varies',
                'Special',
                'Dodge',
                'Create fire through force of will and molecular agitation. Fire Eruption: Cause something to erupt and be engulfed by fire. Range: 90ft; ISP: Combustible items 6, Non-combustible items 10. Fire Ball: Create and blast out a fire ball. Range: 120ft; ISP: 4; Damage: 2D6. Spontaneous Combustion: Cause combustible material to ignite. Range: 30ft; ISP: 2; Savings Throw: None. Wall of Flame: Creation of a roaring wall or circle of flame. Range: Up to 120ft away; Duration: 2 minutes per level of psionic; ISP: 4; Damage: 3D6 to anyone who passes through it; Savings Throw: None'
            ),
            new Psionic(
                'Telekinesis',
                '120ft plus 60ft per level of the psionic',
                '10 minutes',
                'Special',
                'None',
                'Cause objects to float, hover, fly, slide, etc., by mental manipulation. The object or person to be moved must be clearly visible and within range. Weight Limitation: The psionic can move a maximum of 500lbs plus 100lbs per level of the psionic\'s experience. ISP: objects weighing < 1lb: 1 ISP, 1-50lbs: 2 ISP. Each one hundred pounds costs 4 ISP. Objects between 2lbs and 5lbs under can be hurled as missile weapons doing 1D6 damage. A telekinetic force field can be erected as an invisible wall that can stop all types of missile weapons, bullets, arrows, vehicles traveling under 90mph, and similar physical objects. It does not stop energy weapons like blasters, lasers, heat, fire, cold, etc. Range: Around self or up to 30ft away; Duration: 5 minutes; ISP: 15; Maximum Area Affected: 15 x 15 wall or 8ft radius.'
            ),
            new Psionic(
                'Telemechanics',
                'Touch or 5ft away (1.5m)',
                '10 minutes plus 2 minutes per level of psionic',
                '10',
                'None',
                'Mentally communicate and understand machines. By touching any non-artificially intelligent machine, whether it be a bicycle, gun, car or airplane, the psionic will instantly have a complete knowledge of exactly how the machine operates.'
            ),
            new Psionic(
                'Telepathy',
                '340ft (103.7m)',
                '10 minutes plus 2 minutes per level of the psionic',
                '4',
                'Standard',
                'Pick up the surface thoughts of others, as well as communicate mentally. When mentally communicating, the psionic is able to have a two-way mental communication with one person per each level of the psionic. A telepathic probe is an extended type of telepathy in which the psionic can delve deeply into a person\'s mind to pull out secrets and deep thoughts. However, it requires an extra 6 ISP.'
            ),
        ];
    }

    public function selectPowersMutantAlien(Hero &$hero, $reason)
    {
        TablePsionics::selectPowers($hero, $reason, 2, 4);

        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_ENDURANCE, new Roll('Psionic - ME', 2, 4), $reason));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_MENTAL_AFFINITY, new Roll('Psionic - MA', 1, 4), $reason));
    }

    public function mutantAlienISP(Hero &$hero, Engine $engine)
    {
        return $hero->mentalEndurance * 2 + $engine->roller->rollDice(new Roll('Psionic: Mutant Alien - ISP', 1, 8));
    }

}
