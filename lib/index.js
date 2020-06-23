var binary = require('node-pre-gyp');
var path = require('path');
var binding_path = binary.find(path.resolve(__dirname,'../package.json'));

const {Renderer} = require(binding_path);


module.exports = {
  Renderer,
  fonts: {
    "dejavu sans": path.resolve(__dirname, "fonts/DejaVuSans.ttf"),
  }
}