'use strict';
const {join} = require("path");
const {promises:fs} = require("fs");
const FCP = require('fontconfig');

async function* walk(dir) {
  for await (const d of await fs.opendir(dir)) {
      const entry = join(dir, d.name);
      if (d.isDirectory()) yield* walk(entry);
      else if (d.isFile() && /\.ttf$/.test(d.name)) yield entry;
  }
}


// Then, use it with a simple async for loop
async function main() {
  const FontConfig = await FCP;
  const cfg = new FontConfig();

  for await (const p of walk('/usr/share/fonts'))
      cfg.addFont(p);
  console.log("Main font : ", cfg.sort({
    family: 'Open Sans',
    weight: FontConfig.FC_WEIGHT_LIGHT
  }).matches[0])
}

main();