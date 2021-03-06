﻿System.config({
    baseURL: "../",
    paths: {
        // paths serve as alias
        'npm:': '../node_modules/',
        'ts:': 'typescript/',
        'js:': 'javascript/',
        'jsts': 'javascript/typescript/'
    },
    defaultJSExtensions: true,
    // map tells the System loader where to look for things
    map: {
        // angular bundles
        '@angular/core': 'npm:@angular/core/bundles/core.umd.js',
        '@angular/common': 'npm:@angular/common/bundles/common.umd.js',
        '@angular/compiler': 'npm:@angular/compiler/bundles/compiler.umd.js',
        '@angular/platform-browser': 'npm:@angular/platform-browser/bundles/platform-browser.umd.js',
        '@angular/platform-browser-dynamic': 'npm:@angular/platform-browser-dynamic/bundles/platform-browser-dynamic.umd.js',
        '@angular/http': 'npm:@angular/http/bundles/http.umd.js',
        '@angular/router': 'npm:@angular/router/bundles/router.umd.js',
        '@angular/forms': 'npm:@angular/forms/bundles/forms.umd.js',
        '@angular/upgrade': 'npm:@angular/upgrade/bundles/upgrade.umd.js',
        '@angular/platform-browser/animations': 'npm:@angular/platform-browser/bundles/platform-browser-animations.umd.js',
        '@angular/animations/browser': 'npm:@angular/animations/bundles/animations-browser.umd.js',
        '@angular/animations': 'npm:@angular/animations/bundles/animations.umd.js',
        'main': '/src/main_system.js',
        '@angular': 'node_modules/@angular',
        // other libraries
        'rxjs': 'npm:rxjs',
        'rxjs/Observable': 'npm:rxjs/Observable',
        'rxjs/Rx': 'npm:rxjs/Rx',
        'angular-in-memory-web-api': 'npm:angular-in-memory-web-api/bundles/in-memory-web-api.umd.js',
        'services/mocks': 'typescript/services/mocks',
        'focus-trap': 'node_modules/focus-trap/index.js',
        'tabbable': 'npm:/tabbable/index.js'
    },
    // packages tells the System loader how to load when no filename and/or no extension
    packages: {
        'api': { defaultExtension: 'js' },
        'rxjs': { defaultExtension: 'js' },
        //    '@angular/animations': { main: 'bundles/animations.umd.js', defaultExtension: 'js' },
        '': { defaultExtension: 'js' }


        // barrels
        // 'app/core':   { main: 'index'},
        // 'app/models': { main: 'index'},
    }
});


