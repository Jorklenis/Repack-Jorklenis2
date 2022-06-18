#pragma once

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�

#include <map>

// �׽�Ʈ ���� ���� �̱��ϰ� ���������� �׽�Ʈ�� ��ü�� ��ü�ϱ� ������ ���⿡ ����ϰ�,
// �׽�Ʈ �Ŀ��� ��ü�� ��ü���� �ϰ������� ������ �� �ֵ��� �ۼ��մϴ�.

enum E_GLOBAL_INSTANCE
{
	GI_NpcMeshMgr,
	GI_EffectManager,
	GI_MatchItemDescMgr,
};

void ClearGlobalSub();

void* ZTddGetGlobalSub(E_GLOBAL_INSTANCE id);
void ZTddSetGlobalSub(E_GLOBAL_INSTANCE id, void* pSubtitute);
void ZTddRemoveGlobalSub(E_GLOBAL_INSTANCE id);


#endif