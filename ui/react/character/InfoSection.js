import React from "react";
import PropTypes from "prop-types";

class InfoDetail extends React.Component {
	render() {
		return (
			<div className="infoDetailContainer">
				<div key="label" className="infoLabel">{this.props.label}:</div>
				<div key="value" className={`infoValue monospace ${this.props.size}`}>{this.props.value}</div>
			</div>
		);
	}
}

InfoDetail.propTypes = {
	label: PropTypes.string.isRequired,
	value: PropTypes.string.isRequired,
	size: PropTypes.string.isRequired,
};




export default class InfoSection extends React.Component {

	render() {
		return (
			<div className="infoContainer">
				<div key="infos" className="infoContainerInfos">
					{this.props.infos.map(i => <InfoDetail key={i.name} label={i.name} value={this.props.character[i.id] + ''} size={i.size ? i.size : InfoSection.SIZE.MEDIUM}/>)}
				</div>
				<div key="background" className="infoContainerBackground">{this.props.title}</div>
			</div>
		);
	}
}

InfoSection.SIZE = {
	SMALL: 'small',
	MEDIUM: 'medium',
	LARGE: 'large',
	FULL: 'full',
};

InfoSection.propTypes = {
	// ==== DATA ==== //
	// character being shown
	character: PropTypes.object.isRequired,

	// infos to show
	infos: PropTypes.array.isRequired,

	// title to show in the background
	title: PropTypes.string.isRequired,
};
