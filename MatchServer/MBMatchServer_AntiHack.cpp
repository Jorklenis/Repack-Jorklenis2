#include "stdafx.h"
#include "MBMatchServer.h"

#ifdef _GAMEGUARD
#include "MBMatchGameGuard.h"
#include "MBMatchGGSvrRef.h"
#endif

#ifdef _XTRAP
#include "MBMatchXTrapCC.h"
#endif

void MBMatchServer::OnResponseGameguardAuth( const MUID& uidUser, const DWORD dwIndex, const DWORD dwValue1, const DWORD dwValue2, const DWORD dwValue3 )
{
#ifdef _GAMEGUARD
	MMatchObject* pObj = GetObject( uidUser );
	if( 0 == pObj )
		return;

	MBMatchGameguard* pGameguard = GetGameguard( uidUser );
	if( 0 == pGameguard )
	{
		// ggtest
		LOG(LOG_PROG,  "GAMEGUARD ERR :gameguard obj is null point (2). AID(%u)\n"
			, pObj->GetAccountInfo()->m_nAID );

//		pObj->SetGameguardHackerDisconnectWaitInfo();
		pObj->DisconnectHacker(MMHT_GAMEGUARD_HACKER);

		return;
	}

#ifdef _DEBUG
	mlog( "GAMEGUARD : receivce from client : index(%u), v1(%u), v2(%u), v3(%u)\n",
		dwIndex, dwValue1, dwValue2, dwValue3 );
#endif

	pGameguard->SetAuthAnswer( dwIndex, dwValue1, dwValue2, dwValue3 );

	if( !pGameguard->CheckAuthAnswer(GetGlobalClockCount()) )
	{
		// ggtest
		LOG(LOG_PROG,  "GAMEGUARD ERR : response gameguard auth : errcode(%u), AID(%u), CreateAuthCount(%u)\n"
			, pGameguard->GetLastError()
			, pObj->GetAccountInfo()->m_nAID
			, pGameguard->GetCreateAuthCount() );

//		pObj->SetGameguardHackerDisconnectWaitInfo();
		pObj->DisconnectHacker(MMHT_GAMEGUARD_HACKER);
		return;
	}

	pGameguard->UpdateLastCheckTime( GetGlobalClockCount() );

#else
	mlog( "this server version isn't use gameguard... why call me!!\n" );
#endif
}


void MBMatchServer::OnResponseFirstGameguardAuth( const MUID& uidUser, const DWORD dwIndex, const DWORD dwValue1, const DWORD dwValue2, const DWORD dwValue3 )
{
#ifdef _GAMEGUARD
	MMatchObject* pObj = GetObject( uidUser );
	if( 0 == pObj )
		return;

#ifdef _DEBUG
	mlog( "GAMEGUARD : first receivce from client : index(%u), v1(%u), v2(%u), v3(%u)\n",
		dwIndex, dwValue1, dwValue2, dwValue3 );
#endif

	MBMatchGameguard* pGameguard = GetGameguard( uidUser );
	if( 0 == pGameguard )
	{
		// ggtest
		LOG(LOG_PROG,  "GAMEGUARD ERR :gameguard obj is null point (2). AID(%u)\n"
			, pObj->GetAccountInfo()->m_nAID );

//		pObj->SetGameguardHackerDisconnectWaitInfo();
		pObj->DisconnectHacker(MMHT_GAMEGUARD_HACKER);

		return;
	}

	pGameguard->SetAuthAnswer( dwIndex, dwValue1, dwValue2, dwValue3 );

	if( !pGameguard->CheckAuthAnswer(GetGlobalClockCount()) )
	{
//		pObj->SetGameguardHackerDisconnectWaitInfo();
		pObj->DisconnectHacker(MMHT_GAMEGUARD_HACKER);

#ifdef _DEBUG
		// ggtest
		LOG(LOG_PROG,  "GAMEGUARD ERR :first gameguard auth : errcode(%u), AID(%u), CreateAuthCount(%u)\n"
			, pGameguard->GetLastError()
			, pObj->GetAccountInfo()->m_nAID
			, pGameguard->GetCreateAuthCount() );
#endif

		return;
	}

	// ó�� ������ ������ �ٷ� �ѹ��� Ȯ���� ����� �Ѵ�.
	if( pGameguard->CreateAuthQuery() )
	{
		const GG_AUTH_DATA& AuthData = pGameguard->GetServerAuth()->GetAuthQuery();
		RequestGameguardAuth( uidUser
			, AuthData.dwIndex
			, AuthData.dwValue1
			, AuthData.dwValue2
			, AuthData.dwValue3 );
	}
	else
	{
//		pObj->SetGameguardHackerDisconnectWaitInfo();
		pObj->DisconnectHacker(MMHT_GAMEGUARD_HACKER);

		LOG(LOG_PROG,  "GAMEGUARD ERR : create second auth key : ErrCode(%d), AID(%u), CreateAuthCount(%u)\n"
			, pGameguard->GetLastError()
			, pObj->GetAccountInfo()->m_nAID
			, pGameguard->GetCreateAuthCount() );

		return;
	}

	// NHN�� �̰� ������ ��� ���Ŀ� ��� Ŀ�ǵ� ��û�� ����ȴ�.
	pObj->FirstGameguardResponseIsRecved();

	// NHN�� �ʱ� gameguard������ �Ϸ�Ǿ�� ĳ���� ����Ʈ�� �����ش�.
	OnRequestAccountCharList( pObj->GetUID(), NULL );

#else
	mlog( "this server version isn't use gameguard... why call me!!\n" );
#endif
}

void MBMatchServer::OnResponseXTrapSeedKey(const MUID &uidUser, unsigned char *pComBuf)
{
#ifdef _XTRAP
	MMatchObject *pObj = GetObject(uidUser);
	if (pObj == NULL)
	{
		return;
	}

	if (pObj->GetDisconnStatusInfo().GetStatus() != MMDS_CONNECTED)
	{
		return;
	}

	MBMatchXTrapCC *pXTrapCC = GetXTrapCC(uidUser);
	if (pXTrapCC == NULL)
	{
        return;
	}

	DWORD retVal = pXTrapCC->XTrapCheckHashData(pComBuf);
    if (retVal != 0)
	{
		// �ش� ���� ���� ó��
//		pObj->SetXTrapHackerDisconnectWaitInfo();
		pObj->DisconnectHacker( MMHT_XTRAP_HACKER );
	}
#endif
}