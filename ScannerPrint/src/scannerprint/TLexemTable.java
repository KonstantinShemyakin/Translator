/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package scannerprint;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;

/**
 *
 * @author Student
 */

public class TLexemTable {
    ArrayList<TLexemTableInfo> lexems = new ArrayList<>();
    
    public TLexemTable() {
        lexems.add(new TLexemTableInfo(2, 52, 0, 78, "..."));
        lexems.add(new TLexemTableInfo(2, 51, 0, 12, "->"));
        lexems.add(new TLexemTableInfo(2, 59, 0, 80, "::="));
        lexems.add(new TLexemTableInfo(2, 69, 0, 64, "/*+"));
        lexems.add(new TLexemTableInfo(2, 70, 0, 64, "*/"));
        lexems.add(new TLexemTableInfo(2, 68, 0, 64, "--+"));
        lexems.add(new TLexemTableInfo(2, 71, 0, 64, "@"));
        lexems.add(new TLexemTableInfo(2, 53, 0, 2, "%%"));
        lexems.add(new TLexemTableInfo(2, 54, 0, 2, "%{"));
        lexems.add(new TLexemTableInfo(2, 55, 0, 2, "%}"));
        lexems.add(new TLexemTableInfo(2, 56, 0, 2, "%token"));
        lexems.add(new TLexemTableInfo(2, 57, 0, 2, "%left"));
        lexems.add(new TLexemTableInfo(2, 58, 0, 2, "%right"));
        lexems.add(new TLexemTableInfo(2, 66, 0, 2, "/."));
        lexems.add(new TLexemTableInfo(2, 67, 0, 2, "./"));
        lexems.add(new TLexemTableInfo(1, 6, 1, 65535, "+="));
        lexems.add(new TLexemTableInfo(1, 7, 1, 65535, "-="));
        lexems.add(new TLexemTableInfo(1, 8, 1, 65535, "*="));
        lexems.add(new TLexemTableInfo(1, 9, 1, 65535, "/="));
        lexems.add(new TLexemTableInfo(1, 10, 1, 65535, "%="));
        lexems.add(new TLexemTableInfo(1, 11, 1, 65535, "&="));
        lexems.add(new TLexemTableInfo(1, 12, 1, 65535, "|="));
        lexems.add(new TLexemTableInfo(1, 13, 1, 65535, "^="));
        lexems.add(new TLexemTableInfo(1, 17, 3, 65535, "||"));
        lexems.add(new TLexemTableInfo(1, 15, 5, 65535, "|"));
        lexems.add(new TLexemTableInfo(1, 18, 4, 65535, "&&"));
        lexems.add(new TLexemTableInfo(1, 16, 7, 65535, "&"));
        lexems.add(new TLexemTableInfo(1, 19, 6, 65535, "^"));
        lexems.add(new TLexemTableInfo(1, 20, 13, 65535, "~"));
        lexems.add(new TLexemTableInfo(1, 03, 12, 65535, "*"));
        lexems.add(new TLexemTableInfo(1, 04, 12, 65535, "/"));
        lexems.add(new TLexemTableInfo(1, 05, 12, 65535, "%"));
        lexems.add(new TLexemTableInfo(1, 22, 14, 65535, "++"));
        lexems.add(new TLexemTableInfo(1, 01, 11, 65535, "+"));
        lexems.add(new TLexemTableInfo(1, 23, 14, 65535, "--"));
        lexems.add(new TLexemTableInfo(1, 02, 11, 65535, "-"));
        lexems.add(new TLexemTableInfo(1, 24, 8, 65535, "=="));
        lexems.add(new TLexemTableInfo(1, 14, 1, 65535, "="));
        lexems.add(new TLexemTableInfo(1, 25, 8, 65535, "!="));
        lexems.add(new TLexemTableInfo(1, 21, 13, 65535, "!"));
        lexems.add(new TLexemTableInfo(1, 32, 1, 65535, "<<="));
        lexems.add(new TLexemTableInfo(1, 27, 9, 65535, "<="));
        lexems.add(new TLexemTableInfo(1, 30, 10, 65535, "<<"));
        lexems.add(new TLexemTableInfo(1, 26, 9, 65535, "<"));
        lexems.add(new TLexemTableInfo(1, 73, 1, 65535, ">>>="));
        lexems.add(new TLexemTableInfo(1, 72, 10, 65535, ">>>"));
        lexems.add(new TLexemTableInfo(1, 33, 1, 65535, ">>="));
        lexems.add(new TLexemTableInfo(1, 31, 10, 65535, ">>"));
        lexems.add(new TLexemTableInfo(1, 29, 9, 65535, ">="));
        lexems.add(new TLexemTableInfo(1, 28, 9, 65535, ">"));
        lexems.add(new TLexemTableInfo(1, 40, 2, 65535, "?"));
        lexems.add(new TLexemTableInfo(1, 47, 13, 65535, "+"));
        lexems.add(new TLexemTableInfo(1, 48, 13, 65535, "-"));
        lexems.add(new TLexemTableInfo(1, 49, 14, 65535, "++"));
        lexems.add(new TLexemTableInfo(1, 50, 14, 65535, "--"));
        lexems.add(new TLexemTableInfo(2, 34, 0, 65535, "{"));
        lexems.add(new TLexemTableInfo(2, 35, 0, 65535, "}"));
        lexems.add(new TLexemTableInfo(2, 36, 0, 65535, "("));
        lexems.add(new TLexemTableInfo(2, 37, 0, 65535, ")"));
        lexems.add(new TLexemTableInfo(2, 38, 0, 65535, "["));
        lexems.add(new TLexemTableInfo(2, 39, 0, 65535, "]"));
        lexems.add(new TLexemTableInfo(2, 41, 0, 65535, "::"));
        lexems.add(new TLexemTableInfo(2, 42, 0, 65535, "\\"));
        lexems.add(new TLexemTableInfo(2, 43, 0, 65535, "."));
        lexems.add(new TLexemTableInfo(2, 45, 0, 65535, ";"));
        lexems.add(new TLexemTableInfo(2, 46, 0, 65535, ":"));
        lexems.add(new TLexemTableInfo(2, 44, 0, 65535, ","));
        lexems.add(new TLexemTableInfo(14, 60, 0, 32, "#define"));
        lexems.add(new TLexemTableInfo(14, 61, 0, 32, "#undef"));
        lexems.add(new TLexemTableInfo(14, 62, 0, 32, "#ifdef"));
        lexems.add(new TLexemTableInfo(14, 64, 0, 32, "#else"));
        lexems.add(new TLexemTableInfo(14, 65, 0, 32, "#endif"));
    }
    
