import React from "react";
import PropTypes from "prop-types";
import Lock from "../widgets/Lock";

export default class Attribute extends React.Component {

	render() {
		return (
			<div className="attributeContainer">
				{this.props.name.split(' ').map(word => {
					return (
						<div key={`word${word}`} className="verticalWord">{
							word.split('')
							.reduce((all, letter) => {
								return all === null ? [letter] : [...all, <br key={all.length}/>, letter];
							}, null)
						}</div>
					);
				})}
				<div className="attributeValueContainer">
					<div className="attributeValue monospace">{this.props.value}</div>
					<svg className="attributeEllipse" viewBox="0 0 120 120"><ellipse cx="60" cy="60" rx="40" ry="59" fill="none" stroke="#eee" strokeWidth="2"/></svg>
				</div>
				<Lock locked={this.props.locked} onToggle={this.props.toggleLocked}/>
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
