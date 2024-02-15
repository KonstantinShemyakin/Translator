package LL1;

//Версия 12.08.2010
import java.util.*;
import java.io.*;

public class LL1 {
	HashMap Grammar = new HashMap();
	/* Для каждого нетерминала Набор отображений номер правила -> правая часть */
	HashSet Nonterms = new HashSet(), Terminals = new HashSet();
	/* Для каждого нетерминала его правые части */
	StreamTokenizer tok;
	String Axiom;
	HashMap NTermsFirst = new HashMap();
	int ruleNumber = 1;
	HashMap RHSFirsts = new HashMap();
	HashMap FOLLOWs = new HashMap();
	HashMap parseTable = new HashMap();

	/* Для каждого нетерминала для входного символа дает номер правила */
	/** *************************************************************** */
	void showSet(String n, HashSet s) {
		System.out.print(n + "=");
		System.out.println(s);
	}

	/** *************************************************************** */
	void showList(String n, LinkedList s) {
		System.out.print(n + "=");
		System.out.println(s);
	}

	/** *************************************************************** */
	HashSet Firsts(LinkedList rightHandSide) {
		boolean flag = true;
		showSet("word ", new HashSet(rightHandSide));
		Iterator rhi = rightHandSide.iterator();
		int size = rightHandSide.size();
		HashSet curFirst = new HashSet();
		while (size > 0) {
			String nextSym = (String) rhi.next();
			if (Terminals.contains(nextSym)) {
				size = 0;
				curFirst.add(nextSym);
			} else {
				boolean eps;
				size--;
				if (nextSym.equals("$"))
					eps = true;
				else {
					HashSet NTfirst = (HashSet) NTermsFirst.get(nextSym);
					curFirst.addAll(NTfirst);
					eps = NTfirst.contains("$");
				}
				if (!eps)
					size = 0;
				else if (size != 0)
					curFirst.remove("$");
				else
					curFirst.add("$");
			}
		}
		return curFirst;
	}

	/** ****************************************************************** */
	public void FirstConstructor() {
		Iterator i = Nonterms.iterator();
		while (i.hasNext())
			NTermsFirst.put((String) i.next(), new HashSet());
		boolean flag = true;
		HashSet NTfirst = new HashSet();
		String lhs;
		while (flag) {
			flag = false;
			i = Nonterms.iterator();
			while (i.hasNext()) {
				lhs = (String) i.next();
				HashSet rhs = new HashSet(((HashMap) Grammar.get(lhs)).values());
				/* Набор списков правых частей */
				Iterator rhsi = rhs.iterator();
				while (rhsi.hasNext()) {
					LinkedList rightHandSide = (LinkedList) rhsi.next();
					showSet("Rule " + lhs, new HashSet(rightHandSide));
					Iterator rhi = rightHandSide.iterator();
					int size = rightHandSide.size();
					while (size > 0) {
						String nextSym = (String) rhi.next();
						HashSet curFirst = (HashSet) NTermsFirst.get(lhs);
						if (Terminals.contains(nextSym)) {
							size = 0;
							if (!curFirst.contains(nextSym)) {
								curFirst.add(nextSym);
								flag = true;
							}
						} else {
							boolean eps;
							size--;
							if (nextSym.equals("$"))
								eps = true;
							else {
								NTfirst = (HashSet) NTermsFirst.get(nextSym);
								eps = NTfirst.remove("$");
								if (!eps)
									size = 0;
								if (!curFirst.containsAll(NTfirst)) {
									curFirst.addAll(NTfirst);
									flag = true;
								}
							}
							if (eps & size == 0) {
								curFirst.add("$");
							}
						}
					}
				}
			}
		}
		i = Nonterms.iterator();
		while (i.hasNext()) {
			lhs = (String) i.next();
			showSet("First 2 " + lhs, new HashSet((HashSet) NTermsFirst
					.get(lhs)));
		}
	}

