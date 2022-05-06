public class main {
    public static void main(String[] args) {
        String Input = "l(dsp{5}*:=<>p$"; //write here

        for (int i = 0; i < Input.length(); i++)
        {
            System.out.println(Input.charAt(i));
        }
        conditions analyser = new conditions(Input);
        analyser.condition1();
    }
}
