#### SatView™ Coding Guidelines<br />
Although SatView™ is built using a kernel-based approach, it's still quite a challenge to adopt it to a mission's needs.<br />
In most cases, there are three major areas which need customization:
- Database
- Data I/O
- Automation<br />
<p align="center">
  <img src="../Images/SatView™%20Interfaces.png" />
</p>

#####1. Database
Currently, SatView™ supports two database standards: SCOS-2000 (ESA) and ALTEL (L3 Communications).<br />
The document [SatView™ Database Standards](../Documents/SatView™ Database Standards.pdf) describes these standards in more detail and helps to evaluate which one fits the mission's needs best.<br />
Depending on the chosen database standard, the associated projects need to be included in the software solution:<br />
**SCOS-2000** & **Satellite (SCOS-2000)** or **ALTEL** & **Satellite (ALTEL)**.
Obviously, the projects **Satellite (SCOS-2000)** or **Satellite (ALTEL)** need to be renamed to the mission's satellite name and the unused projects can be excluded from the solution.<br />
Whereas the projects **SCOS-2000** & **ALTEL** define the generic behavior of all satellites using that database standard, the associated **Satellite (SCOS-2000)** & **Satellite (ALTEL)** projects contain any deviating code. With other words, the latter ones contain derived classes that implement a satellite specific behavior via virtual functions.<br />
In a nutshell, such a database driver is made-up of these classes:<br />
**CDatabaseEngine**:<br />
Handles the database loading/parsing and table rendering.<br />
Consult the document [SatView™ Database Interface](../Documents/SatView™ Database Interface.pdf) for a detailed description of this class.<br />
For both database standards, this class needs only few changes.<br />
**CMemoryDumpsServiceEngine**:<br />
Implements the interface to handle memory dumps.<br />
**CTPEPServiceEngine**:<br />
Defines the interface for the *Telemetry Parameter Exchange Protocol* (TPEP).<br />
Read the document ['Telemetry Parameter Exchange Protocol'](../Documents/SatView™ Telemetry Parameter Exchange Protocol (TPEP).pdf) to learn more about TPEP.<br />
**CPFLPServiceEngine**:<br />
**CTMProcessEngine**:<br />
**CTCProcessEngine**:<br />


<br />  
#####2. Data I/O
#####3. Automation

<br />  
To be completed soon.
