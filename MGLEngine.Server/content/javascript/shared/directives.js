/// <reference path="../defines/angular.d.ts" />
/// <reference path="../defines/jquery.d.ts" />
/// <reference path="../templates.ts" />
/// <reference path="../shared/models.ts" />
/// <reference path="../defines/spectrum.d.ts"/>
/// <reference path="linearalgebra.ts"/>
/// <reference path="../defines/spectrum.d.ts" />
"use strict";
var templates = require("../templates");
var la = require("../shared/linearalgebra");
var $ = require("jquery");
var spectrum = require('spectrum');
var e = typeof spectrum;
var VectorPicker = (function () {
    /*
        updateDialog(scope: IVectorPickerScope) {
            var xy =
        }
        */
    //scope: any;
    function VectorPicker() {
        this.scope = {
            vector: "="
        };
        this.restrict = 'E';
        this.template = templates.vectorpicker;
        this.link = function (scope, element, attributes) {
            var dim = 100;
            var rotXYZ = 0;
            var xy = element.find("#xy");
            var xyz = element.find("#xyz");
            scope.RotXY = 0;
            scope.RotXYZ = 0;
            scope.CssRotXYZ = 0;
            scope.CssRotXY = 0;
            scope.norm = 1;
            scope.showDialog = false;
            scope.displayDialog = function (ev) {
                scope.showDialog = true;
            };
            scope.hideDialog = function (ev) {
                scope.showDialog = false;
            };
            scope.$watch('RotXY', function (newValue, oldValue, scope) {
                var rotxy = scope.RotXY;
                scope.CssRotXY = 360 - rotxy;
                xy.css('transform', "rotate(" + scope.CssRotXY + "deg)");
                VectorPicker.updateInput(scope);
            });
            VectorPicker.updateControl(scope);
            scope.$watch('RotXYZ', function (newValue, oldValue, scope) {
                var rotxyz = scope.RotXYZ;
                scope.CssRotXYZ = 360 - rotxyz;
                xyz.css('transform', "rotate(" + scope.CssRotXYZ + "deg)");
                VectorPicker.updateInput(scope);
            });
            scope.$watch('norm', function (newValue, oldValue, scope) {
                VectorPicker.updateInput(scope);
            });
            scope.$watch('vector.X + vector.Y + vector.Z', function (newValue, oldValue, scope) {
                VectorPicker.updateControl(scope);
            });
            var re = new RegExp("<\\d+.(?=\\d{1,3}),\\d+.(?=\\d{1,3}),\\d+.(?=\\d{1,3})>");
            element[0].addEventListener("mousewheel", function (ev) {
                if (ev.wheelDelta > 0) {
                    scope.norm *= 1.1;
                    scope.$apply();
                }
                else if (ev.wheelDelta < 0) {
                    scope.norm *= 0.9;
                    scope.$apply();
                }
                ev.preventDefault();
            });
            xy.on('mousedown', function (event) {
                var v = new la.Vec2([event.offsetX, event.offsetY]);
                var o = new la.Vec2([dim / 2.0, dim / 2.0]);
                var d = v.sub(o);
                var that = $(event.target);
                event.preventDefault();
                var angle = d.angleDeg();
                //alert("Angle: " + angle + "deg =>" + rot);
                scope.CssRotXY += angle;
                scope.CssRotXY = scope.CssRotXY % 360;
                that.css('transform', "rotate(" + scope.CssRotXY + "deg)");
                scope.RotXY = parseFloat((360 - scope.CssRotXY % 360).toFixed(0));
                scope.$apply();
                //element[0].style.width = '400px';
            });
            xyz.on('mousedown', function (event) {
                var v = new la.Vec2([event.offsetX, event.offsetY]);
                var o = new la.Vec2([dim / 2.0, dim / 2.0]);
                var d = v.sub(o);
                var that = $(event.target);
                event.preventDefault();
                var angle = d.angleDeg();
                scope.CssRotXYZ += angle;
                scope.CssRotXYZ = scope.CssRotXYZ % 360;
                that.css('transform', "rotate(" + scope.CssRotXYZ + "deg)");
                scope.RotXYZ = parseFloat((360 - scope.CssRotXYZ % 360).toFixed(0));
                scope.$apply();
            });
        };
    }
    VectorPicker.updateInput = function (scope) {
        var v = (new la.Vec3([scope.norm, la.Angle.toRad(scope.RotXY), la.Angle.toRad(scope.RotXYZ)]));
        scope.vector.X;
        scope.vector.Y;
        scope.vector.Z;
        var x = v[0] * Math.cos(v[1]) * Math.cos(v[2]);
        var y = v[0] * Math.sin(v[1]) * Math.cos(v[2]);
        var z = v[0] * Math.sin(v[2]);
        if (la.gl_equal(x, scope.vector.X) &&
            la.gl_equal(y, scope.vector.Y) &&
            la.gl_equal(z, scope.vector.Z))
            return;
        if (Math.abs(x) < 1.e-10)
            x = 0.0;
        if (Math.abs(y) < 1.e-10)
            y = 0.0;
        if (Math.abs(z) < 1.e-10)
            z = 0.0;
        scope.vector.X = x;
        scope.vector.Y = y;
        scope.vector.Z = z;
    };
    VectorPicker.updateControl = function (scope) {
        var v = (new la.Vec3([scope.vector.X, scope.vector.Y, scope.vector.Z]));
        scope.norm = Math.sqrt(scope.vector.X * scope.vector.X + scope.vector.Y * scope.vector.Y + scope.vector.Z * scope.vector.Z);
        scope.RotXYZ = Math.asin(scope.vector.Z / scope.norm);
        if (scope.RotXYZ < 0.0)
            scope.RotXYZ = scope.RotXYZ + Math.PI * 2;
        scope.RotXYZ = la.Angle.toDeg(scope.RotXYZ);
        var hypXY = Math.sqrt(scope.vector.X * scope.vector.X + scope.vector.Y * scope.vector.Y);
        if (la.gl_equal(hypXY, 0)) {
            scope.RotXY = 0;
        }
        else {
            scope.RotXY = Math.acos(scope.vector.X / hypXY);
            if (scope.vector.Y < 0)
                scope.RotXY = Math.PI * 2 - scope.RotXY;
            scope.RotXY = la.Angle.toDeg(scope.RotXY);
        }
    };
    return VectorPicker;
}());
exports.VectorPicker = VectorPicker;
var DxColorPicker = (function () {
    function DxColorPicker() {
        this.restrict = 'E';
        this.require = 'ngModel';
        this.scope = { cl: "@" };
    }
    DxColorPicker.prototype.template = function () { return '<input id="DxColorPicker{0}" type="text" ng-model="cl" />'.replace("{0}", (DxColorPicker.idCount++).toString()); };
    DxColorPicker.componentToHex = function (c) {
        var hex = (c * 255).toString(16);
        return hex.length == 1 ? "0" + hex : hex;
    };
    DxColorPicker.toColorString = function (color) {
        return "#" +
            DxColorPicker.componentToHex(color.X) +
            DxColorPicker.componentToHex(color.Y) +
            DxColorPicker.componentToHex(color.Z);
    };
    DxColorPicker.prototype.link = function (scope, instanceElement, instanceAttributes, controller, transclude) {
        instanceElement.find("input").spectrum({
            preferredFormat: "hex",
        });
        controller.$render = function () {
            scope.cl = controller.$viewValue.cl;
            instanceElement.find("input").spectrum("set", scope.cl);
        };
        controller.$parsers.push(function (viewValue) {
            var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(viewValue.cl);
            var parsed = {
                X: parseInt(result[1], 16) / 255.0,
                Y: parseInt(result[2], 16) / 255.0,
                Z: parseInt(result[3], 16) / 255.0
            };
            return parsed;
        });
        controller.$formatters.push(function (modelValue) {
            var hex = DxColorPicker.toColorString(modelValue);
            return {
                cl: hex
            };
        });
        scope.$watch('cl', function () {
            controller.$setViewValue({ cl: scope.cl });
        });
    };
    return DxColorPicker;
}());
exports.DxColorPicker = DxColorPicker;
var ShapeForm = (function () {
    function ShapeForm($compile) {
        this.$compile = $compile;
        this.restrict = "E";
        this.scope = {
            shape: "="
        };
        this.link = this._link.bind(this);
    }
    ShapeForm.prototype.template = function () {
        return '<form class="main-form"><div class="form-header"><img src="../images/shapes.svg"/>{{shape.type.typeName}}</div><div class="form-body"></div></form>';
    };
    ShapeForm.prototype._link = function (scope, instanceElement, instanceAttributes, controller, transclude) {
        var result = "";
        var shape = scope.shape;
        var template = this.createTemplate(shape.type, "shape.shapeData");
        var el = this.$compile(template)(scope);
        var recompileElem = instanceElement.find(".form-body");
        //recompileElem.html(el);
    };
    ShapeForm.prototype.createTemplate = function (type, scopeDatadPath) {
        var result = "";
        type.members.forEach(function (member) {
            var inputHtml = "";
            var fieldPath = scopeDatadPath + "." + member.fieldName;
            switch (member.directiveType.toLowerCase()) {
                case "number":
                case "int":
                case "float":
                case "double":
                    inputHtml = "<input class=\"input-number\" type=\"number\" name=\"" + member.fieldName + "\" ng-model=\"" + fieldPath + "\"/>";
                    break;
                default:
                    throw "Shape member type " + member.directiveType.toLowerCase() + " is unknown";
            }
            result += "<div class=\"form-input\">\n                            <span class=\"span-label\">\n                                " + member.labelName + ":\n                            </span>\n                            " + inputHtml + "\n                        </div>";
        });
        return result;
    };
    return ShapeForm;
}());
exports.ShapeForm = ShapeForm;
function RegisterDirectives(app) {
    app.directive('vectorPicker', function () { return new VectorPicker(); });
    app.directive('dxColorPicker', function () { return new DxColorPicker(); });
    app.directive('shapeform', ["$compile", function ($compile) { return new ShapeForm($compile); }]);
}
exports.RegisterDirectives = RegisterDirectives;
//# sourceMappingURL=directives.js.map