package com.testcode.library;

import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.util.Log;

public class SystemInfo {

	public static native void init();

	public static String getSourceDir() {
		String apkFilePath = "";
		ApplicationInfo appInfo = null;
		PackageManager packMgmr = TestCodeActivity.currentActivity()
				.getApplication().getPackageManager();
		try {
			appInfo = packMgmr.getApplicationInfo(TestCodeActivity
					.currentActivity().getPackageName(), 0);
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			throw new RuntimeException("Unable to locate assets, aborting...");
		}
		apkFilePath = appInfo.sourceDir;
		Log.e("apk path", apkFilePath);
		return apkFilePath;
	}

}
