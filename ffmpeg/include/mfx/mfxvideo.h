/* ****************************************************************************** *\

INTEL CORPORATION PROPRIETARY INFORMATION
This software is supplied under the terms of a license agreement or nondisclosure
agreement with Intel Corporation and may not be copied or disclosed except in
accordance with the terms of that agreement
Copyright(c) 2007-2012 Intel Corporation. All Rights Reserved.

File Name: mfxvideo.h

\* ****************************************************************************** */
#ifdef LIBMFX_EXPORTS
#define LIBMFX_API __declspec(dllexport)
#else
#define LIBMFX_API __declspec(dllimport)
#endif

#ifndef __MFXVIDEO_H__
#define __MFXVIDEO_H__
#include "mfxstructures.h"

/* This is the external include file for the Intel(R) Media Software Development Kit product */
#define MFX_VERSION_MAJOR 1
#define MFX_VERSION_MINOR 6

#ifdef _WIN32
    #define MFX_CDECL __cdecl
    #define MFX_STDCALL __stdcall
#else
    #define MFX_CDECL
    #define MFX_STDCALL
#endif /* _WIN32 */

#ifdef __cplusplus
extern "C"
{
#endif

/* MFXVideoCORE */
typedef struct {
    mfxU32      reserved[4];
    mfxHDL      pthis;
    mfxStatus  (MFX_CDECL *Alloc)    (mfxHDL pthis, mfxU32 nbytes, mfxU16 type, mfxMemId *mid);
    mfxStatus  (MFX_CDECL *Lock)     (mfxHDL pthis, mfxMemId mid, mfxU8 **ptr);
    mfxStatus  (MFX_CDECL *Unlock)   (mfxHDL pthis, mfxMemId mid);
    mfxStatus  (MFX_CDECL *Free)     (mfxHDL pthis, mfxMemId mid);
} mfxBufferAllocator;

typedef struct {
    mfxU32      reserved[4];
    mfxHDL      pthis;

    mfxStatus  (MFX_CDECL  *Alloc)    (mfxHDL pthis, mfxFrameAllocRequest *request, mfxFrameAllocResponse *response);
    mfxStatus  (MFX_CDECL  *Lock)     (mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr);
    mfxStatus  (MFX_CDECL  *Unlock)   (mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr);
    mfxStatus  (MFX_CDECL  *GetHDL)   (mfxHDL pthis, mfxMemId mid, mfxHDL *handle);
    mfxStatus  (MFX_CDECL  *Free)     (mfxHDL pthis, mfxFrameAllocResponse *response);
} mfxFrameAllocator;

/* Global Functions */
typedef struct _mfxSession *mfxSession;
LIBMFX_API mfxStatus MFX_CDECL MFXInit(mfxIMPL impl, mfxVersion *ver, mfxSession *session);
LIBMFX_API mfxStatus MFX_CDECL MFXClose(mfxSession session);

LIBMFX_API mfxStatus MFX_CDECL MFXQueryIMPL(mfxSession session, mfxIMPL *impl);
LIBMFX_API mfxStatus MFX_CDECL MFXQueryVersion(mfxSession session, mfxVersion *version);

LIBMFX_API mfxStatus MFX_CDECL MFXJoinSession(mfxSession session, mfxSession child);
LIBMFX_API mfxStatus MFX_CDECL MFXDisjoinSession(mfxSession session);
LIBMFX_API mfxStatus MFX_CDECL MFXCloneSession(mfxSession session, mfxSession *clone);
LIBMFX_API mfxStatus MFX_CDECL MFXSetPriority(mfxSession session, mfxPriority priority);
LIBMFX_API mfxStatus MFX_CDECL MFXGetPriority(mfxSession session, mfxPriority *priority);

/* VideoCORE */
LIBMFX_API mfxStatus MFX_CDECL MFXVideoCORE_SetBufferAllocator(mfxSession session, mfxBufferAllocator *allocator);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoCORE_SetFrameAllocator(mfxSession session, mfxFrameAllocator *allocator);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoCORE_SetHandle(mfxSession session, mfxHandleType type, mfxHDL hdl);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoCORE_GetHandle(mfxSession session, mfxHandleType type, mfxHDL *hdl);

typedef struct _mfxSyncPoint *mfxSyncPoint;
LIBMFX_API mfxStatus MFX_CDECL MFXVideoCORE_SyncOperation(mfxSession session, mfxSyncPoint syncp, mfxU32 wait);

/* VideoENCODE */
LIBMFX_API mfxStatus MFX_CDECL MFXVideoENCODE_Query(mfxSession session, mfxVideoParam *in, mfxVideoParam *out);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoENCODE_QueryIOSurf(mfxSession session, mfxVideoParam *par, mfxFrameAllocRequest *request);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoENCODE_Init(mfxSession session, mfxVideoParam *par);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoENCODE_Reset(mfxSession session, mfxVideoParam *par);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoENCODE_Close(mfxSession session);

LIBMFX_API mfxStatus MFX_CDECL MFXVideoENCODE_GetVideoParam(mfxSession session, mfxVideoParam *par);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoENCODE_GetEncodeStat(mfxSession session, mfxEncodeStat *stat);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoENCODE_EncodeFrameAsync(mfxSession session, mfxEncodeCtrl *ctrl, mfxFrameSurface1 *surface, mfxBitstream *bs, mfxSyncPoint *syncp);

/* VideoDECODE */
LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_Query(mfxSession session, mfxVideoParam *in, mfxVideoParam *out);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_DecodeHeader(mfxSession session, mfxBitstream *bs, mfxVideoParam *par);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_QueryIOSurf(mfxSession session, mfxVideoParam *par, mfxFrameAllocRequest *request);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_Init(mfxSession session, mfxVideoParam *par);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_Reset(mfxSession session, mfxVideoParam *par);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_Close(mfxSession session);

LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_GetVideoParam(mfxSession session, mfxVideoParam *par);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_GetDecodeStat(mfxSession session, mfxDecodeStat *stat);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_SetSkipMode(mfxSession session, mfxSkipMode mode);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_GetPayload(mfxSession session, mfxU64 *ts, mfxPayload *payload);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoDECODE_DecodeFrameAsync(mfxSession session, mfxBitstream *bs, mfxFrameSurface1 *surface_work, mfxFrameSurface1 **surface_out, mfxSyncPoint *syncp);

/* VideoVPP */
LIBMFX_API mfxStatus MFX_CDECL MFXVideoVPP_Query(mfxSession session, mfxVideoParam *in, mfxVideoParam *out);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoVPP_QueryIOSurf(mfxSession session, mfxVideoParam *par, mfxFrameAllocRequest request[2]);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoVPP_Init(mfxSession session, mfxVideoParam *par);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoVPP_Reset(mfxSession session, mfxVideoParam *par);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoVPP_Close(mfxSession session);

LIBMFX_API mfxStatus MFX_CDECL MFXVideoVPP_GetVideoParam(mfxSession session, mfxVideoParam *par);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoVPP_GetVPPStat(mfxSession session, mfxVPPStat *stat);
LIBMFX_API mfxStatus MFX_CDECL MFXVideoVPP_RunFrameVPPAsync(mfxSession session, mfxFrameSurface1 *in, mfxFrameSurface1 *out, mfxExtVppAuxData *aux, mfxSyncPoint *syncp);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
