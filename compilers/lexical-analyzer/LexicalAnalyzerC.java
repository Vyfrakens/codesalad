// package com.lexicalanalyzer;

import java.io.*;

// Identify keywords and identifiers
public class LexicalAnalyzerC {
	private static final String[] PREPROCESSORS = {"define", "undef", "include", "if", "ifdef", "ifndef", "else", "elif", "endif", "line", "error", "pragma"};
	private static final String[] KEYWORDS = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "	restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
	private static final Character[] PUNCTUATIONS = {'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~', '}'};

	public static void main(String[] args) {
		try {
			StreamTokenizer st = new StreamTokenizer(new FileReader(new File("input/input.c")));
			st.slashSlashComments(true);
			st.slashStarComments(true);
			st.eolIsSignificant(true);
			st.wordChars('_', '_');
			while (true) {
				int c = st.nextToken();
				if (c == StreamTokenizer.TT_EOF)
					break;
				switch (c) {
					case '#':
						System.out.print((char) c);
						int x;
						st.nextToken();

						if (isPreprocessor(st.sval)) {
							System.out.print(st.sval + " (Preprocessor)");
							while ((x = st.nextToken()) != StreamTokenizer.TT_EOL) ;
							System.out.println();
						}
						break;
					case StreamTokenizer.TT_EOL:
						System.out.println("\nLine " + st.lineno() + ": ");
						continue;
					case StreamTokenizer.TT_WORD:
						if (isKeyword(st.sval))
							System.out.println(st.sval + " (Keyword)");
						else
							System.out.println(st.sval + " (Identifier)");
						break;
					case StreamTokenizer.TT_NUMBER:
						System.out.println(st.nval + " (Constant)");
						break;
					default:
						if (c == '\'' || c == '"')
							System.out.println((char) c + st.sval + (char) c + (c == '\'' ? " (Character)" : " (String)"));
						else if (isPunctuation((char) c))
							System.out.println((char) c + " (Punctuation)");
						break;
				}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private static boolean isPunctuation(Character c) {
		return stringIn(c, PUNCTUATIONS);
	}

	private static boolean isKeyword(String s) {
		return stringIn(s, KEYWORDS);
	}

	private static boolean isPreprocessor(String s) {
		return stringIn(s, PREPROCESSORS);
	}

	private static <T> boolean stringIn(T needle, T[] haystack) {
		for (T s : haystack)
			if (s.equals(needle))
				return true;
		return false;
	}
}
