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
//3525845875
var core_1 = require("@angular/core");
var animations_1 = require("@angular/animations");
var createFocusTrap = require('focus-trap');
var MdcModalComponent = (function () {
    function MdcModalComponent() {
        this.visibleChange = new core_1.EventEmitter();
    }
    MdcModalComponent.prototype.ngOnChanges = function (changes) {
        if (typeof changes["visible"] !== "undefined") {
            if (changes["visible"].currentValue == true)
                document.body.classList.add("mdc-dialog-scroll-lock");
            else
                document.body.classList.remove("mdc-dialog-scroll-lock");
        }
    };
    MdcModalComponent.prototype.ngOnInit = function () {
        if (this.type == 'primary') {
            this.css_class = "mdc-button--raised";
        }
    };
    MdcModalComponent.prototype.ngAfterViewInit = function () {
        var that = this;
        this.focusTrap = createFocusTrap(this.main.nativeElement, {
            onDeactivate: function () {
                that.focusDeactivated();
            },
            clickOutsideDeactivates: this.closeOnClickOut
        });
    };
    MdcModalComponent.prototype.focusDeactivated = function () {
        if (this.closeOnClickOut) {
            this.close();
        }
    };
    MdcModalComponent.prototype.close = function () {
        this.visible = false;
        this.visibleChange.emit(this.visible);
    };
    MdcModalComponent.prototype.clicked = function (event) {
        console.log(event);
    };
    __decorate([
        core_1.Input(),
        __metadata("design:type", String)
    ], MdcModalComponent.prototype, "type", void 0);
    __decorate([
        core_1.Input(),
        __metadata("design:type", Boolean)
    ], MdcModalComponent.prototype, "visible", void 0);
    __decorate([
        core_1.Input(),
        __metadata("design:type", Boolean)
    ], MdcModalComponent.prototype, "closeOnClickOut", void 0);
    __decorate([
        core_1.Output(),
        __metadata("design:type", core_1.EventEmitter)
    ], MdcModalComponent.prototype, "visibleChange", void 0);
    __decorate([
        core_1.ViewChild("mainPanel"),
        __metadata("design:type", core_1.ElementRef)
    ], MdcModalComponent.prototype, "main", void 0);
    MdcModalComponent = __decorate([
        core_1.Component({
            moduleId: module.id.toString(),
            selector: 'mdc-modal',
            templateUrl: 'mdc-modal.component.html',
            animations: [
                animations_1.trigger('visibleAnim', [
                    animations_1.state('1', animations_1.style({ opacity: 1, transform: "scale(1) translate(0px,0px)", top: "0px" })),
                    animations_1.state('0', animations_1.style({ opacity: 0, transform: "scale(0.75) translate(0px,250px)" })),
                    animations_1.transition('0 => 1', animations_1.animate('0.25s cubic-bezier(0, 0, .2, 1)')),
                    animations_1.transition('1 => 0', animations_1.animate('0.25s cubic-bezier(.4,0,.6,1)'))
                ])
            ]
        }),
        __metadata("design:paramtypes", [])
    ], MdcModalComponent);
    return MdcModalComponent;
}());
exports.MdcModalComponent = MdcModalComponent;
//# sourceMappingURL=mdc-modal.component.js.map