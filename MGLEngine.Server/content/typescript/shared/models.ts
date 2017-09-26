 

export class DXVector3 {
    constructor(public X: number, public Y: number, public Z: number) { }
}

export class DXVector4 {
    constructor(public X: number, public Y: number, public Z: number, public W: number) { }
}




export class DirectionalLightData {
    constructor(
        public Ambient: DXVector4,
        public Diffuse: DXVector4,
        public Specular: DXVector3,
        public SpecPower: number,
        public Direction: DXVector3) { }
}


export class ShapeUI {
    constructor(
        public shapeType: string,
        public shapeData: any,
        public type: ShapeType
    ) {
    }
}

export class ShapeType {
    constructor(
        public typeName: string,
        public members: Array<ShapeMember>
    ) { }
}

export class ShapeMember {
    constructor(
        public fieldName: string,
        public labelName: string,
        public directiveType: string
    ) { }
}
