javascript-syntax
=================

参考：

* javascript-the-core [翻译](http://weizhifeng.net/javascript-the-core.html) [原文](http://dmitrysoshnikov.com/ecmascript/javascript-the-core/)

### 属性类型

#### 数据属性
|--|--|
|`[[Configurable]]` |表示能否通过delete删除属性从而重新定义属性，能否改变属性的特性，或者能否改变把属性改为访问器属性。true|
|`[[Enumerable]]`   |表示能否通过for-in循环返回属性。true|
|`[[Writable]]`	    |表示能否修改属性值。ture|
|`[[Value]]`		|包含实际值。undefined|

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
|-|-|
|`[[Configurable]]`	|表示能否通过delete删除属性从而重新定义属性，能否改变属性的特性，或者能否改变把属性改为访问器属性。true|
|`[[Enumerable]]`	|表示能否通过for-in循环返回属性。true|
|`[[Getter]]`		|取值函数。undefined|
|`[[Setter]]`		|赋值函数。undefined|

Note:

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

应用：观察者模式
例子[JavaScript实现MVVM之我就是想监测一个普通对象的变化](http://hcysun.me/2016/04/28/JavaScript%E5%AE%9E%E7%8E%B0MVVM%E4%B9%8B%E6%88%91%E5%B0%B1%E6%98%AF%E6%83%B3%E7%9B%91%E6%B5%8B%E4%B8%80%E4%B8%AA%E6%99%AE%E9%80%9A%E5%AF%B9%E8%B1%A1%E7%9A%84%E5%8F%98%E5%8C%96/)


### 对象保护

ECMAScript5对象保护功能

严格模式下抛出异常，普通模式下安静的失败；
在JavaScript里，默认情况下，你可修改任何你可以访问到的对象；
你可以自由的删除对象的属性或覆盖对象的方法，这在多人协作开发的项目中，会造成很大问题，因为你不知道你的修改会对别人造成什么样的影响；
如果你是一个模块或代码库的作者，你可能想锁定一些核心库的某些部分，保证任何人不能有意或无意的修改它们。

* 禁止添加属性：禁止扩展。禁止为对象添加属性和方法，但已存在的属性和方法是可以被修改和删除的。

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

* 禁止删除属性：密封。禁止删除对象已存在的属性和方法。

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

* 禁止添加或删除属性：冻结。禁止修改对象已存在的属性和方法，所有字段都是只读的。

```js
var persion3 = { name: 'liuht' };
Object.freeze(persion3);
console.log('isFrozen:', Object.isFrozen(persion3));            // -> true
console.log('isSealed:', Object.isSealed(persion3));            // -> true
console.log('isExtensible:', Object.isExtensible(persion3)); 	// -> false
delete persion3.name;
persion3.age = 10;
persion3.name = 'new name';
console.log(persion3);

```

***`访问器属性`和`数据保护功能`都是针对对象属性，而不是变量。***


### 数据类型

五种基本类型 `Undefined`，`Null`，`Boolean`，`Number`，`String`。

平时使用的时候都使用的是字面量形式，但是当需要的时候，它们也会被转换成对象，即基本类型的包装类型。

没有`Undefined`和`Null`内建函数，而是有`Undefined`和`Null`类型的内建象，分别是`undefined`和`null`。

ECMAScript认为`undefined`是从`null`派生出来的，所以把它们定义为相等的, 相同的地方是都可以视为布尔值的false。

引用类型：`Object`、`Function`、`Array`、`Error`、`Regexp`、`Map`、`Set`...

***Note：JavaScript中除了 `null` 和 `undefined` 之外的一切都被当做对象！***

undefined与null的区别：
null表示"没有对象"，即该处不应该有值。
1. 作为函数的参数，表示该函数的参数不是对象。
2. 作为对象原型链的终点。
undefined表示"缺少值"，就是此处应该有一个值，但是还没有定义。
1. 变量被声明了，但没有赋值时，就等于undefined。
2. 调用函数时，应该提供的参数没有提供，该参数等于undefined。
3. 对象没有赋值的属性，该属性的值为undefined。
4. 函数没有返回值时，默认返回undefined。

```js
console.log(undefined instanceof Object);   // false
console.log(typeof undefined);              // undefined
console.log(null instanceof Object);        // false
console.log(typeof null);                   // object
console.log(undefined === null);            // false
console.log(undefined == null);             // true Object.prototype.valueOf(undefined) === Object.prototype.valueOf(null)

var undefined = 'foo';
console.log(undefined, typeof undefined);   // foo 'string'
console.log(void(0) === undefined);         // true

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

var str = '';
var strObj = new String('');
console.log(str instanceof Object);         // false
console.log(str instanceof String);         // false
console.log(strObj instanceof Object);      // true
console.log(strObj instanceof String);      // true
console.log(str === strObj);                // false
console.log(typeof str);                    // string
console.log(typeof strObj);                 // object

var bool = true;
var boolObj = new Boolean(true);
console.log(bool instanceof Object);        // false
console.log(bool instanceof Boolean);       // false
console.log(boolObj instanceof Object);     // true
console.log(boolObj instanceof Boolean);    // true
console.log(bool === boolObj);              // false
console.log(typeof bool);                   // boolean
console.log(typeof boolObj);                // object

// 引用类型Object
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

注意：GetValue一定要调用，即使它的值不会被用到，但是这个表达式可能会有副作用(side-effects)。

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

我们拥有一个这样的结构，两个明显的自身属性和一个隐藏的属性`__proto__`，这个属性是对`foo.prototype`的引用：

![basic-object](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/basic-object.png)

这些`prototype`有什么用？让我们以`原型链`的概念来回答这个问题。


### 原型链（prototype-chain）

`原型对象`也是简单的对象并且可以拥有它们自己的原型，如果一个原型对象的原型是一个非`null`的引用，那么以此类推，这就叫作`原型链`。
`原型链`是一个用来实现`继承`和`共享属性`的有限长度的对象链。
`原型链`是为了实现代码重用，在基于类的系统中，这个代码重用风格叫作`类继承`。

ECMAScript中没有类的概念，但是代码重用的风格并没有太多不同且通过原型链来实现，这种继承方式叫作委托继承(delegation based inheritance)，或者，更贴近ECMAScript一些，叫作原型继承(prototype based inheritance)。

```js
var a = {
  x: 10,
  calculate: function (z) {
    return this.x + this.y + z
  }
};

var b = {
  y: 20,
  __proto__: a
};

var c = {
  y: 30,
  __proto__: a
};

// call the inherited method
b.calculate(30); // 60
c.calculate(40); // 80
```

b和c访问到了在对象a中定义的calculate方法，这是通过`原型链lookup`实现的。

原型链lookup规则：

如果一个属性或者一个方法在对象自身中无法找到，它会尝试在原型链中寻找这个`属性`/`方法`。

如果这个属性在原型中没有查找到，那么将会查找原型的原型，以此类推，遍历整个原型链，第一个被查找到的同名`属性`/`方法`会被使用。如果在遍历了整个原型链之后还是没有查找到这个属性的话，返回undefined值。

在类继承中也是一样的，当解析一个继承的方法的时候－我们遍历class链（class chain）

下一张图展示了对象a，b，c之间的继承层级：

![prototype-chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/prototype-chain.png)

ES5标准化了一个实现原型继承的可选方法，即使用`Object.create`函数：

```js
var b = Object.create(a, {y: {value: 20}});
var c = Object.create(a, {y: {value: 30}});
```

ES6标准化了`__proto__`属性，并且可以在对象初始化的时候使用它。

### __proto__

`Object.prototype.__proto__`

The `__proto__` property of `Object.prototype` is an `accessor property` (a getter function and a setter function) that exposes the internal `[[Prototype]]` (either an object or null) of the object through which it is accessed.

如果没有明确为一个对象指定原型，那么它将会使用`__proto__`的默认值－`Object.prototype`。`Object.prototype`对象自身也有一个`__proto__`属性，这是原型链的终点并且值为`null`。

***Note:项目中不要直接使用`__proto__`访问原型，而是使用`Object.getPrototypeOf()`读取原型，`Object.create()`设置原型。***

```js
var Shape = function () { };

var proto = {
    say: function () {
        console.log('hello world!');
    }
};

Shape.prototype = proto;
var circle = new Shape();
console.log('circle:', circle.__proto__ === Shape.prototype);						// true
console.log('circle:', Object.getPrototypeOf(circle) === Shape.prototype);			// true
console.log('circle:', typeof circle); 												// object
console.log('circle:', circle instanceof Shape); 									// true
console.log('circle:', circle instanceof Object); 									// true
circle.say(); 																		// hello world!


var rectangle = Object.create(proto);
console.log('ractangle:', rectangle.__proto__ === Shape.prototype);					// true
console.log('ractangle:', Object.getPrototypeOf(rectangle) === Shape.prototype);	// true
console.log('ractangle:', typeof rectangle); 										// object
console.log('ractangle:', rectangle instanceof Shape); 								// true
console.log('ractangle:', rectangle instanceof Object); 							// true
circle.say(); 																		// hello world!


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

通常情况下需要对象拥有相同或者相似的状态结构（也就是相同的属性集合），赋以不同的状态值，在这个情况下我们可能需要使用`构造函数`(constructor function)，其以指定的模式来创造对象。


### 构造函数

除了以指定模式创建对象之外，构造函数也做了另一个有用的事情－它自动地为新创建的对象设置一个原型对象，这个原型对象存储在`ConstructorFunction.prototype`属性中。

我们可以使用构造函数来重写上一个拥有对象b和对象c的例子。因此，对象a（一个原型对象）的角色由Foo.prototype来扮演：

```js
// a constructor function
function Foo(y) {
  // which may create objects
  // by specified pattern: they have after
  // creation own "y" property
  this.y = y;
}

// also "Foo.prototype" stores reference
// to the prototype of newly created objects,
// so we may use it to define shared/inherited
// properties or methods, so the same as in
// previous example we have:

// inherited property "x"
Foo.prototype.x = 10;

// and inherited method "calculate"
Foo.prototype.calculate = function (z) {
  return this.x + this.y + z;
};

// now create our "b" and "c"
// objects using "pattern" Foo
var b = new Foo(20);
var c = new Foo(30);

// call the inherited method
b.calculate(30); // 60
c.calculate(40); // 80

// let's show that we reference
// properties we expect

console.log(

  b.__proto__ === Foo.prototype, // true
  c.__proto__ === Foo.prototype, // true

  // also "Foo.prototype" automatically creates
  // a special property "constructor", which is a
  // reference to the constructor function itself;
  // instances "b" and "c" may found it via
  // delegation and use to check their constructor

  b.constructor === Foo, // true
  c.constructor === Foo, // true
  Foo.prototype.constructor === Foo // true

  b.calculate === b.__proto__.calculate, // true
  b.__proto__.calculate === Foo.prototype.calculate // true

);
```

这个代码可以表示为如下关系：

![constructor-proto-chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/constructor-proto-chain.png)

可以看到，构造函数`Foo`也有自己的`__proto__`，值为`Function.prototype`，`Function.prototype`也通过其`__proto__`属性关联到`Object.prototype`。实际上除了`null`之外的每个对象都有`原型`。

如果思考一下类的概念，那么构造函数和原型对象合在一起可以叫作「类」。例如：Python的First-Class Dynamic-Classes显然是以同样的属性/方法处理方案来实现的。从这个角度来说，Python中的类就是ECMAScript使用的委托继承的一个语法糖。

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

### new 操作符 都做了什么？

***Note：用`new`来调用，就是构造函数，不用`new`调用，就是普通函数。***

1. 创建一个新对象
2. 将构造函数作用域赋给新对象，即this指向了新对象
3. 执行构造函数中的代码
4. 返回新对象的引用

```js
var o = new NewObject(11, 22)
var o;
NewObject.apply(o, 11, 22);
NewObject.call(o, [11, 22]);

var obj1 = new NewObject(11, 22);   // 构造函数方式
obj1.func();                        // this == obj1

var obj2 = NewObject(33, 44);       //　普通函数方式
obj2.func();                        // error
global.func();                      // this == global
console.log(obj2);                  // undefined  NewObject()作为函数并无返回值，所以undefined

// 在另一个对象的作用域中调用，同样是当作普通函数调用
var obj3 = new Object();
NewObject.call(obj3, 55, 66);       //原this指针(global)被替换成obj3,　原属性同样转移到obj3上。
obj3.func();

console.log(obj1.func === obj3.func); 		// false
console.log(obj1.func() === obj3.func()); 	// true  ???
```


### 为什么要有`bind`、`call`、`apply`三个函数存在。
    
TODO: 要改
从设计者的角度去考虑各个点，call、apply、bind 存在的原因。
C++中类的方法是隐式传递了this指针，python的方法都是显示的指定self，而js也同样需要this。
但是this在js中是作为一个执行环境上下文的概念存在，并且对于任意一个函数（一级公民），它有语法逻辑上的上下文，但是它的上下文又可以是人为绑定的，
这三个函数就可以用来完成绑定工作。任何一个函数也是在一个上下文对象上进行工作。上下文是一个this对象。
这是一种松散的绑定关系，随时可以根据需要来绑定。因此就可以自由的将其他模块上的属性方法，绑定到自己身上，但是要避免名字冲突。


### 对象构造

#### 工厂模式

解决了创建对象的问题，但是对象无法识别类型，只是一个Object.

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

构造函数名字用来标志一个`特定类型`
问题在于：每个方法在每个对象上都要重新创建一次，把每个函数当作Function就明白了。

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

每个函数都有一个`prototype`属性，这是一个指针，指向一个对象，这个对象可以实现属性的共享。
`prototype`是函数对象的一个属性，`prototype`指向的`原型对象`拥有一个`constructor`属性指向原型对象的拥有者。
通过构造函数创建的`对象实例`的`原型对象`可以通过实例属性`__proto__`访问，但是不能重写，重名的属性将屏蔽原型中的同名属性。

在原型中修改属性，会立刻在实例中反映出来。但是如果重写整个原型对象，那么实例对象将找不到原型中定义的属性。

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

#### 组合使用构造函数和原型模式

* 集两者之长默认模式
* 实例属性在构造函数中定义　　
* 共享属性在原型中定义

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

#### 动态原型模式

只在第一次调用构造函数时　实例化原型

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

#### 寄生模式

这种方式，可以用来扩展原生对象，在不修改原生对象的前提下，增加方法。

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

适合用于一些安全环境，这些环境禁止使用this和new，防止数据被其他程序改动时使用。数据成员位于作用域链中，不在对象的属性中。

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


### 对象继承

#### 原型链

存在的问题：
1. 原型属性会被所有实例共享
2. 无法向超类传递参数

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
	SupType.call(this); // this 指 SubType 普通函数调用 把函数当作一个模板 同时可以传递参数
}
var instance = new SubType();
instance.colors.push('black');
console.log(instance);
```

#### 组合继承

原型链继承原型
借用构造函数继承实例属性

```js
function SuperType(name) {
	this.name = name;
	this.colors = ['red', 'blue', 'green'];
}
SuperType.prototype.sayName = function () {
	console.log(this.name);
};

function SubType(name, age) {
	SuperType.call(this, name);         // 普通函数
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

此方式必须有一个对象作为基础  作为原型

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
	var clone = Object.create(original);    // 封装了原型式继承
	clone.sayHi = function () {
		console.log('Hi');
	};
	return clone;
}
```

#### 寄生组合式继承

借用构造函数继承属性
原型链的混成形式继承方法

```js
function inheritPrototype(subType, supType) {
	var prototype = Object.create(supType.prototype);
	prototype.constructor = subType;
	subType.prototype = prototype;
}
//var prot = new Object.prototype;   // error
```

Node.js原生实现：

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
    constructor: {
      value: ctor,
      enumerable: false,
      writable: true,
      configurable: true
    }
  });
};
```

下图是一个Javascript Prototype Chain关系图：

![Javascript Prototype Chain](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/javascript-prototype.png)


现在，在我们知道了对象的基础之后，让我们看看运行时程序的执行（runtime program execution）在ECMAScript中是如何实现的。

这叫作执行上下文栈（execution context stack），其中的每个元素也可以抽象成为一个对象。是的，ECMAScript几乎在任何地方都和对象的概念打交道;)

