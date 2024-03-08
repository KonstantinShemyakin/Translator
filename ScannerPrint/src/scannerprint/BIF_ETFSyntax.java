package scannerprint;

public class BIF_ETFSyntax {
	private TScanner parent_scanner = null;
	
	public BIF_ETFSyntax(TScanner parent) { parent_scanner = parent; } 
	
	public boolean Z() {
		if (!E() || !parent_scanner.Match(Lexemme.TGroup.Eof)) return false;
		return true;
	}
	
	public boolean E() {
		do {
			if (!T()) return false;	   
		} while (parent_scanner.Match(Lexemme.TGroup.Oper, Lexemme.TType.Add) || 
				 parent_scanner.Match(Lexemme.TGroup.Oper, Lexemme.TType.Sub));
		return true;
	}
	
	public boolean T() {
		do {
			if (!F()) return false;	   
		} while (parent_scanner.Match(Lexemme.TGroup.Oper, Lexemme.TType.Multi) || 
				 parent_scanner.Match(Lexemme.TGroup.Oper, Lexemme.TType.Div));
		return true;
	}
	
	public boolean F() {
		if (parent_scanner.Match(Lexemme.TGroup.Ident)) return true;
		if (parent_scanner.Match(Lexemme.TGroup.Integer)) return true;
		if (parent_scanner.Match(Lexemme.TGroup.Number)) return true;
		if (parent_scanner.Match(Lexemme.TType.LeftBracket) && E() && parent_scanner.Match(Lexemme.TType.RightBracket)) return true;
		return false;
	}
}