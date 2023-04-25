#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;

END

enum SKILLUI
{
	TIMESTOP,
	GRAVITION,
	TACTICAL,
	SKILLEND
};


class CSkillUI : public CUI
{

protected:
	explicit CSkillUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSkillUI();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	array<CComponent*, SKILLEND> m_arrMap;
	D3DXMATRIX  matWorld, matView;

	CRcTex* m_pRcTex = nullptr;

public:
	static CSkillUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};
