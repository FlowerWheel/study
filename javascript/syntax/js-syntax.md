# javascript-syntax



## 数据类型


### 基本类型

`Undefined、Null、Boolean、Number、String`


基本类型是不可变的，我们无法给它们添加属性。

```js
var str = '~~~~~';
str.prop = '!!!!!';
str.prop; // undefined

var num = 10;
num.prop = 11;
num.prop; // undefined

var bool = true;
bool.prop = '';
bool.prop // undefined

'---'.charAt === String.prototype.charAt
(12345).toString(); // 使用数字调用方法时需要用用括号括起来
```


#### `Boolean`、`Number`、`String`

  这三种基本类型分别存在`Boolean()`、`Number()`、`String()`内建函数。
  平时使用的时候大都使用的是字面量形式，字面量并不是对象。
  当需要的时候，它们也会被转换成对象，也就是会被转换成 **基本类型的包装类型**。


#### `Undefined`、`Null`

  并不存在`Undefined()`和`Null()`内建函数，只存在`Undefined`和`Null`类型的内建对象`undefined`和`null`。
  ECMAScript认为`undefined`是从`null`派生出来的，所以把它们定义为相等的，相同的地方是都可以视为布尔值的false。
  这两个类型无**包装类型**。

  `undefined`与`null`的区别：

* `null`表示 **没有对象**，即该处不应该有值。
  1. 作为函数的参数，表示该函数的参数不是对象。
  1. 作为对象原型链的终点。
* `undefined`表示 **缺少值**，即应该有一个值但是**未定义**。
  1. 变量被声明了，但没有赋值时，该变量`undefined`。
  1. 调用函数时，参数没有提供，该参数`undefined`。
  1. 对象没有赋值的属性，该属性`undefined`。
  1. 函数没有返回值时，返回`undefined`。


### 引用类型

`Object、Function、Array、Error、Regexp、Map、Set`...

JavaScript中一切都可以被当做对象！但是只有引用类型才是真正的对象，基本类型除了`null`和`undefined`之外，都可以像对象一样使用，因为他们有包装类型。


#### Object{} - 对象

```js
var obj = {};
var boolObj = new Object({});
console.log(obj instanceof Object);         // true
console.log(boolObj instanceof Object);     // true
console.log(obj === boolObj);               // false
console.log(typeof obj);                    // object
console.log(typeof boolObj);                // object
```


#### Function - 函数对象

Function 是一个构造函数，用于创建一个函数对象：

```js
var foo = new Function ([arg1[, arg2[, ...argN]],] functionBody)

var foo = new Function () {}
```

function 是一个关键字可以声明一个函数对象，有两种创建的方式：

```js
// 函数声明
function foo() {}

// 函数表达式
var foo = function () {}

// 每一个函数对象都继承 Function 构造函数的原型对象。
Function.prototype.foo = 1

var bar = function () {}
bar.foo // 1
```


#### Array[] -  复合类型 （引用，指针）

数组是对象，能够添加属性。

```js
var arr = [1, 2, 3];
arr.i = 4;
console.log(arr); // [1, 2, 3, i: 4]
for(var a in arr) {
  console.log(a, arr[a]);
}
// 0 1
// 1 2
// 2 3
// i 4
```

```js
var foo = [1, 2, 3, 4, 5, 6];
foo.length = 3;
foo; // [1, 2, 3]

foo.length = 6;
foo.push(4);
foo; // [1, 2, 3, undefined, undefined, undefined, 4]
```

pop,push,reverse,shift,sort,splice,unshift      会改变原数组
join,concat,indexOf,lastIndexOf,slice,toString  不会改变原数组
map,filter,some,every,reduce,forEach            这些迭代方法不会改变原数组


#### 类数组对象


一个JS数组是特殊的, 因为：

1. 它的length属性有些特殊行为:
    1. 当新的元素添加到列表中,其值自动更新;
    1. 设置这一属性可以扩展或截断数组.
1. JS数组也是Array的实例，可以调用不同的Array方法。

1、2都是JS数组的独特特性，但它们不是一个数组的最基本的特性。

把任何具有一个`length`属性及相应的 *非负整数属性* 的 *对象* 作为一种数组, 称之为"类似数组"。

这种类似数组的对象出现频率不高, 而且也不能在它们之上调用数组方法或者通过`length`属性期待特殊的行为1)2), 但仍然可以用遍历一个真正数组的代码来遍历它们。

事实上很多数组算法对于类似数组的对象和真正的数组对象都是适用的, 只要不尝试对数组添加元素或者改变length属性, 就可以把类似数组的对象当作真正的数组来对待.

如下创建一个类似数组，然后遍历该类似数组:

```js
var a = {};
var i = 0;
// 不小心就引进了一个小bug
while(i++ < 10) { a[i] = i * i; }
while(i < 10) { a[i] = i * i; i++; }

a.length = i;

var total = 0;
for(var j = 0, len = a.length; j < len; j++) {
  total += a[j];
}
```

特别地，函数中的Arguments对象就是一个类似数组的对象; 而getElementsByTagName()返回的DOM结点列表也是类似数组的对象。


### 类型识别


#### 识别方法

* `typeof`

  * 返回值：首字母小写的字符串形式
  * 可以识别基本类型(将Null识别为object)
  * 不能识别具体的对象类型(Function除外)

* `instanceof`

  * 返回值：true或false
  * 可以识别内置对象类型、自定义类型及其父类型
  * 不能识别标准类型,会返回false。 (true instanceof Boolean) -> false
  * 不能识别undefined、null，会报错

* `Object.prototype.toString`

  * 返回值：[object 数据类型] 的字符串形式
  * 可以识别标准类型及内置对象类型
  * 不能识别自定义类型

```js
// 使用toString实现type函数
function type(obj){
  return Object.prototype.toString.call(obj).slice(8,-1).toLowerCase();
}
```

* `.constructor` eq. Object.prototype.constructor

  * 返回值：function 数据类型(){[native code]}或者function 自定义类型(){}
  * 可以识别标准类型、内置对象类型及自定义类型
  * 不能识别undefined、null，会报错

```js
// 使用constructor实现type函数
function type(obj){
  return obj.constructor.toString().replace(/^function (\w+)\(\).+$/,'$1');
}
```


#### Example


* Number

```js
var num = 0;
var numObj = new Number(0);
console.log(num instanceof Object);         // false
console.log(num instanceof Number);         // false
console.log(numObj instanceof Object);      // true
console.log(numObj instanceof Number);      // true
console.log(typeof num);                    // number
console.log(typeof numObj);                 // object
console.log(numObj === new Number(0));      // false
console.log(numObj === numObj);             // true
console.log(num === numObj);                // false
```


* String

```js
var str = '';
var strObj = new String('');
console.log(str instanceof Object);         // false
console.log(str instanceof String);         // false
console.log(strObj instanceof Object);      // true
console.log(strObj instanceof String);      // true
console.log(typeof str);                    // string
console.log(typeof strObj);                 // object
console.log(str === strObj);                // false
```


* Boolean

```js
var bool = true;
var boolObj = new Boolean(true);
console.log(bool instanceof Object);        // false
console.log(bool instanceof Boolean);       // false
console.log(boolObj instanceof Object);     // true
console.log(boolObj instanceof Boolean);    // true
console.log(typeof bool);                   // boolean
console.log(typeof boolObj);                // object
console.log(bool === boolObj);              // false
```


* Undefined Null

```js
console.log(undefined instanceof Object);   // false
console.log(typeof undefined);              // undefined
console.log(null instanceof Object);        // false
console.log(typeof null);                   // object
console.log(undefined === null);            // false
console.log(undefined == null);             // true
var undefined = 'foo';
console.log(undefined, typeof undefined);   // foo 'string'
console.log(void(0) === undefined);         // true
```

* Function

```js
var objPrototype = Object.prototype;
console.log(objPrototype);                          // {}
console.log(objPrototype.__proto__);                // null
console.log(objPrototype.toString());               // [object Object]
console.log(objPrototype.valueOf());                // object
console.log(typeof objPrototype);                   // object
console.log(Object.prototype instanceof Object);    // false !

console.log(typeof Object);                         // function
console.log(Object);                                // [Function: Object]
console.log(Object instanceof Object);              // true
console.log(Object instanceof Function);            // true !

console.log(typeof Function);                       // function
console.log(Function);                              // [Function: Function]
console.log(Function instanceof Object);            // true
console.log(Function instanceof Function);          // true ！

console.log(Object.__proto__ === Function.prototype);
console.log(Function.__proto__ === Function.prototype);

console.log(Function.prototype.__proto__ === Object.prototype);

console.log(Object.__proto__.__proto__ === Object.prototype);
console.log(Function.__proto__.__proto__ === Object.prototype);

console.log(Object.prototype.__proto__);
```


### 类型转换


#### 显式转换

通过手动进行类型转换，JavaScript提供了以下转型函数：

* 转换为数值类型：`Number(mix)`、`parseInt(string,radix)`、`parseFloat(string)`
* 转换为字符串类型：`toString(radix)`、`String(mix)`
* 转换为布尔类型：`Boolean(mix)`


1. `Number(mix)`函数，可以将任意类型的参数mix转换为数值类型。其规则为：

Type        |Example
------------|---------------------------------------
Boolean     | Number(true)->1 Number(false)->0
Number      | Number(num)->num
Null        | Number(null)->0
Undefined   | Number(undefined)->NaN
String      | Number('012345')->12345 Number('012345.6789')->12345.6789 Number('')->0 Number('A-Z')->NaN
Object      | 调用对象的valueOf()方法，依据前面的规则转换返回的值。如果转换的结果是NaN，则调用对象的toString()方法，再依据前面的规则转换返回的值。

下表列出了对象的`valueOf()`的返回值：

Type        |valueOf()
------------|---------------------------------------
`Array`     | 数组的元素被转换为字符串，这些字符串由逗号分隔，连接在一起，其操作与 Array.toString 和 Array.join 方法相同。
`Boolean`   | Boolean 值是
`Date`      | 存储的时间是从 1970 年 1 月 1 日午夜开始计的毫秒数 UTC
`Function`  | 函数本身
`Object`    | 对象本身
`String`    | 字符串值
`Number`    | 数字值


Example：

```js
var arr1 = new Array();
Number(arr1.valueOf());
Number(arr1.toString());
Number(arr2);
var arr2 = new Array([1, 2, 3]);
Number(arr2.valueOf());
Number(arr2.toString());
Number(arr2);
var bool = new Boolean(true);
Number(bool.valueOf());
Number(bool.toString());
Number(bool);
var date = new Date();
Number(date.valueOf());
Number(date.toString());
Number(date);
var func = new Function();
Number(func);
```


1. `parseInt(string, radix)`函数，将字符串转换为整数类型的数值。

它也有一定的规则：

* 忽略字符串前面的空格，直至找到第一个非空字符。
* 如果第一个字符不是数字符号或者负号，返回NaN。
* 如果第一个字符是数字，则继续解析直至字符串解析完毕或者遇到一个非数字符号为止。
* 如果上步解析的结果以0开头，则将其当作八进制来解析；如果以0x开头，则将其当作十六进制来解析。
* 如果指定radix参数，则以radix为基数进行解析。


1. `parseFloat(string)`函数，将字符串转换为浮点数类型的数值。

它的规则与parseInt基本相同，但也有点区别：字符串中第一个小数点符号是有效的，另外parseFloat会忽略所有前导0，如果字符串包含一个可解析为整数的数，则返回整数值而不是浮点数值。


1. `toString(radix)`方法。

除`undefined`和`null`之外的所有类型的值都具有`toString()`方法，转换成字符串表示。

```js
console.log([1, 2, 3].toString())       // 1, 2, 3
console.log(true.toString())            // true
console.log(new Date().toString(10))    // Wed Aug 17 2016 13:52:21 GMT+0800 (中国标准时间)
console.log({}.toString())              // [object Object]
```


1. `String(mix)`函数，将任何类型的值转换为字符串，其规则为：

* `null` -> "null"
* `undefined` -> "undefined"
* 调用`toString()`方法，返回结果，如果没有`toString()`，则报异常，无法转换。


1. `Boolean(mix)`函数，将任何类型的值转换为布尔值。

* `false`：false、''、0、NaN、null、undefined
* `true` : 除了以上转换问false的


#### 隐式转换

在某些情况下，即使我们不提供显示转换，JavaScript也会进行自动类型转换，主要情况有：


1. 用于检测是否为非数值的函数：`isNaN(mix)`

`isNaN()`函数，经测试发现，该函数会尝试将参数值用`Number()`进行转换，如果结果为“非数值”则返回true，否则返回false。


