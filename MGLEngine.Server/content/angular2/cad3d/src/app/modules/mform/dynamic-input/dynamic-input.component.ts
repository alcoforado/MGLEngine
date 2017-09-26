import {Component,Input} from '@angular/core';
import {MFormModel,MFormComponent} from '../mformmodel';
@Component({
    moduleId: module.id,
    selector: 'dynamic-input',
    templateUrl: 'dynamic-input.component.html'
})
export class DynamicInputComponent  {
    @Input() directiveType: string;
    @Input() mformComponent:MFormComponent;
}


export interface IMemberInfo {
    directiveType: string
}