package com.qst.dms.dos;

public class Thread01 {
	
	public static void main(String[] args) {
		//ThreadTest tt = new ThreadTest();
		ThreadTest2 t = new ThreadTest2();
		Thread tt = new Thread(t);
		System.out.println("----主方法执行！----");
		tt.start();
		System.out.println("----主方法执行结束！----");
	}
}

class ThreadTest extends Thread{
	public void run() {
		for(int i=0;i<10;i++) {
			System.out.println(i);
		}
	}
}

class ThreadTest2 implements Runnable{
	public void run() {
		for(int i=0;i<10;i++) {
			System.out.println(i);
		}
	}
}