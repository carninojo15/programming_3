#include <stdlib.h>
#include "bmplib.h"
#include <stdio.h>
#include <unistd.h>

/*
 * This method enlarges a 24-bit, uncompressed .bmp file
 * that has been read in using readFile()
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the original number of rows
 * cols     - the original number of columns
 *
 * scale    - the multiplier applied to EACH OF the rows and columns, e.g.
 *           if scale=2, then 2* rows and 2*cols
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (scale*rows)
 * newcols  - the new number of cols (scale*cols)
 */
int enlarge(PIXEL* original, int rows, int cols, int scale, 
	    PIXEL** new, int* newrows, int* newcols) {
  
  int row, col, i, j;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *newrows = scale*rows;
  *newcols = scale*cols;
  *new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
  for (row=0; row < rows; row++){
    for(i=0; i<scale; i++){
      for (col=0; col < cols; col++){
        for(j=0; j<scale; j++){
          PIXEL* o = original + row*cols + col;
          PIXEL* n = (*new) + row*cols*scale*scale + cols*scale*i + col*scale + j;
          *n = *o;
        }
      }
    }
  }
  return 0;
}

/*
 * This method rotates a 24-bit, uncompressed .bmp file that has been
 * read in using readFile(). Rotate 90 degrees clockwise if 'rotation'
 * is 1; rotate 90 degrees counter-clockwise if 'rotation' is 0; all
 * other values of 'rotation' are invalid.
 * 
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 * rotation - clockwise or counter clockwise, 
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows
 * newcols  - the new number of cols
 */
/*int rotate(PIXEL* original, int rows, int cols, int rotation,
	   PIXEL** new, int* newrows, int* newcols){
  int row, col;

  // ccw
  if((rotation > 0 && rotation % 270 == 0)){
    *newrows = cols;
    *newcols = rows;
    *new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
    for (row=0; row < rows; row++){
      for (col=0; col < cols; col++) {
        PIXEL* o = original + row*cols + col;
        PIXEL* n = (*new) + (cols-col-1)*rows + row;   
        *n = *o;
      }
    }
  }
  // cw
  else if((rotation > 0 && rotation % 90 == 0)){
    *newrows = cols;
    *newcols = rows;
    *new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
    for (row=0; row < rows; row++){
      for (col=0; col < cols; col++) {
        PIXEL* o = original + row*cols + col;
        PIXEL* n = (*new) + col*rows + (rows-row-1);
        *n = *o;
      }
    }
  }
  return 0;
} */

/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile(). 
 * 
 * THIS IS PROVIDED TO YOU AS AN EXAMPLE FOR YOU TO UNDERSTAND HOW IT
 * WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
int flip(PIXEL *original, PIXEL **new, int rows, int cols) {
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + row*cols + (cols-1-col);
      *n = *o;
    }

  return 0;
}

/*
 * This method virtically flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile(). 
 * 
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
int flipv(PIXEL *original, PIXEL **new, int rows, int cols){
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + (rows-row)*cols - (col+1);
      *n = *o;
    }
  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + row*cols + (cols-1-col);
      *n = *o;
    }

  return 0;
}

int main(int argc, char *argv[])
{
  int r, c, nr, nc;
  PIXEL *b, *nb;
  int scale, cw, ccw, fliph, flipv, out;
  int argind;
  int scale_value;
  char* infile;
  char* outfile;

  // initiatize values
  infile = NULL;
  outfile = NULL;
  argind = scale_value = scale = cw = ccw = fliph = flipv = out = 0;

  while((c=getopt(argc,argv,"srfo")) != -1){
    switch(c){
      case '?': 
        exit(-1);
        break;
      case 's':
        if(scale) exit(-1);
        scale = 1;
        break;
      case 'r':
        if(cw) exit(-1);
        cw = 1;
        break;
      case 'c':
        if(ccw) exit(-1);
        ccw = 1;
        break;
      case 'f':
        if(fliph) exit(-1);
        fliph = 1;
        break;
      case 'v':
        if(flipv) exit(-1);
        flipv = 1;
        break;
      case 'o':
        if(out) exit(-1);
        out = 1;
        break;
      default:
        fprintf(stderr, "usage: bmptool [-s scale | -r degree | -f ] [-o output_file] [input_file] \n");
        exit(1);
        printf("You did nothing to the image.");
    }
  }

  argc -= optind;
  argv += optind;
  if(scale) scale_value = atoi(argv[argind++]);
  if(out) outfile = argv[argind++];
  if(argc - 1 == argind) infile = argv[argind];

  readFile(infile, &r, &c, &b);
  
  if(scale){
    enlarge(b, r, c, scale_value, &nb, &nr, &nc);
    r = nr;
    c = nc;
  }
  /*if(cw){
    rotate(b, r, c, 90, &nb, &nr, &nc);
    r = nr;
    c = nc;
  }
  if(ccw){
    rotate(b, r, c, 270, &nb, &nr, &nc);
    r = nr;
    c = nc;
  }*/
  if(fliph){
    flip(b, &nb, r, c);
  }
  if(flipv){
    //flipv(b, &nb, r, c);
    flip(b, &nb, r, c);
  }

  writeFile(outfile, r, c, nb);
    
  free(b);
  free(nb);
  return 0;
}
