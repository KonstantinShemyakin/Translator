package Automata;
//������ 04.05.2010
import java.util.*;
import java.io.*;

class State {
	String state;
}

class StateProps {
	int length;
	boolean fin;

	StateProps(int l) {
		length = l;
		fin = false;
	}
}

class Configuration {
	State state;
	LinkedList input;

	Configuration() {
		input = new LinkedList();
		state = new State();
	};

	int getInputLength() {
		return input.size();
	}

	Configuration(Configuration copy) {
		this();
		state.state = copy.state.state;
		Iterator i = copy.input.iterator();
		while (i.hasNext()) {
			input.add(i.next());
		}
	}
}

interface FiniteAutomaton {
	boolean Transition();

	void read() throws IOException;

	void ComeOn();

	void NFAtoDFA();

	void InvertTransitionFunction();

	void equivalence();
}

/** *********************************************** */
class Finite implements FiniteAutomaton {

	HashSet Alphabet = new HashSet();
	/* ��������� ����� */
	HashMap States = new HashMap();
	/* ���� �� ��������� ���������� � Integer */
	/*
	 * ��������� ��� <���,�����>, ��� ����� - ����� ����������� ����� �
	 * ������������ � ���������� "���" ��� ����������� ���������� ������������
	 */
	HashSet FinalStates = new HashSet();
	/* ��������� ���� ��������� */
	State StartState = new State();
	HashMap TransitionFunction = new HashMap();
	/* ����������� ��������� -> (������ -> {��������� ���������}) */
	HashMap invertTransitionFunction = new HashMap();
	/* �� �� �����, �� �������� �������� */
	LinkedList configurations;
	/*
	 * ������ ������������, � ������� ����� ���������� ������� �� ���������
	 * ������ �������, ����� ������� �������� � ������������
	 */
	StreamTokenizer tok;
	boolean accept = false;
	Configuration config = new Configuration();
	HashMap disting = new HashMap();
	HashMap equiSets = new HashMap();

	/** ************************************************ */
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
	Finite(Reader r) throws IOException {

		tok = new StreamTokenizer(r);
		tok.resetSyntax();
		tok.wordChars(33, 255);
		tok.whitespaceChars(0, ' ');
		tok.eolIsSignificant(true);
		configurations = new LinkedList();

		while (tok.nextToken() != tok.TT_EOL) {
	
			Alphabet.add(tok.sval);
		}
		while (tok.nextToken() != tok.TT_EOL) {
			States.put(tok.sval, new StateProps(1000));
		}
		while (tok.nextToken() != tok.TT_EOL) {
			FinalStates.add(tok.sval);
			StateProps sp = (StateProps) States.get(tok.sval);
			sp.fin = true;
		}
		tok.nextToken();
		// ��������� ���������
		StartState.state = tok.sval;
		config.state.state = tok.sval;

		if (tok.nextToken() == tok.TT_EOL)
			while ((tok.nextToken() != tok.TT_EOL) && (tok.ttype != tok.TT_EOF)) {
				HashMap symbolTransition;
				HashSet objectSet;
				String DomainState, DomainSymb, RangeState;
				HashMap SymbolToState;
				DomainState = new String(tok.sval);
				tok.nextToken();
				DomainSymb = new String(tok.sval);
				tok.nextToken();
				RangeState = new String(tok.sval);
				tok.nextToken();

				if (TransitionFunction.containsKey(DomainState)) {
					// ������� �� DomainState ���������
					SymbolToState = (HashMap) TransitionFunction
							.get(DomainState);
					// ������� ����������� ��������� � ������� (������ ��
					// ��������� ���������)
					if (SymbolToState.containsKey(DomainSymb))
						// ���� � ������ ��������� ���� ������� �� �������
						// �������
						// ������� ����������� ������� �� ��������� ���������
						objectSet = (HashSet) SymbolToState.get(DomainSymb);
					// ������� ��������� ��������� - ������� �� �������
					// DomainSymb
					else
						objectSet = new HashSet();
				} else
				// ������� ��������� �� �������� �������� �� ������� ���������

				// ������� �� ������� ������� ��� �� ���������
				{
					SymbolToState = new HashMap();
					// ����� ����������� ������� �� ��������� ���������
					objectSet = new HashSet();
				}
				// ����� ��������� ��������� ��������
				objectSet.add(RangeState);
				// �������� ����� ��������� � ��������� ��������� ��������� ��
				// ������� �������

				SymbolToState.put(DomainSymb, objectSet);

				TransitionFunction.put(DomainState, SymbolToState);

				if (!tok.sval.equals(";"))
					break;
			}
		// System.out.println("TransitionFunction:" + DomainState+ DomainSymb +
		// RangeState);
		showTransitionFunction(TransitionFunction);
	}

