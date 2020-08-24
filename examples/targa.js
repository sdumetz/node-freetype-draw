//Takes an input string and outputs it as tga on stdout
//
const { program: p } = require('commander');
const {Renderer, fonts} = require("../lib");


function write_to_stdout(bytes){
  process.stdout.write(Buffer.isBuffer(bytes)? bytes : Buffer.from(bytes));
}



p
//  .option('-o --output <file>', 'output file. Default is "-" for stdout','-')
  .option('-t --text <text>', 'text to write','Hello world!')
  .option("-f --font", "Font name", "dejavu sans")
  .option('-w --width <number>', "window width", (v)=>parseInt(v, 10), 400)
  .option('-h --height <number>', "window height", (v)=>parseInt(v, 10), 300)
p.parse(process.argv);

const write = write_to_stdout;
const r = new Renderer({
  font: fonts["dejavu sans"],
  width: p.width,
  height: p.height,
  size: 64,
  pixFmt: "BGRA",
});
r.color = "#103040FF";
r.draw(p.text);


write([
  0x00, //ID length
  0x00, //no color map
  0x02, //Uncompressed true-color
  0x00, // color map specification (5 bytes)
  0x00,
  0x00,
  0x00,
  0x00,
  0x00, //X origin (lower-left corner)
  0x00, //X origin most significant byte
  p.height & 0xff, //Y origin (lower-left corner)
  (p.height >> 8) & 0xFF, //Y origin most significant byte
  p.width & 0xff, //width first byte
  (p.width >> 8) & 0xFF, //Width second byte
  p.height & 0xff, //height first byte
  (p.height >> 8) & 0xFF, //height second byte
  32, //Bits per pixel
  0b00101000, //bits 3-0 give the alpha channel depth, bits 5-4 give direction (Origin in upper left corner)
]);

//Image ID goes here
//Color map goes here

// The image data is stored bottom-to-top, left-to-right
let b = Buffer.allocUnsafe(p.width*p.height*3);

write(r.buffer);
