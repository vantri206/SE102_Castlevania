#include "Gate.h"

CGate::CGate()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(GATEPORTAL_ANI_SET_ID));
	this->state = GATE_STATE_CLOSE;
	this->ani_id = ANI_ID_GATE_CLOSE;

	this->SetSize(GATE_CLOSE_WIDTH, GATE_CLOSE_HEIGHT);

	isActived = 0;
}

void CGate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD now = GetTickCount64();	

	if (state == GATE_STATE_OPEN && now - startOpen >= TRANSITION_SCENE_TIME)
	{
		this->ChangeScene();
		return;
	}
}

void CGate::Render()
{
	animation_set->at(ani_id)->Render(x, y, nx, width, height);
}

void CGate::LoadExtraSetting(vector<int> extra_settings)
{
	if (extra_settings.size() > 1)
	{
		sceneId = extra_settings[0];
		sceneEntryId = extra_settings[1];
	}
}

void CGate::Active()
{
	if (isActived) return;
	isActived = 1;
	startOpen = GetTickCount64();
	this->SetState(GATE_STATE_OPEN);
	this->SetAniId(ANI_ID_GATE_OPEN);
	this->SetSize(GATE_OPEN_WIDTH, GATE_OPEN_HEIGHT);
	this->SetPosition(this->x - (GATE_OPEN_WIDTH - GATE_CLOSE_WIDTH) / 2, this->y);
}

void CGate::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = (x - width * 3);
	r = (x + width / 2);
	t = (y + height / 2);
	b = (y - height / 2);
}