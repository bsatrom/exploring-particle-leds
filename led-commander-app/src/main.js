import Vue from 'nativescript-vue';

import RGBController from './components/RGBController';

import './styles.scss';

Vue.config.silent = false;

new Vue({
  render: h => h(RGBController)
}).$start();
