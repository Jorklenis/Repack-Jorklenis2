/*
* (C) Copyright 2005. AhnLab, Inc.
*
* Any part of this source code can not be copied with
* any method without prior written permission from
* the author or authorized person.
*
* File Name : AntiCpSvrFunc.h
* Author: Nam Sung il(oncea@ahnlab.com)
*
* Revision History
* Date			Name					Description
* 2005-06-07	Nam, Sung-Il(siNam)		Created
* 2005-10-28	Park, Heean(hapark)		Add the Memory Checking
* 2005-11-15	Park, Heean(hapark)		Solve the Server rebooting issue
*
*/

#ifndef _ANTICPSVRFUNC_H
#define _ANTICPSVRFUNC_H

#define SIZEOF_REQMSG			160				// Request Message�� ���� ������ ũ��
#define SIZEOF_REQINFO			72				// Request Info�� ���� ������ ũ��
#define SIZEOF_ACKMSG			56				// Ack Message�� ���� ������ ũ��
#define SIZEOF_GUIDREQMSG		20				// GUID Request Message�� ���� ������ ũ��
#define SIZEOF_GUIDREQINFO		20				// GUID Request Info�� ���� ������ ũ��
#define SIZEOF_GUIDACKMSG		20				// GUID Ack Message�� ���� ������ ũ��

#define ALLOWED_ALL_SESSION				0xFFFFFFFF
#define ALLOWED_ONLY_LATEST_SESSION		0x00000001

#define ANTICPSVR_CHECK_GAME_MEMORY			0x1		// Game���� ��ȣ�ϴ� Memory�� ���� Request�� �����.
#define ANTICPSVR_CHECK_HACKSHIELD_FILE		0x2		// HackShield File�� ���� Request�� �����.
#define ANTICPSVR_CHECK_GAME_FILE			0x4		// Game File�� ���� Request�� �����.
#define ANTICPSVR_CHECK_ALL	( ANTICPSVR_CHECK_GAME_MEMORY | ANTICPSVR_CHECK_HACKSHIELD_FILE | ANTICPSVR_CHECK_GAME_FILE )


// �����ڵ� ����
#define ERROR_ANTICPSVR_BASECODE									0x0001C000
#define ERROR_ANTICPSVR_INIT_INVALIDPARAM							ERROR_ANTICPSVR_BASECODE + 0x1
#define ERROR_ANTICPSVR_INIT_INSERTCRCDATATOLIST_FAIL				ERROR_ANTICPSVR_BASECODE + 0x2

#define ERROR_ANTICPSVR_MAKEREQMSG_INVALIDPARAM						ERROR_ANTICPSVR_BASECODE + 0x10
#define ERROR_ANTICPSVR_MAKEREQMSG_MAKESKEY_FAIL					ERROR_ANTICPSVR_BASECODE + 0x11
#define ERROR_ANTICPSVR_MAKEREQMSG_INITCRYPT_FAIL					ERROR_ANTICPSVR_BASECODE + 0x12
#define ERROR_ANTICPSVR_MAKEREQMSG_ENCRYPT_FAIL						ERROR_ANTICPSVR_BASECODE + 0x13
#define ERROR_ANTICPSVR_MAKEREQMSG_GETRNDHASHINFO_FAIL				ERROR_ANTICPSVR_BASECODE + 0x14

#define ERROR_ANTICPSVR_ANALACKMSG_INVALIDPARAM						ERROR_ANTICPSVR_BASECODE + 0x20
#define ERROR_ANTICPSVR_ANALACKMSG_MAKESKEY_FAIL					ERROR_ANTICPSVR_BASECODE + 0x21
#define ERROR_ANTICPSVR_ANALACKMSG_INITCRYPT_FAIL					ERROR_ANTICPSVR_BASECODE + 0x22
#define ERROR_ANTICPSVR_ANALACKMSG_DECRYPT_FAIL  					ERROR_ANTICPSVR_BASECODE + 0x23
#define ERROR_ANTICPSVR_ANALACKMSG_HSHIELD_ERROR 					ERROR_ANTICPSVR_BASECODE + 0x24
#define ERROR_ANTICPSVR_ANALACKMSG_PACKET_ERROR 					ERROR_ANTICPSVR_BASECODE + 0x25
#define ERROR_ANTICPSVR_ANALACKMSG_FILECRC_ERROR					ERROR_ANTICPSVR_BASECODE + 0x26
#define ERROR_ANTICPSVR_ANALACKMSG_MEMORYCRC_ERROR					ERROR_ANTICPSVR_BASECODE + 0x27
#define ERROR_ANTICPSVR_ANALACKMSG_INVLIDSESSION					ERROR_ANTICPSVR_BASECODE + 0x28

