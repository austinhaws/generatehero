import React from "react";
import clone from "clone";

export default {
	ACTION_TYPES: {
		// set ajaxing start/stop
		SET_AJAXING: 'SET_AJAXING',

		// set the currently viewed character
		SET_CHARACTER: 'SET_CHARACTER',

		// toggle a lock open/closed
		TOGGLE_LOCK: 'TOGGLE_LOCK',
	},
	ACTIONS: {
		// reducer: update ajaxing count
		// payload: boolean true for an ajax began, false an ajax ended
		SET_AJAXING: (state, action) => {
			const result = clone(state);
			result.ajaxingCount += action.payload ? 1 : -1;
			return result;
		},

		// reducer: set currently viewed character
		// payload: the character to view
		SET_CHARACTER: (state, action) => {
			const result = clone(state);
			result.character = clone(action.payload);
			return result;
		},

		// reducer: toggle lock open/closed
		// payload: id of the lock to toggle
		TOGGLE_LOCK: (state, action) => {
			const result = clone(state);
			result.locks[action.payload] = !result.locks[action.payload];
			return result;
		}
	},
};