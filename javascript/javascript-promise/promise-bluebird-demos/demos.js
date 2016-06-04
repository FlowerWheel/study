'use strict';
const _ = require('lodash');
const Promise = require('bluebird');

function f() {
  return new Promise((resolve, reject)=>{
    setTimeout(()=>resolve('success'), 3000);
  });
}

let p = f().then((result)=>{
  console.log(result);
});

console.log(p);

