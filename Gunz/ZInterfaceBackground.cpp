#include "stdafx.h"

#include "ZApplication.h"
#include "ZInterfaceBackground.h"
#include "RealSpace2.h"
#include "ZMapDesc.h"
#include "MDebug.h"
#include "ZScreenEffectManager.h"

#define DIR_LOGIN	"interface/login"

#define D3DPAIR std::pair<D3DXVECTOR3, D3DXVECTOR3>
static int mapIndex = 0;
static std::vector<D3DPAIR> mapVecs;
#define MAPPAIR(x1, x2, x3, y1, y2, y3) mapVecs.push_back(D3DPAIR(D3DXVECTOR3(x1, x2, x3), D3DXVECTOR3(y1, y2, y3)))

void initMapVecs() 
{
	if (mapVecs.empty()) 
	{

		MAPPAIR(-26.f, -2812.f, 796.f, -35.f, -408.f, 1062.f);
		MAPPAIR(1957.f, -2033.f, 895.f, 8.f, 406.f, 950.f);
		MAPPAIR(-2010.f, -1904.f, 858.f, -161.f, -651.f, 1203.f);
		MAPPAIR(-1680.f, -1789.f, 1035.f, -216.f, 1677.f, 955.f);
	}
}

ZInterfaceBackground::ZInterfaceBackground( void)
{
	RealSpace2::RSetFileSystem( ZApplication::GetFileSystem());

	m_pLogin = NULL;
	m_pMapDesc = NULL;
	//	m_bShowMaietLogo = false;
	m_fFogMulti = 1.0f;

	initMapVecs();
	mapIndex = 0;
}


ZInterfaceBackground::~ZInterfaceBackground( void)
{
	if ( m_pLogin != NULL)
		delete m_pLogin;
	m_pLogin = NULL;

	if ( m_pMapDesc != NULL)
		delete m_pMapDesc;
	m_pMapDesc = NULL;
}

void ZInterfaceBackground::LoadMesh( void)
{
#ifdef _FASTDEBUG
	return;
#endif

	if ( m_pLogin == NULL)
	{
		m_pLogin = new RBspObject();

#ifndef _DEBUG
		const char* descExt = "xml";
#else
		const char* descExt = "xml";
#endif
		m_pLogin->Open( DIR_LOGIN"/login.rs", descExt);

		RDummyList* pDummyList = m_pLogin->GetDummyList();

		for ( RDummyList::iterator itor = pDummyList->begin();  itor != pDummyList->end();  ++itor)
		{
			RDummy* pDummy = *itor;

			if( stricmp( pDummy->szName.c_str(), "camera_pos 01" ) == 0 )
			{
				m_vCamPosSt = pDummy->Position;
				m_vCamDirSt = pDummy->Direction;
			}
			else if( stricmp( pDummy->szName.c_str(), "camera_pos 02" ) == 0 )
			{
				m_vCamPosEd = pDummy->Position;
				m_vCamDirEd = pDummy->Direction;
			}
			else if( stricmp( pDummy->szName.c_str(), "spawn_solo_101" ) == 0 )
			{
				m_vCharPos = pDummy->Position;
				m_vCharDir = pDummy->Direction;
			}
		}

		RMapObjectList* pMapObject = m_pLogin->GetMapObjectList();

		list<ROBJECTINFO*>::iterator it;

		ROBJECTINFO* pInfo = NULL;

		for(it = pMapObject->begin();it!=pMapObject->end();it++ ) {

			pInfo = (*it);

			if(!pInfo->pVisualMesh) continue;

			if(pInfo) {// �ʿ��ϸ� xml �� ����..
				string str = "login_obj_ef_sky02.elu";
				if( pInfo->name == str ) {
					pInfo->pVisualMesh->SetUVAnimation(-0.055f,0.f);
				}
			}
		}


		// Map description
		if ( m_pMapDesc == NULL)
		{
			m_pMapDesc = new ZMapDesc();
			m_pMapDesc->Open( m_pLogin);

			if( m_pMapDesc ) {

				char szBuf[128];
				sprintf( szBuf, "%s/smoke.xml", DIR_LOGIN );
				m_pMapDesc->LoadSmokeDesc(szBuf);
				mlog("Load smoke description mesh.\n");
			}

		}

		m_pLogin->SetMapObjectOcclusion( true );
	}
}

void ZInterfaceBackground::Free( void)
{
	if ( m_pLogin != NULL)
		delete m_pLogin;
	m_pLogin = NULL;

	if ( m_pMapDesc != NULL)
		delete m_pMapDesc;
	m_pMapDesc = NULL;
}

void ZInterfaceBackground::OnUpdate(float fElapsed)
{
	ZGetEffectManager()->Update( fElapsed);
	ZGetScreenEffectManager()->UpdateEffects();
}

void ZInterfaceBackground::Draw(void)
{
#ifdef _FASTDEBUG
	MWidget* pWidget = (MWidget*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "CharSelection");
	if ( pWidget)
	{
		if ( ZApplication::GetGameInterface()->GetState() == GUNZ_CHARSELECTION)
			pWidget->Show( true);
	}

	MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "CharSel_TopScreen");
	if ( pPicture)
		pPicture->SetOpacity( 0);

	return;
