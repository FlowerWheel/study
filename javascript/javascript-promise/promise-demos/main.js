/**
 * Created by admin on 2014/11/22.
 */
var Promise = require('promise');

var promise = new Promise(function (resolve, reject) {
	setTimeout(function(){
		resolve(100);
	},2000)

});

promise
	.then(function fn1(val) {
		return val + 100
	})
	.then(function fn2(val) {//这里为了便于说明给匿名函数加了个名字
		console.log(val);
	})
	.then(function fn3(val) {//这里为了便于说明给匿名函数加了个名字
		console.log(val);
	});
