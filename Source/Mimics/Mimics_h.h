

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0613 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for Mimics.odl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0613 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __Mimics_h_h__
#define __Mimics_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DMimicsLine_FWD_DEFINED__
#define ___DMimicsLine_FWD_DEFINED__
typedef interface _DMimicsLine _DMimicsLine;

#endif 	/* ___DMimicsLine_FWD_DEFINED__ */


#ifndef ___DMimicsLineEvents_FWD_DEFINED__
#define ___DMimicsLineEvents_FWD_DEFINED__
typedef interface _DMimicsLineEvents _DMimicsLineEvents;

#endif 	/* ___DMimicsLineEvents_FWD_DEFINED__ */


#ifndef __MimicsLine_FWD_DEFINED__
#define __MimicsLine_FWD_DEFINED__

#ifdef __cplusplus
typedef class MimicsLine MimicsLine;
#else
typedef struct MimicsLine MimicsLine;
#endif /* __cplusplus */

#endif 	/* __MimicsLine_FWD_DEFINED__ */


#ifndef ___DMimicsRectangle_FWD_DEFINED__
#define ___DMimicsRectangle_FWD_DEFINED__
typedef interface _DMimicsRectangle _DMimicsRectangle;

#endif 	/* ___DMimicsRectangle_FWD_DEFINED__ */


#ifndef ___DMimicsRectangleEvents_FWD_DEFINED__
#define ___DMimicsRectangleEvents_FWD_DEFINED__
typedef interface _DMimicsRectangleEvents _DMimicsRectangleEvents;

#endif 	/* ___DMimicsRectangleEvents_FWD_DEFINED__ */


#ifndef __MimicsRectangle_FWD_DEFINED__
#define __MimicsRectangle_FWD_DEFINED__

#ifdef __cplusplus
typedef class MimicsRectangle MimicsRectangle;
#else
typedef struct MimicsRectangle MimicsRectangle;
#endif /* __cplusplus */

#endif 	/* __MimicsRectangle_FWD_DEFINED__ */


#ifndef ___DMimicsEllipse_FWD_DEFINED__
#define ___DMimicsEllipse_FWD_DEFINED__
typedef interface _DMimicsEllipse _DMimicsEllipse;

#endif 	/* ___DMimicsEllipse_FWD_DEFINED__ */


#ifndef ___DMimicsEllipseEvents_FWD_DEFINED__
#define ___DMimicsEllipseEvents_FWD_DEFINED__
typedef interface _DMimicsEllipseEvents _DMimicsEllipseEvents;

#endif 	/* ___DMimicsEllipseEvents_FWD_DEFINED__ */


#ifndef __MimicsEllipse_FWD_DEFINED__
#define __MimicsEllipse_FWD_DEFINED__

#ifdef __cplusplus
typedef class MimicsEllipse MimicsEllipse;
#else
typedef struct MimicsEllipse MimicsEllipse;
#endif /* __cplusplus */

#endif 	/* __MimicsEllipse_FWD_DEFINED__ */


#ifndef ___DMimicsArc_FWD_DEFINED__
#define ___DMimicsArc_FWD_DEFINED__
typedef interface _DMimicsArc _DMimicsArc;

#endif 	/* ___DMimicsArc_FWD_DEFINED__ */


#ifndef ___DMimicsArcEvents_FWD_DEFINED__
#define ___DMimicsArcEvents_FWD_DEFINED__
typedef interface _DMimicsArcEvents _DMimicsArcEvents;

#endif 	/* ___DMimicsArcEvents_FWD_DEFINED__ */


#ifndef __MimicsArc_FWD_DEFINED__
#define __MimicsArc_FWD_DEFINED__

#ifdef __cplusplus
typedef class MimicsArc MimicsArc;
#else
typedef struct MimicsArc MimicsArc;
#endif /* __cplusplus */

#endif 	/* __MimicsArc_FWD_DEFINED__ */


