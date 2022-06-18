#include "stdafx.h"

#ifdef _TDD		// ��� ���� �׽�Ʈ ���� �ڵ�� _TDD�� ���ε��� �մϴ�
#include "GlobalSubtitutes.h"

typedef std::map<E_GLOBAL_INSTANCE, void*> MapGlobalSub;
static MapGlobalSub mapGlobalSub;


void ClearGlobalSub()
{
	// ��ü�� ��ü���� �޸� ������ ���⼭ ���� �ʽ��ϴ�. ������ ������ ���� �ؾ��մϴ�.

	mapGlobalSub.clear();
}


void* ZTddGetGlobalSub(E_GLOBAL_INSTANCE id)
{
	MapGlobalSub::iterator it = mapGlobalSub.find(id);
	if (it!=mapGlobalSub.end())
		return it->second;
	return NULL;
}

void ZTddSetGlobalSub(E_GLOBAL_INSTANCE id, void* pSubtitute)
{
	MapGlobalSub::iterator it = mapGlobalSub.find(id);
	if (it!=mapGlobalSub.end())
	{
		_ASSERT(0); // �̹� �߰��� ��ü�� ��ü�� �ֽ��ϴ�. �޸� ������ �Ͼ ���Դϴ�.
	}
	mapGlobalSub[id] = pSubtitute;
}

void ZTddRemoveGlobalSub(E_GLOBAL_INSTANCE id)
{
	mapGlobalSub[id] = NULL;
}

#endif
