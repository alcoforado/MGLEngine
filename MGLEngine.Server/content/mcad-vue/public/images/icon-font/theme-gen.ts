import * as  fs from 'fs';
import * as path from 'path'

if (process.argv.length!=5)
{
    console.log("Error parameters are")
    console.log("themegen {src folder} {dst Folder} color")
    console.log("Ex: themegen srcFolder dstFolder #000000ff")
}

var srcDir = process.argv[2];
var dstFolder = process.argv[3];
var color = process.argv[4];
var srcItems:string[];
srcItems=fs.readdirSync(srcDir)


srcItems.forEach(function(file){
    console.log(`processing file ${file}`);
    fs.readFile(file,{encoding:'utf8'},function(err,data:string)
    {
        var content = data.replace("#000000ff",color);
        var dstFile = dstFolder+"/"+path.basename(file);
        console.log(`writting file to ${dstFile}`)
        fs.writeFile(dstFile,content,(err)=> {if (err) console.log(`Error writing file ${dstFile}: ${err.message}`);})
    })
})
