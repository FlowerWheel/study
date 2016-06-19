'use strict';
var gutil = require("gulp-util");
var md5 = require('gulp-md5-plus');
var spriter = require('gulp-css-spriter');
var webpack = require("webpack");
var webpackConfig = require("./webpack.config.js");

gulp.task("webpack", function(callback) {
  var webpackConfig = Object.create(webpackConfig);
  webpack(webpackConfig, function(err, stats) {
    if(err){
      throw new gutil.PluginError("webpack", err);
    }
    gutil.log("[webpack]", stats.toString({}));
    callback();
    });
});

gulp.task('sprite', function (done) {
  var timestamp = +new Date();
  gulp.src('dist/css/style.min.css')
    .pipe(spriter({
      spriteSheet: 'dist/images/spritesheet' + timestamp + '.png',
      pathToSpriteSheetFromCSS: '../images/spritesheet' + timestamp + '.png',
      spritesmithOptions: {
        padding: 10
      }
    }))
    .pipe(base64())
    .pipe(cssmin())
    .pipe(gulp.dest('dist/css'))
    .on('end', done);
});

gulp.task('md5:js', function (done) {
  gulp.src('dist/js/*.js')
    .pipe(md5(10, 'dist/app/*.html'))
    .pipe(gulp.dest('dist/js'))
    .on('end', done);
});