	/** *************************************************************** */
	void FollowConstructor() {
		String lhs;
		Iterator i = Nonterms.iterator();
		/* Строим FOLLOW */
		while (i.hasNext())
			FOLLOWs.put((String) i.next(), new HashSet());
		((HashSet) FOLLOWs.get(Axiom)).add("#");

		i = Nonterms.iterator();
		while (i.hasNext()) {
			lhs = (String) i.next();
			HashMap lhsMaps = (HashMap) Grammar.get(lhs);
			/*
			 * Для каждого нетерминала Набор отображений номер правила -> правая
			 * часть
			 */
			HashSet maps = new HashSet(lhsMaps.entrySet());
			Iterator itr = maps.iterator();
			/* Итератор по правилам */
			while (itr.hasNext()) {
				Map.Entry me = (Map.Entry) itr.next();

				LinkedList rightHandSide = (LinkedList) me.getValue();
				showSet("Rule " + lhs, new HashSet(rightHandSide));
				Iterator rhi = rightHandSide.iterator();
				int size = rightHandSide.size();
				int length = 1;
				while (rhi.hasNext()) {
					String nextSym = (String) rhi.next();
					if (Nonterms.contains(nextSym) & size != length) {
						LinkedList beta = new LinkedList(rightHandSide.subList(
								length, size));
						showSet("sub rhs ", new HashSet(beta));
						HashSet betaFirst = Firsts(beta);

						HashSet rhsf = ((HashSet) FOLLOWs.get(nextSym));
						rhsf.addAll(betaFirst);
						rhsf.remove("$");
						showSet("Follow " + nextSym, (HashSet) FOLLOWs
								.get(nextSym));
					}
					length++;
				}
			}
		}
		i = Nonterms.iterator();
		while (i.hasNext()) {
			lhs = (String) i.next();
			showSet("FOLLOW " + lhs, new HashSet((HashSet) FOLLOWs.get(lhs)));
		}
		boolean flag = true;
		while (flag) {
			i = Nonterms.iterator();
			while (i.hasNext()) {
				flag = false;
				lhs = (String) i.next();
				HashSet rhs = new HashSet(((HashMap) Grammar.get(lhs)).values());
				/* Набор списков правых частей */
				Iterator rhsi = rhs.iterator();
				while (rhsi.hasNext()) {
					LinkedList rightHandSide = (LinkedList) rhsi.next();
					showSet("Rule " + lhs, new HashSet(rightHandSide));
					Iterator rhi = rightHandSide.iterator();
					int size = rightHandSide.size();
					int length = 1;
					while (rhi.hasNext()) {
						String nextSym = (String) rhi.next();
						HashSet betaFirst = null;
						if (Nonterms.contains(nextSym)) {
							if (size != length) {
								LinkedList beta = new LinkedList(rightHandSide
										.subList(length, size));
								showSet("beta ", new HashSet(beta));
								betaFirst = Firsts(beta);
								showSet("betaFirst ", betaFirst);
							}
							if (size == length || betaFirst.contains("$")) {
								betaFirst = (HashSet) FOLLOWs.get(nextSym);
								if (!betaFirst.containsAll((HashSet) FOLLOWs
										.get(lhs))) {
									betaFirst
											.addAll((HashSet) FOLLOWs.get(lhs));
									showSet("Follow " + nextSym,
											(HashSet) FOLLOWs.get(nextSym));
									flag = true;
								}
							}
						}
						length++;
					}
				}
			}
		}
	}

	/** *************************************************************** */
	void TableConstructor() {
		Iterator i = Nonterms.iterator();
		while (i.hasNext())
			parseTable.put((String) i.next(), new HashMap());
		i = Nonterms.iterator();
		while (i.hasNext()) {
			String lhs = (String) i.next();
			HashMap lhsMaps = (HashMap) Grammar.get(lhs);
			/*
			 * Для каждого нетерминала Набор отображений номер правила -> правая
			 * часть
			 */
			HashSet maps = new HashSet(lhsMaps.entrySet());
			/*
			 * Набор отображений номер правила -> правая часть
			 */
			Iterator itr = maps.iterator();
			HashMap symToRn = (HashMap) parseTable.get(lhs);
			/* Итератор по правилам */
			while (itr.hasNext()) {
				Map.Entry me = (Map.Entry) itr.next();
				Integer rn = (Integer) me.getKey();
				HashSet rhsfirsts = (HashSet) RHSFirsts.get(rn);
				showSet(rn + " ", rhsfirsts);
				Iterator rhsitr = rhsfirsts.iterator();
				while (rhsitr.hasNext()) {
					String nextSym = (String) rhsitr.next();
					if (!nextSym.equals("$")) {
						symToRn.put(nextSym, rn);
						System.out.println("Table " + lhs + " " + nextSym + " "
								+ rn);
					} else {
						HashSet lhsfollows = (HashSet) FOLLOWs.get(lhs);
						Iterator lhsitr = lhsfollows.iterator();
						while (lhsitr.hasNext()) {
							nextSym = (String) lhsitr.next();
							symToRn.put(nextSym, rn);
							System.out.println("Table " + lhs + " " + nextSym
									+ " " + rn);
						}
					}
				}
			}
		}
	}

	/** *************************************************************** */
	class syntaxError extends Exception {
		syntaxError() {
			System.out.println("Синтаксическая ошибка:");
		}
	}

