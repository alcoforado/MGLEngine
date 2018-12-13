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

    clicked(event: any) {
        var d: number = Math.max(this.bt.nativeElement.offsetWidth, this.bt.nativeElement.offsetHeight) * 2;
        this._width = + d + 'px';
        this._x = (event.pageX - this.bt.nativeElement.offsetLeft - d / 2) + 'px';
        this._y = (event.pageY - this.bt.nativeElement.offsetTop - d / 2) + 'px';
        this._ripple = this._ripple == '0' ? '1' : '0';
    }

   
render() {
        const SemanticButton = this.props.href ? 'a' : 'button';

        <button type="button" class="mdc-button {{_class}}" (click)="clicked($event)">
    <div [@ripple]="_ripple" class='material-ripple' [ngStyle]="{'top': _y, 'left':_x, 'width': _width, 'height': _width}"></div>
    <ng-content></ng-content>
    <div class="mdc-button-overlay"></div>
</button>

        return (
          <SemanticButton  className={this._classes}>
            {this.props.children}
          </SemanticButton>
        );
      
     
    }
}  