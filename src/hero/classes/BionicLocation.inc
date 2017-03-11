<?php
namespace Heroes\hero\classes;

class BionicLocation
{
    const BODY_PART_ARM_LEFT = 'left arm';
    const BODY_PART_ARM_RIGHT = 'right arm';
    const BODY_PART_CHEST_RIBS = 'chest/ribs';
    const BODY_PART_EAR_LEFT = 'left ear';
    const BODY_PART_EAR_RIGHT = 'right ear';
    const BODY_PART_EYE_LEFT = 'left eye';
    const BODY_PART_EYE_RIGHT = 'right eye';
    const BODY_PART_FOOT_LEFT = 'left foot';
    const BODY_PART_FOOT_RIGHT = 'right foot';
    const BODY_PART_HAND_LEFT = 'left hand';
    const BODY_PART_HAND_RIGHT = 'right hand';
    const BODY_PART_HEART = 'heart';
    const BODY_PART_KIDNEY = 'kidney';
    const BODY_PART_LEG_LEFT = 'left leg';
    const BODY_PART_LEG_RIGHT = 'right leg';
    const BODY_PART_LUNGS = 'lungs';
    const BODY_PART_MOUTH_THROAT = 'mouth/throat';
    const BODY_PART_SKULL_FACE = 'skull/face';

    public $andLocations;
    public $orLocations;
    public $orMultiplePossible;
    public $fillsLocation;

    /**
     * BionicLocationInfo constructor.
     * if both andLocations and orLocations are false then this bionic requires no bionic body parts and can be placed anywhere (fillsLocation should be false too)
     * if all four parameters are false then the bionic part does not go to a specific location (armor is like this)
     *
     * @param $andLocations array|bool locations that this bionic will be placed in; or false if not used
     * @param $orLocations array|bool locations in which the bionic could be placed (pick one); or false if not used
     * @param $orMultiplePossible bool if true then when choosing from "or" locations, also have option of choosing multiple of the locations and installing this bionic multiple times
     * @param $fillsLocation bool the picked location(s) can not have any other bionics in it
     */
    public function __construct($andLocations, $orLocations, $orMultiplePossible, $fillsLocation)
    {
        $this->andLocations = $andLocations;
        $this->orLocations = $orLocations;
        $this->orMultiplePossible = $orMultiplePossible;
        $this->fillsLocation = $fillsLocation;
    }

    public static function ALL_LOCATIONS()
    {
        return [
            BionicLocation::BODY_PART_ARM_LEFT,
            BionicLocation::BODY_PART_ARM_RIGHT,
            BionicLocation::BODY_PART_CHEST_RIBS,
            BionicLocation::BODY_PART_EAR_LEFT,
            BionicLocation::BODY_PART_EAR_RIGHT,
            BionicLocation::BODY_PART_EYE_LEFT,
            BionicLocation::BODY_PART_EYE_RIGHT,
            BionicLocation::BODY_PART_FOOT_LEFT,
            BionicLocation::BODY_PART_FOOT_RIGHT,
            BionicLocation::BODY_PART_HAND_LEFT,
            BionicLocation::BODY_PART_HAND_RIGHT,
            BionicLocation::BODY_PART_HEART,
            BionicLocation::BODY_PART_KIDNEY,
            BionicLocation::BODY_PART_LEG_LEFT,
            BionicLocation::BODY_PART_LEG_RIGHT,
            BionicLocation::BODY_PART_LUNGS,
            BionicLocation::BODY_PART_MOUTH_THROAT,
            BionicLocation::BODY_PART_SKULL_FACE,
        ];
    }
}
