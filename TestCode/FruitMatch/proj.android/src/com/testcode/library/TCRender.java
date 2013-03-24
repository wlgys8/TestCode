package com.testcode.library;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;

public class TCRender implements Renderer{ 

	@Override
	public void onDrawFrame(GL10 gl) {
		nativeRender();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		nativeInit(width,height);
		
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		
	}
	
	
	public native void nativeInit(int width,int height);
	public native void nativeRender();

}
