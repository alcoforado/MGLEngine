import { Component, OnInit, Input, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { trigger, state, style, animate, transition, keyframes } from '@angular/animations';
import { createFocusTrap } from '@material/dialog'
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
export class MdcModalComponent implements OnInit, AfterViewInit {
    @Input() type: string;
    @Input() visible: boolean;
    @Input() closeOnClickOut: boolean;
    @ViewChild("mainPanel") main: ElementRef
    css_class: string;
    focusTrap: any;
    constructor() { }

    ngOnInit() {
        if (this.type == 'primary') {
            this.css_class = "mdc-button--raised"
        }
    }
    ngAfterViewInit() {
        var that = this;
        this.focusTrap = createFocusTrap(this.main.nativeElement, {
            onDeactivate: function () {
                that.focusDeactivated()
            },
            clickOutsideDeactivates: this.closeOnClickOut
        })
    }

    focusDeactivated() {
        if (this.closeOnClickOut) {
            this.close();
        }
    }
    close() {
        visible = 0;
    }
    clicked(event: any) {
        console.log(event);

    }
}

