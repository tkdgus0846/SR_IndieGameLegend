#include "stdafx.h"
#include "ObjCamera.h"

#include "Export_Function.h"

CObjCamera::CObjCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CObjCamera::~CObjCamera()
{
}

HRESULT CObjCamera::Ready_GameObject(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = _vec3(15.f, 20.f, 30.f);

	return S_OK;
}

_int CObjCamera::Update_GameObject(const _float & fTimeDelta)
{
	Key_Input(fTimeDelta);

	CTransform*	pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"Player", L"Transform", ID_DYNAMIC));

	m_pTransform->m_vInfo[INFO_LOOK] = 
		pPlayerTransformCom->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS];

	__super::Update_GameObject(fTimeDelta);
	return 0;
}

void CObjCamera::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CObjCamera::Render_GameObject(void)
{
}

HRESULT CObjCamera::Add_Component(void)
{
	CComponent*		pComponent = nullptr;

	pComponent = m_pCamera = dynamic_cast<CCamera*>(Engine::Clone_Proto(L"Camera", this));
	NULL_CHECK_RETURN(m_pCamera, E_FAIL);
	m_uMapComponent[ID_DYNAMIC].insert({ L"Obj_Camera", pComponent });
	m_pCamera->Set_CameraName(L"Obj_Camera");

	return S_OK;
}

void CObjCamera::Key_Input(const _float & fTimeDelta)
{
	if (GetAsyncKeyState(VK_F2)) Engine::On_Camera(L"Obj_Camera");
	if (GetAsyncKeyState(VK_F3)) Engine::Shake_Camera();
}

CObjCamera * CObjCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CObjCamera*		pInstance = new CObjCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CObjCamera::Free()
{
	__super::Free();
}