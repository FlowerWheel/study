'use strict';
const fs = require('fs-extra');
const path = require('path');
const Promise = require('bluebird');

Promise.promisifyAll(fs);

function cbFunction(data, cb) {
  setTimeout(()=>{
    console.log(data);
    return cb();
  }, 1000);
}

const asyncFunction = Promise.promisify(cbFunction);

asyncFunction('This sentence will never be output!');

asyncFunction('This sentence will never be output after call then!').then();

let asyncFunctions = [];
for (var i = 0; i < 100; ++i) {
    asyncFunctions.push(asyncFunction(`this is the no ${i}`));
}

console.log('Promise.all will start');
setTimeout(()=>{
  Promise.all(asyncFunctions).then(function() {
    console.log("all the files were created");
  }).then(()=>{
    console.log('Promise.all will start');
  });
}, 3000);

var files = [];
for (var i = 0; i < 100; ++i) {
    files.push(fs.writeFileAsync(path.join(__dirname, 'files', "file-" + i + ".txt"), "utf-8"));
}
Promise.all(files).then(function() {
    console.log("all the files were created");
});