	/** ************************************************** */
	public void read() throws IOException {
		try {
			int i;

			System.out.println("Input string:");
			InputStreamReader inputStream = new InputStreamReader(System.in);
			tok = new StreamTokenizer(inputStream);
			tok.resetSyntax();
			tok.wordChars(33, 255);
			tok.whitespaceChars(0, ' ');
			tok.eolIsSignificant(true);
			tok.nextToken();
			while (!tok.sval.equals("#")) {
				config.input.add(new String(tok.sval));
				tok.nextToken();
			}
			configurations.add(config);

		} catch (IOException e) {
			System.out.println("wrong input");
		}
	}

	/** ********************************************************** */
	int compareConfig(Object obj1, Object obj2) {
		int cmp = ((Configuration) obj1).state.state
				.compareTo(((Configuration) obj2).state.state);
		if (cmp != 0)
			return cmp;
		else
			return (((Configuration) obj1).input.size() - ((Configuration) obj2).input
					.size());
	}

	/** **************************************************************** */
	class Comp implements Comparator {
		public int compare(Object obj1, Object obj2) {
			return compareConfig(obj1, obj2);
		}
	}

	/** ***************************************************** */
	void showConfigurations() {
		Iterator itr = (configurations.iterator());
		while (itr.hasNext()) {
			Configuration config = (Configuration) itr.next();
			System.out.print("Configuration:State = " + config.state.state
					+ " input = ");
			Iterator i = config.input.iterator();
			while (i.hasNext())
				System.out.print(i.next());
			System.out.println();
		}
	}

	/** ********************************************************************* */
	boolean onSymbolTransition(String currentSymbol) {
		HashMap symbolTransition = (HashMap) TransitionFunction
				.get(config.state.state);
		// �������, �� ������� ��������� ������� � ������ ���������

		Iterator itr = ((HashSet) symbolTransition.get(currentSymbol))
				.iterator();
		// �������� �� ��������� ��������� �� ������� ������� ��
		// ������� ���������
		if (!currentSymbol.equals("$"))
			config.input.removeFirst();
		// ������� ��������� ������
		String nextState;
		while (itr.hasNext()) {
			nextState = (String) itr.next();
			if (config.input.isEmpty() && FinalStates.contains(nextState)) {
				System.out.println("Accept in the state " + nextState);
				accept = true;
				return false;
			}
			Configuration newConfig = new Configuration(config);
			// ����� ������������
			newConfig.state.state = nextState;
			configurations.remove(config);
			// if (compareConfig(newConfig, config) != 0)
			StateProps inputLength = (StateProps) States.get(nextState);
			if (inputLength.length != newConfig.getInputLength()) {
				inputLength.length -= 1;
				// ���� �� � ��������� � �� �� ������������, �� ��
				// �������� �������� �� ����
				configurations.addLast(newConfig);
			}
			// ����� �������� ����� ������������
			// �� ����� �� �����������? �� ����� �� �������������
			// ��� ��� ���������� ������������?
			System.out.println("After modification");
			showConfigurations();
			System.out.println("Transition:" + config.state.state
					+ currentSymbol + newConfig.state.state);
		}
		return true;
	}

