import React, { Component } from 'react';
import logo from './logo.svg';
import './App.scss';

import { Button } from './material/button';
import { AppBar } from './material/appbar';
import {ShapeForm} from './app/shape-form'

class App extends Component {
  render() {
    return (
      <div className="App">
        <AppBar>
          <a href="#" className="material-icons mdc-top-app-bar__action-item" aria-label="Download" >save_alt</a>
        </AppBar>
        <ShapeForm title="hello world">

        </ShapeForm>
        <Button raised className='button-alternate' >
          Click Me!
        </Button>
        <i className="material-icons">face</i>
        <header className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <p>
            Edit <code>src/App.tsx</code> and save to load.
          </p>
          <a
            className="App-link"
            href="https://reactjs.org"
            target="_blank"
            rel="noopener noreferrer"
          >
            Learn React
          </a>
        </header>


      </div>
    );
  }
}

export default App;
