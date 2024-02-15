package LR1;

//Версия 04.05.2010
import java.util.*;
import java.io.*;

public class LR1 {
	HashMap GrammarR = new HashMap();
	/* Набор отображений номер правила -> Левая часть, правая часть */
	HashMap GrammarN = new HashMap();
	/* Для каждого нетерминала Набор отображений номер правила -> правая часть */
	HashSet Nonterms = new HashSet(), Terminals = new HashSet();

	StreamTokenizer tok;
	String Axiom;
	HashMap NTermsFirst = new HashMap();
	int ruleNumber = 1;
	int stateNumber = 1;
	LinkedList statesList = new LinkedList();
	/*
	 * Список необработанных состояний; содержит номера состояний из
	 * canonicalSystem
	 */
	HashMap canonicalSystem = new HashMap();
	/* Это отображение Номер состояния -> множество LR1 ситуаций */
	HashMap actionTable = new HashMap();
	/* Это отображение Номер состояния ->входной символ -> действие */
	HashMap gotoTable = new HashMap();

	/* Это отображение Номер состояния ->нетерминал -> состояние */

	/** *************************************************************** */
	class LR1Item {
		Integer ruleNumber, position;
		String lookAHead;

		int CompareTo(LR1Item arg) {
			int p11 = this.ruleNumber.intValue();
			int p12 = arg.ruleNumber.intValue();
			int p21 = this.position.intValue();
			int p22 = arg.position.intValue();
			int p31 = this.lookAHead.charAt(0);
			int p32 = arg.lookAHead.charAt(0);
			return (p11 - p12) * 1000000 + (p21 - p22) * 1000 + (p31 - p32);
		}

		LR1Item(int rn, int pos, String lAH) {
			ruleNumber = new Integer(rn);
			position = new Integer(pos);
			lookAHead = new String(lAH);
		}
	}

	/** *************************************************************** */
	class Rule {
		String lhs;
		LinkedList rhs;

		Rule(String l, LinkedList r) {
			lhs = l;
			rhs = r;
		}
	}

	/** *************************************************************** */
	class Action {
		boolean action;
		/* true - reduce, false - shift */
		Integer state;

		Action(boolean a, Integer s) {
			action = a;
			state = s;
		}
	}

	/** *************************************************************** */
	void showSet(String n, HashSet s) {
			System.out.print(n+"=");
			System.out.println(s);
	}

	/** *************************************************************** */
	void showState(Integer i, HashMap s) {
		System.out.println("showState ");
		Set hs = s.entrySet();
		Iterator iter = hs.iterator();
		while (iter.hasNext()) {
			Map.Entry me = (Map.Entry) iter.next();
			String r = (String) me.getKey();
			Action LAHAction = (Action) me.getValue();
			System.out
					.println("State " + i + " LAH " + r + " action "
							+ (LAHAction.action ? "reduce" : "shift")
							+ LAHAction.state);
		}
	}

	/** *************************************************************** */
	HashSet Firsts(LinkedList rightHandSide) {
		boolean flag = true;
//		showSet("word ", new HashSet(rightHandSide));
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
				HashSet rhs = new HashSet(((HashMap) GrammarN.get(lhs))
						.values());
				/* Набор списков правых частей */
				Iterator rhsi = rhs.iterator();
				while (rhsi.hasNext()) {
					LinkedList rightHandSide = (LinkedList) rhsi.next();
//					showSet("Rule " + lhs, new HashSet(rightHandSide));
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
//			showSet("First 2 " + lhs, new HashSet((HashSet) NTermsFirst
//					.get(lhs)));
		}
	}

	/** *************************************************************** */
	void showState(String s, TreeSet Iset) {
		/* Множество ситуаций */
		System.out.println(s);
		Iterator itr = Iset.iterator();
		while (itr.hasNext()) {
			LR1Item item = (LR1Item) itr.next();
			System.out.println("LR1Item Rule number" + item.ruleNumber
					+ " position " + item.position + " LAH " + item.lookAHead);
		}
	}

