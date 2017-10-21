import { Component, OnInit,ViewChild,ElementRef } from '@angular/core';
import  'jsoneditor' 
@Component({
    moduleId: module.id,
    selector: 'app-json-editor',
    templateUrl: 'json-editor.component.html'
})

export class JsonEditorComponent implements OnInit {
    @ViewChild("jsonpanel") jsonPanel: ElementRef;
    editor: any = null;
    constructor() { }
    ngOnInit() { 
        var JSONEditor = window["JSONEditor"];
        this.editor = new JSONEditor(this.jsonPanel.nativeElement,{mode:"code"}); 
        var json = {
            "Array": [1, 2, 3],
            "Boolean": true,
            "Null": null,
            "Number": 123,
            "Object": {"a": "b", "c": "d"},
            "String": "Hello World"
        };   
        this.editor.set("");
    }

    setText(text:string): void {
        this.editor.set(text)
    }

    getText(): string {
        return this.editor.getText();
    }

    validateJson(): boolean {
        try {
            var obj = this.editor.get();
        }
        catch (e) {
            return false;
        }
        return true;
    }    
}
