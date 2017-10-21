import { Component, OnInit,Input } from '@angular/core';
import { NgModule } from '@angular/core';
import * as $ from 'jquery'

interface IDropBoxItem {
  label: string

}

@Component({
  moduleId: module.id.toString(),
  selector: 'app-drop-box',
  templateUrl: './drop-box.component.html',
})
export class DropBoxComponent implements OnInit {
  isExpanded: boolean = false;
  selectedIndex:number = 0;
  @Input() items: Array<any>=[];
  @Input() fieldName: string=null;
  constructor() { }

  ngOnInit() {
    if (this.isEmpty())
    {
      if (this.fieldName ==null)
      {
        this.fieldName="label"
      }
      this.items=[{}];
      this.items[0][this.fieldName]=" ";
    }  
  }

 isEmpty():boolean
 {
   return this.items == null || this.items.length == 0;
 }

 item_clicked(evt:MouseEvent)
 {
    let i = evt.srcElement.getAttribute("data-option-array-index");
    if (i==null || i == "")
      throw "No array index was found for option";
    let ii = parseInt(i);
    this.selectedIndex=ii;    
 }

  clicked()
  {
    if (this.items == null || this.items.length == 0)
      return;
    this.isExpanded = !this.isExpanded;
  }


}


