import { Component, OnInit, Input } from '@angular/core';
import { MFormComponent, MFormModel, IMFormModel } from "../../modules/mform/mformmodel";
import { FormGroup, FormControl, AbstractControl, FormArray } from '@angular/forms'
@Component({
  moduleId: module.id,
  selector: 'app-color-render2d',
  templateUrl: './color-render2d.component.html'
})
export class ColorRender2DComponent implements OnInit {
  @Input() mformComponent: MFormComponent;
  constructor() { }

  ngOnInit() {
    this.mformComponent.setAsGroupValue(new FormGroup({ colors: new FormArray([]) }))

  }




}
