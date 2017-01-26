<?php
namespace Heroes\tables;

use Heroes\engine\Engine;
use Heroes\engine\TableEntry;
use Heroes\hero\Hero;
use Heroes\hero\insanity\Insanity;

class TableInsanity
{
    // for rollInsanity
    const NEUROSIS = 'Neurosis';
    const OBSESSION = 'Obsession';
    const PHOBIA = 'Phobia';
    const PSYCHOSIS = 'Psychosis';
    const AFFECTIVE = 'Affective Disorders';

    // for addInsanity
    const ALCOHOLISM = 'Alcoholism';
    const DRUGS = 'Drugs';

    private $engine;

    function __construct(Engine $engine)
    {
        $this->engine = $engine;
    }

    /**
     * add a specific insanity type to a character
     *
     * @param Hero $hero the her to which to add an insanity
     * @param $type string the type to add (alcohol or drug)
     * @throws \Exception if type not known
     */
    function addInsanity(Hero &$hero, $type)
    {
        switch ($type) {
            case TableInsanity::ALCOHOLISM:
                $hero->insanities[] = new Insanity('Alcoholism', $this->engine->tableRoller->rollTable('Alcoholism Type', [
                    new TableEntry(10, 'Mean, hostile, strong: +2 to damage.'),
                    new TableEntry(20, 'Quick temper, argumentative; +1 on initiative, -1 to parry or dodge.'),
                    new TableEntry(30, 'Impulsive, takes risks; +2 on initiative.'),
                    new TableEntry(40, 'Quiet, withdrawn; -2% on skills.'),
                    new TableEntry(50, 'Paranoid, trusts no one, agitated; +1 on initiative.'),
                    new TableEntry(60, 'Moody, sad; -5% on all skills.'),
                    new TableEntry(70, 'Secure/self-assured only while intoxicated; -2% on all skills when sober.'),
                    new TableEntry(80, 'Depressed, pessimistic; -5% on all skills.'),
                    new TableEntry(90, 'Hyper, agitated, always moving, distracted; -2 on initiative.'),
                    new TableEntry(100, 'Super syndrome; believes he/she is best when intoxicated. +5% on all skills when intoxicated, -10% when sober.'),
                ]));
                break;
            case TableInsanity::DRUGS:
                $hero->insanities[] = new Insanity('Drug Addiction', $this->engine->tableRoller->rollTable('Drug Addiction Type', [
                    new TableEntry(10, 'Quick temper, argumentative; +1 on initiative.'),
                    new TableEntry(20, 'Totally passive, will not attack, confused, wants to be left alone. -5 to parry, dodge, and roll with punch or fall.'),
                    new TableEntry(30, 'Extremely paranoid. Trusts no one, not even friends; +1 on initiative.'),
                    new TableEntry(40, 'Disoriented. Has difficulty following movement; -4 to parry and dodge, -2 to strike.'),
                    new TableEntry(50, 'Hallucinations. Totally oblivious to reality; -4 to parry and dodge, 50% chance of not recognizing friend or foe, or attacking a friend (thinking him an enemy), or not recognizing danger, or cringe in terror of battle phantoms.'),
                    new TableEntry(60, 'Withdrawn, quiet; -6% on all skills.'),
                    new TableEntry(70, 'Secure/Self-assured only while high; -4% on all skills when not on drugs.'),
                    new TableEntry(80, 'Depressed, pessimistic; -8% on all skills.'),
                    new TableEntry(85, 'Reoccurring hallucinations when under severe pressure/combat. 43% chance of recurrence/flash-back, -4 to parry and dodge, 50% chance of not recognizing friend or foe, or attacking a friend (thinking him an enemy), or not recognizing danger, or cringe in terror of battle phantoms.'),
                    new TableEntry(91, 'Hyper, agitated, always moving, distracted; -2 on initiative, -2% on all skills.'),
                    new TableEntry(100, 'Super syndrome, believes his abilities are heightened by drugs; +1 to strike, parry, and dodge; +6% on all skills when high. -1 to strike, parry, and dodge; -12% on all skills when not high.'),
                ]));
                break;
            default:
                throw new \Exception("Unknown add Insanity: $type");
        }
    }

