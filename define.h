#pragma once

#define SINGLE(type) public:\
                     static type* GetInst()\
                  {\
                     static type mgr;\
                        return &mgr;\
                  }\
                private:\
                   type();\
                   ~type();\

#define fDT CTimeMgr::GetInst()->GetfDT();
#define DT CTimeMgr::GetInst()->GetDT();

#define CLONE(type) type* Clone() {return new type(*this);}

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define TILE_SIZE 64

#define PI 3.1415926535f





enum class GROUP_TYPE
{
    DEFALUT,
    TILE,
    GROUND,
    MONSTER,
    PLAYER,
 
    PROJ_PLAYER,
    PROJ_MONSTER,



    UI = 31,
    END=32,
};

enum class SCENE_TYPE
{
    TOOL,
    START,
    STAGE_01,
    STAGE_02,
    

    END,
};


enum class BRUSH_TYPE
{
    HOLLOW,
    BLACK,
    END,
};

enum class PEN_TYPE
{
    RED,
    GREEN,
    BLUE,
    BLACK,
    WHITE,
    END,

};

enum class EVENT_TYPE
{
    CREATE_OBJECT,
    DELETE_OBJECT,
    SCENE_CHANGE,
    CHANCE_AI_STATE,


    END,
};

enum class MON_STATE
{
    IDLE,
    PATROL,
    TRACE,
    ATT,
    RUN,
    DEAD,

    END,
    
};