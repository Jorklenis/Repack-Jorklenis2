#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZFSMFunctionServer.h"

TEST(ZFSMFunctionServer, Dice)
{
	ZFSMFunctionServer funcSvr;

	// dice����� �������� �����Ѵ�
	ASSERT_TRUE(funcSvr.ExecuteFunction(0, ZFSMFunctionServer::FSMFUNC_DICE, 0, 100));
	EXPECT_TRUE(0 <= funcSvr.GetDice() && funcSvr.GetDice() < 100);
}

#endif