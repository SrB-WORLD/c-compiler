
int f() {
    int x = 0;
    int y = 0;
    while (x < 3) {
        int z = 0;
        while (z < 3) {
            z = z + 1;
            if (z == 2) {
                continue;
            }
            y = y + 1;
        }
        x = x + 1;
    }
    return y;
}
