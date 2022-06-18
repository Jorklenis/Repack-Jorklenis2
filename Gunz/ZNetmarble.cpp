#include "stdafx.h"

#include <windows.h>
#include <crtdbg.h>
#include "ZNetmarble.h"
#include "ZLocale.h"
#include "MDebug.h"
#include "MLex.h"


//// ZNetmarbleAuthInfo ////////////////

ZNetmarbleAuthInfo::ZNetmarbleAuthInfo() : ZBaseAuthInfo()
{
	m_AuthCookie[0] = NULL;
	m_DataCookie[0] = NULL;
	strcpy( m_SpareParam, "12" );
}

ZNetmarbleAuthInfo::~ZNetmarbleAuthInfo()
{
}

////////////////ZNetmarbleAuthInfo ////

#ifdef LOCALE_KOREA

/* [ Ŭ���̾�Ʈ �۾� ���� ]
---------------------------------------------------------------------------------------------

1. Ŭ���̾�Ʈ������ Ŭ���̾�Ʈ ��ȣȭ ����� NMCrypt�� ����ؾ��Ѵ�.

  ����) ������ ��ȣȭ ����� CPSSOLib ���̺귯���� DLL�� �ݵ�� ���������� ����ؾ��Ѵ�.
        �����!! Ŭ���̾�Ʈ�� �ڵ�� DLL�� ���Խ�Ű�� �ȵ�.
        (Ŭ���̾�Ʈ�� �ڵ忡 ���Եǰ� �Ǹ� disassemble������ �ڵ� ������ ������)

        Ŭ���̾�Ʈ���� ID�� �˰��� �ϴ� ���� �ϴ��� 
        �ݵ�� �������� ��ȣȭ�Ͽ� Ŭ���̾�Ʈ�� �˷��ֵ��� �ؾ���

        ���ȿ� ���õ� ���� �߿��� ������.


2. ������ ����ϴ� �Ʒ��� �� �Լ��� �� �ڵ�� ��ü�Ѵ�.
  (��, ���ϵǴ� ��Ű�� ����� ����� ��� ������ ���۸� ����� �����ְ� ��ƾ� ��.)

3. �м��� ������ �̿��Ͽ� ������ �����Ͽ�

   g_CpCookie �� ������ ������ ������ ��ģ��.

   Ŭ���̾�Ʈ������ g_CpCookie ���� ��ȣȭ�Ǿ� �ֱ� ������ � ���� ����ִ����� �� �� ����.

   g_AuthCookie, g_DataCookie�� �ݸ��� ���� ���� ��Ű�̱� ������ CP��ü�� ������ ����(���� �ѱ��� ���� ���� �ִ�).
   (��, ī�����̼��� ���� Ư�� ������ 3���� ��Ű ��� �ʿ���) 
*/

static char* _StrTok(const char* str, const char sep)
{
	// strtok()�� ���� ����� �Լ������� separator�� 1���� �ް�
	// ���ڰ� ����ִ� ��쵵 ���ڷ� ������

	static const int TOK_BUFSIZE = 1024*40;

	static char* pnow = NULL;
	static char buf[TOK_BUFSIZE];
	static char token[TOK_BUFSIZE];

	if(str) {
		size_t slen = strlen(str);
		//_ASSERT(slen < TOK_BUFSIZE);		// ASSERT
		strcpy(buf, str);
		pnow = buf;
	}

	if(!pnow || *pnow == 0)
		return NULL;

	int tlen = 0;
	char* porg = pnow;
	while(*pnow != 0)
	{
		if(*pnow == sep) {
			++pnow;
			break;
		}

		++tlen;
		++pnow;
	}

	if(tlen > 0) {
		strncpy(token, porg, tlen);
		token[tlen] = 0;
	}
	else {
		token[0] = 0;
	}

	return token;
}

static void TrimStr(const char* szSrcStr, char* outStr)
{
	char szTemp[256] = "";

	// ���� ��������
	int nSrcStrLen = (int)strlen(szSrcStr);
	for (int i = 0; i < nSrcStrLen; i++)
	{
		if (!isspace(szSrcStr[i]))
		{
			strcpy(szTemp, &szSrcStr[i]);
			break;
		}
	}
	// ������ ��������
	int nLen = (int)strlen(szTemp);
	for (int i = nLen-1; i >= 0; i--)
	{
		if (isspace(szTemp[i]))
		{
			szTemp[i] = '\0';
		}
		else
		{
			break;
		}
	}

	strcpy(outStr, szTemp);
}

static BOOL AnalyzeArgument(char *key)
{
	return false;
}


bool NetmarbleParseArguments(const char* pszArgs)
{
	if (AnalyzeArgument((char*)pszArgs) == TRUE)
		return true;
	else
		return false;
}

#endif // #ifdef LOCALE_KOREA