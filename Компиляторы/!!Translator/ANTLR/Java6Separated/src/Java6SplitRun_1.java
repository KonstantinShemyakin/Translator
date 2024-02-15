/*
 * Java6SplitRun.java - Parse input against the Java6Parse.g and Java6Lex.g grammar
 *
 * [The "BSD licence"]
 * Copyright (c) 2012 George S. Cowan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

import java.io.IOException;
import org.antlr.runtime.ANTLRFileStream;
import org.antlr.runtime.ANTLRStringStream;
import org.antlr.runtime.CommonTokenStream;


  public class
Java6SplitRun {

  private static CommonTokenStream
fileToTokenStream(String fileToParse)
            throws IOException {
  if (fileToParse == null) {
    exitWithCommandLineFormatError("ERROR: file to parse was not found");
  }
  final ANTLRStringStream input = new ANTLRFileStream(fileToParse);
  final Java6Lex lexer = new Java6Lex(input);
  return new CommonTokenStream(lexer);
}

  private static void
exitWithCommandLineFormatError(String msg) {
  System.out.println(msg);
  System.out.println("ERROR: Format of JavaSplitRun command line is");
  System.out.println("  java -cp .;your/path/antlr.current.jar JavaSplitRun file...");
  System.exit(1);
}

  public static void
main(String[] args) throws Exception {
  int firstFileArg = 0; // so far

  if (args.length == 0) {
    exitWithCommandLineFormatError("ERROR: file to parse is missing");
  } else { // some args are present
	  for (int i = firstFileArg; i < args.length; i++) {
      final CommonTokenStream tokenStream = fileToTokenStream(args[i]);
      final Java6Parse parser = new Java6Parse(tokenStream);
      parser.compilationUnit();
	  }
  }
}

} // end class JavaSplitRun
