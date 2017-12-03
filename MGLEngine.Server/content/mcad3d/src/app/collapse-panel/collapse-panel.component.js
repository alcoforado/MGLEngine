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
var CollapsePanelComponent = (function () {
    function CollapsePanelComponent() {
        this.css = "";
    }
    CollapsePanelComponent.prototype.ngOnInit = function () {
        //this.show = false;
    };
    __decorate([
        core_1.Input(),
        __metadata("design:type", Boolean)
    ], CollapsePanelComponent.prototype, "show", void 0);
    __decorate([
        core_1.Input(),
        __metadata("design:type", String)
    ], CollapsePanelComponent.prototype, "css", void 0);
    CollapsePanelComponent = __decorate([
        core_1.Component({
            moduleId: module.id.toString(),
            selector: 'collapse-panel',
            templateUrl: './collapse-panel.component.html',
            animations: [
                animations_1.trigger('collapse', [
                    animations_1.state('*', animations_1.style({ height: '*', opacity: 1, overflow: "hidden" })),
                    animations_1.state('void', animations_1.style({ height: 0, opacity: 0, overflow: "hidden" })),
                    animations_1.transition('void => *', [animations_1.animate('0.5s linear', animations_1.keyframes([
                            animations_1.style({ height: 0, opacity: 0, offset: 0 }),
                            animations_1.style({ height: '*', opacity: 0, offset: 0.25 }),
                            animations_1.style({ height: '*', opacity: 1, offset: 1 })
                        ]))]),
                    animations_1.transition('* => void', [animations_1.animate('0.5s linear', animations_1.keyframes([
                            animations_1.style({ height: '*', opacity: 1, offset: 0 }),
                            animations_1.style({ height: '*', opacity: 0, offset: 0.75 }),
                            animations_1.style({ height: 0, opacity: 0, offset: 1 })
                        ]))]),
                ])
            ]
        }),
        __metadata("design:paramtypes", [])
    ], CollapsePanelComponent);
    return CollapsePanelComponent;
}());
exports.CollapsePanelComponent = CollapsePanelComponent;
//# sourceMappingURL=collapse-panel.component.js.map