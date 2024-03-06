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
            String line;
            Lexemme buffer;
            while(true) {
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
            
            String file = "";
            String line = scan_lexems.readLine();
            while(line != null) {
                file += line;
                if((line = scan_lexems.readLine()) != null) file += '\n';
            }
            file += '\0';
            String prev_line = "";
            Lexemme buffer;
            int line_num = -1;
            int column;
            int pos = 0;
            int current_char;
                    while(current_char != line.length()) {
                        buffer = new Lexemme();
                        if(Character.isDigit(line.charAt(current_char))) {
                            String lexem = collectNumber(line, current_char, true);
                            
                            buffer.column = column;
                            buffer.pos = pos;
                            buffer.line = line_num;
                            
                            if(lexem.charAt(0) == 'I'){
                                buffer.group = Lexemme.TGroup.Integer;
                                lexem = lexem.substring(1);
                                buffer.value = Integer.parseInt(lexem);   
                            }
                            else {
                                buffer.group = Lexemme.TGroup.Number;
                                lexem = lexem.substring(1);
                                //buffer.value = Double.parseDouble(lexem); 
                            }
                            buffer.len = lexem.length();
                            buffer.text = lexem;                            
                        }                        
                        else if (line.charAt(current_char) == ' ') {
                            buffer.column = column;
                            buffer.line = line_num;
                            buffer.pos = pos;
                            buffer.group = Lexemme.TGroup.Space;
                            int space_pointer = current_char;
                            while(line.charAt(space_pointer) == ' ') {
                                buffer.len++;
                                space_pointer++;
                            }
                            //Add value
                        }
                        // Check if readLine() function reads '\n' symbol from the end
                        else if (line.charAt(current_char) == '\0') {
                            buffer.group = Lexemme.TGroup.Eof;
                            buffer.line = line_num;
                            buffer.pos = pos;
                            buffer.column = column;
                            current_char++;
                            //Add value
                        }
                        else if (line.charAt(current_char) == '\n') {
                            buffer.group = Lexemme.TGroup.Line;
                            buffer.line = line_num;
                            buffer.pos = pos;
                            buffer.column = column;
                            current_char++;
                            line_num++;
                            column = 0;
                            //Add value
                        }
                        else if (line.charAt(current_char) == '"') {
                            String lexem = collectString(line, current_char);
                            
                            buffer.group = Lexemme.TGroup.String;
                            buffer.line = line_num;
                            buffer.pos = pos;
                            buffer.column = column;
                            buffer.text = lexem;
                            buffer.len = lexem.length();
                            //Add value
                        }
                        else if (!Character.isLetterOrDigit(line.charAt(current_char))) {
                            TLexemTableInfo identified = identifyOperator(line, current_char);
                            if (identified != null) {
                                buffer.group = identified.group;
                                buffer.line = line_num;
                                buffer.pos = pos;
                                buffer.column = column;
                                buffer.type = identified.type;
                                buffer.text = identified.text;
                                buffer.len = identified.text.length();
                                //Add value
                            }
                            else {
                                // do something if unknown
                            }
                        }
                        lexems.add(buffer);
                        current_char += buffer.len;
                        pos += buffer.len;
                        column += buffer.len;
                    }
        }
        catch(IOException ex) {
            System.out.println(ex);
        }
    }
    
    public String collectString(String text, int startIndex) {
        char[][] escapes = {{'t' , '\t'},
                            {'n' , '\n'},
                            {'\\', '\\'},
                            {'"' , '\"'},
                            {'\'', '\''}}; 
        //Make array of escapes and escape values and search escape values if found
        if (text.charAt(startIndex) != '"') return null;
        String lexeme_string = "\"";
        int current_char = startIndex + 1;
        while(text.charAt(current_char) != '"' || 
              current_char != text.length()) {
            if(text.charAt(current_char) == '\\') {
                int start = current_char;
                current_char++;
                for(int i = 0; i < escapes.size(); i++) {
                    if(text.charAt(current_char) == escapes[i][0]) {
                        lexeme_string += escapes[i][1];
                        current_char++;
                        break;
                    }
                }
                if(current_char - 1 == start) {
                    // throw an error here, escape sequence not found
                }
            }
            else {
                lexeme_string += text.charAt(current_char); 
                current_char++;
            }
        }
        if (current_char == text.length()) {
            //throw an error here
        }
        return lexeme_string;
    }
    
    public String collectIdentifier(String text, int startIndex) {
        String identifier = "";
        int current_char = startIndex;
        
        while(Character.isLetterOrDigit(text.charAt(current_char)) ||
              text.charAt(current_char) == '_') {
            identifier += text.charAt(current_char);
            current_char++;
        }
        return identifier;
    }
    
    public TLexemTableInfo identifyOperator(String text, int startIndex) {
        lexem_table.resetSearch();
        
        TLexemTableInfo found_lexem;
        boolean found;
        do {
            found_lexem = lexem_table.matchLexem(String.format("%c",text.charAt(startIndex)), false);
            if(found_lexem == null) return null;
            if(found_lexem.text.length() + startIndex >= text.length()) continue;
            found = true;
            for(int i = 1; i < found_lexem.text.length(); i++) {
                if (text.charAt(i + startIndex) != found_lexem.text.charAt(i)) {
                    found = false;
                    break;
                }
            }
            if (found) return found_lexem;
        } while (true/*found_lexem != null*/);
    }
    
    public String collectNumber(String text, int startIndex, boolean exponent) {
        Lexemme.TGroup group = Lexemme.TGroup.Integer;
        int current_char = startIndex;
        
        String number = "";
        
        boolean dot_met = false;
        
        while(Character.isDigit(text.charAt(current_char))) {
            number += text.charAt(current_char);
            current_char++;
            if(current_char >= text.length() || 
               text.charAt(current_char) == '\0' ||
               text.charAt(current_char) == '\n') break;
            if(text.charAt(current_char) == '.') {
                if(!dot_met) {
                    dot_met = true;
                    group = Lexemme.TGroup.Number;
                    number += text.charAt(current_char);
                    current_char++;
                }
                else {/*throw an error here*/}
            } 
            else if (text.charAt(current_char) == 'E' ||
                     text.charAt(current_char) == 'e') {
                if(!exponent) {/*throw error here*/}
                group = Lexemme.TGroup.Number;
                number += text.charAt(current_char);
                current_char++;
                if(text.charAt(current_char) == '-' ||
                   text.charAt(current_char) == '+') {
                    number += text.charAt(current_char);
                    current_char++;   
                }
                number += collectNumber(text, current_char, false);
            }
        }
        if(group == Lexemme.TGroup.Integer) return "I" + number;
        else return "N" + number;
        /*
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
                        if (symb == '.') {*/
                            /* if already met dot and met another */ // Make flag to see if dot already met make error
                            /*if (buffer.group != Lexemme.TGroup.Number) buffer.group = Lexemme.TGroup.Number;
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
                    }*/
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
