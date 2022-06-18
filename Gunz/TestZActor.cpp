#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "GlobalSubtitutes.h"
#include "ZGameMock.h"
#include "ZActor.h"
#include "ZObjectVMeshMock.h"


class ZActorMock : public ZActor
{
	MQuestNPCInfo m_npcInfo;
	MTD_NPCINFO m_mtdNpcInfo;	// �������� ���� npc ����

public:
	ZActorMock(IGame* pGame) : ZActor(pGame)
	{
		//strcpy(m_pNPCInfo->szMeshName, "testMesh");
	}

	virtual MQuestNPCInfo* GetQuestNPCInfo(MQUEST_NPC nNPCType)
	{
		return &m_npcInfo;
	}
	virtual MUID GetQuestBossUid()
	{
		return MUID(0,0);
	}
	virtual bool GetQuestCheat(ZQuestCheetType cheat)
	{
		return false;
	}
	virtual const MTD_NPCINFO* GetMyActorServerNPCInfo( const MQUEST_NPC nNPCID )
	{
		// m_npcInfo�� ���� ���� �����ش�
		m_mtdNpcInfo.m_nNPCTID = m_npcInfo.nID;
		m_mtdNpcInfo.m_nMaxHP = m_npcInfo.nMaxHP;
		m_mtdNpcInfo.m_nMaxAP = m_npcInfo.nMaxAP;
		m_mtdNpcInfo.m_nInt = m_npcInfo.nIntelligence;
		m_mtdNpcInfo.m_nAgility = m_npcInfo.nAgility;
		m_mtdNpcInfo.m_fAngle = m_pNPCInfo->fViewAngle;
		m_mtdNpcInfo.m_fDyingTime = m_pNPCInfo->fDyingTime;

		m_mtdNpcInfo.m_fCollisonRadius = m_pNPCInfo->fCollRadius;
		m_mtdNpcInfo.m_fCollisonHight = m_pNPCInfo->fCollHeight;

		m_mtdNpcInfo.m_nAttackType = m_npcInfo.nNPCAttackTypes;
		m_mtdNpcInfo.m_fAttackRange = m_npcInfo.fAttackRange;
		m_mtdNpcInfo.m_nWeaponItemID = m_npcInfo.nWeaponItemID;
		m_mtdNpcInfo.m_fDefaultSpeed = m_pNPCInfo->fSpeed;

		return &m_mtdNpcInfo;
	}
	virtual void AddLandingEffect(rvector vPos, rvector vDir) { }
	virtual void ShockBossGauge(float fDamage) { }
	virtual void LinkAniEventSet(MQUEST_NPC nNPCType) { }
	virtual void AllocObjectVMesh() { m_pVMesh = new ZObjectVMeshMock; }
	virtual float MakeSpeed( float fSpeed) { return fSpeed; }
	virtual float MakePathFindingUpdateTime( char nIntelligence) { return 1.f; }
	virtual float MakeAttackUpdateTime( char nAgility) { return 1.f; }
	virtual float MakeDefaultAttackCoolTime() { return 1.f; }
};

class ZBrainMock : public IBrain
{
public:
	virtual void Init( ZActor* pBody) {}
	virtual void Think( float fDelta) {}
	virtual void OnDamaged() {}

	virtual void OnBody_AnimEnter( ZA_ANIM_STATE nAnimState) {}
	virtual void OnBody_AnimExit( ZA_ANIM_STATE nAnimState) {}
	virtual void OnBody_OnTaskFinished( ZTASK_ID nLastID) {}
};

// �ܵ����� ZActor ��ü�� ������ �� �ִ��� �׽�Ʈ�Ѵ� (���������鿡 �����ϴ� �κ��� ����� �и��ߴ���)
// �׷��� �������� �Ǵ���, �ʱ�ȭ ���� ���� ����������� ���� ũ������ ���� �ʴ��� ������ üũ�ϴ� �����̹Ƿ�
// ���� �׽�Ʈ�� ������ ���� �ּ� ������ �����ϴ� �����̴�.
TEST(TestZActor, CreateZActor)
{
	MMatchItemDescMgrMock matchItemDescMgrMock;
	ZTddSetGlobalSub(GI_MatchItemDescMgr, &matchItemDescMgrMock);

	ZGameMock game;

	ZActorMock* pActor = new ZActorMock(&game);
	ZBrainMock* pBrain = new ZBrainMock;
	ZActor* pActorRet = ZActor::CreateActor(NPC_GOBLIN, 1.f, 0, false, pActor, pBrain);
	ASSERT_EQ(pActor, pActorRet);

	pActor->SetMyControl(true);

	pActor->Update(1.f);

	delete pActor;

	ZTddRemoveGlobalSub(GI_MatchItemDescMgr);
}


// �� ���� ZActor���� ���ο� ����Ʈ�� ���� ����Ǿ�� �� ��
// - ��ų ���� ������ �ø��� -> ��ų�� �ִϸ��̼�(nCastingAnimation)�� �޶� 4���ۿ� ���ٴ� ��(ZA_EVENT_SPECIAL1~4)�� �����ؾ� �Ѵ�
// - ZBrain�� FSM���� �ۼ��� AI ������ ������ �� �־�� �Ѵ�
// - �ִϸ��̼ǿ� �̵��� ���Ե� ��� ���� ���� ��ġ�� �̵����� �� �־�� �Ѵ� (ĳ���� �ʿ� �̹� �Ǿ� �ִ� �װ�)


#endif