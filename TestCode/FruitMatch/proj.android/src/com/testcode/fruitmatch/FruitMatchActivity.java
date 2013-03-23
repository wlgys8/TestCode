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
    
    public static int test(int p1,float p2,boolean p3,double p4){
    	Log.e("asd", "test:"+p1+":"+p2+":"+p3+":"+p4);
    	return 2;
    }
    private native int play();
}