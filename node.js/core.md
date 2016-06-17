Node.js概念
=========

https://nodejs.org/en/

http://www.jb51.net/article/56022.htm
http://www.jb51.net/article/60488.htm
http://blog.csdn.net/yanghua_kobe/article/details/12145537

https://cnodejs.org/user/bigtree9307
https://cnodejs.org/user/LanceHBZhang

* Node.js® is a JavaScript runtime built on Chrome's V8 JavaScript engine. 
* Node.js uses an event-driven, non-blocking I/O model that makes it lightweight and efficient. 
* Node.js' package ecosystem, npm, is the largest ecosystem of open source libraries in the world.

### 进程退不退出本质上不是JS代码决定的，而是Node决定的，Node如何决定是不是需要退出，又是libuv决定的，libuv在进行事件循环，此处需要说明事件循环【图】。

### 事件驱动编程

理解事件循环，首先要理解事件驱动编程（Event Driven Programming）。它出现在1960年。如今，事件驱动编程在UI编程中大量使用。JavaScript的一个主要用途是与DOM交互，所以使用基于事件的API是很自然的。

简单地定义：事件驱动编程通过事件或状态的变化来进行应用程序的流程控制。一般通过事件监听实现，一旦事件被检测到（即状态改变）则调用相应的回调函数。听起来很熟悉？其实这就是Node.js事件循环的基本工作原理。

Node.js通过EventEmitter（事件发生器）触发这种模式，如在服务器端的Socket和“http”模块中。可以从一个单一实例触发一种或一种以上的状态改变。

EventEmitter经常表现地很异步，因为它经常用于通知需要异步完成的操作，但EventEmitter API本身是完全同步的。监听函数内部可以按异步执行，但请注意，所有的监听函数将按被添加的顺序同步执行。

### 机制概述和线程池

Node本身依赖多个库。其中之一是`libuv`，神奇的处理异步事件队列和执行的库。

Node利用尽可能多的利用操作系统内核实现现有的功能。像生成响应请求(request)，转发连接(connections)并委托给系统处理。例如，传入的连接通过操作系统进行队列管理，直到它们可以由Node处理。

您可能听说过，Node有一个线程池，你可能会疑惑：“如果Node会按次序处理任务，为什么还需要一个线程池？”这是因为在内核中，不是所有任务都是按异步执行的。在这种情况下，Node.JS必须能在操作时将线程锁定一段时间，以便它可以继续执行事件循环而不会被阻塞。

### 事件循环

### 事件驱动

### 异步IO

### 异步回掉

### 异步函数

`setTimeout`
`setInterval`
`setImmediate`
`api中IO相关函数`

### 模块系统
