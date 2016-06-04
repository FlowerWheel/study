/**
 * Created by admin on 2015/1/10.
 */
'use strict';

module.exports = function Promise(fn) {
	if (!(this instanceof Promise)) {
		return new Promise(fn);
	}

	if (typeof fn !== 'function') {
		throw new TypeError('fn not a function');
	}

	var state = null;
	var delegating = false;
	var value = null;
	var deferreds = [];
	var self = this;

	this.then = function (onFulfilled, onRejected) {
		return new Promise(function (resolve, reject) {
			handle(new Handler(onFulfilled, onRejected, resolve, reject));
		});
	};

	function handle(deferred) {
		console.log('handle state', state, state === null ? 'defer' : 'handle');
		if (state === null) {
			deferreds.push(deferred);
			//console.log('handle deferreds:', deferreds);
			return;
		}

		process.nextTick(function() {
			var cb = state ? deferred.onFulfilled : deferred.onRejected;
			if (cb === null) {
				(state ? deferred.resolve : deferred.reject)(value);
				return;
			}
			var ret;
			try {
				ret = cb(value);
			}
			catch (e) {
				deferred.reject(e);
				return;
			}
			deferred.resolve(ret);
		})
	}

	function resolve(newValue) {
		console.log('resolve 1');
		if (delegating) {
			console.log('delegating', delegating);
			return;
		}
		_resolve(newValue);
		console.log('resolve 2');
	}

	function _resolve(newValue) {
		console.log('_resolve state', state, newValue);
		if (state !== null) {
			return;
		}
		try {
			console.log('newValue', newValue);
			if (newValue === self) {
				throw new TypeError('A promise cannot be resolved whit itself.');
			}
			if (newValue && (typeof newValue === 'object' || typeof newValue === 'function')) {
				var then = newValue.then;
				if (typeof then === 'function') {
					delegating = true;
					then.call(newValue, _resolve, _reject);
					return;
				}
			}
			state = true;
			value = newValue;
			finale();
		}
		catch (e) {
			_reject(e);
		}
	}

	function reject(newValue) {
		//console.log('reject 1')
		if (delegating) {
			//console.log('delegating', delegating)
			return;
		}
		_reject(newValue);
		//console.log('reject 2')
	}

	function _reject(newValue) {
		console.log('_reject');
		if (state !== null) {
			return;
		}
		state = false;
		value = newValue;
		finale();
	}

	function finale() {
		console.log('finale', deferreds);
		for (var i = 0, len = deferreds.length; i < len; i++) {
			//console.log('finale deferreds', i, deferreds[i])
			handle(deferreds[i]);
		}
		deferreds = null;
	}

	try {
		fn(resolve, reject);
	}
	catch (e) {
		reject(e);
	}
	console.log('================================================');
};

function Handler(onFulfilled, onRejected, resolve, reject) {
	this.onFulfilled = typeof onFulfilled === 'function' ? onFulfilled : null;
	this.onRejected = typeof onRejected === 'function' ? onRejected : null;
	this.resolve = resolve;
	this.reject = reject;
}
