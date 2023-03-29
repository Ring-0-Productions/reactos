

/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 501
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __d3d10_1_h__
#define __d3d10_1_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __ID3D10BlendState1_FWD_DEFINED__
#define __ID3D10BlendState1_FWD_DEFINED__
typedef interface ID3D10BlendState1 ID3D10BlendState1;

#endif 	/* __ID3D10BlendState1_FWD_DEFINED__ */


#ifndef __ID3D10ShaderResourceView1_FWD_DEFINED__
#define __ID3D10ShaderResourceView1_FWD_DEFINED__
typedef interface ID3D10ShaderResourceView1 ID3D10ShaderResourceView1;

#endif 	/* __ID3D10ShaderResourceView1_FWD_DEFINED__ */


#ifndef __ID3D10Device1_FWD_DEFINED__
#define __ID3D10Device1_FWD_DEFINED__
typedef interface ID3D10Device1 ID3D10Device1;

#endif 	/* __ID3D10Device1_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_d3d10_1_0000_0000 */
/* [local] */ 

#if defined( __d3d10_h__ ) && !defined( D3D10_ARBITRARY_HEADER_ORDERING )
#error d3d10.h is included before d3d10_1.h, and it will confuse tools that honor SAL annotations. \
If possibly targeting d3d10.1, include d3d10_1.h instead of d3d10.h, or ensure d3d10_1.h is included before d3d10.h
#endif
#ifndef _D3D10_1_CONSTANTS
#define _D3D10_1_CONSTANTS
#define	D3D10_1_DEFAULT_SAMPLE_MASK	( 0xffffffff )

#define D3D10_1_FLOAT16_FUSED_TOLERANCE_IN_ULP	( 0.6 )
#define D3D10_1_FLOAT32_TO_INTEGER_TOLERANCE_IN_ULP	( 0.6f )
#define	D3D10_1_GS_INPUT_REGISTER_COUNT	( 32 )

#define	D3D10_1_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT	( 32 )

#define	D3D10_1_IA_VERTEX_INPUT_STRUCTURE_ELEMENTS_COMPONENTS	( 128 )

#define	D3D10_1_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT	( 32 )

#define	D3D10_1_PS_OUTPUT_MASK_REGISTER_COMPONENTS	( 1 )

#define	D3D10_1_PS_OUTPUT_MASK_REGISTER_COMPONENT_BIT_COUNT	( 32 )

#define	D3D10_1_PS_OUTPUT_MASK_REGISTER_COUNT	( 1 )

#define	D3D10_1_SHADER_MAJOR_VERSION	( 4 )

#define	D3D10_1_SHADER_MINOR_VERSION	( 1 )

#define	D3D10_1_SO_BUFFER_MAX_STRIDE_IN_BYTES	( 2048 )

#define	D3D10_1_SO_BUFFER_MAX_WRITE_WINDOW_IN_BYTES	( 256 )

#define	D3D10_1_SO_BUFFER_SLOT_COUNT	( 4 )

#define	D3D10_1_SO_MULTIPLE_BUFFER_ELEMENTS_PER_BUFFER	( 1 )

#define	D3D10_1_SO_SINGLE_BUFFER_COMPONENT_LIMIT	( 64 )

#define	D3D10_1_STANDARD_VERTEX_ELEMENT_COUNT	( 32 )

#define	D3D10_1_SUBPIXEL_FRACTIONAL_BIT_COUNT	( 8 )

#define	D3D10_1_VS_INPUT_REGISTER_COUNT	( 32 )

#define	D3D10_1_VS_OUTPUT_REGISTER_COUNT	( 32 )

#endif
#include <winapifamily.h>
#include "d3d10.h" //
#if !defined(__GNUC__) && !defined(__clang__)
#pragma region Desktop Family
#endif
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

typedef 
enum D3D10_FEATURE_LEVEL1
    {
        D3D10_FEATURE_LEVEL_10_0	= 0xa000,
        D3D10_FEATURE_LEVEL_10_1	= 0xa100,
        D3D10_FEATURE_LEVEL_9_1	= 0x9100,
        D3D10_FEATURE_LEVEL_9_2	= 0x9200,
        D3D10_FEATURE_LEVEL_9_3	= 0x9300
    } 	D3D10_FEATURE_LEVEL1;

typedef struct D3D10_RENDER_TARGET_BLEND_DESC1
    {
    BOOL BlendEnable;
    D3D10_BLEND SrcBlend;
    D3D10_BLEND DestBlend;
    D3D10_BLEND_OP BlendOp;
    D3D10_BLEND SrcBlendAlpha;
    D3D10_BLEND DestBlendAlpha;
    D3D10_BLEND_OP BlendOpAlpha;
    UINT8 RenderTargetWriteMask;
    } 	D3D10_RENDER_TARGET_BLEND_DESC1;

typedef struct D3D10_BLEND_DESC1
    {
    BOOL AlphaToCoverageEnable;
    BOOL IndependentBlendEnable;
    D3D10_RENDER_TARGET_BLEND_DESC1 RenderTarget[ 8 ];
    } 	D3D10_BLEND_DESC1;



extern RPC_IF_HANDLE __MIDL_itf_d3d10_1_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d10_1_0000_0000_v0_0_s_ifspec;

#ifndef __ID3D10BlendState1_INTERFACE_DEFINED__
#define __ID3D10BlendState1_INTERFACE_DEFINED__

/* interface ID3D10BlendState1 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D10BlendState1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EDAD8D99-8A35-4d6d-8566-2EA276CDE161")
    ID3D10BlendState1 : public ID3D10BlendState
    {
    public:
        virtual void STDMETHODCALLTYPE GetDesc1( 
            /* [annotation] */ 
            _Out_  D3D10_BLEND_DESC1 *pDesc) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D10BlendState1Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D10BlendState1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D10BlendState1 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D10BlendState1 * This);
        
        DECLSPEC_XFGVIRT(ID3D10DeviceChild, GetDevice)
        void ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D10BlendState1 * This,
            /* [annotation] */ 
            _Out_  ID3D10Device **ppDevice);
        
        DECLSPEC_XFGVIRT(ID3D10DeviceChild, GetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D10BlendState1 * This,
            /* [annotation] */ 
            _In_  REFGUID guid,
            /* [annotation] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation] */ 
            _Out_writes_bytes_opt_(*pDataSize)  void *pData);
        
        DECLSPEC_XFGVIRT(ID3D10DeviceChild, SetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D10BlendState1 * This,
            /* [annotation] */ 
            _In_  REFGUID guid,
            /* [annotation] */ 
            _In_  UINT DataSize,
            /* [annotation] */ 
            _In_reads_bytes_opt_(DataSize)  const void *pData);
        
        DECLSPEC_XFGVIRT(ID3D10DeviceChild, SetPrivateDataInterface)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D10BlendState1 * This,
            /* [annotation] */ 
            _In_  REFGUID guid,
            /* [annotation] */ 
            _In_opt_  const IUnknown *pData);
        
        DECLSPEC_XFGVIRT(ID3D10BlendState, GetDesc)
        void ( STDMETHODCALLTYPE *GetDesc )( 
            ID3D10BlendState1 * This,
            /* [annotation] */ 
            _Out_  D3D10_BLEND_DESC *pDesc);
        
        DECLSPEC_XFGVIRT(ID3D10BlendState1, GetDesc1)
        void ( STDMETHODCALLTYPE *GetDesc1 )( 
            ID3D10BlendState1 * This,
            /* [annotation] */ 
            _Out_  D3D10_BLEND_DESC1 *pDesc);
        
        END_INTERFACE
    } ID3D10BlendState1Vtbl;

    interface ID3D10BlendState1
    {
        CONST_VTBL struct ID3D10BlendState1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D10BlendState1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D10BlendState1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D10BlendState1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D10BlendState1_GetDevice(This,ppDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,ppDevice) ) 

#define ID3D10BlendState1_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D10BlendState1_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D10BlendState1_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 


#define ID3D10BlendState1_GetDesc(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc(This,pDesc) ) 


#define ID3D10BlendState1_GetDesc1(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc1(This,pDesc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D10BlendState1_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d10_1_0000_0001 */
/* [local] */ 

typedef struct D3D10_TEXCUBE_ARRAY_SRV1
    {
    UINT MostDetailedMip;
    UINT MipLevels;
    UINT First2DArrayFace;
    UINT NumCubes;
    } 	D3D10_TEXCUBE_ARRAY_SRV1;

typedef D3D_SRV_DIMENSION D3D10_SRV_DIMENSION1;

