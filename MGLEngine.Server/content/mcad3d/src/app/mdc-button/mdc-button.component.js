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
var MdcButtonComponent = (function () {
    function MdcButtonComponent() {
    }
    MdcButtonComponent.prototype.ngOnInit = function () {
        if (this.type == 'primary') {
            this.css_class = "mdc-button--raised";
        }
        this._x = '0';
        this._y = '0';
        this._ripple = '0';
    };
    MdcButtonComponent.prototype.clicked = function (event) {
        console.log(event);
        console.log(this.bt);
        this._x = (event.pageX - this.bt.nativeElement.offsetLeft - this.bt.nativeElement.offsetWidth / 2) + 'px';
        this._y = (event.pageY - this.bt.nativeElement.offsetTop - this.bt.nativeElement.offsetHeight / 2) + 'px';
        this._width = Math.max(this.bt.nativeElement.offsetWidth, this.bt.nativeElement.offsetHeight) + 'px';
        this._ripple = this._ripple == '0' ? '1' : '0';
    };
    __decorate([
        core_1.Input(),
        __metadata("design:type", String)
    ], MdcButtonComponent.prototype, "type", void 0);
    __decorate([
        core_1.ViewChild('bt'),
        __metadata("design:type", core_1.ElementRef)
    ], MdcButtonComponent.prototype, "bt", void 0);
    MdcButtonComponent = __decorate([
        core_1.Component({
            moduleId: module.id.toString(),
            selector: 'mdc-button',
            templateUrl: 'mdc-button.component.html',
            animations: [
                animations_1.trigger('ripple', [
                    animations_1.state('1', animations_1.style({})),
                    animations_1.state('0', animations_1.style({})),
                    animations_1.transition('0 <=> 1', animations_1.animate('1s ease-in', animations_1.style({ transform: 'scale(1.0)' })))
                ])
            ]
        }),
        __metadata("design:paramtypes", [])
    ], MdcButtonComponent);
    return MdcButtonComponent;
}());
exports.MdcButtonComponent = MdcButtonComponent;
//# sourceMappingURL=mdc-button.component.js.map