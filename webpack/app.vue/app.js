'use strict'
let Vue = require('vue');

let VueRouter = require('vue-router');

Vue.use(VueRouter);

let App = Vue.extend({});

let router = new VueRouter();

router.map({
  '/' : {
  }
});

ruter.start(App, '#app');


