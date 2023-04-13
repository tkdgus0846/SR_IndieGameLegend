#include "LookAtTarget.h"

#include "Export_Function.h"

CLookAtTarget::CLookAtTarget(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CLookAtTarget::CLookAtTarget(const CLookAtTarget & rhs)
	: CBehavior(rhs)
{
}

CLookAtTarget::~CLookAtTarget()
{
}

HRESULT CLookAtTarget::Ready_Behavior()
{
	return S_OK;
}

_int CLookAtTarget::Update_Component(const _float & fTimeDelta)
{
	CTransform* pTargetTransform = dynamic_cast<CTransform*>(Engine::Get_Component(LAYER_PLAYER, L"Player", L"Transform", ID_UPDATE));
	NULL_CHECK_RETURN(pTargetTransform, BEHAVIOR_FAIL);

	m_pGameObject->m_pTransform->Set_Target(pTargetTransform->m_vInfo[INFO_POS]);

	return BEHAVIOR_SUCCES;
}

void CLookAtTarget::Render_Component(void)
{
}

CComponent * CLookAtTarget::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLookAtTarget* pInstance = new CLookAtTarget(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CLookAtTarget::Clone(void)
{
	return new CLookAtTarget(*this);
}

void CLookAtTarget::Free()
{
	__super::Free();
}