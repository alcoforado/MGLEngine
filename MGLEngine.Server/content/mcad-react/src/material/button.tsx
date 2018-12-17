import React, { Component } from 'react';
import classnames from 'classnames';
import ReactDOM from 'react-dom'
import { AsyncResource } from 'async_hooks';


interface IButtonProp {
    className?:any,
    raised?:boolean,
    unelevated?:boolean,
    outlined?:boolean,
    dense?:boolean,
    children?:any,
    unbounded?:boolean,
    href?:string
}


interface IButtonState {
}


export class Button extends Component<IButtonProp,IButtonState> {
    private _classes:string;
    private _rippleEl:React.RefObject<any>;

    constructor(props:IButtonProp){
        super(props);
        this._rippleEl = React.createRef();
        this._classes = classnames('mdc-button', props.className, {
            'mdc-button--raised': props.raised,
            'mdc-button--unelevated': props.unelevated,
            'mdc-button--outlined': props.outlined,
            'mdc-button--dense': props.dense,
            'mdc-ripple-surface':true
          });
    }
    componentDidMount(){
        var node = ReactDOM.findDOMNode(this);
    }


    clicked(event: any) {
  
    }

   
render() {
        const SemanticButton = this.props.href ? 'a' : 'button';

        return (<button type="button" className={this._classes}>
            {this.props.children}
            <div className="mdc-button-overlay"></div>
        </button>)

      
     
    }
}  