package com.testcode.library;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.KeyEvent;

public class TestCodeActivity extends Activity {
	private static TestCodeActivity _currentActivity;

	static {
		System.loadLibrary("testcode");
		System.loadLibrary("fruitmatch");

	}
	TCRender _render;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		_currentActivity = this;
		SystemInfo.init();

		GLSurfaceView view = new TCGLSurfaceView(this);
		_render = new TCRender();
		view.setRenderer(_render);
		setContentView(view);
	}

	public static TestCodeActivity currentActivity() {
		return _currentActivity;
	}

	public void onDestroy() {
		if(_render!=null){
			_render.nativeDestroy();
		}
		_currentActivity = null;
		super.onDestroy();
		System.exit(0);
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			finish();
			return true;
		}
		return super.onKeyDown(keyCode, event);
	}

}