typedef struct D3D10_SHADER_RESOURCE_VIEW_DESC1
    {
    DXGI_FORMAT Format;
    D3D10_SRV_DIMENSION1 ViewDimension;
    union 
        {
        D3D10_BUFFER_SRV Buffer;
        D3D10_TEX1D_SRV Texture1D;
        D3D10_TEX1D_ARRAY_SRV Texture1DArray;
        D3D10_TEX2D_SRV Texture2D;
        D3D10_TEX2D_ARRAY_SRV Texture2DArray;
        D3D10_TEX2DMS_SRV Texture2DMS;
        D3D10_TEX2DMS_ARRAY_SRV Texture2DMSArray;
        D3D10_TEX3D_SRV Texture3D;
        D3D10_TEXCUBE_SRV TextureCube;
        D3D10_TEXCUBE_ARRAY_SRV1 TextureCubeArray;
        } 	;
    } 	D3D10_SHADER_RESOURCE_VIEW_DESC1;



extern RPC_IF_HANDLE __MIDL_itf_d3d10_1_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d10_1_0000_0001_v0_0_s_ifspec;

#ifndef __ID3D10ShaderResourceView1_INTERFACE_DEFINED__
#define __ID3D10ShaderResourceView1_INTERFACE_DEFINED__

/* interface ID3D10ShaderResourceView1 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D10ShaderResourceView1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B7E4C87-342C-4106-A19F-4F2704F689F0")
    ID3D10ShaderResourceView1 : public ID3D10ShaderResourceView
    {
    public:
        virtual void STDMETHODCALLTYPE GetDesc1( 
            /* [annotation] */ 
            _Out_  D3D10_SHADER_RESOURCE_VIEW_DESC1 *pDesc) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D10ShaderResourceView1Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D10ShaderResourceView1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D10ShaderResourceView1 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D10ShaderResourceView1 * This);
        
        DECLSPEC_XFGVIRT(ID3D10DeviceChild, GetDevice)
        void ( STDMETHODCALLTYPE *GetDevice )( 
            ID3D10ShaderResourceView1 * This,
            /* [annotation] */ 
            _Out_  ID3D10Device **ppDevice);
        
        DECLSPEC_XFGVIRT(ID3D10DeviceChild, GetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D10ShaderResourceView1 * This,
            /* [annotation] */ 
            _In_  REFGUID guid,
            /* [annotation] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation] */ 
            _Out_writes_bytes_opt_(*pDataSize)  void *pData);
        
        DECLSPEC_XFGVIRT(ID3D10DeviceChild, SetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D10ShaderResourceView1 * This,
            /* [annotation] */ 
            _In_  REFGUID guid,
            /* [annotation] */ 
            _In_  UINT DataSize,
            /* [annotation] */ 
            _In_reads_bytes_opt_(DataSize)  const void *pData);
        
        DECLSPEC_XFGVIRT(ID3D10DeviceChild, SetPrivateDataInterface)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D10ShaderResourceView1 * This,
            /* [annotation] */ 
            _In_  REFGUID guid,
            /* [annotation] */ 
            _In_opt_  const IUnknown *pData);
        
        DECLSPEC_XFGVIRT(ID3D10View, GetResource)
        void ( STDMETHODCALLTYPE *GetResource )( 
            ID3D10ShaderResourceView1 * This,
            /* [annotation] */ 
            _Out_  ID3D10Resource **ppResource);
        
        DECLSPEC_XFGVIRT(ID3D10ShaderResourceView, GetDesc)
        void ( STDMETHODCALLTYPE *GetDesc )( 
            ID3D10ShaderResourceView1 * This,
            /* [annotation] */ 
            _Out_  D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc);
        
        DECLSPEC_XFGVIRT(ID3D10ShaderResourceView1, GetDesc1)
        void ( STDMETHODCALLTYPE *GetDesc1 )( 
            ID3D10ShaderResourceView1 * This,
            /* [annotation] */ 
            _Out_  D3D10_SHADER_RESOURCE_VIEW_DESC1 *pDesc);
        
        END_INTERFACE
    } ID3D10ShaderResourceView1Vtbl;

    interface ID3D10ShaderResourceView1
    {
        CONST_VTBL struct ID3D10ShaderResourceView1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D10ShaderResourceView1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D10ShaderResourceView1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D10ShaderResourceView1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D10ShaderResourceView1_GetDevice(This,ppDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,ppDevice) ) 

#define ID3D10ShaderResourceView1_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D10ShaderResourceView1_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D10ShaderResourceView1_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 


#define ID3D10ShaderResourceView1_GetResource(This,ppResource)	\
    ( (This)->lpVtbl -> GetResource(This,ppResource) ) 


#define ID3D10ShaderResourceView1_GetDesc(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc(This,pDesc) ) 


