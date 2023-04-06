#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;

END

class CBulletGauge :
	public CUI
{
public:
	CBulletGauge(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBulletGauge();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	void		Set_OrthoProj();

private:
	Engine::CRcTex*			m_pBufferCom;
	Engine::CTexture*		m_pTextureCom;
	D3DXMATRIX  matWorld, matView;

	_float m_GaugeScale = 106.f;
	_float m_GaugePos = -203.f;
	_float m_VBGuage = 1.f;

public:
	static CBulletGauge*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};
