/**
 * Created by admin on 2014/11/22.
 */

var Stat = {
	PENDING  : 0,
	FULFILLED: 1,
	REJECTED : 2
};

function then(onFulfilled, onRejected) {
	var self = this;

	var promise = new Promise(function () {
	});

	self._subscribers.push({
		fulfillPromise: typeof onFulfilled === 'function' ? onFulfilled : null,
		rejectPromise : typeof onRejected === 'function' ? onRejected : null,
		thenPromise   : promise
	});

	invokeCallback(self);

	return promise;
}

function invokeCallback (promise) {
	if (promise._state === Stat.PENDING) {
		return undefined;
	}

	async(function () {
		while (promise._subscribers.length) {
			var obj = promise._subscribers.shift();
			try {
				var value = (promise._state === Stat.FULFILLED ? obj.fulfillPromise || function (x) {
					return x;
				} : obj.rejectPromise || function (x) {
					return x;
				})
				(promise._value);
			} catch (err) {
				return (obj.thenPromise);
				continue;
			}
			resolve(obj.thenPromise, value);//2.2.7.1
		}
	});
}

function async(fn) {
	setTimeout(fn, 0);
}

function resolve(promise, x) {

	if (promise === x) {//2.3.1

		reject(promise, new TypeError("it cant't fulfill promise equals value condition"));

	}

	else if (x && x.constructor === Promise) {//2.3.2

		if (x._state === State.PENDING) {//2.3.2.1

			x.then(function (val) {

				resolve(promise, val)

			}, function (reason) {

				reject(promise, reason);

			})
		}
		else if (x._state === State.FULFILLED) {//2.3.2.2

			fulfill(promise, x._value);

		}
		else if (x._state === State.REJECTED) {//2.3.2.3

			reject(promise, x._value);

		}
	}
	else if (x !== null && (typeof x == "object" || typeof x == "function")) {

		var isCalled = false;//2.3.3.3.3

		try {

			var then = x.then;//2.3.3.1

			if (typeof then == "function") {//2.3.3.3

				then.call(x, function (val) {

					isCalled || resolve(promise, val);//2.3.3.3.1

					isCalled = true;

				}, function (reason) {

					isCalled || reject(promise, reason);//2.3.3.3.2

					isCalled = true;
				})
			}

			else {

				fulfill(promise, x);//2.3.3.4

			}

		} catch (e) {

			isCalled || reject(promise, e);//2.3.3.2 ,2.3.3.3.4

		}
	}
	else {
		fulfill(promise, x);//2.3.4
	}
}