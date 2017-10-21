import { Component, OnInit,Input } from '@angular/core';
import {   trigger,  state,  style,  animate,  transition,keyframes} from '@angular/animations';
@Component({
  moduleId: module.id.toString(),
  selector: 'collapse-panel',
  templateUrl: './collapse-panel.component.html',
  animations: [
    trigger('collapse', [
      state('*', style({ height: '*', opacity:1,overflow:"hidden" })),
      state('void', style({ height: 0,opacity:0,overflow:"hidden" })),
      transition('void => *', [animate('0.5s linear', keyframes([
        style({ height: 0, opacity: 0, offset: 0 }),
        style({ height: '*', opacity: 0, offset:0.25}),
        style({ height: '*', opacity: 1, offset:1 })
      ]))]),
      transition('* => void', [animate('0.5s linear', keyframes([
        style({ height: '*', opacity: 1,offset: 0 }),
        style({ height: '*', opacity: 0,offset: 0.75}),
        style({ height: 0, opacity: 0, offset:1 })
      ]))]),
    ])
  ]
}) 
export class CollapsePanelComponent implements OnInit {
  @Input() show:boolean;
  @Input() css:string="";
  constructor() { }

  ngOnInit() {
    
    //this.show = false;
  }

}

