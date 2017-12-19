import React from "react";
import {render} from "react-dom";
import {connect, Provider} from "react-redux";
import store from "../redux/Store";
import App from "../app/App";

// ==== setup react container for the report ==== //
class CharacterClass extends React.Component {

	render() {
		return <div>Hello World!</div>;
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
