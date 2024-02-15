package Boolean;
//Версия 04.05.2010
import java.util.*;
import java.io.*;

class Boolean {
	final int LEFTBR = '(';
	final int RIGHTBR = ')';

	final int NOT = '~';
	final int DISJ = '|';
	final int CONJ = '&';
	final int IDENT = 1;
	final int EOF = -1;
	FileWriter outFile;
	StreamTokenizer tok;
	int lexType;
	int nodeLabel = 2;

	Boolean(Reader r, FileWriter w) throws IOException {
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
			BoolExpr();
		} catch (syntaxError e) {
		} catch (lexicalError e) {

		}
	}

	/** *********************************************************************** */
	class TreeNode {
		int op;
		TreeNode left = null, right = null;
		String leaf = null;
		boolean sign;
		int trueLab, falseLab;

		TreeNode(int o) {
			op = o;
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

			case LEFTBR:
				return tok.ttype;
			case RIGHTBR:
				return tok.ttype;
			case DISJ:
				return tok.ttype;
			case CONJ:
				return tok.ttype;
			case NOT:
				return tok.ttype;
			case StreamTokenizer.TT_WORD:
				return IDENT;
			case StreamTokenizer.TT_EOF:
				return EOF;
			default:
				throw new lexicalError();
			}
		} catch (IOException e) {
			System.out.println("Wrong input");
		}
		return 0;
	}

	/** *********************************************************************** */
	TreeNode Atom() throws syntaxError, lexicalError, IOException {
		try {
			if (lexType == LEFTBR) {
				TreeNode tree = Disjunction();
				if ((lexType = yylex()) != RIGHTBR)
					throw new syntaxError();
				return tree;
			} else if (lexType == IDENT) {
				TreeNode node = new TreeNode(0);
				node.leaf = new String(tok.sval);
				return node;
			} else
				throw new syntaxError();

		} catch (lexicalError e) {
		}
		return null;
	}

	/** *********************************************************************** */

	TreeNode Factor() throws syntaxError, lexicalError, IOException {
		try {
			lexType = yylex();
			if (lexType == NOT) {
				TreeNode node = new TreeNode(NOT);
				node.left = Factor();
				return node;
			} else
				return Atom();

		} catch (syntaxError e) {
		}
		return null;
	}

	/** *********************************************************************** */

	TreeNode Conjunction() throws syntaxError, lexicalError, IOException {
		TreeNode node = null, newNode, newNode1;
		try {
			int first = 0;
			do {
				newNode = Factor();
				if (first == 0) {
					node = new TreeNode(0);
					node.left = newNode;
				} else if (first == 1){
					node.right = newNode;
					node.op = CONJ;
				}
				else {
					newNode1 = new TreeNode(CONJ);
					newNode1.left = node;
					newNode1.right = newNode;
					node =newNode1;
				}
				first++;
			} while (yylex() == CONJ);
			tok.pushBack();
		} catch (syntaxError e) {
		}
		return node;
	}

	/** *********************************************************************** */

	TreeNode Disjunction() throws syntaxError, lexicalError, IOException {
		TreeNode node = null, newNode, newNode1;
		try {
			int first = 0;
			do {
				newNode = Conjunction();
				if (first == 0) {
					node = new TreeNode(0);
					node.left = newNode;
				} else if (first == 1){
					node.right = newNode;
					node.op = DISJ;
				}
				else {
					newNode1 = new TreeNode(DISJ);
					newNode1.left = node;
					newNode1.right = newNode;
					node =newNode1; 
				}
				first++;
			} while (yylex() == DISJ);
			tok.pushBack();
		} catch (syntaxError e) {
		}
		return node;
	}

	/** *********************************************************************** */
	void TreeWalk(TreeNode tree) throws IOException {
		if (tree.leaf != null) {
				outFile.write("TST " + tree.leaf + "\n");
			if (tree.sign)
				outFile
						.write("BNE " + String.valueOf((int) tree.trueLab)
								+ "\n");
			else
				outFile.write("BEQ " + String.valueOf((int) tree.falseLab)
						+ "\n");
		} else if (tree.op == 0) {
			tree.left.falseLab = tree.falseLab;
			tree.left.trueLab = tree.trueLab;
			tree.left.sign = tree.sign;
			TreeWalk(tree.left);
		} else if (tree.op == NOT) {
			tree.left.falseLab = tree.trueLab;
			tree.left.trueLab = tree.falseLab;
			tree.left.sign = !tree.sign;
			TreeWalk(tree.left);
		} else if (tree.op == CONJ) {
			int rightNode = nodeLabel++;
			tree.left.falseLab = tree.falseLab;
			tree.left.trueLab = rightNode;
			tree.left.sign = false;
			TreeWalk(tree.left);
			outFile.write(String.valueOf((int) rightNode) + ":\n");
			tree.right.falseLab = tree.falseLab;
			tree.right.trueLab = tree.trueLab;
			tree.right.sign = tree.sign;
			TreeWalk(tree.right);
		} else // if (tree.op == DISJ)
		{
			int rightNode = nodeLabel++;
			tree.left.falseLab = rightNode;
			tree.left.trueLab = tree.trueLab;
			tree.left.sign = true;
			TreeWalk(tree.left);
			outFile.write(String.valueOf((int) rightNode) + ":\n");
			tree.right.falseLab = tree.falseLab;
			tree.right.trueLab = tree.trueLab;
			tree.right.sign = tree.sign;
			TreeWalk(tree.right);
		}
	}

	/** *********************************************************************** */
	void BoolExpr() throws syntaxError, lexicalError, IOException {
		try {
			TreeNode tree = Disjunction();
			tree.sign = false;
			tree.falseLab = 0;
			tree.trueLab = 1;
			TreeWalk(tree);
		} catch (syntaxError e) {
		}
	}

	/** ************************************************************************* */
	public static void main(String args[]) {
		try {
			String inFileName = "e:/AutoLang/Bool/Bool.1";
			FileInputStream inputStream = new FileInputStream(inFileName);
			InputStreamReader streamReader = new InputStreamReader(inputStream);
			String outFileName = "e:/AutoLang/Bool/BoolOut";
			FileWriter outStream = new FileWriter(outFileName);
			Boolean TL = new Boolean(streamReader, outStream);
			outStream.close();
		} catch (FileNotFoundException e) {
			System.out.println("File not found");
		} catch (IOException e) {
			System.out.println("Wrong input");
		}
	}
	/** ************************************************************************ */
}