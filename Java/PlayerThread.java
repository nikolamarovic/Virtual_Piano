package Projekat2;

public class PlayerThread extends Thread{
	public MidiPlayer player;
	public Integer midi, duration;
	public PlayerThread(MidiPlayer player, Integer midi, Integer duration) {
		this.player = player;
		this.midi = midi;
		this.duration = duration;
		this.start();
	}
	@Override
	public void run() {
		try {
		while(!isInterrupted()) {
			player.play(midi);
			Thread.sleep(duration);
			player.release(midi);
		}
		}catch(InterruptedException e){ }
	
	}

}
