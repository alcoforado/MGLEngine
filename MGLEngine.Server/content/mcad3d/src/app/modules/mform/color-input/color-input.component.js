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
var forms_1 = require("@angular/forms");
var ColorInputComponent = (function () {
    function ColorInputComponent() {
    }
    ColorInputComponent.prototype.ngOnInit = function () {
        this.formComponent.setAsGroupValue(new forms_1.FormGroup({ x: new forms_1.FormControl(0), y: new forms_1.FormControl(0), z: new forms_1.FormControl(0) }));
        this.g = new forms_1.FormGroup({ value: new forms_1.FormControl() });
        this.g.valueChanges.subscribe(function (c) {
            debugger;
            var str = c.value;
        });
    };
    __decorate([
        core_1.Input(),
        __metadata("design:type", mformmodel_1.MFormComponent)
    ], ColorInputComponent.prototype, "formComponent", void 0);
    ColorInputComponent = __decorate([
        core_1.Component({
            moduleId: module.id,
            selector: 'app-color-input',
            templateUrl: './color-input.component.html',
            styleUrls: ['./color-input.component.css']
        }),
        __metadata("design:paramtypes", [])
    ], ColorInputComponent);
    return ColorInputComponent;
}());
exports.ColorInputComponent = ColorInputComponent;
//# sourceMappingURL=color-input.component.js.map