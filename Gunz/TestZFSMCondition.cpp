#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZFSMCondition.h"
#include "ZFSMConditionSourceMock.h"


TEST(ZFSMCondition, TestAccessor)
{
	ZFSMCondition cond;
	cond.Init(FSMCOND_HP_LESS, 5);
	EXPECT_EQ(FSMCOND_HP_LESS, cond.GetConditionId());
	EXPECT_EQ(5, cond.GetArg(0));

	// ���⼭ ũ������ ���� �ȵ˴ϴ�.
	cond.GetArg(100);
	cond.GetArg(-1);
}

TEST(ZFSMCondition, Default)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_DEFAULT);
	EXPECT_TRUE(pCond->Check(&condSrc));	// �׻� true
	delete pCond;
}

TEST(ZFSMCondition, Dice)
{
	// dice�� ���� ���ο��� ���������� ���� �������� Ȯ���ؼ� �װ��� �������� ��/������ ���Ѵ�
	ZFSMConditionSourceMock condSrc;
	
	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_DICE, 10, 20);

	condSrc.m_nDice = 10;
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_nDice = 15;
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_nDice = 20;
	EXPECT_FALSE(pCond->Check(&condSrc));
	condSrc.m_nDice = 70;
	EXPECT_FALSE(pCond->Check(&condSrc));

	delete pCond;
}

TEST(ZFSMCondition, HpLessEqual)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_HP_EQUAL, 0);

	condSrc.m_fHp = 0.f;
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_fHp = 1.f;
	EXPECT_FALSE(pCond->Check(&condSrc));
	condSrc.m_fHp = -1.f;
	EXPECT_FALSE(pCond->Check(&condSrc));

	delete pCond;
}

TEST(ZFSMCondition, HpLessThan)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_HP_LESS, 10);

	condSrc.m_fHp = 8.f;
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_fHp = 11.f;
	EXPECT_FALSE(pCond->Check(&condSrc));
	condSrc.m_fHp = 10.f;
	EXPECT_FALSE(pCond->Check(&condSrc));		// '����'�� �ƴ� '�̸�'�̾�� ����

	delete pCond;
}

TEST(ZFSMCondition, HpGreaterThan)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_HP_GREATER, 0);

	condSrc.m_fHp = 0.1f;
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_fHp = -0.1f;
	EXPECT_FALSE(pCond->Check(&condSrc));
	condSrc.m_fHp = 0.f;
	EXPECT_FALSE(pCond->Check(&condSrc));		// '�̻�'�� �ƴ� '�ʰ�'�̾�� ����

	delete pCond;
}

TEST(ZFSMCondition, GroggyGreaterThan)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_GROGGY_GREATER, 30);

	condSrc.m_fGroggy = 35;
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_fGroggy = 10;
	EXPECT_FALSE(pCond->Check(&condSrc));
	condSrc.m_fGroggy = 30;
	EXPECT_FALSE(pCond->Check(&condSrc));		// '�̻�'�� �ƴ� '�ʰ�'�̾�� ����

	delete pCond;
}

TEST(ZFSMCondition, VelocityZLessThan)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_VELOCITY_Z_LESS, 0);

	condSrc.m_vVelocity = rvector(0, 0, -1);
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_vVelocity = rvector(0, 0, 1);
	EXPECT_FALSE(pCond->Check(&condSrc));
	condSrc.m_vVelocity = rvector(0, 0, 0);
	EXPECT_FALSE(pCond->Check(&condSrc));		// '����'�� �ƴ� '�̸�'�̾�� ����

	delete pCond;
}

TEST(ZFSMCondition, VelocityMagnitudeLessThan)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_VELOCITY_MAGNITUDE_LESS, 16);

	condSrc.m_vVelocity = rvector(0, 0, 10);
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_vVelocity = rvector(0, 0, 36);
	EXPECT_FALSE(pCond->Check(&condSrc));
	condSrc.m_vVelocity = rvector(0, 0, 16);
	EXPECT_FALSE(pCond->Check(&condSrc));		// '����'�� �ƴ� '�̸�'�̾�� ����

	delete pCond;
}

TEST(ZFSMCondition, EndOfAction)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_END_ACTION);

	condSrc.m_bEndAction = true;
	EXPECT_TRUE(pCond->Check(&condSrc));

	condSrc.m_bEndAction = false;
	EXPECT_FALSE(pCond->Check(&condSrc));

	delete pCond;
}

