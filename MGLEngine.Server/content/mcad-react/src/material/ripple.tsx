import React, { Component } from 'react';
import classnames from 'classnames';
import ReactDOM from 'react-dom'



class IRippleState {
    top:string =  "0" 
    left:string="0"
    width:string ="0px"
    height:string = "0px"
}

interface IRippleProp {
    
}


export class Ripple extends Component<IRippleProp,IRippleState> {
    
    private _rippleRef:React.RefObject<any>;


    constructor(props:IRippleProp){
        super(props);
        this.setState(new IRippleState());
        this._rippleRef=React.createRef();
    }
    componentDidMount(){
        var node = ReactDOM.findDOMNode(this);
    }

    getRippleElement():HTMLElement{
        return this._rippleRef.current;
    }

    clicked(event: any) {
        var d: number = Math.max(this.getRippleElement().offsetWidth, this.getRippleElement().offsetHeight) * 2;
        
        var state = new IRippleState();
        state.width = + d + 'px';
        state.left = (event.pageX - this.getRippleElement().offsetLeft - d / 2) + 'px';
        state.top = (event.pageY - this.getRippleElement().offsetTop - d / 2) + 'px';
        state.height = state.width;
        this.setState(state);
    }

   
render() {

    return (
    <div ref={this._rippleRef} className='material-ripple' style={this.state}></div>
    );
    }
}  