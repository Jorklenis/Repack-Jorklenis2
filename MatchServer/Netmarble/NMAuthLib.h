// NMAuthLib.h: interface for the CNMAuthLib class.
/**
@file	NMAuthLib.h
@brief	�ݸ��� ���� ���� ���̺귯�� ��� ����.
@author	Heo Jaemin<judge@cj.net>
@date 	2009.10.28
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NMAUTHLIB_H__493CC8A5_8FFB_4CA8_86DB_C2318A62FC52__INCLUDED_)
#define AFX_NMAUTHLIB_H__493CC8A5_8FFB_4CA8_86DB_C2318A62FC52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

// �ݸ��� ���� ���� ���̺귯��(NMAuth) �ڵ��߰�.(Library ��δ� ������Ʈ ������ �߰�)
#if !defined(_LIB) && !defined(_NMAUTHDLL)
#ifndef _NMAUTHLIBNAME
#define _NMAUTHLIBNAME "./netmarble/NMAuthLib"
#endif //#ifndef _NMAUTHLIBNAME
#ifdef _DLL
#ifdef _DEBUG	// Debug multithread DLL
#pragma comment(lib, _NMAUTHLIBNAME "_MDd")
#else			// multithread DLL
#pragma comment(lib, _NMAUTHLIBNAME "_MD")
#endif // #ifdef _DEBUG
#else
#ifdef _DEBUG	// Debug multithread
#pragma comment(lib, _NMAUTHLIBNAME "_MTd")
#else			// multithread
#pragma comment(lib, _NMAUTHLIBNAME "_MT")
#endif // #ifdef _DEBUG
#endif // #ifdef _DLL
#endif //#if !defined(_LIB) && !defined(_NMAUTHDLL)

#define TIMEOUT_NMAUTH_DEFAULT 10000

/**
@defgroup GROUPERRCODE Error Code
@{
*/
/// @brief - �ݸ��� ���� ���̺귯�� �����ڵ�
enum eERROR_NMAUTH
{
	ERROR_NMAUTH_SUCCESS = 0,								///< ����(���� ����).
	ERROR_NMAUTH_FAIL,										///< ����.
	ERROR_NMAUTH_INVALIDPARAM,								///< �߸��� �Ķ����.
	ERROR_NMAUTH_OUTOFMEMEORY,								///< �޸𸮺���.
	ERROR_NMAUTH_FATALERROR,								///< ġ���� ����.
///	@details <b> ERROR_NMAUTH_LIB
	ERROR_NMAUTH_LIB_ALREADY_INITIALIZE = 11,				///< �̹� �ʱ�ȭ�Ǿ���.
	ERROR_NMAUTH_LIB_DLL_CANT_LOAD,							///< DLL�� �ε��� �� ����.
	ERROR_NMAUTH_LIB_DLL_NOT_LOADED,						///< DLL�� �ε���� ����.
	ERROR_NMAUTH_LIB_DLLPROC_NOTFOUND,						///< DLL �Լ��� ã�� �� ����.
///	@details <b> ERROR_NMAUTH_DLL
	ERROR_NMAUTH_DLL_ALREADY_INITED = 101,					///< DLL�� �̹� �ʱ�ȭ�Ǿ���.
	ERROR_NMAUTH_DLL_AUTHWINDOW_CREATE_FAIL,				///< ���� ���̺귯�� ���� ������ ���� ����.
///	@details <b> ERROR_NMAUTH_DLL_AUTHDATA
	ERROR_NMAUTH_DLL_AUTHDATA_NOT_INITED = 201,				///< ���� ������ Class�� �ʱ�ȭ���� �ʾ���.
	ERROR_NMAUTH_DLL_AUTHDATA_DUPKEY,						///< ���� ������ Class�� Key�� �ߺ���.
	ERROR_NMAUTH_DLL_AUTHDATA_NOTFOUND,						///< ���� ������ Class�� ã���� ����.
	ERROR_NMAUTH_DLL_AUTHDATA_ALREADY_INITED,				///< ���� ������ Class�� �̹� �ʱ�ȭ�Ǿ���.
	ERROR_NMAUTH_DLL_AUTHDATA_ALREADY_LOADING,				///< ���� ������ Class�� �̹� �����͸� �������� ����.
	ERROR_NMAUTH_DLL_AUTHDATA_INVALID_XMLURL,				///< �߸��� XML URL.
	ERROR_NMAUTH_DLL_AUTHDATA_XMLURL_ISNONE,				///< XML Url�� �������� ����.
	ERROR_NMAUTH_DLL_AUTHDATA_FAIL_INIT_EVTHANDLER,			///< �̺�Ʈ �ڵ鷯�� �ʱ�ȭ �Ҽ� ����.
	ERROR_NMAUTH_DLL_AUTHDATA_FAIL_MAKE_REQHEADER,			///< XML Request ����� �����ϴµ� ������.
	ERROR_NMAUTH_DLL_AUTHDATA_FAIL_GET_SOCKET,				///< XML Socket�� ȹ���ϴµ� ������.
	ERROR_NMAUTH_DLL_AUTHDATA_FAIL_OPEN_SOCKET,				///< XML Socket�� ���µ� ������.
	ERROR_NMAUTH_DLL_AUTHDATA_FAIL_WAITFORSYNC,				///< �̺�Ʈ�� ����ϴµ� ������.
	ERROR_NMAUTH_DLL_AUTHDATA_TIMEOUT_WAITFORSYNC,			///< �̺�Ʈ�� ����ϴµ� ������.(Ÿ�Ӿƿ�)
	ERROR_NMAUTH_DLL_AUTHDATA_MISSING_COOKIEDATA,			///< ��Ű�����Ͱ� ������.
	ERROR_NMAUTH_DLL_AUTHDATA_MISSING_AUTHDATA,				///< ���������Ͱ� ������.
///	@details <b> ERROR_NMAUTH_DLL_AUTHDATA_DECRYPT
	ERROR_NMAUTH_DLL_AUTHDATA_DECRYPT_INIT_FAIL = 301,		///< ��ȣȭ ��� �ʱ�ȭ ����.
	ERROR_NMAUTH_DLL_AUTHDATA_DECRYPT_FAIL,					///< ��ȣȭ ����.
///	@details <b> ERROR_NMAUTH_DLL_AUTHDATA_XML
	ERROR_NMAUTH_DLL_AUTHDATA_XML_NOT_LOADED_DATA = 401,	///< �����Ͱ� �ε���� ����.
	ERROR_NMAUTH_DLL_AUTHDATA_XML_FAIL_SENDREQUEST,			///< XML Request Header�� �����ϴµ� ������.
	ERROR_NMAUTH_DLL_AUTHDATA_XML_FAIL_ONSOCKDATA,			///< ���� ������ ó���� ������ �߻���.
	ERROR_NMAUTH_DLL_AUTHDATA_XML_FAIL_GETXMLCONTENTS,		///< XML Reponse �����͸� �������� ����.
///	@details <b> ERROR_NMAUTH_DLL_AUTHDATA_XML_STATUSCODE
	ERROR_NMAUTH_DLL_AUTHDATA_XML_STATUSCODE_FAIL_GET = 411,///< XML Status Code�� �����ü� ����.
	ERROR_NMAUTH_DLL_AUTHDATA_XML_STATUSCODE_INVALID,		///< �߸��� XML Status Code.
///	@details <b> ERROR_NMAUTH_DLL_AUTHDATA_XML_COM
	ERROR_NMAUTH_DLL_AUTHDATA_XML_COM_FAIL_CREATE = 421,	///< XML Com ���� ����.
	ERROR_NMAUTH_DLL_AUTHDATA_XML_COM_FAIL_LOAD,			///< XML Com ������ �ε� ����.
	ERROR_NMAUTH_DLL_AUTHDATA_XML_COM_FAIL_GETROOTELEMENT,	///< XML Com Root Element �������� ����.
	ERROR_NMAUTH_DLL_AUTHDATA_XML_COM_INVALID_ROOTNAME,		///< XML Com Root Element�� �̸��� ��ȿ���� ����.
	ERROR_NMAUTH_DLL_AUTHDATA_XML_COM_CHILDNODE_IS_NONE,	///< XML Com Chile element�� �������� ����.
///	@details <b> ERROR_NMAUTH_DLL_AUTHDATA_XML_DATA
	ERROR_NMAUTH_DLL_AUTHDATA_XML_DATA_NOTFOUND = 431,		///< XML �����͸� ã�� �� ����.
};

