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

/**
 * 有时候一个方法定义的地方和使用的地方会相隔十万八千里，那方法执行时，它能访问哪些变量，不能访问哪些变量，这个怎么判断呢？这个就是我们这次需要分析的问题—词法作用域
 */

/**
 * 词法作用域：变量的作用域是在定义时决定而不是执行时决定，也就是说词法作用域取决于源码，通过静态分析就能确定，因此词法作用域也叫做静态作用域。 with和eval除外，所以只能说JS的作用域机制非常接近词法作用域（Lexical scope）。
 */


// 解析过程
// 1、执行顺序
// 编译型语言，编译步骤分为：词法分析、语法分析、语义检查、代码优化和字节生成。
// 解释型语言，通过词法分析和语法分析得到语法分析树后，就可以开始解释执行了。这里是一个简单原始的关于解析过程的原理，仅作为参考，详细的解析过程（各种JS引擎还有不同）还需要更深一步的研究
//
// JavaScript执行过程，如果一个文档流中包含多个script代码段（用script标签分隔的js代码或引入的js文件），它们的运行顺序是：
// 阶段一：解析
// 步骤1. 载入第一个代码段（js执行引擎并非一行一行地执行程序，而是一段一段地分析执行的）。
// 步骤2. 做词法分析->[词法作用域] 和 语法分析->[语法分析树]，有错则报语法错误(Syntax Error)（比如括号不匹配等），并跳转到步骤5。
// 步骤3. 对[var]变量和[function]定义做“预解析“（永远不会报错的，因为只解析正确的声明）。
// 阶段二：执行
// 步骤4. 执行代码段，有错则报错（比如变量未定义）。
//
// 步骤5. 如果还有下一个代码段，则读入下一个代码段，重复步骤2。
// 步骤6. 结束
//
// 2、特殊说明
// 全局域（window）域下所有JS代码可以被看成是一个“匿名方法“，它会被自动执行，而此“匿名方法“内的其它方法则是在被显示调用的时候才被执行

// 3、关键步骤
// 上面的过程，我们主要是分成两个阶段
// 解析：就是通过语法分析和预解析构造合法的语法分析树。
// 执行：执行具体的某个函数，JS引擎在执行每个函数实例时，都会创建一个执行环境（ExecutionContext）和活动对象（activeObject）（它们属于宿主对象，与函数实例的生命周期保持一致）
// 3、关键概念
// 到这里，我们再更强调以下一些概念，这些概念都会在下面用一个一个的实体来表示，便于大家理解
// 语法分析树（SyntaxTree）可以直观地表示出这段代码的相关信息，具体的实现就是JS引擎创建了一些表，用来记录每个方法内的变量集（variables），方法集（functions）和作用域（scope）等
// 执行环境（ExecutionContext）可理解为一个记录当前执行的方法【外部描述信息】的对象，记录所执行方法的类型、名称、参数和活动对象（activeObject）
// 活动对象（activeObject）可理解为一个记录当前执行的方法【内部执行信息】的对象，记录内部变量集（variables）、内嵌函数集（functions）、实参（arguments）、作用域链（scopeChain）等执行所需信息，其中内部变量集（variables）、内嵌函数集（functions）是直接从第一步建立的语法分析树复制过来的。
// 词法作用域：变量的作用域是在定义时决定而不是执行时决定，也就是说词法作用域取决于源码，通过静态分析就能确定，因此词法作用域也叫做静态作用域。 with和eval除外，所以只能说JS的作用域机制非常接近词法作用域（Lexical scope）
// 作用域链：词法作用域的实现机制就是作用域链（scopeChain）。作用域链是一套按名称查找（Name Lookup）的机制，首先在当前执行环境的 ActiveObject 中寻找，没找到，则顺着作用域链到父 ActiveObject 中寻找，一直找到全局调用对象（Global Object）

