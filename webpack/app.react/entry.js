'use strict'
let React = require('react');
let ReactDOM = require('react-dom');
let Hello = require('./hello');

// ReactDOM.render(<Hello name="Nate" />, document.body);

ReactDOM.render(
  <h1>Hello, world!</h1>,
  document.getElementById('example')
);

