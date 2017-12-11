"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
Object.defineProperty(exports, "__esModule", { value: true });
var core_1 = require("@angular/core");
var mformmodel_1 = require("../mformmodel");
var forms_1 = require("@angular/forms");
var DynamicInputComponent = (function () {
    function DynamicInputComponent() {
        this.mformComponent = null;
        this.listType = null;
    }
    DynamicInputComponent.prototype.ngOnInit = function () {
        var dt = this.directiveType;
        if (dt.startsWith("List ") && this.mformComponent) {
            this.mformComponent.setAsArrayValue(new forms_1.FormArray([]));
            this.listType = dt.replace("List ", "");
        }
    };
    DynamicInputComponent.prototype.removeComponentFromList = function (fc) {
        if (this.mformComponent != null) {
            this.mformComponent.removeFormComponent(fc);
        }
    };
    DynamicInputComponent.prototype.addFormComponent = function () {
        this.mformComponent.appendFormComponent();
    };
    __decorate([
        core_1.Input(),
        __metadata("design:type", String)
    ], DynamicInputComponent.prototype, "directiveType", void 0);
    __decorate([
        core_1.Input(),
        __metadata("design:type", mformmodel_1.MFormComponent)
    ], DynamicInputComponent.prototype, "mformComponent", void 0);
    DynamicInputComponent = __decorate([
        core_1.Component({
            moduleId: module.id,
            selector: 'dynamic-input',
            templateUrl: 'dynamic-input.component.html'
        })
    ], DynamicInputComponent);
    return DynamicInputComponent;
}());
exports.DynamicInputComponent = DynamicInputComponent;
//# sourceMappingURL=dynamic-input.component.js.map