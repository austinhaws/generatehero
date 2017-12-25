<?php
namespace Heroes\hero\classes;

use Heroes\engine\Engine;
use Heroes\engine\Roll;
use Heroes\enums\BonusTargets;
use Heroes\enums\SkillPrograms;
use Heroes\hero\Bonus;
use Heroes\hero\Hero;
use Heroes\tables\superabilities\EducationOptions;
use Heroes\tables\TableEducation;

class PhysicalTraining extends BaseClass
{
    public function __construct(Engine &$engine)
    {
        parent::__construct($engine, 'Physical Training');
    }

    /**
     * create a character's class
     *
     * @param Hero $hero the hero
     * @param bool $options
     * @throws \Exception ya ya, whatever
     */
    public function create(Hero &$hero, $options = false)
    {
        $tableEducation = new TableEducation($this->engine);

        $tableEducation->rollEducationLevel(
            $hero,
            0,
            // one less skill program from education
            new EducationOptions(
                -1,
                // and do not select physical skills
                [SkillPrograms::PHYSICAL],
                BonusTargets::physicalSkills(false))
        );

        // 8 physical skills : +20%
        $skills = $this->engine->skillPrograms->selectSkills(8, $hero, 20, BonusTargets::physicalSkills(false), false);
        foreach ($skills as $skill) {
            $hero->addSkill($skill, 'Physical Training Skill', 20);
        }

        // 3 espionage skills: +20
        $skills = $this->engine->skillPrograms->selectSkills(3, $hero, 20, BonusTargets::espionageSkills(false), false);
        foreach ($skills as $skill) {
            $hero->addSkill($skill, 'Physical Training Skill', 20);
        }

        // hand to hand export OR martial arts
        if ($this->engine->roller->rollDice(new Roll('Physical Training: Hand to Hand type', 1, 2)) === 2) {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_HAND_TO_HAND_EXPERT, 0, 'Physical Training: Hand to Hand'));
        } else {
            $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SKILL_HAND_TO_HAND_MARTIAL_ARTS, 0, 'Physical Training: Hand to Hand'));
        }

        // add +10% save vs comma/death
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_COMMA, 10, 'Physical Training: Save'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SAVE_COMMA, 10, 'Physical Training: Save'));

        // 2d6 HPs
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::HIT_POINTS, new Roll('Physical Training: Hit points Bonus', 2, 6), 'Physical Training: Hit Points Bonus'));

        // 3d4 X 10 SDC
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::SDC, new Roll('Physical Training: SDC Bonus', 3, 4, 10), 'Physical Training: SDC Bonus'));

        // +1 attack per melee
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::ATTACKS_PER_MELEE, 1, 'Physical Training: Extra attacks'));

        // special powers
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Power Punch - 3D6 damage', 'Physical Training: Special Power'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Power Kick - 4D6 damage', 'Physical Training: Special Power'));
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::DESCRIPTION, 'Force of Will - Stay on one\'s feet even after all SDC and hit points have been reduced to zero or below.', 'Physical Training: Special Power'));

        // 4d6 X 100 dollars starting cash
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_ADD, BonusTargets::MONEY, new Roll('Physical Training: Bonus Money', 4, 6, 100), 'Physical Training: Bonus Money'));

        // 89% owns car : 1d6 years old
        $this->hasCar($hero, 89);

        // base SDC of 30
        $hero->addBonus(new Bonus(Bonus::BONUS_TYPE_SET, BonusTargets::SDC, 30, 'Physical Training: Base SDC'));
    }
}
