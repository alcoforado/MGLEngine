import React, { Component } from 'react';
import classnames from 'classnames';
import ReactDOM from 'react-dom'



class RippleStyle {
    top:string =  "0" 
    left:string="0"
    width:string ="0px"
    height:string = "0px"
    constructor(){}
}
interface IRippleState {
    style: RippleStyle;
    animState: AnimStateCss;
}

interface IRippleProp {
    
}

enum AnimStateCss {
    NEVER_PRESSED="material-ripple",
    PRESSED_1="material-ripple active-0",
    PRESSED_2="material-ripple active-1"
}

export class Ripple extends Component<IRippleProp,IRippleState> {
    
    private _rippleRef:React.RefObject<HTMLDivElement>;


    constructor(props:IRippleProp){
        super(props);
        this.state = {
            style: new RippleStyle(),
         animState: AnimStateCss.NEVER_PRESSED
        };
        this._rippleRef=React.createRef();
    }
    componentDidMount(){
        var node = ReactDOM.findDOMNode(this);
    }

    getRippleElement():HTMLElement{
        return this._rippleRef.current.parentElement;
    }

    clicked(event: React.MouseEvent<HTMLButtonElement>) {
       
        var d: number = Math.max(this.getRippleElement().offsetWidth, this.getRippleElement().offsetHeight)*2;
    
        var style = new RippleStyle();
        style.width = + d + 'px';
        style.left = (event.pageX - this.getRippleElement().offsetLeft - d / 2) + 'px';
        style.top = (event.pageY - this.getRippleElement().offsetTop - d / 2) + 'px';
        style.height = style.width;

        var newAnimState:AnimStateCss=null;
        if (this.state.animState == AnimStateCss.NEVER_PRESSED || this.state.animState == AnimStateCss.PRESSED_2)
        {
            newAnimState=AnimStateCss.PRESSED_1;
        }
        else
        {
            newAnimState = AnimStateCss.PRESSED_2;
        }


        this.setState({
            style: style,
            animState:newAnimState
        });
        }
    render() {

    return (
    <div ref={this._rippleRef} className={this.state.animState} style={this.state.style}></div>
    );
    }
}  