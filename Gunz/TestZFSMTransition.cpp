#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZFSMTransition.h"
#include "ZFSMConditionSourceMock.h"
#include "ZFSMState.h"


TEST(ZFSMTransition, CheckConditions)
{
	ZFSMState* pState = new ZFSMState;
	pState->SetName("someState");

	ZFSMConditionSourceMock condSrc;

	ZFSMCondition* pCondHpLess = new ZFSMCondition;
	pCondHpLess->Init(FSMCOND_HP_LESS, 15);
	ZFSMCondition* pCondGroggy = new ZFSMCondition;
	pCondGroggy->Init(FSMCOND_GROGGY_GREATER, 50);

	ZFSMTransition trans;
	trans.AddCondition(pCondHpLess);
	trans.AddCondition(pCondGroggy);
	trans.SetNextState(pState);

	// ���� ��� �����Ҷ�
	condSrc.m_fHp = 1;
	condSrc.m_fGroggy = 99;
	EXPECT_TRUE(trans.Check(&condSrc));

	// ���� �Ϻθ� �����Ҷ�
	condSrc.m_fHp = 1;
	condSrc.m_fGroggy = 0;
	EXPECT_FALSE(trans.Check(&condSrc));

	// ���� ��� �������� ���Ҷ�
	condSrc.m_fHp = 100;
	condSrc.m_fGroggy = 0;
	EXPECT_FALSE(trans.Check(&condSrc));

	delete pState;
	// �߰��� ���ǰ�ü�� ZFSMTransition�� �˾Ƽ� �Ҹ��Ŵ
}

TEST(ZFSMTransition, WhenHasNoConditions)
{
	ZFSMConditionSourceMock condSrc;

	ZFSMState* pState = new ZFSMState;
	pState->SetName("someState");

	ZFSMTransition trans;
	trans.SetNextState(pState);
	EXPECT_TRUE(trans.Check(&condSrc));	// ������ �ϳ��� �߰��Ǿ� ���� ������ �˻����� �׻� �����̴�

	delete pState;
}

TEST(ZFSMTransition, NextState)
{
	ZFSMTransition trans;

	// ó������ ������ ���°� �����Ǿ� ���� �ʴ�
	EXPECT_EQ(NULL, trans.GetNextState());

	// �ܺο� �����ϴ� � ���°� ���� ������ ������ ���¶�� ���� �˷���
	ZFSMState* pSomeState = new ZFSMState;
	trans.SetNextState(pSomeState);
	EXPECT_EQ(pSomeState, trans.GetNextState());

	delete pSomeState;
}

TEST(ZFSMTransition, CheckCondition)
{
	ZFSMState* pState = new ZFSMState;
	pState->SetCooltime(100);
	pState->SetName("someState");

	// �׻� true�� ��ȯ�ϴ� ������ ���� ���̰�ü
	ZFSMTransition trans;
	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_DEFAULT);
	trans.AddCondition(pCond);
	trans.SetNextState(pState);

	ZFSMConditionSourceMock condSrc;
	EXPECT_TRUE(trans.Check(&condSrc));

	delete pState;
}

#endif