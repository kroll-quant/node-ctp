console.log('p0');
const addon = require('bindings')('nodeCtp');
const process = require('process');
console.log('p1');
const cbFunc= {
    OnFrontConnected: () => {
        console.log(`cbFunc OnFrontConnected`);
    },
    OnFrontDisconnected: (nReason) => {
        console.log(`cbFunc OnFrontDisconnected nReason: ${nReason}`);
    },
    OnHeartBeatWarning: (nTimeLapse)=>{
        console.log(`cbFunc OnHeartBeatWarning nTimeLapse: ${nTimeLapse}`);
    },
    OnRspUserLogin: (rspField, rspInfo, requestId, isLast)=>{

    }
};
const mdApi = new addon.WrapperMd(cbFunc.OnFrontConnected);
console.log('p2');
let fontAddress = 'tcp://180.168.146.187:10111';
console.log('p3');
mdApi.RegisterFront(fontAddress);
console.log('p4');

//防止mdApi被回收
setInterval(() => {mdApi}, 1 << 30);

