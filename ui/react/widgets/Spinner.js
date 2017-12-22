import React from "react";

export default class Lock extends React.Component {

	render() {
		return (
			<div>
				<div key="background" className="spinnerBackground"></div>
				<div key="spinner" className="spinner"></div>
			</div>
		);
	}
}

Lock.propTypes = {
};
