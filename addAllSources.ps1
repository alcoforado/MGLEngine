param (
    [Parameter(Mandatory=$True)]
    [string]$root 
)

if (-not (Test-Path  -Path $root)) {    
throw "Error directory does not exist"
}

#get the full path of the root
$rootDir = get-item -Path $root
$fp=$rootDir.FullName;


$files = Get-ChildItem -Path $root -Recurse -File | 
         Where-Object { ".cpp",".cxx",".cc",".h" -contains $_.Extension} | 
         Foreach {$_.FullName.replace("${fp}\","").replace("\","/")}

$CMakeExpr = "set(SOURCES "

foreach($file in $files){

    $CMakeExpr+= """$file"" " ;
}
$CMakeExpr+=")"
return $CMakeExpr;