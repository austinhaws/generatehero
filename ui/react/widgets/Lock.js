import React from "react";
import PropTypes from "prop-types";

export default class Lock extends React.Component {

	render() {
		return (
			<div className={`lock ${this.props.locked ? 'locked' : 'unlocked'}`} onClick={this.props.onToggle}></div>
		);
	}
}

Lock.propTypes = {
	// boolean whether to show the lock locked or unlocked
	locked: PropTypes.bool.isRequired,

	// callback for when the lock is clicked to have it toggled : () => {}
	onToggle: PropTypes.func.isRequired,
};
