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
    let s = 13;
    beforeEach(()=>{
      r = new Renderer({
        font: default_font,
        width: s,
        height: s,
      });
    })

    // Provide a human-readable "view" of the bufffer that can be saved and inspected in snapshots
    function imageToText(b){
      let res = [];
      for(let y=0; y < s ; y++){
        res[y] = [];
        for(let x=0; x < s ; x++){
          let idx = (y*s + x)*4;
          res[y][x] = ((b[idx] + b[idx+1] + b[idx+2])/4) == 0 ? " " : "X";
        }
      }
      return res;
    }

    it("draws a letter (H)", function(){
      r.draw("H", {x:0, y:s});
      expect(imageToText(r.buffer).map(row=> row.join(" ")).join("\n")).toMatchSnapshot();
    })

    it("draw non-ASCII letter (é)", function(){
      r.draw("é", {x:0, y:s});
      expect(imageToText(r.buffer).map(row=> row.join(" ")).join("\n")).toMatchSnapshot();
    })
    it("draw missing char (作)", function(){
      r.draw("作", {x:0, y:s});
      expect(imageToText(r.buffer).map(row=> row.join(" ")).join("\n")).toMatchSnapshot();
    })
  })

})