#define ERROR_ANTICPSVR_INITCRYPT_INVALIDPARAM						ERROR_ANTICPSVR_BASECODE + 0x30
#define ERROR_ANTICPSVR_MAKESESSIONKEY_INVALIDPARAM					ERROR_ANTICPSVR_BASECODE + 0x31
#define ERROR_ANTICPSVR_GETENCMSG_INVALIDPARAM						ERROR_ANTICPSVR_BASECODE + 0x32
#define ERROR_ANTICPSVR_GETDECMSG_INVALIDPARAM						ERROR_ANTICPSVR_BASECODE + 0x33
#define ERROR_ANTICPSVR_MAKEACKSEQ_INVALIDPARAM						ERROR_ANTICPSVR_BASECODE + 0x34
#define ERROR_ANTICPSVR_GETRNDHASHINFO_INVALIDPARAM					ERROR_ANTICPSVR_BASECODE + 0x35
#define ERROR_ANTICPSVR_GETRNDHASHINFO_INVALIDENTRY					ERROR_ANTICPSVR_BASECODE + 0x36
#define ERROR_ANTICPSVR_GETRNDHASHINFO_EMPTYFUNCTIONLIST_ERROR		ERROR_ANTICPSVR_BASECODE + 0x37
#define ERROR_ANTICPSVR_EXCEPTION_OCCURED							ERROR_ANTICPSVR_BASECODE + 0x38
#define ERROR_ANTICPSVR_GETGUIDFROMCRCFILE_INVALIDPARAM				ERROR_ANTICPSVR_BASECODE + 0x39

#define ERROR_ANTICPSVR_MAKEGUIDREQMSG_INVALIDPARAM					ERROR_ANTICPSVR_BASECODE + 0x40
#define ERROR_ANTICPSVR_MAKEGUIDREQMSG_MAKESKEY_FAIL				ERROR_ANTICPSVR_BASECODE + 0x41
#define ERROR_ANTICPSVR_MAKEGUIDREQMSG_INITCRYPT_FAIL				ERROR_ANTICPSVR_BASECODE + 0x42
#define ERROR_ANTICPSVR_MAKEGUIDREQMSG_ENCRYPT_FAIL					ERROR_ANTICPSVR_BASECODE + 0x43

#define ERROR_ANTICPSVR_ANALGUIDACKMSG_INVALIDPARAM					ERROR_ANTICPSVR_BASECODE + 0x50
#define ERROR_ANTICPSVR_ANALGUIDACKMSG_MAKESKEY_FAIL				ERROR_ANTICPSVR_BASECODE + 0x51
#define ERROR_ANTICPSVR_ANALGUIDACKMSG_INITCRYPT_FAIL				ERROR_ANTICPSVR_BASECODE + 0x52
#define ERROR_ANTICPSVR_ANALGUIDACKMSG_DECRYPT_FAIL  				ERROR_ANTICPSVR_BASECODE + 0x53
#define ERROR_ANTICPSVR_ANALGUIDACKMSG_PACKET_ERROR 				ERROR_ANTICPSVR_BASECODE + 0x54
#define ERROR_ANTICPSVR_ANALGUIDACKMSG_DENIED_NEWSESSION			ERROR_ANTICPSVR_BASECODE + 0x55
#define ERROR_ANTICPSVR_ANALGUIDACKMSG_GETGUIDFROMCRCFILE_ERROR		ERROR_ANTICPSVR_BASECODE + 0x56
#define ERROR_ANTICPSVR_ANALGUIDACKMSG_INSERTCRCDATATOLIST_FAIL		ERROR_ANTICPSVR_BASECODE + 0x57
#define ERROR_ANTICPSVR_ANALGUIDACKMSG_INVALIDGUID					ERROR_ANTICPSVR_BASECODE + 0x58



