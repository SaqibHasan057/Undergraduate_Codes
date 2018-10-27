package lecture2;

/**
 * Created by rifat on 28/09/15.
 */
public class test {
    public static void main(String[] args) {
        byte b = 50;
        b *= 2;                  //  Error
        int c = b*2;           //  Ok
        byte d = (byte) (b*2);      // Ok

    }
}