// javascript词法分析 lexical analyzer  Lexer  Tokenizer
// 词法分析主要分为3步：
// 第1步：分析形参
// 第2步：分析变量声明
// 第3步：分析函数声明
// 
// 如果存在函数嵌套，则从外往内进行词法分析
// 
// 具体步骤：
// 0：在函数执行的一瞬间，生产 Active Object（活动对象），下面简称AO
// 1:
// 1.1 函数声明的形参，形成AO的属性，默认值是undefined,
// 1.2 接收形参，给刚刚形成AO的属性的形参赋值
// 2：分析var声明变量！如 var age;（变量的值是在运行时期决定）
// 2.1 如果AO上还没有age属性，则给AO添加age属性，默认值是undefined
// 2.2 如果AO上已经有age属性，则不做任何操作。
// 3：分析函数声明！如 function foot(){}
// 3.1 如果AO上没有foot属性，则把函数赋给AO.foot属性
// 3.2 如果AO上有foot属性，则会直接覆盖，把函数赋给AO.foot属性
//
// 代码演示与分析：
// 
//   function a(b){
//        alert(b);
//        function b(){
//            alert(b);
//        }
//        b();
//    }
//    a(1);
// 
// 分析过程：
// 0、形成活动对象AO={}
// 1、分析形参，--> AO={b:undefined}; 分析传参，--> AO={b:1}
// 2、分析变量声明var，没有
// 3、分析函数声明，AO.b=function(){alert(b);},执行覆盖操作
// 
// 执行过程：
// alert(b);//function
// b(); // 执行function b...alert(b), 在函数b的作用域内部找不到b,根据作用域链原理
//（见上一篇http://blog.csdn.net/guixuecheng/article/details/43670323）往外层寻找，找到b就是函数自己，打印出function ...



// JavaScript的每个函数function都有自己的作用域，使用Active Object（简称AO）活动对象来保存，在相互嵌套的函数中形成了作用域链，如图：
// 作用域链就是从里到外的AO链变量的寻找：

// 函数fn3中使用的变量，如在fn3作用域内寻找不到，则往外层fn2作用域寻找，以此类推，直到全局对象window

// 解析模拟
// 估计，看到这儿，大家还是很朦胧吧，什么是语法分析树，语法分析树到底长什么样子，作用域链又怎么实现的，活动对象又有什么内容等等，还是不是太清晰，
// 下面我们就通过一段实际的代码来模拟整个解析过程，我们就把语法分析树，活动对象实实在在的创建出来，理解作用域，作用域链的到底是怎么实现的

// 1、模拟代码
/**
 * 全局（window）域下的一段代码
 */
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

// 2、语法分析树
// 上面的代码很简单，就是先定义了一些全局变量和全局方法，接着在方法内再定义局部变量和局部方法，现在JS解释器读入这段代码开始解析，
// 前面提到 JS 引擎会先通过语法分析和预解析得到语法分析树，至于语法分析树长什么样儿，都有些什么信息，下面我们以一种简单的结构：
// 一个 JS 对象(为了清晰表示个各种对象间的引用关系，这里的只是伪对象表示，可能无法运行)来描述语法分析树
// （这是我们比较熟悉的，实际结构我们不去深究，肯定复杂得多，这里是为了帮助理解解析过程而特意简化）
/**
 * 模拟建立一棵语法分析树，存储function内的变量和方法
 */
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

