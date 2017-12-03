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
require("jsoneditor");
var JsonEditorComponent = (function () {
    function JsonEditorComponent() {
        this.editor = null;
    }
    JsonEditorComponent.prototype.ngOnInit = function () {
        var JSONEditor = window["JSONEditor"];
        this.editor = new JSONEditor(this.jsonPanel.nativeElement, { mode: "code" });
        var json = {
            "Array": [1, 2, 3],
            "Boolean": true,
            "Null": null,
            "Number": 123,
            "Object": { "a": "b", "c": "d" },
            "String": "Hello World"
        };
        this.editor.set("");
    };
    JsonEditorComponent.prototype.setText = function (text) {
        this.editor.set(text);
    };
    JsonEditorComponent.prototype.getText = function () {
        return this.editor.getText();
    };
    JsonEditorComponent.prototype.validateJson = function () {
        try {
            var obj = this.editor.get();
        }
        catch (e) {
            return false;
        }
        return true;
    };
    __decorate([
        core_1.ViewChild("jsonpanel"),
        __metadata("design:type", core_1.ElementRef)
    ], JsonEditorComponent.prototype, "jsonPanel", void 0);
    JsonEditorComponent = __decorate([
        core_1.Component({
            moduleId: module.id,
            selector: 'app-json-editor',
            templateUrl: 'json-editor.component.html'
        }),
        __metadata("design:paramtypes", [])
    ], JsonEditorComponent);
    return JsonEditorComponent;
}());
exports.JsonEditorComponent = JsonEditorComponent;
//# sourceMappingURL=json-editor.component.js.map