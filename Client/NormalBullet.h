#pragma once
#include "Bullet.h"

class CNormalBullet : public CBullet
{
	friend class CBulletPool;
private:
	explicit CNormalBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNormalBullet();

public:
	virtual void SetDead() override;

	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;


	virtual void OnCollisionEnter(const class Collision* collsion) override;
	virtual void OnCollisionStay(const class Collision* collision) override;
	virtual void OnCollisionExit(const class Collision* collision) override;
	virtual void OnTriggerEnter(const class CCollider* other) override;
	virtual void OnTriggerStay(const class CCollider* other) override;
	virtual void OnTirggerExit(const class CCollider* other) override;

protected:
	virtual void Free(void) override;

private:
	// 총알은 매니저를 통해서 생성할것.
	static CNormalBullet*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

};