### 执行上下文堆栈

这里有三种类型的ECMAScript代码：`全局代码`、`函数代码`和`eval代码`。

每个代码是在其执行上下文（execution context）中被求值的。

这里只有一个全局上下文，可能有多个函数执行上下文以及eval执行上下文。

对一个函数的每次调用，会进入到函数执行上下文中，并对函数代码类型进行求值。

每次对eval函数进行调用，会进入eval执行上下文并对其代码进行求值。

注意，一个函数可能会创建无数的上下文，因为对函数的每次调用（即使这个函数递归的调用自己）都会生成一个具有新状态的上下文：

```js
function foo(bar) {}

// call the same function,
// generate three different
// contexts in each call, with
// different context state (e.g. value
// of the "bar" argument)

foo(10);
foo(20);
foo(30);
```

一个执行上下文可能会触发另一个上下文，比如，一个函数调用另一个函数（或者在全局上下文中调用一个全局函数）。从逻辑上来说，这是以栈的形式实现的，它叫作执行上下文栈。

一个触发其他上下文的上下文叫作`caller`，被触发的上下文叫作`callee`，`callee`在同一时间可能是一些其他`callee`的`caller`（比如，一个在全局上下文中被调用的函数，之后调用了一些内部函数）。

当一个`caller`触发（调用）了一个`callee`，这个`caller`会暂缓自身的执行，然后把控制权传递给`callee`。
这个`callee`被push到栈中，并成为一个运行中（活动的）执行上下文，在`callee`的上下文结束后，它会把控制权返回给`caller`，然后`caller`的上下文继续执行（它可能触发其他上下文）直到它结束，以此类推。
`callee`可能简单的返回或者由于异常而退出，一个抛出的但是没有被捕获的异常可能退出一个或者多个上下文。

