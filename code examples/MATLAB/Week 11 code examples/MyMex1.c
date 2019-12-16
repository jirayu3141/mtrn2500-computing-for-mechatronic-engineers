//---------------------------------------------------------------
/* Example code for interfacing C with Matlab.
 *
 * In this function, we just analyze the input and expected output variables.
 * 

 *  Jose Guivant - MTRN2500 - S2.2017
 */
//---------------------------------------------------------------
// Questions:  Ask, via Moodle or email j.guivant@unsw.edu.au
//---------------------------------------------------------------



//..........................................................
// We need to include this header, it contains declarations for the compiler.
// All the MEX files we implement do need this header file.
#include "mex.h"


// --------------- My part here ----
//  (this part is the example code, itself)

//I declare a function, which is defined in the same file, but below.
//after being referenced. 
//(you know these matters, from C programming)
static void DescribeVariable(const mxArray *ma);


//some particular constants, for my example.
#define MyDefaultRows 4
#define MyDefaultColumns 3


// The main entry to this DLL (MEX) function is here,  "mexFunction(...)"
// It must have this name!

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int i;

    //this mex file, like other Matlab function, is called 
    // [o1,o2,,..,o_m] = MyMex1(i1,i2,....,i_n);
    
    //Input arguments. 
    //"int nlhs": Number of outputs (LEFT hand side arguments).
    //"mxArray *plhs[]": Array of pointers, to the descriptors of the output
    // variables.
    
    //"int nrhs": Number of input arguments (RIGTH side arguments).
    //"mxArray *plrs[]": Array of pointers, to the descriptors of the input
    // variables.
    
    mexPrintf("\nHELLO,(printing from inside the MEX function)\n; ",nrhs);
       
    // In this basic example, we just print information about the input variables.
    {   
        mexPrintf("In this call We have received [%d] input arguments,\n; ",nrhs);
        mexPrintf("and the caller expects [%d] returned variables\n",nlhs);
    } 
    
    
    // In this example, I just return the requested number of output variables just creating small matrixes, 
    // of class double. Usually, these output variables (their sizes, classes, 
    // content) would depend on the purpose of this function.
    
    if (nlhs>0)
    {   mexPrintf("( By default I return variables class double, of size [%d]x[%d])\n;",MyDefaultRows, MyDefaultColumns);
    }
        
    
    for (i=0;i<nlhs;i++)
    {   plhs[i] = mxCreateNumericMatrix(MyDefaultRows, MyDefaultColumns, mxDOUBLE_CLASS, mxREAL); }
    
    
    
    // IMPORTANT: Our function is responsible for actually creating the
    // output variables.
    // The number of output variables is defined by the caller.
    // It is specified by the variable "nhls".
    // However, we MUST set the contents of the array "plhs[]".
    // The system (Matlab) calls our functions providing an array (of pointers)
    // whose length is exactly specified by "nhls".
    // We must set, EXACTLY, that number of elements in "plhs[]". No MORE, no LESS.
    // LESS: some pointers will contain rubbish, and the system would usually 
    // crash, when trying to access those memory addresses.
    // MORE: e.g. plhs[nlhs], we will be writing memory we do not own; 
    // consequently, we would corrupt Matlab memory; and the system would turn unstable.
    
    //However, we has the freedom to create the variables themselves.
    //We decide what we return. 
    //The caller will need to deal with our resturned variables.

    
    
    
    
    // Now, I just want to print some brief info about the input variables.
    
    // In this example, we describe each of the "nrhs" input variables.
    mexPrintf("------------------------------------------------\n",i);
    for (i=0;i<nrhs;i++)
    {   mexPrintf("Describing input variable #%d\n",i);
        
        // Each element "prhs[i]" is a pointer to a descriptor of one variable.
        // descriptors are instances of the structure class "mxArray"
        
        
        DescribeVariable(prhs[i]);   
        // I implemented a C-function, to print some basic info. See it, below.
        
    }
     
    mexPrintf("\nMyMex1 says BYE\n",nrhs);
    return;
}


// .......................................................................

// This function does just print a brief description about the Matlab's variable 
// which is referenced by the pointer "ma"  (const mxArray *ma).
// The function obtains information about the variable (numeric class, dimensionality, size)
// and print it, for us.
// The intention is to show how to inspect certain relevant properties of Matlab variables, from C/C++.


static void DescribeVariable(const mxArray *ma)
{
  const char    *class_name;
  const mwSize  *dims;
  mwSize        i;                         // FYI: data type "mwSize" is an integer.
  mwSize        number_of_dimensions; 
  
  number_of_dimensions = mxGetNumberOfDimensions(ma);               // we ask for the dimensionality of this variable.
  
  //here we ask for "sizes"
  dims = mxGetDimensions(ma);                                       // dims[i-1]: size fo dimension "i"  (i=1:number_of_dimensions)

  class_name = mxGetClassName(ma);                                  //data type (expressed as text)  
  
  
  mexPrintf("This variable is class [%s]\n",class_name);
  mexPrintf("It has [%d] dimensions\n",number_of_dimensions);
  /*
  for (i=0; i<number_of_dimensions; i++)
  {     mexPrintf("Dimension[%d] has length = [%d]\n",i+1,dims[i]); }
  */
  
  mexPrintf("( its size is: [%d]",dims[0]);
  for (i=1; i<number_of_dimensions; i++)
  {     mexPrintf(" x [%d]",dims[i]); }
  mexPrintf(" )\n");
  
  
  mexPrintf("------------------------------------------------\n");
}

// END of example.


//---------------------------------------------------------------
// Compile it, this way:  mex MyMex1.c; 
// You may run it, e.g.

// [a,b,c]= MyMex1( zeros(2,3), uint8([2,3,4]),rand(3,4,5,'single')) ;


//---------------------------------------------------------------
// Questions:  Ask, via Moodle or email j.guivant@unsw.edu.au
//---------------------------------------------------------------

// Next example:  mex MyMex2.c; 
//---------------------------------------------------------------