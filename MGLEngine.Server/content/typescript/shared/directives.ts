/// <reference path="../defines/angular.d.ts" />
/// <reference path="../defines/jquery.d.ts" />
/// <reference path="../templates.ts" />
/// <reference path="../shared/models.ts" />
/// <reference path="../defines/spectrum.d.ts"/>
/// <reference path="linearalgebra.ts"/>
/// <reference path="../defines/spectrum.d.ts" />


import templates = require("../templates");
import angular = require("angular");
import la = require("../shared/linearalgebra");
import $ = require("jquery");
import dx = require("../shared/models");
import spectrum = require('spectrum');
import ShapeUI = dx.ShapeUI;
import ShapeType = dx.ShapeType;
var e = typeof spectrum;




interface IVectorPickerScope extends ng.IScope {
    RotXY: number;
    RotXYZ: number;
    CssRotXYZ: number;
    CssRotXY: number;
    norm: number;
    vector: dx.DXVector3;
    showDialog: boolean;
    displayDialog(ev: any):void;
    hideDialog(ev:any):void;
    
}






export class VectorPicker implements angular.IDirective
{
    template: string;
    restrict: string;
    
    link: ng.IDirectiveLinkFn;

    scope:any =  {
        vector: "=" 
    }


    static updateInput(scope: IVectorPickerScope) {
        var v: la.Vec3 = (new la.Vec3([scope.norm, la.Angle.toRad(scope.RotXY), la.Angle.toRad(scope.RotXYZ)]));

        scope.vector.X;
        scope.vector.Y;
        scope.vector.Z;


        var x = v[0] * Math.cos(v[1]) * Math.cos(v[2]);
        var y = v[0]*Math.sin(v[1]) * Math.cos(v[2]);
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
        scope.vector.X=x;
        scope.vector.Y=y;
        scope.vector.Z=z;

    }

