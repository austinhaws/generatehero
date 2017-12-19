import React from "react";

// ==== setup react container for the report ==== //
export default class App extends React.Component {

	render() {
		return (
			<div id="app">
				<div id="app-header">
					<div id="app-title">Hero Generator</div>
					<div id="sub-title"><a href="http://strategerygames.com">Strategery Games</a></div>
					<div id="app-menu"><a href="#">Go Somewhere</a><a href="#">Go Elsewhere</a><a href="#">Go Nowhere</a></div>
				</div>
				<div id="app-content">
					{this.props.children}
				</div>
			</div>
		);
	}
}
