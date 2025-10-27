int f() {
    int x = 0;
    int y = 0;
    while (x < 2) {
        int z = 0;
        while (z < 2) {
            y = y + 1;
            z = z + 1;
        }
        x = x + 1;
    }
    return y;
}
