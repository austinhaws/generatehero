import React from "react";
import {createStore} from "redux";
import reducers from "./Reducers";

const store = createStore((state, action) => {
		// === reducers ===
		let reducer = false;

		// is reducer valid?
		if (action.type in reducers) {
			reducer = reducers[action.type];
		}

		// ignore redux/react "system" reducers
		if (!reducer && action.type.indexOf('@@') !== 0) {
			console.error('unknown reducer action:', action.type, action)
		}

		// DO IT!
		return reducer ? reducer(state, action) : state;
	}, {
		// === default data ===
		// how many ajax requests are currently in progress
		ajaxingCount: 0,

		// current hero being viewed
		hero: undefined,
	}
);
export default store;