#define ID3D10ShaderResourceView1_GetDesc1(This,pDesc)	\
    ( (This)->lpVtbl -> GetDesc1(This,pDesc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D10ShaderResourceView1_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d10_1_0000_0002 */
/* [local] */ 

typedef 
enum D3D10_STANDARD_MULTISAMPLE_QUALITY_LEVELS
    {
        D3D10_STANDARD_MULTISAMPLE_PATTERN	= 0xffffffff,
        D3D10_CENTER_MULTISAMPLE_PATTERN	= 0xfffffffe
    } 	D3D10_STANDARD_MULTISAMPLE_QUALITY_LEVELS;



extern RPC_IF_HANDLE __MIDL_itf_d3d10_1_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d10_1_0000_0002_v0_0_s_ifspec;

#ifndef __ID3D10Device1_INTERFACE_DEFINED__
#define __ID3D10Device1_INTERFACE_DEFINED__

/* interface ID3D10Device1 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_ID3D10Device1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B7E4C8F-342C-4106-A19F-4F2704F689F0")
    ID3D10Device1 : public ID3D10Device
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView1( 
            /* [annotation] */ 
            _In_  ID3D10Resource *pResource,
            /* [annotation] */ 
            _In_opt_  const D3D10_SHADER_RESOURCE_VIEW_DESC1 *pDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10ShaderResourceView1 **ppSRView) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateBlendState1( 
            /* [annotation] */ 
            _In_  const D3D10_BLEND_DESC1 *pBlendStateDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10BlendState1 **ppBlendState) = 0;
        
        virtual D3D10_FEATURE_LEVEL1 STDMETHODCALLTYPE GetFeatureLevel( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ID3D10Device1Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ID3D10Device1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ID3D10Device1 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ID3D10Device1 * This);
        
        DECLSPEC_XFGVIRT(ID3D10Device, VSSetConstantBuffers)
        void ( STDMETHODCALLTYPE *VSSetConstantBuffers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
            /* [annotation] */ 
            _In_reads_opt_(NumBuffers)  ID3D10Buffer *const *ppConstantBuffers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, PSSetShaderResources)
        void ( STDMETHODCALLTYPE *PSSetShaderResources )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
            /* [annotation] */ 
            _In_reads_opt_(NumViews)  ID3D10ShaderResourceView *const *ppShaderResourceViews);
        
        DECLSPEC_XFGVIRT(ID3D10Device, PSSetShader)
        void ( STDMETHODCALLTYPE *PSSetShader )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_opt_  ID3D10PixelShader *pPixelShader);
        
        DECLSPEC_XFGVIRT(ID3D10Device, PSSetSamplers)
        void ( STDMETHODCALLTYPE *PSSetSamplers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
            /* [annotation] */ 
            _In_reads_opt_(NumSamplers)  ID3D10SamplerState *const *ppSamplers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, VSSetShader)
        void ( STDMETHODCALLTYPE *VSSetShader )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_opt_  ID3D10VertexShader *pVertexShader);
        
        DECLSPEC_XFGVIRT(ID3D10Device, DrawIndexed)
        void ( STDMETHODCALLTYPE *DrawIndexed )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  UINT IndexCount,
            /* [annotation] */ 
            _In_  UINT StartIndexLocation,
            /* [annotation] */ 
            _In_  INT BaseVertexLocation);
        
        DECLSPEC_XFGVIRT(ID3D10Device, Draw)
        void ( STDMETHODCALLTYPE *Draw )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  UINT VertexCount,
            /* [annotation] */ 
            _In_  UINT StartVertexLocation);
        
        DECLSPEC_XFGVIRT(ID3D10Device, PSSetConstantBuffers)
        void ( STDMETHODCALLTYPE *PSSetConstantBuffers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
            /* [annotation] */ 
            _In_reads_opt_(NumBuffers)  ID3D10Buffer *const *ppConstantBuffers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, IASetInputLayout)
        void ( STDMETHODCALLTYPE *IASetInputLayout )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_opt_  ID3D10InputLayout *pInputLayout);
        
        DECLSPEC_XFGVIRT(ID3D10Device, IASetVertexBuffers)
        void ( STDMETHODCALLTYPE *IASetVertexBuffers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_1_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_1_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumBuffers,
            /* [annotation] */ 
            _In_reads_opt_(NumBuffers)  ID3D10Buffer *const *ppVertexBuffers,
            /* [annotation] */ 
            _In_reads_opt_(NumBuffers)  const UINT *pStrides,
            /* [annotation] */ 
            _In_reads_opt_(NumBuffers)  const UINT *pOffsets);
        
        DECLSPEC_XFGVIRT(ID3D10Device, IASetIndexBuffer)
        void ( STDMETHODCALLTYPE *IASetIndexBuffer )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_opt_  ID3D10Buffer *pIndexBuffer,
            /* [annotation] */ 
            _In_  DXGI_FORMAT Format,
            /* [annotation] */ 
            _In_  UINT Offset);
        
        DECLSPEC_XFGVIRT(ID3D10Device, DrawIndexedInstanced)
        void ( STDMETHODCALLTYPE *DrawIndexedInstanced )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  UINT IndexCountPerInstance,
            /* [annotation] */ 
            _In_  UINT InstanceCount,
            /* [annotation] */ 
            _In_  UINT StartIndexLocation,
            /* [annotation] */ 
            _In_  INT BaseVertexLocation,
            /* [annotation] */ 
            _In_  UINT StartInstanceLocation);
        
        DECLSPEC_XFGVIRT(ID3D10Device, DrawInstanced)
        void ( STDMETHODCALLTYPE *DrawInstanced )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  UINT VertexCountPerInstance,
            /* [annotation] */ 
            _In_  UINT InstanceCount,
            /* [annotation] */ 
            _In_  UINT StartVertexLocation,
            /* [annotation] */ 
            _In_  UINT StartInstanceLocation);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GSSetConstantBuffers)
        void ( STDMETHODCALLTYPE *GSSetConstantBuffers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
            /* [annotation] */ 
            _In_reads_opt_(NumBuffers)  ID3D10Buffer *const *ppConstantBuffers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GSSetShader)
        void ( STDMETHODCALLTYPE *GSSetShader )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_opt_  ID3D10GeometryShader *pShader);
        
        DECLSPEC_XFGVIRT(ID3D10Device, IASetPrimitiveTopology)
        void ( STDMETHODCALLTYPE *IASetPrimitiveTopology )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  D3D10_PRIMITIVE_TOPOLOGY Topology);
        
        DECLSPEC_XFGVIRT(ID3D10Device, VSSetShaderResources)
        void ( STDMETHODCALLTYPE *VSSetShaderResources )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
            /* [annotation] */ 
            _In_reads_opt_(NumViews)  ID3D10ShaderResourceView *const *ppShaderResourceViews);
        
        DECLSPEC_XFGVIRT(ID3D10Device, VSSetSamplers)
        void ( STDMETHODCALLTYPE *VSSetSamplers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
            /* [annotation] */ 
            _In_reads_opt_(NumSamplers)  ID3D10SamplerState *const *ppSamplers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, SetPredication)
        void ( STDMETHODCALLTYPE *SetPredication )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_opt_  ID3D10Predicate *pPredicate,
            /* [annotation] */ 
            _In_  BOOL PredicateValue);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GSSetShaderResources)
        void ( STDMETHODCALLTYPE *GSSetShaderResources )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
            /* [annotation] */ 
            _In_reads_opt_(NumViews)  ID3D10ShaderResourceView *const *ppShaderResourceViews);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GSSetSamplers)
        void ( STDMETHODCALLTYPE *GSSetSamplers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
            /* [annotation] */ 
            _In_reads_opt_(NumSamplers)  ID3D10SamplerState *const *ppSamplers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, OMSetRenderTargets)
        void ( STDMETHODCALLTYPE *OMSetRenderTargets )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT )  UINT NumViews,
            /* [annotation] */ 
            _In_reads_opt_(NumViews)  ID3D10RenderTargetView *const *ppRenderTargetViews,
            /* [annotation] */ 
            _In_opt_  ID3D10DepthStencilView *pDepthStencilView);
        
        DECLSPEC_XFGVIRT(ID3D10Device, OMSetBlendState)
        void ( STDMETHODCALLTYPE *OMSetBlendState )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_opt_  ID3D10BlendState *pBlendState,
            /* [annotation] */ 
            _In_  const FLOAT BlendFactor[ 4 ],
            /* [annotation] */ 
            _In_  UINT SampleMask);
        
        DECLSPEC_XFGVIRT(ID3D10Device, OMSetDepthStencilState)
        void ( STDMETHODCALLTYPE *OMSetDepthStencilState )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_opt_  ID3D10DepthStencilState *pDepthStencilState,
            /* [annotation] */ 
            _In_  UINT StencilRef);
        
        DECLSPEC_XFGVIRT(ID3D10Device, SOSetTargets)
        void ( STDMETHODCALLTYPE *SOSetTargets )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_SO_BUFFER_SLOT_COUNT)  UINT NumBuffers,
            /* [annotation] */ 
            _In_reads_opt_(NumBuffers)  ID3D10Buffer *const *ppSOTargets,
            /* [annotation] */ 
            _In_reads_opt_(NumBuffers)  const UINT *pOffsets);
        
        DECLSPEC_XFGVIRT(ID3D10Device, DrawAuto)
        void ( STDMETHODCALLTYPE *DrawAuto )( 
            ID3D10Device1 * This);
        
        DECLSPEC_XFGVIRT(ID3D10Device, RSSetState)
        void ( STDMETHODCALLTYPE *RSSetState )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_opt_  ID3D10RasterizerState *pRasterizerState);
        
        DECLSPEC_XFGVIRT(ID3D10Device, RSSetViewports)
        void ( STDMETHODCALLTYPE *RSSetViewports )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_(0, D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT NumViewports,
            /* [annotation] */ 
            _In_reads_opt_(NumViewports)  const D3D10_VIEWPORT *pViewports);
        
        DECLSPEC_XFGVIRT(ID3D10Device, RSSetScissorRects)
        void ( STDMETHODCALLTYPE *RSSetScissorRects )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_(0, D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT NumRects,
            /* [annotation] */ 
            _In_reads_opt_(NumRects)  const D3D10_RECT *pRects);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CopySubresourceRegion)
        void ( STDMETHODCALLTYPE *CopySubresourceRegion )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10Resource *pDstResource,
            /* [annotation] */ 
            _In_  UINT DstSubresource,
            /* [annotation] */ 
            _In_  UINT DstX,
            /* [annotation] */ 
            _In_  UINT DstY,
            /* [annotation] */ 
            _In_  UINT DstZ,
            /* [annotation] */ 
            _In_  ID3D10Resource *pSrcResource,
            /* [annotation] */ 
            _In_  UINT SrcSubresource,
            /* [annotation] */ 
            _In_opt_  const D3D10_BOX *pSrcBox);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CopyResource)
        void ( STDMETHODCALLTYPE *CopyResource )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10Resource *pDstResource,
            /* [annotation] */ 
            _In_  ID3D10Resource *pSrcResource);
        
        DECLSPEC_XFGVIRT(ID3D10Device, UpdateSubresource)
        void ( STDMETHODCALLTYPE *UpdateSubresource )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10Resource *pDstResource,
            /* [annotation] */ 
            _In_  UINT DstSubresource,
            /* [annotation] */ 
            _In_opt_  const D3D10_BOX *pDstBox,
            /* [annotation] */ 
            _In_  const void *pSrcData,
            /* [annotation] */ 
            _In_  UINT SrcRowPitch,
            /* [annotation] */ 
            _In_  UINT SrcDepthPitch);
        
        DECLSPEC_XFGVIRT(ID3D10Device, ClearRenderTargetView)
        void ( STDMETHODCALLTYPE *ClearRenderTargetView )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10RenderTargetView *pRenderTargetView,
            /* [annotation] */ 
            _In_  const FLOAT ColorRGBA[ 4 ]);
        
        DECLSPEC_XFGVIRT(ID3D10Device, ClearDepthStencilView)
        void ( STDMETHODCALLTYPE *ClearDepthStencilView )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10DepthStencilView *pDepthStencilView,
            /* [annotation] */ 
            _In_  UINT ClearFlags,
            /* [annotation] */ 
            _In_  FLOAT Depth,
            /* [annotation] */ 
            _In_  UINT8 Stencil);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GenerateMips)
        void ( STDMETHODCALLTYPE *GenerateMips )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10ShaderResourceView *pShaderResourceView);
        
        DECLSPEC_XFGVIRT(ID3D10Device, ResolveSubresource)
        void ( STDMETHODCALLTYPE *ResolveSubresource )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10Resource *pDstResource,
            /* [annotation] */ 
            _In_  UINT DstSubresource,
            /* [annotation] */ 
            _In_  ID3D10Resource *pSrcResource,
            /* [annotation] */ 
            _In_  UINT SrcSubresource,
            /* [annotation] */ 
            _In_  DXGI_FORMAT Format);
        
        DECLSPEC_XFGVIRT(ID3D10Device, VSGetConstantBuffers)
        void ( STDMETHODCALLTYPE *VSGetConstantBuffers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
            /* [annotation] */ 
            _Out_writes_opt_(NumBuffers)  ID3D10Buffer **ppConstantBuffers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, PSGetShaderResources)
        void ( STDMETHODCALLTYPE *PSGetShaderResources )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
            /* [annotation] */ 
            _Out_writes_opt_(NumViews)  ID3D10ShaderResourceView **ppShaderResourceViews);
        
        DECLSPEC_XFGVIRT(ID3D10Device, PSGetShader)
        void ( STDMETHODCALLTYPE *PSGetShader )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_  ID3D10PixelShader **ppPixelShader);
        
        DECLSPEC_XFGVIRT(ID3D10Device, PSGetSamplers)
        void ( STDMETHODCALLTYPE *PSGetSamplers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
            /* [annotation] */ 
            _Out_writes_opt_(NumSamplers)  ID3D10SamplerState **ppSamplers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, VSGetShader)
        void ( STDMETHODCALLTYPE *VSGetShader )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_  ID3D10VertexShader **ppVertexShader);
        
        DECLSPEC_XFGVIRT(ID3D10Device, PSGetConstantBuffers)
        void ( STDMETHODCALLTYPE *PSGetConstantBuffers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
            /* [annotation] */ 
            _Out_writes_opt_(NumBuffers)  ID3D10Buffer **ppConstantBuffers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, IAGetInputLayout)
        void ( STDMETHODCALLTYPE *IAGetInputLayout )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_  ID3D10InputLayout **ppInputLayout);
        
        DECLSPEC_XFGVIRT(ID3D10Device, IAGetVertexBuffers)
        void ( STDMETHODCALLTYPE *IAGetVertexBuffers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_1_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_1_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumBuffers,
            /* [annotation] */ 
            _Out_writes_opt_(NumBuffers)  ID3D10Buffer **ppVertexBuffers,
            /* [annotation] */ 
            _Out_writes_opt_(NumBuffers)  UINT *pStrides,
            /* [annotation] */ 
            _Out_writes_opt_(NumBuffers)  UINT *pOffsets);
        
        DECLSPEC_XFGVIRT(ID3D10Device, IAGetIndexBuffer)
        void ( STDMETHODCALLTYPE *IAGetIndexBuffer )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_opt_  ID3D10Buffer **pIndexBuffer,
            /* [annotation] */ 
            _Out_opt_  DXGI_FORMAT *Format,
            /* [annotation] */ 
            _Out_opt_  UINT *Offset);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GSGetConstantBuffers)
        void ( STDMETHODCALLTYPE *GSGetConstantBuffers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - StartSlot )  UINT NumBuffers,
            /* [annotation] */ 
            _Out_writes_opt_(NumBuffers)  ID3D10Buffer **ppConstantBuffers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GSGetShader)
        void ( STDMETHODCALLTYPE *GSGetShader )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_  ID3D10GeometryShader **ppGeometryShader);
        
        DECLSPEC_XFGVIRT(ID3D10Device, IAGetPrimitiveTopology)
        void ( STDMETHODCALLTYPE *IAGetPrimitiveTopology )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_  D3D10_PRIMITIVE_TOPOLOGY *pTopology);
        
        DECLSPEC_XFGVIRT(ID3D10Device, VSGetShaderResources)
        void ( STDMETHODCALLTYPE *VSGetShaderResources )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
            /* [annotation] */ 
            _Out_writes_opt_(NumViews)  ID3D10ShaderResourceView **ppShaderResourceViews);
        
        DECLSPEC_XFGVIRT(ID3D10Device, VSGetSamplers)
        void ( STDMETHODCALLTYPE *VSGetSamplers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
            /* [annotation] */ 
            _Out_writes_opt_(NumSamplers)  ID3D10SamplerState **ppSamplers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GetPredication)
        void ( STDMETHODCALLTYPE *GetPredication )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_opt_  ID3D10Predicate **ppPredicate,
            /* [annotation] */ 
            _Out_opt_  BOOL *pPredicateValue);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GSGetShaderResources)
        void ( STDMETHODCALLTYPE *GSGetShaderResources )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - StartSlot )  UINT NumViews,
            /* [annotation] */ 
            _Out_writes_opt_(NumViews)  ID3D10ShaderResourceView **ppShaderResourceViews);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GSGetSamplers)
        void ( STDMETHODCALLTYPE *GSGetSamplers )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - 1 )  UINT StartSlot,
            /* [annotation] */ 
            _In_range_( 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT - StartSlot )  UINT NumSamplers,
            /* [annotation] */ 
            _Out_writes_opt_(NumSamplers)  ID3D10SamplerState **ppSamplers);
        
        DECLSPEC_XFGVIRT(ID3D10Device, OMGetRenderTargets)
        void ( STDMETHODCALLTYPE *OMGetRenderTargets )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT )  UINT NumViews,
            /* [annotation] */ 
            _Out_writes_opt_(NumViews)  ID3D10RenderTargetView **ppRenderTargetViews,
            /* [annotation] */ 
            _Out_opt_  ID3D10DepthStencilView **ppDepthStencilView);
        
        DECLSPEC_XFGVIRT(ID3D10Device, OMGetBlendState)
        void ( STDMETHODCALLTYPE *OMGetBlendState )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_opt_  ID3D10BlendState **ppBlendState,
            /* [annotation] */ 
            _Out_opt_  FLOAT BlendFactor[ 4 ],
            /* [annotation] */ 
            _Out_opt_  UINT *pSampleMask);
        
        DECLSPEC_XFGVIRT(ID3D10Device, OMGetDepthStencilState)
        void ( STDMETHODCALLTYPE *OMGetDepthStencilState )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_opt_  ID3D10DepthStencilState **ppDepthStencilState,
            /* [annotation] */ 
            _Out_opt_  UINT *pStencilRef);
        
        DECLSPEC_XFGVIRT(ID3D10Device, SOGetTargets)
        void ( STDMETHODCALLTYPE *SOGetTargets )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_range_( 0, D3D10_SO_BUFFER_SLOT_COUNT )  UINT NumBuffers,
            /* [annotation] */ 
            _Out_writes_opt_(NumBuffers)  ID3D10Buffer **ppSOTargets,
            /* [annotation] */ 
            _Out_writes_opt_(NumBuffers)  UINT *pOffsets);
        
        DECLSPEC_XFGVIRT(ID3D10Device, RSGetState)
        void ( STDMETHODCALLTYPE *RSGetState )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_  ID3D10RasterizerState **ppRasterizerState);
        
        DECLSPEC_XFGVIRT(ID3D10Device, RSGetViewports)
        void ( STDMETHODCALLTYPE *RSGetViewports )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Inout_ /*_range(0, D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )*/   UINT *NumViewports,
            /* [annotation] */ 
            _Out_writes_opt_(*NumViewports)  D3D10_VIEWPORT *pViewports);
        
        DECLSPEC_XFGVIRT(ID3D10Device, RSGetScissorRects)
        void ( STDMETHODCALLTYPE *RSGetScissorRects )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Inout_ /*_range(0, D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE )*/   UINT *NumRects,
            /* [annotation] */ 
            _Out_writes_opt_(*NumRects)  D3D10_RECT *pRects);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GetDeviceRemovedReason)
        HRESULT ( STDMETHODCALLTYPE *GetDeviceRemovedReason )( 
            ID3D10Device1 * This);
        
        DECLSPEC_XFGVIRT(ID3D10Device, SetExceptionMode)
        HRESULT ( STDMETHODCALLTYPE *SetExceptionMode )( 
            ID3D10Device1 * This,
            UINT RaiseFlags);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GetExceptionMode)
        UINT ( STDMETHODCALLTYPE *GetExceptionMode )( 
            ID3D10Device1 * This);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *GetPrivateData )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  REFGUID guid,
            /* [annotation] */ 
            _Inout_  UINT *pDataSize,
            /* [annotation] */ 
            _Out_writes_bytes_opt_(*pDataSize)  void *pData);
        
        DECLSPEC_XFGVIRT(ID3D10Device, SetPrivateData)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateData )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  REFGUID guid,
            /* [annotation] */ 
            _In_  UINT DataSize,
            /* [annotation] */ 
            _In_reads_bytes_opt_(DataSize)  const void *pData);
        
        DECLSPEC_XFGVIRT(ID3D10Device, SetPrivateDataInterface)
        HRESULT ( STDMETHODCALLTYPE *SetPrivateDataInterface )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  REFGUID guid,
            /* [annotation] */ 
            _In_opt_  const IUnknown *pData);
        
        DECLSPEC_XFGVIRT(ID3D10Device, ClearState)
        void ( STDMETHODCALLTYPE *ClearState )( 
            ID3D10Device1 * This);
        
        DECLSPEC_XFGVIRT(ID3D10Device, Flush)
        void ( STDMETHODCALLTYPE *Flush )( 
            ID3D10Device1 * This);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateBuffer)
        HRESULT ( STDMETHODCALLTYPE *CreateBuffer )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_BUFFER_DESC *pDesc,
            /* [annotation] */ 
            _In_opt_  const D3D10_SUBRESOURCE_DATA *pInitialData,
            /* [annotation] */ 
            _Out_opt_  ID3D10Buffer **ppBuffer);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateTexture1D)
        HRESULT ( STDMETHODCALLTYPE *CreateTexture1D )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_TEXTURE1D_DESC *pDesc,
            /* [annotation] */ 
            _In_reads_opt_(_Inexpressible_(pDesc->MipLevels * pDesc->ArraySize))  const D3D10_SUBRESOURCE_DATA *pInitialData,
            /* [annotation] */ 
            _Out_  ID3D10Texture1D **ppTexture1D);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateTexture2D)
        HRESULT ( STDMETHODCALLTYPE *CreateTexture2D )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_TEXTURE2D_DESC *pDesc,
            /* [annotation] */ 
            _In_reads_opt_(_Inexpressible_(pDesc->MipLevels * pDesc->ArraySize))  const D3D10_SUBRESOURCE_DATA *pInitialData,
            /* [annotation] */ 
            _Out_  ID3D10Texture2D **ppTexture2D);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateTexture3D)
        HRESULT ( STDMETHODCALLTYPE *CreateTexture3D )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_TEXTURE3D_DESC *pDesc,
            /* [annotation] */ 
            _In_reads_opt_(_Inexpressible_(pDesc->MipLevels))  const D3D10_SUBRESOURCE_DATA *pInitialData,
            /* [annotation] */ 
            _Out_  ID3D10Texture3D **ppTexture3D);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateShaderResourceView)
        HRESULT ( STDMETHODCALLTYPE *CreateShaderResourceView )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10Resource *pResource,
            /* [annotation] */ 
            _In_opt_  const D3D10_SHADER_RESOURCE_VIEW_DESC *pDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10ShaderResourceView **ppSRView);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateRenderTargetView)
        HRESULT ( STDMETHODCALLTYPE *CreateRenderTargetView )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10Resource *pResource,
            /* [annotation] */ 
            _In_opt_  const D3D10_RENDER_TARGET_VIEW_DESC *pDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10RenderTargetView **ppRTView);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateDepthStencilView)
        HRESULT ( STDMETHODCALLTYPE *CreateDepthStencilView )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10Resource *pResource,
            /* [annotation] */ 
            _In_opt_  const D3D10_DEPTH_STENCIL_VIEW_DESC *pDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10DepthStencilView **ppDepthStencilView);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateInputLayout)
        HRESULT ( STDMETHODCALLTYPE *CreateInputLayout )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_reads_(NumElements)  const D3D10_INPUT_ELEMENT_DESC *pInputElementDescs,
            /* [annotation] */ 
            _In_range_( 0, D3D10_1_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT )  UINT NumElements,
            /* [annotation] */ 
            _In_reads_(BytecodeLength)  const void *pShaderBytecodeWithInputSignature,
            /* [annotation] */ 
            _In_  SIZE_T BytecodeLength,
            /* [annotation] */ 
            _Out_opt_  ID3D10InputLayout **ppInputLayout);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateVertexShader)
        HRESULT ( STDMETHODCALLTYPE *CreateVertexShader )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_reads_(BytecodeLength)  const void *pShaderBytecode,
            /* [annotation] */ 
            _In_  SIZE_T BytecodeLength,
            /* [annotation] */ 
            _Out_opt_  ID3D10VertexShader **ppVertexShader);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateGeometryShader)
        HRESULT ( STDMETHODCALLTYPE *CreateGeometryShader )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_reads_(BytecodeLength)  const void *pShaderBytecode,
            /* [annotation] */ 
            _In_  SIZE_T BytecodeLength,
            /* [annotation] */ 
            _Out_opt_  ID3D10GeometryShader **ppGeometryShader);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateGeometryShaderWithStreamOutput)
        HRESULT ( STDMETHODCALLTYPE *CreateGeometryShaderWithStreamOutput )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_reads_(BytecodeLength)  const void *pShaderBytecode,
            /* [annotation] */ 
            _In_  SIZE_T BytecodeLength,
            /* [annotation] */ 
            _In_reads_opt_(NumEntries)  const D3D10_SO_DECLARATION_ENTRY *pSODeclaration,
            /* [annotation] */ 
            _In_range_( 0, D3D10_SO_SINGLE_BUFFER_COMPONENT_LIMIT )  UINT NumEntries,
            /* [annotation] */ 
            _In_  UINT OutputStreamStride,
            /* [annotation] */ 
            _Out_opt_  ID3D10GeometryShader **ppGeometryShader);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreatePixelShader)
        HRESULT ( STDMETHODCALLTYPE *CreatePixelShader )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_reads_(BytecodeLength)  const void *pShaderBytecode,
            /* [annotation] */ 
            _In_  SIZE_T BytecodeLength,
            /* [annotation] */ 
            _Out_opt_  ID3D10PixelShader **ppPixelShader);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateBlendState)
        HRESULT ( STDMETHODCALLTYPE *CreateBlendState )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_BLEND_DESC *pBlendStateDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10BlendState **ppBlendState);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateDepthStencilState)
        HRESULT ( STDMETHODCALLTYPE *CreateDepthStencilState )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_DEPTH_STENCIL_DESC *pDepthStencilDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10DepthStencilState **ppDepthStencilState);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateRasterizerState)
        HRESULT ( STDMETHODCALLTYPE *CreateRasterizerState )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_RASTERIZER_DESC *pRasterizerDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10RasterizerState **ppRasterizerState);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateSamplerState)
        HRESULT ( STDMETHODCALLTYPE *CreateSamplerState )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_SAMPLER_DESC *pSamplerDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10SamplerState **ppSamplerState);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateQuery)
        HRESULT ( STDMETHODCALLTYPE *CreateQuery )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_QUERY_DESC *pQueryDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10Query **ppQuery);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreatePredicate)
        HRESULT ( STDMETHODCALLTYPE *CreatePredicate )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_QUERY_DESC *pPredicateDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10Predicate **ppPredicate);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CreateCounter)
        HRESULT ( STDMETHODCALLTYPE *CreateCounter )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_COUNTER_DESC *pCounterDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10Counter **ppCounter);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CheckFormatSupport)
        HRESULT ( STDMETHODCALLTYPE *CheckFormatSupport )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  DXGI_FORMAT Format,
            /* [annotation] */ 
            _Out_  UINT *pFormatSupport);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CheckMultisampleQualityLevels)
        HRESULT ( STDMETHODCALLTYPE *CheckMultisampleQualityLevels )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  DXGI_FORMAT Format,
            /* [annotation] */ 
            _In_  UINT SampleCount,
            /* [annotation] */ 
            _Out_  UINT *pNumQualityLevels);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CheckCounterInfo)
        void ( STDMETHODCALLTYPE *CheckCounterInfo )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_  D3D10_COUNTER_INFO *pCounterInfo);
        
        DECLSPEC_XFGVIRT(ID3D10Device, CheckCounter)
        HRESULT ( STDMETHODCALLTYPE *CheckCounter )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_COUNTER_DESC *pDesc,
            /* [annotation] */ 
            _Out_  D3D10_COUNTER_TYPE *pType,
            /* [annotation] */ 
            _Out_  UINT *pActiveCounters,
            /* [annotation] */ 
            _Out_writes_opt_(*pNameLength)  LPSTR szName,
            /* [annotation] */ 
            _Inout_opt_  UINT *pNameLength,
            /* [annotation] */ 
            _Out_writes_opt_(*pUnitsLength)  LPSTR szUnits,
            /* [annotation] */ 
            _Inout_opt_  UINT *pUnitsLength,
            /* [annotation] */ 
            _Out_writes_opt_(*pDescriptionLength)  LPSTR szDescription,
            /* [annotation] */ 
            _Inout_opt_  UINT *pDescriptionLength);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GetCreationFlags)
        UINT ( STDMETHODCALLTYPE *GetCreationFlags )( 
            ID3D10Device1 * This);
        
        DECLSPEC_XFGVIRT(ID3D10Device, OpenSharedResource)
        HRESULT ( STDMETHODCALLTYPE *OpenSharedResource )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  HANDLE hResource,
            /* [annotation] */ 
            _In_  REFIID ReturnedInterface,
            /* [annotation] */ 
            _Out_opt_  void **ppResource);
        
        DECLSPEC_XFGVIRT(ID3D10Device, SetTextFilterSize)
        void ( STDMETHODCALLTYPE *SetTextFilterSize )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  UINT Width,
            /* [annotation] */ 
            _In_  UINT Height);
        
        DECLSPEC_XFGVIRT(ID3D10Device, GetTextFilterSize)
        void ( STDMETHODCALLTYPE *GetTextFilterSize )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _Out_opt_  UINT *pWidth,
            /* [annotation] */ 
            _Out_opt_  UINT *pHeight);
        
        DECLSPEC_XFGVIRT(ID3D10Device1, CreateShaderResourceView1)
        HRESULT ( STDMETHODCALLTYPE *CreateShaderResourceView1 )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  ID3D10Resource *pResource,
            /* [annotation] */ 
            _In_opt_  const D3D10_SHADER_RESOURCE_VIEW_DESC1 *pDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10ShaderResourceView1 **ppSRView);
        
        DECLSPEC_XFGVIRT(ID3D10Device1, CreateBlendState1)
        HRESULT ( STDMETHODCALLTYPE *CreateBlendState1 )( 
            ID3D10Device1 * This,
            /* [annotation] */ 
            _In_  const D3D10_BLEND_DESC1 *pBlendStateDesc,
            /* [annotation] */ 
            _Out_opt_  ID3D10BlendState1 **ppBlendState);
        
        DECLSPEC_XFGVIRT(ID3D10Device1, GetFeatureLevel)
        D3D10_FEATURE_LEVEL1 ( STDMETHODCALLTYPE *GetFeatureLevel )( 
            ID3D10Device1 * This);
        
        END_INTERFACE
    } ID3D10Device1Vtbl;

    interface ID3D10Device1
    {
        CONST_VTBL struct ID3D10Device1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ID3D10Device1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D10Device1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D10Device1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D10Device1_VSSetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers)	\
    ( (This)->lpVtbl -> VSSetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers) ) 

