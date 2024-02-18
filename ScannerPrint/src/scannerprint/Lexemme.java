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
public class Lexemme {
    public TGroup group = 0;
    public int type = 0;
    public int pos = 0, line = 0, len = 0, column = 0;
    public int value = 0;
    public String text;
    
    public enum TGroup {None, Oper, Separator, Integer, Number, String, Ident, Reserv, Space, Line, Error, Priority, Syntax, Eof, Preproc, Meta, Grammar;
                
                public TGroup getGroup(int ordinal){
                    return TGroup.values()[ordinal];
                }
    };
    public const String t_group[] = { "None", "Oper", "Separator", "Integer", "Number", "String", "Ident", "Reserv", "Space", "Line", "Error", "Priority", "Syntax", "Eof", "Preproc", "Meta", "Grammar"};

    public enum TType {None, Add, Sub, Multi, Div, Mod, AddAssign, SubAssign, MultiAssign, DivAssign, ModAssign, AndAssign, OrAssign, XOrAssign, Assign, Or, And, OrOr, AndAnd, XOr, Tilda, Not, PlusPlus, MinusMinus, Equ, NotEqu, LT, LE, GT, GE, LShift, RShift, LShiftAssign, RShiftAssign, LeftCramp, RightCramp, LeftBracket, RightBracket, LeftScrape, RightScrape, Question, ColonColon, Slach, Point, Comma, Semicolon, Colon, UnaryAdd, UnarySub, PostInc, PostDec, Pointer, Ellipsis, ModMod, ModBegin, ModEnd, ModToken, ModLeft, ModRight, BNFSet, Define, Undef, Ifdef, Ifndef, Else, Endif, LeftMaker, RightMaker, Hint, BegHint, EndHint, At, RZShift, RZShiftAssign};
    public const String lexeme_type[] = { "None", "Add", "Sub", "Multi", "Div", "Mod", "AddAssign", "SubAssign", "MultiAssign", "DivAssign", "ModAssign", "AndAssign", "OrAssign", "XOrAssign", "Assign", "Or", "And", "OrOr", "AndAnd", "XOr", "Tilda", "Not", "PlusPlus", "MinusMinus", "Equ", "NotEqu", "LT", "LE", "GT", "GE", "LShift", "RShift", "LShiftAssign", "RShiftAssign", "LeftCramp", "RightCramp", "LeftBracket", "RightBracket", "LeftScrape", "RightScrape", "Question", "ColonColon", "Slach", "Point", "Comma", "Semicolon", "Colon", "UnaryAdd", "UnarySub", "PostInc", "PostDec", "Pointer", "Ellipsis", "ModMod", "ModBegin", "ModEnd", "ModToken", "ModLeft", "ModRight", "BNFSet", "Define", "Undef", "Ifdef", "Ifndef", "Else", "Endif", "LeftMaker", "RightMaker", "Hint", "BegHint", "EndHint", "At", "RZShift", "RZShiftAssign"};

    public enum TPriority {None, Assign, Question, OrOr, AndAnd, Or, XOr, And, Equ, Compare, Shift, Term, Factor, Unary, IncDec};
    public const String lexeme_priority[] = { "None", "Assign", "Question", "OrOr", "AndAnd", "Or", "XOr", "And", "Equ", "Compare", "Shift", "Term", "Factor", "Unary", "IncDec"};

    
    public Lexemme() { }
    
    public Lexemme(int group, 
                   int type, 
                   int pos, 
                   int line, 
                   int column,
                   int len,
                   int value,
                   String text) {
        this.group = TGroup::getGroup(group);
        this.type = type;
        this.pos = pos;
        this.line = line;
        this.column = column;
        this.len = len;
        this.value = value;
        this.text = text;
    }
    
    public Lexemme(TGroup group, 
                   int type, 
                   int pos, 
                   int line, 
                   int column,
                   int len,
                   int value,
                   String text) {
        this.group = group;
        this.type = type;
        this.pos = pos;
        this.line = line;
        this.column = column;
        this.len = len;
        this.value = value;
        this.text = text;
    }
    
    public String Text() {return text;}
    
    public void parceFromString(String line) {
        String parced[] = line.split(" ");
        group = TGroup::getGroup(Integer.parseInt(parced[0]));
        type = Integer.parseInt(parced[1]);
        pos = Integer.parseInt(parced[2]);
        this.line = Integer.parseInt(parced[3]);
        column = Integer.parseInt(parced[4]);
        len = Integer.parseInt(parced[5]);
        value = Integer.parseInt(parced[6]);
        text = parced[7];
    }
    
    public void write() {
        System.out.print(String.format("%d %d %d %d %d %d %d", group.ordinal(), type, pos, line, column, len));
        if ((group != TGroup.Space) && 
            (group != TGroup.grNone) && 
            (group != TGroup.Line) && 
            (group != TGroup.Eof))
        {
            System.out.print(String.format("%d %s", value, text));
        }
    }
    
    public void print() {
        System.out.print(String.format("group: %s, ", t_group[group.ordinal()]));
        System.out.print(String.format("type: %s, ", lexeme_type[type]));
        System.out.print(String.format("pos: %d, ", pos));
        System.out.print(String.format("line: %d, ", line));
        System.out.print(String.format("column: %d, ", column));
        System.out.print(String.format("len: %d, ", len));
        System.out.print(String.format("value: %d, ", value));
        System.out.print(String.format("text: %s", text));
    }
}
