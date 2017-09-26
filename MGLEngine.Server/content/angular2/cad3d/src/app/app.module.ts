import { NgModule } from '@angular/core';
import { ReactiveFormsModule } from '@angular/forms'
import { platformBrowserDynamic } from '@angular/platform-browser-dynamic';
import { BrowserModule } from '@angular/platform-browser';
import { Component } from '@angular/core';
import { InMemoryWebApiModule } from 'angular-in-memory-web-api';
import { InMemMockService } from './services/mocks'
import { HttpModule } from '@angular/http';
import { ShapesMngrService } from './services/shapes-mngr-service';
import { ShapesMngrComponent } from './shapes-mngr/shapes-mngr.component';
import { AppComponent } from './app.component';
import { MFormModule } from './modules/mform/mform.module';
import { ListViewComponent } from './list-view/list-view.component'
import { ProcessingAnimationComponent } from './processing-animation/processing-animation.component'
import { RouterModule, Routes } from '@angular/router';
const appRoutes: Routes = [
    { path: 'shapes', component: ShapesMngrComponent },
    { path: 'src/index_system.html', component: ShapesMngrComponent },
    { path: 'src/index_system.html', redirectTo: 'src/index_system.html#shapes', pathMatch: 'full' }
]
@NgModule({
    imports: [
        HttpModule,
        BrowserModule,
        ReactiveFormsModule,
        MFormModule,
        RouterModule.forRoot(appRoutes)
    ],
    declarations: [
        AppComponent,
        ShapesMngrComponent,
        ListViewComponent,
        ProcessingAnimationComponent
    ],
    providers: [
        ShapesMngrService
    ],
    bootstrap: [AppComponent]
})
export class AppModule { }