#endif

	// Set rendering state
	RSetViewport( 0, 0, RGetScreenWidth(), RGetScreenHeight());
	RGetDevice()->SetRenderState( D3DRS_CULLMODE  ,D3DCULL_CW);					// from rbs rendering
	RGetDevice()->SetRenderState( D3DRS_NORMALIZENORMALS , TRUE );
	RGetDevice()->SetSamplerState( 0, D3DSAMP_MINFILTER , D3DTEXF_LINEAR);		// Texture filtering
	RGetDevice()->SetSamplerState( 0, D3DSAMP_MAGFILTER , D3DTEXF_LINEAR);
	RGetDevice()->SetSamplerState( 0, D3DSAMP_MIPFILTER , D3DTEXF_LINEAR);

	// Set camera position and direction
	rvector vCamPos, vCamDir;
	float fForgDensity;

	switch ( m_nSceneNumber)
	{
	case  LOGIN_SCENE_FIXEDSKY :
		{
			// Fixed camera
			vCamPos = m_vCamPosSt;
			vCamDir = m_vCamDirSt;

			// Fixed fog -> black screen
			fForgDensity = 0.0f;

			break;
		}

	case  LOGIN_SCENE_FALLDOWN :
		{
			// Get current clock
			DWORD dwClock = ( timeGetTime() - m_dwClock);

			/*
			// Show maiet logo
			if ( !m_bShowMaietLogo)
			{
			m_bShowMaietLogo = true;
			ZGetScreenEffectManager()->AddScreenEffect( "maiet_logo");
			}
			*/

			// Set fog density
			fForgDensity = dwClock * 15.0f;

			// Set wait time
			if ( dwClock < 500)
				dwClock = 0;
			else
				dwClock -= 500;

			// Play BGM music
			if ( dwClock > 2000)
				ZApplication::GetSoundEngine()->PlayMusic( true);


			// End of scroll camera
			float fSeed = dwClock * 0.00035f;			// ī�޶� ���� �� �������� ���� �ɸ��� �ð�( dwClock�� �����ִ� ����
			// �������� ���� ������)
			if ( fSeed > 3.14)
			{
				m_nSceneNumber = LOGIN_SCENE_FIXEDCHAR;
				//				m_bShowMaietLogo = false;
			}


			// Move camera position & direction
			float fGain = ( cos( fSeed) + 1.0f) / 2.0f;			// 0 < fGain < 1.0
			vCamPos = m_vCamPosEd + ( m_vCamPosSt - m_vCamPosEd) * fGain;
			vCamDir = m_vCamDirEd + ( m_vCamDirSt - m_vCamDirEd) * fGain;

			//if (m_bShowMaietLogo)
			//{
			//	ZGetScreenEffectManager()->UpdateEffects();
			ZGetScreenEffectManager()->DrawEffects();
			//}

			break;
		}

	case  LOGIN_SCENE_FIXEDCHAR :
		{
			// Show menu UI
			MWidget* pWidget = (MWidget*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "CharSelection");
			if ( pWidget)
			{
				if ( ZApplication::GetGameInterface()->GetState() == GUNZ_CHARSELECTION)
					pWidget->Show( true);
			}
			MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "CharSel_TopScreen");
			if ( pPicture)
				pPicture->SetOpacity( 0);

			// Play BGM music
			ZApplication::GetSoundEngine()->PlayMusic( true);

			// Fixed camera
			vCamPos = m_vCamPosEd;
			vCamDir = m_vCamDirEd;

#ifdef _MAP_LOGIN
#define FADE_IN_TIME 500
			DWORD dwClock = ( timeGetTime() - m_dwClock);

			float fGain = ((float)dwClock / (float)FADE_IN_TIME);
			if (fGain > 1.0f)
				fGain = 1.0f;	
			SetFogMulti(fGain);  
#endif 


			// Cleared fog
			fForgDensity = 50000.0f;
			break;
		}

	case  LOGIN_SCENE_SELECTCHAR:
	{
		// Get current clock
		DWORD dwClock = (timeGetTime() - m_dwClock);
		float fGain = (cos(dwClock * 0.0012f) + 1.0f) / 2.0f;
#ifdef _MOVING_CAMERA_AFTER_CHAR_SEL
		vCamPos = m_vCamPosEd + (m_vCamPosSt - m_vCamPosEd) * fGain;
		vCamDir = m_vCamDirEd + (m_vCamDirSt - m_vCamDirEd) * fGain;
#else
		vCamPos = m_vCamPosEd;
		vCamDir = m_vCamDirEd;
#endif

			MPicture* pPicture = (MPicture*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget( "CharSel_TopScreen");
			if ( pPicture)
			{
				// Set wait time
				if ( dwClock < 2000)
					dwClock = 0;
				else
					dwClock -= 2000;

				// Set opacity of black screen
				int nOpacity = (int)( dwClock / 3.0f);
				if ( nOpacity > 255)
					nOpacity = 255;

				pPicture->SetOpacity( nOpacity);
			}

			// Cleared fog
			fForgDensity = 50000.0f;
			break;
		}

	case  LOGIN_SCENE_MAIN :
		{
			DWORD dwClock = ( timeGetTime() - m_dwClock);

			fForgDensity = dwClock * 15.0f;

			float fSeed = dwClock * 0.00035f;

			vCamPos = m_vCamPosEd + ( m_vCamPosSt - m_vCamPosEd);
			vCamDir = m_vCamDirEd + ( m_vCamDirSt - m_vCamDirEd);

			break;
		}

	case  LOGIN_ROAMING :
		{
#define ROAM_SPEED 10000
			DWORD dwClock = ( timeGetTime() - m_dwClock);

			/*if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
			off.y -= 1.0f;
			if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
			off.y += 1.0f;
			if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
			off.x += 1.0f;
			if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
			off.x -= 1.0f;
			if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
			off.z -= 1.0f;
			if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
			off.z += 1.0f;

			vCamPos = m_vCamPosEd + off;
			vCamDir = m_vCamDirEd;

			// Cleared fog
			fForgDensity = 50000.0f;*/

			float fGain = ((float)dwClock / (float)ROAM_SPEED);
			if (fGain > 1.0f)
				fGain = 1.0f;
			//vCamDir = mapVecs[mapIndex].second - mapVecs[mapIndex].first;
			vCamDir = m_vCamDirEd;
			vCamPos = mapVecs[mapIndex].first + ((mapVecs[mapIndex].second - mapVecs[mapIndex].first) * fGain) + D3DXVECTOR3(0.f,-100.f,0.f);

			if (dwClock > ROAM_SPEED) {
				m_dwClock = timeGetTime();				
				mapIndex = rand() % mapVecs.size();
			}

			//fForgDensity = 50000.0f; //Clear
			fForgDensity = ((-4 * fGain * fGain) + (4 * fGain)) * 20000.f;

			break;
		}
	}

	// Set camera
	RSetCamera( vCamPos, (vCamPos + vCamDir), rvector( 0, 0, 1));

	// Draw
	RSetProjection( D3DX_PI * 70 / 180, RGetScreenWidth() / (float)RGetScreenHeight(), 10.0f, 15000.0f);
	SetFogState( fForgDensity-10000.0f, fForgDensity, 0x00000000);
	D3DXMatrixTranslation( &m_matWorld, 0, 0, 0);
	RGetDevice()->SetTransform( D3DTS_WORLD, &m_matWorld);

	// Draw background
	if ( m_pLogin)
	{
		m_pLogin->Draw();
		m_pLogin->DrawObjects();
	}

	if ( m_pMapDesc)
		m_pMapDesc->DrawMapDesc();

	// Draw effects(smoke, cloud)
	ZGetEffectManager()->Draw( timeGetTime());

	// Draw maiet logo effect
	//	ZGetScreenEffectManager()->DrawEffects();
}


