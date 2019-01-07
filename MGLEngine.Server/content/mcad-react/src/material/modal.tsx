import React, { Component } from 'react';
import classnames from 'classnames';
import ReactDOM from 'react-dom'
import  * as createFocusTrap from 'focus-trap';

export interface IModalProp
{
    headerText?:string;
    closeOnClickOut?:boolean;
}

export interface IModalState
{
    show?:boolean;
    focusTrap?:any;
}

export class Modal extends Component<IModalProp,IModalState> {
    constructor(props:IModalProp){
        super(props);
        this.state={show:false};

    }

    close(confirm:boolean) {
        this.setState({show:false});
        document.body.classList.remove("mdc-dialog-scroll-lock");
    }

    show()
    {
        this.setState({show:true})
        document.body.classList.add("mdc-dialog-scroll-lock");
    }

    componentDidMount()
    {
            var that = this;
            var focusTrap = (createFocusTrap as any)(ReactDOM.findDOMNode(this), {
                onDeactivate: ()=> {
                    if (this.props.closeOnClickOut)
                        that.close(false);
                },
                clickOutsideDeactivates: this.props.closeOnClickOut ? true : false
            })
    }

    render(){
        return (
<aside  className={classnames("mdc-dialog",{"mdc-dialog--open":this.state.show})} role="alertdialog">
    <div className="mdc-dialog__surface mdc-dialog--open">
        <header className="mdc-dialog__header">
            <h2 className="mdc-dialog__header__title">
                {this.props.headerText}
            </h2>
        </header>
        <section className="mdc-dialog__body">
            {this.props.children}
        </section>
        <footer className="mdc-dialog__footer">
            <button type="button" className="mdc-button mdc-dialog__footer__button mdc-dialog__footer__button--cancel" onClick={()=>this.close(false)}>Decline</button>
            <button type="button" className="mdc-button mdc-dialog__footer__button mdc-dialog__footer__button--accept" onClick={()=>this.close(true)}>Accept</button>
        </footer>
    </div>
    <div className="mdc-dialog__backdrop"></div>
</aside>
        )
    }

}