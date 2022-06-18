#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "ZActorActionManager.h"
#include "ZActorAction.h"

TEST(ZActorActionManager, AddAction_GetAction)
{
	ZActorActionManager mgr;

	ZActorAction* pAction1 = new ZActorAction;
	pAction1->SetName("some_action");
	EXPECT_TRUE(mgr.AddAction(pAction1));
	EXPECT_EQ(1, mgr.GetCount());

	ZActorAction* pAction2 = new ZActorAction;
	pAction2->SetName("another_action");
	EXPECT_TRUE(mgr.AddAction(pAction2));
	EXPECT_EQ(2, mgr.GetCount());

	ZActorAction* pAction3 = new ZActorAction;
	pAction3->SetName("another_action");		// ���� �̸��� �׼��� �� �߰��ϸ� ����
	EXPECT_FALSE(mgr.AddAction(pAction2));
	EXPECT_EQ(2, mgr.GetCount());				// ���������Ƿ� ������ �״���̴�
	delete pAction3;

	// ����ִ°� ã�ƺ���
	EXPECT_TRUE(NULL != mgr.GetAction("some_action"));
	EXPECT_TRUE(NULL == mgr.GetAction("no_exist_action"));
}

TEST(ZActorActionManager, ReadXmlFromStr)
{
	ZActorActionManager mgr;

	//// �������̰� �ܼ��� xml�� �ѹ� �о��
	const char szXml[] =
		"\
		<XML>\
			<ACTION name=\"idle\" animation=\"idlemotion\" />\
			<ACTION name=\"run\" animation=\"runmotion\" movinganimation=\"false\"/>\
			<ACTION name=\"dash\" animation=\"dashmotion\" movinganimation=\"true\" />\
		</XML>\
		";
	EXPECT_TRUE(mgr.ParseXmlFromStr(szXml));
	EXPECT_EQ(3, mgr.GetCount());
	EXPECT_STREQ("idlemotion", mgr.GetAction("idle")->GetAnimationName());
	EXPECT_STREQ("runmotion", mgr.GetAction("run")->GetAnimationName());

	EXPECT_FALSE(mgr.GetAction("idle")->IsMovingAnimation());	// ���ǰ� ������ false
	EXPECT_FALSE(mgr.GetAction("run")->IsMovingAnimation());
	EXPECT_TRUE(mgr.GetAction("dash")->IsMovingAnimation());

	//// �̹� ������ ������ �ִµ� �ٸ� xml�� �Ľ��ϸ� ���� ������ ��������
	const char szXmlAnother[] =
		"\
		<XML>\
			<ACTION name=\"someAction\" animation=\"foo\" />\
		</XML>\
		";
	EXPECT_TRUE(mgr.ParseXmlFromStr(szXmlAnother));
	EXPECT_EQ(1, mgr.GetCount());

	//// �׼��� name attribute�� �� �־�� �Ѵ�
	const char szXmlNoNameNode[] =
		"\
		<XML>\
			<ACTION name=\"idle\" animation=\"idle\" />\
			<ACTION name=\"\" animation=\"run\" />\
		</XML>\
		";
	EXPECT_FALSE(mgr.ParseXmlFromStr(szXmlNoNameNode));
	EXPECT_EQ(0, mgr.GetCount());	// �߰��� �Ľ� ���а� �Ͼ�� �տ��� �о��� ������� ���� �ı�ȴ�

	/// �׼ǿ� MELEESHOT�� ���Ե� ���
	const char szXmlWithMeleeShot[] =
		"\
		<XML>\
			<ACTION name=\"knifeman_attack\" animation=\"melee_attack\">\
				<MELEESHOT delay=\"2000\" damage=\"10\" range=\"100\" angle=\"30\" pierce=\"90\" sound=\"blade\" knockback=\"333\" />\
			</ACTION>\
		</XML>\
		";
	EXPECT_TRUE(mgr.ParseXmlFromStr(szXmlWithMeleeShot));
	ZActorAction* pAction = mgr.GetAction("knifeman_attack");
	ASSERT_TRUE(NULL != pAction);
	ASSERT_TRUE(NULL != pAction->GetMeleeShot());
	EXPECT_EQ(2.f, pAction->GetMeleeShot()->GetDelay());
	EXPECT_EQ(10.f, pAction->GetMeleeShot()->GetDamage());
	EXPECT_EQ(100.f, pAction->GetMeleeShot()->GetRange());
	EXPECT_EQ(30.f, pAction->GetMeleeShot()->GetAngle());
	EXPECT_EQ(0.9f, pAction->GetMeleeShot()->GetPierce());
	EXPECT_STREQ("blade", pAction->GetMeleeShot()->GetSound());
	EXPECT_EQ(333.f, pAction->GetMeleeShot()->GetKnockbackForce());

	/// �׼ǿ� RANGESHOT ���Ե� ���
	const char szXmlWithRangeShot[] =
		"\
		<XML>\
			<ACTION name=\"rifleman_fire\" animation=\"rifle_fire\">\
				<RANGESHOT delay=\"400\" damage=\"20\" pierce=\"50\" sound=\"hitsound\" mesh=\"bullet1\" speed=\"444\"\
							collradius=\"111\" dirmod=\"1.5 2.5 3.5\" posparts=\"head\"/>\
			</ACTION>\
		</XML>\
		";
	EXPECT_TRUE(mgr.ParseXmlFromStr(szXmlWithRangeShot));
	pAction = mgr.GetAction("rifleman_fire");
	ASSERT_TRUE(NULL != pAction);
	ASSERT_TRUE(NULL != pAction->GetRangeShot(0));
	EXPECT_EQ(0.4f, pAction->GetRangeShot(0)->GetDelay());
	EXPECT_EQ(20.f, pAction->GetRangeShot(0)->GetDamage());
	EXPECT_EQ(0.5f, pAction->GetRangeShot(0)->GetPierce());
	EXPECT_STREQ("hitsound", pAction->GetRangeShot(0)->GetSound());
	EXPECT_STREQ("bullet1", pAction->GetRangeShot(0)->GetMeshName());
	EXPECT_EQ(444.f, pAction->GetRangeShot(0)->GetSpeed());
	EXPECT_EQ(111.f, pAction->GetRangeShot(0)->GetCollRadius());
	EXPECT_EQ(rvector(1.5, 2.5, 3.5), pAction->GetRangeShot(0)->GetDirectionMod());
	EXPECT_EQ(eq_parts_pos_info_Head, pAction->GetRangeShot(0)->GetPosPartsType());

	/// �׼ǿ� RANGESHOT�� ������ ���Ե� ���
	const char szXmlWithRangeShot2[] =
		"\
		<XML>\
			<ACTION name=\"rifleman_doublefire\" animation=\"rifle_fire\">\
				<RANGESHOT delay=\"400\" damage=\"20\" pierce=\"50\" sound=\"hitsound\" mesh=\"bullet1\" speed=\"444\" collradius=\"111\" />\
				<RANGESHOT delay=\"500\" damage=\"20\" pierce=\"50\" sound=\"hitsound\" mesh=\"bullet1\" speed=\"444\" collradius=\"111\" />\
			</ACTION>\
		</XML>\
		";
	EXPECT_TRUE(mgr.ParseXmlFromStr(szXmlWithRangeShot2));
	pAction = mgr.GetAction("rifleman_doublefire");
	ASSERT_TRUE(NULL != pAction);
	ASSERT_EQ(2, pAction->GetNumRangeShot());
	ASSERT_TRUE(NULL != pAction->GetRangeShot(0));
	ASSERT_EQ(0.4f, pAction->GetRangeShot(0)->GetDelay());
	ASSERT_EQ(0.5f, pAction->GetRangeShot(1)->GetDelay());
}


#endif