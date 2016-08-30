# 函数声明和函数表达式

计算机语言发展到 C 就已经不区分函数和子过程了。

在 javascript 中所有表达式都有返回值（如果没有返回值就是undefined），这个返回值就可以继续作为表达式的一部分。大多数语言表达式的定义基本分为（忽略优先级）：运算符 表达式(一元，比如!true) 表达式 运算符 表达式(二元,比如1+2) 表达式1 ？ 表达式2 ： 表达式3(三元,a>b?a:b) 左括号 表达式 右括号（括号 (1+2)） 表达式(参数列表)(函数调用)等。 可见这是一种递归的定义，所以又规定字面量(就是1，2，3，“abc”)，this等是表达式。那么什么是表达式已经很明显了。

上面这段话“语句”的意思是指不是表达式的语句。在 javascript 里面满足这个条件的就函数声明、变量声明(var a=10是声明和赋值)、for语句、if语句、while语句、switch语句、return、try catch。
但是 javascript 还有一种函数表达式，它的形式跟函数声明一模一样。如果写 function fn() { return 0;} 是函数声明而写var a = function fn(){ return 0;} 等号后面的就是函数表达式。

楼主还是不要纠结什么是语句什么是表达式了，因为大多数时候我们说“语句”是指这门语言中的“一句话”。而表达式本身就可以作为“一句话”（表达式加一个分号就是“语句”），这段话的是说函数调用（方法调用）是表达式而已。

http://www.cnblogs.com/TomXu/archive/2011/12/29/2290308.html
http://kangax.github.io/nfe/

http://www.cnblogs.com/yuzhongwusan/archive/2012/01/30/2331693.html
http://javascript.info/tutorial/functions-declarations-and-expressions

## 函数声明和函数表达式s

函数声明:
`function 函数名称 (参数：可选){ 函数体 }`

函数表达式：
`function 函数名称（可选）(参数：可选){ 函数体 }`

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

还有一种函数表达式不太常见，就是被括号括住的(function foo(){})，他是表达式的原因是因为括号 ()是一个分组操作符，它的内部只能包含表达式，我们来看几个例子：

```js
  function foo(){}      // 函数声明
  (function foo(){});   // 函数表达式：包含在分组操作符内

  try {
    (var x = 5);        // 分组操作符，只能包含表达式而不能包含语句：这里的var就是语句
  } catch(err) {
    // SyntaxError
  }
```

你可以会想到，在使用eval对JSON进行执行的时候，JSON字符串通常被包含在一个圆括号里：eval('(' + json + ')')，这样做的原因就是因为分组操作符，也就是这对括号，会让解析器强制将JSON的花括号解析成表达式而不是代码块。

```js
  try {
    { "x": 5 }; // "{" 和 "}" 做解析成代码块
  } catch(err) {
    // SyntaxError
  }

  ({ "x": 5 }); // 分组操作符强制将"{" 和 "}"作为对象字面量来解析
```

表达式和声明存在着十分微妙的差别，首先，函数声明会在任何表达式被解析和求值之前先被解析和求值，即使你的声明在代码的最后一行，它也会在同作用域内第一个表达式之前被解析/求值，参考如下例子，函数fn是在alert之后声明的，但是在alert执行的时候，fn已经有定义了：

```js
  alert(fn());

  function fn() {
    return 'Hello world!';
  }
```

另外，还有一点需要提醒一下，函数声明在条件语句内虽然可以用，但是没有被标准化，也就是说不同的环境可能有不同的执行结果，所以这样情况下，最好使用函数表达式：

```js
  // 千万别这样做！
  // 因为有的浏览器会返回first的这个function，而有的浏览器返回的却是第二个

  if (true) {
    function foo() {
      return 'first';
    }
  }
  else {
    function foo() {
      return 'second';
    }
  }
  foo();

  // 相反，这样情况，我们要用函数表达式
  var foo;
  if (true) {
    foo = function() {
      return 'first';
    };
  }
  else {
    foo = function() {
      return 'second';
    };
  }
  foo();
```

函数声明的实际规则如下：

函数声明只能出现在程序或函数体内。

从句法上讲，它们 不能出现在Block（块）（{ ... }）中，例如不能出现在 if、while 或 for 语句中。

因为 Block（块） 中只能包含Statement语句，而不能包含函数声明这样的源元素。

另一方面，仔细看一看规则也会发现，唯一可能让表达式出现在Block（块）中情形，就是让它作为表达式语句的一部分。

但是，规范明确规定了表达式语句不能以关键字function开头。

而这实际上就是说，函数表达式同样也不能出现在Statement语句或Block（块）中（因为Block（块）就是由Statement语句构成的）。 


## 命名函数表达式

函数表达式在实际应用中还是很常见的，在web开发中友个常用的模式是基于对某种特性的测试来伪装函数定义，从而达到性能优化的目的，但由于这种方式都是在同一作用域内，所以基本上一定要用函数表达式：

```js
  // 该代码来自Garrett Smith的APE Javascript library库(http://dhtmlkitchen.com/ape/) 
  var contains = (function() {
    var docEl = document.documentElement;

    if (typeof docEl.compareDocumentPosition != 'undefined') {
      return function(el, b) {
        return (el.compareDocumentPosition(b) & 16) !== 0;
      };
    }
    else if (typeof docEl.contains != 'undefined') {
      return function(el, b) {
        return el !== b && el.contains(b);
      };
    }
    return function(el, b) {
      if (el === b) return false;
      while (el != b && (b = b.parentNode) != null);
      return el === b;
    };
  })();
```

提到命名函数表达式，理所当然，就是它得有名字，前面的例子var bar = function foo(){};就是一个有效的命名函数表达式，但有一点需要记住：这个名字只在新定义的函数作用域内有效，因为规范规定了标示符不能在外围的作用域内有效：

```js
  var f = function foo(){
    return typeof foo; // foo是在内部作用域内有效
  };
  // foo在外部用于是不可见的
  typeof foo; // "undefined"
  f(); // "function"
```

既然，这么要求，那命名函数表达式到底有啥用啊？为啥要取名？

正如我们开头所说：给它一个名字就是可以让调试过程更方便，因为在调试的时候，如果在调用栈中的每个项都有自己的名字来描述，那么调试过程就太爽了，感受不一样嘛。




