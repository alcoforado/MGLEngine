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

export class Button extends Component<IButtonProp,any> {
    private _classes:string;

    constructor(props:IButtonProp){
        super(props);
        
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

    
   
render() {
        const SemanticButton = this.props.href ? 'a' : 'button';

        return (
          <SemanticButton  className={this._classes}>
            {this.props.children}
          </SemanticButton>
        );
      
     
    }
}  