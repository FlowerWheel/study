'use strict';
let gulp = require('gulp');
let gUtil = require('gulp-util');
let gConcat = require('gulp-concat');
let gUglify = require('gulp-uglify');
let gMd5 = require('gulp-md5-plus');
let gCssSpriter = require('gulp-css-spriter');
let gCoffee = require('gulp-coffee');
let gImageMin = require('gulp-imagemin');
let gSourcemaps = require('gulp-sourcemaps');
let gCached = require('gulp-cached');
let gChanged = require('gulp-changed');
let gNewer = require('gulp-newer');
let del = require('del');

let webpack = require('webpack');
let webpackConfig = require('./webpack.config.js');

let paths = {
  scripts: ['src/.js'],
  images: ['images/*']
}

let buildPath = ['build'];

let dist = 'dist';

gulp.task('clean', () => {
  return del(buildPath);
});

gulp.task('scripts', ['clean'], () => {
  // Minify and copy all JavaScript (except vendor scripts)
   // with sourcemaps all the way down
  return gulp.src(paths.scripts)
    .pipe(gChanged(dist))
    .pipe(gCached('scripts'))
    .pipe(gSourcemaps.init())
    .pipe(gCoffee())
    .pipe(gUglify())
    .pipe(gConcat('all.min.js'))
    .pipe(gSourcemaps.write())
    .pipe(gulp.dest('build/js'));
});

gulp.task('images', ['clean'], function() {
  return gulp.src(paths.images)
    .pipe(gNewer(paths.images))
    .pipe(gImageMin({optimizationLevel: 5}))
    .pipe(gulp.dest('build/img'));
});

// Rerun the task when a file changes
gulp.task('watch', function() {
  gulp.watch(paths.scripts, ['scripts']);
  gulp.watch(paths.images, ['images']);
});

gulp.task('webpack', function(callback) {
  let webpackConfig = Object.create(webpackConfig);
  webpack(webpackConfig, function(err, stats) {
    if(err){
      throw new gutil.PluginError('webpack', err);
    }
    gutil.log('[webpack]', stats.toString({}));
    callback();
    });
});

gulp.task('sprite', function (done) {
  let timestamp = +new Date();
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

