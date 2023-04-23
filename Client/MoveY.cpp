#include "MoveY.h"

#include "Export_Function.h"

CMoveY::CMoveY(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_bIsUp(false)
	, m_bStart(false), m_fTime(0.f), m_fFstSpeed(0.f)
	, m_fDest(0.f)
{
}

CMoveY::CMoveY(const CMoveY & rhs)
	: CBehavior(rhs), m_bIsUp(rhs.m_bIsUp)
	, m_bStart(rhs.m_bStart), m_fTime(rhs.m_fTime)
	, m_fFstSpeed(rhs.m_fFstSpeed), m_fDest(rhs.m_fDest)
{
}

CMoveY::~CMoveY()
{
}

HRESULT CMoveY::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CMoveY::Update_Component(const _float & fTimeDelta)
{
	m_fTime += fTimeDelta;

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);

	if (!m_bStart)
	{
		m_fFstSpeed = fSpeed;
		if (m_bIsUp)
			fSpeed = 5.f;
		else
			fSpeed *= 2.f;
		FAILED_CHECK_RETURN(m_pBlackBoard->Set_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);
		m_bStart = true;
	}

	if(m_bIsUp)
		m_pGameObject->m_pTransform->Set_Dir(_vec3(0.f, 1.f, 0.f));
	else
		m_pGameObject->m_pTransform->Set_Dir(_vec3(0.f, -1.f, 0.f));

	if ((m_fDest < m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y && m_bIsUp) ||
		(m_fDest > m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y && !m_bIsUp))
	{
		FAILED_CHECK_RETURN(m_pBlackBoard->Set_Type(L"fSpeed", m_fFstSpeed), BEHAVIOR_ERROR);
		m_fTime = 0.f;
		m_bStart = false;

		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_RUNNING;
}

void CMoveY::LateUpdate_Component(void)
{
	if(m_bIsUp)
		Shake_Camera(SHAKE_Y, 0.2f, 1.f);
}

CMoveY * CMoveY::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMoveY* pInstance = new CMoveY(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CMoveY::Clone(void)
{
	return new CMoveY(*this);
}

void CMoveY::Free()
{
	__super::Free();
}