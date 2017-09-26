/// <reference path="./defines/jquery.d.ts" />
/// <reference path="./defines/angular.d.ts" />
/// <reference path="./defines/custom.d.ts" />
/// <reference path="./shared/linearalgebra.ts" />
/// <reference path="./shared/svg_plots.ts" />
/// <reference path="./shared/wpf.ts" />
"use strict";
var plots = require("./shared/svg_plots");
var angular = require("angular");
var Interop = require('./shared/wpf');
var Data = (function () {
    function Data(NumElements, minWidth, maxWidth, minHeight, maxHeight, numberOfRuns, rotate, areaUsageValues) {
        if (numberOfRuns === void 0) { numberOfRuns = 1; }
        if (rotate === void 0) { rotate = false; }
        if (areaUsageValues === void 0) { areaUsageValues = []; }
        this.NumElements = NumElements;
        this.minWidth = minWidth;
        this.maxWidth = maxWidth;
        this.minHeight = minHeight;
        this.maxHeight = maxHeight;
        this.numberOfRuns = numberOfRuns;
        this.rotate = rotate;
        this.areaUsageValues = areaUsageValues;
    }
    return Data;
}());
var Ctrl = (function () {
    function Ctrl($wpf, $scope) {
        this.$wpf = $wpf;
        this.$scope = $scope;
        $scope.Data = new Data(50, 10, 100, 10, 100);
    }
    Ctrl.prototype.plotEfficiencyGraph = function (y) {
        var y = this.$scope.Data.areaUsageValues;
        if (y.length <= 1)
            $(".efficiency-graph-container").html("");
        else {
            var options = {
                height: 369,
                width: 545,
                line_width: 0,
                points_size: 2,
                points_type: 'circle',
                color: 'purple',
                padding: [5, 5, 5, 5],
                font_size: 8,
                yrange: [0, 100]
            };
            var x = [];
            for (var i = 0; i < y.length; i++) {
                x.push(i);
            }
            var p = new plots.SvgPlot();
            p.plot2d($(".efficiency-graph-container")[0], x, y, options);
        }
    };
    Ctrl.prototype.Run = function () {
        var i = 0;
        var that = this;
        var data = this.$scope.Data;
        if (data.numberOfRuns <= 1) {
            that.RunOnce();
        }
        else {
            var interval = setInterval(function () {
                that.RunOnce();
                if (++i >= data.numberOfRuns) {
                    clearInterval(interval);
                }
            }, 100);
        }
    };
    Ctrl.prototype.RunOnce = function () {
        var d = this.$wpf.postSync("/binpack/randomrun", this.$scope.Data);
        this.$scope.Data.areaUsageValues.push(d * 100);
        this.plotEfficiencyGraph(this.$scope.Data.areaUsageValues);
    };
    Ctrl.prototype.RunAgain = function () {
    };
    return Ctrl;
}());
///////////////////////////////////////////////////////////////////////////////////////////////////
//Angular initialization with require.js
/////////////////////////////////////////////////////////////////////////////////////////////////
var app = angular.module('app', []);
app.controller('Ctrl', Ctrl);
app.service('$wpf', Interop.Wpf);
var $html = angular.element(document.getElementsByTagName('html')[0]);
angular.element().ready(function () {
    // bootstrap the app manually
    angular.bootstrap(document, ['app']);
});
//$(function () {
//    var p = new plots.SvgPlot();
//    var options: plots.PlotOptionsBase = {
//        height: 369,
//        width: 545,
//        line_width: 0,
//        points_size: 5,
//        points_type: 'circle',
//        color: 'purple',
//        padding: [5, 5, 5, 5],
//        font_size: 8,
//        yrange:[0,500]
//    };
//    var x = [1, 2, 3, 4 , 5];
//    var y = [100, 200, 300,400,500];
//   // p.plot2d($(".efficiency-graph-container")[0],x,y, options);
//});
//# sourceMappingURL=bin_packing.js.map