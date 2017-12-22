import axios from 'axios';
import store from "../redux/Store";
import reducers from "../redux/Reducers";

const shared = {
	consts: {

	},
	functions: {
		startAjaxing: () => store.dispatch({type: reducers.ACTION_TYPES.SET_AJAXING, payload: true}),
		stopAjaxing: () => store.dispatch({type: reducers.ACTION_TYPES.SET_AJAXING, payload: false}),

		axiosGeneric: (method, url, data, callback) => {
			shared.functions.startAjaxing();
			axios[method](url, data)
				.then(response => {
					shared.functions.stopAjaxing();
					callback(response);
				})
				.catch(error => {
					shared.functions.stopAjaxing();
					console.error(error);
				});
		},

		ajaxGet: (url, callback) => {
			shared.functions.axiosGeneric('get', url, undefined, callback);
		},
		ajaxPost: (url, data, callback) => {
			shared.functions.axiosGeneric('post', url, data, callback);
		},
	},
};

export default shared;
