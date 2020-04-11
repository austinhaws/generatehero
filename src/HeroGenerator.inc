<?php

namespace Heroes;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\engine\TableEntry;
use Heroes\enums\BonusTargets;
use Heroes\enums\UrlParameters;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\CharacterBasics;
use Heroes\tables\TableAttributes;
use Heroes\tables\TableEducation;
use RuntimeException;

class HeroGenerator
{
    /** @var Engine drive me */
    public $engine;

    /**
     * HeroGenerator constructor.
     * @param Engine $engine allows testing to override engine
     */
    public function __construct(Engine $engine = null)
    {
        $this->engine = $engine ? $engine : new Engine();
    }

	/**
	 * create a hero!
	 *
	 * @param $urlParams
	 * @return Hero the hero
	 */
    public function generate($urlParams = [])
    {
    	$this->engine->urlParams = $urlParams;
        $hero = new Hero();

        /**
         * this process accomplishes the following
         *  - rolling attributes
         *  - possible crazy hero
         *  - determine super ability type and apply it
         *  - roll education (if super ability type hasn't already determined it)
         *  - alignment
         *  - extra info (weight/originland/etc)
         *  - and tallying all bonuses and calculations
         */

        $hero->gender = $this->engine->tableRoller->rollTable('gender', [
            new TableEntry(1, 'Male'),
            new TableEntry(2, 'Female'),
        ]);

        // step 1 - attributes (3d6; +1d6 if >= 16)
        $attributes = ['intelligenceQuotient', 'mentalEndurance', 'mentalAffinity', 'physicalStrength', 'physicalProwess', 'physicalEndurance', 'physicalBeauty', 'speed'];
        foreach ($attributes as $attribute) {
            $hero->$attribute = $hero->{$attribute . 'Base'} = $this->engine->roller->rollDice(new Roll($attribute, 3, 6));
            if ($hero->$attribute >= 16) {
                $hero->$attribute += $this->engine->roller->rollDice(new Roll('=16 attribute bonus', 1, 6));
            }
        }


        // is the hero crazy?
        if ($this->engine->roller->rollDice(new Roll('is crazy?', 1, 100)) == 100) {
            $crazy = $this->engine->tableRoller->rollTable('crazy element', [
                new TableEntry(30, 'Frenzy'),
                new TableEntry(60, 'Association'),
                new TableEntry(85, 'Personalities'),
                new TableEntry(100, 'Crazy'),
            ]);
            $crazy = "Heroes\\hero\\crazy\\$crazy";
            $hero->crazy = new $crazy($this->engine);
            $hero->crazy->create($hero);
        }


        // step 3 - determine super abilities
        $this->generatePowerCategory($hero);

        // step 4 - education / skills
        if (!$hero->educationLevel) {
            (new TableEducation($this->engine))->rollEducationLevel($hero);
        }

        // step 5 - alignment
        $hero->alignment = $this->engine->tableRoller->rollTable('Alignment', [
            new TableEntry(35, 'Principled'),
            new TableEntry(70, 'Scrupulous'),
            new TableEntry(85, 'Unprincipled'),

            new TableEntry(92, 'Anarchist'),

            new TableEntry(95, 'Miscreant'),
            new TableEntry(98, 'Aberrant'),
            new TableEntry(100, 'Diabolic'),
        ]);

        // step 6 - character start
        $characterBasics = new CharacterBasics($this->engine);
        $characterBasics->generateCharacterBasics($hero);

        // all done, give character's class one last crack at computing
        $hero->class->postCreate($hero);

        // total all bonuses and attributes to get final values
        $this->totalHero($hero);


        return $hero;
    }

    /**
     * @param Hero $hero the hero to total
     */
    public function totalHero(Hero &$hero) {


        // add bonuses from having taken skills; athletic skills and some others add bonuses to attributes and other skills
        $this->addHeroSkillBonuses($hero);

        $statsTotaller = new StatsTotaller($this->engine);

        // attributes give bonuses to other things, so total them first
        $statsTotaller->calculateAttributeTotals($hero);

        // now that attributes are determined, determine their bonuses
        (new TableAttributes($this->engine))->applyAttributeBonuses($hero);

        // with skill bonuses and attribute bonuses all added as bonuses, can now get final totals for stats
        $statsTotaller->calculateNonAttributeTotals($hero);
    }

