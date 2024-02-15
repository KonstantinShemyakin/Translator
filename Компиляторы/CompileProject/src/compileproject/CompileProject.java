/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package compileproject;

import java.util.List;

/**
 *
 * @author Student
 */
public class CompileProject {
    public static void main(String[] args) {
        List<Lexeme> lexemLst = LexFileScanner.readLexFile("C:\\Users\\Student\\Desktop\\Компиляторы\\01_Parse\\test.lex");
        CustomScanner customScanner = new CustomScanner(lexemLst);
    }
}
