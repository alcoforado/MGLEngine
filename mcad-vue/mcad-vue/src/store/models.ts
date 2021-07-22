
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
    SObjects:{[id:string]:SceneObject};
    DisplayCreateShapeDialog:boolean;
}

export class UIState 
{
    Selected:boolean=false;
    Invalid:boolean=true;
}

export class SceneObject {
    TopologyType:string="";
    PainterType:string="";
    Topology:any=null;
    Painter:any=null;
    Id:string="";
    Name:string="";
    UI:UIState=new UIState();
}


