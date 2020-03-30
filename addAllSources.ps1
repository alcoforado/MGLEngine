param (
    [Parameter(Mandatory=$True)]
    [string]$root,
    [int]$nCols=130  
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
$count=0;
foreach($file in $files){
    $add="""$file"" "
    $count+=$add.Length;
    if ($count -ge $nCols)
    {
        $count=$add.Length;
        $CMakeExpr+="`n" #break line
    }
    $CMakeExpr+= $add;
}
$CMakeExpr+=")"
return $CMakeExpr;