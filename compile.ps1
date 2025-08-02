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

# -fsanitize=address
clang -std=c23 -Wall -Werror -Wextra -Wsign-compare -xc -fuse-ld=lld $SourceFile -o $output