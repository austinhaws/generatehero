import React from "react";
import {render} from "react-dom";
import {connect, Provider} from "react-redux";
import store from "../redux/Store";
import App from "../app/App";
import Attribute from "./Attribute";

// ==== setup react container for the report ==== //
class CharacterClass extends React.Component {

	render() {
		return (
			<div id="characterContainer">
				<div id="topContainer">
					<div id="topContainerLeft">
						<input type="text" name="Name" placeholder="Name" value=""/>
					</div>
					<div id="topContainerRight">
						<a href="#" className="button">Generate</a>
						<img src="img/gears.svg" title="Settings" className="gearsImage"/>
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
};

const Character = connect(
	state => state,
	dispatch => { return {
		// openRequisition: requisition => dispatch({type: reducers.ACTION_TYPES.SET_VIEWING_REQUISITION, payload: requisition}),
	}},
)(CharacterClass);

render(<Provider store={store}><App><Character/></App></Provider>, document.getElementById('react'));
