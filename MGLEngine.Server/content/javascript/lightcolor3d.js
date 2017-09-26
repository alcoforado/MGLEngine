/// <reference path="./defines/jquery.d.ts" />
/// <reference path="./defines/angular.d.ts" />
/// <reference path="./defines/custom.d.ts" />
/// <reference path="./shared/linearalgebra.ts" />
/// <reference path="./shared/svg_plots.ts" />
/// <reference path="./shared/wpf.ts" />
/// <reference path="./defines/ui-bootstrap.d.ts"/>
/// <reference path="./shared/models.ts"/>
/// <reference path="./shared/services.ts"/>
/// 
"use strict";
var angular = require("angular");
var directives = require("./shared/directives");
var Interop = require('./shared/wpf');
var ui_bootstrap = require('ui-bootstrap');
var dx = require('./shared/models');
var Services = require('./shared/services');
var d = typeof ui_bootstrap;
var Ctrl = (function () {
    function Ctrl($wpf, $settings, $shapesMngr, $scope) {
        this.$wpf = $wpf;
        this.$settings = $settings;
        this.$shapesMngr = $shapesMngr;
        this.$scope = $scope;
        $scope.dirLight = new dx.DirectionalLightData(new dx.DXVector4(1, 0, 0, 0), new dx.DXVector4(0, 0, 0, 0), new dx.DXVector3(0, 0, 0), 0, new dx.DXVector3(1, 1, 1));
        $settings.SetObject("lights", $scope.dirLight);
        $scope.shapes = $shapesMngr.GetShapes();
        $scope.types = $shapesMngr.GetTypesAsArray();
    }
    Ctrl.prototype.set_lights = function () {
        //this.$scope
        this.$settings.Save("lights", this.$scope.dirLight);
        this.$wpf.postSync("cad/setlights", this.$scope.dirLight);
    };
    Ctrl.prototype.createShape = function (type) {
        this.$shapesMngr.CreateShape(type);
    };
    return Ctrl;
}());
var Test = (function () {
    function Test() {
    }
    return Test;
}());
var app = angular.module('app', ['ui.bootstrap']);
app.controller('Ctrl', Ctrl);
if (typeof (window.external.JavascriptRequest) != "undefined")
    app.service('$wpf', Interop.Wpf);
else
    app.service('$wpf', Interop.MoqWpf);
Services.registerServices(app);
//app.service('$settings', Services.Settings);
//app.service('$shapesMngr', Services.ShapeMngr);
directives.RegisterDirectives(app);
//Register Fixtures
Interop.MoqWpf.Fixtures["persistence/save"] = null;
Interop.MoqWpf.Fixtures["persistence/load"] = null;
Interop.MoqWpf.Fixtures["shapesmngr/gettypes"] = [
    {
        typeName: "OrthoMesh",
        members: [
            {
                fieldName: "elemsX",
                labelName: "elements in X",
                directiveType: "number"
            }, {
                fieldName: "elemsY",
                labelName: "elements in Y",
                directiveType: "number"
            }
        ]
    }
];
Interop.MoqWpf.Fixtures["shapesmngr/getshapes"] = [
    {
        shapeType: "OrthoMesh",
        shapeData: {
            elemsX: 5,
            elemsY: 6
        }
    },
    {
        shapeType: "OrthoMesh",
        shapeData: {
            elemsX: 2,
            elemsY: 3
        }
    }
];
var $html = angular.element(document.getElementsByTagName('html')[0]);
angular.element().ready(function () {
    angular.bootstrap(document, ['app']);
});
//# sourceMappingURL=lightcolor3d.js.map