	/** *************************************************************** */
	public void LL1Parser(InputStreamReader inputReader) throws IOException {
		try {
			LinkedList stack = new LinkedList();
			String top;
			tok = new StreamTokenizer(inputReader);
			tok.resetSyntax();
			tok.wordChars(33, 255);
			tok.whitespaceChars(0, ' ');
			tok.eolIsSignificant(false);
			tok.nextToken();
			stack.add("#");
			stack.addFirst(Axiom);
			do {
				top = (String) stack.getFirst();
				if (Terminals.contains(top))
					if (top.equals(tok.sval)) {
						System.out.println("Shift "+ top);
						stack.removeFirst();
						top = (String) stack.getFirst();
						tok.nextToken();
					} else
						throw new syntaxError();
				else if (Nonterms.contains(top)) {
					HashMap tableRow = (HashMap) parseTable.get(top);
					Integer rule = (Integer) tableRow.get(tok.sval);
					System.out.println("Rule "+rule);
					stack.removeFirst();
					HashMap rhss = (HashMap) Grammar.get(top);
					LinkedList rhs = (LinkedList) rhss.get(rule);
					int length = rhs.size();
					String first = (String) rhs.getFirst();
					if (!(length == 1 & first.equals("$")))
						while (length > 0)
							stack.addFirst((String) rhs.get(--length));
				} else if (!top.equals("#"))
					throw new syntaxError();
			} while (!top.equals("#"));
			if (!tok.sval.equals("#"))
				throw new syntaxError();
		} catch (syntaxError e) {
		}
	}

	/** *************************************************************** */

	LL1(Reader r) throws IOException {
		tok = new StreamTokenizer(r);
		tok.resetSyntax();
		tok.wordChars(33, 255);
		tok.whitespaceChars(0, ' ');
		tok.eolIsSignificant(false);
		tok.nextToken();
		while (!(tok.sval).equals(";")) {
			Terminals.add(tok.sval);
			tok.nextToken();
		}
		tok.nextToken();
		while (!(tok.sval).equals(";")) {
			Nonterms.add(tok.sval);
			tok.nextToken();
		}
		tok.nextToken();
		Axiom = new String(tok.sval);
		tok.nextToken();
		Iterator i = Nonterms.iterator();
		/*
		 * Для каждого нетерминала A строится функция A -> {Номер правила ->
		 * {правая часть}}
		 */
		while (i.hasNext())
			Grammar.put(new String((String) i.next()), new HashMap());
		while (tok.nextToken() != tok.TT_EOF) {
			LinkedList rightHandSide = new LinkedList();
			String lhs = new String(tok.sval);
			HashMap RHSs = (HashMap) Grammar.get(lhs);
			int j = ruleNumber, k;
			tok.nextToken();
			do {
				rightHandSide.add(tok.sval);
				tok.nextToken();
			} while (!(tok.sval).equals(";"));
			showList(lhs, rightHandSide);
			RHSs.put(new Integer(ruleNumber++), rightHandSide);
		}
		FirstConstructor();
		int j;
		for (j = 1; j <= ruleNumber; j++)
			RHSFirsts.put(new Integer(j), new HashSet());
		i = Nonterms.iterator();
		while (i.hasNext()) {
			HashMap lhsMaps = (HashMap) Grammar.get(i.next());
			HashSet maps = new HashSet(lhsMaps.entrySet());
			Iterator itr = maps.iterator();
			while (itr.hasNext()) {
				Map.Entry me = (Map.Entry) itr.next();
				Integer rn = (Integer) me.getKey();
				LinkedList ll = (LinkedList) me.getValue();
				HashSet rhsf = (HashSet) RHSFirsts.get(rn);
				rhsf.addAll(Firsts(ll));
			}
		}
		FollowConstructor();
		TableConstructor();
	}

	/** *************************************************************** */
	public static void main(String args[]) {
		try {
			String grammarFile = "e:/AutoLang/LL1/Grammar.9";
			FileInputStream GrammarStream = new FileInputStream(grammarFile);
			InputStreamReader GrammarReader = new InputStreamReader(
					GrammarStream);

			LL1 grammar = new LL1(GrammarReader);

			String input = "e:/AutoLang/LL1/10";
			FileInputStream inputStream = new FileInputStream(input);
			InputStreamReader inputReader = new InputStreamReader(inputStream);
			grammar.LL1Parser(inputReader);

		} catch (FileNotFoundException e) {
			System.out.println("File not found");
		} catch (IOException e) {
			System.out.println("Wrong input");
		}
	}
}