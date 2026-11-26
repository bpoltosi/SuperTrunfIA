$ErrorActionPreference = "Stop"
$repoRoot = Split-Path -Parent $PSScriptRoot
$buildPath = Join-Path $repoRoot "build.exe"
$testPath = Join-Path $PSScriptRoot "test_refactors.exe"
$inputPath = Join-Path $PSScriptRoot "smoke_input.txt"
$outputPath = Join-Path $PSScriptRoot "smoke_output.txt"

Push-Location $repoRoot
try {
    gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes src\*.c -o $buildPath
    if ($LASTEXITCODE -ne 0) { throw "Falha na compilacao do aplicativo." }

    gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes tests\test_refactors.c src\jogo.c src\carta.c src\jogador.c src\baralho.c src\interface.c src\util.c -o $testPath
    if ($LASTEXITCODE -ne 0) { throw "Falha na compilacao dos testes automatizados." }

    & $testPath
    if ($LASTEXITCODE -ne 0) { throw "Os testes automatizados falharam." }

    @("1", "Alice", "Bob", "1", "1", "P", "0") | Set-Content $inputPath
    Get-Content $inputPath | & $buildPath 2>&1 | Out-File -FilePath $outputPath -Encoding utf8
    if ($LASTEXITCODE -ne 0) { throw "Falha durante o smoke test da partida." }

    $output = Get-Content $outputPath -Raw
    if (!$output.Contains("Sorteio inicial: Alice")) { throw "O sorteio inicial nao exibiu o nome do primeiro jogador." }
    if (!$output.Contains("RODADA 1 |")) { throw "A primeira rodada nao foi executada." }
    if (!$output.Contains("Atributo: ") -or $output.IndexOf("Atributo: ") -gt $output.IndexOf("SIMULACAO AUTOMATICA ATIVADA")) { throw "A primeira rodada nao foi comprovadamente manual." }
    if (!$output.Contains("SIMULACAO AUTOMATICA ATIVADA")) { throw "A opcao P nao ativou a simulacao." }
    if (!$output.Contains("CAMPEAO:") -and !$output.Contains("PARTIDA ENCERRADA EM EMPATE")) { throw "A simulacao nao chegou ao encerramento da partida." }

    Write-Output "Smoke test: primeira rodada manual, pausa P e simulacao ate o fim passaram."
}
finally {
    Remove-Item $buildPath, $testPath, $inputPath, $outputPath -Force -ErrorAction SilentlyContinue
    Pop-Location
}
