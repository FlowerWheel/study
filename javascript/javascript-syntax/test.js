
var objPrototype = Object.prototype;
console.log(objPrototype);                          // {}
console.log(objPrototype.__proto__);                // null
console.log(objPrototype.toString());               // [object Object]
console.log(objPrototype.valueOf());                // object
console.log(typeof objPrototype);                   // object
console.log(Object.prototype instanceof Object);    // false

console.log();

console.log(typeof Object);                         // function
console.log(Object);                                // [Function: Object]
console.log(Object instanceof Object);              // true
console.log(Object instanceof Function);            // true

console.log(typeof Function);                       // function
console.log(Function);                              // [Function: Function]
console.log(Function instanceof Object);            // true
console.log(Function instanceof Function);          // true

console.log();

console.log(Object.__proto__ === Function.prototype);
console.log(Function.__proto__ === Function.prototype);

console.log(Function.prototype.__proto__ === Object.prototype);

console.log(Object.__proto__.__proto__ === Object.prototype);
console.log(Function.__proto__.__proto__ === Object.prototype);

console.log(Object.prototype.__proto__);

console.log();

// console.log('__proto__:', 'xxx'.__proto__);
// console.log(String.prototype);

// console.log(Object instanceof Object);
// console.log([] instanceof Object);
// console.log({} instanceof Object);


void function iife() {
  var bar = function () {};
  var baz = function () {};
  var foo = function () {
    bar();
    baz();
  };
  var biz = function () {};

  foo();
  biz();
  console.log('...............')
}();