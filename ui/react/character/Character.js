import React from "react";
import {connect} from "react-redux";
import Attribute from "./Attribute";
import shared from "../app/Shared";
import reducers from "../redux/Reducers";
import PropTypes from "prop-types";
import InfoSection from "./InfoSection";

// ==== setup react container for the report ==== //
class CharacterClass extends React.Component {

	componentDidMount() {
		if (!this.props.ajaxingCount && !this.props.character) {
			shared.functions.ajaxGet('/heroes/src/generate.php', response => this.props.setCharacter(response.data));
		}
	}

	render() {
		if (!this.props.character) {
			return false;
		}
		const attributes = [
			{name: 'Intel Quotient', id: 'intelligenceQuotient',},
			{name: 'Mental Endurance', id: 'mentalEndurance',},
			{name: 'Mental Affinity', id: 'mentalAffinity',},
			{name: 'Physical Strength', id: 'physicalStrength',},
			{name: 'Physical Prowess', id: 'physicalProwess',},
			{name: 'Physical Endurance', id: 'physicalEndurance',},
			{name: 'Physical Beauty', id: 'physicalBeauty',},
			{name: 'Speed ', id: 'speed',},
		];

		const infoSections = {
			'Character': [
				{name: 'Alignment', id: 'alignment',},
				{name: 'Gender', id: 'gender',},
				{name: 'Birth Order', id: 'birthOrder',},

				{name: 'Weight', id: 'weightString',},
				{name: 'Height', id: 'height',},
				{name: 'Age', id: 'age',},

				{name: 'Environment', id: 'environment', size: InfoSection.SIZE.LARGE, },
				{name: 'When Manifested', id: 'whenManifested', size: InfoSection.SIZE.LARGE, },

				{name: 'Land of Origin', id: 'landOfOrigin', size: InfoSection.SIZE.LARGE, },
				{name: 'Social Economic', id: 'socialEconomic', size: InfoSection.SIZE.LARGE, },

				{name: 'Disposition', id: 'disposition', size: InfoSection.SIZE.FULL, },
			],
			'Combat': [
				{name: 'HPs', id: 'hitPoints',},
				{name: 'SDC', id: 'sdc',},
				{name: '# Attacks', id: 'attacksPerMelee',},
				{name: 'Parry', id: 'parry',},
				{name: 'Roll', id: 'roll',},
				{name: 'Dodge', id: 'dodge',},
				{name: 'Strike', id: 'strike',},
				{name: 'Pull Punch', id: 'pullPunch',},
				{name: 'Roll With Punch', id: 'rollWithPunch',},
				{name: 'Natural Armor', id: 'naturalArmor',},
				{name: 'Damage', id: 'damageBonus',},
				{name: 'Initiative', id: 'initiativeBonus',},
			],
			'Saves': [
				{name: 'Comma', id: 'saveComma',},
				{name: 'Death', id: 'saveDeath',},
				{name: 'Gases', id: 'saveGases',},
				{name: 'Chemicals', id: 'saveChemicals',},
				{name: 'Control Others', id: 'saveControlOthers',},
				{name: 'Illusions', id: 'saveIllusions',},
				{name: 'Magic', id: 'saveMagic',},
				{name: 'Spells', id: 'saveSpells',},
				{name: 'Enchantments', id: 'saveEnchantments',},
				{name: 'Mind Altering', id: 'saveMindAlteringEffects',},
				{name: 'Poison', id: 'savePoison',},
				{name: 'Possession', id: 'savePossession',},
				{name: 'Psionics', id: 'savePsionics',},
				{name: 'Psionic Attack', id: 'savePsionicAttackInsanity',},
				{name: 'Psionic Control', id: 'savePsionicMindControl',},
				{name: 'Toxins', id: 'saveToxins',},
			],
			'Other': [
				{name: 'Carry / Throw Lbs', id: 'carryThrowWeight',},
				{name: 'Lift Lbs', id: 'liftWeight',},
				{name: 'IQ', id: 'iq',},
				{name: 'Run mph', id: 'runsMilesPerHour',},
				{name: 'Money $', id: 'money',},
				{name: 'Trust / Intimidate', id: 'trustIntimidate',},
				{name: 'Balance Tightrope', id: 'balanceWalkTightrope',},
				{name: 'Charm / Impress', id: 'charmImpress',},
				{name: 'Grip / Footing', id: 'maintainGripHoldFooting',},
				{name: 'Alien Machines', id: 'understandOperateAlienMachines',},
				{name: 'Identify Plants', id: 'recognizeIdentifyPlants',},
				{name: 'Imitate Voices', id: 'imitateVoices',},
				{name: 'Education Level', id: 'educationLevel',},
			],
		};
/*
		crazy = null;
		bonuses = [];
		insanities = [];
		abilities = [];
		psionics = [];
		educationProgramsPicked = [];
		skillTotals;
		descriptions = [];
*/

		return (
			<div id="characterContainer">
				<div id="topContainer">
					<div id="topContainerLeft">
						<input type="text" name="Name" placeholder="Name" value=""/>
					</div>
					<div id="topContainerRight">
						<a href="#" className="button">Generate</a>
						<img src="ui/img/gears.svg" title="Settings" className="gearsImage"/>
					</div>
				</div>
				<div id="topTitleContainer">{this.props.character.class.classType} {this.props.character.class.classSubtype ? [<br key="br"/>, this.props.character.class.classSubtype] : false}</div>

				<div id="middleSectionContainer">
					<div id="characterAttributes">
						{attributes.map(a => <Attribute key={a.id} name={a.name} value={this.props.character[a.id]} locked={!!this.props.locks[a.id]} baseValue={this.props.character[a.id + 'Base']} toggleLocked={() => this.props.toggleLock(a.id)} />)}
					</div>
					<div id="characterInfoContainers">
						{Object.keys(infoSections).map(title => <InfoSection key={title} character={this.props.character} infos={infoSections[title]} title={title}/>)}
					</div>
				</div>

				<div id="bottomSectionContainer">
					<div id="characterSkillsAbilitiesContainer">
						<div id="characterSkills">Skills go here</div>
						<div id="characterAbilities">Abilities go here</div>
					</div>

					<div id="characterBonusesContainer">
					</div>
				</div>
			</div>
		);
	}
}

CharacterClass.propTypes = {
	// == data == //
	ajaxingCount: PropTypes.number.isRequired,
	character: PropTypes.object,
	locks: PropTypes.object.isRequired,

	// == callbacks == //
	setCharacter: PropTypes.func.isRequired,
};

const Character = connect(
	state => state,
	dispatch => { return {
		setCharacter: character => dispatch({type: reducers.ACTION_TYPES.SET_CHARACTER, payload: character}),
		toggleLock: lockName => dispatch({type: reducers.ACTION_TYPES.TOGGLE_LOCK, payload: lockName}),
	}},
)(CharacterClass);

export default Character;