所有ECMAScript程序的运行时可以用执行上下文（EC）栈来表示，栈顶是当前活动的上下文：

![ec-stack](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/ec-stack.png)

当程序开始的时候它会进入全局执行上下文，此上下文位于栈底并且是栈中的第一个元素。然后全局代码进行一些初始化，创建需要的对象和函数。

在全局上下文的执行过程中，它的代码可能触发其他（已经创建完成的）函数，这些函数将会进入它们自己的执行上下文，向栈中push新的元素，以此类推。

当初始化完成之后，运行时系统（runtime system）就会等待一些事件（比如，用户鼠标点击），这些事件将会触发一些函数，从而进入新的执行上下文中。

在下个图中，拥有一些函数上下文EC1和全局上下文Global EC，当EC1进入和退出全局上下文的时候下面的栈将会发生变化：

![ec-stack-changes](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/ec-stack-changes.png)

这就是ECMAScript的运行时系统如何真正地管理代码执行的。

更多有关ECMAScript中执行上下文的信息可以在对应的第一章 执行上下文中获取。

栈中的每个执行上下文都可以用一个对象来表示。

让我们来看看它的结构以及一个上下文到底需要什么状态（什么属性）来执行它的代码。


### 执行上下文

一个执行上下文可以抽象的表示为一个简单的对象。每一个执行上下文拥有一些属性（可以叫作上下文状态）用来跟踪和它相关的代码的执行过程。在下图中展示了一个上下文的结构：

