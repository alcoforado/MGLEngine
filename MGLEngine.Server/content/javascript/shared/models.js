"use strict";
var DXVector3 = (function () {
    function DXVector3(X, Y, Z) {
        this.X = X;
        this.Y = Y;
        this.Z = Z;
    }
    return DXVector3;
}());
exports.DXVector3 = DXVector3;
var DXVector4 = (function () {
    function DXVector4(X, Y, Z, W) {
        this.X = X;
        this.Y = Y;
        this.Z = Z;
        this.W = W;
    }
    return DXVector4;
}());
exports.DXVector4 = DXVector4;
var DirectionalLightData = (function () {
    function DirectionalLightData(Ambient, Diffuse, Specular, SpecPower, Direction) {
        this.Ambient = Ambient;
        this.Diffuse = Diffuse;
        this.Specular = Specular;
        this.SpecPower = SpecPower;
        this.Direction = Direction;
    }
    return DirectionalLightData;
}());
exports.DirectionalLightData = DirectionalLightData;
var ShapeUI = (function () {
    function ShapeUI(shapeType, shapeData, type) {
        this.shapeType = shapeType;
        this.shapeData = shapeData;
        this.type = type;
    }
    return ShapeUI;
}());
exports.ShapeUI = ShapeUI;
var ShapeType = (function () {
    function ShapeType(typeName, members) {
        this.typeName = typeName;
        this.members = members;
    }
    return ShapeType;
}());
exports.ShapeType = ShapeType;
var ShapeMember = (function () {
    function ShapeMember(fieldName, labelName, directiveType) {
        this.fieldName = fieldName;
        this.labelName = labelName;
        this.directiveType = directiveType;
    }
    return ShapeMember;
}());
exports.ShapeMember = ShapeMember;
//# sourceMappingURL=models.js.map