#define ID3D10Device1_PSSetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews)	\
    ( (This)->lpVtbl -> PSSetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews) ) 

#define ID3D10Device1_PSSetShader(This,pPixelShader)	\
    ( (This)->lpVtbl -> PSSetShader(This,pPixelShader) ) 

#define ID3D10Device1_PSSetSamplers(This,StartSlot,NumSamplers,ppSamplers)	\
    ( (This)->lpVtbl -> PSSetSamplers(This,StartSlot,NumSamplers,ppSamplers) ) 

#define ID3D10Device1_VSSetShader(This,pVertexShader)	\
    ( (This)->lpVtbl -> VSSetShader(This,pVertexShader) ) 

#define ID3D10Device1_DrawIndexed(This,IndexCount,StartIndexLocation,BaseVertexLocation)	\
    ( (This)->lpVtbl -> DrawIndexed(This,IndexCount,StartIndexLocation,BaseVertexLocation) ) 

#define ID3D10Device1_Draw(This,VertexCount,StartVertexLocation)	\
    ( (This)->lpVtbl -> Draw(This,VertexCount,StartVertexLocation) ) 

#define ID3D10Device1_PSSetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers)	\
    ( (This)->lpVtbl -> PSSetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers) ) 

#define ID3D10Device1_IASetInputLayout(This,pInputLayout)	\
    ( (This)->lpVtbl -> IASetInputLayout(This,pInputLayout) ) 