	/** *************************************************************** */
	void showGrammaR() {
		HashSet grammar = new HashSet(GrammarR.entrySet());
		Iterator i = grammar.iterator();
		while (i.hasNext()) {
			Map.Entry me = (Map.Entry) i.next();
			Rule r = (Rule) me.getValue();
			Integer n = (Integer) me.getKey();
//			System.out.print("Rule " + n + r.lhs);
//			showSet("rhs ", new HashSet(r.rhs));
		}
	}

	/** *************************************************************** */
	class ItemsCompare implements Comparator {
		public int compare(Object ii1, Object ii2) {
			LR1Item i1 = (LR1Item) ii1;
			LR1Item i2 = (LR1Item) ii2;
			int p11 = i1.ruleNumber.intValue();
			int p12 = i2.ruleNumber.intValue();
			int p21 = i1.position.intValue();
			int p22 = i2.position.intValue();
			int p31 = i1.lookAHead.charAt(0);
			int p32 = i2.lookAHead.charAt(0);
			return (p11 - p12) * 1000000 + (p21 - p22) * 1000 + (p31 - p32);
		}
	}

	/** *************************************************************** */
	int lookUpStates(TreeSet Iset) {
		int i;
//		showState("lookUpStates 1 ", Iset);
		for (i = 1; i < canonicalSystem.size(); i++) {
			TreeSet s = (TreeSet) canonicalSystem.get(new Integer(i));
//			showState("lookUpStates 2 ", s);
			if (Iset.size() == s.size()) {
				LinkedList l1 = new LinkedList(Iset);
				LinkedList l2 = new LinkedList(s);
				int j;
				boolean sign = true;
				for (j = 0; j < Iset.size(); j++) {
					LR1Item item1 = (LR1Item) l1.get(j);
					// System.out.println("LR1Item 1 Rule number" +
					// item1.ruleNumber
					// + " position " + item1.position + " LAH " +
					// item1.lookAHead);
					LR1Item item2 = (LR1Item) l2.get(j);
					// System.out.println("LR1Item 2 Rule number" +
					// item2.ruleNumber
					// + " position " + item2.position + " LAH " +
					// item2.lookAHead);
					if (item1.CompareTo(item2) != 0) {
						sign = false;
						break;
					}
				}
				if (sign)
					return i;
			}
		}
		return -1;
	}

