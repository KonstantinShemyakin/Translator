/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package scannerprint;

import java.io.File;

/**
 *
 * @author Student
 */
public class ScannerPrint {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        //File dir_scanner = new File("C:\\Users\\Student\\Documents\\Lego\\Scanner");
        
        //TScanner my_scanner = new TScanner();
        
        //my_scanner.parceFile("C:\\Projects\\Translator\\01_Parse\\test.lex");
        //my_scanner.printLexems();
        
        TScanner scan_file = new TScanner();
        
        scan_file.scanFile("C:\\Projects\\Translator\\01_Parse\\test.cpp");
        scan_file.printLexems();
        
        // TODO code application logic here
    }
}