#define ID3D10Device1_IASetVertexBuffers(This,StartSlot,NumBuffers,ppVertexBuffers,pStrides,pOffsets)	\
    ( (This)->lpVtbl -> IASetVertexBuffers(This,StartSlot,NumBuffers,ppVertexBuffers,pStrides,pOffsets) ) 

#define ID3D10Device1_IASetIndexBuffer(This,pIndexBuffer,Format,Offset)	\
    ( (This)->lpVtbl -> IASetIndexBuffer(This,pIndexBuffer,Format,Offset) ) 

#define ID3D10Device1_DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation)	\
    ( (This)->lpVtbl -> DrawIndexedInstanced(This,IndexCountPerInstance,InstanceCount,StartIndexLocation,BaseVertexLocation,StartInstanceLocation) ) 

#define ID3D10Device1_DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation)	\
    ( (This)->lpVtbl -> DrawInstanced(This,VertexCountPerInstance,InstanceCount,StartVertexLocation,StartInstanceLocation) ) 

#define ID3D10Device1_GSSetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers)	\
    ( (This)->lpVtbl -> GSSetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers) ) 

#define ID3D10Device1_GSSetShader(This,pShader)	\
    ( (This)->lpVtbl -> GSSetShader(This,pShader) ) 

#define ID3D10Device1_IASetPrimitiveTopology(This,Topology)	\
    ( (This)->lpVtbl -> IASetPrimitiveTopology(This,Topology) ) 

