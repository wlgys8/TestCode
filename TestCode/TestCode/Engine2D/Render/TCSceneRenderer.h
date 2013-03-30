#ifndef __TC_SCENERENDERER_H__
#define __TC_SCENERENDERER_H__
#include "TCSingleton.h"
#include "TCVector2f.h"
#include "TCPaint.h"
NS_TC_BEGIN
class TCSceneRenderer{
private:
	float* _vertexBuffer;
	float* _uvBuffer;
	unsigned char* _colorBuffer;
	unsigned short* _indicesBuffer;
	~TCSceneRenderer();
	TCSceneRenderer();
	int _startBatchIndex;
	int _size;
	int _lastTextureID;
	int _capacity;
	Paint _lastPaint;
	void drawBatch(const Paint& paint);
	void checkAndExpand();
public:

	void render(const int& textureID,Vector2f* vertex,Vector2f* uv, const Paint& paint);

	void flush();

	static TCSceneRenderer* instance();
};
NS_TC_END
#endif