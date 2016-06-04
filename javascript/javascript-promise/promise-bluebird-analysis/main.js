/**
 * Created by admin on 2015/9/12.
 */

var BBPromise = require('bluebird').noConflict();

var promise = new BBPromise(function resolver(resolve) {
	//throw new Error('error');
	return resolve(true);
});
console.log('_isFulfilled', promise._isFulfilled());
console.log('_value', promise._value());
promise.then(function (r) {
	console.log('r', r);
});


