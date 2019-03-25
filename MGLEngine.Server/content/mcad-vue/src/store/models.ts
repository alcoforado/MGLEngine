
export interface Shape {
    Id:string;
    Type:string;
}

export interface PainterType {
    Dim:number;
    Name:string;
}

export interface TopologyType {
    Dim:number;
    Name:string;
}



export interface StoreRootState {
    PaiterTypes:PainterType[];
    TopologyTypes:TopologyType[];
    SObjects:SceneObject[];
    DisplayCreateShapeDialog:boolean;
}


export class SceneObject {
    TopologyType:string="";
    PainterType:string="";
    Topology:any=null;
    Painter:any=null;
    Id:string="";
    Name:string="";
}


