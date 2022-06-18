#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZFSMParser.h"
#include "ZFSMCondition.h"
#include "ZFSMTransition.h"
#include "ZFSMFunctionServer.h"
#include "ZFSM.h"
#include "ZFSMState.h"
#include "ZActorAction.h"
#include "ZActorActionManager.h"
#include "ZActorActionManagerMock.h"


TEST(ZFSMParser, ParseMethodStatement)
{
	ZFSMParser parser;
	ZFSMMethodCall mc;
	
	// �޼ҵ��̸������� �� ���� �Ľ�
	parser.ParseMethodStatement(&mc, "findTarget");
	EXPECT_STREQ("findTarget", mc.strMethodName.c_str());
	EXPECT_EQ(FSMMETHOD_ARG_NONE, mc.nArg[0]);
	
	// �޼ҵ��̸�:���� 1���� ������ �Ľ�
	parser.ParseMethodStatement(&mc, "hpLess:10");
	EXPECT_STREQ("hpLess", mc.strMethodName.c_str());
	EXPECT_EQ(10, mc.nArg[0]);
	EXPECT_EQ(FSMMETHOD_ARG_NONE, mc.nArg[1]);

	// ���ڰ� ���� �޼ҵ� ȣ�� ����
	parser.ParseMethodStatement(&mc, "distTarget:100;250");
	EXPECT_STREQ("distTarget", mc.strMethodName.c_str());
	EXPECT_EQ(100, mc.nArg[0]);
	EXPECT_EQ(250, mc.nArg[1]);
	EXPECT_EQ(FSMMETHOD_ARG_NONE, mc.nArg[2]);

	// ���̻��̿� ���鹮�ڸ� �־��� ���
	parser.ParseMethodStatement(&mc, " \t foo: \t333; 555  \t ");
	EXPECT_STREQ("foo", mc.strMethodName.c_str());
	EXPECT_EQ(333, mc.nArg[0]);
	EXPECT_EQ(555, mc.nArg[1]);
	EXPECT_EQ(FSMMETHOD_ARG_NONE, mc.nArg[2]);
}

TEST(ZFSMParser, DivideMultipleMethodStatement)
{
	// ','�� ���� �޼ҵ� ȣ���� ������ ������ �Ľ�

	ZFSMParser parser;
	vector<string> v;

	// �ΰ��� ȣ���� ��� ����
	parser.DevideMultipleMethodStatement(v, "dice:5,distTarget:7;9");
	EXPECT_EQ(2, (int)v.size());

	EXPECT_STREQ("dice:5",			v[0].c_str());
	EXPECT_STREQ("distTarget:7;9",	v[1].c_str());

	// �Ѱ��� ȣ���� ����־ �� �д´�
	parser.DevideMultipleMethodStatement(v, "hpLess:15");
	EXPECT_EQ(1, (int)v.size());

	EXPECT_STREQ("hpLess:15", v[0].c_str());
}

// ��� ���๮ 1���� �Ľ��Ѵ�
TEST(ZFSMParser, ParseSingleFunctionStatement)
{
	ZFSMParser parser;
	ZFSMFunctionCall funcCall;

	// ����
	EXPECT_FALSE(parser.ParseFunction(NULL, "dice"));			// condition ��ü ������
	EXPECT_FALSE(parser.ParseFunction(&funcCall, "xxxxx"));		// �˼����� ���ڿ�

	// ���ڿ��� ������ �ƴ�
	EXPECT_TRUE(parser.ParseFunction(&funcCall, ""));
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_DONOTHING, funcCall.id);

	EXPECT_TRUE(parser.ParseFunction(&funcCall, "dice"));
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_DICE, funcCall.id);

	EXPECT_TRUE(parser.ParseFunction(&funcCall, "findTarget"));
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_FIND_TARGET, funcCall.id);

	EXPECT_TRUE(parser.ParseFunction(&funcCall, "setTargetLastAttacker"));
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_SET_TARGET_LAST_ATTACKER, funcCall.id);

	EXPECT_TRUE(parser.ParseFunction(&funcCall, "rotateToTarget"));
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_ROTATE_TO_TARGET, funcCall.id);

	EXPECT_TRUE(parser.ParseFunction(&funcCall, "faceToTarget"));
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_FACE_TO_TARGET, funcCall.id);

	EXPECT_TRUE(parser.ParseFunction(&funcCall, "reduceGroggy:10"));
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_REDUCE_GROGGY, funcCall.id);
	EXPECT_EQ(10, funcCall.nArg[0]);

	EXPECT_TRUE(parser.ParseFunction(&funcCall, "buildWaypointsToTarget"));
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_BUILD_WAYPOINTS_TO_TARGET, funcCall.id);

	EXPECT_TRUE(parser.ParseFunction(&funcCall, "runWaypoints"));
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_RUN_WAYPOINTS, funcCall.id);
}