    /**
     * @param Hero $hero
     * @param bool|String $baseType use static class constants to prepick an insanity type or pass false or nothing to have it randomly rolled
     * @throws \Exception if basetype is not known
     */
    function rollInsanity(Hero &$hero, $baseType = false)
    {
        if (!$baseType) {
            $this->engine->tableRoller->rollTable('Insanity: Type', [
                new TableEntry(10, 'Reborn'),
                new TableEntry(20, TableInsanity::NEUROSIS),
                new TableEntry(30, 'Compulsive Liar'),
                new TableEntry(40, 'Kleptomaniac'),
                new TableEntry(50, TableInsanity::OBSESSION),
                new TableEntry(60, TableInsanity::PHOBIA),
                new TableEntry(70, TableInsanity::PSYCHOSIS),
                new TableEntry(80, 'Fear of Animals'),
                new TableEntry(90, TableInsanity::AFFECTIVE),
                new TableEntry(100, 'Fear of the Dark'),
            ]);
        }

        $detail = false;
        switch ($baseType) {
            case TableInsanity::AFFECTIVE:
                $detail = $this->engine->tableRoller->rollTable('Insanity: Affective', [
                    new TableEntry(19, 'Frightened by loud noises to the point of cowering and wetting self.'),
                    new TableEntry(35, 'Disgusted by anything sticky, and will go to any length to avoid touching it.'),
                    new TableEntry(54, 'Obsessed with cleanliness, and must clean up any area he/she is at for more than a few minutes.'),
                    new TableEntry(75, 'Outraged by acts of violence, becoming violent himself; 72% chance of going berserk and attacking the perpetrator of the violent act without regard for self. Bonus while berserk: +1 to strike, +2 to damage.'),
                    new TableEntry(88, 'Hates music and musicians, and will try to destroy or stop the source of those terrible noises.'),
                    new TableEntry(100, 'Intimidated by spoken language; cannot speak meaningful sentences, and must use sign language or written communication.'),
                ]);
                break;

            case TableInsanity::NEUROSIS:
                $detail = $this->engine->tableRoller->rollTable('Insanity: Neurosis', [
                    new TableEntry(18, 'Fear of the dark: Spent too much time locked in closets to the point of gibbering and total collapse while in the dark.'),
                    new TableEntry(34, 'Fear of animals: Chewed on by the family pet while a nipper to the point of running away when confronted by small, furry things.'),
                    new TableEntry(49, 'Cannot tell the truth: compulsive liar, even if of a good alignment.'),
                    new TableEntry(64, 'Invasion of hte Body Snatchers: Acute paranoia toward all aliens, those of alien heritage and even humans born off the Earth.'),
                    new TableEntry(85, 'Fear of heights: To the poitn of being frozen above the second story; character is fine as long as ground is not visible.'),
                    new TableEntry(100, 'Fear of success: Character will sabotage self at critical moments. The following minuses apply during critical or high pressure moments: -15% to all skills, -3 to hit, dodge, parry, and damage.'),
                ]);
                break;

            case TableInsanity::OBSESSION:
                $detail = ($this->engine->roller->rollDice('Obsession: love/hate', 1, 2) == 1 ? 'Love ' : 'Hate ')
                    . $this->engine->tableRoller->rollTable('Insanity: Obsession', [
                        New TableEntry(5, 'Timelines: '),
                        New TableEntry(12, 'High Technology: Acquire/Use'),
                        New TableEntry(20, 'Opposite Sex'),
                        New TableEntry(27, 'Wealth'),
                        New TableEntry(35, 'Secrecy'),
                        New TableEntry(43, 'Specific Individual'),
                        New TableEntry(50, 'Specific object, item, or animal'),
                        New TableEntry(55, 'Appearance'),
                        New TableEntry(63, 'Danger'),
                        New TableEntry(70, 'Food'),
                        New TableEntry(78, 'Alcohol'),
                        New TableEntry(86, 'Gambling'),
                        New TableEntry(92, 'Solitude'),
                        New TableEntry(100, 'Crimebusting'),
                    ]);

                if (strpos($detail, 'Timelines') !== false) {
                    $detail .= $this->engine->roller->rollDice('Timeline', 1, 2) == 1 ? 'Punctuality' : 'Tardiness';
                }
                break;

            case TableInsanity::PHOBIA:
                $detail = 'Phobia: ' . $this->engine->tableRoller->rollTable('Insanity: Phobia', [
                        new TableEntry(5, 'Insects'),
                        new TableEntry(10, 'Reptiles'),
                        new TableEntry(15, 'BOats'),
                        new TableEntry(18, 'Opposite Sex'),
                        new TableEntry(20, 'Dogs'),
                        new TableEntry(25, 'Darkness'),
                        new TableEntry(30, 'Confining Enclosures'),
                        new TableEntry(35, 'Warehouses/Abandoned Buildings'),
                        new TableEntry(40, 'Contamination'),
                        new TableEntry(45, 'Mutants'),
                        new TableEntry(50, 'Heights'),
                        new TableEntry(55, 'Psionics'),
                        new TableEntry(60, 'Aliens'),
                        new TableEntry(65, 'Water'),
                        new TableEntry(70, 'Drugs'),
                        new TableEntry(75, 'Robots'),
                        new TableEntry(80, 'Flying'),
                        new TableEntry(85, 'Police'),
                        new TableEntry(90, 'Computers'),
                        new TableEntry(92, 'Strangers'),
                        new TableEntry(95, 'Cats'),
                        new TableEntry(100, 'Open Spaces'),
                    ]);
                break;

            case TableInsanity::PSYCHOSIS:
                $detail = $this->engine->tableRoller->rollTable('Insanity: Psychosis', [
                    new TableEntry(15, 'Hysterical Blindness when under pressure (89% likelihood of happening)'),
                    new TableEntry(28, 'Paranoid Type; everyone is out to get you/trusts no one.'),
                    new TableEntry(49, 'Manic Depressive, alternate severe depression one week (suicidal, nobody loves you; -5% on all skills) with manic episodes the next week (everything is great and I\'m the best that there ever was; +5% on all skills).'),
                    new TableEntry(73, 'Schizophrenia: you are passive and easily frightened; jumpy. You hear voices telling you that all the angels are dead; worry about what angels are.'),
                    new TableEntry(85, 'Mindless Aggression: '),
                    new TableEntry(100, 'Become a psychiatrist and try to cure everyone around.'),
                ]);

                // additional details
                if (strpos($detail, 'Manic Depressive') !== false) {
                    if ($this->engine->roller->rollDice('Manic Depressive: Alcoholism', 1, 100) <= 30) {
                        $this->addInsanity($hero, TableInsanity::ALCOHOLISM);
                    }
                } else if ($detail === 'Mindless Aggression: ') {
                    $detail .= $this->engine->tableRoller->rollTable('Mindless Aggression', [
                        new TableEntry(94, 'Semi-Functional: when frustrated, angry, or upset, there is a 72% likelihood of going berserk and lashing out at anyone/everyone around until killed or confined; will take 3-18 minutes of confinement to regain composure.'),
                        new TableEntry(100, 'Non-Functional/Homicidal: Continually going berserk until confined or killed; have one lucid day a week and try to talk your way out of confinement.'),
                    ]);
                } else if (strpos($detail, 'Schizophrenia') !== false && $this->engine->roller->rollDice('Schizophrenia: Addiction', 1, 100) <= 50) {
                    $this->addInsanity($hero, $this->engine->roller->rollDice('Schizophrenia: Addiction Type', 1, 2) == 1 ? TableInsanity::ALCOHOLISM : TableInsanity::DRUGS);
                }
                break;

            default:
                $detail = array(
                    'Reborn' => 'Alignment reversal. Was one alignment and became the opposite.',
                    'Neurosis' => 'Alignment reversal. Was one alignment and became the opposite.',
                    'Compulsive Liar' => 'Even if of a good alignment.',
                    'Kleptomaniac' => 'A compulsion to steal, even if of a good alignment.',
                    'Fear of Animals' => 'Chewed on by the family pet while a nipper to the point of running away when confronted by small, furry things.',
                    'Fear of the Dark' => 'Spent too much time locked in closets to the point of gibbering and total collapse while in the dark.',
                )[$baseType];
                break;
        }

        if (!$detail) {
            throw new \Exception("Unknown baseType: '$baseType'");
        }
        $hero->insanities[] = new Insanity($baseType, $detail);
    }
}