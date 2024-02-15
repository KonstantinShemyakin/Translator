package regularExpression;
//Версия 04.05.2010
import java.util.*;
import java.io.*;

class RegularExpression {
	class ResultSet {
		boolean nullable;
		HashSet firstPos, lastPos;
	}

	final int LEFTBR = '(';
	final int RIGHTBR = ')';
	final int EPS = '$';
	final int ASTERIC = '*';
	final int UNION = '|';
	final int EOF = '#';
	final int LEX = 0;
	StreamTokenizer tok;
	HashSet Alphabet = new HashSet();
	int lexType, position;
	HashMap posToSymbol = new HashMap();
	// Символ каждой позиции
	ResultSet root;
	HashMap followPos = new HashMap();

	void showResultSet(ResultSet RS) {
		System.out.println("nullable " + RS.nullable);
		System.out.print("firstPos ");
		Iterator itr = RS.firstPos.iterator();
		while (itr.hasNext()) {
			System.out.print((Integer) itr.next() + " ");
		}
		System.out.println();
		System.out.print("lastPos ");
		itr = RS.lastPos.iterator();
		while (itr.hasNext()) {
			System.out.print((Integer) itr.next() + " ");
		}
		System.out.println();
	}

	void showEntry(Integer entry) {
		System.out.println("entry = " + entry);
		HashSet config = (HashSet) followPos.get(entry);
		System.out.print("followPos:entry = " + entry + " positions = ");
		Iterator i = config.iterator();
		while (i.hasNext())
			System.out.print(i.next());
		System.out.println();
	}

	void showFollowPos() {
		Set entries = followPos.keySet();
		Iterator itr = entries.iterator();
		while (itr.hasNext()) {
			Integer entry = (Integer) itr.next();
			showEntry(entry);
		}
	}

	RegularExpression(Reader r) throws IOException {
		tok = new StreamTokenizer(r);
		tok.resetSyntax();
		tok.wordChars(33, 255);
		tok.whitespaceChars(0, ' ');
		tok.eolIsSignificant(true);
		position = 1;
		try {
			root = Expr();
		} catch (syntaxError e) {
		} catch (lexicalError e) {
		}
		showFollowPos();
	}

	class lexicalError extends Exception {
		lexicalError() {
			System.out.println("Лексическая ошибка:");
		}
	}

	class syntaxError extends Exception {
		syntaxError() {
			System.out.println("Синтаксическая ошибка:");
		}
	}

	int yylex() throws lexicalError, IOException {
		tok.nextToken();
		if (tok.sval.length() == 1)
			lexType = tok.sval.charAt(0);
		else {
			String lex = new String(tok.sval);
			int lexLen = lex.length();
			if ((lex.charAt(0) == '\'') & (lex.charAt(lexLen - 1) == '\'')) {
				String newSymb = new String(lex.substring(1, lexLen - 1));
				Alphabet.add(newSymb);
				System.out.println("Position "+position+" Symbol "+newSymb);
				posToSymbol.put(new Integer(position), newSymb);
				lexType = LEX;
			} else
				throw new lexicalError();
		}
		return lexType;
	}

	/** ************************************************************************ */
	HashSet move(HashSet fromSet, String currentSymbol) {
		// Результатом является множество-состояние ДКА - переход
		// из множества-состояния fromSet по символу currentSymbol
		Iterator i = fromSet.iterator();
		HashSet toState = new HashSet();
		while (i.hasNext()) {
			Integer nextPos = (Integer) i.next();
			System.out.println("nextPos "+nextPos+" currentSymbol "+currentSymbol);
			// Символы, по которым определен переход в данном состоянии
			if (posToSymbol.get(nextPos).equals(currentSymbol))
				toState.addAll((HashSet) followPos.get(nextPos));
		}
		return toState;
	}

	/** ********************************************** */
	void showStates(HashSet st) {
		Iterator i = st.iterator();
		while (i.hasNext()) {
			// Для каждого водного символа
			Integer nextSymbol = (Integer) i.next();
			System.out.print(" " + nextSymbol);
		}
		System.out.println();
	}

	/** ***************************************************************************** */
	void showTransitionFunction(HashMap TransitionFunction) {
		Set set = TransitionFunction.entrySet();
		Iterator i = set.iterator();
		while (i.hasNext()) {
			Map.Entry me;
			me = (Map.Entry) i.next();
			System.out.println("Map:" + me.getKey() + me.getValue());
		}
	}

