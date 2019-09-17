### SatView™ Installation Guide<br />
**Installing Satview™ and customizing it to your needs is a challenging task and requires deep knowledge of the Microsoft® Windows® platform and the related development tools.<br />Feel free to get in touch with BINARY SPACE in case of questions.**<br /><br />Here is a short list to get started with the installation:
- Install Microsoft® Windows® 10 Professional/Enterprise or Microsoft® Windows® Server 2019
- Install Microsoft® Visual Studio® 2019 (Version 16.1.4 or later) with at least the following features:<br />'**.NET desktop development**' and '**Desktop development with C++**' (make sure that the options '**Windows 10 SDK (10.0.18362.0)**', '**Visual C++ MFC for x86 and x64**' & '**Visual C++ ATL for x86 and x64**' are checked)
- Open Microsoft® Visual Studio® 2019 and install the '**GitHub Extension for Visual Studio**' via the 'Tools'->'Extensions and Updates...' menu item
- Install Microsoft® SQL Server® 2017 (the 'Database Engine Services' feature is sufficient) with mixed-mode authentication where the 'sa' account shares the same password as the 'Administrator' account for SatView™ and add the 'Administrator' account to the 'sysadmin' group
- Download and install the SQL Server® Management Studio 18.1 (SSMS):<br />https://docs.microsoft.com/en-us/sql/ssms/download-sql-server-management-studio-ssms?view=sql-server-2017
- Add the following environment variables to the 'System Variables' (for 64-bit):<br />
**Include**=\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\\***XX.XX.XXXXX***\\include<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\\***XX.XX.XXXXX***\\atlmfc\include<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Windows Kits\10\Include\10.0.***XXXXX***.0\shared<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Windows Kits\10\Include\10.0.***XXXXX***.0\ucrt<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Windows Kits\10\Include\10.0.***XXXXX***.0\um<br />
**Lib**=\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\\***XX.XX.XXXXX***\\lib\x64<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\\***XX.XX.XXXXX***\\atlmfc\lib\x64<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Windows Kits\10\Lib\10.0.***XXXXX***.0\ucrt\x64<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Windows Kits\10\Lib\10.0.***XXXXX***.0\um\x64<br />
Note: ***XX.XX.XXXXX*** = Microsoft® Visual Studio® Version, ***XXXXX*** = Windows® 10 SDK Version (e.g. 18362)
- Clone the repository by selecting the 'Open in Visual Studio' option and call it 'SatView'
- Close Microsoft® Visual Studio® 2019 and reopen it under the 'Administrator' account (right-click and select 'Run as administrator')
- Open the downloaded repository and load the available solution file 'SatView (GitHub)' inside the 'Source' folder
- Exclude either the projects '**SCOS-2000**' & '**Satellite (SCOS-2000)**' or '**ALTEL**' & '**Satellite (ALTEL)**' from the solution  depending on the database standard selected (read the [coding guidelines](Coding.md))
- Rename the project '**Satellite (SCOS-2000)**' or '**Satellite (ALTEL)**' (including the contained classes and the resulting output file) to the name of the satellite to be supported
- Open the file called 'messages.man' in the '**Library**' project and modify the absolute paths associated with the '**resourceFileName**' and '**messageFileName**' entries to point to the resulting output file 'SatView.dll'
- Complete the coding for the projects '**SCOS-2000**' or '**ALTEL**' and the associated (renamed) spacecraft project
- Code the data I/O interface driver (read the [coding guidelines](Coding.md))
- Compile the solution
- Launch the '**SatView™ Editor**' for the first time, register the satellite name and enter the password for the 'Administrator' account (i.e. the password for the 'Administrator' account of SatView™ must be identical to the one for the OS)
- Start building the database (consult the help file '**Editor.chm**' in order to learn how to create & modify databases)
- Integrate the system into your ground segment and launch the '**SatView™ Desktop**' to monitor & control the spacecraft
