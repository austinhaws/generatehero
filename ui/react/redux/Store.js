import React from "react";
import {createStore} from "redux";
import reducers from "./Reducers";

export default createStore((state, action) => {
		// === reducers ===
		let reducer = false;

		// is reducer valid?
		if (action.type in reducers.ACTIONS) {
			reducer = reducers.ACTIONS[action.type];
		}

		// ignore redux/react "system" reducers
		if (!reducer && action.type.indexOf('@@') !== 0) {
			console.error('unknown reducer action:', action.type, action)
		}

		// DO IT!
		return reducer ? reducer(state, action) : state;
	}, {
		// === default data ===
		// != 0 when ajax is in progress and spinner should be shown
		// > 0 when there are ajax requests pending
		ajaxingCount: 0,

		// the currently viewed character
		character: undefined,
	}

	// for chrome redux plugin
	, window.__REDUX_DEVTOOLS_EXTENSION__ && window.__REDUX_DEVTOOLS_EXTENSION__()
);
