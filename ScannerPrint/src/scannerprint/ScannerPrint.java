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
        
        TScanner my_scanner = new TScanner();
        
        my_scanner.parceFile("C:\\Users\\Student\\Documents\\01_Parce\\test.lex");
        my_scanner.printLexems();
        
        TScanner scan_file = new TScanner();
        
        
        // TODO code application logic here
    }
}
