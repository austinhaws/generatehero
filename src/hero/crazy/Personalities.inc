<?php
namespace Heroes\hero\crazy;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\hero\classes\BaseClass;
use Heroes\hero\Hero;

class Personality
{
    /** @var string alignment of the personality */
    public $alignment;
    /** @var string what is quirky about this personality */
    public $quirk;
}

class PersonalityQuirk
{
    public $title;
    public $description;
    public $modifiers;

    function __construct($title, $description, $modifiers)
    {
        $this->title = $title;
        $this->description = $description;
        $this->modifiers = $modifiers;
    }
}

class Personalities extends BaseClass
{
    // additional personalities besides the character's main personality
    public $personalities = [];

    // note: personalities take over: severe shock or trauma, coma or near death, hypnosis, telepathic probe, hypnotic suggestion, mind wipe

    public function __construct(Engine &$engine)
    {
        parent::__construct($engine, 'Crazy');
        $this->classSubtype = 'Multiple Personalities';
    }

    /**
     * @param Hero $hero
     * @param bool $options
     * @throws \Exception
     */
    function create(Hero &$hero, $options = false)
    {
        // this is in addition to the main personality. a result of 1 here means 2 total personalities.
        $numberPersonalities = $this->engine->tableRoller->rollTable('Personalities: total', [
            new TableEntry(30, 1),
            new TableEntry(50, 2),
            new TableEntry(65, 3),
            new TableEntry(89, 4),
            new TableEntry(100, 5),
        ]);

        // main personality doesn't know about these other personalities

        for ($x = 0; $x < $numberPersonalities; $x++) {
            $personality = new Personality();
            $personality->alignment = $this->engine->tableRoller->rollTable('Personality: Alignment', [
                new TableEntry(20, 'Principled'),
                new TableEntry(35, 'Scrupulous'),
                new TableEntry(50, 'Unprincipled'),
                new TableEntry(65, 'Anarchist'),
                new TableEntry(77, 'Miscreant'),
                new TableEntry(89, 'Aberrant'),
                new TableEntry(100, 'Diabolic'),
            ]);

            $goodEvil = false;
            switch ($personality->alignment) {
                case 'Principled':
                case 'Scrupulous':
                    $goodEvil = 'Good';
                    break;
                case 'Unprincipled':
                case 'Anarchist':
                    // selfish
                    $goodEvil = $this->engine->roller->rollDice(new Roll('Personality: selfish', 1, 2)) == 2 ? 'Good' : 'Evil';
                    break;
                case 'Miscreant':
                case 'Aberrant':
                case 'Diabolic':
                    // evil
                    $goodEvil = 'Evil';
                    break;
                default:
                    throw new \Exception("invalid personality alignment: {$personality->alignment}");
            }
            $personality->quirk = $this->{'quirk' . $goodEvil}();

            $this->personalities[] = $personality;
        }
    }

