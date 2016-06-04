/**
 * Created by admin on 2015/9/9.
 */

var _ = require('lodash');
var BBPromise = require('bluebird');

function getPictures() {
	return BBPromise.resolve({Pictures: {}});
}

BBPromise.join(getPictures(), getPictures(), getPictures()).then(function (results) {
	console.log('=============', results);
});

BBPromise.join(getPictures(), getPictures(), getPictures(), function (p1, p2, p3) {
	console.log('-------------', p1, p2, p3);
});