#ifndef ___DMimicsTriangle_FWD_DEFINED__
#define ___DMimicsTriangle_FWD_DEFINED__
typedef interface _DMimicsTriangle _DMimicsTriangle;

#endif 	/* ___DMimicsTriangle_FWD_DEFINED__ */


#ifndef ___DMimicsTriangleEvents_FWD_DEFINED__
#define ___DMimicsTriangleEvents_FWD_DEFINED__
typedef interface _DMimicsTriangleEvents _DMimicsTriangleEvents;

#endif 	/* ___DMimicsTriangleEvents_FWD_DEFINED__ */


#ifndef __MimicsTriangle_FWD_DEFINED__
#define __MimicsTriangle_FWD_DEFINED__

#ifdef __cplusplus
typedef class MimicsTriangle MimicsTriangle;
#else
typedef struct MimicsTriangle MimicsTriangle;
#endif /* __cplusplus */

#endif 	/* __MimicsTriangle_FWD_DEFINED__ */


#ifndef ___DMimicsSwitch_FWD_DEFINED__
#define ___DMimicsSwitch_FWD_DEFINED__
typedef interface _DMimicsSwitch _DMimicsSwitch;

#endif 	/* ___DMimicsSwitch_FWD_DEFINED__ */


#ifndef ___DMimicsSwitchEvents_FWD_DEFINED__
#define ___DMimicsSwitchEvents_FWD_DEFINED__
typedef interface _DMimicsSwitchEvents _DMimicsSwitchEvents;

#endif 	/* ___DMimicsSwitchEvents_FWD_DEFINED__ */


#ifndef __MimicsSwitch_FWD_DEFINED__
#define __MimicsSwitch_FWD_DEFINED__

#ifdef __cplusplus
typedef class MimicsSwitch MimicsSwitch;
#else
typedef struct MimicsSwitch MimicsSwitch;
#endif /* __cplusplus */

#endif 	/* __MimicsSwitch_FWD_DEFINED__ */


#ifndef ___DMimicsText_FWD_DEFINED__
#define ___DMimicsText_FWD_DEFINED__
typedef interface _DMimicsText _DMimicsText;

#endif 	/* ___DMimicsText_FWD_DEFINED__ */


#ifndef ___DMimicsTextEvents_FWD_DEFINED__
#define ___DMimicsTextEvents_FWD_DEFINED__
typedef interface _DMimicsTextEvents _DMimicsTextEvents;

#endif 	/* ___DMimicsTextEvents_FWD_DEFINED__ */


#ifndef __MimicsText_FWD_DEFINED__
#define __MimicsText_FWD_DEFINED__

#ifdef __cplusplus
typedef class MimicsText MimicsText;
#else
typedef struct MimicsText MimicsText;
#endif /* __cplusplus */

#endif 	/* __MimicsText_FWD_DEFINED__ */


#ifndef ___DMimicsImage_FWD_DEFINED__
#define ___DMimicsImage_FWD_DEFINED__
typedef interface _DMimicsImage _DMimicsImage;

#endif 	/* ___DMimicsImage_FWD_DEFINED__ */


#ifndef ___DMimicsImageEvents_FWD_DEFINED__
#define ___DMimicsImageEvents_FWD_DEFINED__
typedef interface _DMimicsImageEvents _DMimicsImageEvents;

#endif 	/* ___DMimicsImageEvents_FWD_DEFINED__ */


#ifndef __MimicsImage_FWD_DEFINED__
#define __MimicsImage_FWD_DEFINED__

#ifdef __cplusplus
typedef class MimicsImage MimicsImage;
#else
typedef struct MimicsImage MimicsImage;
#endif /* __cplusplus */

#endif 	/* __MimicsImage_FWD_DEFINED__ */


#ifndef ___DMimicsGroup_FWD_DEFINED__
#define ___DMimicsGroup_FWD_DEFINED__
typedef interface _DMimicsGroup _DMimicsGroup;