// �������� �̷���� ��� ���๮�� �Ľ��Ѵ�
TEST(ZFSMParser, ParseFunctionsStatement)
{
	ZFSMParser parser;
	vector<ZFSMFunctionCall> v;

	// �����ϴ� ���
	EXPECT_FALSE(parser.ParseFunctionsStatement(v, "dice,xxxx,findTarget"));		// �˼����� ���ڿ��� ���Ե�
	ASSERT_TRUE(v.empty());		// �����ϸ� �� �迭�� ��������

	// ����
	EXPECT_TRUE(parser.ParseFunctionsStatement(v, "dice,reduceGroggy:33,rotateToTarget"));
	ASSERT_EQ(3, (int)v.size());
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_DICE, v[0].id);
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_REDUCE_GROGGY, v[1].id);
	EXPECT_EQ(33, v[1].nArg[0]);
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_ROTATE_TO_TARGET, v[2].id);
	v.clear();

	// ��� ���๮�� 1��¥������ �� �ȴ�
	EXPECT_TRUE(parser.ParseFunctionsStatement(v, "dice"));
	EXPECT_EQ(1, (int)v.size());
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_DICE, v[0].id);
	v.clear();

	// ��� ���๮�� ����־ ������ �ƴϴ�
	EXPECT_TRUE(parser.ParseFunctionsStatement(v, ""));
	EXPECT_EQ(1, (int)v.size());
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_DONOTHING, v[0].id);
}

TEST(ZFSMParser, ParseConditionStatement)
{
	ZFSMParser parser;
	ZFSMCondition cond;

	// �����ϴ� ���
	EXPECT_FALSE(parser.ParseCondition(NULL, "HpLess:10"));			// condition ��ü ������
	EXPECT_FALSE(parser.ParseCondition(&cond, "zmxncbzbnz"));		// �˼����� ���ڿ�
	EXPECT_FALSE(parser.ParseCondition(&cond, ""));					// ���ڿ�

	// default
	EXPECT_TRUE(parser.ParseCondition(&cond, "Default"));
	EXPECT_EQ(FSMCOND_DEFAULT, cond.GetConditionId());

	// dice
	EXPECT_TRUE(parser.ParseCondition(&cond, "Dice:7"));
	EXPECT_EQ(FSMCOND_DICE, cond.GetConditionId());
	EXPECT_EQ(7, cond.GetArg(0));

	// hp equal
	EXPECT_TRUE(parser.ParseCondition(&cond, "HpEqual:11"));
	EXPECT_EQ(FSMCOND_HP_EQUAL, cond.GetConditionId());
	EXPECT_EQ(11, cond.GetArg(0));

	// hp less than
	EXPECT_TRUE(parser.ParseCondition(&cond, "HpLess:10"));
	EXPECT_EQ(FSMCOND_HP_LESS, cond.GetConditionId());
	EXPECT_EQ(10, cond.GetArg(0));

	// hp greater than
	EXPECT_TRUE(parser.ParseCondition(&cond, "HpGreater:50"));
	EXPECT_EQ(FSMCOND_HP_GREATER, cond.GetConditionId());
	EXPECT_EQ(50, cond.GetArg(0));

	// groggy greater than
	EXPECT_TRUE(parser.ParseCondition(&cond, "groggyGreater:4"));
	EXPECT_EQ(FSMCOND_GROGGY_GREATER, cond.GetConditionId());
	EXPECT_EQ(4, cond.GetArg(0));

	// velocity z less than
	EXPECT_TRUE(parser.ParseCondition(&cond, "velocityZLess:-10"));
	EXPECT_EQ(FSMCOND_VELOCITY_Z_LESS, cond.GetConditionId());
	EXPECT_EQ(-10, cond.GetArg(0));
	
	// velocity magnitude less than
	EXPECT_TRUE(parser.ParseCondition(&cond, "velocityMagnitudeLess:20"));
	EXPECT_EQ(FSMCOND_VELOCITY_MAGNITUDE_LESS, cond.GetConditionId());
	EXPECT_EQ(20, cond.GetArg(0));

	// is end of action
	EXPECT_TRUE(parser.ParseCondition(&cond, "endAction"));
	EXPECT_EQ(FSMCOND_END_ACTION, cond.GetConditionId());

	// is landing
	EXPECT_TRUE(parser.ParseCondition(&cond, "isLanding"));
	EXPECT_EQ(FSMCOND_IS_LANDING, cond.GetConditionId());

	// has target
	EXPECT_TRUE(parser.ParseCondition(&cond, "hasTarget"));
	EXPECT_EQ(FSMCOND_HAS_TARGET, cond.GetConditionId());

	// has no target
	EXPECT_TRUE(parser.ParseCondition(&cond, "hasNoTarget"));
	EXPECT_EQ(FSMCOND_HAS_NO_TARGET, cond.GetConditionId());

	// distance to target
	EXPECT_TRUE(parser.ParseCondition(&cond, "distTarget:20;99"));
	EXPECT_EQ(FSMCOND_DIST_TARGET_IN, cond.GetConditionId());
	EXPECT_EQ(20, cond.GetArg(0));
	EXPECT_EQ(99, cond.GetArg(1));

	// look at target in degree
	EXPECT_TRUE(parser.ParseCondition(&cond, "lookAtTarget:20"));
	EXPECT_EQ(FSMCOND_LOOK_AT_TARGET, cond.GetConditionId());
	EXPECT_EQ(20, cond.GetArg(0));

	// is empty space
	EXPECT_TRUE(parser.ParseCondition(&cond, "isEmptySpace:30;100"));
	EXPECT_EQ(FSMCOND_IS_EMPTY_SPACE, cond.GetConditionId());
	EXPECT_EQ(30, cond.GetArg(0));
	EXPECT_EQ(100, cond.GetArg(1));

	// time elapsed since entered into current state
	EXPECT_TRUE(parser.ParseCondition(&cond, "TimeElapsedSinceEntered:1000"));
	EXPECT_EQ(FSMCOND_TIME_ELAPSED_SINCE_ENTERED, cond.GetConditionId());
	EXPECT_EQ(1000, cond.GetArg(0));

	// is end of lightning damage
	EXPECT_TRUE(parser.ParseCondition(&cond, "EndLightningDamage"));
	EXPECT_EQ(FSMCOND_END_LIGHTNINGDAMAGE, cond.GetConditionId());
}

