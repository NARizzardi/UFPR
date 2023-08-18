public class Time {
    private int h;
    private int m;

    
    public Time(int h, int m){
        this.h = h;
        this.m = m;
    }
    
    public int getH() {
        return h;
    }
    public void setH(int h) {
        this.h = h;
    }
    public int getM() {
        return m;
    }
    public void setM(int m) {
        this.m = m;
    }

    public boolean anterior(int h, int m){
        if(this.h > h || (this.h == h && this.m > m))
            return true;
        return false;
    }

    public boolean posterior(int h, int m){
        if(h > this.h || (this.h == h && m > this.m))
            return true;    
        return false;
    }

    public boolean equals(int h, int m){
        if(this.h == h && this.m == m)
            return true;
        return false;
    }

    public String toString(){
        String time;
        if(h < 10){
            time = String.format("0%d:", h);
        } else {
            time = String.format("%d:", h);
        }

        if(this.m < 10){
            time = time.concat(String.format("0%d", m));
        } else {
            time = time.concat(String.format("%d", m));
        }
        return time;
    }
}
