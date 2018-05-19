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
var animations_1 = require("@angular/animations");
var ModalComponent = (function () {
    function ModalComponent() {
    }
    ModalComponent.prototype.ngOnChanges = function (ch) {
    };
    ModalComponent.prototype.ngOnInit = function () {
    };
    __decorate([
        core_1.Input(),
        __metadata("design:type", String)
    ], ModalComponent.prototype, "title", void 0);
    __decorate([
        core_1.Input(),
        __metadata("design:type", Boolean)
    ], ModalComponent.prototype, "show", void 0);
    ModalComponent = __decorate([
        core_1.Component({
            moduleId: module.id,
            selector: 'app-modal',
            templateUrl: './modal.component.html',
            styleUrls: ['./modal.component.css'],
            animations: [
                animations_1.trigger('visibleAnim', [
                    animations_1.state('1', animations_1.style({ opacity: 1, transform: "scale(1) translate(0px,0px)", top: "0px" })),
                    animations_1.state('0', animations_1.style({ opacity: 0.2, transform: "scale(0.75) translate(0px,250px)" })),
                    animations_1.transition('0 => 1', animations_1.animate('0.25s cubic-bezier(0, 0, .2, 1)')),
                    animations_1.transition('1 => 0', animations_1.animate('0.25s cubic-bezier(0,0,.2,1)'))
                ])
            ]
        }),
        __metadata("design:paramtypes", [])
    ], ModalComponent);
    return ModalComponent;
}());
exports.ModalComponent = ModalComponent;
//# sourceMappingURL=modal.component.js.map