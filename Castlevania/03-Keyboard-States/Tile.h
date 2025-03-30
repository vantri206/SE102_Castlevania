#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "Textures.h"

class CTile : public CGameObject
{
protected:
	int left;
	int top;
	int right;
	int bottom;

public:
	CTile(float _x, float _y, int _left, int _top, int _right, int _bottom)
		: CGameObject(_x, _y), left(_left), top(_top), right(_right), bottom(_bottom)
	{
		width = right - left;
		height = bottom - top;
	};

	void Update(DWORD dt) override
	{

	};

	void Render() override;
};