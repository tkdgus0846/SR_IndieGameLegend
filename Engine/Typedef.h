#pragma once

typedef		signed char				_byte;
typedef		unsigned char			_ubyte;

typedef		wchar_t					_tchar;

typedef		signed short			_short;
typedef		unsigned short			_ushort;

typedef		signed int				_int;
typedef		unsigned int			_uint;

typedef		signed long				_long;
typedef		unsigned long			_ulong;

typedef		float					_float;
typedef		double					_double;

typedef		bool					_bool;


typedef		D3DXVECTOR2				_vec2;
//typedef		D3DXVECTOR3				_vec3;
typedef		D3DXVECTOR4				_vec4;

//typedef		D3DXMATRIX				_matrix;



typedef	struct MyVec3 : public D3DXVECTOR3
{
	MyVec3() : D3DXVECTOR3() {}
	MyVec3(_float x, _float y, _float z) : D3DXVECTOR3(x, y, z) {}
	MyVec3(const D3DXVECTOR3& vec) : D3DXVECTOR3(vec) {}

	// 벡터의 길이를 반환하는 메서드입니다.
	// ex) float fLength = vVec.Length();
	float Length() const { return D3DXVec3Length(this); }

	// 벡터 간의 내적 결과를 반환하는 메서드 입니다.
	// ex) float fDot = vVec.Dot(vOther);
	float Dot(const D3DXVECTOR3& other) const { return D3DXVec3Dot(this, &other); }

	// 두 벡터의 외적 결과를 반환하는 메서드입니다.
	// ex) MyVec3 vRight = vUp.Cross(vLook); 같은 방법으로 쓰면 됨.
	MyVec3 Cross(const D3DXVECTOR3& other) const {
		D3DXVECTOR3 result;
		return *D3DXVec3Cross(&result, this, &other);
	}

	// 단위 벡터로 만드는 메서드입니다.
	// ex) vVec.Normalize();
	void Normalize() { D3DXVec3Normalize(this, this); }

	// 벡터 사이의 라디안을 반환하는 메서드입니다.
	// ex) float fRadians = vMyVec.Radians(vOtherVec);
	float Radians(D3DXVECTOR3& other) const { return acos(this->Dot(other) / (this->Length() * D3DXVec3Length(&other))); }

	// 벡터 사이의 각도(Degree)를 반환하는 메서드입니다.
	// ex) float Degree = vMyVec.Degree(vOtherVec);
	float Degree(D3DXVECTOR3& other) const { return D3DXToDegree(Radians(other)); }

	// 두 벡터 사이를 선형적으로 보간하는 메서드입니다.
	// ex) 
	// MyVec3 startVec(0.0f, 0.0f, 0.0f);
	// MyVec3 endVec(10.0f, 10.0f, 10.0f);
	// float t = 0.5f;
	// MyVec3 lerpVec = MyVec3::lerp(startVec, endVec, t);
	// ********** 결과 lerpVec = {5.0f, 5.0f, 5.0f} ************* 
	static MyVec3 Lerp(const D3DXVECTOR3& start, const D3DXVECTOR3& end, float t) { return (1.0f - t) * start + t * end; }

	// D3DXVec3TransformNormal을 래핑한 메서드입니다.
	// ex) 
	// MyVec3 vVec;
	// vVec.TransformNormal(&matRot);
	MyVec3* TransformNormal(const D3DXMATRIX* matRot)
	{
		return reinterpret_cast<MyVec3*>(D3DXVec3TransformNormal(this, this, matRot));
	}

	// D3DXVec3TransformCoord을 래핑한 메서드입니다.
	// ex) 
	// MyVec3 vVec;
	// vVec.TransformCoord(&matRot);
	MyVec3* TransformCoord(const D3DXMATRIX* matRot)
	{
		return reinterpret_cast<MyVec3*>(D3DXVec3TransformCoord(this, this, matRot));
	}
}_vec3;

