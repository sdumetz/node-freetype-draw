'use strict';
const {Renderer} = require(".");
const {resolve} = require("path");

const default_font = resolve(__dirname, "fonts/DejaVuSans.ttf");
describe("Renderer", ()=>{

  it("can be initialized", ()=>{
    expect(()=> new Renderer({})).not.toThrow();
  });

  it("can be opened with a font", ()=>{
    expect(()=> new Renderer({font: default_font})).not.toThrow();
  });

  it("throw an error if it can not find requested font",()=>{
    expect(()=> new Renderer({font: "/to/foo.ttf"})).toThrow();
  })

  describe("draw()", function(){
    let r;
    beforeEach(()=>{
      r = new Renderer({
        font: default_font,
        width: 20,
        height: 20,
      });
    })

    it("can draw to its buffer", function(){
      r.draw("H");
    });

  })
})