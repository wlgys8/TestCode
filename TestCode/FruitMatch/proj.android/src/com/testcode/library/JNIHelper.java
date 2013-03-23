package com.testcode.library;

import java.lang.reflect.Method;

public class JNIHelper {

	public static void main(String[] args){
	//	getSignatureByParam(JNIHelper.class, "getSignatureByParam", "");
	}
	
	public static String getSignatureByParam(Class<?> clazz,String methodName,String signature){
		try {
			Method[] methods=clazz.getMethods();
			for(int i=0;i<methods.length;i++){
				System.out.println(methods[i].toGenericString());
			}
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		return signature;
	}
}
