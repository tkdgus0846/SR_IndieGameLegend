﻿#include "stdafx.h"
#include "Bullet.h"

#include "Export_Function.h"

CBullet::CBullet(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev),
	m_Damage(1)
{
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);
}

CBullet::~CBullet()
{
}

