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
                <header className="mdc-top-app-bar">
                    <div className="mdc-top-app-bar__row">
                        <section className="mdc-top-app-bar__section mdc-top-app-bar__section--align-start">
                            <a href="#" className="material-icons mdc-top-app-bar__navigation-icon">menu</a>
                            <span className="mdc-top-app-bar__title">Title</span>
                        </section>
                        <section className="mdc-top-app-bar__section mdc-top-app-bar__section--align-end" role="toolbar">
                            {this.props.children}
                        </section>
                    </div>
                </header>
            </div>
        );
      
     
    }
}  