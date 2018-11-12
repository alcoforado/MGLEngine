import React, { Component } from 'react';
import classnames from 'classnames';
import "./button.scss";
import * as mdcRiple from "@material/ripple"


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
    
   
render() {
        const SemanticButton = this.props.href ? 'a' : 'button';

        return (
          <SemanticButton className={this._classes}>
            {this.props.children}
          </SemanticButton>
        );
      
     
    }
}  