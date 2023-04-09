#include "FlameProjector.h"



#include "Export_Function.h"

#include "BulletMgr.h"
#include "FireBullet.h"

CFlameProjector::CFlameProjector(LPDIRECT3DDEVICE9 pGraphicDev) :
	CWeapon(pGraphicDev)
{
	m_fCycle = 0.3f;
	m_MaxBulletNum = 20;
	m_CurBulletNum = 20;
}

CFlameProjector::~CFlameProjector()
{
}

CBullet* CFlameProjector::Shot_Setting()
{
	CCamera* playerCamera = dynamic_cast<CCamera*>(Get_Player()->Get_Component(L"Player_Camera", ID_UPDATE));

	if (playerCamera == nullptr) return nullptr;


	VIEWPARAMS* cameraViewparams = playerCamera->Get_Camera_ViewParams();
	_vec3 cameraAt = cameraViewparams->vAt;
	_vec3 cameraEye = cameraViewparams->vEye;

	_vec3 look = cameraAt - cameraEye;

	look = look*30.f;

	cameraAt = cameraEye + look;


	_vec3 bulletDir = cameraAt - m_pTransform->m_vInfo[INFO_POS];
	bulletDir.Normalize();

	CBullet* bullet = CBulletMgr::GetInstance()->Pop<CFireBullet>(L"FireBullet", m_pGraphicDev, m_pTransform->m_vInfo[INFO_POS], bulletDir, { 0.5f,0.5f,1.f }, false);

	return bullet;
}

_int CFlameProjector::Update_GameObject(const _float& fTimeDelta)
{
	return __super::Update_GameObject(fTimeDelta);
}

HRESULT CFlameProjector::Add_Component()
{

	/*CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });*/
	return S_OK;
}

HRESULT CFlameProjector::Ready_GameObject(void)
{
	return __super::Ready_GameObject();
}

void CFlameProjector::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CFlameProjector::Render_GameObject(void)
{

	__super::Render_GameObject();
}

CFlameProjector* CFlameProjector::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform)
{
	CFlameProjector*		pInstance = new CFlameProjector(pGraphicDev);
	pInstance->m_pOwnerTransform = pOnwerTransform;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CFlameProjector::Free(void)
{
	__super::Free();
}