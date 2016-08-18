'use strict';
const gulp = require('gulp');
const gUtil = require('gulp-util');
const gConcat = require('gulp-concat');
const gUglify = require('gulp-uglify');
const gMd5 = require('gulp-md5-plus');
const gCssSpriter = require('gulp-css-spriter');
const gCoffee = require('gulp-coffee');
const gImageMin = require('gulp-imagemin');
const gSourcemaps = require('gulp-sourcemaps');
const gCached = require('gulp-cached');
const gChanged = require('gulp-changed');
const newer = require('gulp-newer');
const del = require('del');
const vinylPaths = require('vinyl-paths');

const gulpClean = require('gulp-clean');
const gMinifyCSS = require('gulp-minify-css');

const webpack = require('webpack');
const webpackConfig = require('./webpack.config.js');

const webpackComplier = webpack(webpackConfig);

const env = process.env.NODE_ENV || 'develpment';

const paths = {
  scripts: ['./app/src/*.js'],
  images: ['images/*']
};

const buildPath = ['build'];
const src = './src';
const dst = './dist';

const isProduction = env === 'production';

gulp.task('clean', () => {
  del(['tmp/*.js', '!tmp/unicorn.js']).then((paths) => {
    gUtil.log('[clean] Deleted files and folders:\n', paths.join('\n'));
  });
});

gulp.task('clean:tmp', function () {
  return gulp.src('tmp/*').pipe(vinylPaths(del)).pipe(gulp.dest('dist'));
});

gulp.task('webpack', ['clean'], (callback) => {
  webpackComplier.run((err, stats) => {
    if (err) {
      throw new gUtil.PluginError('[ERROR] webpack', err);
    }
    gUtil.log('[webpack]', stats.toString());
    callback();
  });
});

function f(src, dst, filters) {
    let stream = gulp.src(src, {'base': dst});
    if (isProduction) {
        if (!Array.isArray(filters)) {
            filters = [filters];
        }
        for (let filter of filters) {
            stream.pipe(filter());
        }
    }
    stream.pipe(gulp.dest(dst));
}

gulp.task('minifyJS', () => {
    f([src + '*.js'], dst, gUglify);
});

// Minify and copy all JavaScript (except vendor scripts)
// with sourcemaps all the way down
gulp.task('scripts', () => {
  return gulp.src(paths.scripts)
    .pipe(gChanged(dst))
    .pipe(gCached('scripts'))
    .pipe(gSourcemaps.init())
        // .pipe(gCoffee())
        .pipe(gUglify())
        .pipe(gConcat('all.min.js'))
    .pipe(gSourcemaps.write())
    .pipe(gulp.dest('app/dist'));
});

gulp.task('minifyCSS', ['clean'], () => {
    let src = [target + '/css/*.css'];
    f(src, target, gMinifyCSS);
});

gulp.task('revision', ['minifyJS', 'minifyCSS'], () => {
    let src = [target + '/css/*.css'];
    f(src, target, [rev, () => {return gulp.dist(target)}, () => {return rev.manifest({merge: true})}]);
});

gulp.task('inlineSource', ['revision'], () => {
    let src = [target + '/html/*.html'];
    // f(src, target, [rev, () => {return gulp.dist(target)}, () => {return rev.manifest({merge: true})}]);
    return gulp.src(src, {'base': dst}).pipe(inlineSource({compress: true, rootpath: './src/'})).pipe(gulp.dist(dst));
});

gulp.task('replace', ['inlineSource'], () => {
 var _src = './' + directory + '/html/*.html', _dest = './views';
    if (environment) {
        return gulp.src(_src)
            .pipe(replace('js/', publicPath + directory + '/js/'))
            .pipe(replace('css/', publicPath + directory + '/css/'))
            .pipe(gulp.dest(_dest));
    } else {
        var manifest = gulp.src(directory + '/rev/rev-manifest.json');
        return gulp.src(_src)
            .pipe(revReplace({
                'prefix': publicPath + directory + '/',
                'manifest': manifest,
                'modifyReved': function (filename) {
                    return filename;
                }
            }))
            .pipe(gulp.dest(_dest));
    }
});

gulp.task('minifyHTML', ['replace'], () => {
if (environment) {
        return gulp.src('views/*.html')
            .pipe(gulp.dest('views'))
            .pipe(livereload());
    } else {
        return gulp.src('views/*.html')
            .pipe(htmlmin({
                collapseWhitespace: true,
                minifyCSS: true
            }))
            .pipe(gulp.dest('views'))
    }

});

gulp.task('watch', ['inlineSource'], () => {
    if (environment) {
        stopClean = true;
        //livereload.listen();
        gulp.watch('src/**/*', ['clean', 'webpack', 'minifyJS', 'minifyCSS', 'rev', 'replace', 'inlineSource', 'minifyHTML']);
    }

});

gulp.task('default', ['clean', 'webpack', 'minifyJS', 'minifyCSS', 'rev', 'replace', 'inlineSource', 'minifyHTML', 'watch']);

gulp.task('images', ['clean'], function() {
  return gulp.src(paths.images)
    .pipe(newer(paths.images))
    .pipe(imageMin({optimizationLevel: 5}))
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

