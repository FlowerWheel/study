'use strict';
const webpack = require('webpack');

let uglifyJsPlugin =  new webpack.optimize.UglifyJsPlugin({
  compress: {
    warnings: false,
  },
  output: {
    comments: false,
  },
})

module.exports = {
  //entry: './src/index.js',
  entry: './app.vue/index.js',
  output: {
    path: './bin',
    filename: 'app.bundle.js'
  },
  module: {
    loaders: [{
      test: /\.js$/,
      exclude: /node_modules/,
      loader: 'babel-loader'
    },
    {
      test: /\.css$/,
      exclude: /node_modules/,
      loader: "style-loader!css-loader"
    },
    {
      test: /\.vue$/,
      exclude: /node_modules/,
      loader:'vue'
    }
    ]
  },
  plugins: [
    // uglifyJsPlugin
  ]
};
