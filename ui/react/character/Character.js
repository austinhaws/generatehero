import React from "react";
import {render} from "react-dom";
import {connect, Provider} from "react-redux";
import store from "../redux/Store";
import App from "../app/App";
import Attribute from "./Attribute";
import shared from "../app/Shared";
import reducers from "../redux/Reducers";
import PropTypes from "prop-types";

// ==== setup react container for the report ==== //
class CharacterClass extends React.Component {

	componentDidMount() {
		shared.functions.ajaxGet('src/generate.php', response => this.props.setCharacter(response.data));
	}

	render() {
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
						<Attribute name="Intel Quotient" value={17} locked={false} baseValue={13} toggleLocked={attributeName => console.log('toggling lock for' + attributeName)} />
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
	character: PropTypes.object.isRequired,

	// == callbacks == //
	setCharacter: PropTypes.func.isRequired,
};

const Character = connect(
	state => state,
	dispatch => { return {
		setCharacter: character => dispatch({type: reducers.ACTION_TYPES.SET_CHARACTER, payload: character}),
	}},
)(CharacterClass);

render(<Provider store={store}><App><Character/></App></Provider>, document.getElementById('react'));
