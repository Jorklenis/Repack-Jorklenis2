#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZFSMStateEnteredTimeStamper.h"
#include "ZFSMState.h"


TEST(ZFSMStateEnteredTimeStamper, CheckCooltime)
{
	ZFSMStateEnteredTimeStamper stamper;

	DWORD dwCurrTime = 10000;

	// �ѹ��� �������� ���� ������ ��Ÿ�� üũ ��û�� ��� �ٷ� ����
	// (stamper�� "state1"�̶�� ������ ���� �ð��� ���� ���� ���� ���̴�)
	ZFSMState state1;
	state1.SetName("state1");
	state1.SetCooltime(3000);
	EXPECT_TRUE(stamper.CheckCooltime(&state1, dwCurrTime));
	stamper.SetEnteredTime(&state1, dwCurrTime);

	// �ð��� �귶��
	dwCurrTime += 2000;

	// �ٽ� ��Ÿ�� �˻縦 �غ��� ���� ��Ÿ���� �ȳ������Ƿ� �̹��� ������ ���̴�
	EXPECT_FALSE(stamper.CheckCooltime(&state1, dwCurrTime));

	// �ٽ� �ð��� �귶��
	dwCurrTime += 1500;

	// �ٽ� ��Ÿ�� �˻縦 �غ��� �̹��� ������ ���̴�
	EXPECT_TRUE(stamper.CheckCooltime(&state1, dwCurrTime));
	stamper.SetEnteredTime(&state1, dwCurrTime);

	// �� �ణ �ð��� �帣��
	dwCurrTime += 1000;
	
	// ��Ÿ�� �˻縦 �ٽ� �غ��� �Ʊ� ���Խð��� ���ŵǾ����Ƿ� �����Ѵ�
	EXPECT_FALSE(stamper.CheckCooltime(&state1, dwCurrTime));
}

TEST(ZFSMStateEnteredTimeStamper, GetSetEnteredTime)
{
	ZFSMStateEnteredTimeStamper stamper;

	DWORD dwCurrTime = 10000;

	ZFSMState state1;
	stamper.SetEnteredTime(&state1, dwCurrTime);
	EXPECT_EQ(dwCurrTime, stamper.GetEnteredTime(&state1));
}


#endif