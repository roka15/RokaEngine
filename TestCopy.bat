
@echo off
mkdir ".\External\Include\TestCopy"
xcopy /s /y  /exclude:exclude_list.txt ".\Project\GenericLib\interface.h" ".\External\Include\TestCopy"
pause