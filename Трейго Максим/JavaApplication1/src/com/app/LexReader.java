
package com.app;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class LexReader {
    
    public static final int ELEMENTS_SIZE = 8;
    
    public static List<Lexeme> parse(final String filePath) throws IOException {
        final FileReader in = new FileReader(filePath);
        final BufferedReader br = new BufferedReader(in);
        
        final StringBuilder sb = new StringBuilder();
        final List<String> lines = new ArrayList<>();
        String line;
        while ((line = br.readLine()) != null) {
            lines.add(line);
        }
        
        final List<Lexeme> result = new ArrayList<>();
        for (final String lex : lines) {
            result.add(parseImpl(lex));
        }
        return result;
    }
    
    private static Lexeme parseImpl(final String lex) {
        final String[] arr = lex.split(" ");
        final int group = Integer.parseInt(arr[0]);
        if (EGroup.getForValue(group) != EGroup.Eof && arr.length != ELEMENTS_SIZE) {
            throw new RuntimeException("Wrong input");
        }
        
        final Integer type = Integer.parseInt(arr[1]);
        final Integer pos = Integer.parseInt(arr[2]);
        final Integer line = Integer.parseInt(arr[3]);
        final Integer column = Integer.parseInt(arr[4]);
        final Integer len = Integer.parseInt(arr[5]);
        final Integer value;
        final String text;
        
        if (EGroup.getForValue(group) == EGroup.Eof) {
            value = null;
            text = null;
        } else {
            value = Integer.parseInt(arr[6]);
            text = arr[7];
        }
        
        final Lexeme result = new Lexeme(
                group, 
                type, 
                pos, 
                line, 
                column, 
                len, 
                value, 
                text
        );
        return result;
    }
   
    private LexReader() {
    }
}
