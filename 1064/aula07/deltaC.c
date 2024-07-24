int delta(){
    int a = 1;
    int b = 2;
    int c = 2;
    return ((b*b)-(4*a*c));
}

int main(){
    if(delta() < 0) return 0;
    return 1;
}