/// @brief -  �ݸ��� ���� ���̺귯�� �����ڵ� Ÿ�� ����
typedef unsigned int ERROR_NMAUTH;

/**
@}
*/

/**
@defgroup GROUPREADYSTATE ReadyState Code
@{
*/
/// @brief - �ݸ��� ���� ��� �����ڵ�
enum eNMAUTHDATA_READYSTATE {
	eNMAUTHDATA_READYSTATE_UNKNOWN = 0,	///< �˼� ���� ReadyState 
	eNMAUTHDATA_READYSTATE_INITED,				///< �ʱ�ȭ��.
	eNMAUTHDATA_READYSTATE_LOADING,         ///< ������ �ε���.
	eNMAUTHDATA_READYSTATE_ERROR,			///< ���� �߻�.
	eNMAUTHDATA_READYSTATE_COMPLETE,     ///< ������ �ε� �Ϸ�.
};

/// @brief - �ݸ��� ���� ���̺귯�� ReadyState �ڵ� Ÿ�� ����
typedef unsigned int NMAUTHDATA_READYSTATE;

/**
@brief - ReadyState ��ȭ �˸��� �Լ� Ÿ�� ����
@param[in] eReadyState - ��ȭ�� ReadyState
@param[in] pNMAuthLib - ��ȭ�� �߻��� ���� ������ Ŭ����.
@param[in] pUserData - �Լ� ������ �Բ� ������ ����������.
*/
typedef void (_stdcall *PFN_NMAUTHDATA_ONREADYSTATECHANGE)(NMAUTHDATA_READYSTATE eReadyState, const void* pNMAuthClass, const void* pUserData);

