package com.testcode.fruitmatch;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class FruitMatchActivity extends Activity {
	static {
		System.loadLibrary("testcode");
		System.loadLibrary("fruitmatch");
		
	} 
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        play();
    }
    
    public static void test(){
    	Log.e("asd", "test");
    }
    private native int play();
}