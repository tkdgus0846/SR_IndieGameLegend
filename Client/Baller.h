#pragma once
#include "Monster.h"
class CBaller : public CMonster
{
private:
	explicit CBaller(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBaller();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;
	virtual void OnCollisionEnter(const class Collision* collsion) override {}
	virtual void OnCollisionStay(const class Collision* collision) override {}
	virtual void OnCollisionExit(const class Collision* collision) override {}

public:
	static CBaller*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

