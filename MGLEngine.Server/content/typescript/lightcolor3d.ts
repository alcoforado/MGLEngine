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

import la = require("./shared/linearalgebra");
import angular = require("angular");
import directives = require("./shared/directives");
import Interop = require('./shared/wpf');
import ui_bootstrap = require('ui-bootstrap');
import dx = require('./shared/models');
import Services = require('./shared/services');

import ShapeType = dx.ShapeType;
import ShapeUi = dx.ShapeUI;
var d = typeof ui_bootstrap;

interface IScope extends ng.IScope {
    dirLight: dx.DirectionalLightData;
    shapes: Array<ShapeUi>;
    types:Array<ShapeType>;
}




class Ctrl {




    constructor(private $wpf: Interop.Wpf, private $settings: Services.Settings, private $shapesMngr:Services.ShapeMngr, private $scope: IScope) {
        $scope.dirLight = new dx.DirectionalLightData(
            new dx.DXVector4(1, 0, 0, 0),
            new dx.DXVector4(0, 0, 0, 0),
            new dx.DXVector3(0, 0, 0),
            0,
            new dx.DXVector3(1, 1,1));
        $settings.SetObject("lights", $scope.dirLight);
        $scope.shapes = $shapesMngr.GetShapes();
        $scope.types = $shapesMngr.GetTypesAsArray();
    }

    set_lights() {
        //this.$scope
        this.$settings.Save("lights",this.$scope.dirLight);
        this.$wpf.postSync("cad/setlights", this.$scope.dirLight);   
    }

    createShape(type: ShapeType) {
        this.$shapesMngr.CreateShape(type)
    }

}

class Test {
    constructor() { }
}



var app = angular.module('app', ['ui.bootstrap']);
app.controller('Ctrl', Ctrl);

if (typeof ((<any> window.external).JavascriptRequest) != "undefined")
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




var $html = angular.element((<any> document).getElementsByTagName('html')[0]);
angular.element().ready(function () {
    angular.bootstrap(document, ['app']);
});