#define ID3D10Device1_VSSetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews)	\
    ( (This)->lpVtbl -> VSSetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews) ) 

#define ID3D10Device1_VSSetSamplers(This,StartSlot,NumSamplers,ppSamplers)	\
    ( (This)->lpVtbl -> VSSetSamplers(This,StartSlot,NumSamplers,ppSamplers) ) 

#define ID3D10Device1_SetPredication(This,pPredicate,PredicateValue)	\
    ( (This)->lpVtbl -> SetPredication(This,pPredicate,PredicateValue) ) 

#define ID3D10Device1_GSSetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews)	\
    ( (This)->lpVtbl -> GSSetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews) ) 

#define ID3D10Device1_GSSetSamplers(This,StartSlot,NumSamplers,ppSamplers)	\
    ( (This)->lpVtbl -> GSSetSamplers(This,StartSlot,NumSamplers,ppSamplers) ) 

#define ID3D10Device1_OMSetRenderTargets(This,NumViews,ppRenderTargetViews,pDepthStencilView)	\
    ( (This)->lpVtbl -> OMSetRenderTargets(This,NumViews,ppRenderTargetViews,pDepthStencilView) ) 

#define ID3D10Device1_OMSetBlendState(This,pBlendState,BlendFactor,SampleMask)	\
    ( (This)->lpVtbl -> OMSetBlendState(This,pBlendState,BlendFactor,SampleMask) ) 

#define ID3D10Device1_OMSetDepthStencilState(This,pDepthStencilState,StencilRef)	\
    ( (This)->lpVtbl -> OMSetDepthStencilState(This,pDepthStencilState,StencilRef) ) 

#define ID3D10Device1_SOSetTargets(This,NumBuffers,ppSOTargets,pOffsets)	\
    ( (This)->lpVtbl -> SOSetTargets(This,NumBuffers,ppSOTargets,pOffsets) ) 

#define ID3D10Device1_DrawAuto(This)	\
    ( (This)->lpVtbl -> DrawAuto(This) ) 

#define ID3D10Device1_RSSetState(This,pRasterizerState)	\
    ( (This)->lpVtbl -> RSSetState(This,pRasterizerState) ) 

#define ID3D10Device1_RSSetViewports(This,NumViewports,pViewports)	\
    ( (This)->lpVtbl -> RSSetViewports(This,NumViewports,pViewports) ) 

#define ID3D10Device1_RSSetScissorRects(This,NumRects,pRects)	\
    ( (This)->lpVtbl -> RSSetScissorRects(This,NumRects,pRects) ) 

#define ID3D10Device1_CopySubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,DstZ,pSrcResource,SrcSubresource,pSrcBox)	\
    ( (This)->lpVtbl -> CopySubresourceRegion(This,pDstResource,DstSubresource,DstX,DstY,DstZ,pSrcResource,SrcSubresource,pSrcBox) ) 

#define ID3D10Device1_CopyResource(This,pDstResource,pSrcResource)	\
    ( (This)->lpVtbl -> CopyResource(This,pDstResource,pSrcResource) ) 

#define ID3D10Device1_UpdateSubresource(This,pDstResource,DstSubresource,pDstBox,pSrcData,SrcRowPitch,SrcDepthPitch)	\
    ( (This)->lpVtbl -> UpdateSubresource(This,pDstResource,DstSubresource,pDstBox,pSrcData,SrcRowPitch,SrcDepthPitch) ) 

#define ID3D10Device1_ClearRenderTargetView(This,pRenderTargetView,ColorRGBA)	\
    ( (This)->lpVtbl -> ClearRenderTargetView(This,pRenderTargetView,ColorRGBA) ) 

#define ID3D10Device1_ClearDepthStencilView(This,pDepthStencilView,ClearFlags,Depth,Stencil)	\
    ( (This)->lpVtbl -> ClearDepthStencilView(This,pDepthStencilView,ClearFlags,Depth,Stencil) ) 

#define ID3D10Device1_GenerateMips(This,pShaderResourceView)	\
    ( (This)->lpVtbl -> GenerateMips(This,pShaderResourceView) ) 

#define ID3D10Device1_ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format)	\
    ( (This)->lpVtbl -> ResolveSubresource(This,pDstResource,DstSubresource,pSrcResource,SrcSubresource,Format) ) 

#define ID3D10Device1_VSGetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers)	\
    ( (This)->lpVtbl -> VSGetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers) ) 

#define ID3D10Device1_PSGetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews)	\
    ( (This)->lpVtbl -> PSGetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews) ) 

#define ID3D10Device1_PSGetShader(This,ppPixelShader)	\
    ( (This)->lpVtbl -> PSGetShader(This,ppPixelShader) ) 