	/** ***************************************** */
	public boolean Transition() {
		boolean success = false, empty;
		System.out.println("Configurations before transition:");
		showConfigurations();
		config = (Configuration) configurations.getFirst();
		String currentSymbol = null;
		if (!(empty = config.input.isEmpty()))
			currentSymbol = (String) config.input.getFirst();
		if (TransitionFunction.containsKey(config.state.state)) {
			HashMap symbolTransition = (HashMap) TransitionFunction
					.get(config.state.state);
			boolean eps = symbolTransition.containsKey("$");
			// �������, �� ������� ��������� ������� � ������ ���������
			if (!empty & symbolTransition.containsKey(currentSymbol))
				success = onSymbolTransition(currentSymbol);
			if (eps)
				success = onSymbolTransition("$");
			if (empty & !eps)
				System.out.println("Empty input in the state:"
						+ config.state.state);
		} else
			System.out
					.println("No transition from state " + config.state.state);
		return success;
	}

	/** ************************************************************************* */
	public void ComeOn() {
		do {
			while (Transition()) {
				System.out.println("Configurations after transition:");
				showConfigurations();
			}
		} while (configurations.isEmpty());
		if (!accept)
			System.out.println("Do not accept");
	}

	/** ************************************************************************* */
	HashSet eClosure(HashSet fromState) {
		HashSet toState = new HashSet(fromState);
		LinkedList stateList = new LinkedList(fromState);

		int count = 0;
		while (!stateList.isEmpty()) {
			String newState = (String) stateList.getFirst();
			if (TransitionFunction.containsKey(newState)) {
				HashMap stateTransition = (HashMap) TransitionFunction
						.get(newState);
				if (stateTransition.containsKey("$")) {
					HashSet epsTransitions = (HashSet) stateTransition.get("$");
					Iterator i = epsTransitions.iterator();
					while (i.hasNext()) {
						newState = (String) i.next();
						if (!toState.contains(newState)) {
							stateList.addLast(newState);
							toState.add(newState);
						}
					}
				}
			}
			stateList.removeFirst();
		}
		return toState;
	}

	/** ********************************************** */
	HashSet move(HashSet fromSet, String currentSymbol) {
		// ����������� �������� ���������-��������� ��� - �������
		// �� ���������-��������� fromSet �� ������� currentSymbol
		Iterator i = fromSet.iterator();
		HashSet toState = new HashSet();
		while (i.hasNext()) {
			HashMap symbolTransition = (HashMap) TransitionFunction.get(i
					.next());
			// �������, �� ������� ��������� ������� � ������ ���������
			if (symbolTransition.containsKey(currentSymbol)) {
				Iterator itr = ((HashSet) symbolTransition.get(currentSymbol))
						.iterator();
				// �������� �� ��������� ��������� �� ������� ������� ��
				// ������� ���������
				String nextState;
				while (itr.hasNext()) {
					nextState = (String) itr.next();
					toState.add(nextState);
				}
			}
		}
		return eClosure(toState);
	}

	/** ********************************************** */
	void showStates(HashSet st) {
		Iterator i = st.iterator();
		while (i.hasNext()) {
			// ��� ������� ������� �������
			String nextSymbol = (String) i.next();
			System.out.print(" " + nextSymbol);
		}
		System.out.println();
	}

