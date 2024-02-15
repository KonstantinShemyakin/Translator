/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package compileproject;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


public class LexFileScanner {
    static public List<Lexeme> readLexFile(String filePath) {
        List<Lexeme> lexemeLst = new ArrayList<>();
        try (Scanner scan = new Scanner(new File(filePath))) {
            while (scan.hasNextLine()) {
                String line = scan.nextLine();
                String[] splitLine = line.split(" ");
                Lexeme lex = createLexeme(splitLine);
                lexemeLst.add(lex);
                System.err.println(lex.makeInfoStr());
            }
        } catch (NullPointerException | FileNotFoundException ex) {
            System.err.println(ex.getMessage());
        }
        return lexemeLst;
    }
    
    static private Lexeme createLexeme(String[] splitLine) {
        return new Lexeme (
            Lexeme.Group.values()[new Integer(splitLine[0])],
            Lexeme.Type.values()[new Integer(splitLine[1])],
            new Integer(splitLine[2]),
            new Integer(splitLine[3]),
            new Integer(splitLine[4]),
            new Integer(splitLine[5]),
            Lexeme.Group.Eof.ordinal() == new Integer(splitLine[0]) ? null : (Object)splitLine[7]
        );
    }
}
