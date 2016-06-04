/**
 * Created by admin on 2015/9/12.
 */

var tryCatchTarget, errorObj = {};
function tryCatcher() {
	console.log(arguments);
	try {
		var target = tryCatchTarget;
		tryCatchTarget = null;
		return target.apply(this, arguments);
	} catch (e) {
		console.log('e', e);
		errorObj.e = e;
		return errorObj;
	}
}
function tryCatch(fn) {
	tryCatchTarget = fn;
	return tryCatcher;
}

tryCatch(function (cb) {
	return cb('result');
})(function (arg) {
	console.log(arg);
	throw new Error('Error');
});

