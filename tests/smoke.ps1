$ErrorActionPreference = 'Stop'
Set-Location (Split-Path -Parent $PSScriptRoot)
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -Iincludes src\*.c -o build.exe
if ($LASTEXITCODE -ne 0) { throw 'GCC build failed' }

# First-round choice is manual; Enter advances and P activates the automatic remainder.
$inputs = @('1', 'SmokeP1', 'SmokeP2', '1', '1', '')
for ($i = 0; $i -lt 50; $i++) { $inputs += [string](1 + ($i % 4)) }
$inputs += 'P'
$inputs += '0'
$output = ($inputs -join "`n") | .\build.exe
$outputText = $output | Out-String
if ($LASTEXITCODE -ne 0) { throw "Game exited with code $LASTEXITCODE" }
if (-not $outputText.Contains('RODADA 1 |') -or -not $outputText.Contains('deve escolher o atributo')) { throw 'First manual round did not identify the choosing player before the prompt' }
$choiceHeaders = [regex]::Matches($outputText, 'RODADA \d+ \| .*deve escolher o atributo')
if ($choiceHeaders.Count -lt 2) { throw 'Next-round chooser was not displayed after the manual Enter transition' }
if (-not $outputText.Contains('Sorteio inicial: SmokeP1')) { throw 'Initial draw did not display Player 1 name' }
if (-not $outputText.Contains('resultado do sorteio:')) { throw 'Initial draw did not display the normalized parity result' }
if (-not $outputText.Contains('SIMULACAO AUTOMATICA ATIVADA')) { throw 'Simulation activation was not reached' }
$simulationText = $outputText.Substring($outputText.IndexOf('SIMULACAO AUTOMATICA ATIVADA'))
if (-not [regex]::IsMatch($simulationText, 'RODADA \d+ \| .*deve escolher o atributo')) { throw 'Simulation did not re-display the choosing player after clearing the terminal' }
$simulatedAttributes = [regex]::Matches($simulationText, 'Atributo escolhido: ([^=]+) =') | ForEach-Object { $_.Groups[1].Value.Trim() } | Select-Object -Unique
if ($simulatedAttributes.Count -lt 2) { throw 'Simulation did not demonstrate random attribute variety' }
if (-not $outputText.Contains('CAMPEAO:')) { throw 'Winner output not found' }
if (-not [regex]::IsMatch($outputText, 'Cartas de SmokeP1: (0|34)')) { throw 'Final card count for SmokeP1 is missing or incorrect' }
if (-not [regex]::IsMatch($outputText, 'Cartas de SmokeP2: (0|34)')) { throw 'Final card count for SmokeP2 is missing or incorrect' }
if (-not ($outputText.Contains('SmokeP1 venceu a disputa!') -or $outputText.Contains('SmokeP2 venceu a disputa!'))) { throw 'Round result did not use a registered player name' }
if ([regex]::IsMatch($outputText, 'Jogador [12] venceu a disputa!')) { throw 'A generic player label remains in a round result' }
if ($outputText.Contains('A V1 suporta exatamente 2 jogadores.')) { throw 'Redundant two-player warning is still displayed' }
if (-not [regex]::IsMatch($outputText, '(?s)SmokeP1 \| cartas na mao: \d+.*?={60}\r?\n\r?\nSmokeP2 \| cartas na mao:')) { throw 'Players are not separated by the requested divider' }
if (-not [regex]::IsMatch($outputText, '={60}\r?\n(?:SmokeP1|SmokeP2) venceu a disputa!')) { throw 'Divider is missing immediately before a round result' }
if (-not $outputText.Contains('Obrigado por jogar SuperTrunfIA')) { throw 'Exit menu flow not reached' }

# EOF while reading a name and a numeric choice must exit without looping.
$eofSetup = @('1', 'EOF_P1', 'EOF_P2')
$eofOutput = ($eofSetup -join "`n") | .\build.exe
$eofText = $eofOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $eofText.Contains('Obrigado por jogar SuperTrunfIA')) { throw 'EOF setup handling failed' }

$longNameInputs = @('1', ('N' * 80))
$longNameOutput = ($longNameInputs -join "`n") | .\build.exe
$longNameText = $longNameOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $longNameText.Contains('Nome muito longo')) { throw 'Long player name was not rejected and re-requested' }
if (-not $longNameText.Contains('Sorteio inicial: Jogador 1')) { throw 'EOF after a long player name did not leave a safe fallback name' }

$eofAttribute = @('1', 'AttrP1', 'AttrP2', '1')
$eofAttributeOutput = ($eofAttribute -join "`n") | .\build.exe
$eofAttributeText = $eofAttributeOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $eofAttributeText.Contains('Obrigado por jogar SuperTrunfIA')) { throw 'EOF at attribute selection failed' }

$maxName = 'A' * 49
$maxNameInputs = @('1', $maxName, ('B' * 49))
$maxNameOutput = ($maxNameInputs -join "`n") | .\build.exe
$maxNameText = $maxNameOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $maxNameText.Contains("Sorteio inicial: $maxName")) { throw 'Maximum valid player name length was not preserved' }

$numericOverflow = @(('9' * 50), '0')
$numericOverflowOutput = ($numericOverflow -join "`n") | .\build.exe
$numericOverflowText = $numericOverflowOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $numericOverflowText.Contains('Entrada invalida')) { throw 'Numeric overflow was not rejected' }

$invalidToken = @('1abc', '0')
$invalidTokenOutput = ($invalidToken -join "`n") | .\build.exe
$invalidTokenText = $invalidTokenOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $invalidTokenText.Contains('Entrada invalida')) { throw 'Trailing characters in numeric input were accepted' }

$invalidPause = @('1', 'PauseP1', 'PauseP2', '1', '1', 'Pxyz', '0')
$invalidPauseOutput = ($invalidPause -join "`n") | .\build.exe
$invalidPauseText = $invalidPauseOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $invalidPauseText.Contains('Opcao invalida')) { throw 'Pause accepted a partial P command instead of a complete token' }

$overflowMenu = @(('9' * 200), '0')
$overflowOutput = ($overflowMenu -join "`n") | .\build.exe
$overflowText = $overflowOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $overflowText.Contains('Entrada muito longa')) { throw 'Overlong numeric input was not rejected safely' }

# Exhaust manual choices and then deliver EOF at a pause.
$eofPause = @('1', 'PauseP1', 'PauseP2', '1')
for ($i = 0; $i -lt 40; $i++) { $eofPause += '1' }
$eofPause += ('X' * 100)
$eofPauseOutput = ($eofPause -join "`n") | .\build.exe
$eofPauseText = $eofPauseOutput | Out-String
if ($LASTEXITCODE -ne 0 -or -not $eofPauseText.Contains('Obrigado por jogar SuperTrunfIA')) { throw 'EOF at a round pause failed' }
if (-not $eofPauseText.Contains('Entrada muito longa')) { throw 'Overlong pause command was not rejected safely' }

Remove-Item build.exe -ErrorAction SilentlyContinue
Write-Output 'INTERFACE + NAMES + DIVIDERS + FINAL RESULT + INPUT/EOF SMOKE: PASS'
