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
var DropBoxComponent = (function () {
    function DropBoxComponent() {
        this.isExpanded = false;
        this.selectedIndex = 0;
        this.items = [];
        this.fieldName = null;
    }
    DropBoxComponent.prototype.ngOnInit = function () {
        if (this.isEmpty()) {
            if (this.fieldName == null) {
                this.fieldName = "label";
            }
            this.items = [{}];
            this.items[0][this.fieldName] = " ";
        }
    };
    DropBoxComponent.prototype.isEmpty = function () {
        return this.items == null || this.items.length == 0;
    };
    DropBoxComponent.prototype.item_clicked = function (evt) {
        var i = evt.srcElement.getAttribute("data-option-array-index");
        if (i == null || i == "")
            throw "No array index was found for option";
        var ii = parseInt(i);
        this.selectedIndex = ii;
    };
    DropBoxComponent.prototype.clicked = function () {
        if (this.items == null || this.items.length == 0)
            return;
        this.isExpanded = !this.isExpanded;
    };
    __decorate([
        core_1.Input(),
        __metadata("design:type", Array)
    ], DropBoxComponent.prototype, "items", void 0);
    __decorate([
        core_1.Input(),
        __metadata("design:type", String)
    ], DropBoxComponent.prototype, "fieldName", void 0);
    DropBoxComponent = __decorate([
        core_1.Component({
            moduleId: module.id.toString(),
            selector: 'app-drop-box',
            templateUrl: './drop-box.component.html',
        }),
        __metadata("design:paramtypes", [])
    ], DropBoxComponent);
    return DropBoxComponent;
}());
exports.DropBoxComponent = DropBoxComponent;
//# sourceMappingURL=drop-box.component.js.map