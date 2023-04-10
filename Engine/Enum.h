﻿#pragma once

enum LOADINGID { LOADING_STAGE, LOADING_BOSS, LOADING_END };
enum WINMODE { MODE_FULL, MODE_WIN };

=======
enum LAYERID 
{ 
	LAYER_ENVIRONMENT,
	LAYER_OBSTACLE,
	LAYER_NPC,
	LAYER_MONSTER,
	LAYER_BOSS,
	LAYER_ITEM,
	LAYER_STATIC_END,

	//////////////////////////////// 위는 방에서 가져올 게임오브젝트들 리스트이다.

	LAYER_SKYBOX,
	LAYER_CAMERA,  
	LAYER_PLAYER,  
	LAYER_BULLET, 
	LAYER_SKILL, 
	LAYER_EFFECT,
	LAYER_UI,

	LAYER_DEBUG_MONSTER,
	LAYER_DEBUG_ITEM,

	LAYER_DYNAMIC_END
};


enum ANIMSTATE {
	// 애니메이션들의 상태들을 최대한 예측해봤음. 여기서 필요한것들만 가져다 쓰면 됨. 다른 경우가 있다면 넣어도 됨. 이 이넘값들을 애니메이션 컴포넌트에 바인딩하면 자동으로 애니메이션 출력함.
	ANIM_IDLE, ANIM_WALK, ANIM_RUN, ANIM_JUMP, ANIM_ATTACK, ANIM_ATTACK2, ANIM_ATTACK3, ANIM_DAMAGED, ANIM_DAMAGED2, ANIM_DAMAGED3, ANIM_FLY, ANIM_SHOT, ANIM_END};

enum COLGROUP
{
	/* 충돌 레이어임. 그룹별로 충돌 검사를 하기위해서 구분하였음. 콜라이더를 넣어줄때 (클론할때) 세번째 매개변수로 넣어도 되고 콜리전 매니져의 Change_ColGroup 함수를 써도 됨.*/
	COL_ENVIRONMENT = 0,
	COL_DETECTION = 1,
	COL_TRIGGER = 2,
	COL_ENEMY = 3,
	COL_OBJ = 4,
	COL_STATIC_END = 5,
	// 위 까지가 룸에 있을 정보들

	COL_PLAYER = 6,
	COL_PLAYERBULLET = 7,
	COL_ENEMYBULLET = 8,
	COL_DYNAMIC_END = 9
	// 위 까지가 동적인 콜라이더들
};

enum COLTYPE
{
	COL_STATIC,
	COL_DYNAMIC
};



enum COL_DIR
{
	/*	DIR_UP,DOWN: 월드좌표 y값으로 + 방향에서 충돌, - 방향에서 충돌
	DIR_RIGHT,LEFT: 월드좌표 x값으로 + 방향에서 충돌, - 방향에서 충돌
	DIR_FROMT,BACK: 월드좌표 z값으로 + 방향에서 충돌, - 방향에서 충돌 */
	DIR_UP = -1,
	DIR_DOWN = 1,
	DIR_LEFT = -2,
	DIR_RIGHT = 2,
	DIR_FRONT = -3,
	DIR_BACK = 3,
	DIR_END = 4
};

namespace Engine
{
	// ID_UPDATE: 업데이트랑 레이트 업데이트만 함.
	// ID_RENDER: 렌더만 부름.
	// ID_ALL: 둘다 함.
	// ID_STATIC: 아무것도 안함.
	enum COMPONENTID{ID_UPDATE, ID_RENDER, ID_ALL, ID_STATIC, ID_END };

	enum INFO {INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum ROTATION { ROT_X, ROT_Y, ROT_Z, ROT_END };
	enum TEXTYPE { TEX_NORMAL, TEX_CUBE, TEX_END };
	enum RENDERID { RENDER_PRIORITY, RENDER_ALPHA, RENDER_NONALPHA, RENDER_UI, RENDER_ALPHA_UI, RENDER_END };

	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };
	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	enum DOOR_DIR { DOOR_UP, DOOR_DOWN, DOOR_LEFT, DOOR_RIGHT };
}

//	UI
// 무기 ID
enum WEAPONTYPE
{
	BIGSHOT,
	EXPLOSIVESHOT,
	FLAMESHOT,
	RAPIDSHOT,
	SPREADSHOT,
	FREEZESHOT,
	LASERSHOT,
	WEAPONEND
};

// 미니맵 요소 ID
enum MAPELEMENT
{
	MINIMAPESWN,
	MINIMAPPOS,
	MINIMAPBLANKBLACK,
	MINIMAPBLANKGRAY,
	MINIMAPEND
};

// Room의 문 정보를 나타내는 ID
enum DOOR_TYPE
{
	DOOR_ES,
	DOOR_ESW,
	DOOR_EW,
	DOOR_N,
	DOOR_NE,
	DOOR_NES,
	DOOR_NESW,
	DOOR_NS,
	DOOR_NW,
	DOOR_S,
	DOOR_SW,
	DOOR_SWN,
	DOOR_W,
	DOOR_WNE,
	DOOR_E,
	DOOR_END
};