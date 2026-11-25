$ErrorActionPreference = 'Stop'
Set-Location (Split-Path -Parent $PSScriptRoot)
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes src\*.c -o build.exe
if ($LASTEXITCODE -ne 0) { throw 'GCC build failed' }

# First-round choice is manual. Numeric entries handle tie-break prompts and are
# consumed as invalid pause choices until P activates the automatic remainder.
$inputs = @('1', 'SmokeP1', 'SmokeP2', '1', '1', '')
for ($i = 0; $i -lt 50; $i++) { $inputs += [string](1 + ($i % 4)) }
$inputs += 'P'
$inputs += '0'
$output = ($inputs -join "`n") | .\build.exe
$outputText = $output | Out-String
if ($LASTEXITCODE -ne 0) { throw "Game exited with code $LASTEXITCODE" }
if (-not $outputText.Contains('RODADA 1 | Escolha de')) { throw 'First manual round was not reached' }
if (-not $outputText.Contains('Sorteio inicial: SmokeP1')) { throw 'Initial draw did not display Player 1 name' }
if (-not $outputText.Contains('SIMULACAO AUTOMATICA ATIVADA')) { throw 'Simulation activation was not reached' }
$simulationText = $outputText.Substring($outputText.IndexOf('SIMULACAO AUTOMATICA ATIVADA'))
$simulatedAttributes = [regex]::Matches($simulationText, 'Atributo escolhido: ([^=]+) =') | ForEach-Object { $_.Groups[1].Value.Trim() } | Select-Object -Unique
if ($simulatedAttributes.Count -lt 2) { throw 'Simulation did not demonstrate random attribute variety' }
if (-not $outputText.Contains('CAMPEAO:')) { throw 'Winner output not found' }
if (-not $outputText.Contains('Total de cartas: 34')) { throw 'Winner did not receive all 34 cards' }
if (-not $outputText.Contains('Obrigado por jogar SuperTrunfIA')) { throw 'Exit menu flow not reached' }
# EOF during setup must return to the menu and exit, not loop forever.
$eofInputs = @('1', 'EOF_P1', 'EOF_P2')
$eofOutput = ($eofInputs -join "`n") | .\build.exe
$eofText = $eofOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $eofText.Contains('Obrigado por jogar SuperTrunfIA')) { throw 'EOF setup handling failed' }
$invalidMenu = @('9', '0')
$invalidOutput = ($invalidMenu -join "`n") | .\build.exe
$invalidText = $invalidOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $invalidText.Contains('Entrada invalida')) { throw 'Invalid menu option handling failed' }
Remove-Item build.exe -ErrorAction SilentlyContinue
Write-Output 'MANUAL FIRST ROUND + AUTO SIMULATION + EOF SMOKE: PASS'
