import React from "react";
import {connect} from "react-redux";
import Attribute from "./Attribute";
import shared from "../app/Shared";
import reducers from "../redux/Reducers";
import PropTypes from "prop-types";

// ==== setup react container for the report ==== //
class CharacterClass extends React.Component {

	componentDidMount() {
		if (!this.props.ajaxingCount && !this.props.character) {
			shared.functions.ajaxGet('/heroes/src/generate.php', response => this.props.setCharacter(response.data));
		}
	}

	render() {
		const attributes = [
			{name: 'Intel Quotient', id: 'intelQuotient',},
			{name: 'Mental Endurance', id: 'mentalEndurance',},
			{name: 'Mental Affinity', id: 'mentalAffinity',},
			{name: 'Physical Strength', id: 'physicalStrength',},
			{name: 'Physical Prowess', id: 'physicalProwess',},
			{name: 'Physical Endurance', id: 'physicalEndurance',},
			{name: 'Physical Beauty', id: 'physicalBeauty',},
			{name: 'Speed ', id: 'speed',},
		];
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
				<div id="topTitleContainer">Physical Training</div>

				<div id="middleSectionContainer">
					<div id="characterAttributes">
						{attributes.map(a => <Attribute key={a.id} name={a.name} value={17} locked={!!this.props.locks[a.id]} baseValue={13} toggleLocked={() => this.props.toggleLock(a.id)} />)}
					</div>
					<div id="characterInfoContainers">
						<div id="characterBasics">gender and other basics</div>
						<div id="characterCombat">combat</div>
						<div id="characterSaves">saves</div>
						<div id="characterOther">Other stuff</div>
					</div>
				</div>

				<div id="characterSkillsAbilitiesContainer">
					<div id="characterSkills">Skills go here</div>
					<div id="characterAbilities">Abilities go here</div>
				</div>

				<div id="characterBonusesContainer">
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
