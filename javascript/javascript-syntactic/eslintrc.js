module.exports = {
  env: {
    browser: {
        es6: true
    },
    node: {
        es6: true
    },
    es6: true
  },
  rules: {
    // Possible Errors部分
    // 不允许在对象字面量和数组字面量的末尾出现`,`
    'comma-dangle': 2,

    // 不允许在布尔上下文中使用赋值表达式
    // 「待商议」是一律不允许（always）还是只允许用()包裹的赋值表达式（except-parens）
    // 个人建议允许用()包裹的赋值表达式（except-parens）
    'no-cond-assign': [2, 'except-parens'],

    // 对使用console进行警告。
    // 在生产环境中禁止使用console
    'no-console': 1,

    // 在布尔上下文中使用字面值时警告
    // 「待商议」是报错还是警告
    'no-constant-condition': 1,

    // 不允许在正则表达式中出现控制字符
    'no-control-regex': 2,

    // 对使用debugger报错
    // 「待商议」是报错还是警告
    // 个人建议报错，因为debugger并不是一个好的调试方法，在dev tools中直接打断点会好一些
    'no-debugger': 2,

    // 不允许同名参数
    'no-dupe-args': 2,

    // 不允许在对象中出现同名属性
    'no-dupe-keys': 2,

    // 不允许在switch语句中出现重复的case标签
    'no-duplicate-case': 2,

    // 不允许在正则表达式中使用空的字符集（`[]`）
    'no-empty-character-class': 2,

    // 不允许空的语句块
    'no-empty': 2,

    // 不允许在`try...catch`的`catch`块中赋值给异常参数
    'no-ex-assign': 2,

    // 不允许在布尔上下文中（使用`!!`）进行多余的布尔值类型转换。
    'no-extra-boolean-cast': 2,

    // 不允许使用多余的()
    'no-extra-parens': 2,

    // 不允许多余的分号
    'no-extra-semi': 2,

    // 不允许给函数声明定义的函数变量进行赋值操作
    'no-func-assign': 2,

    // 不允许在语句块中进行函数声明
    // ES6中有了对块级作用域的支持，但是函数声明并不是语句；另外实际结果是ES6中函数声明会被限制在声明的块中
    'no-inner-declarations': 2,

    // 不允许无效的正则表达式
    'no-invalid-regexp': 2,

    // 不允许使用非常规空白字符
    // 关于非常规空白字符请查看：http://eslint.org/docs/rules/no-irregular-whitespace
    'no-irregular-whitespace': 2,

    // 不允许对`in`操作符的左操作数取反
    // for ( !key in obj ) 的本意通常是 for ( !(key in obj) )
    'no-negated-in-lhs': 2,

    // 不允许以函数形式调用全局对象Math和JSON，因为它们只是提供了一个命名空间
    'no-obj-calls': 2,

    // 不允许在正则表达式中连续使用多个空格，使用数量元字符
    'no-regex-spaces': 2,

    // 不允许使用稀疏数组直接量
    'no-sparse-arrays': 2,

    // 不允许不合理（unexpected）的多行表达式
    'no-unexpected-multiline': 2,

    // 不允许出现永远不会被执行的代码
    // return、throw、break或者continue后面代码可能永远不会执行
    'no-unreachable': 2,

    // 使用`isNaN`方法，而不是使用比较操作符和`NaN`进行比较
    'use-isnan': 2,

    // 使用有效的JSDoc注释
    'valid-jsdoc': 2,

    // 保证`typeof`的结果是和有效的类型字符串进行比较
    'valid-typeof': 2,

    // best practice部分
    // 如果不会用到访问器属性则不需要设置
    'accessor-pairs': 2,

    // 按块级作用域使用var，同时就近声明变量
    'block-scoped-var': 2,

    // 复杂性 「待商议」高级话题
    complexity: [0, 11],

    // 强制不同分支使用一致的返回值
    // 「待商议」能够执行自然是好，只是有些严格，而且还不确定是否适合所有场景
    'consistent-return': 1,

    // 总是使用代码块，即使只有一条语句。
    curly: 2,

    // 强制switch语句中始终添加default分支
    'default-case': 2,

    // 总是优先使用点操作符访问属性，同时允许使用点操作符访问保留字属性
    'dot-notation': [2, { 'allowKeywords': true}],

    // 统一点操作符和属性名在同一行，点操作符出现在一行的开始
    'dot-location': [2, "property"],

    // 总是使用===
    eqeqeq: 2,

    // 总是在for...in中使用hasOwnProperty进行检测
    'guard-for-in': 2,

    // 对alert、prompt和confirm进行警告
    'no-alert': 1,

    // 不允许使用arguments.caller/callee
    'no-caller': 2,

    // 不允许在case分支中进行变量声明、函数声明和类声明。因为它们只在相关分支执行时才会被执行
    'no-case-declarations': 2,

    // 是否允许疑似除法运算的正则表达式，即第一个字符是等号的正则表达式直接量`var re = /=foo/;`
	'no-div-regex': 0,

    // 不允许在包含return的if块后使用else块
    'no-else-return': 2,

    // 不允许使用空的label
    'no-empty-label': 2,

    // 是否允许和null进行相等判断
    // 「待商议」个人建议不允许
    'no-eq-null': 2,

    // 不允许使用eval
    'no-eval': 2,

    // 不允许扩充内置对象
    'no-extend-native': 2,

    // 不允许使用bind进行没有必要的this绑定
    'no-extra-bind': 2,

    // switch中不允许使用fall through
    'no-fallthrough': 2,

    // 不允许省略浮点数中小数点前后的数字
    'no-floating-decimal': 2,

    // 是否允许隐式类型转换
    // 个人建议可以考虑，它们的可读性更强。但是也要繁琐一些，毕竟`!!`、`'' + foo`和`+foo`等还是比较好用的
    'no-implicit-coercion': 0,

    // 不允许给setTimeout和setInterval传递字符串作为第一个参数，它们是另一种形式的eval
    'no-implied-eval': 2,

    // 是否允许不必要的this，即是否只允许在类或者class like的对象中使用
    // 「待商议」在构建可重用的方法时也可能用到，结合call和apply和写出更灵活的代码
    // 个人建议添加这条规则，并且在非类的情况下使用是在jsDoc中添加@this注释（这种情况下也不会报错），这样可以最大化可读性
    'no-invalid-this': 2,

    // 不允许使用SpiderMonkey引擎对JavaScript的扩展__iterator__
    'no-iterator': 2,

    // 不允许使用label
    'no-labels': 2,

    // 不允许使用单独的代码块
    'no-lone-blocks': 2,

    // 不允许在循环中定义函数，更具体的说是不允许在循环中定义的函数引用外层作用域的变量
    // 对于最常见的情况，使用let而不是var声明循环变量就可以了
    'no-loop-func': 2,

    // 不允许出现神奇数字，数字要使用有意义的变量
    'no-magic-numbers': 2,

    // 不允许出现多个连续的空格
    'no-multi-spaces': 2,

    // 不允许使用\来拼接字符串
    'no-multi-str': 2,

    // 不允许向内置对象进行赋值操作
    'no-native-reassign': 2,

    // 不允许以利用副作用的方式来使用`new`操作符。
    'no-new': 2,

     // 不允许使用new Function，new Function是另一种形式的eval
    'no-new-func': 2,

    // 不允许使用`new`操作符调用直接量包裹构造函数来创建直接量
    'no-new-wrapper': 2,

    // 不允许使用八进制字面值
    'no-octal': 2,

    // 不允许使用八进制转义序列
    'no-octal-escape': 2,

    // 不允许函数参数进行赋值操作，包括参数的属性
    'no-param-reassign': [1, { 'props': true }],

    // 是否允许使用process.env
    // 「待商议」node相关
    'no-process-env': 0,

    // 不允许使用`__proto__`
    'no-proto': 2,

    // 不允许（在同一个作用域内）声明同名变量。
    'no-redeclare': 2,

    // 不允许在`return`语句中使用赋值表达式
    'no-return-assign': 2,

    // 不允许使用脚本URL
    'no-script-url': 2,

    // 不允许一个值和它自身进行比较
    'no-self-compare': 2,

    // 不允许使用逗号操作符`,`在一个语句中包含多个表达式
    'no-sequences': 2,

    // 限制异常抛出的内容：Error对象或者基于Error的对象
    'no-throw-literal': 2,

    // 不允许出现没有被使用的表达式
    'no-unused-expressions': 2,

    // 不允许不必要的`call`和`apply`
    'no-useless-call': 2,

    // 是否允许使用void
    // 「待商议」void是undefined的变体，建议只使用undefined
    'no-void': 1,

    // 是否允许使用提醒注释
    'no-warning-comments': [0, { 'terms': ['todo', 'fixme', 'xxx'], 'location': 'start' }],

    // 不允许使用with
    'no-with': 2,

    // 总是给parseInt提供第二个参数
    // 前后端区分
    'radix': 1,

    // 是否总是在顶部声明所有的变量。
    'vars-on-top': 2,

    // 总是使用()包裹IIFE
    // 「待商议」具体使用哪一种风格。个人倾向于`(function () {})()`
    'wrap-iife': [2, 'any'],

    // 是否要求使用yoda表达式。
    'yoda': 0,

    // Strict Mode部分
    // 总是使用严格模式
    strict: [2, 'global'],

    // variables部分
    // 是否统一在声明变量是一致进行初始化或者一律不允许初始化
    // 「待商议」个人建议不做统一
    'init-declarations': 0,

    // 不允许出现和catch的异常变量同名的变量名，主要是考虑到目前还要兼容IE8
    'no-catch-shadow': 2,

    // 不允许对变量使用delete
    'no-delete-var': 2,

    // 「待商议」因为不允许使用标记，所以不用检测这一项
    'no-label-var': 0,

    // 不允许使用和限制名相同的变量名
    'no-shadow-restricted-names': 2,

    // 不允许作用域链中出现同名的变量
    'no-shadow': 2,

    // 不允许初始化变量为undefined。因为不进行初始化，会默认初始化为undefined
    'no-undef-init': 2,

    // 不允许使用未经声明的变量
    'no-undef': 2,

    // 是否允许使用undefined
    'no-undefined': 1,

    // 不允许声明没有被使用的变量。全局变量允许，同时参数只有最后一个需要被使用
    // 「待商议」使用模块化后可以完全不允许声明没有被使用的变量（？？）
    'no-unused-vars': [2, {vars: 'local', args: 'after-used'}],

    // 不允许在声明之前使用变量
    'no-use-before-define': 2,

    // node.js部分
    // 强制把回调放在`return`语句中
    // 「待商议」符合error-first回调的原则
    'callback-return': 2,

    // 强制在模块的顶层使用`require`加载所有模块
    'global-require': 2,

    // 强制在回调中处理错误。与airbnb不同
    'handle-callback-err': 2,

    // 是否强制所有模块加载放在一起，同时按类型分块
    'no-mixed-requires': [2, true],

    // 不允许使用`new`调用`require`的模块。与airbnb不同
    'no-new-require': 2,

    // 禁止在使用`__dirname`和`__filename`时使用字符串拼接来创建路径。与airbnb不同
    'no-path-concat': 2,

    // 是否允许使用process.exit
    'no-process-exit': 2,

    // 是否限制使用某些模块
    'no-restricted-modules': 0,

    // 是否允许使用同步模块
    'no-sync': 0,

    // style部分
    // 数组[]内侧不允许添加空格
    'array-bracket-spacing': [2, 'never'],

    // 始终使用代码块，且代码块的{不出现在行首
    'brace-style': [2, '1tbs', {'allowSingleLine': false }],

    // 使用驼峰命名法，无论是变量名还是属性名
    'camelcase': [2, {'properties': 'always'}],

    // 在,后面添加空格
    'comma-spacing': [2, {'before': false, 'after': true}],

    // 在,之后换行
    'comma-style': [2, 'last'],

    // 「待商议」不允许计算属性中添加空格。计算熟悉不要使用方括号语法访问属性
    'computed-property-spacing': [2, 'never'],

    // 统一使用词法this，并且使用context作为变量名。
    // 「待商议」保证this正确有两种方法：词法this，包括使用变量存储和箭头函数；使用bind
    'consistent-this': 2,

    // 非空文件以换行符结尾
    'eol-last': 2,

    // 要求始终使用命名函数表达式，警告
    // 「待商议」有时给函数表达式起名比较繁琐
    'func-names': 1,

    // 「待商议」是否统一定义函数的方式：函数声明或者函数表达式
    'func-style': 0,

    // 是否限制标志符的长度
    // 「待商议」目前并没有这方面的需求，也难以给出一个合适的数字
    'id-length': 0,

    // 缩进使用两个空格
    // 「待商议」在一些语句中可以做一些调整，以增强可读性。
    indent: [2, 2, { SwitchCase: 2, VariableDeclarator: {'var': 2, 'let': 2, 'const': 4}}],

    // jsx中的引号，不会被用到
    'jsx-quotes': [2, 'prefer-double'],

    // 对象字面值，统一在冒号后面添加一个空格，冒号前面不允许有空格
    'key-spacing': [2, {'beforeColon': false, 'afterColon': true}],

    // 是否统一在注释前后添加一个空行
    // 「待商议」
    'lines-around-comment': 0,

    // 不允许混用两种换行符'LF'和'CRLF'
    // 「待商议」建议不混用
    'linebreak-style': 0,

    // 指定一行的最大字符数
    // 「待商议」80， 100 还是120
    // https://github.com/eslint/eslint/blob/master/docs/rules/max-len.md
    'max-len': [2, 100, 2, {
      'ignoreUrls': true,
      'ignoreComments': false
    }],

    // 指定最大回调嵌套层数
    // 「待商议」目前并没有这方面的需求，也难以给出一个合适的数字
    'max-nested-callbacks': 0,

    // 强制构造函数首字母大写
    'new-cap': [2, {'newIsCap': true}],

    // 是否允许当构造函数没有参数时省略()进行调用
    // 「待商议」
    'new-parens': 0,

    // 是否允许在声明之后添加一个空行
    // 「待商议」建议添加
    'newline-after-var': 0,

    // 是否允许使用Array来创建数组
    // 「待商议」唯一的例外是可以使用new Array创建一定长度的由某些字符重复构成的字符串，相当于ES6字符串的repeate的方法
    'no-array-constructor': 0,

    // 是否允许使用continue
    // 「待商议」不建议使用
    'no-continue': 0,

    // 是否允许在一行的末尾添加注释
    // 「待商议」添加更方便，而且在显示结果时很好用，但是降低了可维护性，不建议使用
    'no-inline-comments': 0,

    // 不允许else块只有一个单独的if块
    'no-lonely-if': 2,

    // 不允许混用空格和制表符
    'no-mixed-spaces-and-tabs': 2,

    // 不允许多个连续空行，最多连续的空行数为2，文档末尾最多1个空行
    'no-multiple-empty-lines': [2, {'max': 2, 'maxEOF': 1}],

    // 是否允许在布尔上下文中使用取反操作符`!`，可以通过调整语句块或者表达式的顺序完全避免`！`
    // 「待商议」可以考虑
    'no-negated-condition': 0,

    // 不允许使用嵌套的三元操作符
    'no-nested-ternary': 2,

    // 不允许使用Object构造函数创建对象
    'no-new-object': 2,

    // 是否允许是否++和--
    'no-plusplus': 0,

    // 是否要禁用一些语法特性
    'no-restricted-syntax': 0,

    // 不允许函数调用时在函数名和()之间添加空格
    'no-spaced-func': 2,

    // 是否允许使用三元操作符
    'no-ternary': 0,

    // 不允许在行尾出现空白字符
    'no-trailing-spaces': 2,

    // 是否允许变量名以下划线开始或结尾
    'no-underscore-dangle': 0,

    // 不允许使用可以被简化的三元操作符
    'no-unneeded-ternary': 2,

    // 统一在对象字面值中紧贴{}是否添加一个空格
    'object-curly-spacing': [2, 'always'],

    // 一个变量对应一个var
    'one-var': [2, 'never'],

    // 统一对复合赋值操作符的使用
    'operator-assignment': 0,

    // 统一拆分过长表达式时操作符的位置
    'operator-linebreak': [2, 'before'],

    // 不允许在代码块的开始和结尾添加空行
    'padded-blocks': [2, 'never'],

    // 对象属性名引号的添加情况
    'quote-props': [2, 'as-needed', { 'keywords': false, 'unnecessary': true, 'numbers': false }],

    // 字符串统一使用单引号包裹，当为了避免转义时可以使用双引号
    'quotes': [2, 'single', 'avoid-escape'],

    // 是否统一标志符满足某个模式
    // 「待商议」目前并没有这方面的需求，也难以给出一个合适的模式
    'id-match': 0,

    // 当`;`出现在表达式中间时，统一在它的后面添加一个空格，前面不允许有空格
    'semi-spacing': [2, {'before': false, 'after': true}],

    // 总是使用`;`
    'semi': [2, 'always'],

    // 不要求对声明的变量按字母顺序进行排序
    'sort-vars': 0,

    // 强制在特定关键字前添加一个空格
    'space-before-keywords': [2, 'always'],

    // 强制在特定关键字后添加一个空格
    'space-after-keywords': [2, 'always'],

    // 统一是否在代码块的左括号前面添加空格
    'space-before-blocks': 2,

    // 命名函数表达式()前面不允许有空格，匿名函数表达式()前面要添加一个空格
    // https://github.com/eslint/eslint/blob/master/docs/rules/space-before-function-paren.md
    'space-before-function-paren': [2, { 'anonymous': 'always', 'named': 'never' }],

    // 不允许在()内侧添加空格
    'space-in-parens': 0,

    // 强制在中缀操作符两侧添加一个空格
    'space-infix-ops': 2,

    // 强制在return、throw和case后面添加一个空格
    'space-return-throw-case': 2,

    // 统一一元操作符中空格的使用
    'space-unary-ops': [2, { "words": true, "nonwords": false }],

    // 强制在注释前添加一个空格，除了一些标志注释之外
    'spaced-comment': [2, 'always', {
      'exceptions': ['-', '+'],
      'markers': ['=', '!']           // space here to support sprockets directives
    }],

    // 是否统一包裹正则表达式
    // 「待商议」建议不做统一，视情况而定是否添加
    'wrap-regex': 0,

    // ES6部分
    // 「待商议」统一箭头函数中函数体对`{}`的使用。建议只在需要的时候添加
    'arrow-body-style': [2, 'as-needed'],

    // 「待商议」统一箭头函数中函数参数对`()`的使用。建议总是使用
    'arrow-parens': [2, 'always'],

    // 强制在箭头函数的箭头前面和后面添加一个空格
    // https://github.com/eslint/eslint/blob/master/docs/rules/arrow-spacing.md
    'arrow-spacing': [2, { 'before': true, 'after': true }],

    // 验证类定义中`super()`的使用
    'constructor-super': 2,

    // 「待商议」统一generator中`*`前后空格的使用
    'generator-star-spacing': [2, {"before": false, "after": true}],

    // 在布尔上下文中，不允许使用箭头函数
    'no-arrow-condition': 2,

    // 不允许修改类声明创建的变量
    'no-class-assign': 2,

    // 不允许对`const`声明的变量进行重新赋值
    'no-const-assign': 2,

    // 不允许在类声明中出现重复的成员名
    'no-dupe-class-members': 2,

    // 在类声明的`constructor`中，不允许在执行`super()`之前使用`this`和`super`
    'no-this-before-super': 0,

    // 强制使用`const`和`let`，不允许使用`var`
    'no-var': 2,
    // 强制使用简洁的对象字面值语法
    // https://github.com/eslint/eslint/blob/master/docs/rules/object-shorthand.md
    'object-shorthand': [2, 'always'],

    // 优先使用箭头函数而不是函数表达式声明回调函数
    'prefer-arrow-callback': 2,

    // 优先使用`const`
    'prefer-const': 2,

    // 「待商议」在可用的情况先优先使用Reflect方法
    'prefer-reflect': 0,

    // 优先使用spread操作符而不是`apply`方法
    'prefer-spread': 2,

    // 优先使用模板字符串，而不是字符串拼接
    'prefer-template': 2,

    // 不允许使用不含有`yield`关键字的generator
    'require-yield': 2
};

var obj = {

}

{
    a: obj.a,
    b: obj.b,
    c: obj.c
}

var obj2 = {obj.a, obj.b, obj.c};
util.f(obj, a, b, c);