1. 递增递减操作符（包括前置和后置）、一元正负符号操作符

这些操作符适用于任何数据类型的值，针对不同类型的值，该操作符遵循以下规则（经过对比发现，其规则与Number()规则基本相同）：

* 如果是包含有效数字字符的字符串，先将其转换为数字值（转换规则同Number()），在执行加减1的操作，字符串变量变为数值变量。
* 如果是不包含有效数字字符的字符串，将变量的值设置为NaN，字符串变量变成数值变量。
* 如果是布尔值false，先将其转换为0再执行加减1的操作，布尔值变量编程数值变量。
* 如果是布尔值true，先将其转换为1再执行加减1的操作，布尔值变量变成数值变量。
* 如果是浮点数值，执行加减1的操作。
* 如果是对象，先调用对象的valueOf()方法，然后对该返回值应用前面的规则。如果结果是NaN，则调用toString()方法后再应用前面的规则。对象变量变成数值变量。

“2″, ”02dd”, ”", false, 22.5, +”", -false, +new Date() 分别对以下类型的值执行后置递增操作，结果是什么？


1. 加减乘除运算符、取模运算符

这些操作符针对的是运算，所以他们具有共同性：如果操作值之一不是数值，则被隐式调用`Number()`函数进行转换。具体每一种运算的详细规则请参考ECMAScript中的定义。

如果两个操作值都是数值，其规则为：

* 如果一个操作数为NaN，则结果为NaN
* 如果是`Infinity+Infinity -> Infinity`
* 如果是`-Infinity+(-Infinity) -> -Infinity`
* 如果是`Infinity+(-Infinity) -> NaN`
* 如果是`+0+(+0) -> +0`
* 如果是`(-0)+(-0) -> -0`
* 如果是`(+0)+(-0) -> +0`

加号运算操作符在JavaScript也用于字符串连接符，所以加号操作符处理字符串是有所不同：

* 如果两个操作值都是字符串，则将它们拼接起来
* 如果只有一个操作值为字符串，则将另外操作值转换为字符串，然后拼接起来
* 如果一个操作数是对象、数值或者布尔值，则调用toString()方法取得字符串值，然后再应用前面的字符串规则。对于undefined和null，分别调用String()显式转换为字符串。
* 可以看出，加法运算中，如果有一个操作值为字符串类型，则将另一个操作值转换为字符串，最后连接起来。


1. 逻辑操作符（!、&&、||）

* 逻辑非 `!` 操作符首先通过`Boolean()`函数将它的操作值转换为布尔值，然后求反。
* 逻辑与 `&&` 操作符，如果一个操作值不是布尔值时，遵循以下规则进行转换：
  * 如果第一个操作数经`Boolean()`转换后为`true`，则返回第二个操作值，否则返回第一个值（不是Boolean()转换后的值）
  * 如果有一个操作值为`null`，返回`null`
  * 如果有一个操作值为`NaN`，返回`NaN`
  * 如果有一个操作值为`undefined`，返回`undefined`
* 逻辑或（||）操作符，如果一个操作值不是布尔值，遵循以下规则：
  * 如果第一个操作值经Boolean()转换后为false，则返回第二个操作值，否则返回第一个操作值（不是Boolean()转换后的值）
  * 对于undefined、null和NaN的处理规则与逻辑与（&&）相同


1. 关系操作符（<, >, <=, >=）

与上述操作符一样，关系操作符的操作值也可以是任意类型的，所以使用非数值类型参与比较时也需要系统进行隐式类型转换：

* 如果两个操作值都是数值，则进行数值比较
* 如果两个操作值都是字符串，则比较字符串对应的字符编码值
* 如果只有一个操作值是数值，则将另一个操作值转换为数值，进行数值比较
* 如果一个操作数是对象，则调用valueOf()方法（如果对象没有valueOf()方法则调用toString()方法），得到的结果按照前面的规则执行比较
* 如果一个操作值是布尔值，则将其转换为数值，再进行比较
* 注：NaN是非常特殊的值，它不和任何类型的值相等，包括它自己，同时它与任何类型的值比较大小时都返回false。


1. 相等操作符（==）

相等操作符会对操作值进行隐式转换后进行比较：

* 如果一个操作值为布尔值，则在比较之前先将其转换为数值
* 如果一个操作值为字符串，另一个操作值为数值，则通过Number()函数将字符串转换为数值
* 如果一个操作值是对象，另一个不是，则调用对象的valueOf()方法，得到的结果按照前面的规则进行比较
* null与undefined是相等的
* 如果一个操作值为NaN，则相等比较返回false
* 如果两个操作值都是对象，则比较它们是不是指向同一个对象



## void


* void UnaryExpression 按如下流程解释:

  * 令`expr`为解释执行`UnaryExpression`的结果。
  * 调用 `GetValue(expr)`.
  * 返回 `undefined`.

* 注意：GetValue一定会被调用，即使它的值不会被用到，但是这个表达式可能会有副作用(side-effects)。

* 为什么要用void？`undefined`不是保留字，可以重新赋值。采用void方式获取undefined便成了通用准则。


