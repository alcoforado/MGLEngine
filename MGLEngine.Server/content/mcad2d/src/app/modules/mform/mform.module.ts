import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { ReactiveFormsModule } from '@angular/forms';
import { HttpModule } from '@angular/http';
import { NumberInputComponent } from './number-input/number-input.component';
import { DynamicInputComponent } from './dynamic-input/dynamic-input.component'
import { TextInputComponent } from './text-input/text-input.component';
import { DropBoxComponent } from './drop-box/drop-box.component';
import { Vec2InputComponent } from './vec2-input/vec2-input.component';
import { ColorInputComponent } from './color-input/color-input.component';



@NgModule({
  declarations: [
    NumberInputComponent,
    TextInputComponent,
    DropBoxComponent,
    DynamicInputComponent,
    Vec2InputComponent,
    ColorInputComponent

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
