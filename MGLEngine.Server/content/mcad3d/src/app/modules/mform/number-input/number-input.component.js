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
var mformmodel_1 = require("./../mformmodel");
var NumberInputComponent = (function () {
    function NumberInputComponent() {
    }
    NumberInputComponent.prototype.ngOnInit = function () {
        this.formComponent.setAsPrimitiveValue(0);
    };
    __decorate([
        core_1.Input(),
        __metadata("design:type", mformmodel_1.MFormComponent)
    ], NumberInputComponent.prototype, "formComponent", void 0);
    NumberInputComponent = __decorate([
        core_1.Component({
            moduleId: module.id.toString(),
            selector: 'app-number-input',
            templateUrl: './number-input.component.html',
        })
    ], NumberInputComponent);
    return NumberInputComponent;
}());
exports.NumberInputComponent = NumberInputComponent;
//# sourceMappingURL=number-input.component.js.map