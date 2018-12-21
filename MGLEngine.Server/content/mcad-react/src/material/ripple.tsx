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
    isActive: boolean;
}

interface IRippleProp {
    
}


export class Ripple extends Component<IRippleProp,IRippleState> {
    
    private _rippleRef:React.RefObject<HTMLDivElement>;


    constructor(props:IRippleProp){
        super(props);
        this.state = {
            style: new RippleStyle(),
            isActive: false
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
        //debugger;
        if (this.state.isActive)
        {
            this.setState({
                isActive: false
            },()=>this.clicked((Object as any).assign({},event)));

        }
        else
        {
        var d: number = Math.max(this.getRippleElement().offsetWidth, this.getRippleElement().offsetHeight)*2;
    
        var style = new RippleStyle();
        style.width = + d + 'px';
        style.left = (event.pageX - this.getRippleElement().offsetLeft - d / 2) + 'px';
        style.top = (event.pageY - this.getRippleElement().offsetTop - d / 2) + 'px';
        style.height = style.width;
        this.setState({
            style: style,
            isActive: true
        });
        }
    }

   
render() {

    return (
    <div ref={this._rippleRef} className={'material-ripple ' + (this.state.isActive ? 'active' : '')} /*style={this.state.style}*/ ></div>
    );
    }
}  