    /**
     * @return mixed
     * @throws \Exception
     */
    private function quirkGood() {
        return $this->engine->tableRoller->rollTable('Quirk Good', [
           new TableEntry(10, new PersonalityQuirk('Despondent', 'Withdrawn; curls up in to a fetal position and gurgles. Can not fight or take any action. Can not use powers or even communicate.', '')),
           new TableEntry(20, new PersonalityQuirk('Coward', 'Afraid of everything: heights, flying, fighting, knives, guns, etc. Will fight only if absolutely necessary, and then only enough to escape. This character will surrender at the slightest hint of trouble Super abilities can be used, but only for self-preservation. He may use the powers to help friends, but would rather stay on the sidelines.', 'Always the last to attack in a melee round. SKills are -10%. Does not know any of the other personalities.')),
           new TableEntry(30, new PersonalityQuirk('Pacifist', 'Gentle, merciful, and compassionate. This character is a as bright and bold as the main personality (maybe even more sot), but will not fight. This personality is adamant against fighting for any reason. If confronted he will dodge, parry, and try to otherwise incapacitate a foe, all the while delivering a speech against fighting and cruelty. He can use his powers, but will rarely use them against others. Will never kill, torture, or strike ot of anger. There are no power or skill penalties.', '+2 to dodge, +1 to parry and roll. Knows about the dominant personality only. THere is a 40% chance that he can be convinced to let the dominant personality back in to control, but only under extreme protest (too violent).')),
           new TableEntry(40, new PersonalityQuirk('Arrogant Warrior', 'Cold, aloof, snob, but extremely capable and confident (over confident). Tends to be incredibly independent, rude, and insensitive. To this personality there are two points of view to everything; the wrong one and his (the only right and logical opinion). This personality uses his powers and skills as he sees fit; usually cold and calculating. There are no skill penalties.', '+10% on all skills, +1 to parry. Knows all the other personalities, but will not willingly let any of them resurface. After all they are inferior to him.')),
           new TableEntry(50, new PersonalityQuirk('Righteous Indignation', 'A personality that has a black and white view of hte world. Evil must be crushed at all costs. This is a war, thus the end justifies the means. He tends to be judgemental, reactionary, and brutal towards evil. Gentle and compassionate to the good and innocent. A potentially volatile and dangerous character. There are no skill or ability penalties, nor bonuses. He sues his extraordinary abilities well. Knows and despises all the other personalities for one reason or another. There is a 50% chance of convincing him to let any of hte other personalities out, except the arrogant warrior.', '')),
           $this->quirkTableEntry_normal(60),
           new TableEntry(70, new PersonalityQuirk('Wildman', 'An overzealous, gregarious, and extremely hyperactive personality with delusions of grandeur. He is fanatically loyal and dedicated to crime fighting, justice, and the American way. He is very reactionary, takes needless risks, and his a complete disregard for his personal safety. This is a character whose intentions are always 100% sincerer, but acts without considering the consequences. Basically, a nutcase with a heart of gold.', 'Suffers from the Frenzy condition. +4 to roll, +1 to parry and dodge. Add 10ft to leaping abilities and 20% to climbing, swimming, and balancing skill abilities. This personality knows all the others and can be convinced to let any of them take control if it is for the good of the group or a good cause (80% likelihood)')),
           $this->quirkTableEntry_hypochondriac(80),
           $this->quirkTableEntry_oppositeSex(90),
           new TableEntry(100, new PersonalityQuirk('The Anti-Super Dude', 'This personality is against the entire concept of super powered beings and vigilantism. Consequently, while he knows about the special powers he possesses he will not use them for any reason. Nor will he engage in superheroics.', '-10% on all skills, no combat skill (one attack per melee and no bonuses to strike, parry, dodge, or roll). Knows about the other personalities but will not let any of them take control!')),
        ]);
    }

