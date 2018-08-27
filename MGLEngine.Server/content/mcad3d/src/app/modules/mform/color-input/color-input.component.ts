import { Component, OnInit, Input } from '@angular/core';
import { MFormComponent, MFormModel, IMFormModel } from "./../mformmodel";
import { FormGroup, FormControl, AbstractControl } from '@angular/forms'

@Component({
  moduleId: module.id,
  selector: 'app-color-input',
  templateUrl: './color-input.component.html'

})
export class ColorInputComponent implements OnInit {
  @Input() formComponent: MFormComponent;
  g: FormGroup;

  constructor() { }

  componentColorToString(d: number): string {
    var str = (d * 255).toString(16);
    if (str.length < 2) {
      str = '0' + str;
    }
    return str;

  }

  ngOnInit() {

    this.formComponent.setAsGroupValue(new FormGroup({ R: new FormControl(0), G: new FormControl(0), B: new FormControl(0) }));
    this.g = new FormGroup({ value: new FormControl() });
    this.g.valueChanges.subscribe(c => {
      var str = c.value;
      var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(str);
      var parsed = {
        R: parseInt(result[1], 16) / 255.0,
        G: parseInt(result[2], 16) / 255.0,
        B: parseInt(result[3], 16) / 255.0
      };
      this.formComponent.Group.setValue(parsed);
    });
    var m = this.formComponent.Model;
    if (m != null) {
      var result = '#' + this.componentColorToString(m.R) + this.componentColorToString(m.G) + this.componentColorToString(m.B);
      this.g.setValue({ value: result });
    }
  }


}





