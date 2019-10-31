 #include <stdio.h>
 #define IN 1 /* inside a word */
 #define OUT 0 /* outside a word */
 /* count lines, words, and characters in input */
int main(){
   int digits[10];
   for (int i = 0; i < 10; ++i) digits[i] = 0;
   int c, nl, nw, nc, state;
   state = OUT;
   nl = nw = nc = 0;
   while ((c = getchar()) != EOF) {
      printf("%c",c);
      ++nc;
      if(c>='0' && c<='9'){
      ++digits[c-'0'];
      }
      else if (c == '\n')
         ++nl;
      if (c == ' ' || c == '\n' || c == '\t')
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