TEST(ZFSMCondition, IsLanding)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_IS_LANDING);

	condSrc.m_bLanding = true;
	EXPECT_TRUE(pCond->Check(&condSrc));

	condSrc.m_bLanding = false;
	EXPECT_FALSE(pCond->Check(&condSrc));

	delete pCond;
}

TEST(ZFSMCondition, HasTarget_and_HasNoTarget)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_HAS_TARGET);

	condSrc.m_bHasTarget = true;
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_bHasTarget = false;
	EXPECT_FALSE(pCond->Check(&condSrc));

	pCond->Init(FSMCOND_HAS_NO_TARGET);

	condSrc.m_bHasTarget = false;
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_bHasTarget = true;
	EXPECT_FALSE(pCond->Check(&condSrc));

	delete pCond;
}

TEST(ZFSMCondition, DistanceToTargetLessThan)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_DIST_TARGET_IN, 30, 80);

	condSrc.m_vMyPos = rvector(0, 0, 0);
	condSrc.m_bHasTarget = true;

	condSrc.m_vTargetPos = rvector(50, 0, 0);
	EXPECT_TRUE(pCond->Check(&condSrc));
	condSrc.m_vTargetPos = rvector(10, 0, 0);
	EXPECT_FALSE(pCond->Check(&condSrc));
	condSrc.m_vTargetPos = rvector(100, 0, 0);
	EXPECT_FALSE(pCond->Check(&condSrc));

	// Ÿ���� ���� ���� ������ �Ÿ� ����üũ�� ����ؼ� �ȵȴ�
	pCond->Init(FSMCOND_DIST_TARGET_IN, 0, 100);
	condSrc.m_bHasTarget = false;
	condSrc.m_vMyPos = rvector(0, 0, 0);
	condSrc.m_vTargetPos = rvector(10, 0, 0);
	EXPECT_FALSE(pCond->Check(&condSrc));

	delete pCond;
}

TEST(ZFSMCondition, LookAtTargetInDegree)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_LOOK_AT_TARGET, 90);	// �¿� 90�� �� �� 180�� ���� ������ ����� �ȴ�

	// ���� ���� �������κ��� ������ ���� ���� ���� �ִ°�
	condSrc.m_bHasTarget = true;
	condSrc.m_vMyPos = rvector(0, 0, 0);
	condSrc.m_vMyDir = rvector(1, 0, 0);
	condSrc.m_vTargetPos = rvector(50, 0, 0);
	EXPECT_TRUE(pCond->Check(&condSrc));

	// ���� - ���� ��ڿ� �ִ�
	condSrc.m_vTargetPos = rvector(-50, 0, 0);
	EXPECT_FALSE(pCond->Check(&condSrc));

	// ���� - �밢�� ����
	condSrc.m_vTargetPos = rvector(30, 30, 0);
	EXPECT_TRUE(pCond->Check(&condSrc));

	// ���� - ���� �밢�� ����
	condSrc.m_vTargetPos = rvector(-1, 50, 0);
	EXPECT_FALSE(pCond->Check(&condSrc));

	// Ÿ���� ���� ���� ������ üũ�� ����ؼ� �ȵȴ�

	delete pCond;
}

TEST(ZFSMCondition, IsEmptySpace)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_IS_EMPTY_SPACE, 0, 100);	// ����0(=����)�������� �Ÿ�100 ���� �ƹ��͵� ��ŷ���� �ʾƾ� ���� ���

	// �̰��� �׽�Ʈ�� ������� ����..;

	delete pCond;
}

TEST(ZFSMCondition, TimeElapsedSinceEntered)
{
	//todok TimeElapsedSinceEntered �׽�Ʈ �ۼ�
}

TEST(ZFSMCondition, EndLightningDamage)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_END_LIGHTNINGDAMAGE);

	// ����Ʈ�״���� ����� Ȱ��ȭ�� ���¸� �ȳ��� ������ ����
	condSrc.m_bActiveLightningDamage = true;
	EXPECT_FALSE(pCond->Check(&condSrc));

	condSrc.m_bActiveLightningDamage = false;
	EXPECT_TRUE(pCond->Check(&condSrc));

	delete pCond;
}

#endif