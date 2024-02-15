package com.oreilly.tiger.ch02;

import java.util.ArrayList;
import java.util.List;

public class Box<T> {

  protected List<T> contents;

  public Box() {
    contents = new ArrayList<T>();
  }

  public int getSize() {
    return contents.size();
  }

  public boolean isEmpty() {
    return (contents.size() == 0);
  }

  public void add(T o) {
    contents.add(o);
  }
 
  public T grab() {
    if (!isEmpty()) {
      return contents.remove(0);
    } else
      return null;
  }
}