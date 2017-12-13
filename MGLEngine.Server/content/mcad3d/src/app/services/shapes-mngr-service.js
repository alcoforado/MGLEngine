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
var http_1 = require("@angular/http");
require("rxjs/Rx");
var Observable_1 = require("rxjs/Observable");
var core_1 = require("@angular/core");
var ErrorResult = (function () {
    function ErrorResult() {
    }
    return ErrorResult;
}());
exports.ErrorResult = ErrorResult;
var UpdateShapeUI = (function () {
    function UpdateShapeUI() {
    }
    return UpdateShapeUI;
}());
exports.UpdateShapeUI = UpdateShapeUI;
var ShapeUI = (function () {
    function ShapeUI(Name, Id, ShapeData, TopologyType, RenderData, RenderType, TopologyTypeName, RenderTypeName) {
        this.Name = Name;
        this.Id = Id;
        this.ShapeData = ShapeData;
        this.TopologyType = TopologyType;
        this.RenderData = RenderData;
        this.RenderType = RenderType;
        this.TopologyTypeName = TopologyTypeName;
        this.RenderTypeName = RenderTypeName;
    }
    return ShapeUI;
}());
exports.ShapeUI = ShapeUI;
var ShapesMngrService = (function () {
    function ShapesMngrService($http) {
        this.$http = $http;
        this.TypesHash = null;
        this.Types = null;
        this.RenderTypes = null;
    }
    ShapesMngrService.prototype.extractData = function (res) {
        var body = res.json();
        return (body || {});
    };
    ShapesMngrService.prototype.responseToArrayUIType = function (res) {
        var body = res.json();
        var types = (body || {});
        return types.filter(function (x) {
            x.CssTypeName = x.TypeName.toLowerCase().replace(" ", "-");
            return x;
        });
    };
    ShapesMngrService.prototype.getRenderTypes = function () {
        if (this.RenderTypes == null) {
            this.RenderTypes = this.$http.get("/api/shapemngr/rendertypes")
                .map(this.extractData)
                .map(function (c) {
                return c.filter(function (x) {
                    x.CssTypeName = x.TypeName.toLowerCase().replace(" ", "-");
                    return x;
                });
            });
        }
        return this.RenderTypes;
    };
    ShapesMngrService.prototype.getTypes = function () {
        if (this.Types == null) {
            this.Types = this.$http.get("/api/shapemngr/shapetypes").map(this.extractData);
            this.TypesHash = this.Types.map(function (c) {
                var typeHash = {};
                c.forEach(function (elem) {
                    typeHash[elem.TypeName] = elem;
                });
                return typeHash;
            });
        }
        return this.TypesHash;
    };
    ShapesMngrService.prototype.getTypesAsArray = function () {
        this.getTypes();
        return this.Types;
    };
    ShapesMngrService.prototype.getType = function (name) {
        if (typeof (this.getTypes()[name]) == "undefined")
            throw "Type " + name + " not found";
        else {
            return this.Types[name];
        }
    };
    ShapesMngrService.prototype.getShapes = function () {
        var _this = this;
        return this.getTypes().mergeMap(function (types) {
            return _this.$http.get('api/shapemngr/shapes')
                .map(_this.extractData)
                .map(function (shapes) {
                shapes.forEach(function (elem) {
                    elem.TopologyType = types[elem.TopologyTypeName];
                    elem.RenderType = null;
                });
                return shapes;
            });
        });
    };
    ShapesMngrService.prototype.createShape = function (UIType) {
        var _this = this;
        return this.$http.post("/api/shapemngr/shape/" + UIType, "")
            .map(this.extractData)
            .mergeMap(function (sh) {
            return _this.getTypes()
                .map(function (x) {
                sh.TopologyType = x[sh.TopologyTypeName];
                sh.RenderData = null;
                return sh;
            });
        });
    };
    ShapesMngrService.prototype.updateShape = function (sh) {
        var _this = this;
        var obj = {
            Id: sh.Id,
            Name: sh.Name,
            RenderType: sh.RenderType.TypeName,
            RenderJsonData: JSON.stringify(sh.RenderData),
            TopologyType: sh.TopologyType.TypeName,
            TopologyJsonData: JSON.stringify(sh.ShapeData)
        };
        return this.$http.put("/api/shapemngr/shape", obj)
            .catch(function (r) {
            return Observable_1.Observable.throw(_this.extractData(r));
        });
    };
    ShapesMngrService = __decorate([
        core_1.Injectable(),
        __metadata("design:paramtypes", [http_1.Http])
    ], ShapesMngrService);
    return ShapesMngrService;
}());
exports.ShapesMngrService = ShapesMngrService;
//# sourceMappingURL=shapes-mngr-service.js.map