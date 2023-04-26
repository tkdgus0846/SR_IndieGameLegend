#pragma once
#include "MapObj.h"
class CSnowMan :
	public CMapObj
{
protected:
	explicit CSnowMan(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSnowMan();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void Render_GameObject() override;
	virtual HRESULT Add_Component() override;

	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"SnowMan"; }

	virtual void OnCollisionStay(const class Collision* collision);
};
