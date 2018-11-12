import React, { Component } from 'react';
import logo from './logo.svg';
import './App.scss';
import {Button} from './material/button';


class App extends Component {
  render() {
    return (

      

      <div className="App">

      <div>
        <Button
          raised
          className='button-alternate'
          
        >
          Click Me!
        </Button>
      </div>



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
