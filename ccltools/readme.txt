CCL Tools NSIS Plugin 1.0
=========================

Summary
-------
Utility functions for NSIS. See the following sections for a description of the provided functions and usage instructions.

runFromExplorer "<application path>"
------------------------------------
Executes the application given in <application path> from the currently running Explorer instance. This is particularly useful when your installer runs with elevated privileges and you want to run the application with the security level of the logged-in user.

Sample script:
    ccltools::runFromExplorer "C:\Windows\notepad.exe"
    pop $0