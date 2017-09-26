import {Component,Input} from '@angular/core';
@Component({
    moduleId: module.id,
    selector: 'dynamic-input',
    templateUrl: 'number-input.html',
})
export class DynamicInputComponent  {
    @Input() member: IMemberInfo;
    @Input() value: any;
}


export interface IMemberInfo {
    directiveType: string
}