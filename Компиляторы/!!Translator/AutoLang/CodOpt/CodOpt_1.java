package CodOpt;
//Версия 04.05.2010
import java.util.*;
import java.io.*;

public class CodOpt {
	final int CONST = '%';
	final int ASS = '=';
	final int PLUS = '+';
	final int LEFTSQBR = '[';
	final int RIGHTSQBR = ']';
	final int LEFTBR = '(';
	final int RIGHTBR = ')';
	final int REF = '@';
	final int EOF = -1;
	final int IDENT = '^';
	final int REG = 3;
	final int STAT = 4;
	int lexType, regNumber = 0;
	FileWriter outFile;
	StreamTokenizer tok;

	Integer REGObject = new Integer(REG);

	class Pattern {
		int patNumber, nodeType, cost;
	}

	class optimalPattern {
		int optCost;// Наименьшая стоимость возможного применения образцов в
		// данной вершине
		int patNumber;// Номер образца, дающего оптимальное значение
	}

	class TreeNode {
		int op;
		HashMap appliedPatterns; // Для каждого нетерминала хранится номер
		// применимого образца, дающего минимальную
		// стоимость именно для этого нетерминала

		TreeNode left = null, right = null;
		String leaf = null;
	}

	/*
	 * Выбор применимых в данной вершине образцов осуществляется следующим
	 * образом. Обходим дерево слева-направо снизу-вверх. Выбираем операцию в
	 * данной вершине. Для каждого образца с данной операцией рекурсивно
	 * спускаемся в потомков и сопоставляем с соответствущей вершиной дерева.
	 * Если в образце и одновременно в дереве в соответствующей вершине -
	 * операция, спускаемся дальше. Если в образце в вершине (листе образца)
	 * нетерминал, смотрим есть ли этот нетерминал во множестве appliedPatterns
	 * вершины. Если есть - берем стоимость для нетерминала в этой вершине и
	 * включаем ее в стоимость применения образца.Если нет - образец неприменим.
	 * Если есть цепные правила с правой частью - нетерминалом в данной вершине,
	 * рассматриваем их наряду с другими. Если проходим по всему дереву образца
	 * удачно, то, если в вершине во множестве appliedPatterns для нетерминала в
	 * вершине образца не было данных, заносим optimalPattern для этого
	 * нетерминала. Если в вершине во множестве appliedPatterns для нетерминала
	 * в вершине образца были данные, смотрим, дает ли вновь рассмотренный
	 * образец меньшую стоимость. Если да, заменяем optimalPattern на данные
	 * нового образца.
	 */
	/*
	 * Построение оптимального покрытия осуществляется следующим образом.В корне
	 * выбираем образец с минимальной стоимостью. Обходим дерево слева-направо
	 * сверху-вниз. При попадании в вершину (сначала в корне) мы знаем, какой
	 * нетерминал должен быть выбран. Для каждого нетермиала в вершине хранится
	 * номер оптимально применимого для данного нетермиала образца. По этому
	 * образцу спускаемся до его листьев. При обратном движении снизу-вверх для
	 * каждого выбранного образца генерируем код.
	 */

