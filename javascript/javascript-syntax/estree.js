
var escope = require('escope');
var esprima = require('esprima');
var estraverse = require('estraverse');

var code = 'var answer = {v1:1, v2:2}; function f(){var a = answer;}';

var ast = esprima.parse(code);
var scopeManager = escope.analyze(ast);

var currentScope = scopeManager.acquire(ast);   // global scope

// console.dir(ast, {depth: null});
console.dir(scopeManager, {depth: null});
