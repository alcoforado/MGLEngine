﻿var proxy = require('http-proxy-middleware');

var apiProxy = proxy('/api', {
    target: 'http://localhost:9000',
    changeOrigin: true   // for vhosted sites
});

module.exports = {
    files: ["./**/*.{html,htm,js,less}"],
    browser: "chrome",
    server: {
        middleware: {
            1: apiProxy
        }
    }
};