#pragma once
#include "Weapon.h"

class CNormalWeapon : public CWeapon
{
protected:
	explicit CNormalWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNormalWeapon();

public:

	// 발사할 위치. 
	virtual void Shot() override;

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;
	

	static CNormalWeapon*		Create(LPDIRECT3DDEVICE9 pGraphicDev, CTransform* pOnwerTransform);
	virtual void Free(void) override;

};

