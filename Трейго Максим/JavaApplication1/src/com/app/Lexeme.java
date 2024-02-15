
package com.app;

public class Lexeme {
        
    private final Integer group;
    private final Integer type;
    private final Integer pos;
    private final Integer line;
    private final Integer column;
    private final Integer len;
    private final Integer value;
    private final String text;

    public Lexeme(
            final Integer group, 
            final Integer type, 
            final Integer pos, 
            final Integer line, 
            final Integer column, 
            final Integer len, 
            final Integer value, 
            final String text
    ) {
        this.group = group;
        this.type = type;
        this.pos = pos;
        this.line = line;
        this.column = column;
        this.len = len;
        this.value = value;
        this.text = text;
    }
    
    public int getGroup() {
        return group;
    }

    public int getType() {
        return type;
    }

    public int getPos() {
        return pos;
    }

    public int getLine() {
        return line;
    }

    public int getColumn() {
        return column;
    }

    public int getLen() {
        return len;
    }

    public int getValue() {
        return value;
    }

    public String getText() {
        return text;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder();
        if (group != null) {
            sb.append("group=" + EGroup.getForValue(group).name());
        }
        if (type != null) {
            sb.append(", type=" + EType.getForValue(type).name());
        }
        if (pos != null) {
            sb.append(", pos=" + pos);
        }
        if (line != null) {
            sb.append(", line=" + line);
        }
        if (column != null) {
            sb.append(", column=" + column);
        }
        if (len != null) {
            sb.append(", len=" + len);
        }
        if (value != null) {
            sb.append(", value=" + value);
        }
        if (text != null) {
            sb.append(", text=" + text);
        }
        return sb.toString();
    }
}