	/** ***************************************************************************** */
	public void NFAtoDFA() {
		int stateNumber = 1;
		HashMap DFATransitionFunction = new HashMap();
		HashMap DFAStates = new HashMap();
		// ��� �������, ������������ ���������� ��� ��������� �� ��������� -
		// ��������� �����������
		HashSet DFAalphabet = Alphabet;
		HashSet DFAstartState = new HashSet();
		DFAstartState.add(StartState.state);
		// ��������� ��������� ��� ��� ���������
		HashSet setState = eClosure(DFAstartState);
		// ��������� ��������� ��� ��� ���������

		DFAStates.put(new Integer(stateNumber).toString(), setState);

		// �������� ��������� ��������� ��� ������� 0->��������� ���������
		HashMap DFAtransitionFunction;
		LinkedList unmarkedStates = new LinkedList();
		// ��� ������ �������������� ��������� - �����������
		String fromState;
		unmarkedStates.add(new Integer(stateNumber).toString());
		while (!unmarkedStates.isEmpty()) {
			// ���� ���� �������������� ���������
			fromState = (String) unmarkedStates.getFirst();
			System.out.println("Current unmarkedState " + fromState);
			setState = (HashSet) DFAStates.get(fromState);
			showStates(setState);
			// ����� ������ ���������-������������
			Iterator i = DFAalphabet.iterator();
			while (i.hasNext()) {
				// ��� ������� ������� �������
				String nextSymbol = (String) i.next();
				HashSet newSetState = move(setState, nextSymbol);
				System.out.println("from ");
				showStates(setState);
				System.out.println("by " + nextSymbol);
				System.out.println("to ");
				showStates(newSetState);
				// ������ ������� �� �������� ��������� �� �������� �������
				if (!newSetState.isEmpty()) {
					// ���� ������� ���������
					int nextName = 0;
					boolean equal;
					do {
						nextName++;
						// ��������� �� ��������� ��� ���������
						// ���������-�����������
						HashSet nextState = (HashSet) DFAStates
								.get(new Integer(nextName).toString());
						// �������� ��������� ������������-���������
						equal = nextState.size() == newSetState.size();
						if (equal) {
							// � ���������� ��� ������������
							Iterator itr1 = nextState.iterator();
							Iterator itr2 = newSetState.iterator();
							while (itr1.hasNext() & equal)
								equal = itr1.next().equals(itr2.next());
							// ���������� ���������, ���������� ������������
						}
					} while (!equal & nextName < stateNumber);
					if (!equal) {
						// ����� ���������
						nextName = ++stateNumber;
						// ����� ���������, � ������� �������������� �������
						DFAStates.put(new Integer(stateNumber).toString(),
								newSetState);
						unmarkedStates.addLast(new Integer(stateNumber)
								.toString());
					}
					// � ����� ������
					HashMap symbolTransition;
					if (DFATransitionFunction.containsKey(fromState))
						symbolTransition = (HashMap) DFATransitionFunction
								.get(fromState);
					else
						symbolTransition = new HashMap();
					HashSet toState = new HashSet();
					toState.add(new Integer(nextName).toString());
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

	/** ********************************************************************* */

	public void InvertTransitionFunction() {

		HashMap fromSymbStates;
		HashSet fromStates;
		/*
		 * ����������� ��������� -> (������ -> {��������� ���������}) ���
		 * ������� ��������� � ������� ������� ��������� ���������, �������� �
		 * ������ �� ������� �������
		 */
		Set statesSet = States.keySet();
		Iterator i = statesSet.iterator();
		/* �������� �� ���������� */
		while (i.hasNext()) {
			String nextState = (String) i.next();
			if (TransitionFunction.containsKey(nextState)) {
				HashMap symbolTransition = (HashMap) TransitionFunction
						.get(nextState);
				Set symbToStates = symbolTransition.entrySet();
				Iterator itr = symbToStates.iterator();
				/*
				 * �������� �� Map.Entry ������������ ������ -> ���������,
				 * ��������� �� ������ ���������
				 */
				while (itr.hasNext()) {
					/* ��� ������� ������� */
					Map.Entry map = (Map.Entry) itr.next();
					HashSet state = (HashSet) map.getValue();
					String symb = (String) map.getKey();
					/*
					 * ��� ��� ��� ��������� ������� � �������� �� ������
					 * ��������
					 */
					Iterator it = state.iterator();
					String toState = (String) it.next();
					/*
					 * ������ nextState �������� ���������, �� �������� �� symb
					 * �������� ������� � toState
					 */
					if (invertTransitionFunction.containsKey(toState)) {
						fromSymbStates = (HashMap) invertTransitionFunction
								.get(toState);
						if (fromSymbStates.containsKey(symb)) {
							fromStates = (HashSet) fromSymbStates.get(symb);
							fromStates.add(nextState);
						} else {
							fromStates = new HashSet();
							fromStates.add(nextState);
							fromSymbStates.put(symb, fromStates);
						}
					} else {
						fromSymbStates = new HashMap();
						fromStates = new HashSet();
						fromStates.add(nextState);
						fromSymbStates.put(symb, fromStates);
						invertTransitionFunction.put(toState, fromSymbStates);
					}
				}
			}
		}
		showTransitionFunction(invertTransitionFunction);
	}

	/** ****************************************************************** */
	void showSet(String n, HashSet s) {
		if (s != null) {
			Iterator i = s.iterator();
			System.out.print("State " + n);
			while (i.hasNext())
				System.out.print(" " + (String) i.next());
			System.out.println();
		}
	}

	/** ****************************************************************** */
	void makePartition() {
		/* ��������� equiSets �������������� ���������� ������� */
		Set statesNames = States.keySet();
		LinkedList equiStates = new LinkedList();

		String firstState, secondState;
		HashSet nextSet;
		Iterator i = statesNames.iterator();
		while (i.hasNext()) {
			firstState = (String) i.next();

			HashSet equiSet = new HashSet();
			nextSet = (HashSet) disting.get(firstState);
			showSet("disting for " + firstState, nextSet);
			Iterator j = statesNames.iterator();
			while (j.hasNext()) {
				secondState = (String) j.next();
				if (firstState.compareTo(secondState) > 0
						& !nextSet.contains(secondState)) {
					equiSet.add(secondState);
				}
			}
			equiSets.put(firstState, equiSet);
		}
		/* ������ ������������ ��������� */
		i = statesNames.iterator();
		while (i.hasNext()) {
			/* ��� ������� ��������� */
			firstState = (String) i.next();
			nextSet = (HashSet) equiSets.get(firstState);
			showSet("nextSet " + firstState, nextSet);
			/* ����� ��������� ��� ������������� �� ������� */

			if (nextSet != null && !nextSet.isEmpty()) {
				equiStates = new LinkedList(nextSet);
				/* ���������� ��� ��������� � ������ */
				// ListIterator li = equiStates.listIterator();
				while (!equiStates.isEmpty()) {
					secondState = (String) equiStates.getFirst();
					/* ��� ������ �������� ������ */
					nextSet = (HashSet) equiSets.get(secondState);

					/* ����� ��������� ��� ������������� �� ������� */
					if ((nextSet != null) && !nextSet.isEmpty()) {
						showSet("nextSet " + secondState, nextSet);
						Iterator itr = nextSet.iterator();
						while (itr.hasNext()) {
							String newState = (String) itr.next();
							equiStates.addLast(newState);
							/* ������� ��� � ��� �� ������ */
							nextSet.add(newState);
						}
					}
					equiSets.put(secondState, null);
					/* � ���������, ��� ������������ � ������, ���������� */
					equiStates.removeFirst();
				}
			}
		}
		i = statesNames.iterator();
		System.out.println("Result:");
		while (i.hasNext()) {
			String firstSet = (String) i.next();
			showSet(firstSet, (HashSet) equiSets.get(firstSet));
		}
	}

	/** ****************************************************************** */
	public void equivalence() {
		/* 0) ������� ������� ����� ������������ */
		/*
		 * 1) ��� ������� ��������� ���������� �� ������ ��������� �� �������
		 * ������� ���� �������
		 */
		/* 2) ������������ ������ {(p,q),a,{(r,s)|r(->a)p, s(->a)q}} */
		/* 3) ������������ ������ ������������ ��� (Q\F,F); */
		/* ���� ���� ������������ ���� (p,q) */
		/* �������� �� */
		/*
		 * ���� ���� ������������ ���� (r,s) (->a) (p,q), ������ �� � ������
		 * ������������ ���
		 */
		/* 4) ��������� ������ L= {QxQ \������ ���������� ���} */
		/* ��� ������ ���� (p,q) �� ����� ������ */
		/* ��������� ��������� Si={p,q} */
		/*
		 * ��� ������� �������� p ����� ��������� ���� � ������ L ���� ����
		 * (r,p)���(p,r) �������� r � ����� ��������� � ��������� ����
		 * (r,p)���(p,r) �� L
		 */
		/*
		 * 5)������ ��������� Si ���������� ����� ����������; ��� ��������� ��
		 * Q\{Si} �������� ���������� �����������
		 */
		/*
		 * 6) Si, ��������� �� �������������� ���������, ����������
		 * ��������������� ����������; ��� �������������� ���������, �� ��������
		 * � {Si}, �������� ��������������� �����������
		 */
		class Pair {
			State first, second;

			Pair(String f, String s) {
				first = new State();
				second = new State();
				first.state = f;
				second.state = s;
			}
		}
		LinkedList distingList = new LinkedList();
		String fName, sName, ffName;

		/* ������� ��� ��������� ����������� ������������ ��������� -> ��������� */
		Set statesNames = States.keySet();
		Iterator i = statesNames.iterator();
		HashSet right;
		while (i.hasNext()) {
			fName = (String) i.next();
			/* ���� ��������� <��������������, ����������������> �������������� */
			disting.put(fName, new HashSet());
			if (!((StateProps) States.get(fName)).fin) {
				Iterator itr = FinalStates.iterator();
				while (itr.hasNext()) {
					sName = (String) itr.next();
					ffName = fName;
					if (fName.compareTo(sName) < 0) {
						/*
						 * ��������� ��������� �����������, ������ ������
						 * ������� � ��������
						 */
						String tmp = fName;
						ffName = sName;
						sName = tmp;
					}
					distingList.add(new Pair(ffName, sName));
					if (disting.containsKey(ffName)) {
						right = (HashSet) disting.get(ffName);
						right.add(sName);
						System.out.println("Disting " + ffName + "  " + sName);
						i = statesNames.iterator();
						System.out.println("Result:");
						while (i.hasNext()) {
							String firstSet = (String) i.next();
							showSet("disting for " + firstSet,
									(HashSet) disting.get(firstSet));
						}

					} else {
						right = new HashSet();
						right.add(sName);
						System.out.println("Disting " + ffName + "  " + sName);
						disting.put(ffName, right);
						i = statesNames.iterator();
						System.out.println("Result:");
						while (i.hasNext()) {
							String firstSet = (String) i.next();
							showSet("disting for " + firstSet,
									(HashSet) disting.get(firstSet));
						}
					}
				}
			}
		}
		i = statesNames.iterator();
		System.out.println("Result:");
		while (i.hasNext()) {
			String firstSet = (String) i.next();
			showSet("disting for " + firstSet, (HashSet) disting.get(firstSet));
		}
		/* ���������� ��������������� ��������� */
		while (!distingList.isEmpty()) {
			Pair nextPair = (Pair) distingList.getFirst();
			String firstState = nextPair.first.state;
			String secondState = nextPair.second.state;
			if (firstState.compareTo(secondState) < 0) {
				String tmp = firstState;
				firstState = secondState;
				secondState = tmp;
			}
			/* ������ (�����) ������� ���� */
			if (invertTransitionFunction.containsKey(firstState)
					& invertTransitionFunction.containsKey(secondState)) {
				HashMap firstMap = (HashMap) invertTransitionFunction
						.get(firstState);
				/*
				 * �������� ��������� ���� ��������� �� �������� � ���������
				 * firstState
				 */
				/* ��� ������ (������) ������� ���� */
				HashMap secondMap = (HashMap) invertTransitionFunction
						.get(secondState);
				/*
				 * �������� ��������� ���� ��������� � ��������� secondState
				 */

				Iterator itr = Alphabet.iterator();
				/* ������ �������� �� ���� �������� ��������������� Map.Entry */
				while (itr.hasNext()) {
					/*
					 * ������ ���������� �������� � ������ ��������� �� �������
					 * �������
					 */
					String nextSymbol = (String) itr.next();

					if (firstMap.containsKey(nextSymbol)
							& secondMap.containsKey(nextSymbol)) {
						HashSet fSet = (HashSet) firstMap.get(nextSymbol);
						/*
						 * ��� ��������� ���������, �� ������� ���� ������� �
						 * firstState �� ������� �������
						 */
						HashSet sSet = (HashSet) secondMap.get(nextSymbol);
						/*
						 * ��� ��������� ���������, �� ������� ���� ������� �
						 * secondState �� ������� �������
						 */
						// showSet(firstState,fSet);
						// showSet(secondState,sSet);
						Iterator firstI = fSet.iterator();
						while (firstI.hasNext()) {
							String fState = (String) firstI.next();

							Iterator secondI = sSet.iterator();
							while (secondI.hasNext()) {
								String sState = (String) secondI.next();
								/*
								 * ���� fState � sState ����� ������� ��
								 * �������� ������� �������������� � firstState
								 * � secondState
								 */
								String ffState = fState;
								if (fState.compareTo(sState) < 0) {
									String tmp = fState;
									ffState = sState;
									sState = tmp;
								}
								/*
								 * �������� ���� fState, sState � disting �
								 * distingList
								 */
								if (disting.containsKey(ffState)) {
									right = (HashSet) disting.get(ffState);
									if (!right.contains(sState)) {
										right.add(sState);
										distingList.addLast(new Pair(ffState,
												sState));
										System.out.println("Disting " + ffState
												+ "  " + sState);

									}
								} else {
									right = new HashSet();
									right.add(sState);
									disting.put(ffState, right);
									System.out.println("Disting " + ffState
											+ "  " + sState);
									distingList.addLast(new Pair(ffState,
											sState));

								}
							}
						}
					}
				}
			}
			distingList.removeFirst();
		}
		i = statesNames.iterator();
		System.out.println("Result:");
		while (i.hasNext()) {
			String firstSet = (String) i.next();
			showSet("disting for " + firstSet, (HashSet) disting.get(firstSet));
		}
		makePartition();
		/*
		 * ���� ��� ��������� A ���� ������������� B, ���� ��� �������� � B
		 * ��������� � A, � ��������� B �������������
		 */
		Set s = equiSets.keySet();
		i = s.iterator();
		/* ������ ������� ��������� � ������� �������� */
		while (i.hasNext()) {
			/* ��� ������� ��������� */
			fName = (String) i.next();
			right = (HashSet) equiSets.get(fName);
			/* ��������� ���������, ������������� fName */
			if (right != null) {
				Iterator itr = right.iterator();
				while (itr.hasNext()) {
					sName = (String) itr.next();
					/* sName ������������ fName */
					HashMap inStates = (HashMap) invertTransitionFunction
							.get(sName);
					Set sMaps = inStates.entrySet();
					HashMap transit;
					/*
					 * �������� ��������� ������� ������ -> ��������� ���������,
					 * �� ������� ���� ������� �� ������� ������� � sName. ���
					 * ������� �� ���� ��������� ����� ������� ������� �
					 * ��������� fName, ����� ���� ��������� sName �������������
					 */
					Iterator st = sMaps.iterator();
					while (st.hasNext()) {
						Map.Entry me = (Map.Entry) st.next();
						String sym = (String) me.getKey();
						HashSet statesSet = (HashSet) me.getValue();
						Iterator si = statesSet.iterator();
						while (si.hasNext()) {
							String state = (String) si.next();
							/*
							 * state - ���������, �� �������� ���� ������� �
							 * sName �� sym � ���� state �����������
							 * equiSets.get(fName) - ������� ������� �� fName �
							 * fName
							 */
							HashSet outSet = new HashSet();
							HashMap newTransition;
							if (right.contains(state))
								newTransition = (HashMap) TransitionFunction
										.get(fName);
							else
								newTransition = (HashMap) TransitionFunction
										.get(state);
							outSet.add(fName);
							newTransition.put(sym, outSet);
						}
					}
					TransitionFunction.remove(sName);
				}
			}
		}
		/* �������� � ���������, ������� ������ ���, ���� ������������� */
		showTransitionFunction(TransitionFunction);
	}

	/** ****************************************************************** */
	public static void main(String args[]) {
		try {
			String FileName = "e:/AutoLang/Finite/Finite.8";
			FileInputStream inputStream = new FileInputStream(FileName);
			InputStreamReader streamReader = new InputStreamReader(inputStream);

			FiniteAutomaton automaton = new Finite(streamReader);
			automaton.InvertTransitionFunction();
			automaton.equivalence();
			// automaton.read();
			// automaton.ComeOn();
			// automaton.NFAtoDFA();
		} catch (FileNotFoundException e) {
			System.out.println("File not found");
		} catch (IOException e) {
			System.out.println("Wrong input");
		}
	}
}