// DOCUMENTS.H : Documents Interface Identifiers.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the documents interface identifiers.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2011/12/27 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DOCUMENTS_H__
#define __DOCUMENTS_H__


// Specify the IID for the DPL code document
static const IID  IID_IDPLCodeDocument = { 0x8CC497C0,0xA1DF,0x11ce,{ 0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D } };
// Specify the IID for the MDL code document
static const IID  IID_IMDLCodeDocument = { 0x8CC497C0,0xA1DF,0x11ce,{ 0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D } };
// Specify the IID for the TPL code document
static const IID  IID_ITPLCodeDocument = { 0x8CC497C0,0xA1DF,0x11ce,{ 0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D } };
// Specify the IID for the automation script code document
static const IID  IID_IScriptCodeDocument = { 0x8CC497C0,0xA1DF,0x11ce,{ 0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D } };
// Specify the IID for the TC Procedure xml document
static const IID  IID_ITCProcedureXmlDocument = { 0x8CC497C0,0xA1DF,0x11ce,{ 0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D } };
// Specify the IID for the AND xml document
static const IID  IID_IANDXmlDocument = { 0x8CC497C0,0xA1DF,0x11ce,{ 0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D } };
// Specify the IID for the GRD xml document
static const IID  IID_IGRDXmlDocument = { 0x8CC497C0,0xA1DF,0x11ce,{ 0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D } };
// Specify the IID for the POD xml document
static const IID  IID_IPODXmlDocument = { 0x8CC497C0,0xA1DF,0x11ce,{ 0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D } };


#endif // __DOCUMENTS_H__