![execution-context](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/execution-context.png)

除了这三个必需的属性，变量对象、this、作用域链之外，执行上下文可以拥有其他附加的状态，这取决于实现。

让我们详细看看上下文中的这些重要的属性。


### 变量对象（variable object）

`变量对象`是与`执行上下文`相关的`数据作用域`。它是一个与上下文相关的特殊对象，其中存储了在上下文中定义的`变量`和`函数声明`。
注意，函数表达式（与函数声明相对）不包含在变量对象之中。

变量对象是一个抽象概念。对于不同的上下文类型，在物理上，是使用不同的对象。在全局上下文中变量对象就是全局对象本身，这就是为什么我们可以通过全局对象的属性名来关联全局变量。

让我们在全局执行上下文中考虑下面这个例子：

```js
var foo = 10;

function bar() {} // function declaration, FD
(function baz() {}); // function expression, FE

console.log(
  this.foo == foo, // true
  window.bar == bar // true
);

console.log(baz); // ReferenceError, "baz" is not defined
```

之后，全局上下文的`变量对象`将会拥有如下属性：

![variable-object](https://raw.githubusercontent.com/liuyanjie/study/master/javascript/javascript-syntax/images/variable-object.png)

再看一遍，函数baz是一个函数表达式，没有被包含在变量对象之中。这就是为什么当我们想要在函数自身之外访问它的时候会出现ReferenceError。

注意，与其他语言（比如C/C++）相比，在ECMAScript中只有函数可以创建一个新的作用域。在函数作用域中所定义的变量和内部函数在函数外边是不能直接访问到的，而且并不会污染全局变量对象。

使用eval我们也会进入一个新的执行上下文。无论如何，eval使用全局的变量对象或者使用caller（比如eval被调用时所在的函数）的变量对象。

那么函数和它的变量对象是怎么样的？在函数上下文中，变量对象是以`活动对象`来表示的。


### 活动对象（activation object）

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


### 作用域链(scope chain)

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
这里有几种技术可以解决这个问题。其中一种是在作用域链中提供一个额外的对象－比如，使用额外函数：

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

对闭包理论和它们的实际应用感兴趣的同学可以在第六章 闭包中找到额外的信息。如果想获取更多关于作用域链的信息，可以看一下同名的第四章 作用域链。

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


### 总结

我们只是没有涉及到两个大的主题：函数（和不同函数之间的区别，比如，函数声明和函数表达式）和ECMAScript中所使用的求值策略(evaluation strategy)。这两个主题是可以ES3系列的在对应章节找到：第五章 函数 和 第八章 求值策略。

### 函数表达式

### 闭包 

有权访问另一个函数作用域中的变量的函数


当函数被调用时 会创建一个 执行环境 和相应 作用域链  然后使用arguments和其他命名函数初始化 活动对象

 #### 语法分析树（SyntaxTree）
 可以直观地表示出这段代码的相关信息，具体的实现就是JS引擎创建了一些表，
 用来记录每个方法的 内部变量集（variables）、内嵌函数集（functions）和作用域（scope）等

 #### 执行环境（ExecutionContext）
 可理解为一个记录当前执行的方法【外部描述信息】的对象,
 记录所执行方法的类型，名称，参数和活动对象（activeObject）

 #### 活动对象（activeObject）
 可理解为一个记录当前执行的方法【内部执行信息】的对象,
 记录 内部变量集（variables）、内嵌函数集（functions）、实参（arguments）、作用域链（scopeChain）等执行所需信息，
 其中 内部变量集（variables）、内嵌函数集（functions）是直接从第一步建立的语法分析树复制过来的

 #### 词法作用域
 变量的作用域是在定义时决定而不是执行时决定，也就是说词法作用域取决于源码，通过静态分析就能确定，因此词法作用域也叫做静态作用域。
 with和eval除外，所以只能说JS的作用域机制非常接近词法作用域（Lexical scope）

 #### 作用域链
 词法作用域的实现机制就是作用域链（scopeChain）。
 作用域链是一套按名称查找（Name Lookup）的机制，
 首先在当前执行环境的 ActiveObject 中寻找，没找到，
 则顺着作用域链到父 ActiveObject 中寻找，一直找到全局调用对象（Global Object）

```js
var v1 = 1;
var v2;

function f1() {
	console.log(f1);
	var v3 = 3;
	var v4;

	function f3() {
		console.log(f3);
	}
	f3();		//f1()执行时进行实例化
}

function f2() {
	console.log(f2);
}

f1();		//全局环境执行时进行实例化
f2();		//全局环境执行时进行实例化

```


 * 1.预解析
 * 词法作用域伪类 把变量，函数格式化成伪类的形式，定义词法作用域的范围，这就是预解析阶段做的啊！
 * 语法分析树：变量集、方法集、作用域等

```js
var SyntaxTree = {
	global: {
		variables: {
			v1: { value: 1 },
			v2: { value: undefined }
		},
		functions: {
			f1: this.f1,
			f2: this.f2
		},
		scope: this.global
	},

	f1: {
		variables: {
			v3: { value: 3 },
			v4: { value: undefined }
		},
		functions: {
			f3: this.f3
		},
		scope: this.global
	},

	f2: {
		variables: {},
		functions: {},
		scope: this.global
	},

	f3: {
		variables: {},
		functions: {},
		scope: this.a
	}
}
```

 语法分析树关键点
 * 1变量集（variables）中，只有变量定义，没有变量值，这时候的变量值全部为“undefined”
 * 2作用域（scope），根据词法作用域的特点，这个时候每个变量的作用域就已经明确了，而不会随执行时的环境而改变。
 * 3作用域（scope）建立规则
 * a对于函数声明和匿名函数表达式来说，[scope]就是它创建时的作用域
 * b对于有名字的函数表达式，[scope]顶端是一个新的JS对象（也就是继承了Object.prototype），这个对象有两个属性，
 * 第一个是自身的名称，第二个是定义的作用域，第一个函数名称是为了确保函数内部的代码可以无误地访问自己的函数名进行递归。



 * 2.解析运行
 * JS代码是一段段执行的。也就是以函数内部的活动代码为单位，一段段活动代码执行。
 * 实例化就是调用对象（Call Object）的过程，上面我们一直说这个分析很像类结构。
 * 这次就真的是把这个像类的词法分析出来的结果进行伪类的实例化了。
 * 实例化的同时，这个调用对象的一个属性被初始化成一个名叫 arguments 的属性，
 * 它引用了这个函数的 Arguments 对象，Arguments 对象是函数的实际参数。
 * 活动对象：变量集、方法集、实参列表、作用域链等		形参（parameters） 实参（arguments）
 *
 * 活动对象关键点：
 * 创建活动对象，从语法分析树复制方法的内部变量集（variables）和内嵌函数集（functions）
 * 方法开始执行，活动对象里的内部变量集全部被重置为 undefined
 * 创建形参（parameters）和实参（arguments）对象，同名的实参，形参和变量之间是【引用】关系
 *
 * 执行方法内的赋值语句，这才会对变量集中的变量进行赋值处理
 * 变量查找规则是首先在当前执行环境的 ActiveObject 中寻找，没找到，则顺着执行环境中属性 ScopeChain 指向的 ActiveObject 中寻找，一直到 Global Object（window）
 * 方法执行完成后，内部变量值不会被重置，至于变量什么时候被销毁，请参考下面一条
 * 方法内变量的生存周期取决于方法实例是否存在活动引用，如没有就销毁活动对象
 * 6和7 是使闭包能访问到外部变量的根本原因

```js
var ActiveObject = {
	global: {
		variables: {
			v1: {value: 1},
			v2: {value: undefined}
		},
		functions: {
			f1: this.f1,
			f2: this.f2
		}
	},

	f1: {
		variables : {
			v3: {value: 3},
			v4: {value: undefined}
		},
		functions : {
			f3: SyntaxTree.f3
		},
		//scope    : this.global,
		parameters: { },
		arguments : [this.v3.value, this.v4.value]
	},

	f2: {
		variables : { },
		functions : { },
		//scope    : this.global
		parameters: { },
		arguments : []
	},

	f3: {
		variables : { },
		functions : { },
		//scope    : this.a
		parameters: { },
		arguments : []
	}
}
```

 * 执行环境：函数执行时创建的执行环境
 * 		body属性，直接指向当前方法的活动对象
 * 		scopeChain属性，作用域链，它是一个链表结构，根据语法分析树中当前方法对应的scope属性，它指向scope对应的方法的活动对象（ActivceObject）。
```js
var ExecutionContext = {
	global: {
		type: 'global',
		name: 'global',
		body: ActiveObject.global
		//scopeChain: this.global
	},

	f1: {
		type: 'function',
		name: 'f1',
		body: ActiveObject.f1,
		scopeChain: this.global.body
	},

	f2: {
		type: 'function',
		name: 'f2',
		body: ActiveObject.f2,
		scopeChain: this.global.body
	},

	f3: {
		type: 'function',
		name: 'f3',
		body: ActiveObject.f3,
		scopeChain: this.f1.body
	}
};
```

 * 闭包是一个拥有许多 变量和绑定了这些变量的环境的表达式（通常是一个函数），因而这些变量也是该表达式的一部分。
 * 	1、保护函数内的变量安全。　通过保护变量的安全实现JS私有属性和 私有方法（不能被外部访问）
 *	2、在内存中维持一个变量。
 *	3、闭包就是将函数内部和函数外部连接起来的一座桥梁。 让外部环境有接口访问内部变量
 *	4、闭包函数可以访问所保持的作用域链上的外部环境。


 * 预解析先建立语法分析树
 * 执行环境定义了变量或函数有权访问的其他数据，决定了他们各自的行为。
 * 每个执行环境都有与之关联的 变量对象(VO)， 环境中定义的所有变量和函数都保存在这个对象中。
 * 全局环境是最外围的执行环境。
 * 每个函数都有自己的自行环境。当执行流进入一个函数时，函数的环境就会被推入一个环境栈中。
 * 当代码在一个环境中执行时，会创建 变量对象(VO)的作用域链，用以保证对执行环境中有权访问的所有变量和函数进行有序访问。
 * 作用域链的前端，始终都是当前执行代码所在环境的变量对象，如果这个环境是函数，则将其活动对象作为变量对象。
