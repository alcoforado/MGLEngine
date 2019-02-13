
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
}


