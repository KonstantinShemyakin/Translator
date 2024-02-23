/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package scannerprint;

/**
 *
 * @author Student
 */
public class TLexemTableInfo {
    public Lexemme.TGroup group = Lexemme.TGroup.None;
    public int priority = 0;
    public int type = 0;
    public int mask;
    public String text = "";
    
    public TLexemTableInfo() {}
    
    public TLexemTableInfo(Lexemme.TGroup group, int type, int priority, int mask, String text) {
        this.group = group;
        this.priority = priority;
        this.type = type;
        this.text = text;
        this.mask = mask;
    }
    
    public TLexemTableInfo(int group, int type, int priority, int mask, String text) {
        this.group = Lexemme.getGroup(group);
        this.priority = priority;
        this.type = type;
        this.text = text;
        this.mask = mask;
    }
}
