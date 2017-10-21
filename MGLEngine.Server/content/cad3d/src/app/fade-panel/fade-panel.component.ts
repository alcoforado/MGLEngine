import { Component, OnInit,Input } from '@angular/core';
import {   trigger,  state,  style,  animate,  transition} from '@angular/animations';
@Component({
  moduleId: module.id.toString(),
  selector: 'fade-panel',
  templateUrl: './fade-panel.component.html',
  animations: [
    trigger('fade', [
      state("true", style({ opacity: 1 })),
      state("false", style({ opacity: 0 })),
      transition('true <=> false', animate('0.5s linear', )),
    ])
  ]
}) 
export class FadePanelComponent implements OnInit {
  @Input() show:boolean;
  @Input() css:string;
  constructor() { }

  ngOnInit() {
    //this.show = false;
  }

}

