import React, { Component } from 'react';
import classnames from 'classnames';
import ReactDOM from 'react-dom'


interface IAppMenuProp {
    className?:any,
}



export class AppBar extends Component<IAppMenuProp,any> {
    private _classes:string;
   
    constructor(props:IAppMenuProp){
        super(props);
        
        this._classes = classnames('mdc-button', props.className, {
          });

    }
    componentDidMount(){
    
    }
render() {
        return (
            <div className="appMenu">
                <nav className="navbar  navbar-dark primary-color">
                            <a href="#" className="material-icons mdc-top-app-bar__navigation-icon">menu</a>
                            <span className="mdc-top-app-bar__title">Title</span>
                </nav>
            </div>
        );
      
     
    }
}  