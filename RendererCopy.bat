@echo off
mkdir ".\External\Include\Renderer"
xcopy /s /y  /exclude:exclude_list.txt ".\Project\Renderer\*.h" ".\External\Include\Renderer"
xcopy /s /y  /exclude:exclude_list.txt ".\Project\Renderer\*.inl"  ".\External\Include\Renderer"

pause