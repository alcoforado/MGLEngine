"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
var forms_1 = require("@angular/forms");
//7274653768
var MFormComponent = (function () {
    function MFormComponent(parent, field) {
        this.parent = parent;
        this.field = field;
        this.Control = null;
        this.Group = null;
        this.Array = null;
        this.Model = null;
        this._formComponentCash = {};
        this._formComponents = [];
    }
    MFormComponent.prototype.getIndex = function () {
        if (this.parent.Array == null) {
            throw "Component parent is not an Array, getting a index does not make sense.";
        }
        else {
            return this.field;
        }
    };
    MFormComponent.prototype.setAsGroupValue = function (g) {
        if (g == undefined)
            g = new forms_1.FormGroup({});
        if (this.parent == null) {
            throw "A root form is always a  group";
        }
        if (this.parent.Group == null && this.parent.Array == null) {
            throw "Parent of a form group must be a group or array";
        }
        if (this.Control != null)
            throw "FormComponent already set as a primitive type";
        if (this.Group != null) {
            debugger;
            throw "MFormComponent already assigned as a group";
        }
        this.Group = g;
        if (this.parent.Model != null && typeof (this.parent.Model[this.field]) != "undefined") {
            if (typeof (this.parent.Model[this.field]) != "object")
                throw "Incosisntency, the MFormModel field " + this.field + " is not an object but it was assigned to a group mformcomponent";
            this.Group.patchValue(this.parent.Model[this.field]);
            this.Model = this.parent.Model[this.field];
        }
        if (this.parent.Group != null)
            this.parent.Group.addControl(this.field, this.Group);
        else if (this.parent.Array != null)
            this.parent.Array.setControl(this.field, this.Group);
    };
    MFormComponent.prototype.setAsArrayValue = function (a) {
        var _this = this;
        if (a === void 0) { a = null; }
        if (a == null)
            a = new forms_1.FormArray([]);
        if (this.parent == null) {
            throw "A form component array cannot be root";
        }
        if (this.parent.Group == null && this.parent.Array == null) {
            throw "Parent of a array must be a group or array";
        }
        if (this.Control != null)
            throw "FormComponent already set as a primitive type";
        if (this.Group != null)
            throw "MFormComponent is already group and cannot be set to an array";
        this.Array = a;
        if (this.parent.Model != null && typeof (this.parent.Model[this.field]) != "undefined") {
            if (this.parent.Model[this.field].constructor !== Array)
                throw "Incosisntency, the MFormModel field " + this.field + " is not an array but it was assigned to an array mformcomponent";
            this.Array.patchValue(this.parent.Model[this.field]);
            this.Model = this.parent.Model[this.field];
            this.Model.forEach(function (e) {
                _this.appendFormComponent();
            });
        }
        if (this.parent.Group != null)
            this.parent.Group.addControl(this.field, this.Array);
        if (this.parent.Array != null)
            this.parent.Array.setControl(this.field, this.Array);
    };
    MFormComponent.prototype.removeFormComponent = function (fc) {
        if (fc.parent != this) {
            return "removeFormComponent error, component to be removed is not a child";
        }
        if (this.Array == null) {
            throw "removeFormComponent is only supported for Array";
        }
        if (this._formComponents.find(function (x) { return x == fc; })) {
            this._formComponents.splice(fc.getIndex(), 1);
            this.Array.removeAt(fc.getIndex());
            //Aling indices
            this._formComponents.filter(function (fc, index) {
                fc.field = index;
                return fc;
            });
        }
    };
    MFormComponent.prototype.appendFormComponent = function () {
        if (this.Array == null)
            throw "appendFormComponent only work for FormComponents that are arrays";
        //Allocate a new entry in the array and fill it with a FormGroup just as placeholder.            
        var index = this.Array.length;
        this.Array.push(new forms_1.FormGroup({}));
        this._formComponents.push(new MFormComponent(this, index));
    };
    MFormComponent.prototype.getFormComponentsArray = function () {
        if (this.Array == null)
            throw "getFormComponentsArray can only be called for Array Components";
        return this._formComponents;
    };
    MFormComponent.prototype.getFormComponent = function (propertyName) {
        if (this.Group == null) {
            throw "Method getFormComponent(propertyName) can only be called from a group component";
        }
        if (typeof (this._formComponentCash[propertyName]) !== "undefined") {
            return this._formComponentCash[propertyName];
        }
        this._formComponentCash[propertyName] = new MFormComponent(this, propertyName);
        return this._formComponentCash[propertyName];
    };
    MFormComponent.prototype.getFormComponentAsGroup = function (propertyName) {
        var result = this.getFormComponent(propertyName);
        if (result.Group == null)
            result.setAsGroupValue(new forms_1.FormGroup({}));
        return result;
    };
    MFormComponent.prototype.setAsPrimitiveValue = function (obj) {
        if (this.parent == null)
            throw "A form control with primitive value must have a parent ";
        if (obj == null)
            throw "MFormComponent needs a non null object";
        var type = typeof (obj);
        switch (type) {
            case "string":
            case "number":
            case "boolean":
                if (this.Group != null || this.Array != null) {
                    throw "Form Control is a group or array, cannot set it as primitive.";
                }
                if (this.Control == null) {
                    this.Control = new forms_1.FormControl();
                    if (this.parent.Group != null)
                        this.parent.Group.addControl(this.field, this.Control);
                    else if (this.parent.Array != null)
                        this.parent.Array.setControl(this.field, this.Control);
                }
                //Set initial  value of the  control
                var init = this.getInitialValue();
                if (init != null) {
                    if (typeof (init) != typeof (obj))
                        throw "Error primitive type  set by function setPrimitiveValue does not match the init  field in the model";
                    this.Control.patchValue(init);
                }
                else
                    this.Control.patchValue(obj);
                return;
            default:
                throw "Type is not primitive";
        }
    };
    MFormComponent.prototype.getInitialValue = function () {
        if (this.parent.Model != null && typeof (this.parent.Model[this.field]) != "undefined")
            return this.parent.Model[this.field];
        else
            return null;
    };
    return MFormComponent;
}());
exports.MFormComponent = MFormComponent;
var TypeMember = (function () {
    function TypeMember(FieldName, LabelName, DirectiveType) {
        this.FieldName = FieldName;
        this.LabelName = LabelName;
        this.DirectiveType = DirectiveType;
    }
    return TypeMember;
}());
exports.TypeMember = TypeMember;
var UIType = (function () {
    function UIType(TypeName, Members, TypeLabel, CssTypeName) {
        this.TypeName = TypeName;
        this.Members = Members;
        this.TypeLabel = TypeLabel;
        this.CssTypeName = CssTypeName;
    }
    UIType.primitiveTypes = ["number", "int", "bool", "string"];
    return UIType;
}());
exports.UIType = UIType;
var MFormModel = (function (_super) {
    __extends(MFormModel, _super);
    function MFormModel(model) {
        var _this = _super.call(this, null, '') || this;
        _this.Model = model;
        _this.Group = new forms_1.FormGroup({});
        return _this;
    }
    return MFormModel;
}(MFormComponent));
exports.MFormModel = MFormModel;
//# sourceMappingURL=mformmodel.js.map