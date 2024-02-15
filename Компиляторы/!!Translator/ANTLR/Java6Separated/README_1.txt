README.txt for the separated Java 6 Lexer and Parser

Please address all issues to the ANTLR Interest mailing list
  http://www.antlr.org/mailman/listinfo/antlr-interest 

Included files:
  Java6Lex.g         - the lexer grammar
  Java6Parse.g       - the parser grammar
  Java6SplitRun.java - Parse input files against the Java6Lex.g and
                       Java6Parse.g grammars
  README.txt         - this file
  build.xml          - the ant build file for testing the grammars
                       (Surely this be done in a simpler way?)
  vendor/examples    - directory of valid and invalid Java programs
  vendor/lib         - directory with the antlr-3.4-complete.jar file

INSTRUCTIONS: 
 1) Place a copy of the antlr-3.4-complete.jar in the directory
      Java6Separated/vendor/lib
 2) Change directory to Java6Separated/src and run: 
      ant

My motivation for separating the lexer and parser was to speed up the 
process of making iterative changes to the Java grammar for experimenting 
with new language features. Generation and compilation of the parser 
grammar (assuming no changes to the lexer grammar) with my ant script 
only dropped from 14 to 6 seconds on my laptop, but it helps a little.

The only changes to the parser that were needed were to replace token
literals with token names, e.g., replace ',' with COMMA, and then add
the tokenVocab=Java6Lex option. And of course change the grammar 
lines in the lexer and parser to: 
  parser grammar Java6Parse;
  lexer grammar Java6Lex;

The grammars' ability to parse correct programs was tested on the 
programs from the book: 
  Java 5.0 Tiger: A Developer's Notebook 
  By Brett McLaughlin, David Flanagan
The programs are available at 
  http://shop.oreilly.com/product/9780596007386.do 
In this distribution they are located at
  ...\Java6Separated\vendor\examples\java\java-adn

The parser's ability to find the errors in invalid Java programs was 
only tested on a single trivial example located at
  ...\Java6Separated\vendor\examples\java\ErrorExamples

This "separated" version was based on the combined lexer/parser that was 
originally written by Terry Parr and modified by Yang Jiang for use in 
the OpenJDK project. See:
http://openjdk.java.net/projects/compiler-grammar/ 
http://openjdk.java.net/projects/compiler-grammar/antlrworks/Java.g

George S. Cowan, July, 2012
