param(
    [Parameter(Mandatory=$false)]
    [Alias("s")]
    [string]$SourceFile,

    [Parameter(Mandatory=$false)]
    [Alias("m")]
    [ValidateSet("debug", "release")]
    [string]$BuildMode = "debug",

    [Parameter(Mandatory=$false)]
    [Alias("a")]
    [ValidateSet("x86", "x64")]
    [string]$Architecture = "x64"
)

if (!(Test-Path $SourceFile)) {
    Write-Host "Source file not found: $SourceFile"
    exit 1
}

# Get the base filename without extension
$SourceFileName = [System.IO.Path]::GetFileNameWithoutExtension($SourceFile)
$Outdir = ".\bin"
if (!(Test-Path $Outdir)) {
    New-Item -ItemType Directory -Path $Outdir | Out-Null
}
$OutFile = Join-Path $Outdir "$SourceFileName.exe"

# Read flags from file
$Flags = Get-Content "compile_flags.txt" |
    Where-Object { $_.Trim() -ne "" -and -not $_.StartsWith("//") } |
    ForEach-Object { $_.Trim().TrimEnd(',') } |
    Where-Object { $_ -ne "" }

# Add architecture flag
if ($Architecture -eq "x86") {
    $Flags += "-m32"
    Write-Host "Building for 32-bit (x86)..."
} else {
    $Flags += "-m64"
    Write-Host "Building for 64-bit (x64)..."
}

# Add build mode specific flags
if ($BuildMode -eq "debug") {
    $Flags += "-g"              # Debug symbols
    $Flags += "-O0"             # No optimization
    $Flags += "-DDEBUG"         # Define DEBUG macro
    #$Flags += "-fsanitize=address"
    #$Flags += "-fno-omit-frame-pointer"
    Write-Host "Building in DEBUG mode..."
} else {
    $Flags += "-O3"             # Maximum optimization
    $Flags += "-DNDEBUG"        # Define NDEBUG macro
    $Flags += "-flto"           # Link-time optimization
    Write-Host "Building in RELEASE mode..."
}

Write-Host "Compiling $SourceFile -> $OutFile"
Write-Host "Flags: $($Flags -join ' ')"

clang @Flags $SourceFile -o $OutFile

if ($LASTEXITCODE -eq 0) {
    Write-Host "Build succeeded!" -ForegroundColor Green
} else {
    Write-Host "Build failed!" -ForegroundColor Red
    exit $LASTEXITCODE
}
