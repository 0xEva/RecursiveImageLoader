# RecursiveImageLoader
[WIP] An Image Loader with Recursive DFS for Dependency Resolution

## Description
This repo outlines the ongoing work for a Recursive DFS-Based Image Loader, with the intention to be a more advanced than userland DoublePulsar.

## Done
- Developed the core recursive loader logic using DFS.
- Circular import detection
- API Sets DLL resolution.
- Established a framework for minimizing reliance custom GetModuleHandle for PEB parsing.
- Custom structure for managing our loaded DLLs

## WIP
### Challenges:
- **ntdll.dll** **kernelbase.dll** **kernel32.dll** Cannot be loaded mannully.

### Uncertainties:
- There is uncertainty regarding other system DLLs beyond ntdll, kernelbase, and kernel32. Further research and testing are required to determine if they can be manually loaded.

### TODO
- FreeLibrary
