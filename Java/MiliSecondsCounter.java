package Projekat2;

public class MiliSecondsCounter extends Thread {
	public boolean working = false,counting = false;
	public int counter = 0;
	public MiliSecondsCounter() { }
	public void run() {
		try {
			while(!isInterrupted()) {
				while(!working) {
					synchronized(this){
						wait();
					}
				}
				for(int i=0;i<600;i++) {
					while(!working) {
						synchronized(this) {
							wait();
						}
					}
					counter = i;
					sleep(100);
				}
				interrupt();
			}
		}catch(InterruptedException e) { }
	}
	public void startRunMethod() {
		start();
	}
	public void setWorking(boolean b) {
		synchronized(this) {
			working = b; 
			notify();
		}
	}
	public synchronized void stopCounting() {interrupt();} 
	public synchronized int getCounter() {return counter;}
}