	void Matched(TreeNode node) {
		System.out.println("Enter op=" + (char) node.op + "\nLeft");
		if (node.op != CONST) {
			Matched(node.left);
			System.out.println("After left op=" + (char) node.op);
			if ((node.op == ASS) | (node.op == PLUS))
				Matched(node.right);
			System.out.println("After right op=" + (char) node.op);
		}
		optimalPattern newPattern;
		int newCost = 0, patNumber = 0, minCost = 1000000;
		Integer nonTerm = null;
		boolean found = false;
		switch (node.op) {
		case CONST: {
			System.out.println("leaf " + node.leaf);
			found = true;
			nonTerm = REGObject;
			minCost = 2;
			patNumber = 1;
			break;
		}
		case ASS: {
			if ((node.left.op == PLUS)
					&& node.left.left.appliedPatterns.containsKey(REGObject)
					&& node.left.right.op == CONST
					&& node.right.appliedPatterns.containsKey(REGObject)) {
				newCost = 4
						+ ((optimalPattern) node.left.left.appliedPatterns
								.get(REGObject)).optCost
						+ ((optimalPattern) node.right.appliedPatterns
								.get(REGObject)).optCost;
				if (newCost < minCost) {
					minCost = newCost;
					patNumber = 2;
				}
				nonTerm = REGObject;
				found = true;
			}
			if (node.left.appliedPatterns.containsKey(REGObject)
					&& node.left.appliedPatterns.containsKey(REGObject)) {
				newCost = 2
						+ ((optimalPattern) node.left.appliedPatterns
								.get(REGObject)).optCost
						+ ((optimalPattern) node.right.appliedPatterns
								.get(REGObject)).optCost;
				if (newCost < minCost) {
					patNumber = 8;
					minCost = newCost;
				}
				found = true;
				nonTerm = REGObject;
			}
			break;
		}
		case PLUS: {
			if (node.left.appliedPatterns.containsKey(REGObject)
					&& node.left.appliedPatterns.containsKey(REGObject)) {
				newCost = 2
						+ ((optimalPattern) node.left.appliedPatterns
								.get(REGObject)).optCost
						+ ((optimalPattern) node.right.appliedPatterns
								.get(REGObject)).optCost;
				if (newCost < minCost) {
					minCost = newCost;
					patNumber = 5;
				}
				found = true;
				nonTerm = REGObject;
			}
			if (node.left.appliedPatterns.containsKey(REGObject)
					&& node.right.op == CONST) {
				newCost = 3 + ((optimalPattern) node.left.appliedPatterns
						.get(REGObject)).optCost;
				if (newCost < minCost) {
					patNumber = 4;
					minCost = newCost;
				}
				found = true;
				nonTerm = REGObject;
			}
			if ((node.right.op == REF)
					&& (node.right.left.op == PLUS)
					&& node.right.left.left.appliedPatterns
							.containsKey(REGObject)
					&& node.right.left.right.op == CONST
					&& node.left.appliedPatterns.containsKey(REGObject)) {
				newCost = 4
						+ ((optimalPattern) node.right.left.left.appliedPatterns
								.get(REGObject)).optCost
						+ ((optimalPattern) node.left.appliedPatterns
								.get(REGObject)).optCost;
				if (newCost < minCost) {
					patNumber = 6;
					minCost = newCost;
				}
				found = true;
				nonTerm = REGObject;
			}
			break;
		}
		case REF: {
			if ((node.left.op == PLUS)
					&& node.left.left.appliedPatterns.containsKey(REGObject)
					&& node.left.right.op == CONST) {
				newCost = 4 + ((optimalPattern) node.left.left.appliedPatterns
						.get(REGObject)).optCost;
				found = true;
				nonTerm = REGObject;
				if (newCost < minCost) {
					patNumber = 3;
					minCost = newCost;
				}
			}
			if (node.left.appliedPatterns.containsKey(REGObject)) {
				newCost = 2 + ((optimalPattern) node.left.appliedPatterns
						.get(REGObject)).optCost;
				found = true;
				nonTerm = REGObject;
				if (newCost < minCost) {
					patNumber = 7;
					minCost = newCost;
				}
			}
			break;
		}
		}
		if (found) {
			System.out.println("Found patNumber:" + patNumber + " minCost:"
					+ minCost);
			if (node.appliedPatterns == null)
				node.appliedPatterns = new HashMap();
			if (!node.appliedPatterns.containsKey(nonTerm)) {
				newPattern = new optimalPattern();
				newPattern.optCost = minCost;
				newPattern.patNumber = patNumber;
				node.appliedPatterns.put(REGObject, newPattern);
			}
		}
	}

	/** *********************************************************************** */
	class lexicalError extends Exception {
		lexicalError() {
			System.out.println("Лексическая ошибка:");
		}
	}

	/** *********************************************************************** */
	class syntaxError extends Exception {
		syntaxError() {
			System.out.println("Синтаксическая ошибка:");
		}
	}

	/** *********************************************************************** */

