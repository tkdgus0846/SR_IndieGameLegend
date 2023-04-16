#include "WormBody.h"

#include "WormHead.h"
#include "Export_Function.h"

CWormBody::CWormBody(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev), m_pFrontBody(nullptr)
	, m_pBackBody(nullptr), m_bMove(false), m_pHead(nullptr)
{
	ZeroMemory(m_vDest, sizeof(_vec3));
}

CWormBody::~CWormBody()
{
}

HRESULT CWormBody::Ready_GameObject(const _vec3 & vPos)
{
	m_fSpeed = 7.f;
	m_iAttack = 1;
	m_iHp = 20;
	m_iMaxHp = 20;

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = vPos;
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);

	m_pTransform->Set_BillMode(true);

	HRESULT result = __super::Ready_GameObject();

	return result;
}

_int CWormBody::Update_GameObject(const _float & fTimeDelta)
{
	if (Key_Down(DIK_9))
	{
		m_pTransform->Set_BillMode(false);
		m_pTransform->Rot_Roll(90.f, 1.f);
	}

	if (GetDead())
	{
		if (m_pFrontBody)
			m_pFrontBody->Chain_Back(m_pBackBody);

		if (m_pBackBody)
			m_pBackBody->Chain_Front(m_pFrontBody);

		return OBJ_DEAD;
	}

	if(m_pHead && m_pHead->Get_Move() != m_bMove)
		m_bMove = m_pHead->Get_Move();

	else if (m_pFrontBody && m_pFrontBody->m_bMove != m_bMove)
		m_bMove = m_pFrontBody->m_bMove;

	if (m_bMove)
		Move(fTimeDelta);

	__super::Update_GameObject(fTimeDelta);

	if (false == m_pTransform->Get_BillMode())
		m_pTransform->Set_BillMode(true);

	if (GetDead()) return OBJ_DEAD;

	Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CWormBody::LateUpdate_GameObject(void)
{
	if (GetDead())
		return;

	if (!Get_Player())
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

	//cout << fAngleRight << ", " << fAngleUp << ", " << fAngleLook << endl;

	__super::LateUpdate_GameObject();
}

void CWormBody::Render_GameObject(void)
{
	if (GetDead())
		return;
	__super::Render_GameObject();
}

HRESULT CWormBody::Add_Component()
{
	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Animation", m_pAnimation);

	CTexture* pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Body_Side_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Body_Side_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_SIDE, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Body_Top_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Body_Top_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_TOP, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Back_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Body_Face_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_FACE, pTexture, 0.05f);

	pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Monster_WormBoss_Drill_Back_Texture", this));
	NULL_CHECK_RETURN(pTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].emplace(L"Monster_WormBoss_Body_Back_Texture", pTexture);
	m_pAnimation->BindAnimation(ANIM_BACK, pTexture, 0.05f);

	m_pAnimation->SelectState(ANIM_FACE);

	CRcTex* pBufferCom1 = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom1, E_FAIL);
	m_uMapComponent[ID_RENDER].emplace(L"RcTex", pBufferCom1);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENEMY));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"BodyCollider", pCollider);
	pCollider->Set_BoundingBox({ 1.f, 1.f, 1.f });

	pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Range", this, COL_DETECTION));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].emplace(L"Range", pCollider);
	pCollider->Set_BoundingBox({ 1.f, 1.f, 1.f });
}

void CWormBody::Move(const _float & fTimeDelta)
{
	_vec3 vPos = m_pTransform->m_vInfo[INFO_POS];
	_vec3 vDir = m_vDest - vPos;
	_float fLength = 0.f;

	if (m_pHead)
	{
		fLength = _vec3(m_pHead->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS]).Length();
		if (vDir.Length() < 0.1f)
			m_vDest = m_pHead->m_pTransform->m_vInfo[INFO_POS];
	}
	else
	{
		fLength = _vec3(m_pFrontBody->m_pTransform->m_vInfo[INFO_POS] - m_pTransform->m_vInfo[INFO_POS]).Length();
		if (vDir.Length() < 0.1f)
			m_vDest = m_pFrontBody->m_pTransform->m_vInfo[INFO_POS];
	}
	m_pTransform->Set_Target(m_vDest);

	vDir = m_vDest - vPos;
	vDir.Normalize();
	if (fLength < 1.f)
		m_pTransform->Move_Walk(1.f, fTimeDelta);
	else
		m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);
}

CWormBody * CWormBody::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3 & vPos)
{
	CWormBody* pInstance = new CWormBody(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject(vPos)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CWormBody::Free(void)
{
	__super::Free();
}
