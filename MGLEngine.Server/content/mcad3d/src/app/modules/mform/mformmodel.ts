import { FormGroup, FormControl, FormArray, AbstractControl } from '@angular/forms'

//7274653768
export class MFormComponent {
    Control: FormControl = null;
    Group: FormGroup = null;
    Array: FormArray = null;
    Model: any = null;
    _formComponentCash: { [id: string]: MFormComponent } = {};
    private _formComponents: Array<MFormComponent> = [];

    constructor(public parent: MFormComponent, public field: string | number) { }

    private getIndex(): number {

        if (this.parent.Array == null) {
            throw "Component parent is not an Array, getting a index does not make sense."
        }
        else {
            return <number>this.field;
        }
    }

    setAsGroupValue(g: FormGroup) {

        if (this.parent == null) {
            throw "A root form is always a  group"
        }

        if (this.parent.Group == null && this.parent.Array == null) {
            throw "Parent of a form group must be a group or array"
        }
        if (this.Control != null)
            throw "FormComponent already set as a primitive type"
        if (this.Group != null) {
            debugger;
            throw "MFormComponent already assigned as a group"

        }
        this.Group = g;


        if (this.parent.Model != null && typeof (this.parent.Model[this.field]) != "undefined") {
            if (typeof (this.parent.Model[this.field]) != "object")
                throw `Incosisntency, the MFormModel field ${this.field} is not an object but it was assigned to a group mformcomponent`
            this.Group.setValue(this.parent.Model[this.field]);
            this.Model = this.parent.Model[this.field]
        }
        if (this.parent.Group != null)
            this.parent.Group.addControl(<string>this.field, this.Group)
        else if (this.parent.Array != null)
            this.parent.Array.push(this.Group);


    }
    setAsArrayValue(a: FormArray = null) {

        if (a == null)
            a = new FormArray([]);

        if (this.parent == null) {
            throw "A form component array cannot be root"
        }

        if (this.parent.Group == null && this.parent.Array == null) {
            throw "Parent of a array must be a group or array"
        }
        if (this.Control != null)
            throw "FormComponent already set as a primitive type"
        if (this.Group != null)
            throw "MFormComponent is already group and cannot be set to an array"
        this.Array = a;
        if (this.parent.Model != null && typeof (this.parent.Model[this.field]) != "undefined") {
            if (this.parent.Model[this.field].constructor !== Array)
                throw `Incosisntency, the MFormModel field ${this.field} is not an array but it was assigned to an array mformcomponent`
            this.Array.setValue(this.parent.Model[this.field]);
            this.Model = this.parent.Model[this.field];
        }
        if (this.parent.Group != null)
            this.parent.Group.addControl(<string>this.field, this.Array)
        if (this.parent.Array != null)
            this.parent.Array.setControl(<number>this.field, this.Array)
    }

    removeFormComponent(fc: MFormComponent) {
        if (fc.parent != this) {
            return "removeFormComponent error, component to be removed is not a child"
        }
        if (this.Array == null) {
            throw "removeFormComponent is only supported for Array";
        }
        if (this._formComponents.find(x => x == fc)) {
            this._formComponents.splice(fc.getIndex(), 1);
            this.Array.removeAt(fc.getIndex())
            //Aling indices
            this._formComponents.filter((fc, index) => {
                fc.field = index;
                return fc;
            });
        }


    }

    appendFormComponent() {
        if (this.Array == null)
            throw "appendFormComponent only work for FormComponents that are arrays"
        //Allocate a new entry in the array and fill it with a FormGroup just as placeholder.            
        let index = this.Array.length;
        this.Array.push(new FormGroup({}));
        this._formComponents.push(new MFormComponent(this, index));
    }

    getFormComponentsArray() {
        if (this.Array == null)
            throw "getFormComponentsArray can only be called for Array Components"
        return this._formComponents;
    }

    getFormComponent(propertyName: string): MFormComponent {
        if (this.Group == null) {
            throw "Method getFormComponent(propertyName) can only be called from a group component"
        }
        if (typeof (this._formComponentCash[propertyName]) !== "undefined") {
            return this._formComponentCash[propertyName];
        }
        this._formComponentCash[propertyName] = new MFormComponent(this, propertyName);
        return this._formComponentCash[propertyName];
    }

    getFormComponentAsGroup(propertyName: string): MFormComponent {
        var result = this.getFormComponent(propertyName);
        result.setAsGroupValue(new FormGroup({}));
        return result;
    }

    setAsPrimitiveValue(obj: any) {
        if (this.parent == null)
            throw "A form control with primitive value must have a parent "

        if (obj == null)
            throw "MFormComponent needs a non null object"
        var type = typeof (obj);
        switch (type) {
            case "string":
            case "number":
            case "boolean":
                if (this.Group != null || this.Array != null) {
                    throw "Form Control is a group or array, cannot set it as primitive."
                }
                if (this.Control == null) {
                    this.Control = new FormControl();
                    if (this.parent.Group != null)
                        this.parent.Group.addControl(<string>this.field, this.Control);
                    else if (this.parent.Array != null)
                        this.parent.Array.setControl(<number>this.field, this.Control);
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
                return;
            default:
                throw "Type is not primitive"
        }
    }
    getInitialValue(): any {
        if (this.parent.Model != null && typeof (this.parent.Model[this.field]) != "undefined")
            return this.parent.Model[this.field];
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
        public TypeLabel: string,
        public CssTypeName: string
    ) { }
}


export class MFormModel extends MFormComponent {
    constructor(model: any) {
        super(null, '');
        this.Group = new FormGroup({});
    }
}




