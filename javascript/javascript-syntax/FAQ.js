
var x = 0, y = 1;
function Fun() {
  var x = 2, y = 3;
  this.x = 4;
  this.y = 5;
  console.log(x, y, this.x, this.y);
}
var obj = {x: 7, y: 8};
// 回答下面的输出结果

var obj2 = new Fun();
console.log(x, y, obj);
Fun();
console.log(x, y, obj);
Fun.bind(obj)();
console.log(x, y, obj);
