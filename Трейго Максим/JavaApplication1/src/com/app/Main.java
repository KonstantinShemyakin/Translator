
package com.app;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.List;

public class Main {
    
    public static void main(String[] args) throws IOException {
        final String filePath = "C:/Users/Student/Documents/01_Parse/test.lex";
        final List<Lexeme> lexemes = LexReader.parse(filePath);
        for (final Lexeme lexeme : lexemes) {
            System.err.println(lexeme);
        }
    }
    
}
