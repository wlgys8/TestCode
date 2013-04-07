#include "ui/AnimationData.h"

AnimationCurve AnimationData::dialogShow;

void AnimationData::init(){
	dialogShow.setWrapMode(CurveWrapClamp);
	dialogShow.addKey(0,0.0f);
	dialogShow.addKey(0.5f,1.2f);
	dialogShow.addKey(0.75f,0.9f);
	dialogShow.addKey(1.0f,1);
}