<?php
namespace Heroes\hero\classes;

class BionicLocation
{
    const BODY_PART_ARM_LEFT = 'Left Arm';
    const BODY_PART_ARM_RIGHT = 'Right Arm';
    const BODY_PART_CHEST_RIBS = 'Chest/Ribs';
    const BODY_PART_EAR_LEFT = 'Left Ear';
    const BODY_PART_EAR_RIGHT = 'Right Ear';
    const BODY_PART_EYE_LEFT = 'Left Eye';
    const BODY_PART_EYE_RIGHT = 'Right Eye';
    const BODY_PART_FOOT_LEFT = 'Left Foot';
    const BODY_PART_FOOT_RIGHT = 'Right Foot';
    const BODY_PART_HAND_LEFT = 'Left Hand';
    const BODY_PART_HAND_RIGHT = 'Right Hand';
    const BODY_PART_HEART = 'Heart';
    const BODY_PART_KIDNEY = 'Kidney';
    const BODY_PART_LEG_LEFT = 'Left Leg';
    const BODY_PART_LEG_RIGHT = 'Right Leg';
    const BODY_PART_LUNGS = 'Lungs';
    const BODY_PART_MOUTH_THROAT = 'Mouth/Throat';
    const BODY_PART_SKULL_FACE = 'Skull/Face';

    // andLocations are the only possible location once a bionic is installed; orlocations is just for when choosing bionics
    public $andLocations;
    // orlocations are not valid once bionic installed; used when choosing bionics to list the possible locations to place the bionic
    public $orLocations;
    // if there are multiple or locations could the bionic be added to the other ones separately too? random chance
    public $orMultiplePossible;
    // the bionic fills the location and doesn't allow any other bionic there; or if there is already a filler at a location then can't add a new bionic there
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

    /**
     * @return array every flippin' bionic body location (note that the rule book doesn't mention feet, but some things are placed on feet)
     */
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
