#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZFSMState.h"
#include "ZFSMTransition.h"
#include "ZFSMConditionSourceMock.h"
#include "ZActorAction.h"
#include "ZFSMFunctionServer.h"

class ZActionDummy : public IActorAction
{
public:
	virtual ~ZActionDummy() {}
	virtual const char* GetName() { return ""; }
	virtual const char* GetAnimationName() { return ""; };
	virtual bool IsMovingAnimation() { return false; }
	virtual const ZActorActionMeleeShot* GetMeleeShot() { return NULL; }
	virtual const ZActorActionRangeShot* GetRangeShot(int idx) { return NULL; }
	virtual int GetNumRangeShot() { return 0; }
};

TEST(ZFSMState, InitFSMState)
{
	ZFSMState* pState = new ZFSMState;
	
	pState->SetName("idle");
	EXPECT_STREQ("idle", pState->GetName());

	pState->SetCooltime(100);
	EXPECT_EQ(100, pState->GetCooltime());

	// �׼��� NULL�� ��ȿ��
	pState->SetAction(NULL);
	EXPECT_EQ(NULL, pState->GetAction());

	ZActionDummy* pAction = new ZActionDummy;
	pState->SetAction(pAction);
	EXPECT_EQ(pAction, pState->GetAction());

	delete pState;
	delete pAction;
}

TEST(ZFSMState, CheckTransition)
{
	ZFSMState* pStateNormal = new ZFSMState;
	ZFSMState* pStateFlee = new ZFSMState;

	ZFSMCondition* pCond = new ZFSMCondition;
	pCond->Init(FSMCOND_HP_LESS, 10);

	ZFSMTransition* pTrans = new ZFSMTransition;
	pTrans->AddCondition(pCond);
	pTrans->SetNextState(pStateFlee);

	pStateNormal->AddTransition(pTrans);

	// ü���� ���� ��¥��ü
	ZFSMConditionSourceMock condSrc;
	condSrc.m_fHp = 80;

	// ü���� ���� ���簡�� ���̰˻� �غ���
	ZFSMState* pNextState = pStateNormal->CheckTransition(&condSrc);
	EXPECT_EQ(NULL, pNextState);	// ���̰� �Ͼ�� ������ NULL�� ����

	condSrc.m_fHp = 3;
	pNextState = pStateNormal->CheckTransition(&condSrc);
	EXPECT_EQ(pStateFlee, pNextState);	// ���̰� �Ͼ�� �ϸ� ������ state ��ü�� �����͸� ����

	// ���� ZFSMTransition��ü�� �˾Ƽ� �����Ѵ�
	delete pStateNormal;
	delete pStateFlee;
}

TEST(ZFSMState, HasFunctionCallList)
{
	// �뷫 �̷� ���� id�� ���ڸ� ���� ������� �ִٰ� ����
	ZFSMFunctionCall funcCall1;
	funcCall1.id = 23;
	funcCall1.nArg[0] = 4;
	funcCall1.nArg[1] = 0;
	funcCall1.nArg[2] = 5;
	funcCall1.nArg[3] = 0;
	ZFSMFunctionCall funcCall2;
	funcCall2.id = 1;
	funcCall2.nArg[0] = 2;
	funcCall2.nArg[1] = 99;
	funcCall2.nArg[2] = 0;
	funcCall2.nArg[3] = 0;

	vector<ZFSMFunctionCall> vecFunctionCall;
	vecFunctionCall.push_back(funcCall1);
	vecFunctionCall.push_back(funcCall2);
	
	// state�� ����־��
	ZFSMState state;
	state.SetFunctionCalls(vecFunctionCall);

	// ������ ���غ���
	EXPECT_EQ(2, state.GetFunctionCallCount());
	const ZFSMFunctionCall* r1 = state.GetFunctionCall(0);
	const ZFSMFunctionCall* r2 = state.GetFunctionCall(1);

	EXPECT_EQ(0, memcmp(&funcCall1, r1, sizeof(ZFSMFunctionCall)));
	EXPECT_EQ(0, memcmp(&funcCall2, r2, sizeof(ZFSMFunctionCall)));

	// ������ �Ѿ ��ûó��
	EXPECT_EQ(NULL, state.GetFunctionCall(9999));
	EXPECT_EQ(NULL, state.GetFunctionCall(-1000));


	// ���� ���� ������ �������Խ� ������ ��Ǹ���Ʈ���� �����غ���
	ZFSMFunctionCall funcCall3;
	funcCall3.id = 77;
	funcCall3.nArg[0] = 9;
	funcCall3.nArg[1] = 8;
	funcCall3.nArg[2] = 7;
	funcCall3.nArg[3] = 6;
	ZFSMFunctionCall funcCall4;
	funcCall4.id = 101;
	funcCall4.nArg[0] = 44;
	funcCall4.nArg[1] = 55;
	funcCall4.nArg[2] = 66;
	funcCall4.nArg[3] = 0;

	// �ֱ�
	vector<ZFSMFunctionCall> vecEnterFunctionCall;
	vecEnterFunctionCall.push_back(funcCall3);
	vecEnterFunctionCall.push_back(funcCall4);

	state.SetEnterFunctionCalls(vecEnterFunctionCall);

	// ������ ��
	EXPECT_EQ(2, state.GetEnterFunctionCallCount());
	const ZFSMFunctionCall* r3 = state.GetEnterFunctionCall(0);
	const ZFSMFunctionCall* r4 = state.GetEnterFunctionCall(1);

	EXPECT_EQ(0, memcmp(&funcCall3, r3, sizeof(ZFSMFunctionCall)));
	EXPECT_EQ(0, memcmp(&funcCall4, r4, sizeof(ZFSMFunctionCall)));

	// ������ �Ѿ ��ûó��
	EXPECT_EQ(NULL, state.GetEnterFunctionCall(9999));
	EXPECT_EQ(NULL, state.GetEnterFunctionCall(-1000));
}

