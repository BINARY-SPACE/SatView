#### SatView™ Installation Guide<br />
- Install Microsoft® Windows® 10 Professional/Enterprise (Version 1511, OS Build 10586 and above) or Microsoft® Windows® Server 2016
- Install Microsoft® Visual Studio® 2015 (Update 2) with all features
- Install Microsoft® SQL Server® 2016 (the 'Database Engine Services' feature is sufficient) with mixed-mode authentication where the 'sa' account shares the same password as the 'Administrator' account for SatView™ and add the 'Administrator' account to the database system administrators
- Download and install the SQL Server® 2016 Management Studio (SSMS)
- Download the '**SatView**' GitHub repository as 'zip' file, extract the '**Source**' directory, rename it to '**SatView**' and move it into the '**Documents**' folder
- Open the Microsoft® Visual Studio® 2015 under the 'Administrator' account (right-click and select 'Run as administrator')
- Open the project solution called 'SatView (GitHub)'
- Exclude either the projects '**SCOS-2000**' & '**Satellite (SCOS-2000)**' or '**ALTEL**' & '**Satellite (ALTEL)**' from the solution  depending on the database standard selected (read [coding guidelines](Coding.md))

<br />  
To be completed soon.
