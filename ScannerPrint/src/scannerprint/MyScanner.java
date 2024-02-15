/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package scannerprint;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;

/**
 *
 * @author Student
 */
public class MyScanner {
    File to_scan;
    File to_write;
    String scan_location;
    String result_location;
    
    public MyScanner(String scan_location, String result_location){
        this.scan_location = scan_location;
        this.result_location = result_location;
    }
    
    public void openFiles()
    {
        to_scan = new File(scan_location);
        to_write = new File(result_location);
    }
    
    public void Scan() {
        try(FileReader scan_stream = new FileReader(to_scan))
        {
            char symb;
            String line = "";
            while((symb = (char)scan_stream.read()) != -1)
            {
                while(symb != '\n') line += symb;
                
                
            }
        }
        catch(IOException ex)
        {
            System.out.println(ex);
        }
    }
    
    
}
