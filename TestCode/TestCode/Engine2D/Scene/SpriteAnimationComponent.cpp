#include "SpriteAnimationComponent.h"

FrameSequence::FrameSequence(){
	_regionArray=vector<TextureRegion*>();
}

FrameSequence::FrameSequence(int capacity){
	_regionArray=vector<TextureRegion*>(capacity);
}
FrameSequence::FrameSequence(TextureRegion** regions,int size){
	for(int i=0;i<size;i++){
		regions[i]->retain();
	}
	_regionArray=vector<TextureRegion*>(regions,regions+size-1);
}
FrameSequence::~FrameSequence(){
	vector<TextureRegion*>::iterator it;
	for(it=_regionArray.begin();it!=_regionArray.end();it++){
		(*it)->release();
	}
	_regionArray.clear();
}
FrameSequence* FrameSequence::add(TextureRegion* region){
	region->retain();
	_regionArray.push_back(region);
	return this;
}