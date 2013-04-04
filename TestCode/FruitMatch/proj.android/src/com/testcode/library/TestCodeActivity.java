package com.testcode.library;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

public class TestCodeActivity extends Activity {
	private static TestCodeActivity _currentActivity;
	
	static {
		System.loadLibrary("testcode");
		System.loadLibrary("fruitmatch");
		
	} 
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        _currentActivity=this;
        SystemInfo.init();
        
        GLSurfaceView view=new TCGLSurfaceView(this);
        view.setRenderer(new TCRender());
        setContentView(view);
    }
    
    public static TestCodeActivity currentActivity(){
    	return _currentActivity;
    }
    
    public void onDestroy(){
    	super.onDestroy();
    	_currentActivity=null;
    }
    
}