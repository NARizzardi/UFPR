import java.util.Random;

public class Aleatorio {
        private static Random aleatorio;

        public static Random getAleatorio() {
            return aleatorio;
        }

        public void setAleatorio() {
            Aleatorio.aleatorio = new Random();
        }
}
