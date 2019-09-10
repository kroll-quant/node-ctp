const addon = require('bindings')('nodeCtp');
const moment = require('moment');

const mdApi = new addon.WrapperMd();

let fontAddress = '';
mdApi.RegisterFront(fontAddress);
