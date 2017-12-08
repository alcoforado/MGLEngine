import { Component, OnInit, Input } from '@angular/core';
import { MFormComponent, MFormModel, IMFormModel } from "./../mformmodel";
import { FormGroup, FormControl, AbstractControl } from '@angular/forms'

@Component({
  moduleId: module.id,
  selector: 'app-color-input',
  templateUrl: './color-input.component.html',
  styleUrls: ['./color-input.component.css']
})
export class ColorInputComponent implements OnInit {
  @Input() formComponent: MFormComponent;
  g: FormGroup;
  constructor() { }

  ngOnInit() {
    this.formComponent.setAsGroupValue(new FormGroup({ x: new FormControl(0), y: new FormControl(0), z: new FormControl(0) }));
    this.g = new FormGroup({ value: new FormControl() });
    this.g.valueChanges.subscribe(c => {
      debugger;
      var str = c.value;
    })
  }



}
