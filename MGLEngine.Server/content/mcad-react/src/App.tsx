import React, { Component } from 'react';
import logo from './logo.svg';
import './App.scss';

import { Button } from './material/button';
import { AppBar } from './material/appbar';
import {ShapeForm} from './app/shape-form'

class App extends Component {
  render() {
    return (
      <>
        <AppBar>
          <a href="#" className="material-icons mdc-top-app-bar__action-item" aria-label="Download" >save_alt</a>
        </AppBar>
        <p>Hello World</p>
      </>
    );
  }
}

export default App;
