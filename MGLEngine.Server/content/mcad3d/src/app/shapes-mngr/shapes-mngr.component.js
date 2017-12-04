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
var shapes_mngr_service_1 = require("../services/shapes-mngr-service");
var mformmodel_1 = require("../modules/mform/mformmodel");
var list_view_component_1 = require("../list-view/list-view.component");
var ShapeRender = (function () {
    function ShapeRender(shapeForm) {
        this.shapeForm = shapeForm;
    }
    return ShapeRender;
}());
var ShapesMngrComponent = (function () {
    function ShapesMngrComponent(shapesMngrService) {
        this.shapesMngrService = shapesMngrService;
        this.ShapeTypes = [];
        this.RenderTypes = null;
        this.shapes = [];
        this.showAddShapeDialog = false;
        this.shapesListView = [];
    }
    ShapesMngrComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.shapesMngrService.getTypesAsArray().subscribe(function (x) {
            _this.ShapeTypes = x;
            _this.shapesListView = _this.ShapeTypes.map(function (sh) {
                var result = new list_view_component_1.ListViewItem();
                result.imageUrl = "/src/images/" + sh.TypeName + ".svg",
                    result.itemLabel = sh.TypeName;
                result.itemId = sh.TypeName;
                return result;
            });
        });
        this.shapesMngrService.getShapes().subscribe(function (x) {
            _this.shapes = x || [];
            _this.shapeForms = _this.shapes.map(function (sh) { return new mformmodel_1.MFormModel(sh.ShapeData); });
            window["shapeForms"] = _this.shapeForms;
        });
        this.RenderTypes = this.shapesMngrService.getRenderTypes();
    };
    ShapesMngrComponent.prototype.disableAddShapeDialog = function () {
        this.showAddShapeDialog = false;
    };
    ShapesMngrComponent.prototype.enableAddShapeDialog = function () {
        this.showAddShapeDialog = true;
    };
    ShapesMngrComponent.prototype.createShape = function ($event) {
        var _this = this;
        this.shapesMngrService.createShape($event.itemId)
            .subscribe(function (x) {
            _this.shapes.push(x);
            _this.shapeForms.push(new mformmodel_1.MFormModel(x.ShapeData));
        });
        this.disableAddShapeDialog();
    };
    ShapesMngrComponent = __decorate([
        core_1.Component({
            moduleId: module.id.toString(),
            selector: 'app-shapes-mngr',
            templateUrl: './shapes-mngr.component.html'
        }),
        __metadata("design:paramtypes", [shapes_mngr_service_1.ShapesMngrService])
    ], ShapesMngrComponent);
    return ShapesMngrComponent;
}());
exports.ShapesMngrComponent = ShapesMngrComponent;
//# sourceMappingURL=shapes-mngr.component.js.map