TEST(ZFSMState, MakeDiceConditionHasRange)
{
	// "dice" ���ǹ��� xml���� �Ľ��� �ڿ� Ư���� ó���� ���ľ� ������ ����� �� �ְ� �ȴ�. 
	// ���⼭ �� 'ó��'�� �׽�Ʈ�Ѵ�. �ڼ��� ������ �ش� �Լ� ������ �ּ��� ����.

	// �켱 �׽�Ʈ�� state�� ����
	ZFSMState* pState = new ZFSMState;
	// ��Ǹ���Ʈ�� "dice" ����� �ִ� (�������� �����ϴ� �κ�)
	{
		vector<ZFSMFunctionCall> vecFuncCall;
		ZFSMFunctionCall fc;
		fc.Clear();
		fc.id = ZFSMFunctionServer::FSMFUNC_DICE;
		vecFuncCall.push_back(fc);
		pState->SetFunctionCalls(vecFuncCall);
	}
	// �������ǿ��� dice�� �ִ� (�������� ����ϴ� �κ�)
	{
		ZFSMTransition* pTrans;

		pTrans = new ZFSMTransition;
		{
			ZFSMCondition* pCond = new ZFSMCondition;
			pCond->Init(FSMCOND_HAS_TARGET);
			pTrans->AddCondition(pCond);
			pTrans->SetNextStateName("combat");
		}
		pState->AddTransition(pTrans);

		pTrans = new ZFSMTransition;
		{
			ZFSMCondition* pCond = new ZFSMCondition;
			pCond->Init(FSMCOND_DICE, 10);
			pTrans->AddCondition(pCond);
			pTrans->SetNextStateName("idle");
		}
		pState->AddTransition(pTrans);

		pTrans = new ZFSMTransition;
		{
			ZFSMCondition* pCond = new ZFSMCondition;
			pCond->Init(FSMCOND_DICE, 10);
			pTrans->AddCondition(pCond);
			pTrans->SetNextStateName("dance");
		}
		pState->AddTransition(pTrans);

		pTrans = new ZFSMTransition;
		{
			ZFSMCondition* pCond = new ZFSMCondition;
			pCond->Init(FSMCOND_DICE, 20);
			pTrans->AddCondition(pCond);
			pTrans->SetNextStateName("have_a_meal");
		}
		pState->AddTransition(pTrans);

		
	}
	// ���� state ���������� ���� Ǯ��� �Ʒ��� ����
	// 1. ���� �ִ°�? -> combat
	// 2. �ֻ������� ó�� 10�� ���� �� -> idle
	// 3. �ֻ������� �״��� 10�� ���� �� -> dance
	// 4. �ֻ������� �״��� 20�� ���� �� -> have_a_meal
	// �ֻ������� �̸� state�� �̹� �����ӿ� ���س��� ���������� ����Ѵ�.

	// ���� �ֻ��� ���� �������� ���ϱ� ���ؼ��� �̸� dice ���ǿ� ���� Ȯ��ġ�� ������ ���صξ�� �Ѵ�.

	// xml���� ���� dice ��ǿ� ���ڰ� �����Ǿ� ���� �ʴ�
	const ZFSMFunctionCall* pFuncCall =  pState->GetFunctionCall(0);
	ASSERT_EQ(ZFSMFunctionServer::FSMFUNC_DICE, pFuncCall->id);
	ASSERT_EQ(FSMMETHOD_ARG_NONE, pFuncCall->nArg[0]);
	// state���� �ڽ��� ���� dice������ ��� ã�Ƽ� �� ������ ������ ���� dice����� ���ڸ� �����ϵ��� �Ѵ�
	pState->MakeDiceFuncHasMaxValue();
	// ���� dice����� 1���� ���ڸ� ������ �Ǿ���
	EXPECT_EQ(10+10+20, pFuncCall->nArg[0]);

	// dice���ǵ��� Ȯ������ �ƴ϶� Ȯ�������� �������� ���ڸ� �����Ѵ�
	pState->MakeDiceConditionHasRange();
	// ���ڵ��� �������� ������ �ٲ������ Ȯ���� �� �ִ�
	ZFSMTransition* pDiceTrans;
	pDiceTrans = pState->GetTransition(1);	// idle transition
	EXPECT_EQ(0,  pDiceTrans->GetCondition(0)->GetArg(0));
	EXPECT_EQ(10, pDiceTrans->GetCondition(0)->GetArg(1));
	pDiceTrans = pState->GetTransition(2);	// dance transition
	EXPECT_EQ(10, pDiceTrans->GetCondition(0)->GetArg(0));
	EXPECT_EQ(20, pDiceTrans->GetCondition(0)->GetArg(1));
	pDiceTrans = pState->GetTransition(3);	// have_a_meal transition
	EXPECT_EQ(20, pDiceTrans->GetCondition(0)->GetArg(0));
	EXPECT_EQ(40, pDiceTrans->GetCondition(0)->GetArg(1));

	delete pState;
}


#endif