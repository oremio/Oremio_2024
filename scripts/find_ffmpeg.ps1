$paths = $env:PATH -split ';'
foreach ($path in $paths) {
    if (-not [string]::IsNullOrWhiteSpace($path) -and (Test-Path $path)) {
        $ffmpegPath = Join-Path -Path $path -ChildPath 'ffmpeg.exe'
        if (Test-Path $ffmpegPath) {
            Write-Output $ffmpegPath
        }
    }
}
