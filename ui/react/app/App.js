import React from "react";
import {Redirect, Route, Switch} from 'react-router';
import {BrowserRouter} from 'react-router-dom'
import Character from '../character/Character';
import {connect, Provider} from "react-redux";
import {render} from "react-dom";
import store from "../redux/Store";
import PropTypes from "prop-types";
import Spinner from "../widgets/Spinner";

// ==== setup react container for the report ==== //
class AppClass extends React.Component {

	render() {
		return (
			<BrowserRouter basename="/heroes/ui/">
				<div id="app">
					<div id="app-header">
						<div id="app-title">Hero Generator</div>
						<div id="sub-title"><a href="http://strategerygames.com">Strategery Games</a></div>
						<div id="app-menu"><a href="#">Go Somewhere</a><a href="#">Go Elsewhere</a><a href="#">Go Nowhere</a></div>
					</div>
					<div id="app-content">
						<Switch>
							<Route path="/character" component={Character}/>
							<Route exact path="/" render={() => <Redirect to="character"/>}/>
						</Switch>
						{this.props.children}
						{this.props.ajaxingCount ? <Spinner/> : undefined}
					</div>
				</div>
			</BrowserRouter>
		);
	}
}

AppClass.PropTypes = {
	ajaxingCount: PropTypes.number.isRequired,
};

const App = connect(
	state => state,
	dispatch => {return {};},
)(AppClass);


render(<Provider store={store}><App/></Provider>, document.getElementById('react'));