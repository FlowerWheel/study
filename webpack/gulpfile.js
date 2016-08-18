'use strict';
const gulp = require('gulp');
const gUtil = require('gulp-util');
const gConcat = require('gulp-concat');
const gUglify = require('gulp-uglify');
const gMd5 = require('gulp-md5-plus');
const gCssSpriter = require('gulp-css-spriter');
const gCoffee = require('gulp-coffee');
const gImageMin = require('gulp-imagemin');
const sourcemaps = require('gulp-sourcemaps');
const gCached = require('gulp-cached');
const gChanged = require('gulp-changed');
const newer = require('gulp-newer');
const del = require('del');
const vinylPaths = require('vinyl-paths');

const gulpClean = require('gulp-clean');
const cleanCSS = require('gulp-clean-css');

const rev = require('gulp-rev');
const base64 = require('gulp-css-base64');
const imageMin = require('gulp-imagemin');

const webpack = require('webpack');
const webpackConfig = require('./webpack.config.js');

const webpackComplier = webpack(webpackConfig);

// const env = process.env.NODE_ENV || 'development';
const env = process.env.NODE_ENV || 'production';

const paths = {
  js: ['./app/src/*.js'],
  images: ['images/*']
};

const buildPath = ['build'];
const srcDir = webpackConfig.srcDir;
const distDir = webpackConfig.distDir;

const jsSrcDirs = [`${srcDir}js/*.js`];
const jsDistDir = `${distDir}js/`;
const cssSrcDirs = [`${srcDir}css/*.css`];
const cssDistDir = `${distDir}css/`;
const htmlSrcDirs = [`${srcDir}html/*.html`, `${srcDir}html/*.ejs`];
const htmlDistDir = `${srcDir}html/`;

const isProduction = env === 'production';

gulp.task('clean', () => {
  del(['tmp/*.js', '!tmp/unicorn.js']).then((paths) => {
    gUtil.log('[clean] Deleted files and folders:\n', paths.join('\n'));
  });
});

gulp.task('clean:tmp', function () {
  return gulp.src('tmp/*').pipe(vinylPaths(del)).pipe(gulp.dest('dist'));
});

gulp.task('webpack', (done) => {
  webpackComplier.run((err, stats) => {
    if (err) {
      throw new gUtil.PluginError('[ERROR] webpack', err);
    }
    gUtil.log('[webpack]', stats.toString());
    done();
  });
});

gulp.task('minify:js', () => {
  return gulp.src(jsSrcDirs)
    .pipe(gChanged(distDir))
    .pipe(gCached('scripts'))
    .pipe(sourcemaps.init())
    .pipe(gUglify())
    .pipe(gConcat('all.min.js'))
    .pipe(sourcemaps.write())
    .pipe(gulp.dest(jsDistDir));
});

gulp.task('minify:css', () => {
  return gulp.src(cssSrcDirs)
    .pipe(sourcemaps.init())
    .pipe(cleanCSS({debug: true}, function cleanCSSLog(details) {
      let stats = details.stats;
      console.log(`${details.name} | ${details.path} | ${stats.originalSize} -> ${stats.minifiedSize} | ${stats.timeSpent}`);
    }))
    .pipe(sourcemaps.write())
    .pipe(gulp.dest(cssDistDir));
});

gulp.task('minify', ['minify:js', 'minify:css']);

gulp.task('revision', ['minify'], () => {
  return gulp.src([].concat(cssSrcDirs, jsSrcDirs), {base: 'assets'})
    .pipe(gulp.dest(distDir + 'build/assets'))
    .pipe(rev())
    .pipe(gulp.dest(distDir + 'build/assets'))
    .pipe(rev.manifest({
      base: 'build/assets',
      merge: true // merge with the existing manifest (if one exists)
    }))
    .pipe(gulp.dest('build/assets'));
});

gulp.task('inlineSource', ['revision'], () => {
  return gulp.src(htmlSrcDirs, {'base': htmlDistDir})
    .pipe(inlineSource({compress: true, rootpath: './src/'}))
    .pipe(gulp.dest(htmlDistDir));
});

gulp.task('replace', ['inlineSource'], () => {
  var manifest = gulp.src(htmlSrcDirs + '/rev/rev-manifest.json');
  return gulp.src(htmlSrcDirs)
    .pipe(revReplace({
      'prefix': publicPath + htmlSrcDirs + '/',
      'manifest': manifest,
      'modifyReved': (filename) -> filename
    }))
    .pipe(gulp.dest(htmlDistDir));
});

gulp.task('minifyHTML', ['replace'], () => {
  return gulp.src('views/*.html')
    .pipe(htmlmin({
      collapseWhitespace: true,
      minifyCSS: true
    }))
    .pipe(gulp.dest('views'))
});

gulp.task('images', ['clean'], function () {
  return gulp.src(paths.images)
    .pipe(newer(paths.images))
    .pipe(imageMin({optimizationLevel: 5}))
    .pipe(gulp.dest('build/img'));
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

gulp.task('watch', ['inlineSource'], () => {
  gulp.watch('src/**/*', [
    'clean', 'webpack',
    'minifyJS', 'minifyCSS',
    'rev', 'replace', 'inlineSource', 'minifyHTML'
  ]);
});

gulp.task('default', [
  'clean', 'webpack',
  'minifyJS', 'minifyCSS',
  'rev', 'replace', 'inlineSource', 'minifyHTML',
  'watch'
]);
