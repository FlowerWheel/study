'use strict';
const webpack = require('webpack');

let uglifyJsPlugin = new webpack.optimize.UglifyJsPlugin({
  compress: {warnings: false,},
  output: {comments: false,},
});

const baseDir = './app';

module.exports = {
  baseDir: baseDir,
  srcDir: `${baseDir}/src/`,
  distDir : `${baseDir}/dist/`,
  // entry: './src/index.js',
  target: 'web',
  devtool: 'source-map',
  devServer: {
    contentBase: './build'
  },
  entry: [
    // './app.vue/vue.app.js',
    `${baseDir}/src/app.js`
  ],
  output: {
    path: `${baseDir}/dist`,
    filename: '[name].bundle.js'
  },
  external: {},
  resolve: {
    alias: [],
    root: [],
    modulesDirectories: ['web_modules', 'node_modules'],
    fallback: [],
    extensions: ['', '.webpack.js', '.web.js', '.js'],
    packageMains: ['webpack', 'browser', 'web', 'browserify', ['jam', 'main'], 'main'],
    packageAlias: {},
    unsafeCache: []
  },
  resolveLoader: {},
  module: {
    preLoaders: [],
    postLoaders: [],
    loaders: [{
      test: /\.js$/,
      exclude: /node_modules/,
      loader: 'babel-loader'
    },
      {
        test: /\.css$/,
        exclude: /node_modules/,
        loader: 'style-loader!css-loader'
      },
      {
        test: /\.vue$/,
        exclude: /node_modules/,
        loader: 'vue'
      }
    ]
  },
  plugins: [
    // uglifyJsPlugin
  ]
};
