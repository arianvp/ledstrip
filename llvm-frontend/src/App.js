import React from 'react';

import darkBaseTheme from 'material-ui/styles/baseThemes/darkBaseTheme';
import lightBaseTheme from 'material-ui/styles/baseThemes/lightBaseTheme';
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider';
import getMuiTheme from 'material-ui/styles/getMuiTheme';

import {
  BrowserRouter as Router,
  Route,
  Link
} from 'react-router-dom'

import {NewLight, Light, Lights} from './Lights';

const Routes = (props) => (
  <Router {...props}>
    <div>
      <Route exact path="/"  component={Lights} />
      <Route exact path="/newlight"  component={NewLight} />
      <Route path="/lights/:lightDomain" component={Light} />
    </div>
  </Router>
);
const theme = getMuiTheme(lightBaseTheme);

const AppStyle = {
  position: "absolute",
  width: "100%",
  height: "100%",
  display: "flex",
  flexDirection: "column",
  backgroundColor: theme.palette.canvasColor
};

const App = (props) => (
  <MuiThemeProvider muiTheme={theme}>
    <div style={AppStyle}>
      <Routes />
    </div>
  </MuiThemeProvider>
);

export default App;