	/** ***************************************************** */
	public void REtoDFA() {
		int stateNumber = 1;
		HashMap DFATransitionFunction = new HashMap();
		// Отображение Состояние -> символ -> Множество состояний
		HashMap DFAStates = new HashMap();
		// Это функция, отображающая символьное имя состояния во множество -
		// результат объединения
		HashSet DFAalphabet = Alphabet;
		HashSet DFAstartState = new HashSet();
		DFAstartState.add(root.firstPos);
		// Начальное состояние НКА как множество

		DFAStates.put(new Integer(stateNumber), root.firstPos);

		// Добавили начальное состояние как функцию 1->начальное множество
		HashMap DFAtransitionFunction;
		LinkedList unmarkedStates = new LinkedList();
		// Это список необработанных состояний - подмножеств
		Integer fromState;
		unmarkedStates.add(new Integer(stateNumber));
		while (!unmarkedStates.isEmpty()) {
			// Пока есть необработанное состояние
			fromState = (Integer) unmarkedStates.getFirst();
			System.out.println("Current unmarkedState " + fromState);
			HashSet setState = (HashSet) DFAStates.get(fromState);
			showStates(setState);
			// Берем первое состояние-подмножество
			Iterator i = DFAalphabet.iterator();
			while (i.hasNext()) {
				// Для каждого входного символа
				String nextSymbol = (String) i.next();
				HashSet newSetState = move(setState, nextSymbol);
				System.out.print("from ");
				showStates(setState);
				System.out.print("by " + nextSymbol);
				System.out.print("to ");
				showStates(newSetState);
				// Делаем переход из текущего состояния по текущему символу
				if (!newSetState.isEmpty()) {
					// Если переход определен
					int nextName = 0;
					boolean equal;
					do {
						nextName++;
						// Пробегаем по множеству уже имеющихся
						// состояний-подмножеств
						HashSet nextState = (HashSet) DFAStates
								.get(new Integer(nextName));
						// Получаем очередное подмножество-состояние
						equal = nextState.size() == newSetState.size();
						if (equal) {
							// И сравниваем эти подмножества
							Iterator itr1 = nextState.iterator();
							Iterator itr2 = newSetState.iterator();
							while (itr1.hasNext() & equal)
								equal = itr1.next().equals(itr2.next());
							// Сравниваем состояния, образующие подмножества
						}
					} while (!equal & nextName < stateNumber);
					if (!equal) {
						// Новое состояние
						nextName = ++stateNumber;
						// Номер состояния, в которое осуществляется переход
						DFAStates.put(new Integer(stateNumber), newSetState);
						unmarkedStates.addLast(new Integer(stateNumber));
					}
					// В любом случае
					HashMap symbolTransition;
					if (DFATransitionFunction.containsKey(fromState))
						symbolTransition = (HashMap) DFATransitionFunction
								.get(fromState);
					else
						symbolTransition = new HashMap();
					HashSet toState = new HashSet();
					toState.add(new Integer(nextName));
					symbolTransition.put(nextSymbol, toState);
					DFATransitionFunction.put(fromState, symbolTransition);
					System.out.println("transition from " + fromState + " by "
							+ nextSymbol + " to " + nextName);
				}
			}
			unmarkedStates.removeFirst();
		}
 		showTransitionFunction(DFATransitionFunction);
	}

	/** *********************************************************************** */
	ResultSet Atom() throws syntaxError, lexicalError, IOException {
		ResultSet retValue;
		try {

			boolean lex;
			switch (lexType) {
			case LEX:
			case EPS:
				retValue = new ResultSet();
				retValue.nullable = lexType == EPS;
				retValue.firstPos = new HashSet();
				retValue.firstPos.add(new Integer(position));
				retValue.lastPos = new HashSet();
				retValue.lastPos.add(new Integer(position++));
				break;
			case LEFTBR: {
				yylex();
				retValue = Union();
				if (lexType == RIGHTBR) {

					break;
				} else
					throw new syntaxError();
			}
			default:
				throw new syntaxError();
			}
			yylex();
//			System.out.println("Atom");
//			showResultSet(retValue);
			return retValue;
		} catch (lexicalError e) {
		}
		return null;
	}