#define ID3D10Device1_PSGetSamplers(This,StartSlot,NumSamplers,ppSamplers)	\
    ( (This)->lpVtbl -> PSGetSamplers(This,StartSlot,NumSamplers,ppSamplers) ) 

#define ID3D10Device1_VSGetShader(This,ppVertexShader)	\
    ( (This)->lpVtbl -> VSGetShader(This,ppVertexShader) ) 

#define ID3D10Device1_PSGetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers)	\
    ( (This)->lpVtbl -> PSGetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers) ) 

#define ID3D10Device1_IAGetInputLayout(This,ppInputLayout)	\
    ( (This)->lpVtbl -> IAGetInputLayout(This,ppInputLayout) ) 

#define ID3D10Device1_IAGetVertexBuffers(This,StartSlot,NumBuffers,ppVertexBuffers,pStrides,pOffsets)	\
    ( (This)->lpVtbl -> IAGetVertexBuffers(This,StartSlot,NumBuffers,ppVertexBuffers,pStrides,pOffsets) ) 

#define ID3D10Device1_IAGetIndexBuffer(This,pIndexBuffer,Format,Offset)	\
    ( (This)->lpVtbl -> IAGetIndexBuffer(This,pIndexBuffer,Format,Offset) ) 

#define ID3D10Device1_GSGetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers)	\
    ( (This)->lpVtbl -> GSGetConstantBuffers(This,StartSlot,NumBuffers,ppConstantBuffers) ) 

#define ID3D10Device1_GSGetShader(This,ppGeometryShader)	\
    ( (This)->lpVtbl -> GSGetShader(This,ppGeometryShader) ) 

#define ID3D10Device1_IAGetPrimitiveTopology(This,pTopology)	\
    ( (This)->lpVtbl -> IAGetPrimitiveTopology(This,pTopology) ) 

#define ID3D10Device1_VSGetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews)	\
    ( (This)->lpVtbl -> VSGetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews) ) 

#define ID3D10Device1_VSGetSamplers(This,StartSlot,NumSamplers,ppSamplers)	\
    ( (This)->lpVtbl -> VSGetSamplers(This,StartSlot,NumSamplers,ppSamplers) ) 

#define ID3D10Device1_GetPredication(This,ppPredicate,pPredicateValue)	\
    ( (This)->lpVtbl -> GetPredication(This,ppPredicate,pPredicateValue) ) 

#define ID3D10Device1_GSGetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews)	\
    ( (This)->lpVtbl -> GSGetShaderResources(This,StartSlot,NumViews,ppShaderResourceViews) ) 

#define ID3D10Device1_GSGetSamplers(This,StartSlot,NumSamplers,ppSamplers)	\
    ( (This)->lpVtbl -> GSGetSamplers(This,StartSlot,NumSamplers,ppSamplers) ) 

#define ID3D10Device1_OMGetRenderTargets(This,NumViews,ppRenderTargetViews,ppDepthStencilView)	\
    ( (This)->lpVtbl -> OMGetRenderTargets(This,NumViews,ppRenderTargetViews,ppDepthStencilView) ) 

#define ID3D10Device1_OMGetBlendState(This,ppBlendState,BlendFactor,pSampleMask)	\
    ( (This)->lpVtbl -> OMGetBlendState(This,ppBlendState,BlendFactor,pSampleMask) ) 

#define ID3D10Device1_OMGetDepthStencilState(This,ppDepthStencilState,pStencilRef)	\
    ( (This)->lpVtbl -> OMGetDepthStencilState(This,ppDepthStencilState,pStencilRef) ) 

#define ID3D10Device1_SOGetTargets(This,NumBuffers,ppSOTargets,pOffsets)	\
    ( (This)->lpVtbl -> SOGetTargets(This,NumBuffers,ppSOTargets,pOffsets) ) 

#define ID3D10Device1_RSGetState(This,ppRasterizerState)	\
    ( (This)->lpVtbl -> RSGetState(This,ppRasterizerState) ) 

#define ID3D10Device1_RSGetViewports(This,NumViewports,pViewports)	\
    ( (This)->lpVtbl -> RSGetViewports(This,NumViewports,pViewports) ) 

#define ID3D10Device1_RSGetScissorRects(This,NumRects,pRects)	\
    ( (This)->lpVtbl -> RSGetScissorRects(This,NumRects,pRects) ) 

#define ID3D10Device1_GetDeviceRemovedReason(This)	\
    ( (This)->lpVtbl -> GetDeviceRemovedReason(This) ) 

#define ID3D10Device1_SetExceptionMode(This,RaiseFlags)	\
    ( (This)->lpVtbl -> SetExceptionMode(This,RaiseFlags) ) 

#define ID3D10Device1_GetExceptionMode(This)	\
    ( (This)->lpVtbl -> GetExceptionMode(This) ) 

#define ID3D10Device1_GetPrivateData(This,guid,pDataSize,pData)	\
    ( (This)->lpVtbl -> GetPrivateData(This,guid,pDataSize,pData) ) 

#define ID3D10Device1_SetPrivateData(This,guid,DataSize,pData)	\
    ( (This)->lpVtbl -> SetPrivateData(This,guid,DataSize,pData) ) 

#define ID3D10Device1_SetPrivateDataInterface(This,guid,pData)	\
    ( (This)->lpVtbl -> SetPrivateDataInterface(This,guid,pData) ) 

#define ID3D10Device1_ClearState(This)	\
    ( (This)->lpVtbl -> ClearState(This) ) 

#define ID3D10Device1_Flush(This)	\
    ( (This)->lpVtbl -> Flush(This) ) 

#define ID3D10Device1_CreateBuffer(This,pDesc,pInitialData,ppBuffer)	\
    ( (This)->lpVtbl -> CreateBuffer(This,pDesc,pInitialData,ppBuffer) ) 

#define ID3D10Device1_CreateTexture1D(This,pDesc,pInitialData,ppTexture1D)	\
    ( (This)->lpVtbl -> CreateTexture1D(This,pDesc,pInitialData,ppTexture1D) ) 

#define ID3D10Device1_CreateTexture2D(This,pDesc,pInitialData,ppTexture2D)	\
    ( (This)->lpVtbl -> CreateTexture2D(This,pDesc,pInitialData,ppTexture2D) ) 

#define ID3D10Device1_CreateTexture3D(This,pDesc,pInitialData,ppTexture3D)	\
    ( (This)->lpVtbl -> CreateTexture3D(This,pDesc,pInitialData,ppTexture3D) ) 

#define ID3D10Device1_CreateShaderResourceView(This,pResource,pDesc,ppSRView)	\
    ( (This)->lpVtbl -> CreateShaderResourceView(This,pResource,pDesc,ppSRView) ) 

#define ID3D10Device1_CreateRenderTargetView(This,pResource,pDesc,ppRTView)	\
    ( (This)->lpVtbl -> CreateRenderTargetView(This,pResource,pDesc,ppRTView) ) 

#define ID3D10Device1_CreateDepthStencilView(This,pResource,pDesc,ppDepthStencilView)	\
    ( (This)->lpVtbl -> CreateDepthStencilView(This,pResource,pDesc,ppDepthStencilView) ) 

#define ID3D10Device1_CreateInputLayout(This,pInputElementDescs,NumElements,pShaderBytecodeWithInputSignature,BytecodeLength,ppInputLayout)	\
    ( (This)->lpVtbl -> CreateInputLayout(This,pInputElementDescs,NumElements,pShaderBytecodeWithInputSignature,BytecodeLength,ppInputLayout) ) 

#define ID3D10Device1_CreateVertexShader(This,pShaderBytecode,BytecodeLength,ppVertexShader)	\
    ( (This)->lpVtbl -> CreateVertexShader(This,pShaderBytecode,BytecodeLength,ppVertexShader) ) 

#define ID3D10Device1_CreateGeometryShader(This,pShaderBytecode,BytecodeLength,ppGeometryShader)	\
    ( (This)->lpVtbl -> CreateGeometryShader(This,pShaderBytecode,BytecodeLength,ppGeometryShader) ) 

#define ID3D10Device1_CreateGeometryShaderWithStreamOutput(This,pShaderBytecode,BytecodeLength,pSODeclaration,NumEntries,OutputStreamStride,ppGeometryShader)	\
    ( (This)->lpVtbl -> CreateGeometryShaderWithStreamOutput(This,pShaderBytecode,BytecodeLength,pSODeclaration,NumEntries,OutputStreamStride,ppGeometryShader) ) 

#define ID3D10Device1_CreatePixelShader(This,pShaderBytecode,BytecodeLength,ppPixelShader)	\
    ( (This)->lpVtbl -> CreatePixelShader(This,pShaderBytecode,BytecodeLength,ppPixelShader) ) 

#define ID3D10Device1_CreateBlendState(This,pBlendStateDesc,ppBlendState)	\
    ( (This)->lpVtbl -> CreateBlendState(This,pBlendStateDesc,ppBlendState) ) 

