package com.testcode.library;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

public class TCGLSurfaceView extends GLSurfaceView {

	public TCGLSurfaceView(Context context) {
		super(context);
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent evt){
		return nativeDispatchEvent(evt.getAction(),evt.getX(),evt.getY());
	}

	private native boolean nativeDispatchEvent(int action,float x,float y);
}
