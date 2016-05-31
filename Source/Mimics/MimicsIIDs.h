// MIMICSIIDS.H : Mimics Control Interface Identifiers.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics control interface identifiers.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSIIDS_H__
#define __MIMICSIIDS_H__


// {D9B0D9EC-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(IID_IEnumMimicsCtrls,
	0xd9b0d9ec, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);
// {D9B0D9ED-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(CLSID_CEnumMimicsCtrls,
	0xd9b0d9ed, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);

// {D9B0D9F0-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(CLSID_CMimicsLineCtrl,
	0xd9b0d9f0, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);
// {D9B0D9FF-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(CLSID_CMimicsRectangleCtrl,
	0xd9b0d9ff, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);
// {D9B0D9FA-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(CLSID_CMimicsEllipseCtrl,
	0xd9b0d9fa, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);
// {D9B0D9F5-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(CLSID_CMimicsArcCtrl,
	0xd9b0d9f5, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);
// {D9B0DA04-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(CLSID_CMimicsTriangleCtrl,
	0xd9b0da04, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);
// {D9B0DA09-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(CLSID_CMimicsSwitchCtrl,
	0xd9b0da09, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);
// {D9B0DA0E-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(CLSID_CMimicsTextCtrl,
	0xd9b0da0e, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);
// {D9B0DA19-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(CLSID_CMimicsImageCtrl,
	0xd9b0da19, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);
// {D9B0DA14-C96C-11d3-B5E7-0060082D5389}
DEFINE_GUID(CLSID_CMimicsGroupCtrl,
	0xd9b0da14, 0xc96c, 0x11d3, 0xb5, 0xe7, 0x0, 0x60, 0x8, 0x2d, 0x53, 0x89);


#endif // __MIMICSIIDS_H__
