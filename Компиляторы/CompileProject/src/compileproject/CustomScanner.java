/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package compileproject;

import java.util.List;

/**
 *
 * @author Student
 */
public class CustomScanner {
    final List<Lexeme> lexemeLst;
    int startPos;
    
    CustomScanner(List<Lexeme> lexemeLst) {
        this.startPos = 0;
        this.lexemeLst = lexemeLst;
    }
    
    public boolean checkGroupOfCurrentLexeme(Lexeme.Group checkingGroup) {
        if (checkingGroup == getCurrentLexeme().group) {
            this.startPos++;
            return true;
        }
        return false;
    }
    
    public boolean checkTypeOfCurrentLexeme(Lexeme.Type checkingType) {
        if (checkingType == getCurrentLexeme().type) {
            this.startPos++;
            return true;
        }
        return false;
    }
    
    public boolean isNumberGroup() {
        return checkGroupOfCurrentLexeme(Lexeme.Group.Number) ||
            checkGroupOfCurrentLexeme(Lexeme.Group.Integer) ||
            checkGroupOfCurrentLexeme(Lexeme.Group.Ident);
    }
    
// TODO: попробовать сделать generic-код
/*    
    private boolean checkParam(Object checking) {
        if (checking instanceof Lexeme.Group && (Lexeme.Group)checking == getCurrentLexeme().group) {
            
        }
    }
*/
    
    public Lexeme getCurrentLexeme() {
        return this.lexemeLst.get(this.startPos);
    }
}