TEST(ZFSMParser, ParseTransition)
{
	ZFSMParser parser;

	ZFSMTransition* pTrans = parser.ParseTransition("hasTarget,distTarget:7;15,HpLess:10", "rotateToTarget");
	EXPECT_TRUE(NULL != pTrans);
	EXPECT_EQ(3, pTrans->CountCondition());
	EXPECT_EQ(FSMCOND_HAS_TARGET,		pTrans->GetCondition(0)->GetConditionId());
	EXPECT_EQ(FSMCOND_DIST_TARGET_IN,	pTrans->GetCondition(1)->GetConditionId());
	EXPECT_EQ(7,						pTrans->GetCondition(1)->GetArg(0));
	EXPECT_EQ(15,						pTrans->GetCondition(1)->GetArg(1));
	EXPECT_EQ(FSMCOND_HP_LESS,			pTrans->GetCondition(2)->GetConditionId());
	EXPECT_EQ(10,						pTrans->GetCondition(2)->GetArg(0));
	EXPECT_STREQ("rotateToTarget", pTrans->GetNextStateName());
	delete pTrans;

	// �����ϴ� ���
	EXPECT_TRUE(NULL == parser.ParseTransition("hasTarget,xxxx", "idle"));	// �˼����� ������̸�
	EXPECT_TRUE(NULL == parser.ParseTransition("", "idle"));				// ������̸� ����
	EXPECT_TRUE(NULL == parser.ParseTransition("hasTarget", ""));			// next state �̸� ����
}

