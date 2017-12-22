import React from "react";
import PropTypes from "prop-types";
import Lock from "../widgets/Lock";

export default class Attribute extends React.Component {

	render() {
		return (
			<div className="attributeContainer">
				<div className="attributeName">{this.props.name}</div>
				<div className="attributeValue">{this.props.value}</div>
				<Lock locked={false} onToggle={() => this.props.toggleLocked(this.props.name)}/>
				<div className="attributeBase">{`${this.props.baseValue} + ${this.props.value - this.props.baseValue}`}</div>
			</div>
		);
	}
}

Attribute.propTypes = {
	// ==== DATA ==== //
	// name of the attribute
	name: PropTypes.string.isRequired,

	// value to show in the attribute
	value: PropTypes.number.isRequired,

	// the base value of the attribute (w/o bonuses added)
	baseValue: PropTypes.number.isRequired,

	// is this value locked so that it won't change?
	locked: PropTypes.bool.isRequired,


	// ==== CALLBACKS ==== //
	// the lock has been toggled : (attributeName) => {}
	toggleLocked: PropTypes.func.isRequired,
};