// 上面就是关于语法分析树的一个简单表示，正如我们前面分析的，语法分析树主要记录了每个 function 中的变量集（variables），方法集（functions）和作用域（scope）
// 语法分析树关键点
// 1变量集（variables）中，只有变量定义，没有变量值，这时候的变量值全部为“undefined”
// 2作用域（scope），根据词法作用域的特点，这个时候每个变量的作用域就已经明确了，而不会随执行时的环境而改变。【什么意思呢？就是我们经常将一个方法 return 回去，然后在另外一个方法中去执行，执行时，方法中变量的作用域是按照方法定义时的作用域走。其实这里想表达的意思就是不管你在多么复杂，多么远的地方执行该方法，最终判断方法中变量能否被访问还是得回到方法定义时的地方查证】
// 3作用域（scope）建立规则
// a对于函数声明和匿名函数表达式来说，[scope]就是它创建时的作用域
// b对于有名字的函数表达式，[scope]顶端是一个新的JS对象（也就是继承了Object.prototype），这个对象有两个属性，第一个是自身的名称，第二个是定义的作用域，第一个函数名称是为了确保函数内部的代码可以无误地访问自己的函数名进行递归。
// 3、执行环境与活动对象
// 语法分析完成，开始执行代码。我们调用每一个方法的时候，JS 引擎都会自动为其建立一个执行环境和一个活动对象，它们和方法实例的生命周期保持一致，为方法执行提供必要的执行支持，针对上面的几个方法，我们这里统一为其建立了活动对象（按道理是在执行方法的时候才会生成活动对象，为了便于演示，这里一下子定义了所有方法的活动对象），具体如下：
// 执行环境
/**
 * 执行环境:函数执行时创建的执行环境
 */
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

// 上面每一个方法的执行环境都存储了相应方法的类型（function）、方法名称（funcName）、活动对象（ActiveObject）、作用域链（scopeChain）等信息,
// 其关键点如下：
// body属性，直接指向当前方法的活动对象
// scopeChain属性，作用域链，它是一个链表结构，根据语法分析树中当前方法对应的scope属性，
// 它指向scope对应的方法的活动对象（ActivceObject），变量查找就是跟着这条链条查找的活动对象
/**
 * 活动对象：函数执行时创建的活动对象列表
 */
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

// 上面每一个活动对象都存储了相应方法的内部变量集（variables）、内嵌函数集（functions）、形参（parameters）、实参（arguments）等执行所需信息，活动对象关键点
// 创建活动对象，从语法分析树复制方法的内部变量集（variables）和内嵌函数集（functions）
// 方法开始执行，活动对象里的内部变量集全部被重置为 undefined
// 创建形参（parameters）和实参（arguments）对象，同名的实参，形参和变量之间是【引用】关系
// 执行方法内的赋值语句，这才会对变量集中的变量进行赋值处理
// 变量查找规则是首先在当前执行环境的 ActiveObject 中寻找，没找到，则顺着执行环境中属性 ScopeChain 指向的 ActiveObject 中寻找，一直到 Global Object（window）
// 方法执行完成后，内部变量值不会被重置，至于变量什么时候被销毁，请参考下面一条
// 方法内变量的生存周期取决于方法实例是否存在活动引用，如没有就销毁活动对象
// 6和7 是使闭包能访问到外部变量的根本原因
// 重释经典案例
// 案列一二三
// 根据【在一个方法中，同名的实参，形参和变量之间是引用关系，也就是JS引擎的处理是同名变量和形参都引用同一个内存地址】，所以才会有二中的修改arguments会影响到局部变量的情况出现
// 案例四
// 根据【JS引擎变量查找规则，首先在当前执行环境的 ActiveObject 中寻找，没找到，则顺着执行环境中属性 ScopeChain 指向的 ActiveObject 中寻找，一直到 Global Object（window）】，所以在四中，因为在当前的ActiveObject中找到了有变量 i 的定义，只是值为 “undefined”，所以直接输出 “undefined” 了
// 总结
// 以上是我在学习和使用了JS一段时间后,为了更深入的了解它, 也为了更好的把握对它的应用, 从而在对闭包的学习过程中,自己对于词法作用域的一些理解和总结,中间可能有一些地方和真实的JS解释引擎有差异,因为我只是站在一个刚入门的前端开发人员而不是系统设计者的角度上去分析这个问题，希望能对JS开发者理解此法作用域带来一些帮助！