    static updateControl(scope: IVectorPickerScope) {
        var v: la.Vec3 = (new la.Vec3([scope.vector.X, scope.vector.Y, scope.vector.Z]));


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
    }




/*
    updateDialog(scope: IVectorPickerScope) {
        var xy = 
    }
    */
    //scope: any;
    constructor()
    {
        this.restrict = 'E';
        this.template = templates.vectorpicker;
        
        
        this.link = (scope: IVectorPickerScope, element: ng.IAugmentedJQuery, attributes: ng.IAttributes) =>
       {
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
           scope.displayDialog = (ev:any) => {
               scope.showDialog = true;
           }
           scope.hideDialog = (ev: any) => {
               scope.showDialog = false;
           }


          

           scope.$watch('RotXY',(newValue:number,oldValue:number,scope:IVectorPickerScope) => {
               var rotxy = scope.RotXY;
               scope.CssRotXY = 360 - rotxy;
               xy.css('transform', "rotate(" + scope.CssRotXY + "deg)");
               VectorPicker.updateInput(scope);
           });

       
           VectorPicker.updateControl(scope);

           scope.$watch('RotXYZ',(newValue: number, oldValue: number, scope: IVectorPickerScope) => {
               var rotxyz = scope.RotXYZ;
               scope.CssRotXYZ = 360 - rotxyz;
               xyz.css('transform', "rotate(" + scope.CssRotXYZ + "deg)");
               VectorPicker.updateInput(scope);
           });

           scope.$watch('norm',(newValue: number, oldValue: number, scope: IVectorPickerScope) => {
               VectorPicker.updateInput(scope);
           });

           scope.$watch('vector.X + vector.Y + vector.Z',(newValue: number, oldValue: number, scope: IVectorPickerScope) => {
               VectorPicker.updateControl(scope);
           });

           var re = new RegExp("<\\d+.(?=\\d{1,3}),\\d+.(?=\\d{1,3}),\\d+.(?=\\d{1,3})>");

           element[0].addEventListener("mousewheel", function (ev: any) {
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
           xy.on('mousedown',(event: JQueryEventObject) => {
               var v = new la.Vec2([event.offsetX, event.offsetY]);
               var o = new la.Vec2([dim / 2.0, dim / 2.0]);
               var d = v.sub(o);
               var that = $(event.target)
               event.preventDefault();
               var angle = d.angleDeg();
               //alert("Angle: " + angle + "deg =>" + rot);
               scope.CssRotXY += angle;
               scope.CssRotXY = scope.CssRotXY % 360;
               that.css('transform', "rotate(" + scope.CssRotXY + "deg)");
               scope.RotXY = parseFloat((360   - scope.CssRotXY %360).toFixed(0));
               scope.$apply();
               //element[0].style.width = '400px';
           });


           xyz.on('mousedown',(event: JQueryEventObject) => {
               var v = new la.Vec2([event.offsetX, event.offsetY]);
               var o = new la.Vec2([dim / 2.0, dim / 2.0]);
               var d = v.sub(o);
               var that = $(event.target)
               event.preventDefault();
               var angle = d.angleDeg();
               scope.CssRotXYZ += angle;
               scope.CssRotXYZ = scope.CssRotXYZ % 360;
               that.css('transform', "rotate(" + scope.CssRotXYZ + "deg)");
               scope.RotXYZ = parseFloat((360 - scope.CssRotXYZ % 360).toFixed(0));
               scope.$apply();


              
           });

           


          

      
               

           }
       }
}

export class DxColorPicker implements angular.IDirective {
    template(): string { return '<input id="DxColorPicker{0}" type="text" ng-model="cl" />'.replace("{0}",(DxColorPicker.idCount++).toString()) }
    restrict: string = 'E';
    require: string = 'ngModel';
    static idCount: number;
    scope: any = { cl: "@" };
    constructor() {
    }

    static componentToHex(c: number): string {
        var hex = (c*255).toString(16);
        return hex.length == 1 ? "0" + hex : hex;
    }

    static toColorString(color:dx.DXVector3):string
    {
        return "#" +
            DxColorPicker.componentToHex(color.X) +
            DxColorPicker.componentToHex(color.Y) +
            DxColorPicker.componentToHex(color.Z);

    }


    link(   
        scope: any,
        instanceElement: angular.IAugmentedJQuery,
        instanceAttributes: angular.IAttributes,
        controller: angular.INgModelController,
        transclude: angular.ITranscludeFunction)
    {
        (<any> instanceElement.find("input")).spectrum(
            {
                preferredFormat: "hex",
            }
            );

        controller.$render = () => {
            scope.cl = controller.$viewValue.cl;
            (<any> instanceElement.find("input")).spectrum("set", scope.cl);
        }

        controller.$parsers.push((viewValue: any) => {
            var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(viewValue.cl);
            var parsed: any = {
                X: parseInt(result[1], 16)/255.0,
                Y: parseInt(result[2], 16)/255.0,
                Z: parseInt(result[3],16)/255.0
            };
            return parsed;
        })



        
        controller.$formatters.push((modelValue: any) => {
            var hex: string = DxColorPicker.toColorString(<dx.DXVector3> modelValue);
            return {
                cl: hex
            };
        });

        scope.$watch('cl',() => {
            controller.$setViewValue({ cl: scope.cl });
        });

    }

}

export class ShapeForm implements angular.IDirective {
    
    restrict = "E";
    scope: any = {
        shape:"="
    };

    constructor(private $compile: ng.ICompileService) {
        this.link = (<any> this._link).bind(this);
    }


    template(): string {
        return '<form class="main-form"><div class="form-header"><img src="../images/shapes.svg"/>{{shape.type.typeName}}</div><div class="form-body"></div></form>';
    }







    public link: any;

    _link(
        scope: any,
        instanceElement: angular.IAugmentedJQuery,
        instanceAttributes: angular.IAttributes,
        controller: angular.INgModelController,
        transclude: angular.ITranscludeFunction):void { 

        var result: string = "";

        var shape = <ShapeUI> scope.shape;

        var template= this.createTemplate(shape.type,"shape.shapeData");
        
        var el = this.$compile(template)(scope);
        var recompileElem = instanceElement.find(".form-body");
        //recompileElem.html(el);

    }

    createTemplate(type: ShapeType,scopeDatadPath: string): string
    {
        var result = "";
        type.members.forEach((member) => {
            var inputHtml = "";
            var fieldPath= `${scopeDatadPath}.${member.fieldName}`;
            switch (member.directiveType.toLowerCase()) {
                case "number":
                case "int":
                case "float":
                case "double":
                    inputHtml = `<input class="input-number" type="number" name="${member.fieldName}" ng-model="${fieldPath}"/>`;
                    break;
                default:
                    throw `Shape member type ${member.directiveType.toLowerCase()} is unknown`;
            }

            result += `<div class="form-input">
                            <span class="span-label">
                                ${member.labelName}:
                            </span>
                            ${inputHtml}
                        </div>`;
        });
        return result;
    }

}



export function RegisterDirectives(app: angular.IModule) {
    app.directive('vectorPicker', () => new VectorPicker());
    app.directive('dxColorPicker', () => new DxColorPicker());
    app.directive('shapeform', ["$compile", ($compile: ng.ICompileService) => { return new ShapeForm($compile); }]);
}
