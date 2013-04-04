package com.testcode.fruitmatch;

import android.os.Bundle;
import android.util.Log;

import com.testcode.library.TestCodeActivity;

public class FruitMatchActivity extends TestCodeActivity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		play();
	}

	public static int test(int p1, float p2, boolean p3, double p4) {
		Log.e("asd", "test:" + p1 + ":" + p2 + ":" + p3 + ":" + p4);
		return 2;
	}

	private native int play();
}