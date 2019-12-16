/* PrintMemoLinearlyUInt8.c ; version 2017.1. 
 * 
 * example code for interfacing C- functions with Matlab.
 *
 *
 * Basic function, which just print the content of a uint8 variable.
 * We can see how data is linearly organized in memory 
 *
 *
 *  Jose Guivant - MTRN2500 - S2.2017
 */


// We need to include this header, for including useful declarations to the compiler.
#include "mex.h"

// --------------- my part here ----


// the main entry, to this MEX functions, is here,  "mexFunction(...)"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    //some local C variables.
    const mwSize  *dimsA;   mwSize        numDimsA; 
    const mxArray *maA;
    
    
    // If my function expects certain type of inputs, I should verify 
    // that the caller is respecting those assumptions.
    // Here we expect two input arguments, and one output variable.
    if (( nrhs != 1 )||(nlhs!=0)){   mexPrintf("????\n");   return;   } 
    
    
    
    // get the pointer of the current input variable.
    maA = prhs[0];  
    
    // get info (size,dimensionality) about the input variables
    numDimsA = mxGetNumberOfDimensions(maA);    // how many dimensions
    dimsA = mxGetDimensions(maA);               // length of each dimension
    
    
    
    if (numDimsA<1){   return ;  }                      
    if (mxGetClassID(maA)!=mxUINT8_CLASS){  return ; }
    
    
    mexPrintf("Printing uint8 contents, linearly\n");
        
    {   int i,n;
        unsigned char *pA;
        pA = (unsigned char *)mxGetPr(maA);         //get pointer to actual data.
        
        
        // total size.
        n = dimsA[0];         for (i=1;i<numDimsA;i++){   n = n*dimsA[i]; }    
        
        
        mexPrintf("The variable  has [%d] elements.\n",n);
        if (n>100){  n=100 ; }          //limit printing; just in case.
        
        
        //loop
        for (i=0;i<n;i++)
        {   mexPrintf("M[%03d]= %03d;\n",i,pA[i]);
        }    
    }           
    return;
}

//test this way:
//x=uint8(1:10); x=[x;x+100;x+200] ; PrintMemoLinearlyUInt8(x);


//---------------------------------------------------------
