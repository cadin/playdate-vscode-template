const fs = require("fs");
const path = require("path");
const os = require("os");
const { exec } = require("child_process");
const process = require("process");

let sdkRoot = null;

let configPath = path.resolve(os.homedir(), ".Playdate", "config");
let configText = fs.readFileSync(configPath, "utf8");
let configLines = configText.split("\n");
configLines.forEach((line) => {
  let components = line.split("\t");
  if (components[0] == "SDKRoot") {
    sdkRoot = components[1];
  }
});

if (sdkRoot == null) {
  throw new Error("No SDK Root");
}

let simulatorPath = path.resolve(sdkRoot, "bin", "Playdate Simulator.app");
exec(`/usr/bin/open -a \"${simulatorPath}\" \"${path.resolve(process.cwd(), process.env["PLAYDATE_OUTPUT"])}\"`);
