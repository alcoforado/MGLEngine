import { Http, Response } from '@angular/http'
import 'rxjs/Rx'
import { Observable } from 'rxjs/Observable'
import { Injectable } from '@angular/core';
import { TypeMember, UIType } from '../modules/mform/mformmodel'


export class ErrorResult {
    Errors: Array<string>;
}

export class UpdateShapeUI {
    Id: string;
    Name: string;
    TopologyType: string;
    TopologyJsonData: string;
    RenderJsonData: string;
    RenderType: string;
}


export class ShapeUI {
    constructor(
        public Name: string,
        public Id: string,
        public ShapeData: any,
        public TopologyType: UIType,
        public RenderData: any,
        public RenderType: UIType,
        public TopologyTypeName: string,
        public RenderTypeName: string
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

    private responseToArrayUIType(res: Response): Array<UIType> {
        let body = res.json();
        let types = <Array<UIType>>(body || {});
        return types.filter(x => {

            x.CssTypeName = x.TypeName.toLowerCase().replace(" ", "-");
            return x;
        })
    }

    constructor(private $http: Http) {

    }

    getRenderTypes(): Observable<Array<UIType>> {
        if (this.RenderTypes == null) {
            this.RenderTypes = this.$http.get("/api/shapemngr/rendertypes")
                .map<Response, Array<UIType>>(this.extractData)
                .map(c => {
                    return c.filter(x => {
                        x.CssTypeName = x.TypeName.toLowerCase().replace(" ", "-");
                        return x;
                    })
                })

        }
        return this.RenderTypes;
    }
    getTypes(): Observable<{ [typeName: string]: UIType }> {
        if (this.Types == null) {
            this.Types = this.$http.get("/api/shapemngr/shapetypes").map<Response, Array<UIType>>(this.extractData)
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
                        elem.TopologyType = types[elem.TopologyTypeName];
                        elem.RenderType = null;
                    });
                    return shapes;
                });
        });

    }
    createShape(UIType: string): Observable<ShapeUI> {
        return this.$http.post(`/api/shapemngr/shape/${UIType}`, "")
            .map(this.extractData)
            .mergeMap((sh: ShapeUI) => {
                return this.getTypes()
                    .map(x => {
                        sh.TopologyType = x[sh.TopologyTypeName];
                        sh.RenderData = null;
                        return sh;
                    })
            });
    }

    updateShape(sh: ShapeUI): Observable<{} | Response> {

        var obj: UpdateShapeUI = {
            Id: sh.Id,
            Name: sh.Name,
            RenderType: sh.RenderType.TypeName,
            RenderJsonData: JSON.stringify(sh.RenderData),
            TopologyType: sh.TopologyType.TypeName,
            TopologyJsonData: JSON.stringify(sh.ShapeData)
        }

        return this.$http.put(`/api/shapemngr/shape`, obj)
            .catch((r: any) => {
                return Observable.throw(this.extractData<ErrorResult>(r))
            });


    }
}