/**
@}
*/


/// @brief - �ݸ��� ���� ���̺귯�� API �Լ� ���ӽ����̽�.
namespace NMAuthLib 
{
	/**
	@brif - �������� �ݸ��� ���� ���� ���̺귯��(DLL) ������ �����Ѵ�.
	@returns �����ϸ� @ref ERROR_NMAUTH_SUCCESS ���� ��ȯ�ϰ�, �����Ͽ��� ��� ERROR_NMAUTH_SUCCESS �� ������ ������ @ref ERROR_NMAUTH ���� �ϳ��� ���� ��ȯ�Ѵ�.
	@param[in] szFileName - ������ ���� ���� ���̺귯��(DLL) ������ �����Ѵ�.
	@note �� �Լ��� Ư�� ��γ� ������ �ε��ؾ��� �ʿ䰡 ���� ��쿡�� ȣ���Ѵ�.<br>
	�� �Լ��� ȣ����� ���� ��� �⺻������ ���� ���丮�� DLL�� �ε��ϵ��� ���� �Ǿ��ִ�.	
	*/
	ERROR_NMAUTH _cdecl		SetCustomDLLFileName(const char* szFileName);

	/**
	@brif - �ݸ��� ���� ���̺귯�� ����� �ʱ�ȭ�Ѵ�.
	@returns �����ϸ� @ref ERROR_NMAUTH_SUCCESS ���� ��ȯ�ϰ�, �����Ͽ��� ��� ERROR_NMAUTH_SUCCESS �� ������ ������ @ref ERROR_NMAUTH ���� �ϳ��� ���� ��ȯ�Ѵ�.
	@param[in] szGameCode - ���� ����� ����ϰ� �ִ� ������ �ݸ��� �����ڵ带 �Է�. <br>
				�ݸ��� �����ڵ�� �ݸ��� ����Ʈ���� ������ �����ϱ� ���ؼ� �߱��ϴ� ���ڿ��� ������ �ڵ�.
	@param[in] bInteralGame - ����/CP ���� ���� �Ķ����. ���ΰ����ϰ�� true����, CP���� �� ��� false���� �Է��Ѵ�.
	@note Ư���� ������ ���� �� ���α׷��� ���۵ɶ� �ѹ��� ȣ��ǵ��� �ϸ�, �ش� �Լ� ȣ��� �����찡 �����ǹǷ�, <br>
	�޽��� ������ ���������� ���� �ֵ��� ���μ����� ���۵� �����忡�� ȣ�� �ϵ����Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEINIT "��� �ʱ�ȭ �� �ı�"
	*/
	ERROR_NMAUTH _cdecl		Init(const char* szGameCode, bool bInteralGame = true);
	
