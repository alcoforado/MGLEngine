import { Http, Response } from '@angular/http'
import 'rxjs/Rx'
import { Observable } from 'rxjs/Observable'
import { InMemMockService } from './mocks'
import { Injectable } from '@angular/core';
import { TypeMember, UIType } from '../modules/mform/mformmodel'




export class ShapeUI {
    constructor(
        public TypeName: string,
        public ShapeData: any,
        public Type: UIType
    ) {
    }
}


export type UITypeHash = { [typeName: string]: UIType };

@Injectable()
export class ShapesMngrService {
    private TypesHash: Observable<{ [typeName: string]: UIType }> = null;
    private Types: Observable<Array<UIType>> = null;
    private RenderTypes: Observable<Array<UIType>> = null;

    private extractData<T>(res: Response): T {
        let body = res.json();
        return <T>(body || {});
    }


    constructor(private $http: Http) {


    }

    getRenderTypes(): Observable<Array<UIType>> {
        if (this.RenderTypes == null) {
            this.RenderTypes = this.$http.get("/api/shapemngr/rendertypes")
                .map(this.extractData)

        }
        return this.RenderTypes;
    }
    getTypes(): Observable<{ [typeName: string]: UIType }> {
        if (this.Types == null) {
            this.Types = this.$http.get("/api/shapemngr/shapetypes").map(this.extractData)
            this.TypesHash = this.Types.map((c: Array<UIType>) => {
                let typeHash: { [typeName: string]: UIType } = {};
                c.forEach((elem) => {
                    typeHash[elem.TypeName] = elem;
                })
                return typeHash;
            });
        }
        return this.TypesHash;
    }

    getTypesAsArray(): Observable<Array<UIType>> {
        this.getTypes();
        return this.Types;
    }

    getType(name: string): UIType {
        if (typeof (this.getTypes()[name]) == "undefined")
            throw "Type " + name + " not found";
        else {
            return this.Types[name];
        }
    }

    getShapes(): Observable<Array<ShapeUI>> {

        return this.getTypes().mergeMap((types: { [typeName: string]: UIType }) => {
            return this.$http.get('api/shapemngr/shapes')
                .map(this.extractData)
                .map((shapes: Array<ShapeUI>) => {
                    shapes.forEach((elem) => {
                        elem.Type = types[elem.TypeName];
                    });
                    return shapes;
                });
        });

    }
    createShape(UIType: string): Observable<ShapeUI> {
        return this.$http.put(`/api/shapemngr/createshape?ShapeTypeId=${UIType}`, "")
            .map(this.extractData)
            .mergeMap((sh: ShapeUI) => {
                return this.getTypes()
                    .map(x => {
                        sh.Type = x[sh.TypeName];
                        return sh;
                    })
            });
    }
}


InMemMockService.AddFixture('api_shapesmngr_types', [
    new UIType("OrthoMesh", [new TypeMember("ElemsX", "Elems X", "int"), new TypeMember("ElemsY", "Elems Y", "int")], "Ortho Mesh"),
    new UIType("OrthoMesh3D", [new TypeMember("ElemsX", "Elems X", "int"), new TypeMember("ElemsY", "Elems Y", "int"), new TypeMember("ElemsZ", "Elems Z", "int")], "Ortho Mesh")
]);

InMemMockService.AddFixture('api_shapesmngr_shapes', [
    new ShapeUI("OrthoMesh", { ElemsX: 1, ElemsY: 2 }, null),
    new ShapeUI("OrthoMesh", { ElemsX: 3, ElemsY: 4 }, null),
    new ShapeUI("OrthoMesh", { ElemsX: 1, ElemsY: 5 }, null),
    new ShapeUI("OrthoMesh3D", { ElemsX: 1, ElemsY: 6, ElemsZ: 5 }, null)
]);



