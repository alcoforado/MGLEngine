import {Component,Input} from '@angular/core';
@Component({
    moduleId: module.id,
    selector: 'number',
    templateUrl: 'number-input.html',
})
export class NumberInputComponent  {
    @Input() value: number;
    @Input() validations: string;
}

