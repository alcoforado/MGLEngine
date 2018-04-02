"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
var core_1 = require("@angular/core");
var forms_1 = require("@angular/forms");
var platform_browser_1 = require("@angular/platform-browser");
var http_1 = require("@angular/http");
var shapes_mngr_service_1 = require("./services/shapes-mngr-service");
var shapes_mngr_component_1 = require("./shapes-mngr/shapes-mngr.component");
var app_component_1 = require("./app.component");
var mform_module_1 = require("./modules/mform/mform.module");
var list_view_component_1 = require("./list-view/list-view.component");
var processing_animation_component_1 = require("./processing-animation/processing-animation.component");
var router_1 = require("@angular/router");
var triangle2d_component_1 = require("./shapes/triangle2d/triangle2d.component");
var modal_component_1 = require("./modal/modal.component");
var color_render2d_component_1 = require("./renders/color-render2d/color-render2d.component");
var mdc_button_component_1 = require("./mdc-button/mdc-button.component");
var animations_1 = require("@angular/platform-browser/animations");
var appRoutes = [
    { path: 'shapes', component: shapes_mngr_component_1.ShapesMngrComponent },
    { path: 'src/index_system.html', component: shapes_mngr_component_1.ShapesMngrComponent },
    { path: 'src/index_system.html', redirectTo: 'src/index_system.html#shapes', pathMatch: 'full' }
];
var AppModule = (function () {
    function AppModule() {
    }
    AppModule = __decorate([
        core_1.NgModule({
            imports: [
                http_1.HttpModule,
                platform_browser_1.BrowserModule,
                forms_1.ReactiveFormsModule,
                mform_module_1.MFormModule,
                animations_1.BrowserAnimationsModule,
                router_1.RouterModule.forRoot(appRoutes)
            ],
            declarations: [
                app_component_1.AppComponent,
                shapes_mngr_component_1.ShapesMngrComponent,
                list_view_component_1.ListViewComponent,
                processing_animation_component_1.ProcessingAnimationComponent,
                triangle2d_component_1.Triangle2dComponent,
                modal_component_1.ModalComponent,
                color_render2d_component_1.ColorRender2DComponent,
                mdc_button_component_1.MdcButtonComponent
            ],
            providers: [
                shapes_mngr_service_1.ShapesMngrService
            ],
            bootstrap: [app_component_1.AppComponent]
        })
    ], AppModule);
    return AppModule;
}());
exports.AppModule = AppModule;
//# sourceMappingURL=app.module.js.map