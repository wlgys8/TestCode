#ifndef __TC_SPRITEANIMATIONCOMPONENT_H__
#define __TC_SPRITEANIMATIONCOMPONENT_H__
#include "BaseComponent.h"
#include "TextureRegion.h"
#include <string>
#include <vector>
using namespace std;
USING_NS_TC;
class FrameSequence:AutoReleaseObjectTemplete<FrameSequence>{

private:
	vector<TextureRegion*> _regionArray;
protected:
	FrameSequence();
	~FrameSequence();
	FrameSequence(int capacity);
	FrameSequence(TextureRegion** regions,int size);
public:
	FrameSequence* add(TextureRegion* region);

public:
	static FrameSequence* alloc(TextureRegion** regions,int size){
		FrameSequence* ret=new FrameSequence(regions,size);
		ret->autoRelease();
		return ret;
	}


};
class SpriteAnimationComponent:BaseComponent{
	typedef map<string,FrameSequence*> SequenceMap;
public:
	SequenceMap _sequenceMap;
	
private:
	int _frameIndex;
	int _sequenceIndex;
};
#endif