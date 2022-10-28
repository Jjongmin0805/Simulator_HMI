

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0626 */
/* at Tue Jan 19 12:14:07 2038
 */
/* Compiler settings for WorkPackagerV3.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0626 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
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

#ifndef __WorkPackagerV3_h_h__
#define __WorkPackagerV3_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if _CONTROL_FLOW_GUARD_XFG
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IWorkPackagerADK_FWD_DEFINED__
#define __IWorkPackagerADK_FWD_DEFINED__
typedef interface IWorkPackagerADK IWorkPackagerADK;

#endif 	/* __IWorkPackagerADK_FWD_DEFINED__ */


#ifndef __IPackager_FWD_DEFINED__
#define __IPackager_FWD_DEFINED__
typedef interface IPackager IPackager;

#endif 	/* __IPackager_FWD_DEFINED__ */


#ifndef __IVersion_FWD_DEFINED__
#define __IVersion_FWD_DEFINED__
typedef interface IVersion IVersion;

#endif 	/* __IVersion_FWD_DEFINED__ */


#ifndef __WorkPackagerADK_FWD_DEFINED__
#define __WorkPackagerADK_FWD_DEFINED__

#ifdef __cplusplus
typedef class WorkPackagerADK WorkPackagerADK;
#else
typedef struct WorkPackagerADK WorkPackagerADK;
#endif /* __cplusplus */

#endif 	/* __WorkPackagerADK_FWD_DEFINED__ */


#ifndef __Packager_FWD_DEFINED__
#define __Packager_FWD_DEFINED__

#ifdef __cplusplus
typedef class Packager Packager;
#else
typedef struct Packager Packager;
#endif /* __cplusplus */

#endif 	/* __Packager_FWD_DEFINED__ */


#ifndef __Version_FWD_DEFINED__
#define __Version_FWD_DEFINED__

#ifdef __cplusplus
typedef class Version Version;
#else
typedef struct Version Version;
#endif /* __cplusplus */

#endif 	/* __Version_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IWorkPackagerADK_INTERFACE_DEFINED__
#define __IWorkPackagerADK_INTERFACE_DEFINED__

