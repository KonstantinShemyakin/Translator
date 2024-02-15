
package com.app;

public enum EGroup {
    None, 
    Oper,
    Separator, 
    Integer,
    Number,
    String,
    Ident, 
    Reserv, 
    Space, 
    Line, 
    Error, 
    Priority, 
    Syntax,
    Eof,
    Preproc, 
    Meta, 
    Grammar; 
    
    public static EGroup getForValue(final int group) {
        return EGroup.values()[group];
    }
}
