#include "UltimateUI.h"
#include "Export_Function.h"
#include "Player.h"

CUltimateUI::CUltimateUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
	Set_ObjTag(L"HP");
}


CUltimateUI::~CUltimateUI()
{
}

HRESULT CUltimateUI::Add_Component()
{
	m_dRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex_Dynamic", this));
	NULL_CHECK_RETURN(m_dRcTex, E_FAIL);

	m_sRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_sRcTex, E_FAIL);

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"UltimateGuage_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[ULTIMATE_GUAGE] = Texture;

	return S_OK;
}

HRESULT CUltimateUI::Ready_GameObject(void)
{
	__super::Ready_GameObject();
	return S_OK;
}

_int CUltimateUI::Update_GameObject(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CUltimateUI::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CUltimateUI::Render_GameObject(void)
{
	_float Cur = dynamic_cast<CPlayer*>(Engine::Get_Player())->Get_UltiGuage();
	_float Max = dynamic_cast<CPlayer*>(Engine::Get_Player())->Get_UltiMaxGuage();

	m_dRcTex->Edit_V(Cur / Max);
	Set_ViewMatrix_UI(-377.f, -231.f);
	dynamic_cast<CTexture*>(m_arrMap[ULTIMATE_GUAGE])->Render_Texture();
	m_dRcTex->Render_Component();

	__super::Render_GameObject();
}

void CUltimateUI::Set_ViewMatrix_UI(_float posX, _float posY)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, 4.f, 22.f, 0.f);
	matTrans.Translation(posX, posY, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

CUltimateUI * CUltimateUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CUltimateUI* pInstance = new CUltimateUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CUltimateUI::Free(void)
{
	Safe_Release(m_sRcTex);
	Safe_Release(m_dRcTex);

	auto iter = m_arrMap.begin();
	for (; iter < m_arrMap.end(); iter++)
	{
		Safe_Release(*iter);
	}

	__super::Free();
}