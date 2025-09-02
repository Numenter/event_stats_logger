@echo off
start powershell -NoExit -Command "Get-Content (-join($env:APPDATA, '\\bakkesmod\\bakkesmod\\bakkesmod.log')) -wait -tail 1 | Select-String -Pattern 'EventStatsLogger'"