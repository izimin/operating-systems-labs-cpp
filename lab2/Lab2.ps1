$a = Read-Host "Введите путь к директории"
$b = Read-Host "Введите название поддиректории"
$b = $a+"\"+$b
if ((Test-Path $b) -ne "True") {md -Path $b}
Get-ChildItem $a|where {$_.Name -match "\d" -and $_.Mode -ne "d-----"}|Move-Item -Destination $b