/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package scannerprint;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


/**
 *
 * @author Student
 */
public class TScanner {
    ArrayList<Lexemme> lexems = new ArrayList<>();
    TLexemTable lexem_table = new TLexemTable();
    int cur_lexem = 0; 
    
    public TScanner() { }
    
    public void parceFile(String parce_location) {
        File to_parce = new File(parce_location);
        try(FileReader parce_stream = new FileReader(to_parce)) {
            BufferedReader reader = new BufferedReader(parce_stream);
            String line = "";
            Lexemme buffer;
            while(line != null) {
                line = reader.readLine();
                if (line == null || line.equals("")) break;
                buffer = new Lexemme();
                buffer.parceFromString(line);
                lexems.add(buffer); 
            }
        }
        catch(IOException ex) {
            System.out.println(ex);
        }
    }
    
    public void scanFile(String scan_location) {
        File to_scan = new File(scan_location);
        try(FileReader scan_stream = new FileReader(to_scan)) {
            BufferedReader scan_lexems = new BufferedReader(scan_stream);
            
            String line;
            String lexem;
            Lexemme buffer;
            int line = -1;
            int column = 0;
            int pos = 0;
            int current_char = 0;
            do {
                current_char = 0;
                column = 0;
                line++;
                line = scan_lexems.readLine();
                if(line != null) {
                    while(current_char != line.length()) {
                        buffer = new Lexemme();
                        if(Character.isDigit(line.charAt(current_char))) {
                            
                        }
                        else if (!Character.isLetterOrDigit(line.charAt(current_char))) {
                            
                        }
                        else if (line.charAt(current_char) == ' ') {
                            
                        }
                        // Check if readLine() function reads '\n' symbol from the end
                        /*else if (line.charAt(current_char) == '\0')
                        {
                            
                        }
                        else if (line.charAt(current_char) == '\n')
                        {
                            
                        }*/
                    }
                }
            } while (line != null);
        /////////////Implementation with symbol by symbol file reading
        /////////////Total shit
            char symb;
            String lexem = "";
            Lexemme buffer;
            do {
                int line = 0;
                int column = 0;
                int pos = 0;
                buffer = new Lexemme();
                symb = (char)scan_stream.read();
                if (Character.isDigit(symb))
                {
                    buffer.line = line;
                    buffer.pos = pos;
                    buffer.column = column;
                    while(Character.isDigit(symb)) {
                        if (buffer.group == Lexemme.TGroup.None) buffer.group = Lexemme.TGroup.Integer;
                        lexem += symb;
                        buffer.len++;
                        pos++;
                        column++;
                        symb = (char)scan_stream.read();
                        if (symb == '.') {
                            /* if already met dot and met another */ // Make flag to see if dot already met make error
                            if (buffer.group != Lexemme.TGroup.Number) buffer.group = Lexemme.TGroup.Number;
                            lexem += symb;
                            buffer.len++;
                            pos++;
                            column++;
                            symb = (char)scan_stream.read();
                        }
                        else if (symb == 'E' || symb == 'e') {
                            // Make flag if E already met throw error
                            // Remove dot flag
                            if (buffer.group != Lexemme.TGroup.Number) buffer.group = Lexemme.TGroup.Number;
                            lexem += symb;
                            buffer.len++;
                            pos++;
                            column++;
                            symb = (char)scan_stream.read();
                            if (symb == '-' || symb == '+') {
                                lexem += symb;
                                buffer.len++;
                                pos++;
                                column++;
                                symb = (char)scan_stream.read();
                            }
                        }
                    }
                    if (buffer.group == Lexemme.TGroup.Integer) {
                        buffer.value = Integer.parseInt(lexem);
                        buffer.text = lexem;
                    }
                    else {
                        //buffer.value = Double.parseDouble(lexem) how to get double value
                        buffer.text = lexem;
                    }
                }
                else if (symb == '\n') {
                    buffer.column = column;
                    buffer.line = line;
                    buffer.pos = pos;
                    buffer.group = Lexemme.TGroup.Line;
                    column = 0;
                    line++;
                    pos++;
                }
                else if (symb == '\0') {
                    buffer.column = column;
                    buffer.line = line;
                    buffer.pos = pos;
                    buffer.group = Lexemme.TGroup.Eof;
                    break;
                }
                else if (!Character.isLetterOrDigit(symb)) {
                    lexem += symb;
                    
                    TLexemTableInfo found;
                    bool 
                    do {
                        found = lexem_table.matchLexem(lexem, false);
                        if (found != null) {
                            symb = (char)scan_stream.read();
                            if(symb == '\0' || symb == '\n'){
                                
                            }
                            lexem += symb;
                            pos++;
                        }
                    } while (found != null);
                    lexem = lexem.substring(0, lexem.length() - 2);
                    pos--;
                    symb
                }
                
            } while(symb != -1);
        }
        
        catch(IOException ex) {
            System.out.println(ex);
        }
    }
    
    public String collectNumber(String text, int startIndex, boolean exponent = false) {
        Lexemme.TGroup group = Lexemme.TGroup.Integer;
        int current_char = startIndex;
        
        String number = "";
        
        boolean dot_met = false;
        boolean exp_met = false;
        
        while(Character.isDigit(text.charAt(current_char))) {
            number += text.charAt(current_char));
            current_char++;
            if(text.charAt(current_char)) == '.') {
                if(!dot_met) {
                    dot_met = true;
                    
                }
            } 
            else if (text.charAt(current_char)) == 'E' ||
                     text.charAt(current_char)) == 'e') {
                         
            }
        }
        
        do {
            
                if (Character.isDigit(symb))
                {
                    buffer.line = line;
                    buffer.pos = pos;
                    buffer.column = column;
                    while(Character.isDigit(symb)) {
                        if (buffer.group == Lexemme.TGroup.None) buffer.group = Lexemme.TGroup.Integer;
                        lexem += symb;
                        buffer.len++;
                        pos++;
                        column++;
                        symb = (char)scan_stream.read();
                        if (symb == '.') {
                            /* if already met dot and met another */ // Make flag to see if dot already met make error
                            if (buffer.group != Lexemme.TGroup.Number) buffer.group = Lexemme.TGroup.Number;
                            lexem += symb;
                            buffer.len++;
                            pos++;
                            column++;
                            symb = (char)scan_stream.read();
                        }
                        else if (symb == 'E' || symb == 'e') {
                            // Make flag if E already met throw error
                            // Remove dot flag
                            if (buffer.group != Lexemme.TGroup.Number) buffer.group = Lexemme.TGroup.Number;
                            lexem += symb;
                            buffer.len++;
                            pos++;
                            column++;
                            symb = (char)scan_stream.read();
                            if (symb == '-' || symb == '+') {
                                lexem += symb;
                                buffer.len++;
                                pos++;
                                column++;
                                symb = (char)scan_stream.read();
                            }
                        }
                    }
                    if (buffer.group == Lexemme.TGroup.Integer) {
                        buffer.value = Integer.parseInt(lexem);
                        buffer.text = lexem;
                    }
                    else {
                        //buffer.value = Double.parseDouble(lexem) how to get double value
                        buffer.text = lexem;
                    }
    }
    
    public void printLexems() {
        for(int i = 0; i < lexems.size(); i++) {
            lexems.get(i).print();
            System.out.println();
        }
    }
    
    public boolean Match(Lexemme.TGroup group, int type) {
        Lexemme lexem = lexems.get(cur_lexem);
        if(lexem.group == group && 
           lexem.type == type) {
            cur_lexem++;
            return true;
        }
        else return false;
    }
}