	/** *************************************************************** */
	Integer closure(TreeSet Iset) {
		LinkedList itemsList = new LinkedList(Iset);
		HashMap LAHmap = null;
//		showGrammaR();
		while (!itemsList.isEmpty()) {
			boolean reduce = true;
			LR1Item currItem = (LR1Item) itemsList.getFirst();
			/* Очередная ситуация */
			Rule rule = (Rule) GrammarR.get(currItem.ruleNumber);
			/* Взяли правило по номеру */
			String LAH = currItem.lookAHead;
			int position = currItem.position.intValue();
			/* Позиция в ситуации */
			LinkedList rhs = (LinkedList) rule.rhs;
			/* Правая часть правила */
			HashSet firstLAH = null;
			String nextSym = null;
			if ((rhs.size() > position)) {
				// reduce = false;
				nextSym = (String) rhs.get(position);
				/* Символ после точки */
				if (!(nextSym.equals("$") & rhs.size() == 1)) {
					reduce = false;
					if (Nonterms.contains(nextSym)) {
						/*
						 * Перебрать все правила с этой левой частью и проверить
						 * наличие ситуации lhs->.rhs, FIRST(rhs.LAH)
						 */
						if (rhs.size() > position + 1) {
							firstLAH = new HashSet(Firsts(new LinkedList(rhs
									.subList(position + 1, rhs.size()))));
							if (firstLAH.contains("$")) {
								firstLAH.remove("$");
								firstLAH.add(LAH);
							}
						} else {
							firstLAH = new HashSet();
							firstLAH.add(LAH);
						}
						/* FIRST(beta.LAH) */
						HashMap RHSs = (HashMap) GrammarN.get(nextSym);
						HashSet RHSme = new HashSet(((HashMap) GrammarN
								.get(nextSym)).entrySet());
						/*
						 * Получили множество отображений номер правила ->
						 * правая часть
						 */
						Iterator itr = RHSme.iterator();
						/* Итератор по парам (номер правила -> правая часть) */
						while (itr.hasNext()) {
							Map.Entry me = (Map.Entry) itr.next();
							Integer rn = (Integer) me.getKey();
							/*
							 * Перебрать все ситуации и проверить нет ли
							 * ситуации (rn, 0, LAH)
							 */
							/* Для каждого правила и каждой LAH */
							boolean flag = false;
							LR1Item item;
							Iterator firstIt = firstLAH.iterator();
							while (firstIt.hasNext()) {
								String lah = (String) firstIt.next();
								Iterator it = Iset.iterator();
								while (it.hasNext() & !flag) {
									LR1Item nextItem = (LR1Item) it.next();
									if (lah.equals(nextItem.lookAHead)
											& (nextItem.ruleNumber
													.compareTo(rn) == 0)
											& (nextItem.position.intValue() == 0))
										flag = true;
								}
								if (!flag) {
									item = new LR1Item(rn.intValue(), 0, lah);
									itemsList.addLast(item);
									Iset.add(item);
//									showState("1:", Iset);
									// flag = true;
								}
							}
						}
					}
				}
			}
			itemsList.removeFirst();
			if (reduce) {
				/* Сформировать действие Reduce */
				if (LAHmap == null)
					LAHmap = new HashMap();
				if (LAHmap.containsKey(LAH))
					System.out.println("Грамматика не LR(1)LAH " + LAH
							+ " rule number " + currItem.ruleNumber);
				LAHmap.put(LAH, new Action(true, currItem.ruleNumber));
				/* действие reduce */
			}
		}
//		showState("2:", Iset);
		// Может быть это состояние уже есть?*/
		int stateN = lookUpStates(Iset);
		Integer state;
		if (stateN == -1) {
			/* Новое состояние */
			state = new Integer(stateNumber);
			stateNumber++;
			statesList.addLast(state);
			canonicalSystem.put(state, Iset);
			// gotoTable.put(state, null);
			if (LAHmap != null) {
//				showState(state, LAHmap);
				actionTable.put(state, LAHmap);
//				showResultSystem();
			}
			/* Все Reduce в данном состоянии */
		} else
			state = new Integer(stateN);
		return state;
	}

