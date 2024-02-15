package ToyLang;
//Версия 04.05.2010
import java.util.*;
import java.io.*;

public class ToyLang {
	final int LEFTBR = '(';
	final int RIGHTBR = ')';
	final int LEFTSQBR = '[';
	final int RIGHTSQBR = ']';
	final int COLN = ':';
	final int ASTERIC = '*';
	final int SEMICOLN = ';';
	final int PLUS = '+';
	final int EQ = '=';
	final int POINT = '.';
	final int COMMA = ',';
	final int BEGIN = 1;
	final int END = 2;
	final int PROGRAM = 3;
	final int VAR = 4;
	final int TYPE = 5;
	final int ARRAY = 6;
	final int OF = 7;
	final int IDENT = 8;
	final int VAROBJECT = 1;
	final int TYPEOBJECT = 2;
	StreamTokenizer tok;
	FileWriter outFile;
	int blockNumber=0;
	LinkedList EnvironStack = new LinkedList();

	/*
	 * Это стек сред блоков
	 */
	/*
	 * TElement - это класс, описывающий объекты программы. В нашем случае это
	 * может быть тип (TYPEOBJECT) или переменная (VAROBJECT).
	 */
	class TElement {
		int object; // Переменная или тип
		String objectName; // Только для отладки
		TElement typeRef = null; // Ссылка на описатель базового типа
		ArrayList IndexList = null; // Список индексов
		int level; //Block level
		TElement(int t) {
			object = t;
		}

		TElement() {
		}
	}

	TElement intRef = new TElement(TYPEOBJECT);

	class TElementRef {
		TElement TER;
		int indexNo;
	}

	class Code {
		String code;
	}

	class Label {
		int label;
	}

