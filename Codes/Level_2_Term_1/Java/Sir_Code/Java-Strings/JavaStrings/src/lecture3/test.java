package lecture3;

/**
 * Created by rifat on 4/10/15.
 */
public class test {
    public static void main(String[] args) {
        String s = "Hello World";
        char [] c = new char[10];
        s.getChars(0, 5, c, 0);
        System.out.println(c);
        String t = "Hell";
        String r = "World";
        System.out.println(s.regionMatches(true, 0, t, 0, 5));
    }
}
