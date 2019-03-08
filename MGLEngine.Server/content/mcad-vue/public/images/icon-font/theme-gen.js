"use strict";
exports.__esModule = true;
var fs = require("fs");
var path = require("path");
if (process.argv.length != 5) {
    console.log("Error parameters are");
    console.log("themegen {src folder} {dst Folder} color");
    console.log("Ex: themegen srcFolder dstFolder #000000ff");
    console.log(process.argv);
    process.exit(1);
}
var srcDir = process.argv[2];
var dstFolder = process.argv[3];
var color = process.argv[4];
console.log("Parameters: srcDir:" + srcDir + ", dstFolder: " + dstFolder + ", color: " + color);
var srcItems;
srcItems = fs.readdirSync(srcDir);
srcItems.forEach(function (file) {
    console.log("processing file " + file);
    fs.readFile(srcDir + "/" + file, { encoding: 'utf8' }, function (err, data) {
        if (err) {
            throw JSON.stringify(err);
            return;
        }
        var content = data.replace(/#000000/g, color);
        var dstFile = dstFolder + "/" + path.basename(file);
        console.log("writting file to " + dstFile);
        fs.writeFile(dstFile, content, function (err) { if (err)
            console.log("Error writing file " + dstFile + ": " + err.message); });
    });
});
