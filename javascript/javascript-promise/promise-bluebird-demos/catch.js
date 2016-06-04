/**
 * Created by admin on 2015/11/10.
 */

var Promise = require('bluebird');

Promise.resolve().then(function () {
  throw new Error('Error');
}).tap(function (str) {
  console.log('1', str);
}).catch(function (err) {
  console.error(err);
  return 'BBB';
}).tap(function (str) {
  console.log('2', str);
});
