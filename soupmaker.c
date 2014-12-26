/* In this program you enter a hexadecimal representation of a 16 by 16 soup
 * in one file and it gives you the soup pattern file in another. */

#include <stdio.h>
#include <ctype.h>

int HexDigit(char ch) {
    if (isdigit(ch)) return ch - '0';
    char lowerch = tolower(ch);
    if ('a' <= lowerch && lowerch <= 'f') {
        return lowerch - 'a' + 10;
    }
    return -1;
}

int PrintCellsFromDigit(char ch, FILE* output) {
    int hexValue = HexDigit(ch);
    if (hexValue == -1) {
        fprintf(output, "The string you entered was invalid.\n");
        return -1;
    }
    int bDigitNum;
    for (bDigitNum = 3; bDigitNum >= 0; bDigitNum--) {
        fprintf(output, "%c", hexValue / (1<<bDigitNum) ? 'o' : '.');
        hexValue = hexValue % (1<<bDigitNum);
    }
    return 0;
}

void PrintPattern(FILE* input, FILE* output) {
    char ch = getc(input);
    int charNum = 1;
    while (ch != EOF) {
        if (PrintCellsFromDigit(ch, output) == -1) break;
        if (charNum % 4 == 0) fprintf(output, "\n");
        ch = getc(input);
        charNum++;
    }
}

int main(void) {
    FILE* input = fopen("num.txt", "r");
    FILE* output = fopen("soup.txt", "w");
    PrintPattern(input, output);
    printf("Soup is done! Open soup.txt to see it.\n");
    fflush(output);
    fclose(input);
    fclose(output);
    getchar();
    return 0;
}
