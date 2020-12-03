package Projekat2;

public class Fraction {
	public long imenilac = 1, brojilac = 0;
	public Fraction() { }
	public Fraction(long brojilac, long imenilac) {
		this.imenilac = imenilac;
		this.brojilac = brojilac;
	}
	public boolean isEqual(Fraction f) {
		return brojilac*f.imenilac == imenilac*f.brojilac;
	}
	public void add(Fraction f) {
		imenilac = brojilac*f.imenilac + f.brojilac*imenilac;
		brojilac = imenilac * f.imenilac;
	}
	public boolean greaterThen(Fraction f) {
		return brojilac*f.imenilac > imenilac*f.brojilac;
	}
	public boolean greaterAndEqualThen(Fraction f) {
		return brojilac*f.imenilac >= imenilac*f.brojilac;
	}
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(brojilac);sb.append("/");sb.append(imenilac);
		return sb.toString();
	}
	
}
