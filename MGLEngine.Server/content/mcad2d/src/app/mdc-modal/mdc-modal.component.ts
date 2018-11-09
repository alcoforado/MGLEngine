//3525845875
import { Component, EventEmitter, OnInit, Input, Output, ViewChild, ElementRef, AfterViewInit, SimpleChanges, OnChanges } from '@angular/core';
import { trigger, state, style, animate, transition, keyframes } from '@angular/animations';
var createFocusTrap = require('focus-trap');
@Component({
    moduleId: module.id.toString(),
    selector: 'mdc-modal',
    templateUrl: 'mdc-modal.component.html',
    animations: [
        trigger('visibleAnim', [
            state('1', style({ opacity: 1, transform: "scale(1) translate(0px,0px)", top: "0px" })),
            state('0', style({ opacity: 0, transform: "scale(0.75) translate(0px,250px)" })),
            transition('0 => 1',
                animate('0.25s cubic-bezier(0, 0, .2, 1)')),
            transition('1 => 0',
                animate('0.25s cubic-bezier(.4,0,.6,1)'))
        ])
    ]
})
export class MdcModalComponent implements OnInit, AfterViewInit, OnChanges {
    @Input() type: string;
    @Input() visible: boolean;
    @Input() closeOnClickOut: boolean;
    @Output() visibleChange: EventEmitter<boolean> = new EventEmitter();
    @ViewChild("mainPanel") main: ElementRef;
    css_class: string;
    focusTrap: any;
    constructor() { }

    ngOnChanges(changes: SimpleChanges) {
        if (typeof changes["visible"] !== "undefined") {
            if (changes["visible"].currentValue == true)
                document.body.classList.add("mdc-dialog-scroll-lock");
            else
                document.body.classList.remove("mdc-dialog-scroll-lock");
        }
    }

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
        this.visible = false;
        this.visibleChange.emit(this.visible)
    }
    clicked(event: any) {
        console.log(event);

    }
}

