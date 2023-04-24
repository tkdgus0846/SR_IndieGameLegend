#include "ShortWall.h"
#include "Export_Function.h"


ShortWall::ShortWall(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

ShortWall::~ShortWall()
{
}

CGameObject * ShortWall::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	ShortWall* pInstance = new ShortWall(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT ShortWall::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"ShortWall", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"ShortWall", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}