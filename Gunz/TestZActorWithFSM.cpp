#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZGameMock.h"
#include "ZActorActionManager.h"
#include "ZActorWithFSM.h"

TEST(ZActorWithFSM, IsNpc)
{
	ZActorActionManager actionMgr;
	ZGameMock gameMock;
	ZActorWithFSM actor(&gameMock, &actionMgr);
	EXPECT_TRUE(actor.IsNPC());
}

TEST(ZActorWithFSM, FindTarget)
{
	ZActorActionManager actionMgr;
	ZGameMock gameMock;

	// ���Ͱ� �ϳ� �ִ�
	ZActorWithFSM actor(&gameMock, &actionMgr);
	actor.SetPosition(rvector(100,0,0));

	// ó���� Ÿ���� ���� ���� �ʴ�
	EXPECT_FALSE(actor.Cond_HasTarget());

	// ���忡 �ƹ��� ���� ������ Ÿ���� ã�� ���� ����
	actor.Func_FindTarget();
	EXPECT_FALSE(actor.Cond_HasTarget());

	// ���� ���忡 ĳ���Ͱ� �ϳ� �ִٰ� ����
	ZCharacterObject character(&gameMock);
	character.SetUID(MUID(0,1));
	character.SetPosition(rvector(0,0,0));
	gameMock.m_characterManager[MUID(0,1)] = &character;

	// ���� Ÿ���� ã�� �� �ִ�
	actor.Func_FindTarget();
	EXPECT_TRUE(actor.Cond_HasTarget());
	EXPECT_TRUE(MUID(0,1) == actor.GetTargetUID());

	// ���忡 ĳ���� �ϳ��� �� �ִ´�
	ZCharacterObject character2(&gameMock);
	character2.SetUID(MUID(0,2));
	character2.SetPosition(rvector(50,0,0));
	gameMock.m_characterManager[MUID(0,2)] = &character2;

	// �� ĳ���Ͱ� �� �����Ƿ� �� ĳ���Ͱ� ���õȴ�
	actor.Func_FindTarget();
	EXPECT_TRUE(actor.Cond_HasTarget());
	EXPECT_TRUE(MUID(0,2) == actor.GetTargetUID());
}

TEST(ZActorWithFSM, RotateToDirection)
{
	ZActorActionManager actionMgr;
	ZGameMock gameMock;

	float fFrameDelta = 0.01f;

	// ���Ͱ� �ϳ� �ִ�
	ZActorWithFSM actor(&gameMock, &actionMgr);
	actor.SetPosition(rvector(100,0,0));

	rvector vDir = rvector(1,0,0);
	actor.SetDirection(vDir);

	// ȸ���� �õ�����
	actor.RotateToDirection(rvector(-1,0,0), fFrameDelta);
	rvector vDir2 = actor.GetDirection();

	float fAngle1 = GetAngleOfVectors(vDir, vDir2);

	// �̹��� �������� 2�� ������ ���ư���
	actor.RotateToDirection(rvector(-1,0,0), fFrameDelta*2);
	rvector vDir3 = actor.GetDirection();
 
	float fAngle2 = GetAngleOfVectors(vDir2, vDir3);

	// �ѹ��� ȸ������ ������ �ð��� ����Ѵ�
	EXPECT_NEAR(fAngle2, fAngle1*2, 0.001f);
}


#endif