	/** *************************************************************** */
	void goTo(Integer state) {
		TreeSet Iset = (TreeSet) canonicalSystem.get(state);
		Iterator itr = Iset.iterator();
		HashMap symToItems = new HashMap();
		/*
		 * Здесь хранятся отображения символ -> множество ситуаций с продвинутым
		 * этим символом
		 */
		while (itr.hasNext()) {
			LR1Item currItem = (LR1Item) itr.next();
			Rule rule = (Rule) GrammarR.get(currItem.ruleNumber);
			int position = currItem.position.intValue();
			LinkedList rhs = (LinkedList) rule.rhs;
//			showSet("Goto ", new HashSet(rhs));
			if (position < rhs.size()) {
				String nextSym = (String) rhs.get(position);
				TreeSet itemsSet;
//				showGrammaR();
				/* Множество ситуаций с одинаковым символом перед точкой */
				if (!((rhs.size() == 1 & nextSym.equals("$")))
						& position != rhs.size()) {
					LR1Item newItem = new LR1Item(currItem.ruleNumber
							.intValue(), position + 1, currItem.lookAHead);
					if (symToItems.containsKey(nextSym))
						itemsSet = (TreeSet) symToItems.get(nextSym);
					else {
						itemsSet = new TreeSet(new ItemsCompare());
						symToItems.put(nextSym, itemsSet);
					}
					itemsSet.add(newItem);
				} else {
					/* Сформировать действие reduce */
				}
			}
		}
		HashSet itemsEntrySet = new HashSet(symToItems.entrySet());
		Iterator it = itemsEntrySet.iterator();
		/* Итератор по парам (символ, множество ситуаций */
		while (it.hasNext()) {
			Map.Entry me = (Map.Entry) it.next();
			TreeSet stateStub = (TreeSet) me.getValue();
			String goToSym = (String) me.getKey();

			Integer j = closure(stateStub);
//			showState("Goto from " + state + " to " + j + " by " + goToSym,
//					stateStub);
			/* Сформировать действие GoTo и если символ терминальный - shift */
			if (Nonterms.contains(goToSym)) {
				/* Сформировать GoTo */
				HashMap goTo;
				if (gotoTable.containsKey(state))
					goTo = (HashMap) gotoTable.get(state);
				else
					goTo = new HashMap();
				goTo.put(goToSym, j);
				gotoTable.put(state, goTo);
			} else {
				/* Сформировать Shift */
				HashMap LAHaction;
				if (actionTable.containsKey(state)) {
					LAHaction = (HashMap) actionTable.get(state);
					if (LAHaction.containsKey(goToSym))
						System.out.println("Грамматика не LR(1)LAH " + goToSym
								+ " rule number " + j);
				} else
					LAHaction = new HashMap();
				LAHaction.put(goToSym, new Action(false, j));
				/* false - признак Shift */
//				showState(state, LAHaction);
				actionTable.put(state, LAHaction);
//				showResultSystem();
			}
		}
	}

	/** *************************************************************** */
	void LR1items() {
		TreeSet currentState = new TreeSet(new ItemsCompare());
		/* Множество LR1 ситуаций */
		currentState.add(new LR1Item(0, 0, "#"));
		closure(currentState);
		do {
			Integer sn = (Integer) statesList.getFirst();
			goTo(sn);
			statesList.removeFirst();
		} while (!statesList.isEmpty());
		showResultSystem();

	}

