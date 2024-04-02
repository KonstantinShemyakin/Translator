package scannerprint;

public class PSyntax {
	public TScanner parent_scanner = null;
	
	public PSyntax(TScanner parent) { parent_scanner = parent; }
	
	// All 13 priorities + constructs
	
	boolean Assign()
	{
		if (!Question()) return false;
		if (parent_scanner.Match(Lexemme.TPriority.Assign)) {
			return Assign();
		}
		return true;
	}
	
	boolean Question()
	{
		//#ifndef EXPRESION_BINARY
		if (!OrOr()) return false;
		//#else
		if (!Binary(Lexemme.TPriority.OrOr)) return false;
		//#endif
		if (parent_scanner.Match(Lexemme.TPriority.Question)) {
			if (!Expressions()) return false;
			if (!MatchMust(T_Symbol::lxColon)) return false; 
			// MatchMust - разобраться что это
			return Question();
		}
		return true;
	}
	
	boolean OrOr()
	{
            if (!AndAnd()) return false;
	    while (parent_scanner.Match(Lexemme.TPriority.OrOr)) {
		if (!AndAnd()) return false;
            }
	    return true;
	}
	
	boolean Or()
	{
		if (!XOr()) return false;
	    while (parent_scanner.Match(Lexemme.TPriority.Or)) {
			if (!XOr()) return false;
		}
	    return true;
	}
	
	boolean AndAnd()
	{
		if (!Or()) return false;
	    while (parent_scanner.Match(Lexemme.TPriority.AndAnd)) {
		   if (!Or()) return false;
		}
	    return true;
	}
	
	boolean And()
	{
	    if (!Equ()) return false;
	    while (parent_scanner.Match(Lexemme.TPriority.And)) {
			if (!Equ()) return false;
		}
	    return true;
	}
	
	boolean xOr()
	{
		if (!And()) return false;
	    while (parent_scanner.Match(Lexemme.TPriority.XOr)) {
			if (!And()) return false;
		}
	    return true;
	}
	
	boolean Equ()
	{
		if (!Compare()) return false;
		while (parent_scanner.Match(Lexemme.TPriority.Equ)) {
			if (!Compare()) return false;
		}
		return true;
	}
	
	boolean Compare()
	{
		if (!Shift()) return false;
	    while (parent_scanner.Match(Lexemme.TPriority.Compare)) {
			if (!Shift()) return false;
		}
	    return true;
	}
	
	boolean Shift()
	{
		if (!Term()) return false;
	    while (parent_scanner.Match(Lexemme.TPriority.Shift)) {
			if (!Term()) return false;
		}
	    return true;
	}
	
	boolean Factor()
	{
		if (!Factor()) return false;
		while (parent_scanner.Match(Lexemme.TPriority.Term)) {
			if (!Factor()) return false;
		}
	    return true;
	}
	
	boolean Unary()
	{
		
	}
	
	boolean Primary()
	{
		
	}
	
	boolean Binary()
	{
		
	}
	
	boolean Statements()
	{
		
	}
	
	boolean Statement()
	{
		
	}
	
	boolean Translate()
	{
		
	}
	
	boolean Expressions()
	{
		
	}
	
	boolean Compaund()
	{
		
	}
	
	boolean DefineParam()
	{
		
	}
	
	boolean DefineParams()
	{
		
	}
	
	boolean InitializerItem()
	{
		
	}
	
	boolean Initializer()
	{
		 
	}
	
	boolean For()
	{
		
	}
	
	boolean While()
	{
		
	}
	
	boolean If()
	{
		
	}
	
	boolean Do()
	{
		
	}
	
	boolean GoTo()
	{
		
	}
	
	boolean Continue()
	{
		
	}
	
	boolean Break()
	{
		
	}
	
	boolean Return()
	{
		
	}
	
	boolean Switch()
	{
		
	}
}