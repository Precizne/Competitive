import java.util.*;
import java.text.*;

class Parent {
    int p = 100;
    void print() {
        System.out.println(p);
    }
}

class Child1 extends Parent {
    int c1 = 1;
    void print() {
        System.out.println(c1);
    }
}

class Child2 extends Parent {
    int c2 = 2;
    void print() {
        System.out.println(c2);
    }
}

class Child3 extends Parent {
    int c3 = 3;
    void print() {
        System.out.println(c3);
    }
}

class Child4 extends Parent {
    int c4 = 4;
    void print() {
        System.out.println(c4);
    }
}

class Child5 extends Parent {
    int c5 = 5;
    void print() {
        System.out.println(c5);
    }
}

class ObjectGenerator {
    static Parent generate(int n) {
        switch(n) {
            case 1: return new Child1();
            case 2: return new Child2();
            case 3: return new Child3();
            case 4: return new Child4();
            case 5: return new Child5();
            default: return null;
        }
    }
}

public class DynamicMethodTypeInference {
    public static void main(String[] args) {
        Parent[] p = new Parent[5];
        for(int i = 0; i < 5; i++) {
            var x = ObjectGenerator.generate(i + 1);
            p[i] = x;
        }
        for(var x : p) {
            x.print();
        }
    }
}