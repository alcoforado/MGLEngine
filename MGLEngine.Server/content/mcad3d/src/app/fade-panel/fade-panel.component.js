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
var FadePanelComponent = (function () {
    function FadePanelComponent() {
    }
    FadePanelComponent.prototype.ngOnInit = function () {
        //this.show = false;
    };
    __decorate([
        core_1.Input(),
        __metadata("design:type", Boolean)
    ], FadePanelComponent.prototype, "show", void 0);
    __decorate([
        core_1.Input(),
        __metadata("design:type", String)
    ], FadePanelComponent.prototype, "css", void 0);
    FadePanelComponent = __decorate([
        core_1.Component({
            moduleId: module.id.toString(),
            selector: 'fade-panel',
            templateUrl: './fade-panel.component.html',
            animations: [
                animations_1.trigger('fade', [
                    animations_1.state("true", animations_1.style({ opacity: 1 })),
                    animations_1.state("false", animations_1.style({ opacity: 0 })),
                    animations_1.transition('true <=> false', animations_1.animate('0.5s linear')),
                ])
            ]
        }),
        __metadata("design:paramtypes", [])
    ], FadePanelComponent);
    return FadePanelComponent;
}());
exports.FadePanelComponent = FadePanelComponent;
//# sourceMappingURL=fade-panel.component.js.map