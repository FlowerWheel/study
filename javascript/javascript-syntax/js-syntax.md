javascript-syntax
=================
参考：
* javascript-the-core [翻译](http://weizhifeng.net/javascript-the-core.html) [原文](http://dmitrysoshnikov.com/ecmascript/javascript-the-core/)


### 属性类型

#### 数据属性
属性|说明
---|---
`[[Configurable]]` |表示能否通过delete删除属性从而重新定义属性，能否改变属性的特性，或者能否改变把属性改为访问器属性。true|
`[[Enumerable]]`   |表示能否通过for-in循环返回属性。true|
`[[Writable]]`	    |表示能否修改属性值。ture|
`[[Value]]`		    |包含实际值。undefined|

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

#### 访问器属性: `getter` `setter`
属性|说明
---|---
`[[Configurable]]`	|表示能否通过delete删除属性从而重新定义属性，能否改变属性的特性，或者能否改变把属性改为访问器属性。true
`[[Enumerable]]`	|表示能否通过for-in循环返回属性。true
`[[Getter]]`		|取值函数。undefined
`[[Setter]]`		|赋值函数。undefined

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
console.log(book1);			// { _year: 2014, edition: 1, year: [Getter/Setter] }
console.log(book1.year);	// 2014
book.year = 2016;
console.log(book1);			// { _year: 2016, edition: 3, year: [Getter/Setter] }
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

应用：
* 观察者模式
  - 例子[JavaScript实现MVVM监测一个普通对象的变化](http://hcysun.me/2016/04/28/JavaScript%E5%AE%9E%E7%8E%B0MVVM%E4%B9%8B%E6%88%91%E5%B0%B1%E6%98%AF%E6%83%B3%E7%9B%91%E6%B5%8B%E4%B8%80%E4%B8%AA%E6%99%AE%E9%80%9A%E5%AF%B9%E8%B1%A1%E7%9A%84%E5%8F%98%E5%8C%96/)


### ECMAScript5对象保护功能

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


### 数据类型

#### 五种基本类型：
`Undefined`、`Null`、`Boolean`、`Number`、`String`

* `Boolean`、`Number`、`String`。
  
  这三种基本类型平时使用的时候大都使用的是字面量形式，字面量并不是对象，但是当需要的时候，它们也会被转换成对象，也就是会被转换成**基本类型的包装类型**。

* `Undefined`、`Null`。
  
  并不存在`Undefined()`和`Null()`内建函数，只存在`Undefined`和`Null`类型的内建对象`undefined`和`null`，这两个中类型并无**基本类型的包装类型**。
  ECMAScript认为`undefined`是从`null`派生出来的，所以把它们定义为相等的，相同的地方是都可以视为布尔值的false。

#### 引用类型：
`Object`、`Function`、`Array`、`Error`、`Regexp`、`Map`、`Set`...

JavaScript中除了 `null` 和 `undefined` 之外的一切都可以被当做对象！

undefined与null的区别：
* null表示"没有对象"，即该处不应该有值。
  1. 作为函数的参数，表示该函数的参数不是对象。
  2. 作为对象原型链的终点。
* undefined表示"缺少值"，即应该有一个值但是未定义。
  1. 变量被声明了，但没有赋值时，该变量undefined。
  2. 调用函数时，参数没有提供，该参数undefined。
  3. 对象没有赋值的属性，该属性undefined。
  4. 函数没有返回值时，返回undefined。

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

* Number
  
```js
var num = 0;
var numObj = new Number(0);
console.log(num instanceof Object);         // false
console.log(num instanceof Number);         // false
console.log(numObj instanceof Object);      // true
console.log(numObj instanceof Number);      // true
console.log(num === numObj);                // false
console.log(typeof num);                    // number
console.log(typeof numObj);                 // object
console.log(numObj === new Number(0));      // false
console.log(numObj === numObj);             // true
```

* String
  
```js
var str = '';
var strObj = new String('');
console.log(str instanceof Object);         // false
console.log(str instanceof String);         // false
console.log(strObj instanceof Object);      // true
console.log(strObj instanceof String);      // true
console.log(str === strObj);                // false
console.log(typeof str);                    // string
console.log(typeof strObj);                 // object
```

* Boolean
  
```js
var bool = true;
var boolObj = new Boolean(true);
console.log(bool instanceof Object);        // false
console.log(bool instanceof Boolean);       // false
console.log(boolObj instanceof Object);     // true
console.log(boolObj instanceof Boolean);    // true
console.log(bool === boolObj);              // false
console.log(typeof bool);                   // boolean
console.log(typeof boolObj);                // object
```

* Object - 引用类型
  
```js
var obj = {};
var boolObj = new Object({});
console.log(obj instanceof Object);         // true
console.log(boolObj instanceof Object);     // true
console.log(obj === boolObj);               // false
console.log(typeof obj);                    // object
console.log(typeof boolObj);                // object
```


### void

`void UnaryExpression` 按如下流程解释:
* 令`expr`为解释执行`UnaryExpression`的结果。
* 调用 `GetValue(expr)`.
* 返回 `undefined`.

注意：GetValue一定会被调用，即使它的值不会被用到，但是这个表达式可能会有副作用(side-effects)。

为什么要用void？undefined不是保留字，可以重新赋值。采用void方式获取undefined便成了通用准则。

[谈谈Javascript中的void操作符](https://segmentfault.com/a/1190000000474941)


### 对象
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

我们拥有一个这样的结构，两个显式的自身属性和一个隐藏的`__proto__`属性，这个属性是对`Object.prototype`的引用。

![basic-object](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/basic-object.png)

这些`prototype`有什么用？让我们以`原型链`的概念来回答这个问题。


### 原型链（prototype-chain）

* `原型对象`也是简单的对象并且可以拥有它们自己的原型，如果一个原型对象的`原型`是一个非`null`的引用，以此类推，原型对象连成的链，就形成了`原型链`。
* `原型链`是一个用来实现`继承`和`共享`属性的有限长度的`对象链`。
* `原型链`是为了实现代码重用而设计的，在基于类的系统中，这个代码重用风格叫作`继承`。

ECMAScript中没有类的概念，但是代码重用的风格并没有太多不同，ECMAScript通过原型链来实现，即**原型继承(prototype based inheritance)**，这种继承方式叫作**委托继承(delegation based inheritance)**。

ES5标准化了一个实现原型继承的新的可选方法，使用`Object.create`函数：
```js
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

#### 原型链lookup规则：
如果一个`属性`/`方法`在对象自身中无法找到，JS引擎会尝试遍历整个原型链，寻找这个`属性`/`方法`，第一个被查找到的同名`属性`/`方法`会被使用。如果在遍历了整个原型链之后还是没有查找到这个属性的话，返回undefined值。

下一张图展示了对象`a`，`b`，`c`之间的继承关系：

![prototype-chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/prototype-chain.png)

#### `__proto__`
* 如果没有明确为一个对象指定原型，那么它将会使用`__proto__`的默认值`Object.prototype`。
* `Object.prototype`对象自身也有一个`__proto__`属性，值为`null`，这是原型链的终点。 即：`Object.prototype.__proto__ === null`
* The `__proto__` property of `Object.prototype` is an `accessor property` (a getter function and a setter function) that exposes the internal `[[Prototype]]` (either an object or null) of the object through which it is accessed.

项目中建议不要直接使用`__proto__`访问原型，而是使用`Object.getPrototypeOf()、Object.create()`读写原型。

```js
var Shape = function () { };
var proto = {
    say: function () {
        console.log('hello world!');
    }
};
Shape.prototype = proto;
```
```js
var circle = new Shape();
console.log('circle:', circle.__proto__ === Shape.prototype);                      // true
console.log('circle:', Object.getPrototypeOf(circle) === Shape.prototype);         // true
console.log('circle:', typeof circle);                                             // object
console.log('circle:', circle instanceof Shape);                                   // true
console.log('circle:', circle instanceof Object);                                  // true
circle.say();                                                                      // hello world!
```
```js
var rectangle = Object.create(proto);
console.log('ractangle:', rectangle.__proto__ === Shape.prototype);                // true
console.log('ractangle:', Object.getPrototypeOf(rectangle) === Shape.prototype);   // true
console.log('ractangle:', typeof rectangle);                                       // object
console.log('ractangle:', rectangle instanceof Shape);                             // true
console.log('ractangle:', rectangle instanceof Object);                            // true
circle.say();                                                                      // hello world!
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

`typeof`和`instanceof`的目的都是检测变量的类型，区别在于typeof一般是检测的是基本数据类型，instanceof主要检测的是引用类型。

通常情况下对象拥有相同或者相似的状态结构（也就是相同的属性集合），赋以不同的状态值，在这个情况下我们可能需要使用`构造函数`，其以指定的模式来创造对象。


### 构造函数
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
![constructor-proto-chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/constructor-proto-chain.png)

思考一下类的概念，那么构造函数和原型对象合在一起可以当作一个「类」了。

例如：Python的`First-Class、Dynamic-Classes`显然是以同样的`属性`/`方法`处理方案来实现的。从这个角度来说，Python中的类可以看作ECMAScript使用的委托继承的一个语法糖。

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
2. 将构造函数作用域赋给新对象，即this指向了新对象
3. 执行构造函数中的代码
4. 返回新对象的引用

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


### 对象构造

#### 工厂模式
* 按指定模式创建对象的，但是对象类型无法标识。
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

#### 构造函数模式
* 构造函数名字用来标志一个`特定类型`。
* 问题在于：每个方法在每个对象上都要重新创建一次。
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

#### 原型模式
* 每个函数都有一个`prototype`属性，引用另一个对象，这个对象可以实现属性的共享。
* `prototype`是构造函数的一个属性，`prototype`指向的`原型对象`拥有一个`constructor`属性指向构造函数，普通函数有此属性无意义。
* 通过构造函数创建的`对象实例`可以通过`__proto__`访问`原型对象`，但是不能重写，重名的属性将屏蔽原型中的同名属性。
* 在原型中修改属性，会立刻在`对象实例`中反映出来。但是如果重写整个原型对象，那么实例对象将找不到原型中定义的属性。

```js
function PrototypeObject() { }
PrototypeObject.prototype.name = 'PrototypeObject';
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

#### 组合构造函数和原型模式
* 集两者之长默认模式
* 实例属性在构造函数中定义　　
* 共享属性在原型中定义
```js
function ConstructPrototypeObject(name, desc) {
	this.name = name;
	this.desc = desc;
}
ConstructPrototypeObject.prototype.display = 
function () {
	console.log(this.name);
	console.log(this.desc);
};
```

#### 动态原型模式
* 只在第一次调用构造函数时　实例化原型
```js
function ConstructPrototypeObject(name, desc) {
	this.name = name;
	this.desc = desc;
	if (!ConstructPrototypeObject.prototypeInstantiated) {
	    //只在第一次调用构造函数时　实例化原型
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

#### 继承模式（寄生模式）
* 这种方式，可以用来扩展原生对象，在不修改原生对象的前提下，增加方法。
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
```

#### 稳妥构造函数模式
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


### 继承

#### 原型链
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

#### 组合继承
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

#### 原型式继承
* 此方式必须有一个对象作为基础，作为原型。
```js
function object(o) {
	function F() { } // 临时性构造函数
	F.prototype = o;
	return new F();
}
Object.create();    //此方法即为原型式继承
```

#### 寄生式继承
```js
function createAnother(original) {          // 工厂
	var clone = Object.create(original);      // 封装了原型式继承
	clone.sayHi = function () {
		console.log('Hi');
	};
	return clone;
}
```

#### 寄生组合式继承
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

### `bind`、`call`、`apply`是做什么的？

TODO: 要改，举例说明使用方法。
从设计者的角度去考虑各个点，call、apply、bind 存在的原因。
C++中类的方法是隐式传递了this指针，python的方法都是显示的指定self，而js也同样需要this。
但是this在js中是作为一个执行环境上下文的概念存在，并且对于任意一个函数（一级公民），它有语法逻辑上的上下文，但是它的上下文又可以是人为绑定的，
这三个函数就可以用来完成绑定工作。任何一个函数也是在一个上下文对象上进行工作。上下文是一个this对象。
这是一种松散的绑定关系，随时可以根据需要来绑定。因此就可以自由的将其他模块上的属性方法，绑定到自己身上，但是要避免名字冲突。

下图是一个Javascript Prototype Chain关系图：

[查看原图](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/javascript-prototype.png)
![Javascript Prototype Chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/javascript-prototype.png)


现在，在我们知道了对象的基础之后，让我们看看运行时程序的执行（runtime program execution）在ECMAScript中是如何实现的。


### 执行上下文堆栈

* EC(执行环境或者执行上下文，Execution Context)
* ECS(执行环境栈Execution Context Stack)
* VO(变量对象，Variable Object)
* AO(活动对象，Active Object)
* Scope Chain(作用域链)和`[[scope]]`属性

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

所有ECMAScript程序的运行时可以用执行上下文栈（ECS）来表示，栈顶是当前活动的上下文：

![ec-stack](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/ec-stack.png)

当程序开始的时候它会进入全局执行上下文，此上下文位于栈顶并且是栈中的第一个元素。然后全局代码进行一些初始化，创建需要的对象和函数。

在全局上下文的执行过程中，它的代码会触发其他函数，进入它们自己的执行上下文，向栈中push新的元素，以此类推。

当初始化完成之后，运行时系统（runtime system）就会等待一些事件，这些事件将会触发一些函数，从而进入新的执行上下文中。

在下个图中，拥有一些函数上下文EC1和全局上下文Global EC，当EC1进入和退出全局上下文的时候下面的栈将会发生变化：

![ec-stack-changes](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/ec-stack-changes.png)

这就是ECMAScript的运行时系统如何真正地管理代码执行的。

栈中的每个执行上下文都可以用一个对象来表示。

让我们来看看它的结构以及一个上下文到底需要什么状态（什么属性）来执行它的代码。


### 执行上下文

一个执行上下文可以抽象的表示为一个简单的对象。每一个执行上下文拥有一些属性（可以叫作上下文状态）用来跟踪和它相关的代码的执行过程。在下图中展示了一个上下文的结构：

![execution-context](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/execution-context.png)

除了这三个必需的属性`变量对象`、`this`、`作用域链`之外，执行上下文可以拥有其他附加的状态，这取决于实现。

让我们详细看看上下文中的这些重要的属性。

#### 变量对象（variable object）

`变量对象`是与`执行上下文`相关的`数据作用域`。它是一个与上下文相关的特殊对象，其中存储了在上下文中定义的`变量`和`函数声明`。

> 函数表达式（与函数声明相对）不包含在变量对象之中。

变量对象是一个抽象概念。对于不同的上下文类型，在物理上，是使用不同的对象。在全局上下文中变量对象就是全局对象本身，这就是为什么我们可以通过`全局对象的属性名`来关联`全局变量`。

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

![variable-object](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/variable-object.png)

函数baz是一个函数表达式，没有被包含在变量对象之中。这就是为什么当我们想要在函数自身之外访问它的时候会出现ReferenceError。

注意，与其他语言（比如C/C++）相比，在ECMAScript中只有函数可以创建一个新的作用域。在函数作用域中所定义的变量和内部函数在函数外边是不能直接访问到的，而且并不会污染全局变量对象。

使用eval我们也会进入一个新的执行上下文。无论如何，eval使用全局的变量对象或者使用caller（比如eval被调用时所在的函数）的变量对象。

那么函数和它的变量对象是怎么样的？在函数上下文中，变量对象是以`活动对象`来表示的。

#### 活动对象（activation object）

当一个函数被`caller`调用，一个特殊的对象，叫作`活动对象`（activation object）将会被创建。这个对象中包含形参和那个特殊的`arguments`对象（是对形参的一个映射，但是值是通过索引来获取）。活动对象之后会做为函数上下文的变量对象来使用。

换句话说，函数的变量对象也是一个同样简单的变量对象，但是除了变量和函数声明之外，它还存储了`形参`和`arguments`对象，并叫作活动对象。

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

![activation-object](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/activation-object.png)

并且函数表达式baz还是没有被包含在`变量/活动对象`中。

关于这个主题所有细节方面（像变量和函数声明的提升问题（hoisting））的完整描述可以在同名的章节第二章 变量对象中找到。

注意，在ES5中`变量对象`和`活动对象`被并入了`词法环境模型`（lexical environments model），详细的描述可以在对应的章节找到。

众所周知，在ECMAScript中我们可以使用内部函数，然后在这些内部函数我们可以引用父函数的变量或者全局上下文中的变量。当我们把变量对象命名为上下文的作用域对象，与上面讨论的原型链相似，这里有一个叫作`作用域链`的东西。

#### 作用域链(scope chain)

作用域链是一个对象列表，上下文代码中出现的标识符在这个列表中进行查找。

这个规则还是与原型链同样简单以及相似：如果一个变量在函数自身的作用域（变量/活动对象）中没有找到，那么将会查找它父函数（外层函数）的变量对象，以此类推。

就上下文而言，标识符指的是：变量名称，函数声明，形参，等等。当一个函数在其代码中引用一个不是局部变量（或者局部函数或者一个形参）的标识符，那么这个标识符就叫作自由变量。搜索这些自由变量(free variables)正好就要用到作用域链。

在通常情况下，作用域链是一个包含所有父（函数）变量对象__加上（在作用域链头部的）函数自身变量/活动对象的一个列表。但是，这个作用域链也可以包含任何其他对象，比如，在上下文执行过程中动态加入到作用域链中的对象－像with对象或者特殊的catch从句（catch-clauses）对象。

当解析（查找）一个标识符的时候，会从作用域链中的活动对象开始查找，然后（如果这个标识符在函数自身的活动对象中没有被查找到）向作用域链的上一层查找－重复这个过程，就和原型链一样。

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

我们可以假设通过隐式的`__parent__`属性来和`作用域链对象`进行关联，这个属性指向作用域链中的下一个对象。

这个方案可能在真实的Rhino代码中经过了测试，并且这个技术很明确得被用于ES5的词法环境中（在那里被叫作outer连接）。

作用域链的另一个表现方式可以是一个简单的数组。利用`__parent__`概念，我们可以用下面的图来表现上面的例子（并且父变量对象存储在函数的`[[Scope]]`属性中）：

![scope-chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/scope-chain.png)

在代码执行过程中，作用域链可以通过使用with语句和catch从句对象来增强。并且由于这些对象是简单的对象，它们可以拥有原型（和原型链）。

这个事实导致作用域链查找变为两个维度：（1）首先是作用域链连接，然后（2）在每个作用域链连接上－深入作用域链连接的原型链（如果此连接拥有原型）。

对于这个例子：

```js
Object.prototype.x = 10;
var w = 20;
var y = 30;
// in SpiderMonkey global object
// i.e. variable object of the global
// context inherits from "Object.prototype",
// so we may refer "not defined global
// variable x", which is found in
// the prototype chain
console.log(x); // 10
(function foo() {
  // "foo" local variables
  var w = 40;
  var x = 100;
  // "x" is found in the
  // "Object.prototype", because
  // {z: 50} inherits from it
  with ({z: 50}) {
    console.log(w, x, y , z); // 40, 10, 30, 50
  }
  // after "with" object is removed
  // from the scope chain, "x" is
  // again found in the AO of "foo" context;
  // variable "w" is also local
  console.log(x, w); // 100, 40
  // and that's how we may refer
  // shadowed global "w" variable in
  // the browser host environment
  console.log(window.w); // 20
})();
```

我们可以给出如下的结构（确切的说，在我们查找`__parent__`连接之前，首先查找`__proto__`链）：

![scope-chain-with](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/scope-chain-with.png)

注意，不是在所有的实现中全局对象都是继承自Object.prototype。上图中描述的行为（从全局上下文中引用「未定义」的变量x）可以在诸如SpiderMonkey引擎中进行测试。

由于所有父变量对象都存在，所以在内部函数中获取父函数中的数据没有什么特别－我们就是遍历作用域链去解析（搜寻）需要的变量。

就像我们上边提及的，在一个上下文结束之后，它所有的状态和它自身都会被销毁，在同一时间父函数可能会返回一个内部函数，而且，这个返回的函数之后可能在另一个上下文中被调用。

如果自由变量的上下文已经「消失」了，那么这样的调用将会发生什么？通常来说，有一个概念可以帮助我们解决这个问题，叫作（词法）闭包，其在ECMAScript中就是和作用域链的概念紧密相关的。

然后我们移动到下个部分，考虑一下执行上下文的最后一个属性。这就是关于this值的概念。

### This

this是一个与执行上下文相关的特殊对象。因此，它可以叫作上下文对象（也就是用来指明执行上下文是在哪个上下文中被触发的对象）。
任何对象都可以做为上下文中的this的值。我想再一次澄清，在一些对ECMAScript执行上下文和部分this的描述中的所产生误解。this经常被错误的描述成是变量对象的一个属性。这类错误存在于比如像这本书中（即使如此，这本书的相关章节还是十分不错的）。再重复一次：

this是执行上下文的一个属性，而不是变量对象的一个属性
这个特性非常重要，因为与变量相反，this从不会参与到标识符解析过程。换句话说，在代码中当访问this的时候，它的值是直接从执行上下文中获取的，并不需要任何作用域链查找。this的值只在进入上下文的时候进行一次确定。

顺便说一下，与ECMAScript相反，比如，Python的方法都会拥有一个被当作简单变量的self参数，这个变量的值在各个方法中是相同的的并且在执行过程中可以被更改成其他值。在ECMAScript中，给this赋一个新值是不可能的，因为，再重复一遍，它不是一个变量并且不存在于变量对象中。

在全局上下文中，this就等于全局对象本身（这意味着，这里的this等于变量对象）：

```js
var x = 10;

console.log(
  x, // 10
  this.x, // 10
  window.x // 10
);
```

在函数上下文的情况下，对函数的每次调用，其中的this值可能是不同的。这个this值是通过函数调用表达式（也就是函数被调用的方式）的形式由caller所提供的。举个例子，下面的函数foo是一个callee，在全局上下文中被调用，此上下文为caller。让我们通过例子看一下，对于一个代码相同的函数，this值是如何在不同的调用中（函数触发的不同方式），由caller给出不同的结果的：

```js
// the code of the "foo" function
// never changes, but the "this" value
// differs in every activation

function foo() {
  alert(this);
}

// caller activates "foo" (callee) and
// provides "this" for the callee

foo(); // global object
foo.prototype.constructor(); // foo.prototype

var bar = {
  baz: foo
};

bar.baz(); // bar

(bar.baz)(); // also bar
(bar.baz = bar.baz)();  // but here is global object
(bar.baz, bar.baz)();   // also global object
(false || bar.baz)();   // also global object

var otherFoo = bar.baz;
otherFoo(); // again global object
```

为了深入理解this为什么（并且更本质一些－如何）在每个函数调用中可能会发生变化，你可以阅读第三章 This。在那里，上面所提到的情况都会有详细的讨论。

http://www.kancloud.cn/kancloud/deep-understand-javascript/43686


### 闭包

在ECMAScript中，函数是一级（first-class）对象。这个术语意味着函数可以做为参数传递给其他函数（「函数类型参数」（funargs，是"functional arguments"的简称））。接收「函数类型参数」的函数叫作`高阶函数`或者，贴近数学一些，叫作高阶操作符。

同样函数也可以从其他函数中返回，返回其他函数的函数叫作以函数为值（function valued）的函数（或者叫作拥有函数类值的函数（functions with functional value））。

这有两个在概念上与「函数类型参数（funargs）」和「函数类型值（functional　values）」相关的问题。

并且这两个子问题在"Funarg problem"（或者叫作"functional argument"问题）中很普遍。

为了解决整个"funarg problem"，闭包（closure）的概念被创造了出来。

我们详细的描述一下这两个子问题（我们将会看到这两个问题在ECMAScript中都是使用图中所提到的函数的`[[Scope]]`属性来解决的）。

「funarg问题」的第一个子问题是「向上funarg问题」（upward funarg problem）。它会在当一个函数从另一个函数向上返回（到外层）并且使用上面所提到的自由变量的时候出现。

为了在即使父函数上下文结束的情况下也能访问其中的变量，内部函数在被创建的时候会在它的`[[Scope]]`属性中保存父函数的作用域链。

所以当函数被调用的时候，它上下文的作用域链会被格式化成活动对象与`[[Scope]]`属性的和（实际上就是我们刚刚在上图中所看到的）：

Scope chain = Activation object + `[[Scope]]`

再次注意这个关键点－确切的说在创建时刻－函数会保存父函数的作用域链，因为确切的说这个保存下来的作用域链将会在未来的函数调用时用来查找变量。

```js
function foo() {
  var x = 10;
  return function bar() {
    console.log(x);
  };
}
// "foo" returns also a function
// and this returned function uses
// free variable "x"
var returnedFunction = foo();
// global variable "x"
var x = 20;
// execution of the returned function
returnedFunction(); // 10, but not 20
```

这个类型的作用域叫作静态（或者词法）作用域。我们看到变量x在返回的bar函数的`[[Scope]]`属性中被找到。通常来说，也存在动态作用域，那么上面例子中的变量x将会被解析成20，而不是10。但是，动态作用域在ECMAScript中没有被使用。

「funarg问题」的第二个部分是「向下funarg问题」。这种情况下可能会存在一个父上下文，但是在解析标识符的时候可能会模糊不清。

问题是：标识符该使用哪个作用域的值－以静态的方式存储在函数创建时刻的还是在执行过程中以动态方式生成的，比如caller的作用域？为了避免这种模棱两可的情况并形成闭包，静态作用域被采用：

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
  // there is no ambiguity,
  // because we use global "x",
  // which was statically saved in
  // [[Scope]] of the "foo" function,
  // but not the "x" of the caller's scope,
  // which activates the "funArg"
  funArg(); // 10, but not 20
})(foo); // pass "down" foo as a "funarg"
```

我们可以断定静态作用域是一门语言拥有闭包的必需条件。

但是，一些语言可能会同时提供动态和静态作用域，允许程序员做选择－什么应该包含（closure）在内和什么不应包含在内。

由于在ECMAScript中只使用了静态作用域（比如我们对于funarg问题的两个子问题都有解决方案），所以结论是：ECMAScript完全支持闭包，技术上是通过函数的`[[Scope]]`属性实现的。

现在我们可以给闭包下一个准确的定义：

闭包是一个代码块（在ECMAScript是一个函数）和以`静态方式`/`词法方式`进行存储的所有父作用域的一个集合体。所以，通过这些存储的作用域，函数可以很容易的找到自由变量。

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

![shared-scope](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/shared-scope.png)

确切来说这个特性在循环中创建多个函数的时候会使人非常困惑。在创建的函数中使用循环计数器的时候，一些程序员经常会得到非预期的结果，所有函数中的计数器都是同样的值。

现在是到了该揭开谜底的时候了－因为所有这些函数拥有同一个`[[Scope]]`，这个属性中的循环计数器的值是最后一次所赋的值。

```js
var data = [];
for (var k = 0; k < 3; k++) {
  data[k] = function () {
    alert(k);
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
      alert(x);
    };
  })(k); // pass "k" value
}
// now it is correct
data[0](); // 0
data[1](); // 1
data[2](); // 2
```

### 闭包

有权访问另一个函数作用域中的变量的函数

当函数被调用时 会创建一个 执行环境 和相应 作用域链  然后使用arguments和其他命名函数初始化 活动对象

c/c++: 函数无法嵌套定义，可以传递函数指针
java c#:
python ruby
go swift
javascript typescript coffeescript ...

```js
'use strict';
var classA = function () {
  this.prop1 = 1;
};

classA.prototype.func1 = function () {
  var that = this,
      var1 = 2;

  function f() {
    return function () {
      console.log(var1);
    }.apply(that);
  }

  f();
};

var objA = new ClassA();
objA.func1();
```

有时候一个方法定义的地方和使用的地方会相隔十万八千里，那方法执行时，它能访问哪些变量，不能访问哪些变量，这个怎么判断呢？这个就是我们这次需要分析的问题—词法作用域

词法作用域：变量的作用域是在定义时决定而不是执行时决定，也就是说词法作用域取决于源码，通过静态分析就能确定，因此词法作用域也叫做静态作用域。 with和eval除外，所以只能说JS的作用域机制非常接近词法作用域（Lexical scope）。


### 函数表达式


### 执行过程

#### 执行顺序
 * 编译型语言，编译步骤分为：词法分析、语法分析、语义检查、代码优化和字节生成。
 * 解释型语言，通过词法分析和语法分析得到语法分析树后，就可以开始解释执行了。这里是一个简单原始的关于解析过程的原理，仅作为参考，详细的解析过程（各种JS引擎还有不同）还需要更深一步的研究

 JavaScript执行过程，如果一个文档流中包含多个script代码段（用script标签分隔的js代码或引入的js文件），它们的运行顺序是：

 * 阶段一：解析
  * 步骤1. 载入第一个代码段（js执行引擎并非一行一行地执行程序，而是一段一段地分析执行的）。
  * 步骤2. 做词法分析->[词法作用域] 和 语法分析->[语法分析树]，有错则报语法错误(Syntax Error)（解析时错误，比如括号不匹配等），并跳转到步骤5。
  * 步骤3. 对[var]变量和[function]定义做`预解析`（永远不会报错的，因为只解析正确的声明）。
 * 阶段二：执行
  * 步骤4. 执行代码段，有错则报错（运行时错误，比如变量未定义）。
 * 步骤5. 如果还有下一个代码段，则读入下一个代码段，重复步骤2。
  * 步骤6. 结束

 * JS代码是一段段执行的。也就是以函数内部的活动代码为单位，一段段活动代码执行。
 * 实例化就是调用对象（Call Object）的过程，上面我们一直说这个分析很像类结构。
 * 这次就真的是把这个像类的词法分析出来的结果进行伪类的实例化了。
 * 实例化的同时，这个调用对象的一个属性被初始化成一个名叫 arguments 的属性，
 * 它引用了这个函数的 Arguments 对象，Arguments 对象是函数的实际参数。

#### 关键步骤
 上面的过程，我们主要是分成两个阶段
 * 解析：通过语法分析和预解析构造合法的语法分析树。
 * 执行：执行具体的某个函数，JS引擎在执行每个函数实例时，都会创建一个执行环境（ExecutionContext）和活动对象（ActiveObject）（它们属于宿主对象，与函数实例的生命周期保持一致）

#### 关键概念
 * 语法分析树（SyntaxTree）
  * 可以直观地表示出这段代码的相关信息，具体的实现就是JS引擎创建了一些表，
  * 用来记录每个方法的 内部变量集（variables）、内嵌函数集（functions）和作用域（scope）等

 * 执行环境（ExecutionContext）
  * 可理解为一个记录当前执行的方法【外部描述信息】的对象,
  * 记录所执行方法的类型，名称，参数和活动对象（activeObject）

 * 活动对象（activeObject）
  * 可理解为一个记录当前执行的方法【内部执行信息】的对象,
  * 记录 内部变量集（variables）、内嵌函数集（functions）、实参（arguments）、作用域链（scopeChain）等执行所需信息，
  * 其中 内部变量集（variables）、内嵌函数集（functions）是直接从第一步建立的语法分析树复制过来的.
  * 方法开始执行，活动对象里的内部变量集全部被重置为 undefined, 创建形参（parameters）和实参（arguments）对象，同名的实参，形参和变量之间是【引用】关系, 执行方法内的赋值语句，这才会对变量集中的变量进行赋值处理
  * 变量查找规则是首先在当前执行环境的 ActiveObject 中寻找，没找到，则顺着执行环境中属性 ScopeChain 指向的 ActiveObject 中寻找，一直到 Global Object
  * 方法执行完成后，内部变量值不会被重置，至于变量什么时候被销毁, 方法内变量的生存周期取决于方法实例是否存在活动引用，如没有就销毁活动对象

 * 词法作用域
  * 变量的作用域是在定义时决定而不是执行时决定，也就是说词法作用域取决于源码，通过静态分析就能确定，因此词法作用域也叫做静态作用域。
  * with和eval除外，所以只能说JS的作用域机制非常接近词法作用域（Lexical scope）

 * 作用域链
  * 词法作用域的实现机制就是作用域链（scopeChain）。
  * 作用域链是一套按名称查找（Name Lookup）的机制，
  * 首先在当前执行环境的 ActiveObject 中寻找，没找到，
  * 则顺着作用域链到父 ActiveObject 中寻找，一直找到全局调用对象（Global Object）

 * 闭包
  * 闭包是一个拥有许多变量和绑定了这些变量的环境的表达式（通常是一个函数），因而这些变量也是该表达式的一部分。
  * 保护函数内的变量安全。通过保护变量的安全实现JS私有属性和 私有方法（不能被外部访问）.
  * 在内存中维持一个变量。
  * 闭包就是将函数内部和函数外部连接起来的一座桥梁。让外部环境有接口访问内部变量。
  * 闭包函数可以访问所保持的作用域链上的外部环境。


### javascript词法分析

lexical-analyzer  Lexer  Tokenizer

词法分析主要分为3步：
 * 第1步：分析形参
 * 第2步：分析变量声明
 * 第3步：分析函数声明

http://blog.csdn.net/guixuecheng/article/details/43670323

JavaScript的每个函数function都有自己的作用域，使用Active Object（简称AO）活动对象来保存，在相互嵌套的函数中形成了作用域链，如图：
作用域链就是从里到外的AO链变量的寻找：

函数fn3中使用的变量，如在fn3作用域内寻找不到，则往外层fn2作用域寻找，以此类推，直到全局对象window

#### 1、解析模拟
估计，看到这儿，大家还是很朦胧吧，什么是语法分析树，语法分析树到底长什么样子，作用域链又怎么实现的，活动对象又有什么内容等等，还是不是太清晰，
下面我们就通过一段实际的代码来模拟整个解析过程，我们就把语法分析树，活动对象实实在在的创建出来，理解作用域，作用域链的到底是怎么实现的

模拟代码
```js
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
```

#### 2、语法分析树
 上面的代码很简单，就是先定义了一些全局变量和全局方法，接着在方法内再定义局部变量和局部方法，现在JS解释器读入这段代码开始解析，
 前面提到 JS 引擎会先通过语法分析和预解析得到语法分析树，至于语法分析树长什么样儿，都有些什么信息，下面我们以一种简单的结构：
 一个 JS 对象(为了清晰表示个各种对象间的引用关系，这里的只是伪对象表示，可能无法运行)来描述语法分析树
（这是我们比较熟悉的，实际结构我们不去深究，肯定复杂得多，这里是为了帮助理解解析过程而特意简化）

模拟建立一棵语法分析树，存储function内的变量和方法
```js
var SyntaxTree = {
  // 全局对象在语法分析树中的表示
  window: {
    variables: {
      i: {value: 1},
      j: {value: 2},
      k: {value: 3}
    },
    functions: {
      a: this.a
    }
  },
  a: {
    variables: {
      x: 'undefined'
    },
    functions: {
      b: this.b
    },
    scope    : this.window
  },
  b: {
    variables: {
      y: 'undefined'
    },
    functions: {
      c: this.c,
      d: this.d
    },
    scope    : this.a
  },
  c: {
    variables: {
      z: 'undefined'
    },
    functions: {},
    scope    : this.b
  },
  d: {
    variables: {},
    functions: {},
    scope    : {
      myname: d,
      scope : this.b
    }
  }
};
```

上面就是关于语法分析树的一个简单表示，正如我们前面分析的，语法分析树主要记录了每个 function 中的变量集（variables），方法集（functions）和作用域（scope）

#### 3、执行环境
```js
var ExecutionContext = {
  window: {
    type: 'global',
    name: 'global',
    body: ActiveObject.window
  },
  a: {
    type      : 'function',
    name      : 'a',
    body      : ActiveObject.a,
    scopeChain: this.window.body
  },
  b: {
    type      : 'function',
    name      : 'b',
    body      : ActiveObject.b,
    scopeChain: this.a.body
  },
  c: {
    type      : 'function',
    name      : 'c',
    body      : ActiveObject.c,
    scopeChain: this.b.body
  },
  d: {
    type      : 'function',
    name      : 'd',
    body      : ActiveObject.d,
    scopeChain: this.b.body
  }
};
```

上面每一个方法的执行环境都存储了相应方法的类型（function）、方法名称（funcName）、活动对象（ActiveObject）、作用域链（scopeChain）等信息。

其关键点如下：
* body属性，直接指向当前方法的活动对象
* scopeChain属性，作用域链，它是一个链表结构，根据语法分析树中当前方法对应的scope属性，它指向scope对应的方法的活动对象（ActivceObject），变量查找就是跟着这条链条查找的活动对象

#### 4、活动对象：函数执行时创建的活动对象列表
```js
var ActiveObject = {
  window: {
    variables: {
      i: {value: 1},
      j: {value: 2},
      k: {value: 3}
    },
    functions: {
      a: this.a
    }
  },
  a: {
    variables : {
      x: {value: 4}
    },
    functions : {
      b: SyntaxTree.b
    },
    parameters: {
      o: {value: 10},
      p: {value: 20},
      x: this.variables.x,
      q: 'undefined'
    },
    arguments : [this.parameters.o, this.parameters.p, this.parameters.x]
  },
  b: {
    variables : {
      y: {value: 5}
    },
    functions : {
      c: SyntaxTree.c,
      d: SyntaxTree.d
    },
    parameters: {
      r: {value: 40},
      s: {value: 50}
    },
    arguments : [this.parameters.r, this.parameters.s]
  },
  c: {
    variables : {
      z: {value: 6}
    },
    functions : {},
    parameters: {
      u: {value: 70}
    },
    arguments : [this.parameters.u]
  },
  d: {
    variables : {},
    functions : {},
    parameters: {},
    arguments : []
  }
};
```


### Javascript线程模型

下面这段代码执行后会有什么效果？
```js
setTimeout(function alertA(){
  alert('a');
}, 0);
while(true){};
alert('b');
```

这段代码，我们希望可以弹出一个警告框a出来，但是始终没有来；
而且，在FireFox中会提示脚本忙，并询问你是否要终止这段脚本的执行，选择终止以后，a倒是弹出来了，但是b却弹不出来了。

因为浏览器多个事件放入队列中执行，事件（如：鼠标响应事件、页面渲染事件、setTimeout定义的事件等）执行的过程当中，是没法中断的。
b所在的那段脚本被终止了（因为干坏事被浏览器发现了），但是a所在的那段setTimeout事件逻辑已经进入了事件队列，并没有被终止。
setTimeout调用之后，这个定时任务已经交代出去了，也就是0s后调用*Timeout*处理函数，但是主线程一直在死循环，所以事件处理函数alertA并没有机会执行。
从这个例子也可以看出，JavaScript的延迟执行并不准确，不一定按照你预订的时间来，时间到了，主线程要有空才行。

但是话说回来，既然这里希望马上执行，为什么要使用setTimeout方法呢？

原因很简单，因为这里我希望把这个弹框的逻辑放到事件队列中去。

如图，JavaScript引擎在逐个执行各类事件的处理函数。

![thread.png](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/thread.png)


#### 为什么要设计成单线程的?

其实javascript核心语言没有包含任何线程机制的，还有客户端的javascript也是没有明确定义线程机制。
大部分语言都没有在语言层面直接定义线程的，线程都是作为代码库提供给开发者调用，所以也并不是因为javascript无法实现多线程，Node.js就有可以支持线程的库。
但是javascript还是严格按照*单线程*的模型去执行代码。为什么？

网上很多声音都说这和它的历史有关系，但是，其实有一个更重要的原因——死锁。多线程的GUI框架特别容易死锁。
[《Multithreaded toolkits: A failed dream?》](https://community.oracle.com/blogs/kgh/2004/10/19/multithreaded-toolkits-failed-dream)描述了其中的缘由，
大致是说GUI的行为大多都是从更抽象的顶部一层一层调用到操作系统级别，而事件则是反过来，从下向上冒泡，
结果就是两个方向相反的行为在碰头，给资源加锁的时候一个正序，一个逆序，极其容易出现互相等待而饿死的情况，而这种情况下要解决这一问题无异于“fight back an oceanic tidal force”——推荐阅读。
AWT最初其实就是想设计成多线程的，但是使用者非常容易引起死锁和竞争，最后Swing还是做成了单线程的。
但凡这种*EventLoop*+*单线程*执行的模式，我们还可以找到很多，比如JDK的GUI线程模型，主线程就是一个“主事件循环”，还有Mac系统的Cocoa等等，都是这样的模式。

#### sleep?

JavaScript是没有sleep方法的，如果非要sleep，我们只能实现一个没有意义的伪sleep，因为这个循环会不断消耗CPU去比对时间，并不是真正的sleep，而是没有响应地工作： 
```js
function sleep(time) {
  var start = Date.now();
  while (Date.now() - start < time) {
  }
}
```

#### 拆分耗时逻辑

很多时候我们需要把耗时的逻辑拆分，腾出时间来给其他逻辑的执行：下面的代码源自《Timed array processing in JavaScript》这篇文章，作者首先给出一个这样的拆分逻辑执行的框架代码：
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
//Copyright 2009 Nicholas C. Zakas. All rights reserved.
//MIT Licensed
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

#### Web Worker

本质上说，web worker 是运行在后台的 JavaScript，不会影响页面的性能。
当在 HTML 页面中执行脚本时，页面的状态是不可响应的，直到脚本已完成。
Web worker 是运行在后台的 JavaScript，也就是另外一个线程中，独立于其他脚本，不会影响页面的性能。
这可以看做是HTML5尝试为单线程JavaScript弊端做的改进。

以下是线程间通信：

```js
var worker = new Worker('w.js');
worker.postMessage('hello world'); //发消息给工作线程
worker.onmessage = function (event) { }
```

```js
onmessage =function (evt){
  postMessage(evt.data); // 发消息给主线程
}
```

#### 链式调用

```js
runner.push(function() {}, 100)
      .push(function() {}, 200)
      .push(function() {}, 200)
      .run();
```

### 细说JavaScript单线程的一些事

#### 首先，说下为什么 JavaScript 是单线程？

总所周知，JavaScript是以单线程的方式运行的，说到线程就自然联想到进程，那它们有什么联系呢？

进程和线程都是操作系统的概念。
进程是应用程序的执行实例，每一个进程都是由私有的虚拟地址空间、代码、数据和其它系统资源所组成；进程在运行过程中能够申请创建和使用系统资源（如独立的内存区域等），这些资源也会随着进程的终止而被销毁。
而线程则是进程内的一个独立执行单元，在不同的线程之间是可以共享进程资源的，所以在多线程的情况下，需要特别注意对临界资源的访问控制。
在系统创建进程之后就开始启动执行进程的主线程，而进程的生命周期和这个主线程的生命周期一致，主线程的退出也就意味着进程的终止和销毁。
主线程是由系统进程所创建的，同时用户也可以自主创建其它线程，这一系列的线程都会并发地运行于同一个进程中。
显然，在多线程操作下可以实现应用的并行处理，从而以更高的CPU利用率提高整个应用程序的性能和吞吐量。
特别是现在很多语言都支持多核并行处理技术，然而JavaScript却以单线程执行，为什么呢？

其实这与它的用途有关。
作为浏览器脚本语言，JavaScript的主要用途是与用户互动，以及操作DOM。
若以多线程的方式操作这些DOM，则可能出现操作的冲突。
假设有两个线程同时操作一个DOM元素，线程1要求浏览器删除DOM，而线程2却要求修改DOM样式，这时浏览器就无法决定采用哪个线程的操作。
当然，我们可以为浏览器引入“锁”的机制来解决这些冲突，但这会大大提高复杂性，所以 JavaScript 从诞生开始就选择了单线程执行。

另外，因为 JavaScript 是单线程的，在某一时刻内只能执行特定的一个任务，并且会阻塞其它任务执行。
那么对于类似I/O等耗时的任务，就没必要等待他们执行完后才继续后面的操作。
在这些任务完成前，JavaScript完全可以往下执行其他操作，当这些耗时的任务完成后则以回调的方式执行相应处理。
这些就是JavaScript与生俱来的特性：异步与回调。

当然对于不可避免的耗时操作（如：繁重的运算，多重循环），HTML5提出了Web Worker，它会在当前JavaScript的执行主线程中利用Worker类新开辟一个额外的线程来加载和运行特定的JavaScript文件，
这个新的线程和JavaScript的主线程之间并不会互相影响和阻塞执行，而且在Web Worker中提供了这个新线程和JavaScript主线程之间数据交换的接口：postMessage和onMessage事件。
但在HTML5 Web Worker中是不能操作DOM的，任何需要操作DOM的任务都需要委托给JavaScript主线程来执行，所以虽然引入HTML5 Web Worker，但仍然没有改线JavaScript单线程的本质。

#### 并发模式与EventLoop

JavaScript 有个基于“EventLoop”并发的模型。

啊，并发？不是说 JavaScript是单线程吗？ 没错，的确是单线程，但是并发与并行是有区别的。前者是逻辑上的同时发生，而后者是物理上的同时发生。所以，单核处理器也能实现并发。

并发和并行的区别就是一个处理器同时处理多个任务和多个处理器或者是多核的处理器同时处理多个不同的任务。

前者是逻辑上的同时发生（simultaneous），而后者是物理上的同时发生．

来个比喻：并发和并行的区别就是一个人同时吃三个馒头和三个人同时吃三个馒头。

![并发与并行](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/并发与并行.jpg)

并行大家都好理解，而所谓“并发”是指两个或两个以上的事件在同一时间间隔中发生。如上图的第一个表，由于计算机系统只有一个CPU，故ABC三个程序从“微观”上是交替使用CPU，但交替时间很短，用户察觉不到，形成了“宏观”意义上的并发操作。

![stack-heap-queue](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/stack-heap-queue.png)

#### Stack（栈）
这里放着JavaScript正在执行的任务，每个任务被称为帧（stack of frames）。

```js
function f(b){
  var a = 12;
  return a + b + 35;
}
function g(x){
  var m = 4;
  return f(m * x);
}
g(21);
```

上述代码调用 g 时，创建栈的第一帧，该帧包含了 g 的参数和局部变量。
当 g 调用 f 时，第二帧就会被创建，并且置于第一帧之上，当然，该帧也包含了 f 的参数和局部变量。
当 f 返回时，其对应的帧就会出栈。
同理，当 g 返回时，栈就为空了（栈的特定就是后进先出 Last-in first-out (LIFO)）。

#### Heap（堆）

一个用来表示内存中一大片非结构化区域的名字，对象都被分配在这。

#### Queue（队列）

一个 JavaScript runtime 包含了一个任务队列，该队列是由一系列待处理的任务组成。
而每个任务都有相对应的函数，当栈为空时，就会从任务队列中取出一个任务，并处理之。
该处理会调用与该任务相关联的一系列函数（因此会创建一个初始栈帧）。
当该任务处理完毕后，栈就会再次为空。（Queue的特点是先进先出 First-in First-out (FIFO)）。

为了方便描述与理解，作出以下约定：

* Stack栈为主线程
* Queue队列为任务队列（等待调度到主线程执行）

OK，上述知识点帮助我们理清了一个 JavaScript runtime 的相关概念，这有助于接下来的分析。

#### EventLoop

之所以被称为Event loop，是因为它以以下类似方式实现：

```js
while(queue.waitForMessage()){
  queue.processNextMessage();
}
```

正如上述所说，“任务队列”是一个事件的队列。
如果I/O设备完成任务或用户触发事件，那么相关事件处理函数就会进入“任务队列”，当主线程空闲时，就会调度“任务队列”里第一个待处理任务。
当然，对于定时器，当到达其指定时间时，才会把相应任务插到“任务队列”尾部。

#### 执行至完成

每当某个任务执行完后，其它任务才会被执行。
也就是说，当一个函数运行时，它不能被取代且会在其它代码运行前先完成。
当然，这也是EventLoop的一个缺点：当一个任务完成时间过长，那么应用就不能及时处理用户的交互（如点击事件），甚至导致该应用奔溃。
这与操作系统的进程调度模式有根本的不同，操作系统不能允许一个进程长时间占有CPU，以保证其他程序能够有机会得到执行。
一个比较好解决方案是：将任务完成时间缩短，或者尽可能将一个任务分成多个任务执行。

#### 绝不阻塞

JavaScript与其它语言不同，其EventLoop的一个特性是永不阻塞。I/O操作通常是通过事件和回调函数处理。
所以，当应用等待 indexedDB 或 XHR 异步请求返回时，其仍能处理其它操作。
例外是存在的，如alert或者同步XHR，但避免它们被认为是最佳实践。

#### 定时器

* 定时器的一些概念

上面也提到，在到达指定时间时，定时器就会将相应回调函数插入“任务队列”尾部，这就是“定时器(timer)”功能。

定时器包括setTimeout与setInterval两个方法，它们的第二个参数是指定其回调函数推迟\每隔多少毫秒数后执行。
对于第二个参数有以下需要注意的地方：

当第二个参数缺省时，默认为0；
当指定的值小于4毫秒，则增加到4ms（4ms是HTML5标准指定的，对于2010年及之前的浏览器则是10ms）；
如果你理解上述知识，那么以下代码就应该对你没什么问题了：

```js
console.log(1);
setTimeout(function(){
    console.log(2);
},10);
console.log(3);
```

* 零延迟 setTimeout(func, 0)

零延迟并不是意味着回调函数立刻执行。它取决于主线程当前是否空闲与“任务队列”里其前面正在等待的任务。

看看以下代码：

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
this is the start
this is just a message
this is the end
undefined // 立即调用函数的返回值
this is a msg from callback
this is a msg from a callback1
```

* setTimeout(func, 0)的作用，其他异步事件函数同样。
      
      改变执行顺序

#### 用setTimeout实现setInterval

大家都可能知道通过setTimeout可以模仿setInterval的效果，下面我们看看以下代码的区别：
```js
setTimeout(function(){
    setTimeout(arguments.callee, 10);
}, 1000);
setInterval(function(){
}, 1000);
```

可能你认为这没什么区别。的确，当回调函数里的操作耗时很短时，并不能看出它们有什么区别。

其实：上面案例中的 setTimeout 总是会在其回调函数执行后延迟 10ms（或者更多，但不可能少）再次执行回调函数，从而实现setInterval的效果，而 setInterval 总是 10ms 执行一次，而不管它的回调函数执行多久。

所以，如果 setInterval 的回调函数执行时间比你指定的间隔时间相等或者更长，那么其回调函数会连在一起执行。

你可以试试运行以下代码：
```js
var counter = 0;
var initTime = new Date().getTime();
var timer = setInterval(function(){
    if(counter===2){
        clearInterval(timer);
    }
    if(counter === 0){
        for(var i = 0; i < 1990000000; i++){
            ;
        }
    }
    console.log("第"+counter+"次：" + (new Date().getTime() - initTime) + " ms");
    counter++;
},1000);
```
我电脑Chrome浏览器的输入如下：

第0次：2007 ms
第1次：2013 ms
第2次：3008 ms

### 浏览器

浏览器不是单线程的

上面说了这么多关于JavaScript是单线程的，下面说说其宿主环境——浏览器。

浏览器的内核是多线程的，它们在内核制控下相互配合以保持同步，一个浏览器至少实现三个常驻线程：

* javascript引擎线程
javascript引擎是基于事件驱动单线程执行的，JS引擎一直等待着任务队列中任务的到来，然后加以处理，浏览器无论什么时候都只有一个JS线程在运行JS程序。
* GUI渲染线程
GUI渲染线程负责渲染浏览器界面，当界面需要重绘（Repaint）或由于某种操作引发回流(reflow)时,该线程就会执行。但需要注意GUI渲染线程与JS引擎是互斥的，当JS引擎执行时GUI线程会被挂起，GUI更新会被保存在一个队列中等到JS引擎空闲时立即被执行。
* 浏览器事件触发线程
事件触发线程，当一个事件被触发时该线程会把事件添加到“任务队列”的队尾，等待JS引擎的处理。这些事件可来自JavaScript引擎当前执行的代码块如setTimeOut、也可来自浏览器内核的其他线程如鼠标点击、AJAX异步请求等，但由于JS是单线程执行的，所有这些事件都得排队等待JS引擎处理。
在Chrome浏览器中，为了防止因一个标签页奔溃而影响整个浏览器，其每个标签页都是一个进程。当然，对于同一域名下的标签页是能够相互通讯的，具体可看 浏览器跨标签通讯。在Chrome设计中存在很多的进程，并利用进程间通讯来完成它们之间的同步，因此这也是Chrome快速的法宝之一。对于Ajax的请求也需要特殊线程来执行，当需要发送一个Ajax请求时，浏览器会开辟一个新的线程来执行HTTP的请求，它并不会阻塞JavaScript线程的执行，当HTTP请求状态变更时，相应事件会被作为回调放入到“任务队列”中等待被执行。

看看以下代码：

```js
document.onclick = function(){
    console.log("click")
}
for(var i = 0; i< 100000000; i++);
```

解释一下代码：首先向document注册了一个click事件，然后就执行了一段耗时的for循环，在这段for循环结束前，你可以尝试点击页面。
当耗时操作结束后，console控制台就会输出之前点击事件的”click”语句。
这视乎证明了点击事件（也包括其它各种事件）是由额外单独的线程触发的，事件触发后就会将回调函数放进了“任务队列”的末尾，等待着JavaScript主线程的执行。


Javascript并发模型和事件循环

JavaScript的"并发模型"是基于事件循环的，这个并发模型有别于Java的多线程， javascript的并发是单线程的。

Javascript 中有个重要一块，Event Loop，能把单线程的 JavaScript 使出 多线程的感觉。

"Event Loop是一个程序结构，用于等待和发送消息和事件。（a programming construct that waits for and dispatches events or messages in a program.）"
 
简单的说，就是在程序中（不一定是浏览器）中跑两个线程，一个负责程序本身的运行，作为主线程； 另一个负责主线程与其他线程的的通信，被称为“Event Loop 线程" 。  每当遇到异步的 setTimeOut ，setInterval 这些异步任务，交给 EventLoop 线程，然后自己往后运行，等到主线程运行完后，再去 Event Loop 线程拿结果。

这种模型人称 "asynchronous" 或 "non-blocking" 模行。 

我简单的画了一个 javascript 的执行图,我们通过图,逐步分析.

![runtime.jpg](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/runtime.jpg)

Javascript core

栈

函数调用时所用的执行环境栈

当js方法被调用时,会进入一个执行环境(execution context),如果有另外一个方法被调用了(或者自身递归调用),会新建一个新的执行环境,并且代码的执行会进入到这个新的执行环境.函数调用返回的时候重新回到原来的执行环境. 由此,代码执行的过程便形成了一个执行环境栈,江湖人称 "stack";

执行环境
execution context 是一个由ECMA定义的抽象的概念,所有的javascript代码都是在 execution context 执行环境中执行的.

全局执行环境是最外层的一个执行环境.在Web浏览器中,全局执行环境认为是window对象.因此所有全局变量和函数都是作为window对象的属性和方法创建的.

全局的代码(inline中执行的代码,通常包括js文件,html页面,加载的)在全局执行环境中执行.每个方法调用都有一个与之关联的执行环境.

某个执行环境中的所有代码执行完毕后,该执行环境被销毁,保存在其中的所有变量和函数定义也随之销毁. 全局执行环境直到页面关闭时才被销毁.

每个函数都有自己的执行环境,当执行流进入一个函数时,函数的执行环境就会被推入环境栈中. 而在函数执行之后,栈

将其环境栈弹出,把控制权返回给之前的执行环境.js中的执行流正是由这个方便的机制的控制着.

当代码在一个执行环境中执行时,会创建变量对象的一个作用域链(scope chain).

作用域链的用途,确保当前执行环境能有序(不明白就接着看)的访问所能获取的变量和函数.

作用域链的前端,始终都是当前执行的代码所在的执行环境的变量对象.

即当前作用域没有,外层作用域兜着.

执行环境被创建时会有次序的进行一些工作.

首先,在方法的执行环境中,Activation 活动对象被创建.活动对象另有一套实现机制.可以认为是对象,但又很特殊,没有prototype,不能在代码中直接引用到.
下一步,在方法调用创建执行环境的时候,会创建 argument 对象(类数组对象,含有传进来的参数,length,callee),活动对象中会有一个"argument"同名属性来引用这个argument对象.
再下一步,执行环境会被指定一个作用域.作用域由承载对象的列表(或链)组成.当代码在一个执行环境中执行,会创建变量对象的一个作用域链(scope chain).作用域链的前端,始终都是当前执行的代码所在执行环境的变量对象(和上面提到的 Activation 活动对象是一个对象). 如果这个环境是函数(javascript 环境只有函数和全局环境这两种), 则将其活动对象作为变量对象使用,活动对象在最开始时只包含一个arguments对象.
作用域链中下一个变量对象来自当前代码的外层环境.以此类推,直到到达最外层的全局执行环境,这样便构成了一条从底到上的作用域链.全局执行环境的变量对象始终都是作用域链的最后一个对象.

标示符解析是沿着作用域链一级一级的搜索标示符的过程.搜索过程始终都是从作用域链的最前端开始,然后主逐级向后回溯.

当进入执行环境

当进入执行环境(代码即将但仍未执行时),变量对象也就是活动对象已经包含了以下这些属性:

函数的所有形参,由名称和对应值组成变量对象的属性.
执行环境所在函数内部的所有子函数声明,由名称和对应值(函数对象 function object)组成变量对象的属性.如果变量对象内已存在同名属性,那么会被替换所有的变量声明.
由名称和对应值(undefined)组成变量对象的属性,如果变量名称跟已经声明的形式参数或函数相同，则变量声明不会干扰已经存在的这类属性.
需要说明的是,每个执行环境都有this,this的值取决于调用者和所执行代码的类型,this值是在进入执行环境时就已经确定的. 取值与执行环境相关联,并且在执行环境运行期间是不能被修改的.

this 执行上下文中的一个属性.

在全局代码中,this始终是全局对象本身.

在通常的函数调用中,this是由函数的调用者提供的,即被调用函数的父执行环境提供的.this值取决于函数调用的方式.

堆

堆是一个对象互联的网络。用数学术语说就是“图”。图由节点及其之间的边构成。节点和边都是可被标记的：节点（对象）用对象构造器的名称标记，边则由属性名称标记。

从一个对象到另一个的边序列被叫做路径（path）。通常我们只对那些不重复经过同一节点两次的简单路径（simple path）感兴趣。

我们把垃圾收集器根节点到某个指定对象的路径叫做retaining path。如果不存在这样的路径，则该对象被称作无法达到的（unreachable），应在垃圾收集过程中被处置。

队列

在web浏览器中,当事件发生时如果该事件有相应的监听器,则该消息会被及时的加进消息队列,如果没有监听器,该事件会被丢失.

javascript运行时伴随一个待处理的消息(也就是任务)队列,每个消息都关联了相关的处理函数,当函数的执行栈为空时,即当前没有正在执行的函数,那么,队列会从中挑出一个去处理.处理过程包括调用相关的函数(不用担心处理函数的作用域问题,因为在javascript中,作用域是词法化作用域,是方法在定义的时候已经确定的,与调用无关.作用域链创建早于方法调用,得益于此,我们方能使用闭包),处理完成后,如果栈为空,则再次尝试从队列中挑选可处理的事件或任务. 从中可以很容易窥探到 setInterval,setTimeout 是怎么进行异步执行的了.

这,就是事件循环,event loop.

总结

通过上面的分析,javascript是不存在并发的,单线程何谈并发? 这只是说说了非阻塞.


### 总结

JavaScript是单线程的，同一时刻只能执行特定的任务。而浏览器是多线程的。
异步任务（各种浏览器事件、定时器等）都是先添加到“任务队列”（定时器则到达其指定参数时）。当Stack栈（JS主线程）为空时，就会读取Queue队列（任务队列）的第一个任务（队首），然后执行。
JavaScript为了避免复杂性，而实现单线程执行。而今JavaScript却变得越来越不简单了，当然这也是JavaScript迷人的地方。

### 总结


### 参考
* http://www.raychase.net/1968?replytocom=51795
* http://www.codeceo.com/article/javascript-threaded.html
* http://www.cnblogs.com/yakun/p/3802725.html
* http://www.cnblogs.com/rainman/archive/2008/12/26/1363321.html
* http://blog.csdn.net/talking12391239/article/details/21168489
* http://ejohn.org/files/Timers.png
* http://ejohn.org/blog/how-javascript-timers-work/
* http://www.zhihu.com/question/20866267
* http://www.zhihu.com/question/31982417
* http://blog.thomasbelin.fr/p/javascript-single-threaded-et-asynchrone/
* http://stackoverflow.com/questions/2734025/is-javascript-guaranteed-to-be-single-threaded
* https://developer.mozilla.org/en-US/docs/Web/JavaScript/EventLoop
* http://www.ruanyifeng.com/blog/2014/10/event-loop.html