	/**
	 * determine a power category for the hero
	 * apply that category using its class
	 *
	 * @param Hero $hero the hero
	 */
    public function generatePowerCategory(Hero &$hero)
    {
    	$class = $this->engine->getUrlParam(UrlParameters::POWER_CATEGORY);
    	if (!$class) {
			$class = $this->engine->tableRoller->rollTable('power category', [
				new TableEntry(10, 'Experiment'),
				new TableEntry(20, 'Robotics'),
				new TableEntry(30, 'Bionics'),

				new TableEntry(40, 'SpecialTrainingAncientMaster'),
				new TableEntry(42, 'SpecialTrainingHunterVigilante'),
				new TableEntry(44, 'SpecialTrainingSecretOperative'),
				new TableEntry(46, 'SpecialTrainingStageMagician'),
				new TableEntry(48, 'SpecialTrainingSuperSleuth'),

				new TableEntry(50, 'Mutants'),
				new TableEntry(60, 'Psionics'),
				new TableEntry(70, 'PhysicalTraining'),
				new TableEntry(80, 'Magic'),
				new TableEntry(90, 'Hardware'),
				new TableEntry(100, 'Aliens'),
			]);
		}

        $class = "Heroes\\hero\\classes\\$class";
        $hero->class = (new $class($this->engine));
        $hero->class->create($hero);
    }

    /**
     * determine skills, and add bonuses from taking those skills
     *
     * @param Hero $hero the hero
     */
    private function addHeroSkillBonuses(Hero &$hero)
    {
        $takenSkills = $this->determineTakenSkills($hero);

        $this->addSkillBonuses($hero, $takenSkills);
    }

    /**
     * find all skills that the hero has taken
     *
     * @param Hero $hero the hero
     * @return array skills that were taken: BonusTargets::... constants
     */
    private function determineTakenSkills(Hero &$hero)
    {
        // key = skill BonusTarget:: name, value is true if hero has that skill and key doesn't exist if doesn't have that skill
        $skillsTaken = [];

        // all possible skills
        $allSkills = BonusTargets::allSkills(false);

        // skills that the hero has taken
        foreach ($hero->bonuses as $bonus) {
            if (false !== array_search($bonus->bonusTarget, $allSkills)) {
                $skillsTaken[$bonus->bonusTarget] = true;
            }
        }

        return $skillsTaken;
    }

    /**
     * create a bonus for a skill that sets it to a start value
     * this is in the context of a when taking a skill the hero gets a base percentage with that skill based on the skill
     *
     * @param string $skill the skill BonusTarget::SKILL...
     * @param int $base base percentage of the skill
     * @return Bonus created setter bonus for the skill base
     */
    private function createSkillSetter($skill, $base) {
        return new Bonus(Bonus::BONUS_TYPE_SET, $skill, $base, $skill);
    }

