HRESULT			Create_Management(CManagement** ppManagement)
{
	CManagement*		pManagement = CManagement::GetInstance();
	NULL_CHECK_RETURN(pManagement, E_FAIL);

	*ppManagement = pManagement;

	return S_OK;
}

CComponent*			Get_Component(LAYERID LayerID, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID)
{
	return CManagement::GetInstance()->Get_Component(LayerID, pObjTag, pComponentTag, eID);
}

void Engine::Add_GameObject(LAYERID LayerID, const _tchar* pObjTag, class CGameObject* pObj)
{
	CManagement::GetInstance()->Add_GameObject(LayerID, pObjTag, pObj);
}

HRESULT			Set_Scene(CScene* pScene)
{
	return CManagement::GetInstance()->Set_Scene(pScene);
}

_int			Update_Management(const _float& fTimeDelta)
{
	return CManagement::GetInstance()->Update_Management(fTimeDelta);
}
void			LateUpdate_Management()
{
	CManagement::GetInstance()->LateUpdate_Management();
}
void			Render_Management(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CManagement::GetInstance()->Render_Management(pGraphicDev);
}

HRESULT		Ready_Proto(const _tchar* pProtoTag, CComponent* pComponent)
{
	return CProtoMgr::GetInstance()->Ready_Proto(pProtoTag, pComponent);
}
CComponent*	Clone_Proto(const _tchar* pProtoTag, CGameObject* pGameObject, class CBlackBoard* pBlackBoard)
{
	return CProtoMgr::GetInstance()->Clone_Proto(pProtoTag, pGameObject, pBlackBoard);
}

void		Add_RenderGroup(RENDERID eID, CGameObject* pGameObject)
{
	CRenderer::GetInstance()->Add_RenderGroup(eID, pGameObject);
}
void		Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev)
{
	CRenderer::GetInstance()->Render_GameObject(pGraphicDev);
}
void		Clear_RenderGroup(void)
{
	CRenderer::GetInstance()->Clear_RenderGroup();
}

void		Add_Collider(CCollider * pCollider)
{
	CCollisionMgr::GetInstance()->Add_Collider(pCollider);
}
void		Check_Collision(COLGROUP eGroup1, COLGROUP eGroup2)
{
	CCollisionMgr::GetInstance()->Check_Collision(eGroup1, eGroup2);
}
void		Clear_Collision()
{
	CCollisionMgr::GetInstance()->Clear_Collision();
}

void		Set_Collider(COLGROUP eGroup, CCollider* pCollider)
{
	CCollisionMgr::GetInstance()->Set_Collider(eGroup, pCollider);
}

void		On_Camera(const _tchar* pCamTag)
{
	CCameraMgr::GetInstance()->On_Camera(pCamTag);
}

void Shake_Camera()
{
	CCameraMgr::GetInstance()->Shake_Camera();
}
HRESULT			Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex)
{
	return CLightMgr::GetInstance()->Ready_Light(pGraphicDev, pLightInfo, iIndex);
}

void						Release_Utility(void)
{
	CCameraMgr::GetInstance()->DestroyInstance();
	CLightMgr::GetInstance()->DestroyInstance();
	CCollisionMgr::GetInstance()->DestroyInstance();
	CRenderer::GetInstance()->DestroyInstance();
	CProtoMgr::GetInstance()->DestroyInstance();
	CManagement::GetInstance()->DestroyInstance();
}