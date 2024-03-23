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
		
	}
	
	boolean Or()
	{
		
	}
	
	boolean AndAnd()
	{
		
	}
	
	boolean And()
	{
		
	}
	
	boolean xOr()
	{
		
	}
	
	boolean Equ()
	{
		
	}
	
	boolean Compare()
	{
		
	}
	
	boolean Shift()
	{
		
	}
	
	boolean Factor()
	{
		
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