/// <reference path="./wpf.ts" />
/// <reference path="./models.ts" />
/// <reference path="../defines/angular.d.ts" />
"use strict";
var Settings = (function () {
    function Settings($wpf) {
        this.$wpf = $wpf;
    }
    Settings.prototype.DeepCopy = function (src, dst) {
        if (dst == null || src == null)
            return;
        for (var property in dst) {
            if (src.hasOwnProperty(property) && dst.hasOwnProperty(property)) {
                if (typeof (src[property]) == "object" && typeof (dst[property] == "object")) {
                    this.DeepCopy(src[property], dst[property]);
                }
                else
                    dst[property] = src[property];
            }
        }
    };
    Settings.prototype.Save = function (key, object) {
        this.$wpf.postSync("persistence/save", { key: key, json: JSON.stringify(object) });
    };
    Settings.prototype.Load = function (key) {
        var json = this.$wpf.postSync("persistence/load", { key: key });
        var value = JSON.parse(json);
        return value;
    };
    Settings.prototype.SetObject = function (key, object) {
        var json = this.$wpf.postSync("persistence/load", { key: key });
        var value = JSON.parse(json);
        this.DeepCopy(value, object);
        return object;
    };
    return Settings;
}());
exports.Settings = Settings;
var ShapeMngr = (function () {
    function ShapeMngr($wpf) {
        this.$wpf = $wpf;
        this.Types = null;
    }
    ShapeMngr.prototype.GetTypes = function () {
        var _this = this;
        if (this.Types == null) {
            this.Types = {};
            this.TypesArray = this.$wpf.postSync("shapesmngr/gettypes");
            this.TypesArray.forEach(function (elem) {
                _this.Types[elem.typeName] = elem;
            });
        }
        return this.Types;
    };
    ShapeMngr.prototype.GetTypesAsArray = function () {
        this.GetTypes();
        return this.TypesArray;
    };
    ShapeMngr.prototype.GetType = function (name) {
        if (typeof (this.GetTypes()[name]) == "undefined")
            throw "Type " + name + " not found";
        else {
            return this.Types[name];
        }
    };
    ShapeMngr.prototype.GetShapes = function () {
        var _this = this;
        var value = this.$wpf.postSync("shapesmngr/getshapes");
        value.forEach(function (elem) {
            elem.type = _this.GetType(elem.shapeType);
        });
        return value;
    };
    ShapeMngr.prototype.CreateShape = function (type) {
        return this.$wpf.postSync("shapesmngr/createShape", {});
    };
    return ShapeMngr;
}());
exports.ShapeMngr = ShapeMngr;
function registerServices(app) {
    app.service('$settings', Settings);
    app.service('$shapesMngr', ShapeMngr);
}
exports.registerServices = registerServices;
//# sourceMappingURL=services.js.map