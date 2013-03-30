package com.testcode.library;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

public class TCRender implements Renderer{ 

	private long time;
	@Override
	public void onDrawFrame(GL10 gl) {
		long deltaTime=System.currentTimeMillis()-time;
		if(!changed){
			nativeInit(480,800);
			changed=true;
		}
		nativeUpdateTime(deltaTime/1000f);
		nativeRender();
		time=System.currentTimeMillis();
	}

	private static boolean changed=false;
	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		time=System.currentTimeMillis();
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		
	}
	
	
	public native void nativeInit(int width,int height);
	public native void nativeRender();
	public native void nativeUpdateTime(float time);

}
