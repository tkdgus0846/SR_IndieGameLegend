#pragma once
#include "Tile.h"
class CSwampTile :
	public CTile
{
private:
	CSwampTile(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSwampTile();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"SwampTile"; }
	CGameObject* LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionStay(const class Collision* collision);
};
