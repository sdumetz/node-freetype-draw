var binary = require('node-pre-gyp');
var path = require('path');
var binding_path = binary.find(path.resolve(__dirname,'../package.json'));

module.exports = require(binding_path);