	ToyLang(Reader r, FileWriter w) throws IOException {
		outFile = w;
		tok = new StreamTokenizer(r);
		tok.resetSyntax();
		tok.whitespaceChars(0, ' ');
		tok.eolIsSignificant(false);
		tok.wordChars('a', 'z');
		tok.wordChars('A', 'Z');
		tok.parseNumbers();
		tok.ordinaryChar('.');

		try {
			ToyParser();
		} catch (syntaxError e) {
		} catch (lexicalError e) {
		} catch (contextError e) {
		}
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

	class contextError extends Exception {
		contextError() {
			System.out.println("Контекстная ошибка:");
		}
	}

	void Error(String mess) throws contextError {
		System.out.println(mess);
		throw new contextError();
	}

	int yylex() throws lexicalError, IOException {
		try {
			tok.nextToken();
			System.out.print("Лексема ");
			if (tok.sval != null)
				System.out.print(tok.sval);
			else {
				System.out.print((char) tok.ttype);
			}
			System.out.println();
			switch (tok.ttype) {
			case EQ:
				return tok.ttype;
			case SEMICOLN:
				return tok.ttype;
			case StreamTokenizer.TT_NUMBER:
				return tok.ttype;
			case LEFTBR:
				return tok.ttype;
			case RIGHTBR:
				return tok.ttype;
			case LEFTSQBR:
				return tok.ttype;
			case RIGHTSQBR:
				return tok.ttype;
			case COLN:
				return tok.ttype;
			case ASTERIC:
				return tok.ttype;
			case PLUS:
				return tok.ttype;
			case POINT:
				return tok.ttype;
			case COMMA:
				return tok.ttype;
			case StreamTokenizer.TT_WORD:
				if (tok.sval.equals("begin"))
					return BEGIN;
				else if (tok.sval.equals("end"))
					return END;
				else if (tok.sval.equals("program"))
					return PROGRAM;
				else if (tok.sval.equals("var"))
					return VAR;
				else if (tok.sval.equals("type"))
					return TYPE;
				else if (tok.sval.equals("array"))
					return ARRAY;
				else if (tok.sval.equals("of"))
					return OF;
				else
					return IDENT;
			default:
				throw new lexicalError();
			}
		} catch (IOException e) {
			System.out.println("Wrong input");
		}
		return 0;
	}

	/** ************************************************************************* */
	void ToyParser() throws syntaxError, lexicalError, contextError,
			IOException {
		Prog();
	}

	// Нет проверки на конец файла
	/** ************************************************************************* */
	// Prog ::= 'program' Ident ';' Block 'END'
	void Prog() throws syntaxError, lexicalError, contextError, IOException {
		try {
			String Ident;
			int i = 0;
			if (yylex() != PROGRAM)
				throw new syntaxError();
			if (yylex() == IDENT) {
				Ident = new String(tok.sval);
			} else
				throw new syntaxError();
			if (yylex() != SEMICOLN)
				throw new syntaxError();
			outFile.write("class " + Ident + "{\n");
			outFile.write("public static void main(String args[]) {\n");
			outFile.write("int ");
			for (i = 0; i < 5; i++)
				outFile.write("XXXX_" + i + ",");
			outFile.write("XXXX_6;\n");
			Block();
			if (yylex() != END)
				throw new syntaxError();
			outFile.write("}}\n");
		} catch (lexicalError e) {
		}
	}

	/** ************************************************************************* */
	// Block ::= [ ( Declaration ) ] 'begin' [ (Statement) ] 'end'
	void Block() throws syntaxError, lexicalError, contextError, IOException {
		int lextype;
		HashMap Environ = new HashMap();
		// Создать среду блока
		if (EnvironStack.isEmpty()) {
			// Блок программы
			/* Занести int */
			String intName = new String("integer");
			intRef.objectName = intName;
			Environ.put(intName, intRef);
		}
		blockNumber++;
		EnvironStack.addFirst(Environ);
		// Добавить среду блока к списку сред
		try {
			while ((lextype = yylex()) == TYPE || lextype == VAR)
				if (lextype == TYPE)
					// Declaration ::= 'type' ( Type_Decl )
					Type_Decl();
				else if (lextype == VAR)
					// Declaration ::= 'var' ( Var_Decl )
					Var_Decl();
			if (lextype == BEGIN)
				while (true) {
					Statement();
					if (yylex() == END)
						break;
					else
						tok.pushBack();
				}
			else
				throw new syntaxError();

		} catch (lexicalError e) {
		}
		EnvironStack.removeFirst();
		// Удалить среду блока
	}

	/** ************************************************************************* */
	// Type_Decl ::=  Ident '=' Type_Defin ';'
	void Type_Decl() throws syntaxError, lexicalError, contextError,
			IOException {
		while (yylex() == IDENT) {
			String Ident = new String(tok.sval);
			if (!((HashMap) EnvironStack.getFirst()).containsKey(Ident)) {
				TElement PV = new TElement(TYPEOBJECT);
				PV.objectName = Ident;
				if (yylex() == EQ) {
					Type_Defin(PV);
					if (PV != null)
						((HashMap) EnvironStack.getFirst()).put(Ident, PV);
					if (yylex() != SEMICOLN)
						throw new syntaxError();
				}
			} else
				Error("Повторное объявление " + Ident);
		}
		tok.pushBack();
	}

	/** ************************************************************************* */
	// Type_Defin ::= 'ARRAY' Index 'OF' Type_Defin
	// Type_Defin ::= Type_Use
	void Type_Defin(TElement TypeRef)
	// TypeRef – синтезируемый атрибут, в который передается ссылка на
			// сформированный тип
			throws syntaxError, lexicalError, contextError, IOException {
		int lexVal = yylex();
		if (lexVal == ARRAY) {
			if (yylex() != tok.TT_NUMBER)
				throw new syntaxError();
			int arraySize = (int) tok.nval;
			if (yylex() != OF)
				throw new syntaxError();
			if (TypeRef.IndexList == null)
				TypeRef.IndexList = new ArrayList();
			TypeRef.IndexList.add(new Integer(arraySize));
			Type_Defin(TypeRef);
		} else if (lexVal == IDENT) {
			tok.pushBack();
			TElementRef TER = new TElementRef();
			Type_Use(TER);
			TypeRef.typeRef = TER.TER;
		} else
			throw new syntaxError();
	}

	/** ************************************************************************* */
	// Var_Decl ::=  Ident_List ':' Type_Use ';'
	void Var_Decl() throws syntaxError, lexicalError, contextError, IOException {
		while (yylex() == IDENT) {
			TElementRef TER = new TElementRef();
			TElement PV;// = new TElement();
			LinkedList IdentSet = new LinkedList();
			Ident_List(IdentSet);
			if (yylex() != COLN)
				throw new syntaxError();
			Type_Use(TER);
			PV = TER.TER;
			/* Ссылка на тип элемента массива */
			if (IdentSet != null) {
				Iterator itr = IdentSet.iterator();
				HashMap Env = (HashMap) EnvironStack.getFirst();
				while (itr.hasNext()) {
					String Ident = (String) itr.next();
					if (!Env.containsKey(Ident)) {
						TElement newVar = new TElement(VAROBJECT);
						newVar.objectName = Ident;
						newVar.typeRef = PV;
						newVar.level = blockNumber;
						Env.put(Ident, newVar);
						outFile.write("\nint " + Ident+"_"+newVar.level);
						TElement eqType = null;
						while ((PV.IndexList == null) & (PV.typeRef != null))
							// Добраться до базового типа
							// для Т1=Т2 IndexList == null & eqType.typeRef !=
							// null
							// для integer IndexList == null & eqType.typeRef
							// ==null
							PV = PV.typeRef;
						eqType = PV;
						if (eqType.typeRef != null) // Не integer
						{
							int i, j = 0;
							do
								// На случай цепочки T1 = array 1 of T2
								// T2 = array 2 of T3 ...
								if (eqType.IndexList != null) {
									j = eqType.IndexList.size();
									for (i = 0; i < j; i++)
										outFile.write("[]");
									eqType = eqType.typeRef;
								}
							while (eqType.typeRef != null);
							outFile.write("=new int");
							eqType = PV;
							do
								if (eqType.IndexList != null) {
									j = eqType.IndexList.size();
									for (i = 0; i < j; i++)
										outFile.write("["
												+ (Integer) eqType.IndexList
														.get(i) + "]");
									eqType = eqType.typeRef;
								}
							while (eqType.typeRef != null);
						}
						outFile.write(";\n");
					} else
						Error("Повторное объявление " + Ident);
				}
			}
			if (yylex() != SEMICOLN)
				throw new syntaxError();
		}
		tok.pushBack();
	}

	/** ************************************************************************* */
	// Type_Use ::= Ident
	void Type_Use(TElementRef TypeRef)
	// ref – синтезируемый атрибут, в который передается ссылка на
			// сформированный тип
			throws syntaxError, lexicalError, contextError, IOException {
		if (yylex() == IDENT) {
			String Ident = new String(tok.sval);
			TElement PV = null;
			HashMap Environ = null;
			Iterator itr = EnvironStack.iterator();
			while (itr.hasNext()) {
				Environ = (HashMap) itr.next();
				if (Environ.containsKey(Ident)) {
					PV = (TElement) Environ.get(Ident);
					if (PV.object != TYPEOBJECT) {
						Error(Ident + " Не идентификатор типа");
						PV = null;
						break;
					}
				}
			}
			TypeRef.TER = PV;
			if (PV == null) {
				Error(Ident + " Не объявлен");
			}
		} else
			throw new syntaxError();
	}

	/** ************************************************************************* */
	// Ident_List ::= ( Ident / ',' )
	void Ident_List(LinkedList IdentSet) throws syntaxError, lexicalError,
			IOException {
		do {
			IdentSet.addFirst(new String(tok.sval));
			if (yylex() != COMMA)
				break;
			if (yylex() != IDENT)
				throw new syntaxError();
		} while (true);
		tok.pushBack();
	}

	/** ************************************************************************* */
	// Statement ::= Block ';'
	// Statement ::= Variable '=' Expression';'
	void Statement() throws syntaxError, lexicalError, contextError,
			IOException {
		int lextype = yylex();
		if ((lextype == BEGIN) || (lextype == TYPE) || (lextype == VAR)) {
			tok.pushBack();
			Block();
		} else {
			TElementRef ref1 = new TElementRef();
			TElement ref;
			Code codeVar = new Code();
			Code codeExp = new Code();
			int i;
			tok.pushBack();
			Variable(ref1, codeVar);
			if (yylex() == EQ) {
				TElementRef ref2 = new TElementRef();
				Label labelExp = new Label();
				Expression(ref2, codeExp, labelExp);
				if (ref1.TER == ref2.TER) {
					if (ref1.TER == intRef) {
						if (labelExp.label == 0)
							outFile.write(codeVar.code + "=" + codeExp.code
									+ ";\n");
						else
							outFile.write(codeExp.code + codeVar.code + "="
									+ "R" + labelExp.label + ";\n");
					} else {// Здесь может быть два случая:
						// 1)ref1.indexNo == 0 - это значит, что ref1.TER
						// указывает на базовый тип.
						// 2) ref1.indexNo != 0 - это значит, что ref1.TER
						// указывает на тип переменной и использовано число
						// индексов, меньшее числа индексов в определении типа.
						// В этом случае сначала надо "добрать" до базового
						// типа, а потом генерировать выборку из базового типа.
						int listSize = ref1.TER.IndexList.size();
						i = 0;
						int j = 0;
						if (ref1.indexNo != 0) {// Добираем до базового типа
							for (i = ref1.indexNo; i < listSize; i++, j++)
								outFile.write("for (XXXX_" + i + "=0;XXXX_" + i
										+ "<"
										+ (Integer) ref1.TER.IndexList.get(i)
										+ ";XXXX_" + i + "++)\n");
							ref = ref1.TER.typeRef;
						} else
							ref = ref1.TER;
						if (ref.IndexList != null)
							listSize = ref.IndexList.size();
						else
							listSize = 0;

						// Для базового типа
						for (i = 0; i < listSize; i++)
							outFile.write("for (XXXX_" + (i + j) + "=0;XXXX_"
									+ (i + j) + "<"
									+ (Integer) ref.IndexList.get(i) + ";XXXX_"
									+ (i + j) + "++)\n");

						outFile.write(codeVar.code);
						for (i = 0; i < listSize + j; i++)
							outFile.write("[XXXX_" + (i + j) + "]");
						outFile.write("=" + codeExp.code);
						for (i = 0; i < listSize + j; i++)
							outFile.write("[XXXX_" + (i + j) + "]");
						outFile.write(";\n");
					}
				} else
					Error("Типы значений различны");
			} else
				throw new syntaxError();
			if (yylex() != SEMICOLN)
				throw new syntaxError();
		}
	}

	/** ************************************************************************* */
	// Variable ::= Ident Access
	void Variable(TElementRef typeRef, Code codeVar)
	// typeRef – синтезируемый атрибут, в который передается ссылка на тип
			// переменной
			throws syntaxError, lexicalError, contextError, IOException {
		int arraySize = 0;
		// TElementRef typeRef = new TElementRef();
		if (yylex() == IDENT) {
			String Ident = new String(tok.sval);
			HashMap Environ = null;
			TElement PV = null;
			Iterator itr = EnvironStack.iterator();
			while (itr.hasNext()) {
				Environ = (HashMap) itr.next();
				if (Environ.containsKey(Ident)) {
					PV = (TElement) Environ.get(Ident);
					if (PV.object == VAROBJECT) {
						/* Получаем ссылку на TElement тип переменной */
						typeRef.TER = PV.typeRef;
						codeVar.code = Ident+"_"+PV.level;
					} else {
						Error(Ident + " Не идентификатор переменной");
						PV = null;
						break;
					}
				}
			}
			if (PV == null)
				Error(Ident + " Не объявлен");
		} else
			throw new syntaxError();
		Access(0, typeRef, codeVar);
	}

	/** ************************************************************************* */
	// Access ::= '[' Expression ']' Access
	// Access ::=
	void Access(int indexNo, TElementRef typeRef, Code codeAccess)
	// typeRef – синтезируемый атрибут, в который передается ссылка на тип
			// переменной
			// indexNo – наследуемый атрибут – число индексов
			throws syntaxError, lexicalError, contextError, IOException {
		if (yylex() == LEFTSQBR) {
			TElementRef ref = new TElementRef();
			Code c = new Code();
			Label label = new Label();
			Expression(ref, c, label);
			if (ref.TER != intRef)
				Error("Тип переменной в выражении должен быть integer");
			if (yylex() != RIGHTSQBR)
				throw new syntaxError();
			codeAccess.code += "[" + c.code + "]";
			Access(indexNo + 1, typeRef, codeAccess);
		} else {
			tok.pushBack();
			TElement eqType = typeRef.TER;
			while ((eqType.IndexList == null)
			/* Список эквивалентных типов */
			& (eqType.typeRef != null))
				/* Пройти по списку эквивалентных типов но не далее intRef */
				eqType = eqType.typeRef;
			if (eqType == intRef) {
				typeRef.TER = intRef;
				typeRef.indexNo = 0;
			} else if (indexNo == eqType.IndexList.size()) {
				// Взяли число индексов, равное числу индексов в описании типа,
				// поэтому тип элемента равен типу элемента массива
				typeRef.TER = eqType.typeRef;
				typeRef.indexNo = 0;
			} else if (indexNo > eqType.IndexList.size())
				Error("Выход за пределы размерности массива");
			else {// Число индексов в использовании переменной меньше числа
				// индексов в базовом типе; сообщаем об этом в оператор
				// присваивания.
				typeRef.TER = eqType;
				typeRef.indexNo = indexNo;
			}
		}
	}

	/** ************************************************************************* */
	// Expression ::= Term ('+'/Term)
	void Expression(TElementRef ref, Code codeExp, Label labelRefExp)
	// ref – синтезируемый атрибут, в который передается ссылка на тип
			// переменной
			// labelRefExp – метка в алгоритме Сети=Ульмана
			throws syntaxError, lexicalError, contextError, IOException {
		TElement typeRef = null;
		Label labelRefTerm = new Label();
		Code codeTerm = new Code();
		int label0, rightLabel, leftLabel = 0;
		boolean first = true;
		String code1 = new String();
		do {
			Term(ref, codeTerm, labelRefTerm);
			if (!first & labelRefTerm.label == 0) {
				labelRefTerm.label = 1;
				codeTerm.code = "R1=" + codeTerm.code + "\n";
			}
			rightLabel = labelRefTerm.label;
			if (first) {
				leftLabel = label0 = labelRefTerm.label;
				code1 = codeTerm.code;
			} else {
				rightLabel = labelRefTerm.label;
				if (rightLabel > leftLabel) {
					label0 = rightLabel;
					if (leftLabel == 0)
						code1 = codeTerm.code + "R" + rightLabel + "=" + code1
								+ "+R" + rightLabel + ";\n";
					else
						code1 = codeTerm.code + code1 + "R" + leftLabel + "+R"
								+ rightLabel + ";\n";
					leftLabel = label0;
				} else if (rightLabel < leftLabel) {
					label0 = leftLabel;
					code1 = code1 + codeTerm.code + "R" + leftLabel + "=R"
							+ leftLabel + "+R" + rightLabel + ";\n";
				} else {// Метки равны
					label0 = leftLabel + 1;
					code1 = codeTerm.code + "R" + label0 + "=" + "R"
							+ rightLabel + ";\n" + code1 + "R" + label0 + "="
							+ "R" + leftLabel + "+R" + label0 + ";\n";
					leftLabel = label0;
				}
			}
			if (!first && ((typeRef != intRef)|(typeRef != ref.TER)))
				Error("Тип переменной в выражении должен быть integer");
			typeRef = ref.TER;
			first = false;
		} while (yylex() == PLUS);
		tok.pushBack();
		codeExp.code = code1;
		labelRefExp.label = label0;
	}

	/** ************************************************************************* */
	// Term ::= Factor (Factor/'*')
	void Term(TElementRef ref, Code codeTerm, Label labelRefTerm)
	// ref – синтезируемый атрибут, в который передается ссылка на тип
			// переменной
			// labelRefExp – метка в алгоритме Сети=Ульмана
			throws syntaxError, lexicalError, contextError, IOException {
		TElement typeRef = null;
		Label labelRefFactor = new Label();
		int label0, rightLabel, leftLabel = 0;
		boolean first = true;
		String code1 = new String();
		Code codeFactor = new Code();
		do {
			Factor(ref, codeFactor, labelRefFactor);
			// Проблема в том, что при замене рекурсии циклом не удается
			// определить, является ли потомок левым
			if (!first & labelRefFactor.label == 0) {
				labelRefFactor.label = 1;
				codeFactor.code = "R1=" + codeFactor.code + ";\n";
			}
			rightLabel = labelRefFactor.label;
			if (first) {
				leftLabel = label0 = labelRefFactor.label;
				code1 = codeFactor.code;
			} else {
				rightLabel = labelRefFactor.label;
				if (rightLabel > leftLabel) {
					label0 = rightLabel;
					if (leftLabel == 0)
						code1 = codeFactor.code + "R" + rightLabel + "="
								+ code1 + "*R" + rightLabel + ";\n";
					else
						code1 = codeFactor.code + code1 + "R" + leftLabel
								+ "*R" + rightLabel + ";\n";
					leftLabel = label0;
				} else if (rightLabel < leftLabel) {
					label0 = leftLabel;
					code1 = code1 + codeFactor.code + "R" + leftLabel + "=R"
							+ leftLabel + "*R" + rightLabel + ";\n";
				} else {// Метки равны
					label0 = leftLabel + 1;
					code1 = codeFactor.code + "R" + label0 + "=" + "R"
							+ rightLabel + ";\n" + code1 + "R" + label0 + "="
							+ "R" + leftLabel + "*R" + label0 + ";\n";
					leftLabel = label0;
				}
			}
			if (!first && ((typeRef != intRef)|(typeRef != ref.TER)))
				Error("Тип переменной в выражении должен быть integer");
			typeRef = ref.TER;
			first = false;
		} while (yylex() == ASTERIC);
		codeTerm.code = code1;
		labelRefTerm.label = label0;
		tok.pushBack();
	}

	/** ************************************************************************* */
	// Factor ::= Variable
	// Factor ::= '(' Expression ')'
	// Factor ::= Integer
	void Factor(TElementRef ref, Code codeFac, Label labelFac)
	// ref – синтезируемый атрибут, в который передается ссылка на тип
			// переменной
			// labelRefExp – метка в алгоритме Сети=Ульмана
			throws syntaxError, lexicalError, contextError, IOException {
		int lexVal = yylex();
		if (lexVal == LEFTBR) {
			Expression(ref, codeFac, labelFac);
			if (ref.TER != intRef)
				Error("Тип переменной в выражении должен быть integer");
			if (yylex() != RIGHTBR)
				throw new syntaxError();
		} else {
			if (lexVal == tok.TT_NUMBER) {
				ref.TER = intRef;
				codeFac.code = String.valueOf((int) tok.nval);
			} else {
				tok.pushBack();
				Variable(ref, codeFac);
				labelFac.label = 0;
			}
		}
	}

	/** ************************************************************************* */
	public static void main(String args[]) {
		try {
			String inFileName = "e:/AutoLang/ToyLang/Toy.3";
			FileInputStream inputStream = new FileInputStream(inFileName);
			InputStreamReader streamReader = new InputStreamReader(inputStream);
			String outFileName = "e:/AutoLang/ToyLang/ToyLangJava.java";
			FileWriter outStream = new FileWriter(outFileName);
			ToyLang TL = new ToyLang(streamReader, outStream);
			outStream.close();
		} catch (FileNotFoundException e) {
			System.out.println("File not found");
		} catch (IOException e) {
			System.out.println("Wrong input");
		}
	}
	/** ************************************************************************ */
}
