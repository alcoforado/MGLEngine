import { Component, OnInit } from '@angular/core';
import { ShapeUI, ShapesMngrService } from '../services/shapes-mngr-service';
import { MFormModel, MFormComponent, UIType } from '../modules/mform/mformmodel';
import { ListViewItem } from '../list-view/list-view.component';
import { Observable } from 'rxjs/Observable'


class ShapeRender {
    constructor(public shapeForm: ShapeUI) { }





}

class ShapeForm {
    shape: ShapeUI;
    form: MFormModel;

    constructor(sh: ShapeUI) {
        this.shape = sh;
        this.form = new MFormModel({});
    }

    getTopologyForm(): MFormComponent {
        return this.form.getFormComponentAsGroup("ShapeData");
    }

    getRenderForm(): MFormComponent {
        return this.form.getFormComponentAsGroup("RenderData");
    }


}

@Component({
    moduleId: module.id.toString(),
    selector: 'app-shapes-mngr',
    templateUrl: './shapes-mngr.component.html'
})
export class ShapesMngrComponent implements OnInit {

    ShapeTypes: Array<UIType> = [];
    RenderTypes: Array<UIType> = null;

    shapes: Array<ShapeUI> = [];

    shapeForms: Array<ShapeForm>;
    showAddShapeDialog: boolean = false;
    shapesListView: Array<ListViewItem> = [];
    rendersListView: Array<ListViewItem> = [];
    showRenderDialog: boolean = false;
    selectedShape: ShapeForm = null;
    ngOnInit() {
        this.shapesMngrService.getTypesAsArray().subscribe(x => {
            this.ShapeTypes = x;
            this.shapesListView = this.ShapeTypes.map(
                (sh: UIType) => {
                    let result = new ListViewItem();
                    result.imageUrl = `images/${sh.TypeName}.svg`,
                        result.itemLabel = sh.TypeName;
                    result.itemId = sh.TypeName;
                    return result;
                });
        });
        this.shapesMngrService.getShapes().subscribe(x => {
            this.shapes = x || [];
            this.shapeForms = this.shapes.map((sh) => {
                return new ShapeForm(sh)
            })
        });
        this.shapesMngrService.getRenderTypes().subscribe(x => {
            this.RenderTypes = x;
            let result = new ListViewItem();
            this.rendersListView = x.map((renderType, index) => {
                let result = new ListViewItem();
                result.imageUrl = `images/${renderType.TypeName}.svg`,
                    result.itemLabel = renderType.TypeName;
                result.index = index;
                return result;
            })
        })
    }

    constructor(private shapesMngrService: ShapesMngrService) { }

    disableAddShapeDialog(): void {
        this.showAddShapeDialog = false;
    }

    enableAddShapeDialog(): void {

        this.showAddShapeDialog = true;
    }

    renderSelected($event: ListViewItem) {
        if (this.selectedShape == null)
            throw "Shave not selected to appy render";

        var sh = this.selectedShape.shape;
        sh.RenderType = this.RenderTypes[$event.index];
        sh.RenderTypeName = sh.RenderType.TypeName;
        sh.RenderData = {};
        this.showRenderDialog = false;
    }

    addRender(sh: ShapeForm) {
        this.showRenderDialog = true;
        this.selectedShape = sh;
    }

    renderShape(shForm: ShapeForm) {
        console.log(shForm.form.Group.value);
    }

    createShape($event: ListViewItem) {
        this.shapesMngrService.createShape(<string>$event.itemId)
            .subscribe(x => {
                this.shapes.push(x)
                this.shapeForms.push(new ShapeForm(x))
            });
        this.disableAddShapeDialog();
    }

}
