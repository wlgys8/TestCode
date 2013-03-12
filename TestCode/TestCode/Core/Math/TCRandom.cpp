#include <math.h>
#include <time.h>
#include "TCRandom.h"
#include <iostream>


NS_TC_BEGIN

bool Random::_hasSetSeed=false;

void Random::setSeed(int seed){
	srand(seed);
}
float Random::value(){
	if(!_hasSetSeed){
		setSeed(time(NULL));
		_hasSetSeed=true;
	}
	return rand()*1.0f/RAND_MAX;
}

float Random::between(float min,float max){
	return min+(max-min)*value();
}

NS_TC_END