	CodOpt(Reader r, FileWriter w) throws IOException {
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
			Assign();
		} catch (syntaxError e) {
		} catch (lexicalError e) {

		}
	}

	/** *********************************************************************** */
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
			case LEFTSQBR:
				return tok.ttype;
			case RIGHTSQBR:
				return tok.ttype;
			case LEFTBR:
				return tok.ttype;
			case RIGHTBR:
				return tok.ttype;
			case ASS:
				return tok.ttype;
			case PLUS:
				return tok.ttype;
			case StreamTokenizer.TT_WORD:
				return IDENT;
			case StreamTokenizer.TT_EOF:
				return EOF;
			case StreamTokenizer.TT_NUMBER:
				return tok.ttype;
			default:
				throw new lexicalError();
			}
		} catch (IOException e) {
			System.out.println("Wrong input");
		}
		return 0;
	}

	/** *********************************************************************** */
	int TreeWalk(TreeNode tree, int type) throws IOException {
		int regI, regJ;
		System.out.println("op=" + (char) tree.op + "\nLeft");
		if (tree.op == CONST)
			System.out.println("leaf " + tree.leaf);
		Integer patType = null;
		switch (type) {
		case REG:
		case STAT:
			patType = REGObject;
		}
		optimalPattern OP = (optimalPattern) tree.appliedPatterns.get(patType);
		switch (OP.patNumber) {
		case 1:
			outFile.write("1: MOVE " + tree.leaf + ",R" + ++regNumber + "\n");
			return regNumber;
		case 2:
			regI = TreeWalk(tree.left.left, REG);
			regJ = TreeWalk(tree.right, REG);
			outFile.write("2: MOVE R" + regJ + "," + tree.left.right.leaf
					+ "(R" + regI + ")\n");
			return regI;
		case 3:
			regI = TreeWalk(tree.left.left, REG);
			outFile.write("3: MOVE " + tree.left.right.leaf + "(R" + regI
					+ "),R" + regI + "\n");
			return regI;
		case 4:
			regI = TreeWalk(tree.left, REG);
			outFile.write("4: ADD " + tree.right.leaf + ",R" + regI + "\n");
			return regI;
		case 5:
			regI = TreeWalk(tree.left, REG);
			regJ = TreeWalk(tree.right, REG);
			outFile.write("5: ADD R" + regI + ",R" + regJ + "\n");
			return regI;
		case 6:
			regI = TreeWalk(tree.left, REG);
			regJ = TreeWalk(tree.right.left.left, REG);
			outFile.write("6: ADD " + tree.right.left.right.leaf + "(R" + regJ
					+ "),R" + regI + "\n");
			return regI;
		case 7:
			regI = TreeWalk(tree.left, REG);
			outFile.write("7: MOVE (R" + regI + "),R" + regI + "\n");
			return regI;
		case 8:
			regI = TreeWalk(tree.left, REG);
			regJ = TreeWalk(tree.right, REG);
			outFile.write("8: MOVE R" + regJ + ",(R" + regI + ")\n");
			return regI;
		}
		return 0;
		/*
		 * { TreeWalk(tree.left); if ((tree.op == PLUS) | (tree.op == ASS)) {
		 * System.out.println("Right"); TreeWalk(tree.right); } }
		 */
	}

	/** *********************************************************************** */
	// Factor ::= Const | Variable | '(' Expression ')'
	TreeNode Factor() throws syntaxError, lexicalError, IOException {
		TreeNode tree = null;
		try {
			lexType = yylex();
			if (lexType == LEFTBR) {
				tree = Expression();
				if ((lexType = yylex()) != RIGHTBR)
					throw new syntaxError();
			} else if (lexType == tok.TT_NUMBER) {
				tree = new TreeNode();
				tree.op = CONST;
				tree.leaf = "#"+String.valueOf((int) tok.nval);
				tree.left = null;
			} else {
				tok.pushBack();
				tree = Variable();
				if (tree.op != CONST) {
					TreeNode newNode = tree;
					tree = new TreeNode();
					tree.op = REF;
					tree.left = newNode;
				}
			}
		} catch (lexicalError e) {
		}
		return tree;
	}

	/** *********************************************************************** */
	// Expression ::= Factor ( '+' Factor )
	TreeNode Expression() throws syntaxError, lexicalError, IOException {
		TreeNode newNode = null, newNode1, node = null;
		boolean first = true;
		try {
			do {
				node = Factor();
				if (first) {
					first = false;
					newNode = node;
				} else {
					newNode1 = new TreeNode();
					newNode1.op = PLUS;
					newNode1.left = newNode;
					newNode1.right = node;
					newNode = newNode1;
				}
			} while (yylex() == PLUS);
			tok.pushBack();
			return newNode;
		} catch (syntaxError e) {
		}
		return null;
	}

	/** *********************************************************************** */
	// Variable ::= Ident [ '[' Expression ']' ]
	TreeNode Variable() throws syntaxError, lexicalError, IOException {
		try {
			lexType = yylex();
			TreeNode node = new TreeNode();
			if (lexType == IDENT) {
				node.op = PLUS;
				node.left = new TreeNode();
				node.left.op = CONST;
				node.right = new TreeNode();
				node.right.op = CONST;
				node.left.leaf = "#" + new String(tok.sval);
				node.right.leaf = "#" + (new String(tok.sval) + "$$");
			} else
				throw new syntaxError();
			if ((lexType = yylex()) == LEFTSQBR) {
				TreeNode newNode = new TreeNode();
				newNode.op = PLUS;
				newNode.left = node;
				node = Expression();
				newNode.right = node;
				if (node.op != CONST) {
					node = new TreeNode();
					node.op = REF;
					node.left = newNode;
				}
				if ((lexType = yylex()) != RIGHTSQBR)
					throw new syntaxError();
				return newNode;
			} else {
				tok.pushBack();
				return node;
			}
		} catch (lexicalError e) {
		}
		return null;
	}

	/** *********************************************************************** */
	// Assign ::= Variable '=' Expression
	void Assign() throws syntaxError, lexicalError, IOException {
		try {
			TreeNode tree = new TreeNode();
			tree.left = Variable();
			if ((lexType = yylex()) != ASS)
				throw new syntaxError();
			tree.right = Expression();
			tree.op = ASS;
			Matched(tree);
			TreeWalk(tree, STAT);
		} catch (syntaxError e) {
		}
	}

	/** ************************************************************************* */
	public static void main(String args[]) {
		try {
			String inFileName = "e:/AutoLang/CodOpt/CodOpt.5";
			FileInputStream inputStream = new FileInputStream(inFileName);
			InputStreamReader streamReader = new InputStreamReader(inputStream);
			String outFileName = "e:/AutoLang/CodOpt/Out";
			FileWriter outStream = new FileWriter(outFileName);
			CodOpt TL = new CodOpt(streamReader, outStream);
			outStream.close();
		} catch (FileNotFoundException e) {
			System.out.println("File not found");
		} catch (IOException e) {
			System.out.println("Wrong input");
		}
	}
}
