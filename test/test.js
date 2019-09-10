const addon = require('bindings')('node-ctp');
const moment = require('moment');

const mdApi = new addon.WrapperMd();

let fontAddress = '';
mdApi.RegisterFront(fontAddress);
