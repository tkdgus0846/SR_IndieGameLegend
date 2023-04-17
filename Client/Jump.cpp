#include "stdafx.h"
#include "Jump.h"

#include "Export_Function.h"


CJump::CJump(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev), m_fTime(0.f), 
	m_fInit(0.f)
{
}

CJump::CJump(const CJump & rhs)
	:CBehavior(rhs), m_fTime(rhs.m_fTime),
	m_fInit(rhs.m_fInit)
{
}

CJump::~CJump()
{
}

HRESULT CJump::Ready_Behavior()
{
	m_fInit = m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y;

	return S_OK;
}

_int CJump::Update_Component(const _float & fTimeDelta)
{
	m_fCurTime = Get_WorldTime();

	if (m_fCurTime - m_fPreTime < m_fTimer)
		return BEHAVIOR_FAIL;

	CAnimation* pAnimation = dynamic_cast<CAnimation*>(m_pGameObject->Get_Component(L"Animation", ID_ALL));
	if (pAnimation)
		pAnimation->SelectState(ANIM_JUMP);

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_FAIL);
	//fSpeed *= 0.8f;

	// 점프했을때 떨어지는 고점을 바꾸면 될거같긴한데
	m_fTime += fTimeDelta * 7.f;

	_float fY = fSpeed * m_fTime - 4.9f * m_fTime * m_fTime;

	m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y += fY / 8.f;

	if (m_fInit > m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y)
	{
		m_pGameObject->m_pTransform->m_vInfo[INFO_POS].y = m_fInit;
		m_fPreTime = m_fCurTime;
		m_fTime = 0.f;

		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_RUNNING;
}

void CJump::Render_Component(void)
{
	__super::Render_Component();
}

CJump * CJump::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CJump* pInstance = new CJump(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CJump::Clone(void)
{
	return new CJump(*this);
}

void CJump::Free()
{
	__super::Free();
}
