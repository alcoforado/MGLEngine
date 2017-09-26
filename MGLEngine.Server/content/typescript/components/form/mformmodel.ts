import {FormGroup,FormControl,AbstractControl} from '@angular/forms'


export class MFormComponent {

    constructor(private component:AbstractControl,private isAGroup:boolean) { }

    isGroup(): boolean {
        return this.isAGroup;
    }

    getFormGroup(): FormGroup {
        if (this.isGroup)
            return <FormGroup> this.component;
        else
            throw "MFormCompoent doesn't have a group"
    }

    getFormControl(): FormControl {
        if (!this.isGroup)
            return <FormControl> this.component;
        else
            throw "MFormComponent doesn't have a form control"
    }


}


export class MFormModel<T> {

    root: FormGroup;

    constructor(public model: T) {
        this.root = new FormGroup({});
    }
    getRoot(): FormGroup { return this.root; }

    createFormComponent(propertyName: string): MFormComponent {

        var type: string = typeof (this.model[propertyName]).toLowerCase();
        switch (type) {
            case "undefined":
                throw `Error, propertyName ${propertyName} does not exist`;
            case "number":
            case "string":
            case "boolean":
                {
                    let child = new FormControl(this.model[propertyName]);
                    this.root.addControl(propertyName, child);
                    return new MFormComponent(child, false);
                }
            case "object":
                {
                    let child = new FormGroup(this.model[propertyName]);
                    this.root.addControl(propertyName, child);
                    return new MFormComponent(child, true);
                }
            default:
                throw `Not valid type ${type} for property ${propertyName}`;
        }
    }

    


}