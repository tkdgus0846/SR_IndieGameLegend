#include "stdafx.h"
#include "Tile.h"

#include "Export_Function.h"

CTile::CTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}


CTile::~CTile()
{
}

HRESULT CTile::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CTile::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);
	return _int();
}

void CTile::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CTile::Render_GameObject(void)
{
	__super::Render_GameObject();
}

HRESULT CTile::Add_Component()
{
	m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"RcTex", m_pBufferCom });

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"NormalBullet_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"NormalBullet_Texture", m_pTextureCom });
	return S_OK;
}

void CTile::Free(void)
{
	__super::Free();
}

