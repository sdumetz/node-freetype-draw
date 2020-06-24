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
  describe("font properties", function(){
    let r;
    beforeEach(()=>{
      r = new Renderer();
    })
    it("has default color : black (opaque)", ()=>{
      expect(r.color).toEqual('#000000FF');
    })

    it(`can set color using hex code : "#103040"`, ()=>{
      r.color = "#103040"
      expect(r.color).toEqual('#103040FF');
    })
    it(`can set color using hex code : "103040"`, ()=>{
      r.color = "103040"
      expect(r.color).toEqual('#103040FF');
    })

    it(`can set color using hex code with alpha : "#10304066"`, ()=>{
      r.color = "#10304066"
      expect(r.color).toEqual('#10304066');
    })
    it(`can set color using hex code with alpha : "10304066"`, ()=>{
      r.color = "#10304066"
      expect(r.color).toEqual('#10304066');
    })
    it(`can set color using short hex code "#fff"`, ()=>{
      r.color = "#fff"
      expect(r.color).toEqual('#FFFFFFFF');
    })
    it(`can set color using short hex code "aaa"`, ()=>{
      r.color = "abc"
      expect(r.color).toEqual('#AABBCCFF');
    });

    it("properly handle invalid colors", ()=>{
      expect(()=>{
        r.color = "xxx";
      }).toThrow("Invalid argument : could not parse xxx");
      expect(()=>{
        r.color = undefined;
      }).toThrow("Invalid argument : could not parse undefined");
    })
  })

  describe("draw()", function(){
    let r;
    let s = 13;
    beforeEach(()=>{
      r = new Renderer({
        font: default_font,
        width: s,
        height: s,
        size: 16,
      });
    })

    // Provide a human-readable "view" of the bufffer that can be saved and inspected in snapshots
    function imageToText(b, channel=3 /*alpha*/){
      let res = [];
      for(let y=0; y < s ; y++){
        res[y] = [];
        for(let x=0; x < s ; x++){
          let idx = (y*s + x)*4;
          res[y][x] = (b[idx + channel] == 0) ? "  " : (b[idx + channel]).toString(16);
        }
      }
      return res.map(row=> row.join(" ")).join("\n");
    }

    it("draws a letter (H)", function(){
      r.draw("H", {x:0, y:s});
      expect(imageToText(r.buffer)).toMatchSnapshot();
    })

    it("draw non-ASCII letter (é)", function(){
      r.draw("é", {x:0, y:s});
      expect(imageToText(r.buffer)).toMatchSnapshot();
    })
    it("draw missing char (作)", function(){
      r.draw("作", {x:0, y:s});
      expect(imageToText(r.buffer)).toMatchSnapshot();
    })
    it("draw colored text (red)", function(){
      r.color ="#345";
      r.draw("é", {x:0, y:s});
      expect(imageToText(r.buffer, 0)).toMatchSnapshot();
    })
    it("draw colored text (green)", function(){
      r.color ="#345";
      r.draw("é", {x:0, y:s});
      expect(imageToText(r.buffer, 1)).toMatchSnapshot();
    })
    it("draw colored text (blue)", function(){
      r.color ="#345";
      r.draw("é", {x:0, y:s});
      expect(imageToText(r.buffer, 2)).toMatchSnapshot();
    })
  })

})