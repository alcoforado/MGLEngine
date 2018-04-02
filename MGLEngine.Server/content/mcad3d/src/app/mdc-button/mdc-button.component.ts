import { Component, OnInit, Input, ViewChild, ElementRef } from '@angular/core';
import { trigger, state, style, animate, transition } from '@angular/animations';

@Component({
    moduleId: module.id.toString(),
    selector: 'mdc-button',
    templateUrl: 'mdc-button.component.html',
    animations: [
        trigger('ripple', [
            state('1', style({})),
            state('0', style({})),
            transition('0 <=> 1', animate('1s ease-in', style({ transform: 'scale(1.0)' })))
        ])
    ]
})



export class MdcButtonComponent implements OnInit {
    @Input() type: string;
    @ViewChild('bt') bt: ElementRef;
    css_class: string;
    constructor() { }
    _ripple: string;
    _x: string;
    _y: string;
    _width: string;
    ngOnInit() {
        if (this.type == 'primary') {
            this.css_class = "mdc-button--raised"
        }
        this._x = '0';
        this._y = '0';
        this._ripple = '0';

    }
    clicked(event: any) {
        console.log(event);
        console.log(this.bt);
        this._x = (event.pageX - this.bt.nativeElement.offsetLeft - this.bt.nativeElement.offsetWidth / 2) + 'px';
        this._y = (event.pageY - this.bt.nativeElement.offsetTop - this.bt.nativeElement.offsetHeight / 2) + 'px';
        this._width = Math.max(this.bt.nativeElement.offsetWidth, this.bt.nativeElement.offsetHeight) + 'px';
        this._ripple = this._ripple == '0' ? '1' : '0';
    }
}

