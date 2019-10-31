 #include <stdio.h>
 #define IN 1 /* inside a word */
 #define OUT 0 /* outside a word */
 /* count lines, words, and characters in input */
int main(){
   FILE* fp;
   char digits[10];
   char filename[100]; 
   printf("Enter file name: "); 
   scanf("%s", filename);
   fp = fopen(filename, "r");
   int c, nl, nw, nc, state;
   int zero, one, two, three, four, five, six, seven, eight, nine;
   state = OUT;
   nl = nw = nc = 0;
   while ((c = getc(fp)) != EOF) {
      printf("%c",c);
      ++nc;
      if(c>='0' && c<='9') digits[c+'0']++;
      /*if (c == ('0'-'0')) ++digits[0];
      if (c == '1') ++one;
      if (c == '2') ++two;
      if (c == '3') ++three;
      if (c == '4') ++four;
      if (c == '5') ++five;
      if (c == '6') ++six;
      if (c == '7') ++seven;
      if (c == '8') ++eight;
      if (c == '9') ++nine;*/ 
      if (c == '\n')
         ++nl;
      if (c == ' ' || c == '\n')
         state = OUT;
      else if (state == OUT) {
         state = IN;
         ++nw;
      }
   }
   printf("%d %d %d\n", nl, nw, nc);
   for(int i=0;i<10;i++) printf("%d, %d\n", i, digits[i]);
   return 0;
}
