"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var forms_1 = require("@angular/forms");
//7274653768
var MFormComponent = (function () {
    function MFormComponent(parent, name) {
        this.parent = parent;
        this.name = name;
        this.Control = null;
        this.Group = null;
    }
    MFormComponent.prototype.setAsGroupValue = function (g) {
        if (this.Control != null)
            throw "FormComponent already set as a primitive type";
        if (this.Group != null)
            throw "MFormComponent already assigned as a group";
        this.Group = g;
        if (this.parent.model != null && typeof (this.parent.model[this.name]) != "undefined") {
            if (typeof (this.parent.model[this.name]) != "object")
                throw "Incosisntency, the MFormModel field " + this.name + " is not an object but it was assigned to a group mformcomponent";
            this.Group.setValue(this.parent.model[this.name]);
        }
        this.parent.getRoot().addControl(this.name, this.Group);
    };
    MFormComponent.prototype.setAsPrimitiveValue = function (obj) {
        if (obj == null)
            throw "MFormComponent needs a non null object";
        var type = typeof (obj);
        switch (type) {
            case "string":
            case "number":
            case "boolean":
                if (this.Group != null) {
                    throw "The type of value passed to the method setValue does not match the one of preveous call";
                }
                if (this.Control == null) {
                    this.Control = new forms_1.FormControl();
                    this.parent.getRoot().addControl(this.name, this.Control);
                }
                //Set initial  value of the  control
                var init = this.getInitialValue();
                if (init != null) {
                    if (typeof (init) != typeof (obj))
                        throw "Error primitive type  set by function setPrimitiveValue does not match the init  field in the model";
                    this.Control.setValue(init);
                }
                else
                    this.Control.setValue(obj);
                this.Group = this.parent.getRoot();
                return;
            default:
                throw "Type is not primitive";
        }
    };
    MFormComponent.prototype.getInitialValue = function () {
        if (this.parent.model != null && typeof (this.parent.model[this.name]) != "undefined")
            return this.parent.model[this.name];
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
    function UIType(TypeName, Members, TypeLabel) {
        this.TypeName = TypeName;
        this.Members = Members;
        this.TypeLabel = TypeLabel;
    }
    UIType.primitiveTypes = ["number", "int", "bool", "string"];
    return UIType;
}());
exports.UIType = UIType;
var MFormModel = (function () {
    function MFormModel(model, type) {
        if (type === void 0) { type = null; }
        this.model = model;
        this.type = type;
        this._formComponentCash = {};
        this.root = new forms_1.FormGroup({});
    }
    MFormModel.prototype.getRoot = function () { return this.root; };
    MFormModel.prototype.getFormComponent = function (propertyName) {
        if (typeof (this._formComponentCash[propertyName]) !== "undefined") {
            return this._formComponentCash[propertyName];
        }
        this._formComponentCash[propertyName] = new MFormComponent(this, propertyName);
        return this._formComponentCash[propertyName];
    };
    return MFormModel;
}());
exports.MFormModel = MFormModel;
//# sourceMappingURL=mformmodel.js.map