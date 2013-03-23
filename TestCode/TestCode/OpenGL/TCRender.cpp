#include "TCRender.h"
#include "AutoReleasePool.h"
#include "TCSceneRenderer.h"
#include "TCSceneManager.h"
#include "TCScreen.h"
NS_TC_BEGIN
TCRender::TCRender(){
}
TCRender::~TCRender(){
	DebugLog("destroy render");
}


void  TCRender::onResize(long width,long height){
	DebugLog("StartResize,width:%d,height,%d",width,height);
	Screen::resize(width,height);
	glViewport(0,0,width,height);
	glClearColor(1,0,0,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(-Screen::width()/2,Screen::width()/2,-Screen::height()/2,Screen::height()/2,-100,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisableClientState(GL_COLOR_ARRAY);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthFunc(GL_LEQUAL);	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	DebugLog("EndResize,width:%d,height,%d",width,height);
	
}

void  TCRender::onRender(){
	TCSceneManager::instance()->loopUpdate();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	TCSceneManager::instance()->loopDraw();
	TCSceneRenderer::instance()->flush();
	AutoReleasePool::instance()->releaseAll();
}

NS_TC_END