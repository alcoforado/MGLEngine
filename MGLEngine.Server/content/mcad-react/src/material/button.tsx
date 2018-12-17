import React, { Component } from 'react';
import classnames from 'classnames';
import ReactDOM from 'react-dom'
import "./button.scss"

interface IButtonProp {
    className?:any,
    appearance?: ButtonType,
    href?:string,
    
}

export  enum ButtonType {
    Flat="Flat",
    Full="Full",
    Text="Text",
    Outlined="Outlined"
}


interface IButtonState {
}


export class Button extends Component<IButtonProp,IButtonState> {
    private _classes:string;
    private _rippleEl:React.RefObject<any>;
    private t:any;
    constructor(props:IButtonProp){
        super(props);
        this._rippleEl = React.createRef();
        this._classes = classnames('mdc-button', props.className, {
            'mdc-button--raised': props.appearance === ButtonType.Full || props.appearance===undefined,
            'mdc-button--unelevated': props.appearance === ButtonType.Flat,
            'mdc-button--outlined': props.appearance == ButtonType.Outlined,
          });
    }
    componentDidMount(){
        var node = ReactDOM.findDOMNode(this);
        const surface = document.querySelector('.mdc-button');
    }


    clicked(event: any) {
  
    }


   
render() {
        const SemanticButton = this.props.href ? 'a' : 'button';

        return (
        <button type="button" className="mdc-button mdc-button--raised"> 
            {this.props.children}
            <div className="mdc-button-overlay"></div>
        </button>)

      
     
    }
}  