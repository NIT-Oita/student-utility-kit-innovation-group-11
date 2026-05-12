#include <stdio.h>
#include "calc.h"
int main() {
    int a, b;
    printf("1‚Â–Ú‚Ì”š‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢: ");
    if (scanf("%d", &a) != 1) return 1; 
        printf("2‚Â–Ú‚Ì”š‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢: ");
    if (scanf("%d", &b) != 1) return 1;
        printf("ŒvZŒ‹‰Ê:\n");
        printf("%d + %d = %d\n", a, b, add(a, b));
        printf("%d - %d = %d\n", a, b, sub(a, b));
    return 0;
}
