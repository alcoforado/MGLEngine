import { Component, OnInit, Input } from '@angular/core';
import { MFormComponent, MFormModel, IMFormModel } from "./../mformmodel";
import { FormGroup, FormControl, AbstractControl } from '@angular/forms'
@Component({
  moduleId: module.id,
  selector: 'app-vec2-input',
  templateUrl: './vec2-input.component.html',
})
export class Vec2InputComponent implements OnInit {
  @Input() formComponent: MFormComponent;


  constructor() { }

  ngOnInit() {
    this.formComponent.setAsGroupValue(new FormGroup({ x: new FormControl(0), y: new FormControl(0) }));

  }




}
