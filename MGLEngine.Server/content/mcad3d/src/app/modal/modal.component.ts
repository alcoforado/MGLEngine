import { Component, OnInit, Input, Output, EventEmitter, OnChanges, SimpleChanges } from '@angular/core';

@Component({
  moduleId: module.id,
  selector: 'app-modal',
  templateUrl: './modal.component.html',
  styleUrls: ['./modal.component.css']
})
export class ModalComponent implements OnInit, OnChanges {
  @Input() title: string;
  @Input() show: boolean;
  @Input() showButtons: string | boolean;
  @Output() close = new EventEmitter<boolean>();
  _showButtons: boolean;
  constructor() { }



  triggerCloseEvent(ok: boolean): void {
    this.close.emit(ok)
  }
  ngOnChanges(ch: SimpleChanges) {
    if (typeof (ch.showButtons) == "undefined")
      return;
    if (typeof (ch.showButtons.currentValue) == "string") {
      this._showButtons = (<string>ch.showButtons.currentValue).toLowerCase() === "true";
    }
    else
      this._showButtons = ch.showButtons.currentValue;
  }

  ngOnInit() {
  }

}
