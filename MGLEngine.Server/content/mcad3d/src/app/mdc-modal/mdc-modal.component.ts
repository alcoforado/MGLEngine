import { Component, OnInit, Input, ViewChild, ElementRef } from '@angular/core';
import { trigger, state, style, animate, transition, keyframes } from '@angular/animations';

@Component({
    moduleId: module.id.toString(),
    selector: 'mdc-modal',
    templateUrl: 'mdc-modal.component.html',
    animations: [
        trigger('visible', [
            state('1', style({ opacity: 1, top: "0px" })),
            state('0', style({ opacity: 1, top: "100px" })),
            transition('0 <=> 1',
                animate('0.5s linear',
                    keyframes([
                        style({ transform: 'scale(0)', opacity: 1 }),
                        style({ transform: 'scale(1)', opacity: 0.2 })])))
        ])
    ]
})
export class MdcModalComponent implements OnInit {
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
        var d: number = Math.max(this.bt.nativeElement.offsetWidth, this.bt.nativeElement.offsetHeight) * 2;
        this._width = + d + 'px';
        this._x = (event.pageX - this.bt.nativeElement.offsetLeft - d / 2) + 'px';
        this._y = (event.pageY - this.bt.nativeElement.offsetTop - d / 2) + 'px';
        this._ripple = this._ripple == '0' ? '1' : '0';
    }
}

