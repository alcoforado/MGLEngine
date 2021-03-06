import { Component, Input, OnChanges, SimpleChanges, OnInit } from '@angular/core';
import { MFormModel, MFormComponent } from '../mformmodel';
import { FormGroup, FormControl, FormArray, AbstractControl } from '@angular/forms'
@Component({
    moduleId: module.id,
    selector: 'dynamic-input',
    templateUrl: 'dynamic-input.component.html'
})
export class DynamicInputComponent implements OnInit {
    @Input() directiveType: string;
    @Input() mformComponent: MFormComponent = null;
    listType = null;
    ngOnInit() {

        let dt = this.directiveType;
        if (dt.startsWith("List ") && this.mformComponent) {
            this.mformComponent.setAsArrayValue(new FormArray([]));
            this.listType = dt.replace("List ", "");
        }
    }
    removeComponentFromList(fc: MFormComponent) {
        if (this.mformComponent != null) {
            this.mformComponent.removeFormComponent(fc);
        }
    }
    addFormComponent() {
        this.mformComponent.appendFormComponent();
        console.log(this.mformComponent)
    }
}