	/**
	@brif - �ݸ��� ���� ���̺귯�� ����� �ʱ�ȭ�Ѵ�.
	@returns �����ϸ� @ref ERROR_NMAUTH_SUCCESS ���� ��ȯ�ϰ�, �����Ͽ��� ��� ERROR_NMAUTH_SUCCESS �� ������ ������ @ref ERROR_NMAUTH ���� �ϳ��� ���� ��ȯ�Ѵ�.
	@param[in] szGameCode - ���� ����� ����ϰ� �ִ� ������ �ݸ��� �����ڵ带 �Է�. <br>
				�ݸ��� �����ڵ�� �ݸ��� ����Ʈ���� ������ �����ϱ� ���ؼ� �߱��ϴ� ���ڿ��� ������ �ڵ�.
	@param[in] szXMLBaseURL - �����͸� ������ XML�� �⺻ URL. �����ǰų� NULL ���� �Է��� ��� �⺻ ��(CP ���ӿ�)���� ó����.
	@note Ư���� ������ ���� �� ���α׷��� ���۵ɶ� �ѹ��� ȣ��ǵ��� �ϸ�, �ش� �Լ� ȣ��� �����찡 �����ǹǷ�, <br>
	�޽��� ������ ���������� ���� �ֵ��� ���μ����� ���۵� �����忡�� ȣ�� �ϵ����Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEINIT "��� �ʱ�ȭ �� �ı�"
	*/
	ERROR_NMAUTH _cdecl		Initialize(const char* szGameCode, const char* szXMLBaseURL = NULL);

	/**
	@brif - �ݸ��� ���� ���̺귯�� ����� �ı��Ѵ�.
	@note Ư���� ������ ���� �� ���α׷��� ����ɶ� �ѹ��� ȣ��ǵ��� �Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEINIT "��� �ʱ�ȭ �� �ı�"
	*/
	void _cdecl				Destroy();

	/**
	@brif - �־��� �����ڵ� ���� �������� ���ڿ� ���� �ڵ���� �����´�.
	@returns �־��� ���� �ڵ� ���� ��Ī�ϴ� ���ڿ� ���� �ڵ���� ������ ��� �ش� ���ڿ� �����ڵ� ���� ��ȯ�ϰ�, �������� ���� ��� NULL ���� ��ȯ�Ѵ�.
	@param[in] code - ���ڿ� ���� �ڵ���� ������ �����ڵ� ��.
	*/
	const char*	_cdecl		ErrorCode2String(ERROR_NMAUTH code);
	/**
	@brif - ReadyState �ڵ� ���� �������� ���ڿ� ReadyState �ڵ���� �����´�.
	@returns �־��� ReadyState �ڵ� ���� ��Ī�ϴ� ���ڿ� ReadyState �ڵ���� ������ ��� �ش� ���ڿ� ReadyState �ڵ� ���� ��ȯ�ϰ�, �������� ���� ��� NULL ���� ��ȯ�Ѵ�.
	@param[in] code - ���ڿ� ReadyState �ڵ���� ������ReadyState �ڵ� ��.
	*/
	const char*	_cdecl		ReadyState2String(NMAUTHDATA_READYSTATE code);
};

/**
@brief - �ݸ��� XML ���� ������ Ŭ����.
*/
class CNMXMLUserData {
public:
	/** @brif - CNMXMLUserData ������ */
	CNMXMLUserData();
	/** @brif - CNMXMLUserData �Ҹ��� */
	virtual ~CNMXMLUserData();

	/**
	@brif - �ݸ��� XML ���� ������ Ŭ������ �ı��Ѵ�.
	*/
	void			Destroy();

	/**
	@brif - ������ ������� SiteCode�� �����Ѵ�. (���ΰ��� ä�θ� ����)
	@returns �����ϸ� @ref ERROR_NMAUTH_SUCCESS ���� ��ȯ�ϰ�, �����Ͽ��� ��� ERROR_NMAUTH_SUCCESS �� ������ ������ @ref ERROR_NMAUTH ���� �ϳ��� ���� ��ȯ�Ѵ�.
	@param[in] iSiteCode - ������ ������� SiteCode
	*/
	ERROR_NMAUTH	SetSiteCode(int iSiteCode);

