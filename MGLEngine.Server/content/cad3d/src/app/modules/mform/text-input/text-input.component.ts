import { Component, Input, OnInit } from '@angular/core';
import { MFormComponent, MFormModel, IMFormModel } from "./../mformmodel";
import { FormGroup, FormControl, AbstractControl } from '@angular/forms'
@Component({
  moduleId: module.id.toString(),
  selector: 'app-text-input',
  templateUrl: './text-input.component.html',
})
export class TextInputComponent implements OnInit {
  @Input() formComponent: MFormComponent;

  constructor() { }

  ngOnInit() {
    this.formComponent.setAsPrimitiveValue("");
  }

}