#endif 	/* ___DMimicsGroup_FWD_DEFINED__ */


#ifndef ___DMimicsGroupEvents_FWD_DEFINED__
#define ___DMimicsGroupEvents_FWD_DEFINED__
typedef interface _DMimicsGroupEvents _DMimicsGroupEvents;

#endif 	/* ___DMimicsGroupEvents_FWD_DEFINED__ */


#ifndef __MimicsGroup_FWD_DEFINED__
#define __MimicsGroup_FWD_DEFINED__

#ifdef __cplusplus
typedef class MimicsGroup MimicsGroup;
#else
typedef struct MimicsGroup MimicsGroup;
#endif /* __cplusplus */

#endif 	/* __MimicsGroup_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MIMICSLib_LIBRARY_DEFINED__
#define __MIMICSLib_LIBRARY_DEFINED__

/* library MIMICSLib */
/* [control][helpstring][helpfile][version][uuid] */ 

#pragma warning(push)
#pragma warning(disable:4001) 
#pragma once
#pragma warning(push)
#pragma warning(disable:4001) 
#pragma once
#pragma warning(pop)
#pragma warning(pop)
#pragma region Desktop Family
#pragma endregion

DEFINE_GUID(LIBID_MIMICSLib,0xD9B0D9EB,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#ifndef ___DMimicsLine_DISPINTERFACE_DEFINED__
#define ___DMimicsLine_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsLine */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsLine,0xD9B0D9EE,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0D9EE-C96C-11D3-B5E7-0060082D5389")
    _DMimicsLine : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsLineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsLine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsLine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsLine * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsLine * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsLine * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsLine * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsLine * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsLineVtbl;

    interface _DMimicsLine
    {
        CONST_VTBL struct _DMimicsLineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsLine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsLine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsLine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsLine_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsLine_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsLine_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsLine_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsLine_DISPINTERFACE_DEFINED__ */


#ifndef ___DMimicsLineEvents_DISPINTERFACE_DEFINED__
#define ___DMimicsLineEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsLineEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsLineEvents,0xD9B0D9EF,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0D9EF-C96C-11D3-B5E7-0060082D5389")
    _DMimicsLineEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsLineEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsLineEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsLineEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsLineEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsLineEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsLineEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsLineEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsLineEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsLineEventsVtbl;

    interface _DMimicsLineEvents
    {
        CONST_VTBL struct _DMimicsLineEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsLineEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsLineEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsLineEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsLineEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsLineEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsLineEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsLineEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsLineEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MimicsLine,0xD9B0D9F0,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#ifdef __cplusplus

class DECLSPEC_UUID("D9B0D9F0-C96C-11D3-B5E7-0060082D5389")
MimicsLine;
#endif

#ifndef ___DMimicsRectangle_DISPINTERFACE_DEFINED__
#define ___DMimicsRectangle_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsRectangle */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsRectangle,0xD9B0D9FD,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0D9FD-C96C-11D3-B5E7-0060082D5389")
    _DMimicsRectangle : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsRectangleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsRectangle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsRectangle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsRectangle * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsRectangle * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsRectangle * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsRectangle * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsRectangle * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsRectangleVtbl;

    interface _DMimicsRectangle
    {
        CONST_VTBL struct _DMimicsRectangleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsRectangle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsRectangle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsRectangle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsRectangle_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsRectangle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsRectangle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsRectangle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsRectangle_DISPINTERFACE_DEFINED__ */


#ifndef ___DMimicsRectangleEvents_DISPINTERFACE_DEFINED__
#define ___DMimicsRectangleEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsRectangleEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsRectangleEvents,0xD9B0D9FE,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0D9FE-C96C-11D3-B5E7-0060082D5389")
    _DMimicsRectangleEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsRectangleEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsRectangleEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsRectangleEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsRectangleEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsRectangleEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsRectangleEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsRectangleEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsRectangleEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsRectangleEventsVtbl;

    interface _DMimicsRectangleEvents
    {
        CONST_VTBL struct _DMimicsRectangleEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsRectangleEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsRectangleEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsRectangleEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsRectangleEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsRectangleEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsRectangleEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsRectangleEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsRectangleEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MimicsRectangle,0xD9B0D9FF,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#ifdef __cplusplus

class DECLSPEC_UUID("D9B0D9FF-C96C-11D3-B5E7-0060082D5389")
MimicsRectangle;
#endif

#ifndef ___DMimicsEllipse_DISPINTERFACE_DEFINED__
#define ___DMimicsEllipse_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsEllipse */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsEllipse,0xD9B0D9F8,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0D9F8-C96C-11D3-B5E7-0060082D5389")
    _DMimicsEllipse : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsEllipseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsEllipse * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsEllipse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsEllipse * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsEllipse * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsEllipse * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsEllipse * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsEllipse * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsEllipseVtbl;

    interface _DMimicsEllipse
    {
        CONST_VTBL struct _DMimicsEllipseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsEllipse_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsEllipse_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsEllipse_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsEllipse_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsEllipse_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsEllipse_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsEllipse_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsEllipse_DISPINTERFACE_DEFINED__ */


#ifndef ___DMimicsEllipseEvents_DISPINTERFACE_DEFINED__
#define ___DMimicsEllipseEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsEllipseEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsEllipseEvents,0xD9B0D9F9,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0D9F9-C96C-11D3-B5E7-0060082D5389")
    _DMimicsEllipseEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsEllipseEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsEllipseEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsEllipseEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsEllipseEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsEllipseEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsEllipseEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsEllipseEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsEllipseEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsEllipseEventsVtbl;

    interface _DMimicsEllipseEvents
    {
        CONST_VTBL struct _DMimicsEllipseEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsEllipseEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsEllipseEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsEllipseEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsEllipseEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsEllipseEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsEllipseEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsEllipseEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsEllipseEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MimicsEllipse,0xD9B0D9FA,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#ifdef __cplusplus

class DECLSPEC_UUID("D9B0D9FA-C96C-11D3-B5E7-0060082D5389")
MimicsEllipse;
#endif

#ifndef ___DMimicsArc_DISPINTERFACE_DEFINED__
#define ___DMimicsArc_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsArc */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsArc,0xD9B0D9F3,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0D9F3-C96C-11D3-B5E7-0060082D5389")
    _DMimicsArc : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsArcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsArc * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsArc * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsArc * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsArc * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsArc * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsArc * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsArc * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsArcVtbl;

    interface _DMimicsArc
    {
        CONST_VTBL struct _DMimicsArcVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsArc_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsArc_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsArc_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsArc_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsArc_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsArc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsArc_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsArc_DISPINTERFACE_DEFINED__ */


#ifndef ___DMimicsArcEvents_DISPINTERFACE_DEFINED__
#define ___DMimicsArcEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsArcEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsArcEvents,0xD9B0D9F4,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0D9F4-C96C-11D3-B5E7-0060082D5389")
    _DMimicsArcEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsArcEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsArcEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsArcEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsArcEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsArcEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsArcEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsArcEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsArcEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsArcEventsVtbl;

    interface _DMimicsArcEvents
    {
        CONST_VTBL struct _DMimicsArcEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsArcEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsArcEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsArcEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsArcEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsArcEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsArcEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsArcEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsArcEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MimicsArc,0xD9B0D9F5,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#ifdef __cplusplus

class DECLSPEC_UUID("D9B0D9F5-C96C-11D3-B5E7-0060082D5389")
MimicsArc;
#endif

#ifndef ___DMimicsTriangle_DISPINTERFACE_DEFINED__
#define ___DMimicsTriangle_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsTriangle */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsTriangle,0xD9B0DA02,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0DA02-C96C-11D3-B5E7-0060082D5389")
    _DMimicsTriangle : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsTriangleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsTriangle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsTriangle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsTriangle * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsTriangle * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsTriangle * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsTriangle * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsTriangle * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsTriangleVtbl;

    interface _DMimicsTriangle
    {
        CONST_VTBL struct _DMimicsTriangleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsTriangle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsTriangle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsTriangle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsTriangle_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsTriangle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsTriangle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsTriangle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsTriangle_DISPINTERFACE_DEFINED__ */


#ifndef ___DMimicsTriangleEvents_DISPINTERFACE_DEFINED__
#define ___DMimicsTriangleEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsTriangleEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsTriangleEvents,0xD9B0DA03,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0DA03-C96C-11D3-B5E7-0060082D5389")
    _DMimicsTriangleEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsTriangleEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsTriangleEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsTriangleEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsTriangleEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsTriangleEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsTriangleEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsTriangleEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsTriangleEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsTriangleEventsVtbl;

    interface _DMimicsTriangleEvents
    {
        CONST_VTBL struct _DMimicsTriangleEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsTriangleEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsTriangleEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsTriangleEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsTriangleEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsTriangleEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsTriangleEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsTriangleEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsTriangleEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MimicsTriangle,0xD9B0DA04,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#ifdef __cplusplus

class DECLSPEC_UUID("D9B0DA04-C96C-11D3-B5E7-0060082D5389")
MimicsTriangle;
#endif

#ifndef ___DMimicsSwitch_DISPINTERFACE_DEFINED__
#define ___DMimicsSwitch_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsSwitch */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsSwitch,0xD9B0DA07,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0DA07-C96C-11D3-B5E7-0060082D5389")
    _DMimicsSwitch : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsSwitchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsSwitch * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsSwitch * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsSwitch * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsSwitch * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsSwitch * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsSwitch * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsSwitch * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsSwitchVtbl;

    interface _DMimicsSwitch
    {
        CONST_VTBL struct _DMimicsSwitchVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsSwitch_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsSwitch_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsSwitch_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsSwitch_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsSwitch_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsSwitch_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsSwitch_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsSwitch_DISPINTERFACE_DEFINED__ */


#ifndef ___DMimicsSwitchEvents_DISPINTERFACE_DEFINED__
#define ___DMimicsSwitchEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsSwitchEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsSwitchEvents,0xD9B0DA08,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0DA08-C96C-11D3-B5E7-0060082D5389")
    _DMimicsSwitchEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsSwitchEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsSwitchEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsSwitchEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsSwitchEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsSwitchEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsSwitchEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsSwitchEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsSwitchEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsSwitchEventsVtbl;

    interface _DMimicsSwitchEvents
    {
        CONST_VTBL struct _DMimicsSwitchEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsSwitchEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsSwitchEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsSwitchEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsSwitchEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsSwitchEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsSwitchEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsSwitchEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsSwitchEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MimicsSwitch,0xD9B0DA09,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#ifdef __cplusplus

class DECLSPEC_UUID("D9B0DA09-C96C-11D3-B5E7-0060082D5389")
MimicsSwitch;
#endif

#ifndef ___DMimicsText_DISPINTERFACE_DEFINED__
#define ___DMimicsText_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsText */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsText,0xD9B0DA0C,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0DA0C-C96C-11D3-B5E7-0060082D5389")
    _DMimicsText : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsTextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsText * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsText * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsText * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsText * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsText * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsText * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsText * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsTextVtbl;

    interface _DMimicsText
    {
        CONST_VTBL struct _DMimicsTextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsText_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsText_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsText_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsText_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsText_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsText_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsText_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsText_DISPINTERFACE_DEFINED__ */


#ifndef ___DMimicsTextEvents_DISPINTERFACE_DEFINED__
#define ___DMimicsTextEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsTextEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsTextEvents,0xD9B0DA0D,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0DA0D-C96C-11D3-B5E7-0060082D5389")
    _DMimicsTextEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsTextEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsTextEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsTextEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsTextEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsTextEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsTextEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsTextEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsTextEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsTextEventsVtbl;

    interface _DMimicsTextEvents
    {
        CONST_VTBL struct _DMimicsTextEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsTextEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsTextEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsTextEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsTextEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsTextEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsTextEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsTextEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsTextEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MimicsText,0xD9B0DA0E,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#ifdef __cplusplus

class DECLSPEC_UUID("D9B0DA0E-C96C-11D3-B5E7-0060082D5389")
MimicsText;
#endif

#ifndef ___DMimicsImage_DISPINTERFACE_DEFINED__
#define ___DMimicsImage_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsImage */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsImage,0xD9B0DA17,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0DA17-C96C-11D3-B5E7-0060082D5389")
    _DMimicsImage : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsImage * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsImage * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsImage * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsImage * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsImage * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsImageVtbl;

    interface _DMimicsImage
    {
        CONST_VTBL struct _DMimicsImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsImage_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsImage_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsImage_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsImage_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsImage_DISPINTERFACE_DEFINED__ */


#ifndef ___DMimicsImageEvents_DISPINTERFACE_DEFINED__
#define ___DMimicsImageEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsImageEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsImageEvents,0xD9B0DA18,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0DA18-C96C-11D3-B5E7-0060082D5389")
    _DMimicsImageEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsImageEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsImageEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsImageEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsImageEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsImageEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsImageEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsImageEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsImageEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsImageEventsVtbl;

    interface _DMimicsImageEvents
    {
        CONST_VTBL struct _DMimicsImageEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsImageEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsImageEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsImageEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsImageEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsImageEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsImageEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsImageEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsImageEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MimicsImage,0xD9B0DA19,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#ifdef __cplusplus

class DECLSPEC_UUID("D9B0DA19-C96C-11D3-B5E7-0060082D5389")
MimicsImage;
#endif

#ifndef ___DMimicsGroup_DISPINTERFACE_DEFINED__
#define ___DMimicsGroup_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsGroup */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsGroup,0xD9B0DA12,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0DA12-C96C-11D3-B5E7-0060082D5389")
    _DMimicsGroup : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsGroup * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsGroup * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsGroup * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsGroup * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsGroup * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsGroup * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsGroup * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsGroupVtbl;

    interface _DMimicsGroup
    {
        CONST_VTBL struct _DMimicsGroupVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsGroup_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsGroup_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsGroup_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsGroup_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsGroup_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsGroup_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsGroup_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsGroup_DISPINTERFACE_DEFINED__ */


#ifndef ___DMimicsGroupEvents_DISPINTERFACE_DEFINED__
#define ___DMimicsGroupEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMimicsGroupEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DMimicsGroupEvents,0xD9B0DA13,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D9B0DA13-C96C-11D3-B5E7-0060082D5389")
    _DMimicsGroupEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMimicsGroupEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMimicsGroupEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMimicsGroupEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMimicsGroupEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMimicsGroupEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMimicsGroupEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMimicsGroupEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMimicsGroupEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMimicsGroupEventsVtbl;

    interface _DMimicsGroupEvents
    {
        CONST_VTBL struct _DMimicsGroupEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMimicsGroupEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMimicsGroupEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMimicsGroupEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMimicsGroupEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMimicsGroupEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMimicsGroupEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMimicsGroupEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMimicsGroupEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MimicsGroup,0xD9B0DA14,0xC96C,0x11D3,0xB5,0xE7,0x00,0x60,0x08,0x2D,0x53,0x89);

#ifdef __cplusplus

class DECLSPEC_UUID("D9B0DA14-C96C-11D3-B5E7-0060082D5389")
MimicsGroup;
#endif
#endif /* __MIMICSLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