    /**
     * @return mixed
     * @throws \Exception
     */
    private function quirkEvil() {
        return $this->engine->tableRoller->rollTable('Quirk Evil', [
           new TableEntry(10, new PersonalityQuirk('Jack the Ripper', 'A twisted personality that preys on the weak, mostly women. Some demented obsession drives this personality to hurt and torment women. If any opponents are female, she will be his first target. The more she fights, the better he likes it. This is a sick individual who loves to torture and watch torment.', '-10% on all skills because hs is physically oriented. +1 to strike. Knows about his other personalities but will not willingly let any of them take control. Prefers blade weapons above all others.')),
           new TableEntry(20, new PersonalityQuirk('Traitor', 'A personality that goes with what is always best for him. He will betray a friend or cause for money, revenge, or to save himself. He will sell or steal information, equipment, or persons without hesitation. To this personality, everything has a price and he intends to cash in on it. The character is amoral, cold, and merciless, taking action that will benefit only him. Completely untrustworthy.', 'Knows about the other personalities and uses them freely to get his way or save his skin.')),
           new TableEntry(30, new PersonalityQuirk('Greedy', 'A personality that craves wealth and fame. He will always look for the profit and value of any activity. He is a stingy braggart who always connives to get hte most money and all the glory. He tends to be secretive, sneaky, deceptive, underhanded, and self-centered.', 'He knows about other personalities but is extremely reluctant to let any of "those losers" take control.')),
           new TableEntry(40, new PersonalityQuirk('Kleptomaniac', 'A compulsive thief who just likes the challenge of stealing. Steals from everybody all the time, just for fun.', 'Has none of the dominant character\'s skills. Pick Pocket: 65%, Pick Locks: 55%, Prowl: 55%, Disguise: 60%, Surveillance Systems: 50%, Hand to Hand: Basic, Pilot Automobile: 88%, Motorcycle: 68%. Knows all other personalities and about his exceptional abilities.')),
           new TableEntry(50, new PersonalityQuirk('Blood Thirsty', 'A personality that loves to fight, hurt people, torture, and kill. A sadistic bully who shows no mercy and intentionally strikes to do maximum damage. This is the personality\'s way of proving his superiority, as well as satisfying his cruel pleasures.', '-5% on all non-combat oriented skills. +1 to strike, parry, and dodge. +10 SDC. Although he knows about the other personalities he will pretend not to and will refuse to willingly let another take control.')),
           new TableEntry(60, new PersonalityQuirk('Megalomaniac', 'Arrogant, feels far superior to all others; mean, cold, and calculating. This personality is totally self-serving. The means justifies his ends and there is only the wrong opinion and his opinion. Those who ignore or chastise his opinions are either fools or potential enemies. The personality is only a team player in the sense that he can use the team to achieve his desires. Tends to be domineering (will try to usurp the leadership). Insensitive and ruthless.', '+10% bonus on all skills.')),
           new TableEntry(70, new PersonalityQuirk('Psychopath', 'A wild, daring, deadly personality who thrives on danger. Nothing is too risky or impossible. Tends to be reactionary, cruel, and strikes with deadly force. Also likes cat and mouse games, as long as he is the cat.', 'Does not know the other personalities. Hand to Hand: Expert, WP Blunt, WP Knife, WP Revolver, WP Automatic Pistol, WP Rifle, Sniper, Prowl: 55%, Climbing 65%, Pilot Automobiles: 92%, Motorcycle: 72%, Truck: 76%, and Escape Artist: 45%. +20 SDC. Will not willingly allow any other personality dominance.')),
           $this->quirkTableEntry_oppositeSex(80),
           $this->quirkTableEntry_hypochondriac(90),
           $this->quirkTableEntry_normal(100),
        ]);
    }

    private function quirkTableEntry_hypochondriac($max) {
        return new TableEntry($max, new PersonalityQuirk('Hypochondriac', 'A personality obsessed with cleanliness, and avoiding injury and disease. He will continually whine about potentially filthy or germ laden environments, and instruct his comrades about proper eating habits, vitamins, medication, and sanitation. If injured in the slightest, the personality will whine and moan about it for hours.', 'Never takes the initiative. -5% on all skills. +1 to parry and doge, and has a paramedic skill with a 85% skill proficiency. Knows all the personalities, but is hesitant to let any take control because they are either too reckless or whimpy and might get him hurt. And they are all "so filthy!!!" However, there is a 50% chance of being convinced to let any of them take control, except the wildman because "that guy\'s crazy". If letting another personality take control is likely to prevent his death or grievous injury, there is an 88% likelihood of letting out a different personality.'));
    }

    private function quirkTableEntry_oppositeSex($max) {
        return new TableEntry($max, new PersonalityQuirk('Opposite Sex', 'Knows about other super powers. Knows other personalities. There is a 40% chance of being convinced to let a different personality surface.', ''));
    }

    private function quirkTableEntry_normal($max) {
        return new TableEntry($max, new PersonalityQuirk('Normal', 'A very mundane, innocent, bumbling nerd-like youth (teenager) who knows nothing about super abilities, crime fighting, or heroics. He is friendly, but shy, and totally bewildered about super beings. He has no recollection of his other personalities or super abilities.', 'Can not use his extraordinary abilities, has no combat training (one attack per melee), and only high school equivalent skills and knowledge. This is a normal kid!'));
    }
}