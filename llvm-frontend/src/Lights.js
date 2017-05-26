import React, {Component} from 'react';
import FloatingActionButton from 'material-ui/FloatingActionButton';
import ContentAdd from 'material-ui/svg-icons/content/add';
import AppBar from 'material-ui/AppBar';
import {List, ListItem} from 'material-ui/List';
import Toggle from 'material-ui/Toggle';
import Divider from 'material-ui/Divider';
import TextField from 'material-ui/TextField';
import IconButton from 'material-ui/IconButton';
import ContentSave from 'material-ui/svg-icons/content/save';
import NavigationClose from 'material-ui/svg-icons/navigation/close';
import NavigationArrowBack from 'material-ui/svg-icons/navigation/arrow-back';
import {Link} from 'react-router-dom';
import {GridList, GridTile} from 'material-ui/GridList';
import DropDownMenu from 'material-ui/DropDownMenu';
import MenuItem from 'material-ui/MenuItem';
import LLVMPreview from './LLVMPreview';

const NewLight = (props) => (
  <div>
    <AppBar
      title="New Light"
      iconElementLeft={<IconButton onTouchTap={() => props.history.goBack()}><NavigationClose /></IconButton>}
      iconElementRight={<IconButton onTouchTap={() => props.history.goBack()}> <ContentSave /> </IconButton>}
    />
    <form style={{marginLeft: 16, marginRight: 16}}>
      <div>
        <TextField
          style={{width: "100%"}}
          floatingLabelText="Name"
          hintText="Living Room"
        />
      </div>
      <div>
        <TextField
          style={{width: "100%"}}
          floatingLabelText="Address"
          hintText="living.casa136.local"
        />
      </div>
    </form>
  </div>
);


const Light = (props) => (
  <div>
    <AppBar
      title="Living Room"
      iconElementLeft={<IconButton onTouchTap={() => props.history.goBack()}><NavigationArrowBack /></IconButton>}
      iconElementLeft={<IconButton onTouchTap={() => props.history.goBack()}><NavigationArrowBack /></IconButton>}
    />
    <List>
        <ListItem
          primaryText="Power"
          rightToggle={<Toggle />}
        />
    </List>
    <DropDownMenu style={{width:"100%"}} value={1}>
      <MenuItem label="Cycle" value={1}><img style={{width: "320px"}} src="/images/cycle.jpg" /></MenuItem>
      <MenuItem label="Funky" value={2}><img style={{width: "320px"}} src="/images/cycle.jpg" /></MenuItem>
      <MenuItem label="lol" value={3}><img style={{width: "320px"}} src="/images/cycle.jpg" /></MenuItem>
      <MenuItem label="derp" value={4}><img style={{width: "320px"}} src="/images/cycle.jpg" /></MenuItem>
    </DropDownMenu>
    <LLVMPreview width={200}  height={200} />
  </div>
);

class Lights extends Component {
  render() {
    const fabStyle = {
      margin: 16,
      top: 'auto',
      right: 0,
      bottom: 0,
      left: 'auto',
      position: 'fixed'
    };
    return (
      <div>
        <AppBar title="Lights" />
        <FloatingActionButton style={fabStyle} containerElement={<Link to="/newlight" />}>
          <ContentAdd />
        </FloatingActionButton>
        <List>
          <Divider />
          <ListItem
            containerElement={<Link to="/lights/living.casa136.local" />}
            primaryText="Living Room"
            secondaryText="living.casa136.local"
          />
          <Divider />
          <ListItem
            containerElement={<Link to="/lights/bed.casa136.local" />}
            primaryText="Bed Room"
            secondaryText="bed.casa136.local"
          />
          <Divider />
        </List>
      </div>
    );
  }
}

export {NewLight, Light, Lights};
