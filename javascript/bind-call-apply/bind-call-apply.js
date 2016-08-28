/**
 * Created by admin on 2015/9/25.
 */

function Obj() {
  this.hi = 'hi!';
}

global.hi = 'HI!';

Obj.prototype.say = function () {
  console.log(this.hi);
};

function say() {
  console.log('hi');
}

function invoke(func) {
  func();
}

var obj = new Obj();
obj.say();
invoke(obj.say);
invoke(obj.say.bind(obj));
invoke(say);

function invoke2(func) {
  invoke(func);
}

var func = obj.say.bind(obj);
invoke2(func);
