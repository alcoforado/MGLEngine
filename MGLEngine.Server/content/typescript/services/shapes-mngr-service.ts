import { Http, Response } from '@angular/http'
import 'rxjs/Rx'
import {Observable} from 'rxjs/Observable'
import {InMemMockService} from './mocks'
import { Injectable } from '@angular/core';




export class ShapeType {
    constructor(
        public typeName: string,
        public members: Array<ShapeMember>
    ) { }
}

export class ShapeUI {
    constructor(
        public typeName: string,
        public shapeData: any,
        public type: ShapeType
    ) {
    }
}

export class ShapeMember {
    constructor(
        public fieldName: string,
        public labelName: string,
        public directiveType: string
    ) { }
}

@Injectable()
export class ShapesMngrService {
    private TypesHash: Observable<{ [typeName: string]: ShapeType }> = null;
    private Types: Observable<Array<ShapeType>> = null;

    private extractData<T>(res: Response): T {
        let body = res.json();
        return <T>(body.data || {});
    }


    constructor(private $http: Http) {


    }



    GetTypes(): Observable<{ [typeName: string]: ShapeType }> {
        if (this.Types == null) {
            this.Types = this.$http.get("api/shapesmngr/types").map(this.extractData)
            this.TypesHash = this.Types.map((c: Array<ShapeType>) => {
                    let typeHash: { [typeName: string]: ShapeType } = {};
                    c.forEach((elem) => {
                        typeHash[elem.typeName] = elem;
                    })
                    return typeHash;
                });
        }
        return this.TypesHash;
    }

    GetTypesAsArray(): Observable<Array<ShapeType>> {
        this.GetTypes();
        return this.Types;
    }

    GetType(name: string): ShapeType {
        if (typeof (this.GetTypes()[name]) == "undefined")
            throw "Type " + name + " not found";
        else {
            return this.Types[name];
        }
    }

    GetShapes(): Observable<Array<ShapeUI>> {

        return this.GetTypes().mergeMap((types:{ [typeName: string]: ShapeType }) => {
            return this.$http.get('api/shapesmngr/shapes')
                .map(this.extractData)
                    .map((shapes: Array<ShapeUI>) => {
                        shapes.forEach((elem) => {
                            elem.type = types[elem.typeName];
                        });
                        return shapes;
                    });
        });

    }
    /*
CreateShape(type: ShapeType): ShapeType {
    return this.$wpf.postSync("shapesmngr/createShape",
        {});
}
    */
}

InMemMockService.AddFixture('api_shapesmngr_types', [
    new ShapeType("OrthoMesh", [new ShapeMember("ElemsX", "Elems X", "int"), new ShapeMember("ElemsY", "Elems Y", "int")]),
    new ShapeType("OrthoMesh3D", [new ShapeMember("ElemsX", "Elems X", "int"), new ShapeMember("ElemsY", "Elems Y", "int"), new ShapeMember("ElemsZ", "Elems Z", "int")])
]);

InMemMockService.AddFixture('api_shapesmngr_shapes', [
    new ShapeUI("OrthoMesh", { ElemsX: 1, ElemsY: 2 }, null),
    new ShapeUI("OrthoMesh", { ElemsX: 3, ElemsY: 4 }, null),
    new ShapeUI("OrthoMesh", { ElemsX: 1, ElemsY: 5 }, null),
    new ShapeUI("OrthoMesh3D", { ElemsX: 1, ElemsY: 6,ElemsZ:5 }, null)
]);



