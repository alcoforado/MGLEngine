
export interface Shape {
    Id:string;
    Type:string;
}

export interface PainterTypes {
    Dim:number;
    Name:string;
}

export interface ShapeTypes {
    Dim:number;
    Name:string;
}



export interface StoreRootState {
    PaiterTypes:PainterTypes[];
    ShapeTypes:ShapeTypes[];
}