	/** *************************************************************** */
	void showResultSystem() {
		int i;
		for (i = 1; i <= actionTable.size(); i++) {
			Integer ii = new Integer(i);
			HashMap LAHaction = (HashMap) actionTable.get(ii);
			showState(ii, LAHaction);
			HashSet actionSet = new HashSet(LAHaction.entrySet());
			Iterator itr = actionSet.iterator();

			while (itr.hasNext()) {
				Map.Entry me = (Map.Entry) itr.next();
				String r = (String) me.getKey();
				Action LAHAction = (Action) me.getValue();
				System.out.println("State " + i + " LAH " + r + " action "
						+ (LAHAction.action ? "reduce" : "shift")
						+ LAHAction.state);
			}

			if (gotoTable.get(ii) != null) {
				LAHaction = (HashMap) gotoTable.get(ii);
				actionSet = new HashSet(LAHaction.entrySet());
				itr = actionSet.iterator();
				while (itr.hasNext()) {
					Map.Entry me = (Map.Entry) itr.next();
					String r = (String) me.getKey();
					Integer LAHAction = (Integer) me.getValue();
					System.out.println("State " + i + " Nonterm " + r
							+ " goto " + LAHAction);
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

	LR1(Reader r) throws IOException {
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
		Nonterms.add("NewAxiom");
		tok.nextToken();
		Axiom = new String(tok.sval);
		tok.nextToken();
		LinkedList rightHandSide;
		HashMap RHSs;
		String lhs;
		Iterator i = Nonterms.iterator();
		/*
		 * Для каждого нетерминала A строится функция A -> {Номер правила ->
		 * {правая часть}}
		 */
		while (i.hasNext())
			GrammarN.put(new String((String) i.next()), new HashMap());
		while (tok.nextToken() != tok.TT_EOF) {
			rightHandSide = new LinkedList();
			lhs = new String(tok.sval);
			RHSs = (HashMap) GrammarN.get(lhs);
			int j = ruleNumber, k;
			tok.nextToken();
			do {
				rightHandSide.add(tok.sval);
				tok.nextToken();
			} while (!(tok.sval).equals(";"));
			showSet(lhs, new HashSet(rightHandSide));
			RHSs.put(new Integer(ruleNumber++), rightHandSide);
		}
		/*
		 * Для каждого правила строится функция {Номер правила ->(левая часть,
		 * правая часть}}
		 */
		i = Nonterms.iterator();
		while (i.hasNext()) {
			lhs = (String) i.next();
			RHSs = (HashMap) GrammarN.get(lhs);
			HashSet RHSme = new HashSet(((HashMap) GrammarN.get(lhs))
					.entrySet());
			Iterator itr = RHSme.iterator();
			while (itr.hasNext()) {
				Map.Entry me = (Map.Entry) itr.next();
				Integer rn = (Integer) me.getKey();
				LinkedList rhs = (LinkedList) me.getValue();
				showSet(lhs, new HashSet(rhs));
				Rule rule = new Rule(lhs, rhs);
				GrammarR.put(rn, rule);
				showGrammaR();
			}
		}
		rightHandSide = new LinkedList();
		rightHandSide.add(Axiom);
		Rule rule = new Rule("NewAxiom", rightHandSide);
		GrammarR.put(new Integer(0), rule);
		showGrammaR();
		FirstConstructor();
	}

	/** *************************************************************** */
	void LR1Parser(InputStreamReader inputReader) throws IOException {
		try {
			LinkedList stack = new LinkedList();
			tok = new StreamTokenizer(inputReader);
			tok.resetSyntax();
			tok.wordChars(33, 255);
			tok.whitespaceChars(0, ' ');
			tok.eolIsSignificant(false);
			tok.nextToken();
			stack.add(new Integer(1));
			do {
				Integer top = (Integer) stack.getFirst();
				HashMap actionMap = (HashMap) actionTable.get(top);
				if (actionMap.containsKey(tok.sval)) {
					Action action = (Action) actionMap.get(tok.sval);
					Integer RN = action.state;
					if (action.action) {/* reduce */
						/* Номер правила */
						if (RN.intValue() == 0) {
							System.out.println("Accept ");
							break;
						} else {
							Rule rule = (Rule) GrammarR.get(RN);
							System.out.println("Reduce rule " + RN);
							int RHSsize = rule.rhs.size();
							if (!((RHSsize == 1) & ((String) rule.rhs
									.getFirst()).equals("$")))
								while (RHSsize-- > 0)
									stack.removeFirst();
							HashMap gotovalue = (HashMap) gotoTable
									.get((Integer) stack.getFirst());
							stack.addFirst((Integer) gotovalue.get(rule.lhs));
						}
					} else {/* shift */
						{
							System.out.println("Shift " + tok.sval);
							stack.addFirst(RN);
							tok.nextToken();
						}
					}
				} else
					throw new syntaxError();
			} while (!stack.isEmpty());
			if (!tok.sval.equals("#"))
				throw new syntaxError();
		} catch (syntaxError e) {
		}
	}

	/** *************************************************************** */
	public static void main(String args[]) {
		try {
			String grammarFile = "e:/AutoLang/LR1/Grammar.10";
			FileInputStream GrammarStream = new FileInputStream(grammarFile);
			InputStreamReader GrammarReader = new InputStreamReader(
					GrammarStream);

			LR1 grammar = new LR1(GrammarReader);
			grammar.LR1items();
			/*
			 * String input = "e:/AutoLang/12"; FileInputStream inputStream =
			 * new FileInputStream(input); InputStreamReader inputReader = new
			 * InputStreamReader(inputStream); grammar.LR1Parser(inputReader);
			 */
		} catch (FileNotFoundException e) {
			System.out.println("File not found");
		} catch (IOException e) {
			System.out.println("Wrong input");
		}
	}
}