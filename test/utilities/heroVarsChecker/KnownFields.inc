<?php

namespace Heroes\tests\utilities\HeroVarsChecker;


abstract class KnownFields
{
	private static $fields;

	public static function fields()
	{
		if (!KnownFields::$fields) {
			KnownFields::$fields = KnownFields::setupFields();
		}
		return KnownFields::$fields;
	}

	private static function setupFields()
	{
		return array_merge(
			[
				'abilities.bonuses.isApplied',
				'abilities.bonuses.bonusType',
				'abilities.bonuses.bonusTarget',
				'abilities.bonuses.value',
				'abilities.bonuses.explanation',

				'abilities.cost',
				'abilities.description',
				'abilities.name',
				'abilities.title',

				'age',
				'alignment',
				'appearance',
				'attacksPerMelee',
				'balanceWalkTightrope',
				'birthOrder',

				// Bonuses: isApplied not shown
				'bonuses.isApplied',
				'bonuses.bonusType',
				'bonuses.bonusTarget',
				'bonuses.value',
				'bonuses.explanation',

				'carryThrowWeight',
				'charmImpress',

				'class',
				'class.classType',
				'class.classSubtype',

				// --- Alien --- //
				'class.appearance',
				'class.earthClothesDisguise',
				'class.magic.classType',
				'class.magic.enchantedWeaponDamage',
				'class.magic.enchantedWeaponType',
				'class.magic.objectSpellLevel',
				'class.magic.objectSpells',
				'class.magic.objectSpellsPerDay',
				'class.magic.physicalLimitation',
				'class.magic.spellsKnown.*',
				'class.magic.spellsPerDay',
				'class.familiarity',
				'class.magic.classSubtype',
				'class.physiologicalModification',
				'class.reasonForComing',
				'class.robotics.*',
				'class.specialWeapon',
				'class.vehicle',

				// --- Bionics --- //
				'class.bionicBody.*',
				'class.bionics.*',
				'class.budgetRemaining',
				'class.conditions',
				'class.startingBudget',

				// --- Experiment --- //
				'class.experimentNature',
				'class.experimentResults',
				'class.sponsor',
				'class.sponsorStatus',

				// --- Hardware --- //
				'class.equipmentBudget',
				'class.mechanicalSponsorStatus',
				'class.workshopBudget',

				// --- Magic --- //
				'class.physicalLimitation',
				'class.spellsPerDay',
				'class.objectSpellLevel',
				'class.objectSpellsPerDay',

				// ------ Enchanted Object ------ //
				'class.objectSpells.description',
				'class.objectSpells.duration',
				'class.objectSpells.range',
				'class.objectSpells.savingThrow',
				'class.objectSpells.title',

				// ------ Enchanted Weapon ------ //
				'class.enchantedWeaponDamage',
				'class.enchantedWeaponType',

				// ------ Magician/Wizard Spells ----- //
				'class.spellsKnown.description',
				'class.spellsKnown.duration',
				'class.spellsKnown.range',
				'class.spellsKnown.savingThrow',
				'class.spellsKnown.title',

				// ----- Mutants ----- //
				'class.animalSize',
				'class.animalPsionics.*',
				'class.cause',
				'class.characteristics',
				'class.isp',
				'class.organization',
				'class.organizationRelationship',
				'class.wildEducationDescription',
				'class.animal.bonuses.*',
				'class.animal.buildType',
				'class.animal.description',
				'class.animal.initialSize',
				'class.animal.name',
				'class.animal.startingBioE',
				'class.animalFeatures.Biped.*',
				'class.animalFeatures.Flight.*',
				'class.animalFeatures.Hands.*',
				'class.animalFeatures.Horns.*',
				'class.animalFeatures.Looks.*',
				'class.animalFeatures.Natural Bite.*',
				'class.animalFeatures.Natural Body Armor.*',
				'class.animalFeatures.Natural Claw.*',
				'class.animalFeatures.Natural Teeth.*',
				'class.animalFeatures.Natural Weapons.*',
				'class.animalFeatures.Powers.*',
				'class.animalFeatures.Speech.*',
				'class.animalFeatures.Teeth.*',
				'class.animal.buyableFeatures.*',

				// ------ Psionics ----- //
				'class.psionics',
				'class.ispPoints',
				'psionics.title',
				'psionics.range',
				'psionics.duration',
				'psionics.isp',
				'psionics.savingThrow',
				'psionics.description',

				// ------ Robotics ------ //
				'class.robot.*',
			],
			KnownFields::robotField('robotAI'),
			KnownFields::robotField('requiresAI'),
			KnownFields::robotField('requiresPilot'),
			KnownFields::robotField('robotAIDescription'),
			KnownFields::robotField('robotAIPersonality'),
			KnownFields::robotField('robotArms'),
			KnownFields::robotField('robotArmsInterchangeableHands'),
			KnownFields::robotField('robotBody'),
			KnownFields::robotField('robotBodyAddOns'),
			KnownFields::robotField('robotEngine'),
			KnownFields::robotField('robotNumberLegs'),
			KnownFields::robotField('robotOptions'),
			KnownFields::robotField('robotPowerSupply'),
			KnownFields::robotField('robotSuperiority'),
			[
				// ------ Secret Operative ------ //
				'class.sponsoringOrganization',
				'class.sponsoringOrganizationStatus',

				'damageBonus',
				'disposition',
				'dodge',
				'educationLevel',
				'educationProgramsPicked',
				'environment',
				'gender',
				'height',
				'hitPoints',
				'imitateVoices',
				'initiativeBonus',
				'intelligenceQuotient',
				'iq',
				'landOfOrigin',
				'liftWeight',
				'maintainGripHoldFooting',
				'mentalAffinity',
				'mentalEndurance',
				'money',
				'naturalArmor',
				'parry',
				'physicalBeauty',
				'physicalEndurance',
				'physicalProwess',
				'physicalStrength',
				'pullPunch',
				'recognizeIdentifyPlants',
				'roll',
				'rollWithPunch',
				'runsMilesPerHour',
				'saveChemicals',
				'saveComma',
				'saveControlOthers',
				'saveDeath',
				'saveEnchantments',
				'saveGases',
				'saveIllusions',
				'saveMagic',
				'saveMindAlteringEffects',
				'savePoison',
				'savePossession',
				'savePsionicAttackInsanity',
				'savePsionicMindControl',
				'savePsionics',
				'saveSpells',
				'saveToxins',
				'sdc',
				'skillTotals.*',
				'socialEconomic',
				'speed',
				'strike',
				'trustIntimidate',
				'understandOperateAlienMachines',
				'weight',
				'weightDescription',
				'whenManifested',

				// not shown fields
				'descriptions',
				'intelligenceQuotientBase',
				'mentalAffinityBase',
				'mentalEnduranceBase',
				'physicalBeautyBase',
				'physicalEnduranceBase',
				'physicalProwessBase',
				'physicalStrengthBase',
				'speedBase',
			],

			// fields for php side that js didn't need
			[
				'class.magic',
				'class.animal',
				'class.animalFeatures',
				'class.animalFeatures.*',
				'class.objectSpells',
				'class.spellsKnown',
			]
		);
	}

	/**
	 * @param string $field give robot fields
	 * @return array
	 */
	private static function robotField(string $field)
	{
		return [
			$field,
			"class.$field",
			"class.robot.$field",
		];
	}
}