#define ID3D10Device1_CreateDepthStencilState(This,pDepthStencilDesc,ppDepthStencilState)	\
    ( (This)->lpVtbl -> CreateDepthStencilState(This,pDepthStencilDesc,ppDepthStencilState) ) 

#define ID3D10Device1_CreateRasterizerState(This,pRasterizerDesc,ppRasterizerState)	\
    ( (This)->lpVtbl -> CreateRasterizerState(This,pRasterizerDesc,ppRasterizerState) ) 

#define ID3D10Device1_CreateSamplerState(This,pSamplerDesc,ppSamplerState)	\
    ( (This)->lpVtbl -> CreateSamplerState(This,pSamplerDesc,ppSamplerState) ) 

#define ID3D10Device1_CreateQuery(This,pQueryDesc,ppQuery)	\
    ( (This)->lpVtbl -> CreateQuery(This,pQueryDesc,ppQuery) ) 

#define ID3D10Device1_CreatePredicate(This,pPredicateDesc,ppPredicate)	\
    ( (This)->lpVtbl -> CreatePredicate(This,pPredicateDesc,ppPredicate) ) 

#define ID3D10Device1_CreateCounter(This,pCounterDesc,ppCounter)	\
    ( (This)->lpVtbl -> CreateCounter(This,pCounterDesc,ppCounter) ) 

#define ID3D10Device1_CheckFormatSupport(This,Format,pFormatSupport)	\
    ( (This)->lpVtbl -> CheckFormatSupport(This,Format,pFormatSupport) ) 

#define ID3D10Device1_CheckMultisampleQualityLevels(This,Format,SampleCount,pNumQualityLevels)	\
    ( (This)->lpVtbl -> CheckMultisampleQualityLevels(This,Format,SampleCount,pNumQualityLevels) ) 

#define ID3D10Device1_CheckCounterInfo(This,pCounterInfo)	\
    ( (This)->lpVtbl -> CheckCounterInfo(This,pCounterInfo) ) 

#define ID3D10Device1_CheckCounter(This,pDesc,pType,pActiveCounters,szName,pNameLength,szUnits,pUnitsLength,szDescription,pDescriptionLength)	\
    ( (This)->lpVtbl -> CheckCounter(This,pDesc,pType,pActiveCounters,szName,pNameLength,szUnits,pUnitsLength,szDescription,pDescriptionLength) ) 

#define ID3D10Device1_GetCreationFlags(This)	\
    ( (This)->lpVtbl -> GetCreationFlags(This) ) 

#define ID3D10Device1_OpenSharedResource(This,hResource,ReturnedInterface,ppResource)	\
    ( (This)->lpVtbl -> OpenSharedResource(This,hResource,ReturnedInterface,ppResource) ) 

#define ID3D10Device1_SetTextFilterSize(This,Width,Height)	\
    ( (This)->lpVtbl -> SetTextFilterSize(This,Width,Height) ) 

#define ID3D10Device1_GetTextFilterSize(This,pWidth,pHeight)	\
    ( (This)->lpVtbl -> GetTextFilterSize(This,pWidth,pHeight) ) 


#define ID3D10Device1_CreateShaderResourceView1(This,pResource,pDesc,ppSRView)	\
    ( (This)->lpVtbl -> CreateShaderResourceView1(This,pResource,pDesc,ppSRView) ) 

#define ID3D10Device1_CreateBlendState1(This,pBlendStateDesc,ppBlendState)	\
    ( (This)->lpVtbl -> CreateBlendState1(This,pBlendStateDesc,ppBlendState) ) 

#define ID3D10Device1_GetFeatureLevel(This)	\
    ( (This)->lpVtbl -> GetFeatureLevel(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ID3D10Device1_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3d10_1_0000_0003 */
/* [local] */ 

#define	D3D10_1_SDK_VERSION	( ( 0 + 0x20 )  )

#include "d3d10_1shader.h" 

///////////////////////////////////////////////////////////////////////////
// D3D10CreateDevice1
// ------------------
//
// pAdapter
//      If NULL, D3D10CreateDevice1 will choose the primary adapter and
//      create a new instance from a temporarily created IDXGIFactory.
//      If non-NULL, D3D10CreateDevice1 will register the appropriate
//      device, if necessary (via IDXGIAdapter::RegisterDrver), before
//      creating the device.
// DriverType
//      Specifies the driver type to be created: hardware, reference or
//      null.
// Software
//      HMODULE of a DLL implementing a software rasterizer. Must be NULL for
//      non-Software driver types.
// Flags
//      Any of those documented for D3D10CreateDeviceAndSwapChain1.
// HardwareLevel
//      Any of those documented for D3D10CreateDeviceAndSwapChain1.
// SDKVersion
//      SDK version. Use the D3D10_1_SDK_VERSION macro.
// ppDevice
//      Pointer to returned interface.
//
// Return Values
//  Any of those documented for 
//          CreateDXGIFactory
//          IDXGIFactory::EnumAdapters
//          IDXGIAdapter::RegisterDriver
//          D3D10CreateDevice1
//
///////////////////////////////////////////////////////////////////////////
typedef HRESULT (WINAPI* PFN_D3D10_CREATE_DEVICE1)(IDXGIAdapter *, 
    D3D10_DRIVER_TYPE, HMODULE, UINT, D3D10_FEATURE_LEVEL1, UINT, ID3D10Device1**);

HRESULT WINAPI D3D10CreateDevice1(
    _In_opt_ IDXGIAdapter *pAdapter,
    D3D10_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    D3D10_FEATURE_LEVEL1 HardwareLevel,
    UINT SDKVersion,
    _Out_opt_ ID3D10Device1 **ppDevice);

///////////////////////////////////////////////////////////////////////////
// D3D10CreateDeviceAndSwapChain1
// ------------------------------
//
// ppAdapter
//      If NULL, D3D10CreateDevice1 will choose the primary adapter and 
//      create a new instance from a temporarily created IDXGIFactory.
//      If non-NULL, D3D10CreateDevice1 will register the appropriate
//      device, if necessary (via IDXGIAdapter::RegisterDrver), before
//      creating the device.
// DriverType
//      Specifies the driver type to be created: hardware, reference or
//      null.
// Software
//      HMODULE of a DLL implementing a software rasterizer. Must be NULL for
//      non-Software driver types.
// Flags
//      Any of those documented for D3D10CreateDevice1.
// HardwareLevel
//      Any of:
//          D3D10_CREATE_LEVEL_10_0
//          D3D10_CREATE_LEVEL_10_1
// SDKVersion
//      SDK version. Use the D3D10_1_SDK_VERSION macro.
// pSwapChainDesc
//      Swap chain description, may be NULL.
// ppSwapChain
//      Pointer to returned interface. May be NULL.
// ppDevice
//      Pointer to returned interface.
//
// Return Values
//  Any of those documented for 
//          CreateDXGIFactory
//          IDXGIFactory::EnumAdapters
//          IDXGIAdapter::RegisterDriver
//          D3D10CreateDevice1
//          IDXGIFactory::CreateSwapChain
//
///////////////////////////////////////////////////////////////////////////
typedef HRESULT (WINAPI* PFN_D3D10_CREATE_DEVICE_AND_SWAP_CHAIN1)(IDXGIAdapter *, 
    D3D10_DRIVER_TYPE, HMODULE, UINT, D3D10_FEATURE_LEVEL1, UINT, DXGI_SWAP_CHAIN_DESC *, IDXGISwapChain **, ID3D10Device1 **);

HRESULT WINAPI D3D10CreateDeviceAndSwapChain1(
    _In_opt_ IDXGIAdapter *pAdapter,
    D3D10_DRIVER_TYPE DriverType,
    HMODULE Software,
    UINT Flags,
    D3D10_FEATURE_LEVEL1 HardwareLevel,
    UINT SDKVersion,
    _In_opt_ DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
    _Out_opt_ IDXGISwapChain **ppSwapChain,
    _Out_opt_ ID3D10Device1 **ppDevice);

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#if !defined(__GNUC__) && !defined(__clang__)
#pragma endregion
#endif
DEFINE_GUID(IID_ID3D10BlendState1,0xEDAD8D99,0x8A35,0x4d6d,0x85,0x66,0x2E,0xA2,0x76,0xCD,0xE1,0x61);
DEFINE_GUID(IID_ID3D10ShaderResourceView1,0x9B7E4C87,0x342C,0x4106,0xA1,0x9F,0x4F,0x27,0x04,0xF6,0x89,0xF0);
DEFINE_GUID(IID_ID3D10Device1,0x9B7E4C8F,0x342C,0x4106,0xA1,0x9F,0x4F,0x27,0x04,0xF6,0x89,0xF0);


extern RPC_IF_HANDLE __MIDL_itf_d3d10_1_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3d10_1_0000_0003_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


