import React, { Component } from 'react';
import classnames from 'classnames';
import ReactDOM from 'react-dom'
import { AsyncResource } from 'async_hooks';


interface IShapeFormProp {
    title?:string;

}

export class ShapeForm extends Component<IShapeFormProp,any> {
    
    constructor(props:IShapeFormProp){
        super(props);
        
       

    }
    componentDidMount(){
        
    }

    
   
render() {
        

        return (
            <div className="mdc-card">
                <div className="mdc-card__primary-action">
                    <h2 className=".mdc-typography--headline6">{this.props.title}</h2>
                </div>
            </div>
        );
      
     
    }
}  