    /**
     * add a bonus to a skill if character has both skills
     *
     * @param string $sourceSkill if hero has this skill
     * @param string $targetSkill add bonus to this skill if hero has this skill
     * @param int $bonus bonus to add to the skill
     * @param Hero $hero the hero
     * @param $takenSkills
     */
    private function addSkillSynergy($sourceSkill, $targetSkill, $bonus, Hero &$hero, $takenSkills) {
        if (isset($takenSkills[$sourceSkill]) && isset($takenSkills[$targetSkill])) {
                $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, $targetSkill, $bonus, $sourceSkill . ' Synergy'));
            }
    }

    /**
     * based on list of skills, give bonuses for that skill
     *
     * @param Hero $hero the hero
     * @param String[] $takenSkills BonusTarget:: skills taken by this hero
     */
    private function addSkillBonuses(Hero &$hero, $takenSkills)
    {
        // all the bonuses for each skill
        $skillBonuses = [
            // -- Communications -- //
            BonusTargets::SKILL_CRYPTOGRAPHY => [
                $this->createSkillSetter(BonusTargets::SKILL_CRYPTOGRAPHY, 35),
            ],
            BonusTargets::SKILL_LASER => [
                $this->createSkillSetter(BonusTargets::SKILL_LASER, 45),
            ],
            BonusTargets::SKILL_OPTIC_SYSTEMS => [
                $this->createSkillSetter(BonusTargets::SKILL_OPTIC_SYSTEMS, 55),
            ],
            BonusTargets::SKILL_RADIO_BASIC => [
                $this->createSkillSetter(BonusTargets::SKILL_RADIO_BASIC, 55),
            ],
            BonusTargets::SKILL_RADIO_SCRAMBLER => [
                $this->createSkillSetter(BonusTargets::SKILL_RADIO_SCRAMBLER, 45),
            ],
            BonusTargets::SKILL_RADIO_SATELLITE => [
                $this->createSkillSetter(BonusTargets::SKILL_RADIO_SATELLITE, 30),
            ],
            BonusTargets::SKILL_SURVEILLANCE => [
                $this->createSkillSetter(BonusTargets::SKILL_SURVEILLANCE, 45),
            ],
            BonusTargets::SKILL_TV_VIDEO => [
                $this->createSkillSetter(BonusTargets::SKILL_SURVEILLANCE, 45),
            ],

            // -- Computer -- //
            BonusTargets::SKILL_COMPUTER_OPERATION => [
                $this->createSkillSetter(BonusTargets::SKILL_COMPUTER_OPERATION, 60),
            ],
            BonusTargets::SKILL_COMPUTER_PROGRAMMING => [
                $this->createSkillSetter(BonusTargets::SKILL_COMPUTER_PROGRAMMING, 40),
            ],

            // -- Domestic -- //
            BonusTargets::SKILL_COOK => [
                $this->createSkillSetter(BonusTargets::SKILL_COOK, 55),
            ],
            BonusTargets::SKILL_DANCE => [
                $this->createSkillSetter(BonusTargets::SKILL_DANCE, 46),
            ],
            BonusTargets::SKILL_FISH => [
                $this->createSkillSetter(BonusTargets::SKILL_FISH, 66),
            ],
            BonusTargets::SKILL_SEW => [
                $this->createSkillSetter(BonusTargets::SKILL_SEW, 45),
            ],
            BonusTargets::SKILL_SING => [
                $this->createSkillSetter(BonusTargets::SKILL_SING, 45),
            ],

            // -- Electric -- //
            BonusTargets::SKILL_BASIC_ELECTRONICS => [
                $this->createSkillSetter(BonusTargets::SKILL_BASIC_ELECTRONICS, 45),
            ],
            BonusTargets::SKILL_ELECTRICAL_ENGINEER => [
                $this->createSkillSetter(BonusTargets::SKILL_ELECTRICAL_ENGINEER, 50),
            ],
            BonusTargets::SKILL_ROBOT_ELECTRONICS => [
                $this->createSkillSetter(BonusTargets::SKILL_ROBOT_ELECTRONICS, 35),
            ],

            // -- Espionage -- //
            BonusTargets::SKILL_CONCEALMENT => [
                $this->createSkillSetter(BonusTargets::SKILL_CONCEALMENT, 25),
            ],
            BonusTargets::SKILL_DETECT_AMBUSH => [
                $this->createSkillSetter(BonusTargets::SKILL_DETECT_AMBUSH, 45),
            ],
            BonusTargets::SKILL_DETECT_CONCEALMENT => [
                $this->createSkillSetter(BonusTargets::SKILL_DETECT_CONCEALMENT, 35),
            ],
            BonusTargets::SKILL_DISGUISE => [
                $this->createSkillSetter(BonusTargets::SKILL_DISGUISE, 45),
            ],
            BonusTargets::SKILL_ESCAPE_ARTIST => [
                $this->createSkillSetter(BonusTargets::SKILL_ESCAPE_ARTIST, 35),
            ],
            BonusTargets::SKILL_FORGERY => [
                $this->createSkillSetter(BonusTargets::SKILL_FORGERY, 35),
            ],
            BonusTargets::SKILL_INTELLIGENCE => [
                $this->createSkillSetter(BonusTargets::SKILL_INTELLIGENCE, 46),
            ],
            BonusTargets::SKILL_IMPERSONATION => [
                $this->createSkillSetter(BonusTargets::SKILL_IMPERSONATION, 44),
            ],
            BonusTargets::SKILL_INTERROGATION => [
                $this->createSkillSetter(BonusTargets::SKILL_INTERROGATION, 45),
            ],
            BonusTargets::SKILL_LAND_NAVIGATION => [
                $this->createSkillSetter(BonusTargets::SKILL_LAND_NAVIGATION, 44),
            ],
            BonusTargets::SKILL_PALMING => [
                $this->createSkillSetter(BonusTargets::SKILL_PALMING, 30),
            ],
            BonusTargets::SKILL_PICK_LOCKS => [
                $this->createSkillSetter(BonusTargets::SKILL_PICK_LOCKS, 40),
            ],
            BonusTargets::SKILL_PICK_POCKETS => [
                $this->createSkillSetter(BonusTargets::SKILL_PICK_POCKETS, 35),
            ],
            BonusTargets::SKILL_SNIPER => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 2, BonusTargets::SKILL_SNIPER),
            ],
            BonusTargets::SKILL_TRACKING => [
                $this->createSkillSetter(BonusTargets::SKILL_TRACKING, 35),
            ],
            BonusTargets::SKILL_WILDERNESS_SURVIVAL => [
                $this->createSkillSetter(BonusTargets::SKILL_WILDERNESS_SURVIVAL, 45),
            ],

            // -- Mechanical -- //
            BonusTargets::SKILL_AUTOMOTIVE_MECHANICS => [
                $this->createSkillSetter(BonusTargets::SKILL_AUTOMOTIVE_MECHANICS, 53),
            ],
            BonusTargets::SKILL_AIRCRAFT_MECHANICS => [
                $this->createSkillSetter(BonusTargets::SKILL_AIRCRAFT_MECHANICS, 48),
            ],
            BonusTargets::SKILL_BASIC_MECHANICS => [
                $this->createSkillSetter(BonusTargets::SKILL_BASIC_MECHANICS, 44),
            ],
            BonusTargets::SKILL_COMPUTER_REPAIR => [
                $this->createSkillSetter(BonusTargets::SKILL_COMPUTER_REPAIR, 45),
            ],
            BonusTargets::SKILL_LOCKSMITH => [
                $this->createSkillSetter(BonusTargets::SKILL_LOCKSMITH, 30),
            ],
            BonusTargets::SKILL_MECHANICAL_ENGINEERING => [
                $this->createSkillSetter(BonusTargets::SKILL_MECHANICAL_ENGINEERING, 50),
            ],
            BonusTargets::SKILL_ROBOT_MECHANICS => [
                $this->createSkillSetter(BonusTargets::SKILL_ROBOT_MECHANICS, 35),
            ],

            // -- Military -- //
            BonusTargets::SKILL_DEMOLITIONS => [
                $this->createSkillSetter(BonusTargets::SKILL_DEMOLITIONS, 63),
            ],
            BonusTargets::SKILL_DEMOLITIONS_DISPOSAL => [
                $this->createSkillSetter(BonusTargets::SKILL_DEMOLITIONS_DISPOSAL, 63),
            ],
            BonusTargets::SKILL_PILOT_TANK => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_TANK, 54),
            ],

            // -- Medical -- //
            BonusTargets::SKILL_CRIMINAL_SCIENCE_FORENSICS => [
                $this->createSkillSetter(BonusTargets::SKILL_CRIMINAL_SCIENCE_FORENSICS, 40),
            ],
            BonusTargets::SKILL_FIRST_AID => [
                $this->createSkillSetter(BonusTargets::SKILL_FIRST_AID, 55),
            ],
            BonusTargets::SKILL_PARAMEDIC => [
                $this->createSkillSetter(BonusTargets::SKILL_PARAMEDIC, 56),
            ],
            BonusTargets::SKILL_MEDICAL_DOCTOR => [
                $this->createSkillSetter(BonusTargets::SKILL_MEDICAL_DOCTOR, 63),
            ],
            BonusTargets::SKILL_PATHOLOGY => [
                $this->createSkillSetter(BonusTargets::SKILL_PATHOLOGY, 50),
            ],

            // -- Medical -- //
            BonusTargets::SKILL_HAND_TO_HAND_BASIC => [],
            BonusTargets::SKILL_HAND_TO_HAND_EXPERT => [],
            BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS => [],
            BonusTargets::SKILL_ACROBATICS => [
                $this->createSkillSetter(BonusTargets::SKILL_PATHOLOGY, 55),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 2, BonusTargets::SKILL_ACROBATICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 1, BonusTargets::SKILL_ACROBATICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Acrobatics - PP', 1, 4), BonusTargets::SKILL_ACROBATICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 1, BonusTargets::SKILL_ACROBATICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Acrobatics - SDC', 1, 6), BonusTargets::SKILL_ACROBATICS),
            ],
            BonusTargets::SKILL_ARCHERY => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, BonusTargets::SKILL_ARCHERY),
            ],
            BonusTargets::SKILL_ATHLETICS => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 2, BonusTargets::SKILL_ATHLETICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, BonusTargets::SKILL_ATHLETICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, BonusTargets::SKILL_ATHLETICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 1, BonusTargets::SKILL_ATHLETICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 1, BonusTargets::SKILL_ATHLETICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, new Roll('Athletics - Speed', 1, 4), BonusTargets::SKILL_ATHLETICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Athletics - SDC', 1, 8), BonusTargets::SKILL_ATHLETICS),
            ],
            BonusTargets::SKILL_BODY_BUILDING => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 2, BonusTargets::SKILL_BODY_BUILDING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, 10, BonusTargets::SKILL_BODY_BUILDING),
            ],
            BonusTargets::SKILL_BOXING => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, BonusTargets::SKILL_BOXING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 2, BonusTargets::SKILL_BOXING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, BonusTargets::SKILL_BOXING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 2, BonusTargets::SKILL_BOXING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, new Roll('Boxing - PS', 1, 4), BonusTargets::SKILL_BOXING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Boxing - SDC', 3, 6), BonusTargets::SKILL_BOXING),
            ],
            BonusTargets::SKILL_CLIMBING => [
                $this->createSkillSetter(BonusTargets::SKILL_CLIMBING, 58),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 1, BonusTargets::SKILL_CLIMBING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 1, BonusTargets::SKILL_CLIMBING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Climbing - SDC', 1, 6), BonusTargets::SKILL_CLIMBING),
            ],
            BonusTargets::SKILL_FENCING => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, BonusTargets::SKILL_FENCING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, BonusTargets::SKILL_FENCING),
            ],
            BonusTargets::SKILL_GYMNASTICS => [
                $this->createSkillSetter(BonusTargets::SKILL_GYMNASTICS, 55),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 3, BonusTargets::SKILL_GYMNASTICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 2, BonusTargets::SKILL_GYMNASTICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_PROWESS, new Roll('Gymnastics - PP', 1, 4), BonusTargets::SKILL_GYMNASTICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 2, BonusTargets::SKILL_GYMNASTICS),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Gymnastics - SDC', 3, 6), BonusTargets::SKILL_GYMNASTICS),
            ],
            BonusTargets::SKILL_PROWL => [
                $this->createSkillSetter(BonusTargets::SKILL_PROWL, 54),
            ],
            BonusTargets::SKILL_RUNNING => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 1, BonusTargets::SKILL_RUNNING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, new Roll('Gymnastics - Speed', 4, 4), BonusTargets::SKILL_RUNNING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Gymnastics - SDC', 1, 6), BonusTargets::SKILL_RUNNING),
            ],
            BonusTargets::SKILL_SWIMMING => [
                $this->createSkillSetter(BonusTargets::SKILL_SWIMMING, 58),
            ],
            BonusTargets::SKILL_SWIMMING_ADVANCED => [
                $this->createSkillSetter(BonusTargets::SKILL_SWIMMING_ADVANCED, 55),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DODGE, 2, BonusTargets::SKILL_SWIMMING_ADVANCED),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 1, BonusTargets::SKILL_SWIMMING_ADVANCED),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 1, BonusTargets::SKILL_SWIMMING_ADVANCED),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_SPEED, new Roll('SCUBA - Speed', 3, 4), BonusTargets::SKILL_SWIMMING_ADVANCED),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Advanced Swimming - SDC', 1, 6), BonusTargets::SKILL_SWIMMING_ADVANCED),
            ],
            BonusTargets::SKILL_WRESTLING => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ROLL, 2, BonusTargets::SKILL_WRESTLING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_STRENGTH, 2, BonusTargets::SKILL_WRESTLING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTRIBUTE_PHYSICAL_ENDURANCE, 1, BonusTargets::SKILL_WRESTLING),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Wrestling - SDC', 4, 6), BonusTargets::SKILL_WRESTLING),
            ],

            // -- Pilot -- //
            BonusTargets::SKILL_PILOT_RACE_CAR => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_RACE_CAR, 60),
            ],
            BonusTargets::SKILL_PILOT_AUTOMOBILE => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_AUTOMOBILE, 84),
            ],
            BonusTargets::SKILL_PILOT_MOTORCYCLE => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_MOTORCYCLE, 64),
            ],
            BonusTargets::SKILL_PILOT_TRUCK => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_TRUCK, 64),
            ],
            BonusTargets::SKILL_PILOT_AIRPLANE_OLD_STYLE => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_AIRPLANE_OLD_STYLE, 74),
            ],
            BonusTargets::SKILL_PILOT_BOATS_SAIL => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_BOATS_SAIL, 64),
            ],
            BonusTargets::SKILL_PILOT_BOATS_MOTOR => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_BOATS_MOTOR, 64),
            ],

            // -- Pilot Advanced -- //
            BonusTargets::SKILL_PILOT_HELICOPTER_BASIC => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_HELICOPTER_BASIC, 64),
            ],
            BonusTargets::SKILL_PILOT_HELICOPTER_COMBAT => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_HELICOPTER_COMBAT, 56),
            ],
            BonusTargets::SKILL_PILOT_JET_COMMERCIAL => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_JET_COMMERCIAL, 64),
            ],
            BonusTargets::SKILL_PILOT_JET_FIGHTER => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_JET_FIGHTER, 54),
            ],
            BonusTargets::SKILL_PILOT_SPACE_SHUTTLE => [
                $this->createSkillSetter(BonusTargets::SKILL_PILOT_SPACE_SHUTTLE, 54),
            ],

            // -- Pilot Related -- //
            BonusTargets::SKILL_NAVIGATION => [
                $this->createSkillSetter(BonusTargets::SKILL_NAVIGATION, 65),
            ],
            BonusTargets::SKILL_NAVIGATION_SPACE => [
                $this->createSkillSetter(BonusTargets::SKILL_NAVIGATION_SPACE, 65),
            ],
            BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS => [
                $this->createSkillSetter(BonusTargets::SKILL_READ_SENSORY_INSTRUMENTS, 45),
            ],
            BonusTargets::SKILL_WEAPON_SYSTEMS => [
                $this->createSkillSetter(BonusTargets::SKILL_WEAPON_SYSTEMS, 52),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 2, BonusTargets::SKILL_WEAPON_SYSTEMS),
            ],

            // -- Science -- //
            BonusTargets::SKILL_ASTROPHYSICS => [
                $this->createSkillSetter(BonusTargets::SKILL_ASTROPHYSICS, 35),
            ],
            BonusTargets::SKILL_BIOLOGY => [
                $this->createSkillSetter(BonusTargets::SKILL_BIOLOGY, 45),
            ],
            BonusTargets::SKILL_BOTANY => [
                $this->createSkillSetter(BonusTargets::SKILL_BOTANY, 45),
            ],
            BonusTargets::SKILL_CHEMISTRY_BASIC => [
                $this->createSkillSetter(BonusTargets::SKILL_CHEMISTRY_BASIC, 55),
            ],
            BonusTargets::SKILL_CHEMISTRY_ANALYTICAL => [
                $this->createSkillSetter(BonusTargets::SKILL_CHEMISTRY_ANALYTICAL, 50),
            ],
            BonusTargets::SKILL_MATHEMATICS_BASIC => [
                $this->createSkillSetter(BonusTargets::SKILL_MATHEMATICS_BASIC, 82),
            ],
            BonusTargets::SKILL_MATHEMATICS_ADVANCED => [
                $this->createSkillSetter(BonusTargets::SKILL_MATHEMATICS_ADVANCED, 68),
            ],

            // -- Technical -- //
            BonusTargets::SKILL_ART => [
                $this->createSkillSetter(BonusTargets::SKILL_ART, 44),
            ],
            BonusTargets::SKILL_LANGUAGE => [
                $this->createSkillSetter(BonusTargets::SKILL_LANGUAGE, 60),
            ],
            BonusTargets::SKILL_PHOTOGRAPHY => [
                $this->createSkillSetter(BonusTargets::SKILL_PHOTOGRAPHY, 55),
            ],
            BonusTargets::SKILL_WRITING => [
                $this->createSkillSetter(BonusTargets::SKILL_WRITING, 38),
            ],

            // -- Weapon Proficiencies - Ancient -- //
            BonusTargets::SKILL_WP_BLUNT => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, BonusTargets::SKILL_WP_BLUNT),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, BonusTargets::SKILL_WP_BLUNT),
            ],
            BonusTargets::SKILL_WP_CHAIN => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, BonusTargets::SKILL_WP_CHAIN),
            ],
            BonusTargets::SKILL_WP_KNIFE => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, BonusTargets::SKILL_WP_KNIFE),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, BonusTargets::SKILL_WP_KNIFE),
            ],
            BonusTargets::SKILL_WP_PAIRED_WEAPONS => [
            ],
            BonusTargets::SKILL_WP_STAFF => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, BonusTargets::SKILL_WP_STAFF),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, BonusTargets::SKILL_WP_STAFF),
            ],
            BonusTargets::SKILL_WP_SWORD => [
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::STRIKE, 1, BonusTargets::SKILL_WP_SWORD),
                new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::PARRY, 1, BonusTargets::SKILL_WP_SWORD),
            ],

            // -- Weapon Proficiencies - Modern -- //
            BonusTargets::SKILL_WP_TARGET => [],
            BonusTargets::SKILL_WP_REVOLVER => [],
            BonusTargets::SKILL_WP_RIFLE => [],
            BonusTargets::SKILL_WP_AUTOMATIC_PISTOL => [],
            BonusTargets::SKILL_WP_SUB_MACHINEGUN => [],
            BonusTargets::SKILL_WP_AUTOMATIC_RIFLE => [],
            BonusTargets::SKILL_WP_HEAVY => [],

            // -- Weapon Proficiencies - Energy -- //
            BonusTargets::SKILL_WP_ENERGY_PISTOL => [],
            BonusTargets::SKILL_WP_ENERGY_RIFLE => [],
        ];

        // add synergy bonuses for skills
        $this->addSkillSynergy(BonusTargets::SKILL_LOCKSMITH, BonusTargets::SKILL_BASIC_ELECTRONICS, 5, $hero, $takenSkills);

        $this->addSkillSynergy(BonusTargets::SKILL_MECHANICAL_ENGINEERING, BonusTargets::SKILL_LOCKSMITH, 5, $hero, $takenSkills);
        $this->addSkillSynergy(BonusTargets::SKILL_MECHANICAL_ENGINEERING, BonusTargets::SKILL_SURVEILLANCE, 5, $hero, $takenSkills);


        // add bonuses for taken skills
        foreach ($takenSkills as $skill => $unused) {
            if (!isset($skillBonuses[$skill])) {
                throw new RuntimeException('missing skill bonuses for skill: ' . $skill);
            }
            $bonuses = $skillBonuses[$skill];
            if ($bonuses) {
                $hero->addBonus($bonuses);
            }
        }
    }
}
