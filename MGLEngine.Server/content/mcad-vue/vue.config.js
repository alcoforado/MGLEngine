module.exports = {
    devServer: {
        proxy: {
            '^/api': {
                target: 'http://localhost:9000',
                ws: true,
                changeOrigin: true
            }
        }
    },
    lintOnSave: false,
    css: {
          loaderOptions: {
            sass: {
              data: `@import "@/scss/apptheme.scss";`
            }
          }
        },
        chainWebpack: config => {
            config.module
                .rule("vue")
                .use("vue-svg-inline-loader")
                    .loader("vue-svg-inline-loader")
                    .options({ /* ... */ });
        }
      
}