#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZFSM.h"
#include "ZFSMState.h"
#include "ZFSMTransition.h"


TEST(ZFSM, HasName)
{
	ZFSM* pFSM = new ZFSM;
	pFSM->SetName("knifeman");
	EXPECT_STREQ("knifeman", pFSM->GetName());
	delete pFSM;
}

TEST(ZFSM, HasEntryStateName)
{
	ZFSM* pFSM = new ZFSM;
	pFSM->SetEntryStateName("idle");
	EXPECT_STREQ("idle", pFSM->GetEntryStateName());
	delete pFSM;
}

TEST(ZFSM, HasStates)
{
	ZFSMState* pState1 = new ZFSMState;
	ZFSMState* pState2 = new ZFSMState;
	
	pState1->SetName("state1");
	pState2->SetName("state2");

	ZFSM* pFSM = new ZFSM;
	pFSM->AddState(pState1);
	pFSM->AddState(pState2);

	EXPECT_EQ(pState1, pFSM->GetState(pState1->GetName()));
	EXPECT_EQ(pState2, pFSM->GetState(pState2->GetName()));

	delete pFSM;
	// FSM�� �־��� state��ü�� FSM�� ������ �����Ѵ�
}

TEST(ZFSM, PrepareTransNextState)
{
	ZFSM* pFSM = new ZFSM;
	pFSM->SetName("knifeman");
	
	ZFSMState* pState1 = new ZFSMState;
	ZFSMState* pState2 = new ZFSMState;

	pState1->SetName("state1");
	pState2->SetName("state2");

	ZFSMTransition* pTrans1 = new ZFSMTransition;
	pTrans1->SetNextStateName("state2");
	pState1->AddTransition(pTrans1);

	ZFSMTransition* pTrans2 = new ZFSMTransition;
	pTrans2->SetNextStateName("state1");
	pState2->AddTransition(pTrans2);

	pFSM->AddState(pState1);
	pFSM->AddState(pState2);

	// �� ������, FSM�� state 2���� ���� �ְ� �� state�� ���ΰ� next state�̴�
	// xml���� FSM�� �ε��� ���Ŀ��� next state�� �̸��� �˰� �ִ� �����̴�
	// ZFSM�� �� transition�� ���� �ִ� next state�� �̸��� ���� state�� �����ͷ� ��ȯ�� �־�� �Ѵ�

	EXPECT_TRUE(NULL == pTrans2->GetNextState());
	EXPECT_TRUE(NULL == pTrans1->GetNextState());

	pFSM->PrepareTransNextState();

	EXPECT_EQ(pState1, pTrans2->GetNextState());
	EXPECT_EQ(pState2, pTrans1->GetNextState());

	delete pFSM;
}


/*
class ZActorActionMock : public IActorAction
{
public:
	
};

TEST(ZFSM, UpdateFrame)
{
	ZFSMCondition* pCondHpLessThan0 = new ZFSMCondition;
	pCondHpLessThan->Init(FSMCOND_HP_LESS, 0);
	ZFSMTransition* pTrans_HpLessThan0_Die = new ZFSMTransition;
	pTrans_HpLessThan0_Die->AddCondition(pCondHpLessThan0);
	pTrans_HpLessThan0_Die->SetNextState("")

	ZFSMState* pState;
	pState = new ZFSMState;
	pState->SetName("findTarget");
	pState->SetCooltime(0);


	ZFSM* pFSM = new ZFSM;
	pFSM->SetName("testFSM");
	pFSM->SetEntryStateName("findTarget");
}
*/

#endif