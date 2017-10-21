import { Component, Input } from '@angular/core';
import { MFormComponent, MFormModel, IMFormModel } from "./../mformmodel";
import { FormGroup, FormControl, AbstractControl } from '@angular/forms'
@Component({
    moduleId: module.id.toString(),
    selector: 'app-number-input',
    templateUrl: './number-input.component.html',
})
export class NumberInputComponent {
    @Input() formComponent: MFormComponent;
    ngOnInit() {
        this.formComponent.setAsPrimitiveValue(0);
    }

}