	/**
	@brif - XML�� ���� ���� �����͸� �ε��Ѵ�. (���� ���)
	@returns �����ϸ� @ref ERROR_NMAUTH_SUCCESS ���� ��ȯ�ϰ�, �����Ͽ��� ��� ERROR_NMAUTH_SUCCESS �� ������ ������ @ref ERROR_NMAUTH ���� �ϳ��� ���� ��ȯ�Ѵ�.
	@param[in] dwTimeOutMillisecond - XML �ε� Ÿ�Ӿƿ����� �����Ѵ�. �־��� Ÿ�� �ƿ� �̻����� ��Ⱑ �Ͼ ���, ������ �ε�� �ߴܵǰ� ������ ��ȯ�Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEXMLDATALOAD "����� ���� - XML ������ �ε�"
	*/
	ERROR_NMAUTH	LoadDataFromXML(DWORD dwTimeOutMillisecond = TIMEOUT_NMAUTH_DEFAULT);
	/**
	@brif - XML�� ���� ���� �����͸� �ε��Ѵ�. (�񵿱� ���)
	@returns �����ϸ� @ref ERROR_NMAUTH_SUCCESS ���� ��ȯ�ϰ�, �����Ͽ��� ��� ERROR_NMAUTH_SUCCESS �� ������ ������ @ref ERROR_NMAUTH ���� �ϳ��� ���� ��ȯ�Ѵ�.
	@param[in] pfnOnReadyStateChange - XML �ε� ReadyState�� ����ɶ� ȣ��� �Լ� �����͸� �Է��Ѵ�.
	@param[in] pUserData - XML �ε� ReadyState�� ����ɶ� ȣ��ɶ� ���� ���� UserData �� �Է��Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEXMLDATALOAD "����� ���� - XML ������ �ε�"
	*/
	ERROR_NMAUTH	LoadDataFromXML(PFN_NMAUTHDATA_ONREADYSTATECHANGE pfnOnReadyStateChange, const void* pUserData);

	/**
	@brif - XML ȣ��� ���������� ��ȯ�� HTTP Status Code�� �����´�.
	@returns XML ȣ��� ���������� ��ȯ�� HTTP Status Code�� ��ȯ�Ѵ�.
	*/
	DWORD			GetHTTPStatusCode();
	/**
	@brif - XML ȣ��� ���������� ��ȯ�� HTTP Contents�� �����´�.
	@returns XML ȣ��� ���������� ��ȯ�� HTTP Contents�� ��ȯ�Ѵ�.
	*/
	const char*		GetHTTPContents();

	/**
	@brif - XML ���� ����� �����´�.
	@returns �����ϸ� @ref ERROR_NMAUTH_SUCCESS ���� ��ȯ�ϰ�, �����Ͽ��� ��� ERROR_NMAUTH_SUCCESS �� ������ ������ @ref ERROR_NMAUTH ���� �ϳ��� ���� ��ȯ�Ѵ�.
	@param[out] bAllow_Out - �α��� ��� ���ΰ� ����� ������ �Է��Ѵ�.
	@param[out] pdwErrorCode_Out - XML ��� �ڵ带 ������ ������ ������ �Է��Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEXMLDATACHECK "����� ���� - XML ��� �ڵ� üũ"
	*/
	ERROR_NMAUTH	GetXMLResult(BOOL& bAllow_Out, DWORD* pdwErrorCode_Out = NULL);

	/**
	@brif - XML ���� ��� �޽����� ��ȯ�Ѵ�. 
	@returns ���ڿ��� �� ���� ��� �޽����� ��ȯ�Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEXMLDATACHECK "����� ���� - XML ��� �ڵ� üũ"
	*/
	const char*		GetXMLResultMessage();

