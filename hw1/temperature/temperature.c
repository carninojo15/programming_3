 #include <stdio.h>
 /* print Fahrenheit-Celsius table
 for fahr = 0, 20, ..., 300 */
int main(){
   int fahr, celsius;
   int lower, upper, step;
   lower = 0; /* lower limit of temperature scale */
   upper = 100; /* upper limit */
   step = 5; /* step size */
   celsius = lower;
   while (celsius <= upper) {
      fahr = (9 * celsius / 5) + 32;
      printf("%d\t%d\n", celsius, fahr);
      celsius = celsius + step;
   }
}
