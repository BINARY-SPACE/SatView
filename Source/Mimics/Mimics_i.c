

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0626 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for Mimics.odl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0626 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_MIMICSLib,0xD9B0D9EB,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsLine,0xD9B0D9EE,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsLineEvents,0xD9B0D9EF,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(CLSID, CLSID_MimicsLine,0xD9B0D9F0,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsRectangle,0xD9B0D9FD,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsRectangleEvents,0xD9B0D9FE,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(CLSID, CLSID_MimicsRectangle,0xD9B0D9FF,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsEllipse,0xD9B0D9F8,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsEllipseEvents,0xD9B0D9F9,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(CLSID, CLSID_MimicsEllipse,0xD9B0D9FA,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsArc,0xD9B0D9F3,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsArcEvents,0xD9B0D9F4,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(CLSID, CLSID_MimicsArc,0xD9B0D9F5,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsTriangle,0xD9B0DA02,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsTriangleEvents,0xD9B0DA03,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(CLSID, CLSID_MimicsTriangle,0xD9B0DA04,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsSwitch,0xD9B0DA07,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsSwitchEvents,0xD9B0DA08,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(CLSID, CLSID_MimicsSwitch,0xD9B0DA09,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsText,0xD9B0DA0C,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsTextEvents,0xD9B0DA0D,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(CLSID, CLSID_MimicsText,0xD9B0DA0E,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsImage,0xD9B0DA17,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsImageEvents,0xD9B0DA18,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(CLSID, CLSID_MimicsImage,0xD9B0DA19,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsGroup,0xD9B0DA12,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(IID, DIID__DMimicsGroupEvents,0xD9B0DA13,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);


MIDL_DEFINE_GUID(CLSID, CLSID_MimicsGroup,0xD9B0DA14,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



