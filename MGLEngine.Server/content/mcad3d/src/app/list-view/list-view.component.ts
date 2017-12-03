import { Component, OnInit,Input,Output,EventEmitter } from '@angular/core';


export class ListViewItem
{
  imageUrl:string;
  itemId:string;
  itemLabel:string;
}


@Component({
  moduleId: module.id,
  selector: 'app-list-view',
  templateUrl: './list-view.component.html'
})
export class ListViewComponent implements OnInit {
  @Input() items:Array<ListViewItem>; 
  @Input() defaultImage:string;
  @Output() itemSelected:EventEmitter<ListViewItem>=new EventEmitter();
  constructor() { }

  onImageNotFound(event:ErrorEvent)
  {
     (<HTMLImageElement> event.srcElement).src=this.defaultImage;
  }

  ngOnInit() {
  }

}