/* interface IWorkPackagerADK */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWorkPackagerADK;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E5BA754C-ED4C-4E88-BD57-0B801C4C2098")
    IWorkPackagerADK : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CharSet( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CharSet( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContentID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ContentID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsTemp( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsTemp( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastErrorNum( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastErrorStr( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OverwriteFlag( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OverwriteFlag( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SecureContainerFileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SecureContainerFileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PackageType( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PackageType( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SecureContainerFilePathName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SecureContainerFilePathName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddRightsFsn( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oSourceFile,
            /* [in] */ BSTR oTargetFile,
            /* [in] */ BSTR targettype,
            /* [in] */ BSTR targetid,
            /* [in] */ BSTR targetname,
            /* [in] */ BSTR rightstring) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteAllRightsFsn( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oSourceFile,
            /* [in] */ BSTR oTargetFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteRightsFsn( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oSourceFile,
            /* [in] */ BSTR oTargetFile,
            /* [in] */ BSTR targettype,
            /* [in] */ BSTR targetid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoExtract( 
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [in] */ BSTR TargetFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoExtract_c( 
            BSTR oHomeDir,
            BSTR oServerID,
            BSTR oSourceFile,
            BSTR oTargetFile,
            BSTR oPurpose) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoExtract_s( 
            BSTR oHomeDir,
            BSTR oServerID,
            BSTR oSourceFile,
            BSTR oTargetFile,
            BSTR oUserId,
            BSTR oPurpose,
            BSTR oDummy1,
            BSTR oDummy2,
            BSTR oDummy3,
            BSTR oDummy4,
            BSTR oDummy5) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoPackaging( 
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [in] */ BSTR TargetFile,
            /* [in] */ BSTR ContentName,
            /* [in] */ BSTR UserID,
            /* [in] */ BSTR UserName,
            /* [in] */ BSTR Etc1,
            /* [in] */ BSTR Etc2,
            /* [in] */ BSTR Etc3,
            /* [in] */ BSTR Etc4,
            /* [in] */ BSTR Etc5) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoPackagingFsn( 
            BSTR oHomeDir,
            BSTR oServerID,
            BSTR oSourceFile,
            BSTR oTargetFile,
            BSTR oContentName,
            BSTR oUserID,
            BSTR oUserName,
            BSTR oWriteID,
            BSTR oWriteName,
            BSTR oWdeptID,
            BSTR oWdeptName,
            BSTR oOwnerID,
            BSTR oOwnerName,
            BSTR oOdeptID,
            BSTR oOdeptName,
            short oSecurityLevel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoPackagingFsn2( 
            BSTR bHomeDir,
            BSTR bServerID,
            BSTR bSourceFile,
            BSTR bTargetFile,
            BSTR bContentName,
            BSTR bUserID,
            BSTR bUserName,
            BSTR bWriteID,
            BSTR bWriteName,
            BSTR bWdeptID,
            BSTR bWdeptName,
            BSTR bOwnerID,
            BSTR bOwnerName,
            BSTR bOdeptID,
            BSTR bOdeptName,
            BSTR bSecurityLevel_s) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoPackagingNx( 
            BSTR bHomeDir,
            BSTR bServerID,
            BSTR bSourceFile,
            BSTR bTargetFile,
            BSTR bContentName,
            BSTR bUserID,
            BSTR bUserName,
            BSTR bWriteID,
            BSTR bWriteName,
            BSTR bWdeptID,
            BSTR bWdeptName,
            BSTR bOwnerID,
            BSTR bOwnerName,
            BSTR bOdeptID,
            BSTR bOdeptName,
            BSTR bSecurityLevel_s) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFileHeader( 
            /* [in] */ BSTR sfile,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFileHeaderA( 
            /* [in] */ BSTR sfile,
            /* [retval][out] */ BSTR *pobj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFileHeaderW( 
            /* [in] */ BSTR sfile,
            /* [retval][out] */ BSTR *pobj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFileType( 
            /* [in] */ BSTR SourceFile,
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsPackageFile( 
            /* [in] */ BSTR SourceFile,
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsSupportFile( 
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadAllRightsFse( 
            /* [in] */ BSTR oTargetFile,
            /* [retval][out] */ BSTR *rightstring) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadAllRightsFsn( 
            /* [in] */ BSTR oTargetFile,
            /* [retval][out] */ BSTR *rightstring) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadRightsFse( 
            /* [in] */ BSTR oTargetFile,
            /* [in] */ BSTR targetid,
            /* [retval][out] */ BSTR *rightstring) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadRightsFsn( 
            /* [in] */ BSTR oTargetFile,
            /* [in] */ BSTR targettype,
            /* [in] */ BSTR targetid,
            /* [retval][out] */ BSTR *rightstring) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadSenderFse( 
            /* [in] */ BSTR oTargetFile,
            /* [retval][out] */ BSTR *sender) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoPackagingFSM( 
            BSTR HomeDir,
            BSTR ServerID,
            BSTR SourceFile,
            BSTR TargetFile,
            BSTR ContentName,
            BSTR UserID,
            BSTR UserName,
            BSTR Etc1,
            BSTR Etc2,
            BSTR Etc3,
            BSTR Etc4,
            BSTR Etc5) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncryptedHeader4FSM( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EncryptedHeader4FSM( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddHeaderInfo( 
            /* [in] */ BSTR key,
            /* [in] */ BSTR value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeHeader( 
            /* [in] */ BSTR homeDir,
            /* [in] */ BSTR serverID,
            /* [in] */ BSTR sourceFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFileHeaderEx( 
            /* [in] */ BSTR sfile,
            /* [in] */ BSTR delim,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFseReaderAndOption( 
            BSTR sFile,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CustomUserName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CustomUserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CustomDeptCode( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CustomDeptCode( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CustomDeptName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CustomDeptName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CustomPositionCode( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CustomPositionCode( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CustomPositionName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CustomPositionName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CustomRoleCode( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CustomRoleCode( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CustomRoleName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CustomRoleName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CustomExdata( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CustomExdata( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoExtract_s2( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oSourceFile,
            /* [in] */ BSTR oTargetFile,
            /* [in] */ BSTR oUserId,
            /* [in] */ BSTR oPurpose,
            /* [in] */ BOOL oSaveFlag,
            /* [in] */ BSTR oDummy1,
            /* [in] */ BSTR oDummy2,
            /* [in] */ BSTR oDummy3,
            /* [in] */ BSTR oDummy4,
            /* [in] */ BSTR oDummy5) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_REQUrl( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_REQUrl( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_REQSubUrl( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_REQSubUrl( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_REQPort( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_REQPort( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_REQProtocol( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_REQProtocol( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RevokeUsage4Fse( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RestoreUsage4Fse( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterUsage4Fse( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MakeHeaderFSD( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oContentID,
            /* [in] */ BSTR oContentKEK,
            /* [in] */ BSTR oContentName,
            /* [in] */ BSTR oUserID,
            /* [in] */ BSTR oUserName,
            /* [in] */ BSTR oEtc1,
            /* [in] */ BSTR oEtc2,
            /* [in] */ BSTR oEtc3,
            /* [in] */ BSTR oEtc4,
            /* [in] */ BSTR oEtc5,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MakeHeaderFSN( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oContentID,
            /* [in] */ BSTR oContentKEK,
            /* [in] */ BSTR oContentName,
            /* [in] */ BSTR oUserID,
            /* [in] */ BSTR oUserName,
            /* [in] */ BSTR WriterID,
            /* [in] */ BSTR WriterNm,
            /* [in] */ BSTR WdeptID,
            /* [in] */ BSTR WdeptNm,
            /* [in] */ BSTR OwnerID,
            /* [in] */ BSTR OwnerNm,
            /* [in] */ BSTR OdeptID,
            /* [in] */ BSTR OdeptNm,
            /* [in] */ BSTR Level,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RequestLicenseInfo( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oLicenseRequestInfo,
            /* [in] */ BSTR oContentHeader,
            /* [in] */ BSTR oDummyInfo,
            /* [in] */ BSTR oUserId,
            /* [in] */ BSTR oEncfile,
            /* [in] */ BSTR pDecFile,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLogInfo( 
            /* [in] */ short level,
            /* [in] */ BSTR path) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLogLevel( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLogPathA( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RevokeUsageReaders4Fse( 
            BSTR oHomeDir,
            BSTR oServerID,
            BSTR oFile,
            BSTR oReaders) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RestoreUsageReaders4Fse( 
            BSTR oHomeDir,
            BSTR oServerID,
            BSTR oFile,
            BSTR oReaders) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoPackaging_sameHeader( 
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [in] */ BSTR TargetFile,
            /* [in] */ BSTR ContentHeader) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUsageLogInfo( 
            /* [in] */ BSTR oUserId,
            /* [in] */ BSTR oUserName,
            /* [in] */ BSTR oDeptId,
            /* [in] */ BSTR oDeptName,
            /* [in] */ BSTR oPositionId,
            /* [in] */ BSTR oPositionName,
            /* [in] */ short logEnabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIssuedDateStr( 
            /* [in] */ BSTR oFilepath,
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWorkPackagerADKVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWorkPackagerADK * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWorkPackagerADK * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWorkPackagerADK * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWorkPackagerADK * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWorkPackagerADK * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWorkPackagerADK * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWorkPackagerADK * This,
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
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_CharSet)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CharSet )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_CharSet)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CharSet )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_ContentID)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContentID )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_ContentID)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ContentID )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_IsTemp)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsTemp )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BOOL *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_IsTemp)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsTemp )( 
            IWorkPackagerADK * This,
            /* [in] */ BOOL newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_LastErrorNum)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastErrorNum )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ long *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_LastErrorStr)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastErrorStr )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_OverwriteFlag)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OverwriteFlag )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BOOL *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_OverwriteFlag)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OverwriteFlag )( 
            IWorkPackagerADK * This,
            /* [in] */ BOOL newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_SecureContainerFileName)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SecureContainerFileName )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_SecureContainerFileName)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SecureContainerFileName )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_PackageType)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PackageType )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_PackageType)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PackageType )( 
            IWorkPackagerADK * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_SecureContainerFilePathName)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SecureContainerFilePathName )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_SecureContainerFilePathName)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SecureContainerFilePathName )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, AddRightsFsn)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddRightsFsn )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oSourceFile,
            /* [in] */ BSTR oTargetFile,
            /* [in] */ BSTR targettype,
            /* [in] */ BSTR targetid,
            /* [in] */ BSTR targetname,
            /* [in] */ BSTR rightstring);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DeleteAllRightsFsn)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteAllRightsFsn )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oSourceFile,
            /* [in] */ BSTR oTargetFile);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DeleteRightsFsn)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteRightsFsn )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oSourceFile,
            /* [in] */ BSTR oTargetFile,
            /* [in] */ BSTR targettype,
            /* [in] */ BSTR targetid);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DoExtract)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoExtract )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [in] */ BSTR TargetFile);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DoExtract_c)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoExtract_c )( 
            IWorkPackagerADK * This,
            BSTR oHomeDir,
            BSTR oServerID,
            BSTR oSourceFile,
            BSTR oTargetFile,
            BSTR oPurpose);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DoExtract_s)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoExtract_s )( 
            IWorkPackagerADK * This,
            BSTR oHomeDir,
            BSTR oServerID,
            BSTR oSourceFile,
            BSTR oTargetFile,
            BSTR oUserId,
            BSTR oPurpose,
            BSTR oDummy1,
            BSTR oDummy2,
            BSTR oDummy3,
            BSTR oDummy4,
            BSTR oDummy5);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DoPackaging)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoPackaging )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [in] */ BSTR TargetFile,
            /* [in] */ BSTR ContentName,
            /* [in] */ BSTR UserID,
            /* [in] */ BSTR UserName,
            /* [in] */ BSTR Etc1,
            /* [in] */ BSTR Etc2,
            /* [in] */ BSTR Etc3,
            /* [in] */ BSTR Etc4,
            /* [in] */ BSTR Etc5);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DoPackagingFsn)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoPackagingFsn )( 
            IWorkPackagerADK * This,
            BSTR oHomeDir,
            BSTR oServerID,
            BSTR oSourceFile,
            BSTR oTargetFile,
            BSTR oContentName,
            BSTR oUserID,
            BSTR oUserName,
            BSTR oWriteID,
            BSTR oWriteName,
            BSTR oWdeptID,
            BSTR oWdeptName,
            BSTR oOwnerID,
            BSTR oOwnerName,
            BSTR oOdeptID,
            BSTR oOdeptName,
            short oSecurityLevel);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DoPackagingFsn2)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoPackagingFsn2 )( 
            IWorkPackagerADK * This,
            BSTR bHomeDir,
            BSTR bServerID,
            BSTR bSourceFile,
            BSTR bTargetFile,
            BSTR bContentName,
            BSTR bUserID,
            BSTR bUserName,
            BSTR bWriteID,
            BSTR bWriteName,
            BSTR bWdeptID,
            BSTR bWdeptName,
            BSTR bOwnerID,
            BSTR bOwnerName,
            BSTR bOdeptID,
            BSTR bOdeptName,
            BSTR bSecurityLevel_s);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DoPackagingNx)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoPackagingNx )( 
            IWorkPackagerADK * This,
            BSTR bHomeDir,
            BSTR bServerID,
            BSTR bSourceFile,
            BSTR bTargetFile,
            BSTR bContentName,
            BSTR bUserID,
            BSTR bUserName,
            BSTR bWriteID,
            BSTR bWriteName,
            BSTR bWdeptID,
            BSTR bWdeptName,
            BSTR bOwnerID,
            BSTR bOwnerName,
            BSTR bOdeptID,
            BSTR bOdeptName,
            BSTR bSecurityLevel_s);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, GetFileHeader)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFileHeader )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR sfile,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, GetFileHeaderA)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFileHeaderA )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR sfile,
            /* [retval][out] */ BSTR *pobj);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, GetFileHeaderW)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFileHeaderW )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR sfile,
            /* [retval][out] */ BSTR *pobj);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, GetFileType)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFileType )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR SourceFile,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, IsPackageFile)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsPackageFile )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR SourceFile,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, IsSupportFile)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsSupportFile )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, ReadAllRightsFse)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadAllRightsFse )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oTargetFile,
            /* [retval][out] */ BSTR *rightstring);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, ReadAllRightsFsn)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadAllRightsFsn )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oTargetFile,
            /* [retval][out] */ BSTR *rightstring);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, ReadRightsFse)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadRightsFse )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oTargetFile,
            /* [in] */ BSTR targetid,
            /* [retval][out] */ BSTR *rightstring);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, ReadRightsFsn)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadRightsFsn )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oTargetFile,
            /* [in] */ BSTR targettype,
            /* [in] */ BSTR targetid,
            /* [retval][out] */ BSTR *rightstring);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, ReadSenderFse)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadSenderFse )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oTargetFile,
            /* [retval][out] */ BSTR *sender);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DoPackagingFSM)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoPackagingFSM )( 
            IWorkPackagerADK * This,
            BSTR HomeDir,
            BSTR ServerID,
            BSTR SourceFile,
            BSTR TargetFile,
            BSTR ContentName,
            BSTR UserID,
            BSTR UserName,
            BSTR Etc1,
            BSTR Etc2,
            BSTR Etc3,
            BSTR Etc4,
            BSTR Etc5);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_EncryptedHeader4FSM)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EncryptedHeader4FSM )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_EncryptedHeader4FSM)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EncryptedHeader4FSM )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, AddHeaderInfo)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddHeaderInfo )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR key,
            /* [in] */ BSTR value);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, ChangeHeader)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangeHeader )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR homeDir,
            /* [in] */ BSTR serverID,
            /* [in] */ BSTR sourceFile);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, GetFileHeaderEx)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFileHeaderEx )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR sfile,
            /* [in] */ BSTR delim,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, GetFseReaderAndOption)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFseReaderAndOption )( 
            IWorkPackagerADK * This,
            BSTR sFile,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_CustomUserName)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CustomUserName )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_CustomUserName)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CustomUserName )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_CustomDeptCode)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CustomDeptCode )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_CustomDeptCode)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CustomDeptCode )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_CustomDeptName)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CustomDeptName )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_CustomDeptName)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CustomDeptName )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_CustomPositionCode)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CustomPositionCode )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_CustomPositionCode)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CustomPositionCode )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_CustomPositionName)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CustomPositionName )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_CustomPositionName)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CustomPositionName )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_CustomRoleCode)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CustomRoleCode )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_CustomRoleCode)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CustomRoleCode )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_CustomRoleName)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CustomRoleName )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_CustomRoleName)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CustomRoleName )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_CustomExdata)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CustomExdata )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_CustomExdata)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CustomExdata )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DoExtract_s2)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoExtract_s2 )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oSourceFile,
            /* [in] */ BSTR oTargetFile,
            /* [in] */ BSTR oUserId,
            /* [in] */ BSTR oPurpose,
            /* [in] */ BOOL oSaveFlag,
            /* [in] */ BSTR oDummy1,
            /* [in] */ BSTR oDummy2,
            /* [in] */ BSTR oDummy3,
            /* [in] */ BSTR oDummy4,
            /* [in] */ BSTR oDummy5);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_REQUrl)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_REQUrl )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_REQUrl)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_REQUrl )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_REQSubUrl)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_REQSubUrl )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_REQSubUrl)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_REQSubUrl )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_REQPort)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_REQPort )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_REQPort)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_REQPort )( 
            IWorkPackagerADK * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, get_REQProtocol)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_REQProtocol )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, put_REQProtocol)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_REQProtocol )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, RevokeUsage4Fse)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RevokeUsage4Fse )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oFile);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, RestoreUsage4Fse)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RestoreUsage4Fse )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oFile);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, RegisterUsage4Fse)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RegisterUsage4Fse )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oFile);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, MakeHeaderFSD)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MakeHeaderFSD )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oContentID,
            /* [in] */ BSTR oContentKEK,
            /* [in] */ BSTR oContentName,
            /* [in] */ BSTR oUserID,
            /* [in] */ BSTR oUserName,
            /* [in] */ BSTR oEtc1,
            /* [in] */ BSTR oEtc2,
            /* [in] */ BSTR oEtc3,
            /* [in] */ BSTR oEtc4,
            /* [in] */ BSTR oEtc5,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, MakeHeaderFSN)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MakeHeaderFSN )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oContentID,
            /* [in] */ BSTR oContentKEK,
            /* [in] */ BSTR oContentName,
            /* [in] */ BSTR oUserID,
            /* [in] */ BSTR oUserName,
            /* [in] */ BSTR WriterID,
            /* [in] */ BSTR WriterNm,
            /* [in] */ BSTR WdeptID,
            /* [in] */ BSTR WdeptNm,
            /* [in] */ BSTR OwnerID,
            /* [in] */ BSTR OwnerNm,
            /* [in] */ BSTR OdeptID,
            /* [in] */ BSTR OdeptNm,
            /* [in] */ BSTR Level,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, RequestLicenseInfo)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RequestLicenseInfo )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oLicenseRequestInfo,
            /* [in] */ BSTR oContentHeader,
            /* [in] */ BSTR oDummyInfo,
            /* [in] */ BSTR oUserId,
            /* [in] */ BSTR oEncfile,
            /* [in] */ BSTR pDecFile,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, SetLogInfo)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetLogInfo )( 
            IWorkPackagerADK * This,
            /* [in] */ short level,
            /* [in] */ BSTR path);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, GetLogLevel)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLogLevel )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, GetLogPathA)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLogPathA )( 
            IWorkPackagerADK * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, RevokeUsageReaders4Fse)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RevokeUsageReaders4Fse )( 
            IWorkPackagerADK * This,
            BSTR oHomeDir,
            BSTR oServerID,
            BSTR oFile,
            BSTR oReaders);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, RestoreUsageReaders4Fse)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RestoreUsageReaders4Fse )( 
            IWorkPackagerADK * This,
            BSTR oHomeDir,
            BSTR oServerID,
            BSTR oFile,
            BSTR oReaders);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, DoPackaging_sameHeader)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoPackaging_sameHeader )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [in] */ BSTR TargetFile,
            /* [in] */ BSTR ContentHeader);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, SetUsageLogInfo)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUsageLogInfo )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oUserId,
            /* [in] */ BSTR oUserName,
            /* [in] */ BSTR oDeptId,
            /* [in] */ BSTR oDeptName,
            /* [in] */ BSTR oPositionId,
            /* [in] */ BSTR oPositionName,
            /* [in] */ short logEnabled);
        
        DECLSPEC_XFGVIRT(IWorkPackagerADK, GetIssuedDateStr)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetIssuedDateStr )( 
            IWorkPackagerADK * This,
            /* [in] */ BSTR oFilepath,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IWorkPackagerADKVtbl;

    interface IWorkPackagerADK
    {
        CONST_VTBL struct IWorkPackagerADKVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWorkPackagerADK_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWorkPackagerADK_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWorkPackagerADK_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWorkPackagerADK_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWorkPackagerADK_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWorkPackagerADK_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWorkPackagerADK_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWorkPackagerADK_get_CharSet(This,pVal)	\
    ( (This)->lpVtbl -> get_CharSet(This,pVal) ) 

#define IWorkPackagerADK_put_CharSet(This,newVal)	\
    ( (This)->lpVtbl -> put_CharSet(This,newVal) ) 

#define IWorkPackagerADK_get_ContentID(This,pVal)	\
    ( (This)->lpVtbl -> get_ContentID(This,pVal) ) 

#define IWorkPackagerADK_put_ContentID(This,newVal)	\
    ( (This)->lpVtbl -> put_ContentID(This,newVal) ) 

#define IWorkPackagerADK_get_IsTemp(This,pVal)	\
    ( (This)->lpVtbl -> get_IsTemp(This,pVal) ) 

#define IWorkPackagerADK_put_IsTemp(This,newVal)	\
    ( (This)->lpVtbl -> put_IsTemp(This,newVal) ) 

#define IWorkPackagerADK_get_LastErrorNum(This,pVal)	\
    ( (This)->lpVtbl -> get_LastErrorNum(This,pVal) ) 

#define IWorkPackagerADK_get_LastErrorStr(This,pVal)	\
    ( (This)->lpVtbl -> get_LastErrorStr(This,pVal) ) 

#define IWorkPackagerADK_get_OverwriteFlag(This,pVal)	\
    ( (This)->lpVtbl -> get_OverwriteFlag(This,pVal) ) 

#define IWorkPackagerADK_put_OverwriteFlag(This,newVal)	\
    ( (This)->lpVtbl -> put_OverwriteFlag(This,newVal) ) 

#define IWorkPackagerADK_get_SecureContainerFileName(This,pVal)	\
    ( (This)->lpVtbl -> get_SecureContainerFileName(This,pVal) ) 

#define IWorkPackagerADK_put_SecureContainerFileName(This,newVal)	\
    ( (This)->lpVtbl -> put_SecureContainerFileName(This,newVal) ) 

#define IWorkPackagerADK_get_PackageType(This,pVal)	\
    ( (This)->lpVtbl -> get_PackageType(This,pVal) ) 

#define IWorkPackagerADK_put_PackageType(This,newVal)	\
    ( (This)->lpVtbl -> put_PackageType(This,newVal) ) 

#define IWorkPackagerADK_get_SecureContainerFilePathName(This,pVal)	\
    ( (This)->lpVtbl -> get_SecureContainerFilePathName(This,pVal) ) 

#define IWorkPackagerADK_put_SecureContainerFilePathName(This,newVal)	\
    ( (This)->lpVtbl -> put_SecureContainerFilePathName(This,newVal) ) 

#define IWorkPackagerADK_AddRightsFsn(This,oHomeDir,oServerID,oSourceFile,oTargetFile,targettype,targetid,targetname,rightstring)	\
    ( (This)->lpVtbl -> AddRightsFsn(This,oHomeDir,oServerID,oSourceFile,oTargetFile,targettype,targetid,targetname,rightstring) ) 

#define IWorkPackagerADK_DeleteAllRightsFsn(This,oHomeDir,oServerID,oSourceFile,oTargetFile)	\
    ( (This)->lpVtbl -> DeleteAllRightsFsn(This,oHomeDir,oServerID,oSourceFile,oTargetFile) ) 

#define IWorkPackagerADK_DeleteRightsFsn(This,oHomeDir,oServerID,oSourceFile,oTargetFile,targettype,targetid)	\
    ( (This)->lpVtbl -> DeleteRightsFsn(This,oHomeDir,oServerID,oSourceFile,oTargetFile,targettype,targetid) ) 

#define IWorkPackagerADK_DoExtract(This,HomeDir,ServerID,SourceFile,TargetFile)	\
    ( (This)->lpVtbl -> DoExtract(This,HomeDir,ServerID,SourceFile,TargetFile) ) 

#define IWorkPackagerADK_DoExtract_c(This,oHomeDir,oServerID,oSourceFile,oTargetFile,oPurpose)	\
    ( (This)->lpVtbl -> DoExtract_c(This,oHomeDir,oServerID,oSourceFile,oTargetFile,oPurpose) ) 

#define IWorkPackagerADK_DoExtract_s(This,oHomeDir,oServerID,oSourceFile,oTargetFile,oUserId,oPurpose,oDummy1,oDummy2,oDummy3,oDummy4,oDummy5)	\
    ( (This)->lpVtbl -> DoExtract_s(This,oHomeDir,oServerID,oSourceFile,oTargetFile,oUserId,oPurpose,oDummy1,oDummy2,oDummy3,oDummy4,oDummy5) ) 

#define IWorkPackagerADK_DoPackaging(This,HomeDir,ServerID,SourceFile,TargetFile,ContentName,UserID,UserName,Etc1,Etc2,Etc3,Etc4,Etc5)	\
    ( (This)->lpVtbl -> DoPackaging(This,HomeDir,ServerID,SourceFile,TargetFile,ContentName,UserID,UserName,Etc1,Etc2,Etc3,Etc4,Etc5) ) 

#define IWorkPackagerADK_DoPackagingFsn(This,oHomeDir,oServerID,oSourceFile,oTargetFile,oContentName,oUserID,oUserName,oWriteID,oWriteName,oWdeptID,oWdeptName,oOwnerID,oOwnerName,oOdeptID,oOdeptName,oSecurityLevel)	\
    ( (This)->lpVtbl -> DoPackagingFsn(This,oHomeDir,oServerID,oSourceFile,oTargetFile,oContentName,oUserID,oUserName,oWriteID,oWriteName,oWdeptID,oWdeptName,oOwnerID,oOwnerName,oOdeptID,oOdeptName,oSecurityLevel) ) 

#define IWorkPackagerADK_DoPackagingFsn2(This,bHomeDir,bServerID,bSourceFile,bTargetFile,bContentName,bUserID,bUserName,bWriteID,bWriteName,bWdeptID,bWdeptName,bOwnerID,bOwnerName,bOdeptID,bOdeptName,bSecurityLevel_s)	\
    ( (This)->lpVtbl -> DoPackagingFsn2(This,bHomeDir,bServerID,bSourceFile,bTargetFile,bContentName,bUserID,bUserName,bWriteID,bWriteName,bWdeptID,bWdeptName,bOwnerID,bOwnerName,bOdeptID,bOdeptName,bSecurityLevel_s) ) 

#define IWorkPackagerADK_DoPackagingNx(This,bHomeDir,bServerID,bSourceFile,bTargetFile,bContentName,bUserID,bUserName,bWriteID,bWriteName,bWdeptID,bWdeptName,bOwnerID,bOwnerName,bOdeptID,bOdeptName,bSecurityLevel_s)	\
    ( (This)->lpVtbl -> DoPackagingNx(This,bHomeDir,bServerID,bSourceFile,bTargetFile,bContentName,bUserID,bUserName,bWriteID,bWriteName,bWdeptID,bWdeptName,bOwnerID,bOwnerName,bOdeptID,bOdeptName,bSecurityLevel_s) ) 

#define IWorkPackagerADK_GetFileHeader(This,sfile,pVal)	\
    ( (This)->lpVtbl -> GetFileHeader(This,sfile,pVal) ) 

#define IWorkPackagerADK_GetFileHeaderA(This,sfile,pobj)	\
    ( (This)->lpVtbl -> GetFileHeaderA(This,sfile,pobj) ) 

#define IWorkPackagerADK_GetFileHeaderW(This,sfile,pobj)	\
    ( (This)->lpVtbl -> GetFileHeaderW(This,sfile,pobj) ) 

#define IWorkPackagerADK_GetFileType(This,SourceFile,pVal)	\
    ( (This)->lpVtbl -> GetFileType(This,SourceFile,pVal) ) 

#define IWorkPackagerADK_IsPackageFile(This,SourceFile,pVal)	\
    ( (This)->lpVtbl -> IsPackageFile(This,SourceFile,pVal) ) 

#define IWorkPackagerADK_IsSupportFile(This,HomeDir,ServerID,SourceFile,pVal)	\
    ( (This)->lpVtbl -> IsSupportFile(This,HomeDir,ServerID,SourceFile,pVal) ) 

#define IWorkPackagerADK_ReadAllRightsFse(This,oTargetFile,rightstring)	\
    ( (This)->lpVtbl -> ReadAllRightsFse(This,oTargetFile,rightstring) ) 

#define IWorkPackagerADK_ReadAllRightsFsn(This,oTargetFile,rightstring)	\
    ( (This)->lpVtbl -> ReadAllRightsFsn(This,oTargetFile,rightstring) ) 

#define IWorkPackagerADK_ReadRightsFse(This,oTargetFile,targetid,rightstring)	\
    ( (This)->lpVtbl -> ReadRightsFse(This,oTargetFile,targetid,rightstring) ) 

#define IWorkPackagerADK_ReadRightsFsn(This,oTargetFile,targettype,targetid,rightstring)	\
    ( (This)->lpVtbl -> ReadRightsFsn(This,oTargetFile,targettype,targetid,rightstring) ) 

#define IWorkPackagerADK_ReadSenderFse(This,oTargetFile,sender)	\
    ( (This)->lpVtbl -> ReadSenderFse(This,oTargetFile,sender) ) 

#define IWorkPackagerADK_DoPackagingFSM(This,HomeDir,ServerID,SourceFile,TargetFile,ContentName,UserID,UserName,Etc1,Etc2,Etc3,Etc4,Etc5)	\
    ( (This)->lpVtbl -> DoPackagingFSM(This,HomeDir,ServerID,SourceFile,TargetFile,ContentName,UserID,UserName,Etc1,Etc2,Etc3,Etc4,Etc5) ) 

#define IWorkPackagerADK_get_EncryptedHeader4FSM(This,pVal)	\
    ( (This)->lpVtbl -> get_EncryptedHeader4FSM(This,pVal) ) 

#define IWorkPackagerADK_put_EncryptedHeader4FSM(This,newVal)	\
    ( (This)->lpVtbl -> put_EncryptedHeader4FSM(This,newVal) ) 

#define IWorkPackagerADK_AddHeaderInfo(This,key,value)	\
    ( (This)->lpVtbl -> AddHeaderInfo(This,key,value) ) 

#define IWorkPackagerADK_ChangeHeader(This,homeDir,serverID,sourceFile)	\
    ( (This)->lpVtbl -> ChangeHeader(This,homeDir,serverID,sourceFile) ) 

#define IWorkPackagerADK_GetFileHeaderEx(This,sfile,delim,pVal)	\
    ( (This)->lpVtbl -> GetFileHeaderEx(This,sfile,delim,pVal) ) 

#define IWorkPackagerADK_GetFseReaderAndOption(This,sFile,pVal)	\
    ( (This)->lpVtbl -> GetFseReaderAndOption(This,sFile,pVal) ) 

#define IWorkPackagerADK_get_CustomUserName(This,pVal)	\
    ( (This)->lpVtbl -> get_CustomUserName(This,pVal) ) 

#define IWorkPackagerADK_put_CustomUserName(This,newVal)	\
    ( (This)->lpVtbl -> put_CustomUserName(This,newVal) ) 

#define IWorkPackagerADK_get_CustomDeptCode(This,pVal)	\
    ( (This)->lpVtbl -> get_CustomDeptCode(This,pVal) ) 

#define IWorkPackagerADK_put_CustomDeptCode(This,newVal)	\
    ( (This)->lpVtbl -> put_CustomDeptCode(This,newVal) ) 

#define IWorkPackagerADK_get_CustomDeptName(This,pVal)	\
    ( (This)->lpVtbl -> get_CustomDeptName(This,pVal) ) 

#define IWorkPackagerADK_put_CustomDeptName(This,newVal)	\
    ( (This)->lpVtbl -> put_CustomDeptName(This,newVal) ) 

#define IWorkPackagerADK_get_CustomPositionCode(This,pVal)	\
    ( (This)->lpVtbl -> get_CustomPositionCode(This,pVal) ) 

#define IWorkPackagerADK_put_CustomPositionCode(This,newVal)	\
    ( (This)->lpVtbl -> put_CustomPositionCode(This,newVal) ) 

#define IWorkPackagerADK_get_CustomPositionName(This,pVal)	\
    ( (This)->lpVtbl -> get_CustomPositionName(This,pVal) ) 

#define IWorkPackagerADK_put_CustomPositionName(This,newVal)	\
    ( (This)->lpVtbl -> put_CustomPositionName(This,newVal) ) 

#define IWorkPackagerADK_get_CustomRoleCode(This,pVal)	\
    ( (This)->lpVtbl -> get_CustomRoleCode(This,pVal) ) 

#define IWorkPackagerADK_put_CustomRoleCode(This,newVal)	\
    ( (This)->lpVtbl -> put_CustomRoleCode(This,newVal) ) 

#define IWorkPackagerADK_get_CustomRoleName(This,pVal)	\
    ( (This)->lpVtbl -> get_CustomRoleName(This,pVal) ) 

#define IWorkPackagerADK_put_CustomRoleName(This,newVal)	\
    ( (This)->lpVtbl -> put_CustomRoleName(This,newVal) ) 

#define IWorkPackagerADK_get_CustomExdata(This,pVal)	\
    ( (This)->lpVtbl -> get_CustomExdata(This,pVal) ) 

#define IWorkPackagerADK_put_CustomExdata(This,newVal)	\
    ( (This)->lpVtbl -> put_CustomExdata(This,newVal) ) 

#define IWorkPackagerADK_DoExtract_s2(This,oHomeDir,oServerID,oSourceFile,oTargetFile,oUserId,oPurpose,oSaveFlag,oDummy1,oDummy2,oDummy3,oDummy4,oDummy5)	\
    ( (This)->lpVtbl -> DoExtract_s2(This,oHomeDir,oServerID,oSourceFile,oTargetFile,oUserId,oPurpose,oSaveFlag,oDummy1,oDummy2,oDummy3,oDummy4,oDummy5) ) 

#define IWorkPackagerADK_get_REQUrl(This,pVal)	\
    ( (This)->lpVtbl -> get_REQUrl(This,pVal) ) 

#define IWorkPackagerADK_put_REQUrl(This,newVal)	\
    ( (This)->lpVtbl -> put_REQUrl(This,newVal) ) 

#define IWorkPackagerADK_get_REQSubUrl(This,pVal)	\
    ( (This)->lpVtbl -> get_REQSubUrl(This,pVal) ) 

#define IWorkPackagerADK_put_REQSubUrl(This,newVal)	\
    ( (This)->lpVtbl -> put_REQSubUrl(This,newVal) ) 

#define IWorkPackagerADK_get_REQPort(This,pVal)	\
    ( (This)->lpVtbl -> get_REQPort(This,pVal) ) 

#define IWorkPackagerADK_put_REQPort(This,newVal)	\
    ( (This)->lpVtbl -> put_REQPort(This,newVal) ) 

#define IWorkPackagerADK_get_REQProtocol(This,pVal)	\
    ( (This)->lpVtbl -> get_REQProtocol(This,pVal) ) 

#define IWorkPackagerADK_put_REQProtocol(This,newVal)	\
    ( (This)->lpVtbl -> put_REQProtocol(This,newVal) ) 

#define IWorkPackagerADK_RevokeUsage4Fse(This,oHomeDir,oServerID,oFile)	\
    ( (This)->lpVtbl -> RevokeUsage4Fse(This,oHomeDir,oServerID,oFile) ) 

#define IWorkPackagerADK_RestoreUsage4Fse(This,oHomeDir,oServerID,oFile)	\
    ( (This)->lpVtbl -> RestoreUsage4Fse(This,oHomeDir,oServerID,oFile) ) 

#define IWorkPackagerADK_RegisterUsage4Fse(This,oHomeDir,oServerID,oFile)	\
    ( (This)->lpVtbl -> RegisterUsage4Fse(This,oHomeDir,oServerID,oFile) ) 

#define IWorkPackagerADK_MakeHeaderFSD(This,oHomeDir,oServerID,oContentID,oContentKEK,oContentName,oUserID,oUserName,oEtc1,oEtc2,oEtc3,oEtc4,oEtc5,pVal)	\
    ( (This)->lpVtbl -> MakeHeaderFSD(This,oHomeDir,oServerID,oContentID,oContentKEK,oContentName,oUserID,oUserName,oEtc1,oEtc2,oEtc3,oEtc4,oEtc5,pVal) ) 

#define IWorkPackagerADK_MakeHeaderFSN(This,oHomeDir,oServerID,oContentID,oContentKEK,oContentName,oUserID,oUserName,WriterID,WriterNm,WdeptID,WdeptNm,OwnerID,OwnerNm,OdeptID,OdeptNm,Level,pVal)	\
    ( (This)->lpVtbl -> MakeHeaderFSN(This,oHomeDir,oServerID,oContentID,oContentKEK,oContentName,oUserID,oUserName,WriterID,WriterNm,WdeptID,WdeptNm,OwnerID,OwnerNm,OdeptID,OdeptNm,Level,pVal) ) 

#define IWorkPackagerADK_RequestLicenseInfo(This,oHomeDir,oServerID,oLicenseRequestInfo,oContentHeader,oDummyInfo,oUserId,oEncfile,pDecFile,pVal)	\
    ( (This)->lpVtbl -> RequestLicenseInfo(This,oHomeDir,oServerID,oLicenseRequestInfo,oContentHeader,oDummyInfo,oUserId,oEncfile,pDecFile,pVal) ) 

#define IWorkPackagerADK_SetLogInfo(This,level,path)	\
    ( (This)->lpVtbl -> SetLogInfo(This,level,path) ) 

#define IWorkPackagerADK_GetLogLevel(This,pVal)	\
    ( (This)->lpVtbl -> GetLogLevel(This,pVal) ) 

#define IWorkPackagerADK_GetLogPathA(This,pVal)	\
    ( (This)->lpVtbl -> GetLogPathA(This,pVal) ) 

#define IWorkPackagerADK_RevokeUsageReaders4Fse(This,oHomeDir,oServerID,oFile,oReaders)	\
    ( (This)->lpVtbl -> RevokeUsageReaders4Fse(This,oHomeDir,oServerID,oFile,oReaders) ) 

#define IWorkPackagerADK_RestoreUsageReaders4Fse(This,oHomeDir,oServerID,oFile,oReaders)	\
    ( (This)->lpVtbl -> RestoreUsageReaders4Fse(This,oHomeDir,oServerID,oFile,oReaders) ) 

#define IWorkPackagerADK_DoPackaging_sameHeader(This,HomeDir,ServerID,SourceFile,TargetFile,ContentHeader)	\
    ( (This)->lpVtbl -> DoPackaging_sameHeader(This,HomeDir,ServerID,SourceFile,TargetFile,ContentHeader) ) 

#define IWorkPackagerADK_SetUsageLogInfo(This,oUserId,oUserName,oDeptId,oDeptName,oPositionId,oPositionName,logEnabled)	\
    ( (This)->lpVtbl -> SetUsageLogInfo(This,oUserId,oUserName,oDeptId,oDeptName,oPositionId,oPositionName,logEnabled) ) 

#define IWorkPackagerADK_GetIssuedDateStr(This,oFilepath,pVal)	\
    ( (This)->lpVtbl -> GetIssuedDateStr(This,oFilepath,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWorkPackagerADK_INTERFACE_DEFINED__ */


#ifndef __IPackager_INTERFACE_DEFINED__
#define __IPackager_INTERFACE_DEFINED__

/* interface IPackager */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPackager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2CFD4C2B-BEB7-4240-9785-6D40CAC9960F")
    IPackager : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CharSet( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CharSet( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ContentID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ContentID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsTemp( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsTemp( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastErrorNum( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastErrorStr( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OverwriteFlag( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OverwriteFlag( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SecureContainerFileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SecureContainerFileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PackageType( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PackageType( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SecureContainerFilePathName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SecureContainerFilePathName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Sender( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Sender( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Reader( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reader( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanView( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CanView( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanPrint( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CanPrint( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanSave( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CanSave( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanSecureSave( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CanSecureSave( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanPrintScreen( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CanPrintScreen( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CanTransfer( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CanTransfer( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Count( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PcCount( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PcCount( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConfirmMail( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConfirmMail( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConfirmMail4In( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConfirmMail4In( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Period( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Period( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Authentication( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Authentication( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LicenseType( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LicenseType( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartDate( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartDate( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EndDate( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EndDate( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Option( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Option( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddReader( 
            /* [in] */ BSTR bstrReader) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoPackagingFSE( 
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [in] */ BSTR TargetFile,
            /* [in] */ BSTR ContentName,
            /* [in] */ BSTR UserID,
            /* [in] */ BSTR UserName,
            /* [in] */ BSTR Etc1,
            /* [in] */ BSTR Etc2,
            /* [in] */ BSTR Etc3,
            /* [in] */ BSTR Etc4,
            /* [in] */ BSTR Etc5) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SSOCLSID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SSOCLSID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MakeHeaderFSE( 
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oContentID,
            /* [in] */ BSTR oContentKEK,
            /* [in] */ BSTR oContentName,
            /* [in] */ BSTR oUserID,
            /* [in] */ BSTR oUserName,
            /* [in] */ BSTR oIssuedDateTime,
            /* [in] */ BSTR oEtc1,
            /* [in] */ BSTR oEtc2,
            /* [in] */ BSTR oEtc3,
            /* [in] */ BSTR oEtc4,
            /* [in] */ BSTR oEtc5,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoPackagingFSE2( 
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [in] */ BSTR TargetFile,
            /* [in] */ BSTR ContentName,
            /* [in] */ BSTR UserID,
            /* [in] */ BSTR UserName,
            /* [in] */ BSTR Etc1,
            /* [in] */ BSTR Etc2,
            /* [in] */ BSTR Etc3,
            /* [in] */ BSTR Etc4,
            /* [in] */ BSTR Etc5) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPackagerVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPackager * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPackager * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPackager * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPackager * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPackager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPackager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPackager * This,
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
        
        DECLSPEC_XFGVIRT(IPackager, get_CharSet)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CharSet )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_CharSet)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CharSet )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_ContentID)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ContentID )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_ContentID)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ContentID )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_IsTemp)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsTemp )( 
            IPackager * This,
            /* [retval][out] */ BOOL *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_IsTemp)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsTemp )( 
            IPackager * This,
            /* [in] */ BOOL newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_LastErrorNum)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastErrorNum )( 
            IPackager * This,
            /* [retval][out] */ long *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_LastErrorStr)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastErrorStr )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_OverwriteFlag)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OverwriteFlag )( 
            IPackager * This,
            /* [retval][out] */ BOOL *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_OverwriteFlag)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OverwriteFlag )( 
            IPackager * This,
            /* [in] */ BOOL newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_SecureContainerFileName)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SecureContainerFileName )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_SecureContainerFileName)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SecureContainerFileName )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_PackageType)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PackageType )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_PackageType)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PackageType )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_SecureContainerFilePathName)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SecureContainerFilePathName )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_SecureContainerFilePathName)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SecureContainerFilePathName )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_Sender)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sender )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_Sender)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Sender )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_Reader)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Reader )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_Reader)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Reader )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_CanView)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanView )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_CanView)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CanView )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_CanPrint)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanPrint )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_CanPrint)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CanPrint )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_CanSave)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanSave )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_CanSave)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CanSave )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_CanSecureSave)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanSecureSave )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_CanSecureSave)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CanSecureSave )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_CanPrintScreen)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanPrintScreen )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_CanPrintScreen)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CanPrintScreen )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_CanTransfer)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CanTransfer )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_CanTransfer)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CanTransfer )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_Count)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_Count)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Count )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_PcCount)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PcCount )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_PcCount)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PcCount )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_ConfirmMail)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConfirmMail )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_ConfirmMail)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConfirmMail )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_ConfirmMail4In)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConfirmMail4In )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_ConfirmMail4In)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConfirmMail4In )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_Period)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Period )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_Period)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Period )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_Authentication)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Authentication )( 
            IPackager * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_Authentication)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Authentication )( 
            IPackager * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_LicenseType)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LicenseType )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_LicenseType)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LicenseType )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_StartDate)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartDate )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_StartDate)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartDate )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_EndDate)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndDate )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_EndDate)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndDate )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, get_Option)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Option )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_Option)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Option )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, AddReader)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddReader )( 
            IPackager * This,
            /* [in] */ BSTR bstrReader);
        
        DECLSPEC_XFGVIRT(IPackager, DoPackagingFSE)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoPackagingFSE )( 
            IPackager * This,
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [in] */ BSTR TargetFile,
            /* [in] */ BSTR ContentName,
            /* [in] */ BSTR UserID,
            /* [in] */ BSTR UserName,
            /* [in] */ BSTR Etc1,
            /* [in] */ BSTR Etc2,
            /* [in] */ BSTR Etc3,
            /* [in] */ BSTR Etc4,
            /* [in] */ BSTR Etc5);
        
        DECLSPEC_XFGVIRT(IPackager, get_SSOCLSID)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SSOCLSID )( 
            IPackager * This,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, put_SSOCLSID)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SSOCLSID )( 
            IPackager * This,
            /* [in] */ BSTR newVal);
        
        DECLSPEC_XFGVIRT(IPackager, MakeHeaderFSE)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MakeHeaderFSE )( 
            IPackager * This,
            /* [in] */ BSTR oHomeDir,
            /* [in] */ BSTR oServerID,
            /* [in] */ BSTR oContentID,
            /* [in] */ BSTR oContentKEK,
            /* [in] */ BSTR oContentName,
            /* [in] */ BSTR oUserID,
            /* [in] */ BSTR oUserName,
            /* [in] */ BSTR oIssuedDateTime,
            /* [in] */ BSTR oEtc1,
            /* [in] */ BSTR oEtc2,
            /* [in] */ BSTR oEtc3,
            /* [in] */ BSTR oEtc4,
            /* [in] */ BSTR oEtc5,
            /* [retval][out] */ BSTR *pVal);
        
        DECLSPEC_XFGVIRT(IPackager, DoPackagingFSE2)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoPackagingFSE2 )( 
            IPackager * This,
            /* [in] */ BSTR HomeDir,
            /* [in] */ BSTR ServerID,
            /* [in] */ BSTR SourceFile,
            /* [in] */ BSTR TargetFile,
            /* [in] */ BSTR ContentName,
            /* [in] */ BSTR UserID,
            /* [in] */ BSTR UserName,
            /* [in] */ BSTR Etc1,
            /* [in] */ BSTR Etc2,
            /* [in] */ BSTR Etc3,
            /* [in] */ BSTR Etc4,
            /* [in] */ BSTR Etc5);
        
        END_INTERFACE
    } IPackagerVtbl;

    interface IPackager
    {
        CONST_VTBL struct IPackagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPackager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPackager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPackager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPackager_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPackager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPackager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPackager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPackager_get_CharSet(This,pVal)	\
    ( (This)->lpVtbl -> get_CharSet(This,pVal) ) 

#define IPackager_put_CharSet(This,newVal)	\
    ( (This)->lpVtbl -> put_CharSet(This,newVal) ) 

#define IPackager_get_ContentID(This,pVal)	\
    ( (This)->lpVtbl -> get_ContentID(This,pVal) ) 

#define IPackager_put_ContentID(This,newVal)	\
    ( (This)->lpVtbl -> put_ContentID(This,newVal) ) 

#define IPackager_get_IsTemp(This,pVal)	\
    ( (This)->lpVtbl -> get_IsTemp(This,pVal) ) 

#define IPackager_put_IsTemp(This,newVal)	\
    ( (This)->lpVtbl -> put_IsTemp(This,newVal) ) 

#define IPackager_get_LastErrorNum(This,pVal)	\
    ( (This)->lpVtbl -> get_LastErrorNum(This,pVal) ) 

#define IPackager_get_LastErrorStr(This,pVal)	\
    ( (This)->lpVtbl -> get_LastErrorStr(This,pVal) ) 

#define IPackager_get_OverwriteFlag(This,pVal)	\
    ( (This)->lpVtbl -> get_OverwriteFlag(This,pVal) ) 

#define IPackager_put_OverwriteFlag(This,newVal)	\
    ( (This)->lpVtbl -> put_OverwriteFlag(This,newVal) ) 

#define IPackager_get_SecureContainerFileName(This,pVal)	\
    ( (This)->lpVtbl -> get_SecureContainerFileName(This,pVal) ) 

#define IPackager_put_SecureContainerFileName(This,newVal)	\
    ( (This)->lpVtbl -> put_SecureContainerFileName(This,newVal) ) 

#define IPackager_get_PackageType(This,pVal)	\
    ( (This)->lpVtbl -> get_PackageType(This,pVal) ) 

#define IPackager_put_PackageType(This,newVal)	\
    ( (This)->lpVtbl -> put_PackageType(This,newVal) ) 

#define IPackager_get_SecureContainerFilePathName(This,pVal)	\
    ( (This)->lpVtbl -> get_SecureContainerFilePathName(This,pVal) ) 

#define IPackager_put_SecureContainerFilePathName(This,newVal)	\
    ( (This)->lpVtbl -> put_SecureContainerFilePathName(This,newVal) ) 

#define IPackager_get_Sender(This,pVal)	\
    ( (This)->lpVtbl -> get_Sender(This,pVal) ) 

#define IPackager_put_Sender(This,newVal)	\
    ( (This)->lpVtbl -> put_Sender(This,newVal) ) 

#define IPackager_get_Reader(This,pVal)	\
    ( (This)->lpVtbl -> get_Reader(This,pVal) ) 

#define IPackager_put_Reader(This,newVal)	\
    ( (This)->lpVtbl -> put_Reader(This,newVal) ) 

#define IPackager_get_CanView(This,pVal)	\
    ( (This)->lpVtbl -> get_CanView(This,pVal) ) 

#define IPackager_put_CanView(This,newVal)	\
    ( (This)->lpVtbl -> put_CanView(This,newVal) ) 

#define IPackager_get_CanPrint(This,pVal)	\
    ( (This)->lpVtbl -> get_CanPrint(This,pVal) ) 

#define IPackager_put_CanPrint(This,newVal)	\
    ( (This)->lpVtbl -> put_CanPrint(This,newVal) ) 

#define IPackager_get_CanSave(This,pVal)	\
    ( (This)->lpVtbl -> get_CanSave(This,pVal) ) 

#define IPackager_put_CanSave(This,newVal)	\
    ( (This)->lpVtbl -> put_CanSave(This,newVal) ) 

#define IPackager_get_CanSecureSave(This,pVal)	\
    ( (This)->lpVtbl -> get_CanSecureSave(This,pVal) ) 

#define IPackager_put_CanSecureSave(This,newVal)	\
    ( (This)->lpVtbl -> put_CanSecureSave(This,newVal) ) 

#define IPackager_get_CanPrintScreen(This,pVal)	\
    ( (This)->lpVtbl -> get_CanPrintScreen(This,pVal) ) 

#define IPackager_put_CanPrintScreen(This,newVal)	\
    ( (This)->lpVtbl -> put_CanPrintScreen(This,newVal) ) 

#define IPackager_get_CanTransfer(This,pVal)	\
    ( (This)->lpVtbl -> get_CanTransfer(This,pVal) ) 

#define IPackager_put_CanTransfer(This,newVal)	\
    ( (This)->lpVtbl -> put_CanTransfer(This,newVal) ) 

#define IPackager_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPackager_put_Count(This,newVal)	\
    ( (This)->lpVtbl -> put_Count(This,newVal) ) 

#define IPackager_get_PcCount(This,pVal)	\
    ( (This)->lpVtbl -> get_PcCount(This,pVal) ) 

#define IPackager_put_PcCount(This,newVal)	\
    ( (This)->lpVtbl -> put_PcCount(This,newVal) ) 

#define IPackager_get_ConfirmMail(This,pVal)	\
    ( (This)->lpVtbl -> get_ConfirmMail(This,pVal) ) 

#define IPackager_put_ConfirmMail(This,newVal)	\
    ( (This)->lpVtbl -> put_ConfirmMail(This,newVal) ) 

#define IPackager_get_ConfirmMail4In(This,pVal)	\
    ( (This)->lpVtbl -> get_ConfirmMail4In(This,pVal) ) 

#define IPackager_put_ConfirmMail4In(This,newVal)	\
    ( (This)->lpVtbl -> put_ConfirmMail4In(This,newVal) ) 

#define IPackager_get_Period(This,pVal)	\
    ( (This)->lpVtbl -> get_Period(This,pVal) ) 

#define IPackager_put_Period(This,newVal)	\
    ( (This)->lpVtbl -> put_Period(This,newVal) ) 

#define IPackager_get_Authentication(This,pVal)	\
    ( (This)->lpVtbl -> get_Authentication(This,pVal) ) 

#define IPackager_put_Authentication(This,newVal)	\
    ( (This)->lpVtbl -> put_Authentication(This,newVal) ) 

#define IPackager_get_LicenseType(This,pVal)	\
    ( (This)->lpVtbl -> get_LicenseType(This,pVal) ) 

#define IPackager_put_LicenseType(This,newVal)	\
    ( (This)->lpVtbl -> put_LicenseType(This,newVal) ) 

#define IPackager_get_StartDate(This,pVal)	\
    ( (This)->lpVtbl -> get_StartDate(This,pVal) ) 

#define IPackager_put_StartDate(This,newVal)	\
    ( (This)->lpVtbl -> put_StartDate(This,newVal) ) 

#define IPackager_get_EndDate(This,pVal)	\
    ( (This)->lpVtbl -> get_EndDate(This,pVal) ) 

#define IPackager_put_EndDate(This,newVal)	\
    ( (This)->lpVtbl -> put_EndDate(This,newVal) ) 

#define IPackager_get_Option(This,pVal)	\
    ( (This)->lpVtbl -> get_Option(This,pVal) ) 

#define IPackager_put_Option(This,newVal)	\
    ( (This)->lpVtbl -> put_Option(This,newVal) ) 

#define IPackager_AddReader(This,bstrReader)	\
    ( (This)->lpVtbl -> AddReader(This,bstrReader) ) 

#define IPackager_DoPackagingFSE(This,HomeDir,ServerID,SourceFile,TargetFile,ContentName,UserID,UserName,Etc1,Etc2,Etc3,Etc4,Etc5)	\
    ( (This)->lpVtbl -> DoPackagingFSE(This,HomeDir,ServerID,SourceFile,TargetFile,ContentName,UserID,UserName,Etc1,Etc2,Etc3,Etc4,Etc5) ) 

#define IPackager_get_SSOCLSID(This,pVal)	\
    ( (This)->lpVtbl -> get_SSOCLSID(This,pVal) ) 

#define IPackager_put_SSOCLSID(This,newVal)	\
    ( (This)->lpVtbl -> put_SSOCLSID(This,newVal) ) 

#define IPackager_MakeHeaderFSE(This,oHomeDir,oServerID,oContentID,oContentKEK,oContentName,oUserID,oUserName,oIssuedDateTime,oEtc1,oEtc2,oEtc3,oEtc4,oEtc5,pVal)	\
    ( (This)->lpVtbl -> MakeHeaderFSE(This,oHomeDir,oServerID,oContentID,oContentKEK,oContentName,oUserID,oUserName,oIssuedDateTime,oEtc1,oEtc2,oEtc3,oEtc4,oEtc5,pVal) ) 

#define IPackager_DoPackagingFSE2(This,HomeDir,ServerID,SourceFile,TargetFile,ContentName,UserID,UserName,Etc1,Etc2,Etc3,Etc4,Etc5)	\
    ( (This)->lpVtbl -> DoPackagingFSE2(This,HomeDir,ServerID,SourceFile,TargetFile,ContentName,UserID,UserName,Etc1,Etc2,Etc3,Etc4,Etc5) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPackager_INTERFACE_DEFINED__ */


#ifndef __IVersion_INTERFACE_DEFINED__
#define __IVersion_INTERFACE_DEFINED__

/* interface IVersion */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVersion;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3A0C7292-DA69-44FB-8400-AD9104CF52E6")
    IVersion : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVersion( 
            /* [retval][out] */ BSTR *pval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVersionVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVersion * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVersion * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVersion * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVersion * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVersion * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVersion * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVersion * This,
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
        
        DECLSPEC_XFGVIRT(IVersion, GetVersion)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVersion )( 
            IVersion * This,
            /* [retval][out] */ BSTR *pval);
        
        END_INTERFACE
    } IVersionVtbl;

    interface IVersion
    {
        CONST_VTBL struct IVersionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVersion_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVersion_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVersion_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVersion_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IVersion_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IVersion_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IVersion_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IVersion_GetVersion(This,pval)	\
    ( (This)->lpVtbl -> GetVersion(This,pval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVersion_INTERFACE_DEFINED__ */



#ifndef __WORKPACKAGERV3Lib_LIBRARY_DEFINED__
#define __WORKPACKAGERV3Lib_LIBRARY_DEFINED__

/* library WORKPACKAGERV3Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WORKPACKAGERV3Lib;

EXTERN_C const CLSID CLSID_WorkPackagerADK;

#ifdef __cplusplus

class DECLSPEC_UUID("A1F07262-DF30-4E93-9E93-63A3D50C991F")
WorkPackagerADK;
#endif

EXTERN_C const CLSID CLSID_Packager;

#ifdef __cplusplus

class DECLSPEC_UUID("1916BD43-E345-4B27-82EC-1CC05F08CD50")
Packager;
#endif

EXTERN_C const CLSID CLSID_Version;

#ifdef __cplusplus

class DECLSPEC_UUID("B620813C-AB71-4747-B8A4-7B67A41676EB")
Version;
#endif
#endif /* __WORKPACKAGERV3Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