[谈谈JavaScript中的void操作符](https://segmentfault.com/a/1190000000474941)



## Object


ECMAScript做为一个高度抽象的面向对象语言，是通过对象来交互的。
一个对象就是一个属性集合，并拥有一个独立的`原型对象`，这个`原型对象`可以是一个`对象`或者`null`。
一个对象的`原型对象`是以对象内部的`[[Prototype]]`属性来引用的。


在示意图里边我们将会使用`__<internal-property>__`下划线标记来替代两个括号，对于prototype对象来说是：`__proto__`。


让我们看一个关于对象的基本例子。


对于以下代码：

```js
var foo = {
  x: 10,
  y: 20
};
```

我们拥有一个这样的结构，两个显式的属性和一个隐藏的`__proto__`属性，这个属性是对`Object.prototype`的引用。

![basic-object](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/basic-object.png)


这些`prototype`有什么用？让我们以`原型链`的概念来回答这个问题。



## 原型链（prototype-chain）


* `原型对象`也是简单的对象并且可以拥有它们自己的原型，如果一个原型对象的`原型`是一个非`null`的引用，以此类推，原型对象连成的链，就形成了`原型链`。
* `原型链`是一个用来实现`继承`和`共享`属性的有限长度的`对象链`。
* `原型链`是为了实现代码重用而设计的，在基于类的系统中，这个代码重用风格叫作`继承`。


ECMAScript中没有类的概念，但是代码重用的风格并没有太多不同，ECMAScript通过原型链来实现，即**原型继承(prototype based inheritance)**，这种继承方式叫作**委托继承(delegation based inheritance)**。


ES5标准化了一个实现原型继承的新的可选方法，使用`Object.create`函数：

```js
var a = {k: 'v'};
var b = Object.create(a, {y: {value: 20}});
var c = Object.create(a, {y: {value: 30}});
```


ES6标准化了`__proto__`属性，并且可以在对象初始化的时候使用它，如下面的用法。
`b`和`c`可以访问到`a`对象中定义的`calculate()`方法，是通过原型链`lookup`实现的。

```js
var a = {
  x: 10,
  calculate: function (z) {
    return this.x + this.y + z
  }
};
var b = {y: 20, __proto__: a};
// 等价于 var b = Object.create(a, {y: {value: 20}});
var c = {y: 30, __proto__: a};
// 等价于 var c = Object.create(a, {y: {value: 30}});
b.calculate(30); // 60
c.calculate(40); // 80
```


### 原型链lookup规则：

如果一个`属性`/`方法`在对象自身中无法找到，JS引擎会尝试遍历整个原型链，寻找这个`属性`/`方法`，第一个被查找到的同名`属性`/`方法`会被使用。如果在遍历了整个原型链之后还是没有查找到这个属性的话，返回undefined值。

下一张图展示了对象`a`，`b`，`c`之间的继承关系：

![prototype-chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/prototype-chain.png)


所以`__proto__`是给JS引擎用的，但是暴露给了我们，并且可以对其修改。


与此类似的还有`作用域链`及其`lookup规则`，原型链和作用域链的用途都是用来名字查找，给解释器用的。
区别是：原型链是属性上的名字查找，这条链可以运行时被修改，作用域链是作用域上（空间上）的名字查找，这条链由代码决定。


### `__proto__`

* 如果没有明确为一个对象指定原型，那么它将会使用 `__proto__` 的默认值 `Object.prototype`。
* `Object.prototype`对象自身也有一个`__proto__`属性，值为`null`，这是原型链的终点。 即：`Object.prototype.__proto__ === null`
* The `__proto__` property of `Object.prototype` is an `accessor property` (a getter function and a setter function) that exposes the internal `[[Prototype]]` (either an object or null) of the object through which it is accessed.


项目中建议不要直接使用`__proto__`读写原型，而是使用`Object.getPrototypeOf()、Object.create()`读写原型。


```js
var Shape = function () { };
var proto = {
    say: function () {
        console.log('hello world!');
    }
};
Shape.prototype = proto;
// Object.prototype.getPrototype = function () { return Object.getPrototypeOf(this) };
```


```js
var circle = new Shape();
console.log('circle:', circle.__proto__ === Shape.prototype);
console.log('circle:', Object.getPrototypeOf(circle) === Shape.prototype);
console.log('circle:', typeof circle);
console.log('circle:', circle instanceof Shape);
console.log('circle:', circle instanceof Object);
```

```js
var rectangle = Object.create(proto);
console.log('ractangle:', rectangle.__proto__ === Shape.prototype);
console.log('ractangle:', Object.getPrototypeOf(rectangle) === Shape.prototype);
console.log('ractangle:', typeof rectangle);
console.log('ractangle:', rectangle instanceof Shape);
console.log('ractangle:', rectangle instanceof Object);
```

```js
var objPrototype = Object.prototype;
console.log(objPrototype);
console.log(typeof objPrototype);
console.log(objPrototype.__proto__);
console.log(Object.prototype instanceof Object);
console.log('__proto__:', 'xxx'.__proto__);
console.log(String.prototype);
console.log(Object instanceof Object);
console.log([] instanceof Object);
console.log({} instanceof Object);
```


`typeof`和`instanceof`的目的都是检测变量的类型，区别在于:

`typeof`    : 可以用来区分原始值和对象。
`instanceof`: 可以用来区分对象，instanceof 对于所有的原始值都返回 false。

typeof 在操作 null 时会返回 "object"，这是 JavaScript 语言本身的 bug。
不幸的是，这个 bug 永远不可能被修复了，因为太多已有的代码已经依赖了这样的表现。
这并不意味着，null 实际上就是一个对象。
typeof 还可以让检查一个变量是否已声明，而不会抛出异常。
没有任何一个函数可以实现此功能，因为你不能把一个未声明的变量传递给函数的参数。

通常情况下对象拥有相同或者相似的状态结构（也就是相同的属性集合），赋以不同的状态值，在这个情况下我们可能需要使用`构造函数`，其以指定的模式来创造对象。



## 属性类型


### 数据属性


属性|说明
---|---
`[[Configurable]]` | 表示能否通过delete删除属性从而重新定义属性，能否改变属性的特性，或者能否改变把属性改为访问器属性。true|
`[[Enumerable]]`   | 表示能否通过for-in循环返回属性。true|
`[[Writable]]`     | 表示能否修改属性值。ture|
`[[Value]]`        | 包含实际值。undefined|

严格模式下不合法的操作会抛出异常，非严格模式会忽略相关操作。

```js
var person = {};
Object.defineProperty(person, 'name', {
  configurable: false,
  enumerable: true,
  writable: false,
  value: 'liuyanjie'
});
Object.defineProperty(person, 'sax', {
  configurable: false,
  enumerable: false,
  writable: false,
  value: 'M'
});
console.log(person);            // { name: 'liuyanjie' }
console.log(person.sax);        // M
```


### 访问器属性: `getter` `setter`


属性|说明
---|---
`[[Configurable]]`    | 表示能否通过delete删除属性从而重新定义属性，能否改变属性的特性，或者能否改变把属性改为访问器属性。true
`[[Enumerable]]`      | 表示能否通过for-in循环返回属性。true
`[[Getter]]`          | 取值函数。undefined
`[[Setter]]`          | 赋值函数。undefined


* `getter`和`setter`不一定要成对出现;
* 只有`getter`函数证明该属性只读，尝试写入在非严格模式下会被忽略，严格模式会抛出错误;
* 只有`setter`函数证明该属性只写，尝试读取在非严格模式下返回undefined，严格模式则抛出错误;
* 对象的``数据属性``、``访问器属性``都包含`[[configurable]]`和`[[enumerable]]`，但不能同时有`[[writeable]]`/`[[value]]`和`[[get]]`/`[[set]]`，数据属性也可以函数。


```js
var book1 = { _year: 2014, edition: 1 };
Object.defineProperty(book1, 'year', {
  configurable: false,
  enumerable: true,
  get: function () {
    return this._year;
  },
  set: function (year) {
    if (year > 2014) {
      this._year = year;
      this.edition += year - 2014;
    }
  }
});
console.log(book1);      // { _year: 2014, edition: 1, year: [Getter/Setter] }
console.log(book1.year);  // 2014
book.year = 2016;
console.log(book1);      // { _year: 2016, edition: 3, year: [Getter/Setter] }
```


```js
// 给 对象 设置 多个 `数据属性` 和 `访问器属性`
var book2 = { _year: 2014, edition: 1 };
Object.defineProperties(book2, {
  _year: {
    value: 2014
  },
  edition: {
    value: 1
  },
  year: {
    configurable: false,
    enumerable: false,
    get: function () { },
    set: function () { }
  },
  getContents: {
    value: function () {
      return 'contents';
    }
  }
});
```


```js
// 获取 属性 信息
var desc1 = Object.getOwnPropertyDescriptor(book2, 'year');
console.log(desc1);
// {
//   get: [Function],
//   set: [Function],
//   enumerable: false,
//   configurable: false
// }
var desc2 = Object.getOwnPropertyDescriptor(book2, 'getContents');
console.log(desc2);
// {
//   value: [Function],
//   writable: false,
//   enumerable: false,
//   configurable: false
// }
```


### 应用：

* [观察者模式]例子[JavaScript实现MVVM监测一个普通对象的变化](http://hcysun.me/2016/04/28/JavaScript%E5%AE%9E%E7%8E%B0MVVM%E4%B9%8B%E6%88%91%E5%B0%B1%E6%98%AF%E6%83%B3%E7%9B%91%E6%B5%8B%E4%B8%80%E4%B8%AA%E6%99%AE%E9%80%9A%E5%AF%B9%E8%B1%A1%E7%9A%84%E5%8F%98%E5%8C%96/)



## ECMAScript5对象保护功能


在JavaScript里，默认情况下，你可修改任何你可以访问到的对象，你可以自由的删除对象的属性或覆盖对象的方法。
这在多人协作开发的项目中，会造成很大问题，因为你不知道你的修改会对别人造成什么样的影响。
如果你是一个模块或代码库的作者，你可能想锁定一些核心库的某些部分，保证任何人不能有意或无意的修改它们。
严格模式下抛出异常，普通模式下安静的失败；


* 禁止添加属性：禁止扩展。即：禁止为对象添加属性和方法，但已存在的属性和方法是可以被修改和删除的。

```js
var person1 = { name: 'liuht' };
Object.preventExtensions(person1);
console.log('isFrozen:', Object.isFrozen(person1));             // -> true
console.log('isSealed:', Object.isSealed(person1));             // -> true
console.log('isExtensible:', Object.isExtensible(person1));     // -> false
person1.sex = 1;
console.log(person1);
console.log(person1.sex);
```


* 禁止删除属性：密封。即：禁止删除对象已存在的属性和方法。

```js
var person2 = { name: 'liuht' };
Object.seal(person2);
console.log('isFrozen:', Object.isFrozen(person2));             // -> true
console.log('isSealed:', Object.isSealed(person2));             // -> true
console.log('isExtensible:', Object.isExtensible(person2));     // -> false
delete person2.name;
person2.age = 10;
console.log(person2);
```


* 禁止添加或删除属性：冻结。即：禁止修改对象已存在的属性和方法，所有字段都是只读的。

```js
var persion3 = { name: 'liuht' };
Object.freeze(persion3);
console.log('isFrozen:', Object.isFrozen(persion3));            // -> true
console.log('isSealed:', Object.isSealed(persion3));            // -> true
console.log('isExtensible:', Object.isExtensible(persion3));    // -> false
delete persion3.name;
persion3.age = 10;
persion3.name = 'new name';
console.log(persion3);
```


**访问器属性** 和 **对象保护功能** 都是针对 **对象属性** ，而不是 **变量**



## 构造函数


* 以指定的模式来创造对象
* 自动地为新创建的对象设置一个原型对象，这个原型对象存储在`ConstructorFunction.prototype`属性中。


我们可以使用构造函数来重写上一个拥有对象`b`和对象`c`的例子。因此，对象`a`的角色由Foo.prototype来扮演：

```js
function Foo(y) { this.y = y; }
Foo.prototype.x = 10;
Foo.prototype.calculate = function (z) {
  return this.x + this.y + z;
};
var b = new Foo(20);
var c = new Foo(30);
b.calculate(30);
c.calculate(40);
console.log(b.__proto__ === Foo.prototype);
console.log(c.__proto__ === Foo.prototype);
console.log(b.constructor === Foo);
console.log(c.constructor === Foo);
console.log(Foo.prototype.constructor === Foo);
console.log(b.calculate === b.__proto__.calculate);
console.log(b.__proto__.calculate === Foo.prototype.calculate);
```


这个代码可以表示为如下关系：

可以看到，构造函数`Foo`也有自己的`__proto__`，即`Function.prototype`，`Function.prototype`通过其`__proto__`属性关联到`Object.prototype`。

![constructor-proto-chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/constructor-proto-chain.png)


思考一下类的概念，那么构造函数和原型对象合在一起可以当作一个「类」了。

例如：Python的`First-Class、Dynamic-Classes`显然是以同样的`属性/方法`处理方案来实现的。从这个角度来说，Python中的类可以看作ECMAScript使用的委托继承的一个语法糖。

在ES6中「类」的概念被标准化了，并且实际上以一种构建在构造函数上面的语法糖来实现，就像上面描述的一样。


用类的方式实现如下：

```js
// ES6
class Foo {
  constructor(name) {
    this._name = name;
  }
  getName() {
    return this._name;
  }
}
class Bar extends Foo {
  getName() {
    return super.getName() + ' Doe';
  }
}
var bar = new Bar('John');
console.log(bar.getName()); // John Doe
```


**new** 操作符 都做了什么？

1. 创建一个新对象
1. 将构造函数作用域赋给新对象，即this指向了新对象
1. 执行构造函数中的代码
1. 返回新对象的引用

只要用`new`操作符来调用函数就是构造函数，否则，就是普通函数。


```js
var o = new NewObject(11, 22)
var o;
NewObject.apply(o, 11, 22);
NewObject.call(o, [11, 22]);
var obj1 = new NewObject(11, 22); // 构造函数方式
obj1.func();                      // this == obj1
var obj2 = NewObject(33, 44);     // 普通函数方式
obj2.func();                      // error
global.func();                    // this == global
console.log(obj2);                // NewObject()作为函数并无返回值，所以undefined
var obj3 = new Object();
NewObject.call(obj3, 55, 66);
obj3.func();
console.log(obj1.func === obj3.func);
console.log(obj1.func() === obj3.func());
```

```js
function NewDate() {
  return new Date();
}
var date = new NewDate();
console.log(date instanceof NewDate); // ?
console.log(date instanceof Date);    // ?
```



## 对象构造


### 工厂模式

* 按指定模式创建对象的，但是对象类型无法标识，且每个方法在每个对象上都要重新创建一次。

```js
function createObject(arg1, arg2) {
  var o = new Object();
  o.property1 = arg1;
  o.property2 = arg2;
  o.func = function () {
    console.log(this.property1);
    console.log(this.property2);
  };
  return o;
}

var o1 = createObject(1, 2);
var o2 = createObject(3, 4);
console.log(o1.property1);
```


### 构造函数模式

* 构造函数名字用来标志一个`特定类型`，同样每个方法在每个对象上都要重新创建一次。

```js
function NewObject(arg1, arg2) {
  this.property1 = arg1;
  this.property2 = arg2;
  this.func = function () {
    console.log(this.property1);
  }
}

var no1 = new NewObject(1, 2);
var no2 = new NewObject(3, 4);
// 构造函数属性 constructor  标志对象类型
console.log(no1.constructor == NewObject);
console.log(no1.constructor == Object);
console.log(no2.constructor == NewObject);
console.log(no2.constructor == Object);
// 检测对象　更可靠
console.log(no1 instanceof Object);
console.log(no1 instanceof NewObject);
console.log(no2 instanceof Object);
console.log(no2 instanceof NewObject);
```


### 原型模式

* 每个函数都有一个`prototype`属性，引用另一个对象，这个对象可以实现属性的共享。
* `prototype`是构造函数的一个属性，`prototype`指向的`原型对象`拥有一个`constructor`属性指向构造函数，普通函数有此属性无意义。
* 通过构造函数创建的`对象实例`可以通过`__proto__`访问`原型对象`，但是不能重写，重名的属性将屏蔽原型中的同名属性。
* 在原型中修改属性，会立刻在`对象实例`中反映出来。但是如果重写整个原型对象，那么实例对象将找不到原型中定义的属性。
* `prototype` 和 `constructor` 构成了双向链表。

```js
function PrototypeObject() { }
PrototypeObject.prototype.name = 'PrototypeObject'; // name 是多实例共享的
PrototypeObject.prototype.sayName = function () {
  console.log(this.name);
};

var po1 = new PrototypeObject();
po1.sayName();
var po2 = new PrototypeObject();
po2.sayName();
console.log(po1.sayName === po2.sayName);       // true
console.log(po1.sayName() === po2.sayName());   // true
console.log(PrototypeObject.prototype.constructor === PrototypeObject); // true
// 每个实例　拥有一个[[Prototype]]属性指向原型对象，但是无法访问此属性。
console.log(PrototypeObject.prototype.isPrototypeOf(po1));  // true  // 判断po1.[[Prototype]] ===
console.log(PrototypeObject.prototype.isPrototypeOf(po1));  // true  // 判断po2.[[Prototype]] ===
console.log(Object.getPrototypeOf(po1));                    // 返回原型对象
console.log(PrototypeObject.prototype);                     // 同样是原型对象
console.log(po1.hasOwnProperty('sayName'));                 // 判断是否是对象属性  检测属性存在于对象中还是原型对象中
function hasPrototypeProperty(object, name) {               // 判断是否是原型属性
  return !object.hasOwnProperty(name) && (name in object);
}
// Object.keys();                    // 返回所有可枚举的实例属性
// Object.getOwnPropertyNames();     // 返回所有实例属性
// 原型同样可以这样定义：原型对象 = 字面量，prototype的constructor不再等于PrototypeObject，但是instanceof()仍能继续工作。
PrototypeObject.prototype = {
    constructor:Person // 默认的constructor被覆盖掉了 [[Enumerable]]会变成true
}
Object.defineProperty(PrototypeObject.prototype, 'constructor', {
  enumerable: false,
  value: Persion
})
```


### 组合构造函数和原型模式 - [默认模式]

* 实例属性在构造函数中定义 共享属性在原型中定义

```js
function ConstructPrototypeObject(name, desc) {
  this.name = name;
  this.desc = desc;
}
ConstructPrototypeObject.prototype.display = function () {
  console.log(this.name);
  console.log(this.desc);
};
```


### 动态原型模式

* 只在第一次调用构造函数时 实例化原型

```js
function ConstructPrototypeObject(name, desc) {
  this.name = name;
  this.desc = desc;
  if (!ConstructPrototypeObject.prototypeInstantiated) {
      //只在第一次调用构造函数时 实例化原型
    ConstructPrototypeObject.prototype.prototypeInstantiated = true;
    ConstructPrototypeObject.prototype.display = function () {
      console.log(this.name);
      console.log(this.desc);
    };
    ConstructPrototypeObject.prototype.sayName = function () {
      console.log(this.name);
    };
    // ... ...
    ConstructPrototypeObject.prototypeInstantiated = true;
  }
}
```


### 继承模式 寄生模式

* 这种方式，可以用来扩展原生对象，在不修改原生对象的前提下，扩展方法。

```js
function SpecialArray() {
  var values = new Array();
  values.push.apply(values, arguments);
  values.toPipedString = function () {
    return this.join('|');
  };
  return values;
}
var colors = new SpecialArray('red', 'blue', 'green');
console.log(colors.toPipedString());
console.log(colors instanceof SpecialArray);  // false
console.log(colors instanceof Array);         // true
```


### 稳妥构造函数模式

* 数据成员位于作用域链中，不在对象的属性中，防止数据被其他程序改动时使用，适合用于一些安全环境，这些环境禁止使用this和new。

```js
function Person(name, age, job) {
  var o = new Object();
  var name = name;
  o.sayName = function () {
    console.log(name);
  };
  return o;
}
var friend = Person('liuyanjie', 22, 'Software Engineer');
friend.sayName();
console.log(friend.name); //undefined
```


```js
function Person(name, age, job) {
  var name = name;
  this.sayName = function () {
    console.log(name);
  };
}

var friend = new Person('liuyanjie', 22, 'Software Engineer');
friend.sayName();
console.log(friend.name); //undefined
```


```js
var Person = (function () {
  // 这里可以定义闭包变量
  return function Person(name, age, job) {
    var name = name;
    this.sayName = function () {
      console.log(name);
    };
  }
})();

var friend = new Person('liuyanjie', 22, 'Software Engineer');
friend.sayName();
console.log(friend.name); //undefined
```



## 继承


### 原型链

* 原型属性会被所有实例共享
* 无法向超类传递参数

```js
function SuperType() {
  this.supProperty = true;
}
SuperType.prototype.getSuperValue = function () {
  return this.supProperty;
};
function SubType() {
  this.subProperty = false;
}
SubType.prototype = new SuperType();
SubType.prototype.getSubValue = function () {
  return this.subProperty;
};
var instance = new SubType();
console.log(instance.getSuperValue());
// 借用构造函数    在子类型的内部调用父类型的构造函数
function SupType() {
  this.colors = ['red', 'blue', 'green'];
}
function SubType() {
  // this 指 SubType 普通函数调用 把函数当作一个模板 同时可以传递参数
  SupType.call(this);
}
var instance = new SubType();
instance.colors.push('black');
console.log(instance);
```


### 组合继承

* 原型链继承原型
* 借用构造函数继承实例属性

```js
function SuperType(name) {
  this.name = name;
  this.colors = ['red', 'blue', 'green'];
}
SuperType.prototype.sayName = function () {
  console.log(this.name);
};
function SubType(name, age) {
  SuperType.call(this, name);           // 普通函数
  this.age = age;
}
SubType.prototype = new SuperType();    // 构造函数
SubType.prototype.constructor = SubType;
SubType.prototype.sayAge = function () {
  console.log(this.age);
};
var instance = new SubType('liuyanjie', 22);
instance.colors.push('black');
instance.sayName();
instance.sayAge();
```


### 原型式继承

* 此方式必须有一个对象作为基础，作为原型。

```js
function object(o) {
  function F() { } // 临时性构造函数
  F.prototype = o;
  return new F();
}
Object.create();    //此方法即为原型式继承
```


### 寄生式继承

```js
function createAnother(original) {          // 工厂
  var clone = Object.create(original);      // 封装了原型式继承
  clone.sayHi = function () {
    console.log('Hi');
  };
  return clone;
}
```


### 寄生组合式继承

* 借用构造函数继承属性
* 原型链的混成形式继承方法

```js
function inheritPrototype(subType, supType) {
  var prototype = Object.create(supType.prototype);
  prototype.constructor = subType;
  subType.prototype = prototype;
}
```


Node.js原生实现的继承函数：

```js
exports.inherits = function(ctor, superCtor) {
  if (ctor === undefined || ctor === null)
    throw new TypeError('The constructor to `inherits` must not be ' +
                        'null or undefined.');
  if (superCtor === undefined || superCtor === null)
    throw new TypeError('The super constructor to `inherits` must not ' +
                        'be null or undefined.');
  if (superCtor.prototype === undefined)
    throw new TypeError('The super constructor to `inherits` must ' +
                        'have a prototype.');
  ctor.super_ = superCtor;
  ctor.prototype = Object.create(superCtor.prototype, {
    constructor: {value: ctor, enumerable: false, writable: true, configurable: true}
  });
};
```



## `bind`、`call`、`apply`

他们使用来做什么的？

TODO: 要改，举例说明使用方法。
从设计者的角度去考虑各个点，call、apply、bind 存在的原因。
C++中类的方法是隐式传递了this指针，python的方法都是显示的指定self，而js也同样需要this。
但是this在js中是作为一个执行环境上下文的概念存在，并且对于任意一个函数（一级公民），它有语法逻辑上的上下文，但是它的上下文又可以是人为绑定的，
这三个函数就可以用来完成绑定工作。任何一个函数也是在一个上下文对象上进行工作。上下文是一个this对象。
这是一种松散的绑定关系，随时可以根据需要来绑定。因此就可以自由的将其他模块上的属性方法，绑定到自己身上，但是要避免名字冲突。



## 对象构造和原型链总结

上面不论是有多少对象构造模式和原型继承模式，只要理解其本质，就容易根据自己的需要实现想要的效果，上面的各种方式都是套路。

构造函数为了构造对象，实现不同功能，第一要先有一个对象（不论怎么来的），然后控制 `原型链` 和 `作用域链`。

下图是一个JavaScript Prototype Chain关系图：[查看原图](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/javascript-prototype.png)


![JavaScript Prototype Chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/javascript-prototype.png)

上面的内容都是静态的内容，主要是想把 原型链 讲清楚。



## 函数


### 函数声明和函数表达式

函数声明: `function 函数名称 (参数){ 函数体 }`，也是函数定义。

函数表达式： `[var f = ] function [函数名称](参数){ 函数体 }`，如果有函数名，就是命名函数表达式。

所以，可以看出，如果不声明函数名称，它肯定是表达式，可如果声明了函数名称的话，如何判断是函数声明还是函数表达式呢？

ECMAScript是通过上下文来区分的，如果function foo(){}是作为赋值表达式的一部分的话，那它就是一个函数表达式，如果function foo(){}被包含在一个函数体内，或者位于程序的最顶部的话，那它就是一个函数声明。

```js
function foo(){}              // 声明，因为它是程序的一部分

var bar = function foo(){};   // 表达式，因为它是赋值表达式的一部分
new function bar(){};         // 表达式，因为它是new表达式

(function(){
  function bar(){}            // 声明，因为它是函数体的一部分
})();
```

还有一种函数表达式不太常见，就是被括号括住的(function foo(){})，他是表达式的原因是因为括号， `()`是一个分组操作符，它的内部只能包含表达式，我们来看几个例子：

```js
function foo(){}      // 函数声明
(function foo(){});   // 函数表达式：包含在分组操作符内

try {
  (var x = 5);        // 分组操作符，只能包含表达式而不能包含语句：这里的var就是语句
} catch(err) {
  // SyntaxError
}
```

在使用eval对JSON进行执行的时候，JSON字符串通常被包含在一个圆括号里：`eval('(' + json + ')')`，这样做的原因就是因为分组操作符，也就是这对括号，会让解析器强制将JSON的花括号解析成表达式而不是代码块。

```js
  try {
    { "x": 5 }; // "{" 和 "}" 做解析成代码块
  } catch(err) {
    // SyntaxError
  }

  ({ "x": 5 }); // 分组操作符强制将"{" 和 "}"作为对象字面量来解析
```


现在，在我们知道了对象的基础之后，让我们看看运行时程序的执行**runtime program execution**在ECMAScript中是如何实现的。



## 执行上下文堆栈


* EC(执行环境或者执行上下文，Execution Context)
* ECS(执行环境栈Execution Context Stack)
* VO(变量对象，Variable Object)
* AO(活动对象，Active Object)
* ScopeChain(作用域链)和`[[scope]]`属性


有三种类型的ECMAScript代码：`全局代码`、`函数代码`和`eval代码`


* 每个代码是在其执行上下文（EC）中被求值的。
* 全局上下文只有一个，可能有多个函数执行上下文以及eval执行上下文。
* 对一个函数的每次调用，会进入到函数执行上下文中，并对函数代码类型进行求值。
* 每次对eval函数进行调用，会进入eval执行上下文并对其代码进行求值。


注意，一个函数可能会创建无数的上下文，因为对函数的每次调用（即使这个函数递归的调用自己）都会生成一个具有新状态的上下文：

```js
function foo(bar) {}
// call the same function,
// generate three different contexts in each call,
// with different context state (e.g. value of the "bar" argument)
foo(10);
foo(20);
foo(30);
```


一个执行上下文(EC)可能会触发另一个上下文(EC)，如，一个函数调用另一个函数。从逻辑上来说，这是以栈的形式实现的，它叫作执行上下文栈(ECS)。


一个触发其他上下文的上下文叫作`caller`，被触发的上下文叫作`callee`，`callee`在同一时间可能是一些其他`callee`的`caller`。


当一个`caller`触发（调用）了一个`callee`，这个`caller`会暂缓自身的执行，然后把控制权传递给`callee`，控制权转移。


这个`callee`被push到栈中，并成为一个`活动的`执行上下文，在`callee`的上下文结束后（`callee`可能简单的返回或者由于异常而退出，一个抛出的但没有被捕获的异常可能退出一个或者多个上下文），它会把控制权返回给`caller`，然后`caller`的上下文继续执行直到它结束，以此类推。


@see https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/caller

> function.caller[Non-standard]
>
> The function.caller property returns the function that invoked the specified function.
> If the function f was invoked by the top level code, the value of f.caller is null, otherwise it's the function that called f.
>
> This property replaces the obsolete arguments.caller property of the arguments object.
>
> The special property `__caller__`, which returned the activation object of the caller thus allowing to reconstruct the stack, was removed for security reasons.

```js
function f(n) { g(n - 1); }
function g(n) { if (n > 0) { f(n); } else { stop(); } }
f(2);

// f(2) -> g(1) -> f(1) -> g(0) -> stop()

// stop.caller === g && f.caller === g && g.caller === f
```

Example:

```js
function trace() {
  var f = trace;
  var stack = 'Stack trace:';
  while (f) {
    stack += '\n' + f.name;
    f = f.caller;
  }
  return stack;
}

function myFunc() {
   return trace();
}
var stacks = myFunc();
console.log(stacks);
function f() {
  return myFunc();
}
var stacks = f();
console.log(stacks);
```


下图是上面代码的函数调用链，对应于执行上下文(EC)，在引擎层面，函数只是执行上下文的一个属性。

![caller-chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/caller-chain.png)


所有ECMAScript程序的运行时可以用执行上下文栈（ECS）来表示，栈顶是当前活动的上下文：

![ec-stack](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/ec-stack.png)


当程序开始的时候它会进入**全局执行上下文**，此上下文位于栈顶并且是栈中的第一个元素。然后全局代码进行一些**初始化**，创建需要的对象和函数。


在全局上下文的执行过程中，它的代码会触发其他函数，进入它们自己的执行上下文，向栈中push新的元素，以此类推。


当初始化完成之后，运行时系统就会等待一些事件，这些事件将会触发一些函数，从而进入新的执行上下文中。


在下个图中，拥有一些函数上下文EC1和全局上下文Global EC，当EC1进入和退出全局上下文的时候下面的栈将会发生变化：

![ec-stack-changes](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/ec-stack-changes.png)


这就是ECMAScript的运行时系统如何真正地管理代码执行的。


栈中的每个执行上下文都可以用一个对象来表示。


让我们来看看它的结构以及一个上下文到底需要什么状态（属性）来执行它的代码。


### 执行上下文


一个执行上下文可以抽象的表示为一个简单的对象。每一个执行上下文拥有一些属性（可以叫作上下文状态）用来跟踪和它相关的代码的执行过程。


在下图中展示了一个上下文的结构：

![execution-context](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/execution-context.png)

除了这三个必需的属性`变量/活动对象`、`作用域链`、`this`之外，执行上下文可以拥有其他附加的状态，这取决于实现。

让我们详细看看上下文中的这些重要的属性。


### 变量对象（variable object）


`变量对象`是与`执行上下文`相关的`数据作用域`。它是一个与上下文相关的特殊对象，其中存储了在上下文中定义的`变量`和`函数`。

> 函数表达式（与函数声明相对）不包含在变量对象之中。

变量对象是一个抽象概念。对于不同的上下文类型，在物理上，是使用不同的对象。
在全局上下文中变量对象就是全局对象本身，这就是为什么我们可以通过 **全局对象的属性名** 来关联 **“全局变量”**。

关于全局变量：JavaScript中并不存在全局变量，所谓的全局变量，不过是Global对象的一个属性，叫**全局属性**还差不多，变量和属性虽然都是数据的引用方式，但是却有很大差别。

Example:

```js
var global = global || window;
global.env = 'production';
NODE_ENV = 'production';
console.log(env);
console.log(global.NODE_ENV);
// 访问 全局属性 直接通过属性名就可以了。
// 这也是为什么被误称为 全局对象 的原因之一。
```


让我们在全局执行上下文中考虑下面这个例子：

```js
var foo = 10;
function bar() {}       // function declaration, FD
(function baz() {});    // function expression, FE
console.log(
  this.foo == foo,      // true
  window.bar == bar     // true
);
console.log(baz); // ReferenceError, "baz" is not defined
```

之后，全局上下文的`变量对象`将会拥有如下属性：

![variable-object](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/variable-object.png)

函数baz是一个函数表达式，没有被包含在变量对象之中。这就是为什么当我们想要在函数自身之外访问它的时候会出现ReferenceError。

注意，与其他语言（比如C/C++）相比，在ECMAScript中只有函数可以创建一个新的作用域。在函数作用域中所定义的变量和内部函数在函数外边是不能直接访问到的，而且并不会污染全局变量对象。

使用eval我们也会进入一个新的执行上下文。无论如何，eval使用全局的变量对象或者使用caller（比如eval被调用时所在的函数）的变量对象。

那么函数和它的变量对象是怎么样的？在函数上下文中，变量对象是以`活动对象`来表示的。


### 活动对象（activation object）


当一个函数被`caller`调用，一个特殊的对象，叫作`活动对象`（activation object）将会被创建。

这个对象中包含形参和那个特殊的`arguments`对象（是对形参的一个映射，但是值是通过索引来获取）。活动对象之后会做为函数上下文的变量对象来使用。

换句话说，函数的*活动对象*就是一个同样简单的*变量对象*，但是除了变量和函数声明之外，它还存储了*形参*和*arguments*对象，并叫作*活动对象*。

即：*活动对象* <=> *变量对象* + *形参* + *arguments*

全局上下文中并没有*形参*，更没有*arguments（实参）*，所以和函数上下文不同。

考虑如下例子：

```js
function foo(x, y) {
  var z = 30;
  function bar() {}     // FD
  (function baz() {});  // FE
}
foo(10, 20);
```

我们看下函数foo的上下文中的活动对象（activation object，简称AO）：

![activation-object](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/activation-object.png)

函数表达式baz还是没有被包含在`变量/活动对象`中。

关于这个主题所有细节方面（像变量和函数声明的提升问题（hoisting））的完整描述可以在同名的章节第二章 变量对象中找到。

注意，在ES5中`变量对象`和`活动对象`被并入了`词法环境模型`（lexical environments model），详细的描述可以在对应的章节找到。

众所周知，在ECMAScript中我们可以使用内部函数，然后在这些内部函数我们可以引用父函数的变量或者全局上下文中的变量。

当我们把变量对象命名为上下文的作用域对象，与上面讨论的原型链相似，这里有一个叫作`作用域链`的东西。


### 作用域链(scope chain)


作用域链是一个对象列表，上下文代码中出现的标识符在这个列表中进行查找。

这个规则还是与原型链同样简单：如果一个变量在函数自身的作用域（`变量/活动对象`）中没有找到，那么将会查找它父函数（外层函数）的`变量/活动对象`，以此类推。

就上下文而言，标识符指的是：*变量名称、函数声明、形参 等*。

当一个函数在其代码中引用一个不是*局部变量*（或者局部函数或者一个形参）的标识符，那么这个标识符就叫作*自由变量*，搜索这些自由变量(free variables)正好就要用到*作用域链*。

在通常情况下，*作用域链*是一个包含所有*Caller的变量/活动对象*__加上（在作用域链头部的）*Callee变量/活动对象*的一个列表。

这个作用域链也可以包含任何其他对象，比如，在上下文执行过程中动态加入到作用域链中的对象－像with对象或者特殊的catch从句（catch-clauses）对象。

当解析一个标识符的时候，会从作用域链中的*活动对象*开始查找，然后（如果这个标识符在函数自身的活动对象中没有被查找到）向作用域链的上一层查找－重复这个过程，就和原型链查找一样。

综上：*作用域链* 可以看作是 *变量对象链*。

```js
var x = 10;
(function foo() {
  var y = 20;
  (function bar() {
    var z = 30;
    // "x" and "y" are "free variables"
    // and are found in the next (after
    // bar's activation object) object
    // of the bar's scope chain
    console.log(x + y + z);
  })();
})();
```

我们可以假设通过隐式的 `__parent__` 属性来和 `作用域链对象` 进行交互，这个属性指向作用域链中的下一个对象。

这个方案可能在真实的Rhino代码中经过了测试，并且这个技术很明确得被用于ES5的词法环境中（在那里被叫作outer连接）。

作用域链的另一个表现方式可以是一个简单的数组。利用 `__parent__` 概念，我们可以用下面的图来表现上面的例子（并且父变量对象存储在函数的`[[Scope]]`属性中）：

![scope-chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/scope-chain.png)

在代码执行过程中，作用域链可以通过使用with语句和catch从句对象来增强。并且由于这些对象是简单的对象，它们可以拥有原型（和原型链）。

这个事实导致作用域链查找变为两个维度：（1）首先是作用域链连接，然后（2）在每个作用域链连接上－深入作用域链连接的原型链（如果此连接拥有原型）。

对于这个例子：

```js
Object.prototype.x = 10;
var w = 20;
var y = 30;
// in SpiderMonkey global object i.e. variable object of the global context inherits from "Object.prototype",
// so we may refer "not defined global variable x", which is found in the prototype chain
console.log(x); // 10
(function foo() {
  // "foo" local variables
  var w = 40;
  var x = 100;
  // "x" is found in the "Object.prototype", because {z: 50} inherits from it
  with ({z: 50}) {
    console.log(w, x, y , z); // 40, 10, 30, 50
  }
  // after "with" object is removed from the scope chain,
  // "x" is again found in the AO of "foo" context;
  // variable "w" is also local
  console.log(x, w); // 100, 40
  // and that's how we may refer shadowed global "w" variable in the browser host environment
  console.log(window.w); // 20
})();
```

我们可以给出如下的结构（确切的说，在我们查找`__parent__`连接之前，首先查找`__proto__`链）：

![scope-chain-with](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/scope-chain-with.png)

注意，不是在所有的实现中全局对象都是继承自Object.prototype。上图中描述的行为（从全局上下文中引用「未定义」的变量x）可以在诸如SpiderMonkey引擎中进行测试。

由于所有父变量对象都存在，所以在内部函数中获取父函数中的数据没有什么特别－就是遍历作用域链去搜寻需要的变量。

就像上边提及的，在一个上下文结束之后，它所有的状态和它自身都会被销毁，这个上下文（函数）可能会返回一个函数，这个返回的函数之后可能在另一个上下文中被调用。
如果**自由变量**的上下文已经「消失」了，将会出现问题，有一个方式可以帮助我们解决这个问题，叫作**闭包**，其在ECMAScript中就是和作用域链的概念紧密相关的。

然后我们移动到下个部分，考虑一下执行上下文的最后一个属性，关于this值的概念。



### This


this是一个与执行上下文相关的特殊对象。因此，它可以叫作**上下文对象**（也就是用来指明执行上下文是在哪个上下文中被触发的对象）。

任何对象都可以做为上下文中的this的值。在一些对ECMAScript执行上下文和部分this的描述中的所产生误解，this经常被错误的描述成是变量对象的一个属性。

正确的是： **this是执行上下文的一个属性，而不是变量对象的一个属性**。

这个特性非常重要，因为与变量相反，this从不会参与到标识符解析过程。
换句话说，在代码中当访问this的时候，它的值是直接从执行上下文中获取的，并不需要任何作用域链查找。
this的值只在进入上下文的时候进行一次确定。

顺便说一下，与ECMAScript相反，Python的方法都会拥有一个被当作简单变量的self参数，这个变量的值在各个方法中是相同的的并且在执行过程中可以被更改成其他值。
在ECMAScript中，给this赋一个新值是不可能的，因为，它不是一个变量并且不存在于变量对象中。

在全局上下文中，this就等于全局对象本身（这意味着，这里的this等于变量对象）：

```js
var x = 10;
console.log(x, this.x, window.x);

function f() {
  console.log(this);
};
f(); // 输出了全局对象
```

在函数上下文的情况下，对函数的每次调用，其中的this值可能是不同的。这个this值是通过函数调用表达式（也就是函数被调用的方式）的形式由caller所提供的。

举个例子，下面的函数foo是一个callee，在全局上下文中被调用，此上下文为caller。

让我们通过例子看一下，对于一个代码相同的函数，this值是如何在不同的调用中（函数触发的不同方式），由caller给出不同的结果的：

```js
// the code of the "foo" function never changes, but the "this" value differs in every activation

function foo() {
  alert(this);
}

// caller activates "foo" (callee) and provides "this" for the callee

foo(); // global object
foo.prototype.constructor(); // foo.prototype

var bar = { baz: foo };

bar.baz(); // bar

(bar.baz)();            // also bar
(bar.baz = bar.baz)();  // but here is global object
(bar.baz, bar.baz)();   // also global object
(false || bar.baz)();   // also global object

var otherFoo = bar.baz;
otherFoo(); // again global object
```


### 执行上下文总结

* 变量/活动对象：记录运行时所需要的数据，变量、函数、形参、实参等。
* 作用域链：变量/活动对象 链到一起，为引擎进行变量查找提供基础。
* this：指明了当前执行的函数作用在哪个对象身上，方法的操作主体是谁。

全局上下文 和 函数上下文比较：

在全局上下文中，`this`就等于全局对象本身，即 `this = 全局对象本身 = 变量对象`，在函数上下文中，this是执行上下文的一个属性。

所以这也解释了一些现象，全局作用域下的代码成为了全局对象的属性了，如上面示例的代码。



## 闭包

在ECMAScript中，函数是一级（first-class）对象。这个术语意味着函数可以做为参数传递给其他函数（「函数类型参数」（funargs，是"functional arguments"的简称））。

接收「函数类型参数」的函数叫作`高阶函数`或者，贴近数学一些，叫作高阶操作符。同样函数也可以返回一个函数。

这有两个在概念上与「函数类型参数（funargs）」和「函数类型值（functional values）」相关的问题。

并且这两个子问题在"Funarg problem"中很普遍。为了解决整个"funarg problem"，闭包（closure）的概念被创造了出来。

我们详细的描述一下这两个子问题（我们将会看到这两个问题在ECMAScript中都是使用图中所提到的函数的`[[Scope]]`属性来解决的）。

「funargs问题」的第一个子问题是「向上funarg问题」（upward funarg problem）。它会在当一个函数从另一个函数中返回并且使用上面所提到的自由变量的时候出现。

为了在即使父函数上下文销毁的情况下也能访问其中的变量，内部函数在被创建的时候会在它的`[[Scope]]`属性中保存父函数的作用域链。

所以当函数被调用的时候，它上下文的作用域链会被格式化成 *活动对象* 与 *[[Scope]]* 属性的和：`Scope chain = Activation object + [[Scope]]`。

函数在创建时会保存父函数的**作用域链**，这个保存下来的**作用域链**将会在未来的函数调用时用来**查找变量**。

如果从对象引用层面来理解，*[[Scope]]*被另外一个对象（函数）引用，引擎不会回收这些资源，所以闭包容易带来内存泄漏的隐患。

```js
function foo() {
  var x = 10;
  return function bar() {
    console.log(x);
  };
}
// "foo" returns also a function and this returned function uses free variable "x"
var returnedFunction = foo();
// global variable "x"
var x = 20;
// execution of the returned function
returnedFunction(); // 10, but not 20
```

这个类型的作用域叫作**静态（或者词法）作用域**。我们看到变量x在返回的bar函数的`[[Scope]]`属性中被找到。

通常来说，也存在动态作用域，那么上面例子中的变量x将会被解析成20，而不是10。但是，动态作用域在ECMAScript中没有被使用。


「funarg问题」的第二个部分是「向下funarg问题」。这种情况下可能会存在一个父上下文，但是在解析标识符的时候可能会模糊不清。

问题是：标识符该使用哪个作用域的值－以静态的方式存储在函数创建时刻的还是在执行过程中以动态方式生成的，比如caller的作用域？

为了避免这种模棱两可的情况并形成闭包，静态作用域被采用：

```js
// global "x"
var x = 10;
// global function
function foo() {
  console.log(x);
}
(function (funArg) {
  // local "x"
  var x = 20;
  // there is no ambiguity, because we use global "x", which was statically saved in [[Scope]] of the "foo" function,
  // but not the "x" of the caller's scope, which activates the "funArg"
  funArg(); // 10, but not 20
})(foo); // pass "down" foo as a "funarg"
```

词法作用域/静态作用域：变量的作用域是在定义时决定而不是执行时决定，也就是说词法作用域取决于源码，通过静态分析就能确定，因此词法作用域也叫做静态作用域。 with和eval除外，所以只能说JS的作用域机制非常接近词法作用域（Lexical scope）。


我们可以断定静态作用域是一门语言拥有闭包的必需条件。但是，一些语言可能会同时提供动态和静态作用域，允许程序员做选择－什么应该包含（closure）在内和什么不应包含在内。

由于在ECMAScript中只使用了静态作用域（比如我们对于funarg问题的两个子问题都有解决方案），所以结论是：ECMAScript完全支持闭包，技术上是通过函数的`[[Scope]]`属性实现的。


现在我们可以给闭包下一个准确的定义：

闭包是一个代码块（在ECMAScript是一个函数）和以`静态方式`/`词法方式`进行存储的所有父作用域的一个集合体。所以，通过这些存储的作用域，函数可以很容易的找到**自由变量**。

闭包使得一个函数有权访问另一个函数作用域中的变量。

注意，由于每个（标准的）函数都在创建的时候保存了`[[Scope]]`，所以理论上来讲，ECMAScript中的所有函数都是闭包。

另一个需要注意的重要事情是，多个函数可能拥有相同的父作用域，比如当我们拥有两个内部/全局函数的时候。

在这种情况下，`[[Scope]]`属性中存储的变量是在拥有相同父作用域链的所有函数之间共享的。一个闭包对变量进行的修改会体现在另一个闭包对这些变量的读取上：

```js
function baz() {
  var x = 1;
  return {
    foo: function foo() { return ++x; },
    bar: function bar() { return --x; }
  };
}
var closures = baz();
console.log(
  closures.foo(), // 2
  closures.bar()  // 1
);
```

以上代码可以通过下图进行说明：

![shared-scope](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/shared-scope.png)

确切来说这个特性在循环中创建多个函数的时候会使人非常困惑。在创建的函数中使用循环计数器的时候，一些程序员经常会得到非预期的结果，所有函数中的计数器都是同样的值。


```js
var data = [];
for (var k = 0; k < 3; k++) {
  data[k] = function () {
    console.log(k);
  };
}
data[0](); // 3, but not 0
data[1](); // 3, but not 1
data[2](); // 3, but not 2
// 这里有几种技术可以解决这个问题。其中一种是在作用域链中提供一个额外的对象－比如，使用额外函数：
var data = [];
for (var k = 0; k < 3; k++) {
  data[k] = (function (x) {
    return function () {
      console.log(x);
    };
  })(k); // pass "k" value
}
// now it is correct
data[0](); // 0
data[1](); // 1
data[2](); // 2
```


现在是到了该揭开谜底的时候了－因为所有这些函数拥有同一个`[[Scope]]`，这个属性中的循环计数器的值是最后一次所赋的值。


c/c++: 函数无法嵌套定义，可以传递函数指针
java c#:
python ruby
go swift
javascript typescript coffeescript ...



## 执行过程


### 执行顺序

* 编译型语言，编译步骤分为：词法分析、语法分析、语义检查、代码优化和字节生成。
* 解释型语言，通过词法分析和语法分析得到语法分析树后，就可以开始解释执行了。

这里是一个简单原始的关于解析过程的原理，仅作为参考，详细的解析过程（各种JS引擎还有不同）还需要更深一步的研究。

JavaScript执行过程，如果一个文档流中包含多个script代码段（用script标签分隔的js代码或引入的js文件），它们的运行顺序是：

* 阶段一：解析
  * 步骤1. 载入第一个代码段（js执行引擎并非一行一行地执行程序，而是一段一段地分析执行的）。
  * 步骤2. 做词法分析->[词法作用域] 和 语法分析->[语法分析树]，如果有错则报语法错误(Syntax Error)（*解析时错误*，比如括号不匹配等），并跳转到步骤5。
  * 步骤3. 对 *var*变量 和 *function*定义 做 *预解析*（永远不会报错的，因为只解析正确的声明）。
* 阶段二：执行
  * 步骤4. 执行代码段，有错则报错（*运行时错误*，比如变量未定义）。
  * 步骤5. 如果还有下一个代码段，则读入下一个代码段，重复步骤2。
  * 步骤6. 结束


### 关键步骤

上面的过程，我们主要是分成两个阶段

* 解析(2,3)：通过 *语法分析* 和 *预解析* 构造的 *语法分析树*。
* 执行( 4 )：执行具体的某个函数，JS引擎在执行每个函数实例时，会创建一个 *执行上下文*。


### 关键概念

* 词法分析 -> 词法作用域
  * 变量的作用域是在定义时决定而不是执行时决定，也就是说词法作用域取决于源码，通过静态分析就能确定，因此词法作用域也叫做静态作用域。
  * 实际上，*运行时的作用域链* 并不是 *词法分析阶段* 得到的，而是运行时得到的，但是在 *词法分析阶段能够确定作用域* 是必须的，要不然写代码的人无法确定作用域，代码还怎么写。
    最终，人和解释器对代码的理解是一致的。某些情况下，静态分析也无法分析出完整的作用域链，比如递归的情况，这个阶段根本无法预知递归深度，无法得出实际的作用域链。
  * `with`和`eval`除外，所以只能说JS的作用域机制非常接近词法作用域（Lexical scope）。
  * *词法分析*（英语：lexical analysis）是计算机科学中将*字符序列*转换为*标记（token）序列*的过程。
  * *词法分析器（扫描器）*的功能输入源程序，按照构词规则分解成一系列单词符号。如：*关键字、标识符、常数、运算符、分界符*等。
* 语法分析树（SyntaxTree）
  * 可以直观地表示出这段代码的相关信息，具体的实现就是JS引擎创建了一些表。
  * 用来记录每个方法的 *内部变量集（variables）*、*内嵌函数集（functions）* 和 *作用域（scope）* 等。
* 执行环境/执行上下文（ExecutionContext）
  * 可理解为一个记录当前执行的方法*【外部描述信息】*的对象。
  * 记录所执行函数的 *活动对象（activeObject）*、*作用域链（scope-chain）*、*this*。
* 活动对象（activeObject）
  * 可理解为一个记录当前执行的方法*【内部执行信息】*的对象。
  * 记录 *内部变量集（variables）*、*内嵌函数集（functions）*、*实参（arguments）*、*作用域链（scopeChain）*等执行所需信息。
  * 直接 *内部变量集（variables）*、*内嵌函数集（functions）*是直接从第一步建立的 *语法分析树* 复制过来的。
  * 方法开始执行，活动对象里的内部变量集全部被设置为 `undefined`, 创建*形参（parameters*）和*实参（arguments）*对象，同名的实参，形参和变量之间是【引用】关系, 执行方法内的赋值语句，这才会对变量集中的变量进行赋值。
  * 变量查找规则是首先在当前执行环境的 *ActiveObject* 中寻找，没找到，则顺着执行环境中属性 *ScopeChain* 指向的 *ActiveObject* 中寻找，一直到 *Global Object*。
  * 方法执行完成后，内部变量值不会被重置，至于变量什么时候被销毁, 取决于方法实例是否存在*活动引用*，如没有就销毁活动对象。
* 作用域链
  * 简单的理解为 *【变量对象链】*，解释器可见的。
  * 词法作用域的实现机制就是作用域链（scopeChain），作用域链是一套按名称查找（Name Lookup）的机制。
* 闭包
  * 闭包是一个拥有许多变量和绑定了这些变量的环境的表达式（通常是一个函数），因而这些变量也是该表达式的一部分。
  * 保护函数内的变量安全，实现 *私有属性* 和 *私有方法*（不能被外部访问）。
  * 闭包就是将 *函数内部和函数外部* 连接起来的一座桥梁，让外部环境有途径访问内部变量。
  * 闭包函数可以访问所保持的作用域链上的外部环境。



### javascript词法分析

lexical-analyzer  Lexer  Tokenizer

词法分析主要分为3步：

* 第1步：分析形参
* 第2步：分析变量声明
* 第3步：分析函数声明


在词法分析阶段，变量声明和函数声明被提升

```js
var str = 'global';
function foo() {
  console.log(str); // undefined
  var str = 'local';
  console.log(str); // local
  var str;
  console.log(str);// local
  str = 'local';
  console.log(str);
}

foo();
```

var str = 'local';  <==> var str; str = 'local';

函数表达式中，变量声明部分被提升，但是知道执行到这一句时，变量才被赋值为一个函数，所以函数表达式需要在使用之前赋值，而函数声明这不需要。


### 模拟解析


模拟代码

```js
var escope = require('escope');
var esprima = require('esprima');
var estraverse = require('estraverse');

var code = `
var i = 1, j = 2, k = 3;
function a(o, p, x, q) {
  var x = 4;
  console.log(i);
  function b(r, s) {
    var i = 11, y = 5;
    console.log(i);
    function c(t) {
      var z = 6;
      console.log(i);
    }
    //函数表达式
    var d = function () {
      console.log(y);
    };
    c(60);
    d();
  }
  b(40, 50);
}
a(10, 20, 30);
`;

var ast = esprima.parse(code);
var scopeManager = escope.analyze(ast);

var currentScope = scopeManager.acquire(ast);   // global scope

// console.dir(ast, {depth: null});
console.dir(scopeManager, {depth: null});
```

![ESTree](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/estree.png)

上面的模拟代码生成了JS解析过程所产生的用于在执行阶段使用的信息，但是并不代表解释器真的是和这个一样的。
这些分析工具有很多，他们大都用于代码压缩、代码混淆、代码转换（ES6->ES5，babel，ts->js）、代码优化等方面。



## JavaScript线程模型


### 为什么JavaScript是单线程的？


单线程是相对多线程而言的，假如系统从来就没有过多线程这个概念，那么为什么JavaScript是单线程的这个问题就不存在了。

那为什么会存在这个问题呢？因为JavaScript可以实现并发，达到类似多线程的效果但是却没有用多线程来实现。

所以引出了另外的问题：为什么要用单线程而不是多线程实现呢？JavaScript如何用单线程实现并发？

JavaScript是以单线程的方式运行的，说到线程就自然联想到进程。

进程是应用程序的执行实例，每一个进程都是由私有的虚拟地址空间、代码、数据和其它系统资源所组成；

线程则是进程内的一个独立执行单元，在不同的线程之间是可以共享进程资源的。

在系统创建进程之后就开始启动执行进程的主线程，而进程的生命周期和这个主线程的生命周期一致，主线程的退出也就意味着进程的终止和销毁。

主线程是由系统进程所创建的，同时用户也可以自主创建其它线程，这一系列的线程都会并发地运行于同一个进程中。

显然，在多线程操作下可以实现应用的并行处理，从而以更高的CPU利用率提高整个应用程序的性能和吞吐量。

特别是现在很多语言都支持多核并行处理技术，然而JavaScript却以单线程执行。


网上很多声音都说这和它的历史有关系，其实这与它的用途有关，因为这个**用途**容易带来死锁，所以有一个更重要的原因——避免死锁。
作为浏览器脚本语言，JavaScript的主要用途是与用户互动，以及操作DOM，若以多线程的方式操作这些DOM，则可能出现操作的冲突。
假设有两个线程同时操作一个DOM元素，*线程1*要求浏览器删除DOM，而*线程2*却要求修改DOM样式，这时浏览器就无法决定采用哪个线程的操作。
当然，我们可以为浏览器引入**锁** 的机制来解决这些冲突，但这会大大提高复杂性，所以 JavaScript 从诞生开始就选择了单线程执行。


多线程的GUI框架特别容易死锁。[《Multithreaded toolkits: A failed dream?》](https://community.oracle.com/blogs/kgh/2004/10/19/multithreaded-toolkits-failed-dream)描述了其中的缘由，
大致是说GUI的行为大多都是从更抽象的顶部一层一层调用到操作系统级别，而事件则是反过来，从下向上冒泡，结果就是两个方向相反的行为在碰头，给资源加锁的时候一个正序，一个逆序，极其容易出现互相等待而饿死的情况。
AWT最初其实就是想设计成多线程的，但是使用者非常容易引起死锁和竞争，最后Swing还是做成了单线程的。
但凡这种**EventLoop+单线程**执行的模式，我们还可以找到很多，比如JDK的GUI线程模型，主线程就是一个**主事件循环**，还有Mac系统的Cocoa等等，都是这样的模式。


因为 JavaScript 是单线程的，在某一时刻内只能执行特定的一个任务，并且会阻塞其它任务执行。
那么对于**I/O**等耗时的任务，就没必要等待他们执行完后才继续后面的操作。
在这些任务完成前，JavaScript完全可以往下执行其他操作，当这些耗时的任务完成后则以回调的方式执行相应处理。
这些就是JavaScript与生俱来的特性：异步与回调？


对于不可避免的耗时操作（如：繁重的运算，多重循环），HTML5提出了WebWorker，它会在当前JavaScript的执行主线程中利用Worker开辟一个额外的线程来加载和运行特定的JavaScript脚本。
这个新的线程和JavaScript的主线程之间并不会互相影响和阻塞执行，而且在WebWorker中提供了这个新线程和JavaScript主线程之间数据交换的接口：`postMessage`和`onMessage`事件。
但WebWorker不能操作DOM的，任何需要操作DOM的任务都需要委托给JavaScript主线程来执行，所以虽然HTML5引入WebWorker，但是他受限的。（并没有改线JavaScript单线程的本质？）


事实上，JavaScript语法核心没有描述任何线程机制，大部分语言都没有在语言层面直接定义线程的。
线程都是作为核心库或者第三方库提供给开发者调用，所以也并不是因为javascript无法实现多线程。
如Node.js就有可以支持线程的库，HTML5也引入了WebWorker。


上面解释了JavaScript为什么要以单线的方式运行，既然JavaScript是单线程的，那么JavaScript是如何实现并发的？


### JavaScript如何用单线程实现并发？

JavaScript有个基于 **EventLoop** 的 **并发模型**，能把单线程的 JavaScript 使出 **多线程** 的 感觉。

首先区分一个概念：*并发(Concurency)*和*并行(Parallelism)*。

并行是指：一组程序按独立异步的速度执行，不等于时间上的重叠（同一个*时刻*发生)。
并发是指：在同一个*时间段*内，两个或多个程序执行，有时间上的重叠（宏观上是同时，微观上仍是顺序执行）。


[通信中的并行串行]https://zh.wikipedia.org/wiki/%E4%B8%B2%E8%A1%8C%E9%80%9A%E4%BF%A1

并行也指8位数据同时通过并行线进行传送，与之相对的是串行，这样数据传送速度大大提高，但并行传送的线路长度受到限制，因为长度增加，干扰就会增加，数据也就容易出错。


前者是逻辑上的同时发生，而后者是物理上的同时发生。所以，单核处理器也能实现并发。
并发和并行的区别就是 *一个处理器同时处理多个任务* 和 *多个处理器或者是多核的处理器同时处理多个不同的任务*。
就是一个人同时吃三个馒头和三个人同时吃三个馒头。

一个错误的结论：**javascript是不存在并发的，并发只是看起来像并发而已**。

![并发与并行](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/并发与并行.jpg)

如上图的第一个表，由于计算机系统只有一个CPU，故ABC三个程序从“微观”上是交替使用CPU，但交替时间很短，用户察觉不到，形成了“宏观”意义上的并发操作。

![stack-heap-queue](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/stack-heap-queue.png)

JavaScript的**EventLoop**的**并发模型**，其原理和操作系统进程调度很相似（只是模型相似），但是比操作系统的调度策略简单的多。


这种 **并发模型** 通常称为 **asynchronous** 或 **non-blocking** 模行。


#### Event_loop

[Event_loop](https://en.wikipedia.org/wiki/Event_loop)

In computer science, the event loop, message dispatcher, message loop, message pump, or run loop is a programming construct that waits for and dispatches events or messages in a program. 

之所以被称为EventLoop，是因为它是用类似以下方式实现：

```js
// other code
function eventloop() {
  while(eventHandler = waitForEvents()){
    eventHandler.processEvent();
  }
  sleep(); // 睡一下
  eventloop();
}
eventloop();
```

![eventloop-in-browser](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/eventloop-in-browser.png)

![eventloop-in-nodejs](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/eventloop-in-nodejs.png)

从图中来看，EventLoop好像并不是V8引擎的一部分，如果真是这样的话，那么在EventLoop应该是Node.js或Browser实现的，不过这不影响理解。

EventLoop绝不能阻塞，这个位置阻不阻塞不是JavaScript代码能决定的。保证当应用等待异步请求返回时，其仍能处理其它操作。


#### 任务队列

![memory-layout](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/memory-layout.jpg)

![memory-layout](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/memory-layout-1.png)

* Stack 这里放着JavaScript正在执行的任务，每个任务被称为帧（frame）。
* Heap 一个用来表示内存中一大片非结构化区域的名字，对象都被分配在这。
* TasksQueue 一个 JavaScript Runtime 包含了一个任务队列，该队列是由一系列待处理的任务（包含事件处理函数）组成。

每个任务都有相对应的函数，当栈为空时，就会从任务队列中取出一个任务，然后进行处理。
该处理会调用与该任务相关联的一系列函数（因此会创建一个初始栈帧），当该任务处理完毕后，栈就会再次为空。

如果I/O设备完成任务或用户触发事件，那么相关事件处理函数就会进入“任务队列”，当主线程处理完上一个任务时，就会调度“任务队列”里第一个待处理任务。
当然，对于定时器，当到达其指定时间时，才会把相应任务插到“任务队列”尾部。

任务不能被中断。

每当某个任务执行完后，其它任务才会被执行。也就是说，当一个函数运行时，它不能被取代且会在其它代码运行前先完成。不会像多线程那样，多个任务交替执行。
当然，这也带来一个缺点：当一个任务完成时间过长，那么应用就不能及时处理用户的交互（如点击事件），甚至导致该应用奔溃。
这与操作系统的进程调度模式有根本的不同，操作系统不能允许一个进程长时间占有CPU，以保证其他程序能够有机会得到执行。
一个比较好解决方案是：将任务完成时间缩短，或者尽可能将一个任务分成多个任务执行，但是这需要开发人员来保证。


#### 只有EventLoop是不够的

通过上面对EventLoop的介绍，已经了解了JavaScript是如何实现并发的，但是只有EventLoop是不够的。那就是任务队列中的方法是哪里来的？

其实我们已经知道答案，那就是异步函数。异步函数的回掉函数在异步函数执行完成之后，被放入了任务队列。同步函数是没有这个能力的，因为没这个需要。

#### 异步和回掉

回掉可以看作是一种协议，用来进行消息通知，Node.js的事件驱动同样也是用来消息通知，但同样也是由回掉函数来处理，Promise也是基于回掉的。

回掉和异步不是一定要连在一起。下面这段代码，有回掉函数，但是依然是同步的。

```js
function sort(compare) {
  return compare(l, r);
}
```

@see
[回调函数](https://zh.wikipedia.org/wiki/%E5%9B%9E%E8%B0%83%E5%87%BD%E6%95%B0)
[回调函数是什么？](https://www.zhihu.com/question/19801131)

#### 事件轮询和异步回掉带来的效果

> 改变了代码的执行顺，代码的执行顺序不再是按照代码的前后关系逐句执行。

代码一段一段入栈（ECS）执行，因为栈的一个单元（EC）可以看作是一个函数，所以这里一段代码就当作一个函数来理解。

当这些最外层的函数执行完之后是不是程序就没事干了？

肯定是不是了。怎么可能让CPU闲着，并且还有很多事情做，只是这些事情还没说开始。

那这个时候 JS 该做什么？

大家都知道，当最外层的代码执行过之后，JS在等待一些事件发生，然后对这些事件进行相应的处理。那么该做的就是等待事件发生。

正在做什么？

最外层的代码做的工作可以看作是初始化工作，加载各个模块，初始化数据库连接、创建目录、注册各种事件处理函数、发起请求、监听网络等。即向系统交代我们的期待。

最外层代码执行完之后（实际上就是那么一瞬间完成），那他现在应该做的就是：等待关注的事情发生，使用的方式就是轮询，轮询的主体就是任务队列。

这些事件可能持续不断的产生，甚至是同时产生，这些事件的处理函数放到任务队列当中，等待JS引擎处理。

JS在这里充当了任务的生产者，任务结果的消费者。这样做可行的场景就是：生产任务和回掉处理函数执行的时间相比之下非常短，而实际任务的执行时间相比之下非常长。

1. JS引擎开始执行全局环境下的代码，创建全局执行环境并入栈，然后开始*事件循环*。
1. JS引擎读取堆栈信息，这种方式下，第一次栈一定不为空。
    1. 如果有任务需要处理，将任务相关处理函数推入执行环境栈中。处理任务的过程可能还是向系统交代其他工作。下一个待处理的任务什么时候处理取决于这个任务什么时候处理完成。
    1. 如果没有任务需要处理，JS引擎过一会儿再来看看。

所以异步函数带来的效果就是，代码执行的时机是不确定的，它取决于异步函数什么时候完成，在还取决于在任务队列中的位置，先进先出。
执行时机不再是代码的静态位置决定，但是闭包却又是静态作用域决定的。这两点结合在一起构成一个强大的模型。

通过上面的分析可以看到，JS的执行过程实际上类似于树的遍历，但是既不是广度的也不是深度的，是时间优先的，谁先有机会执行就谁先。
而且这颗树在持续不断的生长，甚至没有边界，直到进程退出。遍历过的部分正常情况都会被回收，静态的代码是有限的，动态的活动对象是无限的。


#### 结论

单线程指的是我们编写的JavaScript代码是运行在一个线程当中，而JavaScript引擎进行的是并发调度。

从我们的角度，JavaScript确实是并发的，因为JS同时可以处理很多任务，但是实际上这些任务并不是JavaScript引擎处理的，而是由运行环境的扩展（如setTimeout）来实现的。
这些扩展作为JavaScript的一部分，在调用的时候肯定是JS线程在执行，扩展程序在执行时可以创建其他线程来工作，JS线程将不会阻塞继续处理其他任务，而这个新线程在任务处理完成之后，会将回掉函数插入到JS的任务队列中。
如果扩展代码是同步的，如Node.jsApi的fs部分的同步函数，那么JS执行线程将被阻塞。
JavaScript只是把任务交代出去，对任务的结果进行处理，处理的函数已经通过回掉的方式写好了，处理函数可以继续安排新的异步任务。

单线程：指的是JavaScript代码是在同一个线程中运行。任何一段JavaScript代码阻塞了执行流，那么程序将会卡在这里。
任务队列：上面说有有一个线程负责与其他线程交互，其实可以没有，JS扩展作为运行环境的一部分，具有与JS引擎交互的能力，如异步完成之后，将任务处理程序放入任务队列。

1. 几个线程？其他线程做什么？

  JS代码肯定执行在一个线程中这是毋庸置疑的。通过上面的描述也无须另一个线程。所以有些博客中说有一个EventLoop线程，我觉的是没必要的。
  其他线程是在js调用异步函数是产生的，但不是一定需要创建新的线程。如Node中监听文件描述符只用一个线程就够了，如果这个线程已经存在就无须再创建。

1. TasksQueue中的队列是谁放进来的？是否有一个维护队列的线程？

  异步函数是JS引擎的在运行环境中的扩展。



### Timer


#### How JavaScript Timers Work？

从基础的层面来讲，理解JavaScript的定时器是如何工作的是非常重要的。
计时器的执行常常和我们的直观想象不同，那是因为JavaScript引擎是单线程的。
我们先来认识一下下面三个函数是如何控制计时器的。

* `var id = setTimeout(fn, delay);`       - 初始化一个计时器，然后在指定的时间间隔后执行。该函数返回一个唯一的标志ID（Number类型），我们可以使用它来取消计时器。
* `var id = setInterval(fn, delay);`      - 和setTimeout有些类似，但它是连续调用一个函数（时间间隔是delay参数）直到它被取消。
* `clearInterval(id);, clearTimeout(id);` - 使用计时器ID（setTimeout 和 setInterval的返回值）来取消计时器回调的发生

为了理解计时器的内在执行原理，有一个重要的概念需要加以探讨：计时器的延迟(delay)是无法得到保障的。
由于所有JavaScript代码是在一个线程里执行的，所有异步事件（例如，鼠标点击和计时器）只有拥有执行机会时才会执行。

用一个很好的图表加以说明：

![Timers.png](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/Timers.png)

在这个图表中有许多信息需要理解，如果完全理解了它们，你会对JavaScript引擎如何实现异步事件有一个很好的认识。

这是一个一维的图标：垂直方向表示时间，蓝色的区块表示JavaScript代码执行块。例如第一个JavaScript代码执行块需要大约18ms，鼠标点击所触发的代码执行块需要11ms，等等。

由于JavaScript引擎同一时间只执行一条代码，所以每一个JavaScript代码执行块会“阻塞”其它异步事件的执行。
这就意味着当一个异步事件发生（例如，鼠标点击，计时器被触发，或者Ajax异步请求）后，这些事件的回调函数将排在执行队列的最后等待执行；

从第一个JavaScript执行块开始研究，在第一个执行块中两个计时器被初始化：一个10ms的setTimeout()和一个10ms的setInterval()。
依据何时何地计时器被初始化(计时器初始化完毕后就会开始计时)，计时器实际上会在第一个代码块执行完毕前被触发。
但是，计时器上绑定的函数不会立即执行，实际上，被延迟的函数将依次排在执行队列的最后，等待下一次恰当的时间再执行。

此外，在第一个JavaScript执行块中我们看到了一个“鼠标点击”事件发生了。
一个JavaScript回调函数绑定在这个异步事件上了（我们从来不知道用户什么时候执行这个（点击）事件，因此认为它是异步的），这个函数不会被立即执行，和上面的计时器一样，它将排在执行队列的最后，等待下一次恰当的时候执行。

当第一个JavaScript执行块执行完毕后，浏览器会立即问一个问题：哪个函数（语句）在等待被执行？
在这时，一个“鼠标点击事件处理函数”和一个“计时器回调函数”都在等待执行。
浏览器会选择一个（实际上选择了“鼠标点击事件的处理函数”，因为由图可知它是先进队的）立即执行。
而“计时器回调函数”将等待下次适合的时间执行。
显然，引擎在处理完一个任务之后，会查看任务队列，如果队列中无任务，则会等下一轮轮询。

注意，当“鼠标点击事件处理函数”执行的时候，setInterval的回调函数第一次被触发了。
和setTimeout的回调函数一样，它将排到执行队列的最后等待执行。
但是，一定要注意这一点：当setInterval回调函数第二次被触发时（此时setTimeout函数仍在执行）setTimeout的第一次触发将被抛弃掉。
当一个很长的代码块在执行时，可能把所有的setInterval回调函数都排在执行队列的后面，代码块执行完之后，结果便会是一大串的setInterval回调函数等待执行，并且这些函数之间没有间隔，直到全部完成。
所以，浏览器倾向于的当没有更多interval的处理函数在排队时再将下一个处理函数排到队尾(这是由于间隔的问题)。

我们能够发现，当第三个setInterval回调函数被触发时，之前的setInterval回调函数仍在执行。
这就说明了一个很重要的事实：setInterval不会考虑当前正在执行什么，而把所有的堵塞的函数排到队列尾部。
这意味着两次setInterval回调函数之间的时间间隔会被牺牲掉（缩减）。

最后，当第二个setInterval回调函数执行完毕后，我们可以看到没有任何程序等待JavaScript引擎执行了。
这就意味着浏览器现在在等待一个新的异步事件的发生。
在50ms时一个新的setInterval回调函数再次被触发，这时，没有任何的执行块阻塞它的执行了。所以它会立刻被执行。

让我们用一个例子来阐明setTimeout和setInterval之间的区别：

```js
  setTimeout(function(){
    /* Some long block of code... */
    setTimeout(arguments.callee, 10);
  }, 10);

  setInterval(function(){
    /* Some long block of code... */
  }, 10);
```

这两句代码乍一看没什么差别，但是它们是不同的。setTimeout回调函数的执行和上一次执行之间的间隔至少有10ms，而setInterval的回调函数将尝试每隔10ms执行一次，不论上次是否执行完毕。

在这里我们学到了很多知识，总结一下：

JavaScript引擎是单线程的，强制所有的异步事件排队等待执行
setTimeout 和 setInterval 在执行异步代码的时候有着根本的不同
如果一个计时器被阻塞而不能立即执行，它将延迟执行直到下一次可能执行的时间点才被执行（比期望的时间间隔要长些）
如果setInterval回调函数的执行时间将足够长（比指定的时间间隔长），它们将连续执行并且彼此之间没有时间间隔。
上述这些知识点都是非常重要的。了解了JavaScript引擎是如何工作的，尤其是大量的异步事件（连续）发生时，才能为构建高级应用程序打好基础。

#### 零延迟 `setTimeout(func, 0)`

零延迟并不是意味着回调函数立刻执行，它取决于主线程当前是否空闲与“任务队列”里其前面正在等待的任务。

用途：改变执行顺序

```js
(function () {
  console.log('this is the start');
  setTimeout(function cb() {
    console.log('this is a msg from call back');
  });
  console.log('this is just a message');
  setTimeout(function cb1() {
    console.log('this is a msg from call back1');
  }, 0);
  console.log('this is the  end');
})();
// 输出如下：
// this is the start
// this is just a message
// this is the end
// undefined // 立即调用函数的返回值
// this is a msg from callback
// this is a msg from a callback1
```

#### 用 setTimeout 模仿 setInterval

```js
function setIntervalSimulation(cb, m) {
  setTimeout(function(){
    cb();
    setTimeout(cb, m);
  }, m);
}

setIntervalSimulation(function(){
}, 1000);

setInterval(function(){
}, 1000);
```

上面案例中的 `setIntervalSimulation` 总是会在其回调函数执行后延迟 1000ms（至少）再次执行回调函数，从而 模拟 `setInterval` 的效果，
而 `setInterval` 总是 1000ms 执行一次，而不管它的回调函数执行多久。

所以，如果 `setInterval` 的回调函数执行时间比你指定的间隔时间相等或者更长，那么其回调函数会连在一起执行。

请看代码：

```js
var counter = 1;
var initTime = new Date().getTime();
var timer = setIntervalSimulation(function () {
  if (counter === 3) {
    clearInterval(timer);
  }
  if (counter === 1) {
    for (var i = 0; i < 1990000000; i++) {
      // 此循环大约需要 2374 ms > 1000 ms
    }
  }
  console.log("第" + counter++ + "次：" + (new Date().getTime() - initTime) + " ms");
}, 1000);

// Chrome的输入如下：
// 第1次：2007 ms
// 第2次：2013 ms
// 第3次：3008 ms
//
// Node.js的输入如下：
// 第1次：2331 ms
// 第2次：4664 ms
// 第3次：5668 ms

```


可见，Node.js的`setInterval`很可能是用`setTimeout`模拟实现的。


### 实例

#### 下面这段代码执行后会有什么效果？


```js
setTimeout(function alertA(){
  alert('A');
}, 0);
while(true){};
alert('B');
```

这段代码，我们希望可以弹出一个警告框A出来，但是始终没有来，而且，在FireFox中会提示脚本忙，并询问你是否要终止这段脚本的执行，选择终止以后，A倒是弹出来了，但是B却弹不出来了。

因为浏览器多个事件放入队列中执行，事件是没法中断的（如：鼠标响应事件、页面渲染事件、定时器事件等）。
*B*所在的那段脚本被终止了（因为干坏事被浏览器发现了），但是*A*所在的事件逻辑*alertA*已经进入了事件队列，并没有被终止。
*setTimeout*调用之后，这个定时任务已经交代出去了，也就是0s后调用*Timeout*处理函数，但是由于主线程一直在循环，所以事件处理函数*alertA*并没有机会执行。
从这个例子也可以看出，JavaScript的延迟执行并不一定按照你预订的时间来，时间到了，主线程要有空才行。

但是既然这里希望马上执行，为什么把alertA放到setTimeout里呢？原因很简单，因为这里希望把这部分逻辑放到事件队列中去。

如图，JavaScript引擎在逐个执行各类事件的处理函数。

![thread.png](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/syntax/images/thread.png)

*B*所在的那段脚本被终止了，为什么*alertA*还能被执行？


#### sleep


JavaScript是没有*sleep*方法的，如果非要*sleep*，我们只能实现一个*伪sleep*，因为这个循环会不断消耗CPU去比对时间，并不是真正的sleep，而是没有响应地工作：

```js
function sleep(time) {
  var start = Date.now();
  while (Date.now() - start < time) {
  }
}
```


#### 拆分耗时逻辑


很多时候我们需要把耗时的逻辑拆分，腾出时间来给其他逻辑的执行。
下面的代码源自《Timed array processing in JavaScript》这篇文章，作者首先给出一个这样的拆分逻辑执行的框架代码：

```js
function chunk(array, process, context){
    var items = array.concat();
    setTimeout(function(){
        var item = items.shift();
        process.call(context, item);
        if (items.length > 0){
            setTimeout(arguments.callee, 100);
        }
    }, 100);
}
```

但他同时也马上指出了其中的问题，100毫秒的间隔延时太长了，也许25毫秒就够了，但是不能为0，0也可以使得这个执行拆分成多个事件进入队列，但是我们需要给UI的更新渲染等等留一些时间。于是他又改进了一下：

```js
// Copyright 2009 Nicholas C. Zakas. All rights reserved.
// MIT Licensed
function timedChunk(items, process, context, callback){
    var todo = items.concat();
    setTimeout(function(){
        var start = +new Date();
        do {
             process.call(context, todo.shift());
        } while (todo.length > 0 && (+new Date() - start < 50));

        if (todo.length > 0){
            setTimeout(arguments.callee, 25);
        } else {
            callback(items);
        }
    }, 25);
}
```

可以看见，这可以更充分地利用时间，执行的任务放到一个数组中，只要每次chunk内执行的时间不足50毫秒，就继续执行；一旦超过50毫秒，就留给外部事件25毫秒去处理。



## Node.js & Browser

浏览器不是单线程的，它们在内核制控下相互配合以保持同步，一个浏览器至少实现三个常驻线程：

* javascript引擎线程
  javascript引擎是基于事件驱动单线程执行的，JS引擎一直等待着任务队列中任务的到来，然后加以处理，浏览器无论什么时候都只有一个JS线程在运行JS程序。

* GUI渲染线程
  GUI渲染线程负责渲染浏览器界面，当界面需要重绘（Repaint）或由于某种操作引发回流(reflow)时,该线程就会执行。但需要注意GUI渲染线程与JS引擎是互斥的，当JS引擎执行时GUI线程会被挂起，GUI更新会被保存在一个队列中等到JS引擎空闲时立即被执行。

* 浏览器事件触发线程
  事件触发线程，当一个事件被触发时该线程会把事件添加到“任务队列”的队尾，等待JS引擎的处理。
  这些事件可来自JavaScript引擎当前执行的代码块如setTimeOut、也可来自浏览器内核的其他线程如鼠标点击、AJAX异步请求等，但由于JS是单线程执行的，所有这些事件都得排队等待JS引擎处理。
  在Chrome浏览器中，为了防止因一个标签页奔溃而影响整个浏览器，其每个标签页都是一个进程。当然，对于同一域名下的标签页是能够相互通讯的，具体可看 浏览器跨标签通讯。在Chrome设计中存在很多的进程，并利用进程间通讯来完成它们之间的同步，因此这也是Chrome快速的法宝之一。
  对于Ajax的请求也需要特殊线程来执行，当需要发送一个Ajax请求时，浏览器会开辟一个新的线程来执行HTTP的请求，它并不会阻塞JavaScript线程的执行，当HTTP请求状态变更时，相应事件会被作为回调放入到“任务队列”中等待被执行。

看看以下代码：

```js
document.onclick = function(){
  console.log("click")
}
for(var i = 0; i< 100000000; i++){};
```

首先向document注册了一个click事件，然后就执行了一段耗时的for循环，在这段for循环结束前，你可以尝试点击页面。
当耗时操作结束后，console控制台就会输出之前点击事件的”click”语句。
这似乎证明了点击事件（也包括其它各种事件）是由额外单独的线程触发的，事件触发后就会将回调函数放进了“任务队列”的末尾，等待着JavaScript主线程的执行。



## 总结

JavaScript是单线程的，同一时刻只能执行特定的任务。而浏览器是多线程的。
异步任务（各种浏览器事件、定时器等）都是先添加到“任务队列”（定时器则到达其指定参数时）。
当Stack栈（JS主线程）为空时，就会读取Queue队列（任务队列）的第一个任务（队首），然后执行。
JavaScript为了避免复杂性，而实现单线程执行。而今JavaScript却变得越来越不简单了，当然这也是JavaScript迷人的地方。



## 参考

* javascript-the-core [翻译](http://weizhifeng.net/javascript-the-core.html) [原文](http://dmitrysoshnikov.com/ecmascript/javascript-the-core/)
* http://www.raychase.net/1968?replytocom=51795
* http://www.codeceo.com/article/javascript-threaded.html
* http://www.cnblogs.com/yakun/p/3802725.html
* http://www.cnblogs.com/rainman/archive/2008/12/26/1363321.html
* http://ejohn.org/blog/how-javascript-timers-work/
* http://www.zhihu.com/question/20866267
* http://www.zhihu.com/question/31982417
* http://blog.thomasbelin.fr/p/javascript-single-threaded-et-asynchrone/
* https://developer.mozilla.org/en-US/docs/Web/JavaScript/EventLoop
* http://www.ruanyifeng.com/blog/2014/10/event-loop.html
* http://blog.csdn.net/z742182637/article/details/51536140
* http://www.cnblogs.com/wilber2013/p/4909430.html#_nav_0
* https://www.nczonline.net/blog/2013/06/25/eval-isnt-evil-just-misunderstood/
* http://www.cnblogs.com/dolphinX/p/3524977.html
* http://www.kancloud.cn/kancloud/deep-understand-javascript/43686
