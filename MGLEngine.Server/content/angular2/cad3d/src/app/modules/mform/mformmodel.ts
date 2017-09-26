import { FormGroup, FormControl, AbstractControl } from '@angular/forms'

//7274653768
export class MFormComponent {
    Control: FormControl = null;
    Group: FormGroup = null;
    constructor(public parent: MFormModel, public name: string) { }

    setAsGroupValue(g: FormGroup) {
        if (this.Control != null)
            throw "FormComponent already set as a primitive type"
        if (this.Group != null)
            throw "MFormComponent already assigned as a group"
        this.Group = g;
        if (this.parent.model != null && typeof (this.parent.model[this.name]) != "undefined") {
            if (typeof (this.parent.model[this.name]) != "object")
                throw `Incosisntency, the MFormModel field ${this.name} is not an object but it was assigned to a group mformcomponent`
            this.Group.setValue(this.parent.model[this.name]);
        }
        this.parent.getRoot().addControl(this.name, this.Group)
    }

    setAsPrimitiveValue(obj: any) {
        if (obj == null)
            throw "MFormComponent needs a non null object"
        var type = typeof (obj);
        switch (type) {
            case "string":
            case "number":
            case "boolean":
                if (this.Group != null) {
                    throw "The type of value passed to the method setValue does not match the one of preveous call"
                }
                if (this.Control == null) {
                    this.Control = new FormControl();
                    this.parent.getRoot().addControl(this.name, this.Control);
                }
                //Set initial  value of the  control
                var init = this.getInitialValue();
                if (init != null) {
                    if (typeof (init) != typeof (obj))
                        throw "Error primitive type  set by function setPrimitiveValue does not match the init  field in the model"
                    this.Control.setValue(init);
                }
                else
                    this.Control.setValue(obj);

                this.Group = this.parent.getRoot();
                return;
            default:
                throw "Type is not primitive"
        }
    }
    getInitialValue(): any {
        if (this.parent.model != null && typeof (this.parent.model[this.name]) != "undefined")
            return this.parent.model[this.name];
        else
            return null;
    }
}





export interface IMFormModel {
    getFormComponent(propertyName: string): MFormComponent;

}

export class TypeMember {
    constructor(
        public FieldName: string,
        public LabelName: string,
        public DirectiveType: string,

    ) { }
}

export class UIType {
    static primitiveTypes: string[] = ["number", "int", "bool", "string"];
    constructor(
        public TypeName: string,
        public Members: Array<TypeMember>,
        public TypeLabel: string
    ) { }
}


export class MFormModel {

    root: FormGroup;
    _formComponentCash: { [id: string]: MFormComponent } = {};
    constructor(public model: any, public type: UIType = null) {
        this.root = new FormGroup({});
    }
    getRoot(): FormGroup { return this.root; }


    getFormComponent(propertyName: string): MFormComponent {
        if (typeof (this._formComponentCash[propertyName]) !== "undefined") {
            return this._formComponentCash[propertyName];
        }
        this._formComponentCash[propertyName] = new MFormComponent(this, propertyName);
        return this._formComponentCash[propertyName];
    }
}




