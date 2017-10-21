import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { ReactiveFormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';
import { NumberInputComponent } from './number-input/number-input.component';
import { DynamicInputComponent } from './dynamic-input/dynamic-input.component'
import { TextInputComponent } from './text-input/text-input.component';
import { DropBoxComponent } from './drop-box/drop-box.component'


@NgModule({
  declarations: [
    NumberInputComponent,
    TextInputComponent,
    DropBoxComponent,
    DynamicInputComponent
  ],
  imports: [
    ReactiveFormsModule,
    BrowserModule
  ],
  exports: [
    NumberInputComponent,
    TextInputComponent,
    DropBoxComponent,
    DynamicInputComponent
  ],
  providers: []
})
export class MFormModule { }