#ifndef UNIX
#ifdef ANTICPSVR_EXPORTS
#define ANTICPSVR_API  __declspec(dllexport)
#else
#define ANTICPSVR_API  __declspec(dllimport)
#endif
#else
#define IN
#define OUT
#define __stdcall
#define ANTICPSVR_API
#endif

#if defined(__cplusplus)
extern "C"
{
#endif


/*!
 * 
 * @remarks �� �Լ��� ������ �ε��ɶ� �ѹ� ȣ���ϴ� �Լ��� ���������� ����ϴ� �������� �ʱ�ȭ�Ѵ�.
 *
 * @param	lpszHashFilePath : �ؽ��������� ����(HackShield.crc)�� ���� ��ü ���
 *
 */
ANTICPSVR_API
unsigned long
__stdcall
_AntiCpSvr_Initialize (
	IN const char *lpszHashFilePath
	);


/*!
 * 
 * @remarks �� �Լ��� ������ ��ε��ɶ� �ѹ� ȣ���ϴ� �Լ��� ���������� ����ϴ� �������� �ʱ�ȭ�Ѵ�.
 *
 */
ANTICPSVR_API
void
__stdcall
_AntiCpSvr_Finalize ();


/*!
 * 
 * @remarks �� �Լ��� ���ο� Ŭ���̾�Ʈ�� ����ɶ� Ŭ���̾�Ʈ�� �ѹ� ȣ��Ǵ� �Լ��� ���� ������
 *			Ŭ���̾�Ʈ�� ����ϴ� GUID ������ �������� Ȯ���ϱ� ���� ��û�޽����� �����ϴ� �Լ��̴�.
 *
 * @param	pbyGuidReqMsg : Ŭ���̾�Ʈ���� ���� ��ȣȭ�� Guid Request Message
 *							�� �����͸� ���� ������ ũ��(Byte)�� ���� ���ǵ� SIZEOF_GUIDREQMSG�̴�.
 * @param	pbyGuidReqInfo : _AntiCpSvr_AnalyzeGuidAckMsg() ���� �˻��Ҷ� ����� ���� Guid Request Info
 *							 �� �����͸� ���� ������ ũ��(Byte)�� ���� ���ǵ� SIZEOF_GUIDREQINFO�̴�.
 *
 * @attention	�� �Լ��� ȣ������ ������ �ش� Ŭ���̾�Ʈ�� GUID�� �� �� ���� ũ�� ������ Ȯ���� �� ����.
 *				���� ���� ũ��� ������ ����� ���� �����Ƿ� �ݵ�� �� ������Ͽ� ���ǵ� ���� ����Ͽ����Ѵ�.
 *
 */
ANTICPSVR_API
unsigned long
__stdcall
_AntiCpSvr_MakeGuidReqMsg (
	OUT unsigned char *pbyGuidReqMsg,
	OUT unsigned char *pbyGuidReqInfo
	);


/*!
 * 
 * @remarks �� �Լ��� ���ο� Ŭ���̾�Ʈ�� ����ɶ� Ŭ���̾�Ʈ�� �ѹ� ȣ��Ǵ� �Լ���
 *			_AntiCpSvr_MakeGuidReqMsg()�� ���� ������ GUID Request Message�� ����޽�����
 *			Ŭ���̾�Ʈ�� ��ȣȭ�Ͽ� ������ �ش� Ŭ���̾�Ʈ�� GUID�� ���Ǵ� �������� Ȯ���� ��
 *			���Ǵ� ������ ��� ������ ��� ����ϰ� �� CRC Info�� �ּҸ� �����Ѵ�.
 *
 * @param	pbyGuidAckMsg : Ŭ���̾�Ʈ���� ���� ��ȣȭ�� Guid ACK Message
 * @param	pbyGuidReqInfo : _AntiCpSvr_MakeGuidReqMsg() �Լ����� ������� ���� Guid Request Info
 * @param	ppCrcInfo : CRC Info�� ����ִ� �޸𸮸� ����ų �����͸� ������ ����
 *
 * @attention	���⼭ ���ϵǴ� ppCrcInfo�� ��� �ּҴ� �ش� Ŭ���̾�Ʈ�� Session�� ���涧����
 *				����ؼ� ���ǹǷ� Ŭ���̾�Ʈ���� ����ǰ� �����Ǿ�� �Ѵ�.
 *
 */
ANTICPSVR_API
unsigned long
__stdcall
_AntiCpSvr_AnalyzeGuidAckMsg (
	IN unsigned char *pbyGuidAckMsg,
	IN unsigned char *pbyGuidReqInfo,
	OUT unsigned long **ppCrcInfo
	);


/*!
 * 
 * @remarks �� �Լ��� Ŭ���̾�Ʈ�� ũ�� ������ Ȯ���ϰ� ���������� ȣ��Ǵ� �Լ���
 *			�ش� Ŭ���̾�Ʈ ������ �´� CRC ������ �̿��Ͽ� �������� �� �޸�, �ٽ���
 *			����� ���������� �����ϴ��� Ȯ���ϴ� Request Message�� ������ ����.
 *
 * @param	pCrcInfo : _AntiCpSvr_AnalyzeGuidAckMsg() �Լ����� ������ CRC Info�� �޸� �ּ�
 * @param	pbyReqMsg : Ŭ���̾�Ʈ���� ���� ��ȣȭ�� Request Message
 *						�� ������ ���� ������ ũ��(Byte)�� ���� ���ǵ� SIZEOF_REQMSG�̴�.
 * @param	pbyReqInfo : _AntiCpSvr_AnalyzeAckMsg() ���� �˻��Ҷ� ����� ���� Request Info
 *						 �� ������ ���� ������ ũ��(Byte)�� ���� ���ǵ� SIZEOF_REQINFO�̴�.
 * @param	ulOption : � �����鿡 ���� Request Message�� �������� ���� Flag, ���� ���ǵ�
 *						ANTICPSVR_CHECK_GAME_MEMORY, ANTICPSVR_CHECK_HACKSHIELD_FILE,
 *						ANTICPSVR_CHECK_GAME_FILE ���� OR�� �̿��Ͽ� ������ �� �ִ�.
 *						��, ������ ���� ���� ȣ��ô� ANTICPSVR_CHECK_ALL Option�� �̿��Ͽ�
 *						��ü�� ���� ���� ������ �˻��ϰ� �� �������ʹ� Performance�� ����
 *						ANTICPSVR_CHECK_GAME_MEMORY Option�� ����ϱ� �����Ѵ�.
 *
 * @attention	���� ũ��� ������ ����� ���� �����Ƿ� �ݵ�� �� ������Ͽ� ���ǵ� ���� ����Ͽ����Ѵ�.
 *
 */
ANTICPSVR_API
unsigned long
__stdcall
_AntiCpSvr_MakeReqMsg (
	IN unsigned long *pCrcInfo,
	OUT unsigned char *pbyReqMsg,
	OUT unsigned char *pbyReqInfo,
	IN unsigned long ulOption
	);


/*!
 * 
 * @remarks �� �Լ��� _AntiCpSvr_MakeReqMsg() �Լ��� ���� ������ ũ�� ���� Request Message��
 *			���� �������� Ŭ���̾�Ʈ�κ��� ��ȣȭ�� Ack Message�� �� ��� �ش� Ack Message��
 *			�м��Ͽ� Ŭ���̾�Ʈ�� ���������� �˻��Ѵ�.
 *
 * @param	pCrcInfo : _AntiCpSvr_AnalyzeGuidAckMsg() �Լ����� ������ CRC Info�� �޸� �ּ�
 * @param	pbyAckMsg : Ŭ���̾�Ʈ���� ���� ��ȣȭ�� ACK Message
 * @param	pbyReqInfo : _AntiCpSvr_MakeReqMsg() �Լ����� ������� ���� Request Message ����
 *
 */
ANTICPSVR_API
unsigned long
__stdcall
_AntiCpSvr_AnalyzeAckMsg (
	IN unsigned long *pCrcInfo,
	IN unsigned char *pbyAckMsg,
	IN unsigned char *pbyReqInfo
	);

#if defined(__cplusplus)
}
#endif

#endif //_ANTICPSVRFUNC_H
