package scannerprint;

public class BIF_ETFSyntax {
	private TScanner parent_scanner = null;
	
	public BIF_ETFSyntax(TScanner parent) { parent_scanner = parent; } 
	
	public boolean Z() {
		if (!E() || !parent_scanner.Match(Lexemme.TGroup.Eof)) return false;
		return true;
	}
	
	public boolean E() {
		
	}
	
	public boolean T() {
		
	}
	
	public boolean F() {
		
	}
}