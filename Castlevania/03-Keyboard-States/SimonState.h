#pragma once

class CSimon;

class CSimonState
{
public:
    virtual void KeyUpHandle(CSimon* simon, int keyCode) = 0;
    virtual void KeyDownHandle(CSimon* simon, int keyCode) = 0;
    virtual void Update(CSimon* simon) = 0;
    virtual ~CSimonState() {};
};