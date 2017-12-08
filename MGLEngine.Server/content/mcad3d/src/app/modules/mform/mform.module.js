"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
var platform_browser_1 = require("@angular/platform-browser");
var core_1 = require("@angular/core");
var forms_1 = require("@angular/forms");
var number_input_component_1 = require("./number-input/number-input.component");
var dynamic_input_component_1 = require("./dynamic-input/dynamic-input.component");
var text_input_component_1 = require("./text-input/text-input.component");
var drop_box_component_1 = require("./drop-box/drop-box.component");
var vec2_array_componen_1 = require("./vec2-array/vec2-array.componen;");
t;
't';
var MFormModule = (function () {
    function MFormModule() {
    }
    MFormModule = __decorate([
        core_1.NgModule({
            declarations: [
                number_input_component_1.NumberInputComponent,
                text_input_component_1.TextInputComponent,
                drop_box_component_1.DropBoxComponent,
                dynamic_input_component_1.DynamicInputComponent,
                Vec2InputCompone,
                vec2_array_componen_1.Vec2ArrayComponent,
                ColorInputComponentnt
            ],
            imports: [
                forms_1.ReactiveFormsModule,
                platform_browser_1.BrowserModule
            ],
            exports: [
                number_input_component_1.NumberInputComponent,
                text_input_component_1.TextInputComponent,
                drop_box_component_1.DropBoxComponent,
                dynamic_input_component_1.DynamicInputComponent
            ],
            providers: []
        })
    ], MFormModule);
    return MFormModule;
}());
exports.MFormModule = MFormModule;
//# sourceMappingURL=mform.module.js.map