	/**
	@brif - ���� Class�� ����� �������� ������ ��ȯ�Ѵ�.
	@returns ���� Class�� ����� �������� ������ ��ȯ�Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEGETDATA "����� ���� - ����� ���� ȹ��"
	*/
	DWORD			GetDataCount();
	/**
	@brif - �־��� �ε����� �������� �̸��� ��ȯ�Ѵ�.
	@returns �־��� �ε����� �������� �̸��� ��ȯ�Ѵ�.
	@param[in] dwIdx - ������ �������� �ε����� �Է��Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEGETDATA "����� ���� - ����� ���� ȹ��"
	*/
	const char* 	GetDataName(DWORD dwIdx);
	/**
	@brif - �־��� �̸��� �����͸� �����´�. 
	@returns �־��� �̸��� ���ڿ� �����͸� ��ȯ�Ѵ�.
	@param[in] szName - ������ �������� �̸��� �Է��Ѵ�.
	@remark �־��� �̸��� �����͸� �����ö�, ������ �̸��� ��ҹ��� �񱳴� ���õȴ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEGETDATA "����� ���� - ����� ���� ȹ��"
	*/
	const char* 	GetData(const char* szName);
	/**
	@brif - �־��� �̸��� �����͸� ���ۿ� �����Ѵ�. 
	@returns ������ ��� TRUE�� �׷��� ���� ��� FALSE�� ��ȯ�Ѵ�.
	@param[in] szName - ������ �������� �̸��� �Է��Ѵ�.
	@param[in] szBuffer - ������ �����Ͱ� ����� ��Ʈ�� ������ �����͸� �Է��Ѵ�.
	@param[in] cbBufferLen - ������ �����Ͱ� ����� ������ ���̸� �Է��Ѵ�.
	*/
	bool			CopyDataToString(const char* szName, char* pszBuffer, size_t cbBufferLen);
	/**
	@brif - �־��� �̸��� ���ڿ� �����͸� ���ڷ� ��ȯ�Ͽ� longŸ���� ���ۿ� �����Ѵ�. 
	@returns ������ ��� TRUE�� �׷��� ���� ��� FALSE�� ��ȯ�Ѵ�.
	@param[in] szName - ������ �������� �̸��� �Է��Ѵ�.
	@param[in] szBuffer - ������ �����Ͱ� ����� ������ �����͸� �Է��Ѵ�.
	*/
	bool			CopyDataToLong(const char* szName, long* pLongBuffer_Out);
	/**
	@brif - ���� XML �ε� ReadyState�� ��ȯ�Ѵ�.
	@returns ���� XML �ε� ReadyState�� ��ȯ�Ѵ�.
	*/
	NMAUTHDATA_READYSTATE	GetReadyState();
	/**
	@brif - XML �ε��߿� ���� �ֱٿ� ������ �����ڵ带 ��ȯ�Ѵ�.
	@returns XML �ε��߿� ���� �ֱٿ� ������ �����ڵ带 ��ȯ�Ѵ�.
	*/
	ERROR_NMAUTH			GetLastError();
};

//////////////////////////////////////////////////////////////////////////
// �ݸ��� ���� ���� ���� Ŭ����. (CP�� ��� �Ұ�)
/**
@brief - �ݸ��� ���� Ŭ����.
*/
class CNMAuth : public CNMXMLUserData {
public:
	/** @brif - CNMAuth ������ */
	CNMAuth();
	/** @brif - CNMAuth �Ҹ��� */
	virtual ~CNMAuth();

	/**
	@brif - �ݸ��� ���� ������ Ŭ������ �ʱ�ȭ�Ѵ�.(��Ű���)
	@returns �����ϸ� @ref ERROR_NMAUTH_SUCCESS ���� ��ȯ�ϰ�, �����Ͽ��� ��� ERROR_NMAUTH_SUCCESS �� ������ ������ @ref ERROR_NMAUTH ���� �ϳ��� ���� ��ȯ�Ѵ�.
	@param[in] szAuthCookie - ������ Ȯ���� ������� �ݸ��� AuthCookie �� �Է��Ѵ�.
	@param[in] szDataCookie - ������ Ȯ���� ������� �ݸ��� DataCookie �� �Է��Ѵ�.
	@param[in] szCPCookie - ������ Ȯ���� ������� �ݸ��� CPCookie �� �Է��Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLEXMLDATALOAD "����� ���� - XML ������ �ε�"
	- @ref PAGEEXAMPLEGETDATA "����� ���� - ����� ���� ȹ��"
	- @ref PAGEEXAMPLECKDATA "����� ���� - ��Ű�� ���� ������ ����"
	*/
	ERROR_NMAUTH	Init(const char* szAuthCookie, const char* szDataCookie, const char* szCPCookie);
	/**
	@brif - ��Ű ���� ���� ��ȣȭ�Ͽ� ���� �����͸� �ε��Ѵ�.
	@returns �����ϸ� @ref ERROR_NMAUTH_SUCCESS ���� ��ȯ�ϰ�, �����Ͽ��� ��� ERROR_NMAUTH_SUCCESS �� ������ ������ @ref ERROR_NMAUTH ���� �ϳ��� ���� ��ȯ�Ѵ�.
	@section SECEXAMPLE ���� ���� 
	- @ref PAGEEXAMPLECKDATA "����� ���� - ��Ű�� ���� ������ ����"
	*/
	ERROR_NMAUTH	LoadDataFromCookie();
};

#endif // !defined(AFX_NMAUTHLIB_H__493CC8A5_8FFB_4CA8_86DB_C2318A62FC52__INCLUDED_)
