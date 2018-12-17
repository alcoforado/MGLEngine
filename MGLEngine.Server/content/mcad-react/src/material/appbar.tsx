import React, { Component } from 'react';
import classnames from 'classnames';
import ReactDOM from 'react-dom'
import "@material/top-app-bar/mdc-top-app-bar.scss"

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
<>
    <header className="mdc-top-app-bar " >
      <div className="mdc-top-app-bar__row">
        <section className="mdc-top-app-bar__section mdc-top-app-bar__section--align-start"><button className="material-icons mdc-top-app-bar__navigation-icon"
            >menu</button><span
            className="mdc-top-app-bar__title">Standard</span></section>
        <section className="mdc-top-app-bar__section mdc-top-app-bar__section--align-end"><button className="material-icons mdc-top-app-bar__action-item"
            aria-label="Download" >file_download</button><button
            className="material-icons mdc-top-app-bar__action-item mdc-ripple-upgraded--unbounded mdc-ripple-upgraded"
            aria-label="Print this page" >print</button><button
            className="material-icons mdc-top-app-bar__action-item mdc-ripple-upgraded--unbounded mdc-ripple-upgraded"
            aria-label="Bookmark this page">bookmark</button></section>
      </div>
    </header>
    <div className="mdc-top-app-bar--fixed-adjust"></div>
    
</>)
  /*          
            <div className="appMenu">
                <nav className="navbar  bg-primary navbar-fixed-top text-light">
                    <div className="container-fluid">
                        <div className="appBarnavbar-header">
                            <button  className="material-icons ">menu</button>
                           
                            <a className="navbar-link" href="#">Brand</a>
                        </div>
                    </div>
                </nav>
            </div>
        );
      
     */
    }
}  