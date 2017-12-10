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
var mformmodel_1 = require("../../modules/mform/mformmodel");
var forms_1 = require("@angular/forms");
var ColorRender2DComponent = (function () {
    function ColorRender2DComponent() {
    }
    ColorRender2DComponent.prototype.ngOnInit = function () {
        this.mformComponent.setAsGroupValue(new forms_1.FormGroup({ colors: new forms_1.FormArray([]) }));
    };
    __decorate([
        core_1.Input(),
        __metadata("design:type", mformmodel_1.MFormComponent)
    ], ColorRender2DComponent.prototype, "mformComponent", void 0);
    ColorRender2DComponent = __decorate([
        core_1.Component({
            moduleId: module.id,
            selector: 'app-color-render2d',
            templateUrl: './color-render2d.component.html'
        }),
        __metadata("design:paramtypes", [])
    ], ColorRender2DComponent);
    return ColorRender2DComponent;
}());
exports.ColorRender2DComponent = ColorRender2DComponent;
//# sourceMappingURL=color-render2d.component.js.map