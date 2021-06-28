var path = require('path');
const {Renderer} = require('node-gyp-build')(path.resolve(__dirname,'..'));

module.exports = {
  Renderer,
  fonts: {
    "dejavu sans": path.resolve(__dirname, "fonts/DejaVuSans.ttf"),
  }
}