void ZInterfaceBackground::OnInvalidate()
{
#ifdef _FASTDEBUG
	return;
#endif

	if( m_pLogin)
		m_pLogin->OnInvalidate();
}


void ZInterfaceBackground::OnRestore()
{
#ifdef _FASTDEBUG
	return;
#endif

	if( m_pLogin)
		m_pLogin->OnRestore();
}


void ZInterfaceBackground::SetScene(int nSceneNumber)
{
	if (nSceneNumber == m_nSceneNumber)
		return;

	if ((nSceneNumber == LOGIN_SCENE_FALLDOWN) || (nSceneNumber == LOGIN_SCENE_SELECTCHAR))
		m_dwClock = timeGetTime();

	// �ΰ� �ѷ��ش�

#ifdef _MAIET_LOGO
	if (nSceneNumber == LOGIN_SCENE_FALLDOWN)
		ZGetScreenEffectManager()->AddScreenEffect("maiet_logo");
#endif

#ifdef _MOVING_CAMERA_AFTER_CHAR_SEL
	if (nSceneNumber == LOGIN_SCENE_SELECTCHAR)
	{
		m_vCamPosSt = m_vCamPosEd;
		m_vCamPosEd.y = -780;
		m_vCamPosEd.z = 60;

		m_vCamDirSt = m_vCamDirEd;
		m_vCamDirEd.x = -0.55f;
		m_vCamDirEd.z = 0.40f;
	}
#endif

	m_nSceneNumber = nSceneNumber;
}


void ZInterfaceBackground::SetFogState( float fStart, float fEnd, unsigned long int color)
{
	RGetDevice()->SetRenderState( D3DRS_FOGENABLE, TRUE);
	RGetDevice()->SetRenderState( D3DRS_FOGCOLOR, color);

	RGetDevice()->SetRenderState( D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	RGetDevice()->SetRenderState( D3DRS_FOGSTART, *(DWORD *)(&fStart));
	RGetDevice()->SetRenderState( D3DRS_FOGEND,   *(DWORD *)(&fEnd));
}