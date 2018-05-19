import { Component, OnInit, Input, Output, EventEmitter, OnChanges, SimpleChanges } from '@angular/core';
import { trigger, state, style, animate, transition, keyframes } from '@angular/animations';


@Component({
  moduleId: module.id,
  selector: 'app-modal',
  templateUrl: './modal.component.html',
  styleUrls: ['./modal.component.css'],
  animations: [
    trigger('visibleAnim', [
      state('1', style({ opacity: 1, transform: "scale(1) translate(0px,0px)", top: "0px" })),
      state('0', style({ opacity: 0.2, transform: "scale(0.75) translate(0px,250px)" })),
      transition('0 => 1',
        animate('0.25s cubic-bezier(0, 0, .2, 1)')),
      transition('1 => 0',
        animate('0.25s cubic-bezier(0,0,.2,1)'))
    ])
  ]
})
export class ModalComponent implements OnInit, OnChanges {
  @Input() title: string;
  @Input() show: boolean;
  constructor() { }



  ngOnChanges(ch: SimpleChanges) {
  }

  ngOnInit() {
  }

}
