/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package compileproject;

import java.util.Map;

public class Lexeme {
    public static enum Group {None, Oper, Separator, Integer, Number, String, Ident, Reserv, Space, Line, Error, Priority, Syntax, Eof, Preproc, Meta, Grammar};
    public static String[] groupsStr = {"None", "Oper", "Separator", "Integer", "Number", "String", "Ident", "Reserv", "Space", "Line", "Error", "Priority", "Syntax", "Eof", "Preproc", "Meta", "Grammar"};
    
    public static enum Type { None, Add, Sub, Multi, Div, Mod, AddAssign, SubAssign, MultiAssign, DivAssign, ModAssign, AndAssign, OrAssign, XOrAssign, Assign, Or, And, OrOr, AndAnd, XOr, Tilda, Not, PlusPlus, MinusMinus, Equ, NotEqu, LT, LE, GT, GE, LShift, RShift, LShiftAssign, RShiftAssign, LeftCramp, RightCramp, LeftBracket, RightBracket, LeftScrape, RightScrape, Question, ColonColon, Slach, Point, Comma, Semicolon, Colon, UnaryAdd, UnarySub, PostInc, PostDec, Pointer, Ellipsis, ModMod, ModBegin, ModEnd, ModToken, ModLeft, ModRight, BNFSet, Define, Undef, Ifdef, Ifndef, Else, Endif, LeftMaker, RightMaker, Hint, BegHint, EndHint, At, RZShift, RZShiftAssign,  };
    public static String[] typesStr = { "None", "Add", "Sub", "Multi", "Div", "Mod", "AddAssign", "SubAssign", "MultiAssign", "DivAssign", "ModAssign", "AndAssign", "OrAssign", "XOrAssign", "Assign", "Or", "And", "OrOr", "AndAnd", "XOr", "Tilda", "Not", "PlusPlus", "MinusMinus", "Equ", "NotEqu", "LT", "LE", "GT", "GE", "LShift", "RShift", "LShiftAssign", "RShiftAssign", "LeftCramp", "RightCramp", "LeftBracket", "RightBracket", "LeftScrape", "RightScrape", "Question", "ColonColon", "Slach", "Point", "Comma", "Semicolon", "Colon", "UnaryAdd", "UnarySub", "PostInc", "PostDec", "Pointer", "Ellipsis", "ModMod", "ModBegin", "ModEnd", "ModToken", "ModLeft", "ModRight", "BNFSet", "Define", "Undef", "Ifdef", "Ifndef", "Else", "Endif", "LeftMaker", "RightMaker", "Hint", "BegHint", "EndHint", "At", "RZShift", "RZShiftAssign",  };

    int pos, len, line, column;
    Type type;
    Group group;
    Object value;
    
    Lexeme(Group group, Type type, int pos, int len, int line, int column, Object value) {
        this.group = group;
        this.type = type;
        this.pos = pos;
        this.len = len;
        this.line = line;
        this.column = column;
        this.value = value;
    }
    
    public String makeInfoStr() {
        String gr = groupsStr[this.group.ordinal()];
        String t = typesStr[this.type.ordinal()];
        return String.format("type: %s, group: %s, pos: %s, len: %s, line: %s, col: %s, value: %s", 
                gr, t, this.pos, this.len, this.line, this.column, this.value.toString());
    }
}
