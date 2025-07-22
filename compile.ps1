param(
    [Parameter(Mandatory=$true)]
    [string]$SourceFile
)

if (!(Test-Path $SourceFile)) {
    Write-Host "Source file not found: $SourceFile"
    exit 1
}

# Get the base filename without extension
$base = [System.IO.Path]::GetFileNameWithoutExtension($SourceFile)
$outdir = ".\target"
if (!(Test-Path $outdir)) {
    New-Item -ItemType Directory -Path $outdir | Out-Null
}

$output = Join-Path $outdir "$base.exe"

# clang -std=c23 -Wall -Werror -xc -fuse-ld=lld -fsanitize=address $SourceFile -o $output
# clang -std=c23 -Wall -Werror -xc -fsanitize=address $SourceFile -o $output
clang -std=c23 -Wall -Werror -xc -fuse-ld=lld $SourceFile -o $output