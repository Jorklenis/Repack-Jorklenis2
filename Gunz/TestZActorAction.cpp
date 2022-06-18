#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZActorAction.h"

TEST(ZActorAction, HasName)
{
	ZActorAction action;
	action.SetName("idle");
	EXPECT_STREQ("idle", action.GetName());
}

TEST(ZActorAction, HasAnimation)
{
	ZActorAction action;
	action.SetAnimationName("dance");
	EXPECT_STREQ("dance", action.GetAnimationName());
}

TEST(ZActorAction, IsMovingAnimation)
{
	ZActorAction action;
	action.SetMovingAnimation(true);
	EXPECT_TRUE(action.IsMovingAnimation());
	action.SetMovingAnimation(false);
	EXPECT_FALSE(action.IsMovingAnimation());
}

TEST(ZActorAction, CanHaveMeleeShot)
{
	// �׼��� �������� �Ӽ��� ������ ���� ���� �ִ�
	ZActorAction action;
	action.SetName("goblin_punch");
	// ������ ���� ���� �׳� ��������
	EXPECT_EQ(NULL, action.GetMeleeShot());

	ZActorActionMeleeShot* pMeleeShot = new ZActorActionMeleeShot;
	pMeleeShot->SetDelay(1000);
	pMeleeShot->SetDamage(8);
	pMeleeShot->SetAngle(11);
	pMeleeShot->SetRange(90);
	pMeleeShot->SetSound("blade");
	action.SetMeleeShot(pMeleeShot);
	ASSERT_TRUE(NULL != action.GetMeleeShot());
	EXPECT_EQ(1000, action.GetMeleeShot()->GetDelay());
	EXPECT_EQ(8, action.GetMeleeShot()->GetDamage());
	EXPECT_EQ(11, action.GetMeleeShot()->GetAngle());
	EXPECT_EQ(90, action.GetMeleeShot()->GetRange());
	EXPECT_STREQ("blade", action.GetMeleeShot()->GetSound());
}

TEST(ZActorAction, CanHaveRangeShot)
{
	// �׼��� ���Ÿ����� �Ӽ��� ������ ���� ���� �ִ�
	ZActorAction action;
	action.SetName("goblin_lasershot");
	// ������ ���� ��� Ȯ��
	EXPECT_EQ(0, action.GetNumRangeShot());

	ZActorActionRangeShot* pRangeShot = new ZActorActionRangeShot;
	pRangeShot->SetDelay(1000);
	pRangeShot->SetDamage(8);
	pRangeShot->SetSound("hit");
	pRangeShot->SetMeshName("bullet");
	pRangeShot->SetDirectionMod(rvector(1,2,3));
	pRangeShot->SetPosPartsType(eq_parts_pos_info_Head);
	action.AddRangeShot(pRangeShot);
	ASSERT_TRUE(NULL != action.GetRangeShot(0));
	EXPECT_EQ(1000, action.GetRangeShot(0)->GetDelay());
	EXPECT_EQ(8, action.GetRangeShot(0)->GetDamage());
	EXPECT_STREQ("hit", action.GetRangeShot(0)->GetSound());
	EXPECT_STREQ("bullet", action.GetRangeShot(0)->GetMeshName());
	EXPECT_EQ(rvector(1,2,3), action.GetRangeShot(0)->GetDirectionMod());
	EXPECT_EQ(eq_parts_pos_info_Head, action.GetRangeShot(0)->GetPosPartsType());
}


#endif