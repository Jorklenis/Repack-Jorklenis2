#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZFSMManager.h"
#include "ZFSM.h"

TEST(ZFSMManager, AddFsms_and_find)
{
	vector<ZFSM*> vec;
	ZFSM* pFSM;
	pFSM = new ZFSM;	pFSM->SetName("fsm1");	vec.push_back(pFSM);
	pFSM = new ZFSM;	pFSM->SetName("fsm2");	vec.push_back(pFSM);
	pFSM = new ZFSM;	pFSM->SetName("fsm3");	vec.push_back(pFSM);

	ZFSMManager mgr;
	mgr.AddFsm(&vec[0], (unsigned int)vec.size());
	EXPECT_EQ(3, mgr.GetFsmCount());

	// find
	pFSM = mgr.GetFsm("fsm1");
	EXPECT_STREQ("fsm1", pFSM->GetName());

	// �������� �ʴ� �� ã���� null
	EXPECT_TRUE(NULL == mgr.GetFsm("invalidname"));
}

#endif