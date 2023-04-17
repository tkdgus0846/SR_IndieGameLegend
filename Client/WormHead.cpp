#include "WormHead.h"

#include "WormBody.h"
#include "WormTail.h"
#include "Export_Function.h"

CWormHead::CWormHead(LPDIRECT3DDEVICE9 pGraphicDev)
	:CMonster(pGraphicDev), m_bMove(true), m_pTail(nullptr)
{
}

CWormHead::~CWormHead()
{
}

HRESULT CWormHead::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 9.f;
	m_iAttack = 1;
	m_iHp = 100;
	m_iMaxHp = 100;

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);

	for (_int i = 0; i < 10; ++i)
		m_vecBody.push_back(dynamic_cast<CWormBody*>(CWormBody::Create(m_pGraphicDev, _vec3(18.f + i, 2.f, 18.f + i))));

	for (auto iter : m_vecBody)
		Add_Static_GameObject(iter);

	m_pTransform->Set_BillMode(true);

	_vec3 vBodyPos = m_vecBody.back()->m_pTransform->m_vInfo[INFO_POS];
	m_pTail = dynamic_cast<CWormTail*>(CWormTail::Create(m_pGraphicDev, { vBodyPos.x + 2.f, 2.f, vBodyPos.z + 2.f}));

	Add_Static_GameObject(m_pTail);

	_int iSize = m_vecBody.size();

	m_vecBody[0]->Chain_Head(this);
	m_vecBody[0]->Set_Dest(m_pTransform->m_vInfo[INFO_POS]);
	m_vecBody[0]->Chain_Back(m_vecBody[1]);
	for (_int i = 1; i < iSize - 1; ++i)
	{
		m_vecBody[i]->Chain_Back(m_vecBody[i + 1]);
		m_vecBody[i]->Chain_Front(m_vecBody[i - 1]);
		m_vecBody[i]->Set_Dest(m_vecBody[i - 1]->m_pTransform->m_vInfo[INFO_POS]);
	}
	m_vecBody[iSize - 1]->Chain_Front(m_vecBody[iSize - 2]);
	m_vecBody[iSize - 1]->Set_Dest(m_vecBody[iSize - 2]->m_pTransform->m_vInfo[INFO_POS]);
	m_vecBody[iSize - 1]->Chain_Tail(m_pTail);

	m_pTail->Chain_Front(m_vecBody[iSize - 1]);
	m_pTail->Set_Dest(m_vecBody[iSize - 1]->m_pTransform->m_vInfo[INFO_POS]);
	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CWormHead::Update_GameObject(const _float & fTimeDelta)
{
	if (!Get_Player())
		return OBJ_NOEVENT;

	if (Key_Down(DIK_SPACE))
		m_fSpeed = 0.f;
	__super::Update_GameObject(fTimeDelta);

	if (GetDead() && m_vecBody.size() == 0 && m_pTail == nullptr)
		return OBJ_DEAD;
	else if (GetDead())
	{
		for (auto iter : m_vecBody)
			iter->SetDead();
		m_vecBody.clear();
		if (m_pTail)
		{
			m_pTail->SetDead();
			m_pTail = nullptr;
		}
		return OBJ_NOEVENT;
	}

	m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);

	_vec3 vDir = m_pTransform->m_vInfo[INFO_LOOK];
	vDir.Normalize();
	_vec3 vDirXZ = { vDir.x, 0.f, vDir.z };
	vDirXZ.Normalize();
	_float fAngle = vDir.Degree(_vec3(vDirXZ.x, 0.f, vDirXZ.z));
	if (isnan(fAngle))
		fAngle = 0.f;

	m_pTransform->Rot_Bill(fAngle);

	for (auto iter = m_vecBody.begin(); iter != m_vecBody.end(); )
	{
		_int iResult = (*iter)->Update_GameObject(fTimeDelta);
		if (iResult == OBJ_DEAD)
			iter = m_vecBody.erase(iter);
		else
			++iter;
	}

	if (m_pTail)
	{
		_int iResult = m_pTail->Update_GameObject(fTimeDelta);
		if (iResult == OBJ_DEAD)
			m_pTail = nullptr;
	}

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return OBJ_NOEVENT;
}

void CWormHead::LateUpdate_GameObject(void)
{
	if (!Get_Player())
		return;

	if (GetDead())
		return;

	m_pTransform->Set_Scale({ 1.f, 1.f, 1.f });

	_vec3 vPos = Get_Player()->m_pTransform->m_vInfo[INFO_POS];
	_vec3 vDir = vPos - m_pTransform->m_vInfo[INFO_POS];
	vDir.Normalize();

	_float fAngleRight = vDir.Degree(m_pTransform->m_vInfo[INFO_RIGHT]);
	_float fAngleUp = vDir.Degree(m_pTransform->m_vInfo[INFO_UP]);
	_float fAngleLook = vDir.Degree(m_pTransform->m_vInfo[INFO_LOOK]);

	if (isnan(fAngleLook))
		return;

	if (fAngleRight < 45.f)
		m_pAnimation->SelectState(ANIM_SIDE);
	else if (fAngleUp < 45.f)
		m_pAnimation->SelectState(ANIM_TOP);
	else if (fAngleLook < 45.f)
		m_pAnimation->SelectState(ANIM_FACE);

	else if (fAngleRight > 135.f)
	{
		m_pTransform->Set_Scale({ -1.f, 1.f, 1.f });
		m_pAnimation->SelectState(ANIM_SIDE);
	}

	else if (fAngleLook > 135.f)
		m_pAnimation->SelectState(ANIM_BACK);

	else if (fAngleUp < 135.f)
	{
		m_pTransform->Set_Scale({ -1.f, 1.f, 1.f });
		m_pAnimation->SelectState(ANIM_TOP);
	}
	else
		m_pAnimation->SelectState(ANIM_FACE);

	for (auto iter : m_vecBody)
		iter->LateUpdate_GameObject();
	if (m_pTail)
		m_pTail->LateUpdate_GameObject();
	__super::LateUpdate_GameObject();
}

void CWormHead::Render_GameObject(void)
{
	if (GetDead())
		return;

	for (auto iter : m_vecBody)
		iter->LateUpdate_GameObject();
	if (m_pTail)
		m_pTail->Render_GameObject();
	__super::Render_GameObject();
}

HRESULT CWormHead::Add_Component()
{
	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Animation", m_pAnimation);

	CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Side_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Drill_Side_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_SIDE, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Top_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Drill_Top_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_TOP, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Face_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Drill_Face_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_FACE, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Back_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Drill_Back_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_BACK, pTexture, 0.05f);

	m_pAnimation->SelectState(ANIM_FACE);

	CRcTex* pBufferCom1 = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom1, E_FAIL);
	m_uMapComponent[ID_RENDER].emplace(L"RcTex", pBufferCom1);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 1.5f, 1.5f, 1.5f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Range", pCollider);
	pCollider->Set_BoundingBox({ 70.f, 30.f, 70.f });

	FAILED_CHECK_RETURN(Create_Root_AI());
	FAILED_CHECK_RETURN(Set_Boss3_AI());
	FAILED_CHECK_RETURN(Init_AI_Behaviours());
}

CGameObject * CWormHead::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CWormHead* pInstance = new CWormHead(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CWormHead::Free(void)
{
	__super::Free();
}