	ResultSet Term() throws syntaxError, lexicalError, IOException {
		try {
			ResultSet retValue;
			retValue = Atom();
			if (lexType == ASTERIC) {
				yylex();
				retValue.nullable = true;
				Iterator lst = retValue.lastPos.iterator();
				while (lst.hasNext()) {
					// Для каждого элемента lastPos
					Integer next = (Integer) lst.next();
					if (followPos.containsKey(next)) {
						HashSet follow = (HashSet) followPos.get(next);
						// Взять соответствующий элемент followPos
						follow.addAll(retValue.firstPos);
						// Добавить к нему firstPos
						followPos.put(next, follow);
						// Положить обратно
					} else
						followPos.put(next, retValue.firstPos);
//					showEntry(next);
				}
			}
//			System.out.println("Term");
//			showResultSet(retValue);
			return retValue;
		} catch (syntaxError e) {
		}
		return null;
	}

	ResultSet Factor() throws syntaxError, lexicalError, IOException {
		try {
			boolean first = true, nullable = true;
			ResultSet retValue = null, rV = new ResultSet();
			// rV накапливает firstPos и lastPos для Factor
			rV.firstPos = new HashSet();
			rV.lastPos = new HashSet();
			HashSet last;
			do {
				if (!first)
					last = retValue.lastPos;
				else
					last = null;
				retValue = Term();
				if (nullable)
					rV.firstPos.addAll(retValue.firstPos);
				nullable &= retValue.nullable;
				if (retValue.nullable) {
					rV.lastPos.addAll(retValue.lastPos);
				} else {
					rV.lastPos = retValue.lastPos;
				}
//				System.out.println("inside Factor");
				// Пополняем followPos
				if (first)
					first = false;
				else {
					Iterator lst = last.iterator();
					while (lst.hasNext()) {
						// Для каждого элемента lastPos
						Integer next = (Integer) lst.next();
						if (followPos.containsKey(next)) {
							HashSet follow = (HashSet) followPos.get(next);
							// Взять соответствующий элемент followPos

							followPos.put(next, follow);
							follow.addAll(retValue.firstPos);
							// Добавить к нему firstPos
							followPos.put(next, follow);
							// Положить обратно
						} else
							followPos.put(next, retValue.firstPos);
//						showEntry(next);
					}
				}

//				showResultSet(rV);
			} while ((lexType == LEX) | (lexType == LEFTBR));
			rV.nullable = nullable;
//			System.out.println("Factor");
//			showResultSet(rV);
			return rV;
		} catch (syntaxError e) {
		}
		return null;
	}

	ResultSet Union() throws syntaxError, lexicalError, IOException {
		try {
			ResultSet retValue = new ResultSet(), rV;
			retValue.firstPos = new HashSet();
			retValue.lastPos = new HashSet();
			boolean cont = true, nullable = false;
			do {
				rV = Factor();
				retValue.firstPos.addAll(rV.firstPos);
				retValue.lastPos.addAll(rV.lastPos);
				if (lexType == UNION)
					yylex();
				else
					cont = false;
				nullable |= rV.nullable;
			} while (cont);
			retValue.nullable = nullable;
//			System.out.println("Union");
//			showResultSet(retValue);
			return retValue;
		} catch (syntaxError e) {
		}
		return null;
	}

	ResultSet Expr() throws syntaxError, lexicalError, IOException {
		try {
			yylex();
			root = Union();
//			showResultSet(root);
			Integer endPosition = new Integer(position);
			if (lexType != EOF)
				throw new syntaxError();
			else if (root.nullable)
				root.firstPos.add(endPosition);
			Iterator lst = root.lastPos.iterator();
			while (lst.hasNext()) {
				// Для каждого элемента lastPos
				Integer next = (Integer) lst.next();
				if (followPos.containsKey(next)) {
					HashSet follow = (HashSet) followPos.get(next);
					// Взять соответствующий элемент followPos
					follow.add(endPosition);
					// Добавить к нему firstPos
					followPos.put(next, follow);
					// Положить обратно
				} else
					followPos.put(next, endPosition);
			}
//			showResultSet(root);
			posToSymbol.put(new Integer(position), "#");
			return root;
		} catch (syntaxError e) {
		}
		return null;
	}

	/** ************************************************************************* */
	public static void main(String args[]) {
		try {
			String FileName = "e:/AutoLang/RegExp/RegExp.6";
			FileInputStream inputStream = new FileInputStream(FileName);
			InputStreamReader streamReader = new InputStreamReader(inputStream);
			RegularExpression RE = new RegularExpression(streamReader);
			RE.REtoDFA();
		} catch (FileNotFoundException e) {
			System.out.println("File not found");
		} catch (IOException e) {
			System.out.println("Wrong input");
		}
	}
}