// �Ľ� �׽�Ʈ�� ���� �ߺ� fsm xml ����
const char g_szFsmXml[] = 
"\
<XML>\
	<FSM name=\"monster1\" entrystate=\"findTarget\">\
	\
		<STATE name=\"idle\" cooltime=\"0\" action=\"idle\" func=\"findTarget\">\
			<TRANS cond=\"default\" next=\"findTarget\"/>\
		</STATE>\
	\
		<STATE name=\"findTarget\" cooltime=\"0\" action=\"idle\" func=\"findTarget\">\
			<TRANS cond=\"hpLess:0\" next=\"die\"/>\
			<TRANS cond=\"hasTarget\" next=\"rotateToTarget\"/>\
		</STATE>\
	\
		<STATE name=\"rotateToTarget\" cooltime=\"0\" action=\"walk\" func=\"rotateToTarget\">\
			<TRANS cond=\"hpLess:0\" next=\"die\"/>\
			<TRANS cond=\"hasNoTarget\" next=\"findTarget\"/>\
			<TRANS cond=\"lookAtTarget:15\" next=\"combat\"/>\
		</STATE>\
	\
		<STATE name=\"combat\" cooltime=\"0\" enterfunc=\"buildWaypointsToTarget\" func=\"dice\">\
			<TRANS cond=\"hpLess:0\" next=\"die\"/>\
			<TRANS cond=\"hasNoTarget\" next=\"findTarget\"/>\
			<TRANS cond=\"dice:20,distTarget:1;3\" next=\"slashTwice\"/>\
			<TRANS cond=\"dice:20,distTarget:10;50\" next=\"sweepFire\"/>\
			<TRANS cond=\"default\" next=\"findTarget\"/>	<!-- default�� ���� ���ǿ� �ϳ��� ���� ���� ��� -->\
		</STATE>\
	\
		<STATE name=\"slashTwice\" cooltime=\"3000\" action=\"slashTwice\">\
			<TRANS cond=\"hpLess:0\" next=\"die\"/>\
			<TRANS cond=\"endAction\" next=\"combat\"/>\
		</STATE>\
	\
		<STATE name=\"sweepFire\" cooltime=\"3000\" action=\"sweepFire\">\
			<TRANS cond=\"hpLess:0\" next=\"die\"/>\
			<TRANS cond=\"endAction\" next=\"combat\"/>\
		</STATE>\
	\
		<STATE name=\"die\" cooltime=\"0\" action=\"die\">\
		</STATE>\
	\
		<STATE name=\"afterblasted\" cooltime=\"0\" exitfunc=\"dice\">\
			<TRANS cond=\"default\" next=\"findTarget\"/>\
		</STATE>\
	</FSM>\
</XML>\
";

TEST(ZFSMParser, ReadXmlFromStr)
{
	vector<ZFSM*> v;
	ZFSMParser parser;
	ZActorActionManagerMock* pActionMgr = new ZActorActionManagerMock;
	parser.m_pActionMgr = pActionMgr;

	// �����ϴ� ���
	EXPECT_FALSE(parser.ReadXmlFromStr(v, ""));
	EXPECT_TRUE(v.empty());
	EXPECT_FALSE(parser.ReadXmlFromStr(v, NULL));
	EXPECT_TRUE(v.empty());

	// ����
	ASSERT_TRUE(parser.ReadXmlFromStr(v, g_szFsmXml));
	EXPECT_EQ(1, (int)v.size());
	ZFSM* pFsm = v[0];
	EXPECT_STREQ("monster1", pFsm->GetName());
	EXPECT_STREQ("findTarget", pFsm->GetEntryStateName());
	ZFSMState* pState = pFsm->GetState("findTarget");
	EXPECT_TRUE(NULL != pState);
	EXPECT_TRUE(NULL != pState->GetAction());
	EXPECT_STREQ("idle", pState->GetAction()->GetName());
	
	// func�� �� ��������? 
	pState = pFsm->GetState("combat");
	EXPECT_TRUE(NULL != pState);
	EXPECT_EQ(1, pState->GetFunctionCallCount());
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_DICE, pState->GetFunctionCall(0)->id);

	// enterfunc�� �� ��������?
	pState = pFsm->GetState("combat");
	EXPECT_TRUE(NULL != pState);
	EXPECT_EQ(1, pState->GetEnterFunctionCallCount());
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_BUILD_WAYPOINTS_TO_TARGET, pState->GetEnterFunctionCall(0)->id);

	// exitfunc�� �� ��������?
	pState = pFsm->GetState("afterblasted");
	EXPECT_TRUE(NULL != pState);
	EXPECT_EQ(1, pState->GetExitFunctionCallCount());
	EXPECT_EQ(ZFSMFunctionServer::FSMFUNC_DICE, pState->GetExitFunctionCall(0)->id);

	// ReadXmlFromStr()���� �����ϸ� ��� transition�� nextstate�� �����Ͱ� ���õǾ� �־����
	ZFSMState* pNextState = pState->GetTransition(0)->GetNextState();
	EXPECT_TRUE(NULL != pNextState);
	EXPECT_STREQ("findTarget", pNextState->GetName());
	
	delete v[0];
	delete pActionMgr;
}


#endif