// Modified to produce error. Original code from
//   Java 5.0 Tiger: A Developer's Notebook
//   By Brett McLaughlin, David Flanagan
// The programs are available at
//   http://shop.oreilly.com/product/9780596007386.do
package com.oreilly.tiger.ch01;

import java.util..Arrays; // error here
import java.util.List;

public class ArraysTester {

  private int[] ar;

  public ArraysTester(int numValues) {
    ar = new int[numValues];

    for (int i=0; i < ar.length; i++) {
      ar[i] = (1000 - (300 + i));
    }
  }

  public int[] get() {
    return ar;
  }

  public static void main(String[] args) {
    ArraysTester tester = new ArraysTester(50);
    int[] myArray = tester.get();

    // Compare two arrays
    int[] myOtherArray = tester.get().clone();
    if (Arrays.equals(myArray, myOtherArray)) {
      System.out.println("The two arrays are equal!");
    } else {
      System.out.println("The two arrays are not equal!");
    }

    // Fill up some values
    Arrays.fill(myOtherArray, 2, 10, new Double(Math.PI).intValue());
    myArray[30] = 98;

    // Print array, as is
    System.out.println("Here's the unsorted array...");
    System.out.println(Arrays.toString(myArray));
    System.out.println();

    // Sort the array
    Arrays.sort(myArray);

    // print array, sorted
    System.out.println("Here's the sorted array...");
    System.out.println(Arrays.toString(myArray));
    System.out.println();

    // Get the index of a particular value
    int index = Arrays.binarySearch(myArray, 98);
    System.out.println("98 is located in the array at index " + index);

    String[][] ticTacToe = { {"X", "O", "O"},
                             {"O", "X", "X"},
                             {"X", "O", "X"}};
    System.out.println(Arrays.deepToString(ticTacToe));

    String[][] ticTacToe2 = { {"O", "O", "X"},
                              {"O", "X", "X"},
                              {"X", "O", "X"}};

    String[][] ticTacToe3 = { {"X", "O", "O"},
                              {"O", "X", "X"},
                              {"X", "O", "X"}};

    if (Arrays.deepEquals(ticTacToe, ticTacToe2)) {
      System.out.println("Boards 1 and 2 are equal.");
    } else {
      System.out.println("Boards 1 and 2 are not equal.");
    }

    if (Arrays.deepEquals(ticTacToe, ticTacToe3)) {
      System.out.println("Boards 1 and 3 are equal.");
    } else {
      System.out.println("Boards 1 and 3 are not equal.");
    }
  }
}