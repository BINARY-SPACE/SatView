### SatView™ Installation Guide<br />
**Installing Satview™ and customizing it to your needs is a challenging task and requires deep knowledge of the Microsoft® Windows® platform and the related development tools. Therefore, it is highly recommended to get in touch with BINARY SPACE.**<br /><br />Here is a short list to get started with the installation:
- Install Microsoft® Windows® 10 Professional/Enterprise or Microsoft® Windows® Server 2016
- Install Microsoft® Visual Studio® 2015 with all features
- Install Microsoft® SQL Server® 2016 (the 'Database Engine Services' feature is sufficient) with mixed-mode authentication where the 'sa' account shares the same password as the 'Administrator' account for SatView™ and add the 'Administrator' account to the 'sysadmin' group
- Download and install the SQL Server® 2016 Management Studio (SSMS)
- Download the '**SatView**' GitHub repository as 'zip' file, extract the '**Source**' directory, rename it to '**SatView**' and move it into the '**Documents**' folder
- Rename the directories '**Satellite_SCOS-2000**' (inside '**SatView**') to '**Satellite (SCOS-2000)**' and '**Satellite_ALTEL**' to '**Satellite (ALTEL)**'
- Add the following environment variables to the 'System variables':<br />
**Include**=\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Microsoft Visual Studio 14.0\VC\atlmfc\include<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Windows Kits\10\Include\10.0.***XXXXX***.0\shared<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Windows Kits\10\Include\10.0.***XXXXX***.0\ucrt<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Windows Kits\10\Include\10.0.***XXXXX***.0\um<br />
**Lib**=\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib\amd64<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Microsoft Visual Studio 14.0\VC\atlmfc\lib\amd64<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Windows Kits\10\Lib\10.0.***XXXXX***.0\ucrt\x64<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\Program Files (x86)\Windows Kits\10\Lib\10.0.***XXXXX***.0\um\x64
<br />
Note: ***XXXXX*** = Windows® 10 SDK Version (e.g. 14393)
- Open the Microsoft® Visual Studio® 2015 under the 'Administrator' account (right-click and select 'Run as administrator')
- Open the project solution called 'SatView (GitHub)'
- Exclude either the projects '**SCOS-2000**' & '**Satellite (SCOS-2000)**' or '**ALTEL**' & '**Satellite (ALTEL)**' from the solution  depending on the database standard selected (read the [coding guidelines](Coding.md))
- Rename the project '**Satellite (SCOS-2000)**' or '**Satellite (ALTEL)**' (including the contained classes and the resulting output file) to the name of the satellite to be supported
- Open the file called 'messages.man' in the '**Library**' project and modify the absolute paths associated with the '**resourceFileName**' and '**messageFileName**' entries to point to the resulting output file 'SatView.dll'
- Complete the coding for the projects '**SCOS-2000**' or '**ALTEL**' and the associated (renamed) satellite project
- Launch the '**SatView™ Editor**' for the first time, register the satellite name and enter the password for the 'Administrator' account (i.e. the password for the 'Administrator' account of SatView™ must be identical to the one for the OS)
- Start building the database; consult the help file '**Editor.chm**' in order to learn how to create & modify databases
