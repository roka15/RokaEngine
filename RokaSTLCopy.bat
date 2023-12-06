@echo off
mkdir ".\External\Include\RokaSTL"
xcopy /s /y  /exclude:exclude_list.txt ".\Project\RokaSTL_Lib\*.h" ".\External\Include\RokaSTL"
pause