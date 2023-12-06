@echo off
mkdir ".\External\Include\Script"
xcopy /s /y  /exclude:exclude_list.txt ".\Project\Script\*.h" ".\External\Include\Script"
pause