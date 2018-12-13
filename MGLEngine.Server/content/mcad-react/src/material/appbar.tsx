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
                <nav className="navbar  bg-primary navbar-fixed-top text-light">
                    <div className="container-fluid">
                        <div className="navbar-header">
                            <button  className="material-icons ">menu</button>
                           
                            <a className="navbar-link" href="#">Brand</a>
                        </div>
                    </div>
                </nav>
            </div>
        );
      
     
    }
}  