typedef	struct MyMatrix : public D3DXMATRIX
{
	MyMatrix() : D3DXMATRIX() {};
	MyMatrix(CONST _float* pFloat) : D3DXMATRIX(pFloat) {};
	MyMatrix(CONST D3DXMATRIX& matrix) : D3DXMATRIX(matrix) {};
	MyMatrix(CONST D3DXFLOAT16* pFloat16) : D3DXMATRIX(pFloat16) {};
	MyMatrix(_float _11, _float _12, _float _13, _float _14,
		_float _21, _float _22, _float _23, _float _24,
		_float _31, _float _32, _float _33, _float _34,
		_float _41, _float _42, _float _43, _float _44) : D3DXMATRIX(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44) {};

	// 항등 행렬로 만드는 메서드입니다.
	// ex)
	// MyMatrix matWorld;
	// matWorld.Identity();
	void Identity() { D3DXMatrixIdentity(this); }

	// 전치 행렬을 만드는 메서드입니다.
	// ex)
	// MyMatrix matView;
	// matView.Transpose();
	void Transpose() { D3DXMatrixTranspose(this, this); }

	// 역행렬을 만드는 메서드입니다. 
	// 역행렬이 존재하지 않는 경우 현재 행렬이 변하지 않고 false를 반환합니다.
	// ex)
	// MyMatrix matView;
	// bool bSuccess = matView.Inverse();
	bool Inverse()
	{
		_float det; // 역행렬 판단하기 위해서 선언된 변수
		return D3DXMatrixInverse(this, &det, this) != nullptr; // true나 false를 반환
	}

	// YawPitchRoll로 회전하는 메서드입니다.
	// ex)
	// MyMatrix matRot;
	// matRot.RotationYawPitchRoll(10.f, 20.f, 30.f);
	void RotationYawPitchRoll(_float yaw, _float pitch, _float roll)
	{
		D3DXMatrixRotationYawPitchRoll(this, yaw, pitch, roll);
	}

	// D3DXMatrixRotationX 래핑 버전입니다.
	// ex)
	// MyMatrix matRot;
	// matRot.D3DXMatrixRotationX(30.f);
	void RotationX(_float fAngle)
	{
		D3DXMatrixRotationX(this, fAngle);
	}

	// D3DXMatrixRotationY 래핑 버전입니다.
	// ex)
	// MyMatrix matRot;
	// matRot.D3DXMatrixRotationY(30.f);
	void RotationY(_float fAngle)
	{
		D3DXMatrixRotationY(this, fAngle);
	}

	// D3DXMatrixRotationZ 래핑 버전입니다.
	// ex)
	// MyMatrix matRot;
	// matRot.D3DXMatrixRotationZ(30.f);
	void RotationZ(_float fAngle)
	{
		D3DXMatrixRotationZ(this, fAngle);
	}

	// D3DXMatrixRotationAxis래핑 버전입니다.
	// ex)
	// MyMatrix matRot;
	// MyVec3 vRight;
	// matRot.RotationAxis(&vRight, 30.f);
	MyMatrix* RotationAxis(_vec3* vAxis, _float fAngle)
	{
		return reinterpret_cast<MyMatrix*>(D3DXMatrixRotationAxis(this, vAxis, D3DXToRadian(fAngle)));
	}

	// D3DXMatrixScaling의 래핑버전입니다.
	// ex)
	// MyMatrix matScale;
	// matScale->Scaling(x, y, z);
	void Scaling(_float x, _float y, _float z)
	{
		D3DXMatrixScaling(this, x, y, z);
	}

	// D3DXMatrixTranslation의 래핑버전입니다.
	// ex)
	// MyMatrix matTrans;
	// matTrans->Translation(x, y, z);
	void Translation(_float x, _float y, _float z)
	{
		D3DXMatrixTranslation(this, x, y, z);
	}

	// 뷰행렬을 만드는 메서드입니다.
	// ex)
	// MyMatrix matView;
	// matView.LookAtLH();
	void LookAtLH(D3DXVECTOR3* eye, D3DXVECTOR3* at, D3DXVECTOR3* up)
	{
		D3DXMatrixLookAtLH(this, eye, at, up);
	}

	// 투영행렬을 만드는 메서드입니다.
	// ex)
	// MyMatrix matProj;
	// matProj.PerspectiveFovLH();
	void PerspectiveFovLH(_float fov = D3DXToRadian(60.f), _float aspect = (WINCX / WINCY), _float zn = 1.f, _float zf = 1000.f)
	{
		D3DXMatrixPerspectiveFovLH(this, fov, aspect, zn, zf);
	}

	// 직교행렬을 만드는 메서드입니다.
	// ex)
	// MyMatrix matOrtho;
	// matOrtho.OrthoLH();
	void OrthoLH(_float width = WINCX, _float height = WINCY, _float zn = 1.f, _float zf = 1000.f)
	{
		D3DXMatrixOrthoLH(this, width, height, zn, zf);
	}

	// 빌보드 행렬을 만드는 메서드 입니다.
	// 인자로 빌보드 패턴을 적용할 객체의 월드 행렬을 넣어주세요.
	void BillBoard(LPDIRECT3DDEVICE9 pGraphicDev)
	{
		_matrix	matView;

		pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

		D3DXMatrixIdentity(this);

		this->_11 = matView._11;
		this->_13 = matView._13;
		this->_31 = matView._31;
		this->_33 = matView._33;

		D3DXMatrixInverse(this, 0, this);
	}
}_matrix;
