#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include <gtest/gtest.h>
#include "MActorDef.h"

TEST(MActorDefManager, ParseXml)
{
	MActorDefManager mgr;

	const char szXml[] =
		"\
		<XML>\
			<ACTOR name=\"knifeman\"\
				model=\"knifeman_red\"\
				ai.fsm=\"knifeman_ai\"\
				max_hp=\"30\"\
				max_ap=\"50\"\
				collision.radius=\"100\" \
				collision.height=\"110\"\
				speed=\"33\"\
				rotspeed=\"5.5\"\
				groggyRecoverPerSec=\"1.5\"\
				neverblasted=\"true\"\
				/>\
		</XML>\
		";

	EXPECT_TRUE(mgr.ParseXmlFromStr(szXml));
	EXPECT_EQ(1, mgr.GetCount());
	MActorDef* pDef = mgr.GetDef("knifeman");
	EXPECT_TRUE(NULL != pDef);
	EXPECT_STREQ("knifeman_ai", pDef->GetFsmName());
	EXPECT_STREQ("knifeman_red", pDef->GetModelName());
	EXPECT_EQ(30, pDef->GetMaxHp());
	EXPECT_EQ(50, pDef->GetMaxAp());
	EXPECT_EQ(100, pDef->GetCollisionRadius());
	EXPECT_EQ(110, pDef->GetCollisionHeight());
	EXPECT_EQ(33, pDef->GetSpeed());
	EXPECT_EQ(5.5f, pDef->GetRotSpeed());
	EXPECT_EQ(1.5f, pDef->GetGroggyRecoverySpeed());
	EXPECT_TRUE(pDef->IsNeverBlasted());
}

TEST(MActorDefManager, AddActorDef)
{
	MActorDefManager mgr;
	MActorDef *pDef1, *pDef2, *pDef3;
	
	pDef1 = new MActorDef;
	pDef1->SetName("an_actor");
	EXPECT_TRUE(mgr.AddActorDef(pDef1));
	EXPECT_EQ(1, mgr.GetCount());

	pDef2 = new MActorDef;
	pDef2->SetName("another_actor");
	EXPECT_TRUE(mgr.AddActorDef(pDef2));
	EXPECT_EQ(2, mgr.GetCount());

	pDef3 = new MActorDef;
	pDef3->SetName("another_actor");		// ���� �̸��� ���Ǹ� �� �߰��Ϸ��Ѵ�
	EXPECT_FALSE(mgr.AddActorDef(pDef2));	// ����..
	EXPECT_EQ(2, mgr.GetCount());			// ������ �������� ����
	delete pDef3;	// �߰��ȵ����� ���⼭ ��������� �Ѵ�
}



#endif