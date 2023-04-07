#include "Baller.h"

#include "Export_Function.h"

CBaller::CBaller(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev)
{
}

CBaller::~CBaller()
{
}

HRESULT CBaller::Ready_GameObject(void)
{
	m_fSpeed = 10.f;

	m_pTransform->m_vScale = { 1.f, 3.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = { 5.f, 3.f, 5.f };
	m_pTransform->Set_MoveType(CTransform::LANDOBJECT);

	HRESULT result = __super::Ready_GameObject();

	return S_OK;
}

_int CBaller::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	

	return S_OK;
}

void CBaller::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBaller::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());

	__super::Render_GameObject();

}

HRESULT CBaller::Add_Component()
{
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_Baller_Texture", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Monster_Bub_Texture", texture });

	CAnimation* animation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(animation, E_FAIL);

	animation->BindAnimation(ANIM_WALK, texture, 0.07f);
	animation->SelectState(ANIM_WALK);
	m_uMapComponent[ID_ALL].insert({ L"Animation", animation });

	CRcTex* rcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(rcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", rcTex });

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", pCollider });
	pCollider->Set_BoundingBox({ 0.6f, 0.6f, 0.6f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Range", pCollider });
	pCollider->Set_BoundingBox({ 50.f, 10.f, 50.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"EvasBullet", pCollider });
	pCollider->Set_BoundingBox({ 2.5f, 2.5f, 2.5f });

	Set_PatrolAndFollow_AI();

	return S_OK;
}

CBaller * CBaller::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBaller* pInstance = new CBaller(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBaller::Free(void)
{
	__super::Free();
}
