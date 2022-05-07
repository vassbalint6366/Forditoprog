import static java.lang.Character.*; //isLetter & isDigit


public class conditions {
    String input; //for the input + charAt
    int index; // which char (in number)
    conditions(String inputString){
        input = inputString;
        index = -1; // -1, because our condition1() will increase and -1+1 = 0 (first char of our input string)
    }

    void indexIncrease()  //inputot olvas
    {
        index++; // indexIncrease in conditions: 1,2,4,6,8,9,10,12,14,17
    }

    void indexDecrease() //backup
    {
        index--; // indexDecrease in conditions: 3,5,20
    }

    void condition1()
    {
        System.out.println("kezdőállapot");
        if(index == input.length()-1)
            return;
        indexIncrease();
        if(isLetter(input.charAt(index))) { condition2(); }
        else if(isDigit(input.charAt(index))) { condition4(); }
        else if(input.charAt(index) == '{') { condition6(); }
        else if(input.charAt(index) == '(') { condition8(); }
        else if(input.charAt(index) == ':') { condition12(); }
        else if(input.charAt(index) == '<') { condition14(); }
        else if(input.charAt(index) == '>') { condition17(); }
        else if(input.charAt(index) == ' ') { condition1(); }
        else if(input.charAt(index) == '$') { condition21(); }
        else { condition19(); } // "}", "*", ")", "="

    }
    void condition2()
    {
        System.out.println("azonosítóban");
        indexIncrease();
        if(isLetter(input.charAt(index))) { condition2(); }
        else if(isDigit(input.charAt(index))) { condition2(); }
        else { condition3(); }
    }

    void condition3()
    {
        System.out.println("azonosító vége");
        indexDecrease();
        condition1();
    }

    void condition4()
    {
        System.out.println("számban");
        indexIncrease();
        if(isLetter(input.charAt(index))) { condition4(); }
        else { condition5(); }
    }

    void condition5()
    {
        System.out.println("szám vége");
        indexDecrease();
        condition1();
    }

    void condition6()
    {
        System.out.println("{} komm.-ban");
        indexIncrease();
        if(input.charAt(index) == '}') { condition7(); }
        else if(input.charAt(index) == '$') { condition19(); }
        else { condition6(); }
    }

    void condition7()
    {
        System.out.println("{} komm. vég");
        condition1();
    }

    void condition8()
    {
        System.out.println("(-talált");
        indexIncrease();
        if(input.charAt(index) == '*') { condition9(); }
        else if(input.charAt(index) == '$') { condition19(); }
        else { condition20(); }
    }

    void condition9()
    {
        System.out.println("(**) komm.ban");
        indexIncrease();
        if(input.charAt(index) == '*') { condition10(); }
        else if(input.charAt(index) == '$') { condition19(); }
        else { condition9(); }
    }

    void condition10()
    {
        System.out.println("* (**)-ban");
        indexIncrease();
        if(input.charAt(index) == '*') { condition10(); }
        else if(input.charAt(index) == ')') { condition11(); }
        else if(input.charAt(index) == '$') { condition19(); }
        else { condition9(); }
    }

    void condition11()
    {
        System.out.println("(**) komm.vég");
        condition1();
    }

    void condition12()
    {
        System.out.println(":-t talált");
        indexIncrease();if(input.charAt(index) == '=') { condition13(); }
        else if(input.charAt(index) == '$') { condition19(); }
        else { condition20(); }
    }

    void condition13()
    {
        System.out.println(":= token");
        condition1();
    }

    void condition14()
    {
        System.out.println("<-t talált");
        indexIncrease();if(input.charAt(index) == '=') { condition15(); }
        else if(input.charAt(index) == '>') { condition16(); }
        else if(input.charAt(index) == '$') { condition20(); }
        else { condition20(); }
    }

    void condition15()
    {
        System.out.println("<= token");
        condition1();
    }

    void condition16()
    {
        System.out.println("<> token");
        condition1();
    }

    void condition17()
    {
        System.out.println(">-t talált");
        indexIncrease();if(input.charAt(index) == '=') { condition18(); }
        else if(input.charAt(index) == '$') { condition19(); }
        else { condition20(); }
    }

    void condition18()
    {
        System.out.println(">= token");
        condition1();
    }
    void condition19()
    {
        System.out.println("hibakezelő: "+input.charAt(index));
        condition1();
    }

    void condition20()
    {
        System.out.println("továbbfejl.");
        indexDecrease();
        condition1();
    }

    void condition21()
    {
        System.out.println("Stop");
    }

}
