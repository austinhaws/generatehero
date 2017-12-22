import axios from 'axios';

function axiosGeneric(method, url, data, callback) {
	axios[method](url, data)
		.then(callback)
		.catch(console.error.bind(console))
}

export default {
	consts: {

	},
	functions: {
		ajaxGet: (url, callback) => {
			axiosGeneric('get', url, undefined, callback);
		},
		ajaxPost: (url, data, callback) => {
			axiosGeneric('post', url, data, callback);
		},
	},
};