    public TLexemTable(String syntax_file) {
        File syntax = new File(syntax_file);
        try(FileReader syntax_stream = new FileReader(syntax)) {
            BufferedReader syntax_lexems = new BufferedReader(syntax_stream);
            
            String lexem_line;
            String[] parsed;
            do {
                lexem_line = syntax_lexems.readLine();
                parsed = lexem_line.split(" ");
            } while (Character.isDigit(parsed[0].charAt(0)));
            
            TLexemTableInfo buffer;
            do {
                buffer = new TLexemTableInfo();
                buffer.group = Lexemme.getGroup(Integer.parseInt(parsed[0]));
                buffer.priority = Integer.parseInt(parsed[2]);
                buffer.type = Integer.parseInt(parsed[1]);
                buffer.mask = Integer.parseInt(parsed[3]);
                buffer.text = parsed[4];
                lexems.add(buffer);
                lexem_line = syntax_lexems.readLine();
                parsed = lexem_line.split(" ");
            } while (lexem_line != null);
        }
        catch(IOException ex) {
            System.out.println(ex);
        }
    }
    
    /*public ArrayList<TLexemTableInfo> matchLexem(String lexem) {
        ArrayList<TLexemTableInfo> found_lexems = new ArrayList<>();
        for(int i = 0; i < lexems.size(); i++) {
            if(lexems.get(i).text.startsWith(lexem)) found_lexems.add(lexems.get(i));
        }
        return found_lexems;
    }*/
    
    public TLexemTableInfo matchLexem(String lexem, boolean full_match) {
        for(int i = 0; i < lexems.size(); i++) {
            if(full_match)
                if(lexems.get(i).text.equals(lexem)) return lexems.get(i);
            else
                if(lexems.get(i).text.startsWith(lexem)) return lexems.get(i);
        }
        return null;
    }
}
