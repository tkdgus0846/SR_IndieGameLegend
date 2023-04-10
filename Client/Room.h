#pragma once

#include "Include.h"
#include "GameObject.h"
#include "Tile.h"

class CWall;
class CTile;
class CFloor;
class CDoor;
class CRoom : public Engine::CGameObject
{
private:
	explicit CRoom(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRoom();

public:
	HRESULT Ready_GameObject(const _float& fVtxCntX, const _float& fVtxCntZ, const _float& fVtxItv);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	CFloor* GetFloor() const { return m_pFloor; }
	CWall* GetWallArray(_uint index) const { return m_apWall[index]; }
	void AddTile(CTile* pTile) { if (nullptr == pTile) return; m_vecTile.push_back(pTile); }
	void AddGameObject(CGameObject* pGameObject) { if (nullptr == pGameObject) return; m_vecGameObj.push_back(pGameObject); }
	_bool& Cur_Door_State(DOOR_DIR eDir) { return m_apDoor[eDir].first; }
	void Set_DoorType(DOOR_TYPE eType);

private:
	virtual HRESULT Add_Component() override;
	HRESULT CreateSubset();

public:
	void FloorSubSet();
	void PlaceSubSet();
	_bool WriteRoomFile(HANDLE hFile, DWORD& dwByte);
	_bool ReadRoomFile(HANDLE hFile, DWORD& dwByte);
	_int ObjNum() const  { return m_vecGameObj.size(); }
	CGameObject* GetObjByIndex(_int iIndex) const
	{
		if (iIndex < 0 || iIndex >= m_vecGameObj.size()) return nullptr;
		return m_vecGameObj[iIndex];
	}

	HRESULT fail() { return E_FAIL; }
	_int TileNum() const { return m_vecTile.size(); }
	CGameObject* GetTileByIndex(_int iIndex) const
	{
		if (iIndex < 0 || iIndex >= m_vecTile.size()) return nullptr;
		return m_vecTile[iIndex];
	}

private:
	_float				m_fVtxCntX;
	_float				m_fVtxCntZ;
	_float				m_fVtxItv;
	vector<CTile*>		m_vecTile;

	vector<CGameObject*> m_vecGameObj; // ���Ͷ�, ��ֹ� ������ ����

private:
	CFloor*				m_pFloor;
	array<CWall*, 4>	m_apWall;

	array<pair<_bool, CDoor*>, 4>	m_apDoor;
	DOOR_TYPE			m_eDoorType;

public:
	static CRoom*		Create(LPDIRECT3DDEVICE9 pGraphicDev, 
		const _float& fVtxCntX = VTXCNTX, const _float& fVtxCntZ = VTXCNTZ, const _float& fVtxItv = VTXITV);

private:
	virtual void Free(void) override;
};

