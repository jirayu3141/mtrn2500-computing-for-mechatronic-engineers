//-------------------------- MyMex1_s.c -----------------------

/* Example code for interfacing C with Matlab.
 *
 * In this function, we just analyze the input and expected output variables.
 * This version of MyMex1.c  (MyMex1_s.c) also describes matlab variables which are STRUCTURES
 * 

 *  Jose Guivant - MTRN2500 - S2.2016
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


//something, particular for this example.
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
    //"int nlhs": Number of outputs (LEFT arguments).
    //"mxArray *plhs[]": Array of pointers, to the descriptors of the output
    // variables.
    
    //"int nrhs": Number of input arguments (RIGTH arguments).
    //"mxArray *plrs[]": Array of pointers, to the descriptors of the input
    // variables.
    
    
       
    // In this basic example, we just print information about the input variables.
    {   mexPrintf("In this call We have received [%d] arguments,\n; ",nrhs);
        mexPrintf("and the caller expects [%d] returned variables\n",nlhs);
    } 
    
    
    // In this example, I just return the requested number of output variables just creating small matrixes, 
    // of class double. Usually, these output variables (their sizes, classes, 
    // content) would depend on the purpose of this function.
    
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
    for (i=0;i<nrhs;i++)
    {   mexPrintf("Describing input variable #%d\n",i);
        
        // Each element "prhs[i]" is a pointer to a descriptor of one variable.
        // descriptors are instances of the structure class "mxArray"
        
        
        DescribeVariable(prhs[i]);   
        // I implemented a C-function, to print some basic info. See it, below.
        
    }
     
    return;
}


// .......................................................................

// This function does just print a brief description about the Matlab's variable 
// which is referenced by the pointer "ma"  (const mxArray *ma).
// The function obtain information about the variable (numeric class, dimensionality, size)
// and print it, for us.

static void DescribeVariable(const mxArray *ma)
{
  const char    *class_name;
  const mwSize  *dims;
  mwSize        i;
  mwSize        number_of_dimensions; 
  mxClassID       type;
  
  
  number_of_dimensions = mxGetNumberOfDimensions(ma);
  dims = mxGetDimensions(ma);

  type =  mxGetClassID(ma);         // See NOTE_0.
  

  class_name = mxGetClassName(ma);
  mexPrintf("This variable is class [%s],#=[%d]\n",class_name,type);
  mexPrintf("It has [%d] dimensions\n",number_of_dimensions);
  for (i=0; i<number_of_dimensions; i++)
  {     mexPrintf("Dim%d has length = [%d]\n",i,dims[i]); }
  mexPrintf("------------------------------------------------\n");

  //If this Matlab variable is a STRUCT, I may navigate deeper, to inspect its fields
  //(which may also be structures...)
  if (type==mxSTRUCT_CLASS)
  {   int i,nf;
      char *s;
      const mxArray *mb;
      nf = mxGetNumberOfFields(ma);
      mexPrintf("**** This struct has %d fields.\nI describe them:\n",nf);

      for (i=0;i<nf;i++)  
      {     s=mxGetFieldNameByNumber(ma,i);
            mexPrintf("Describing field #%d, name=< %s >\n",i,s);
            mb=mxGetFieldByNumber(ma, 0, i);            //Read NOTE 1
            if (mb!=NULL){  DescribeVariable(mb); }     //call, recursivelly, the same function.
            
      }
 
      mexPrintf("**** End ***\n");
      mexPrintf("------------------------------------------------\n");
      return;
  }    
      
}
//(*) the array may have many items. However, the same property in different items may be of different
// type, size, etc. So, I just anlylize one, in this example.
//====================================================


// NOTE_0:

/*   CLASSES of VARIABLES . (This IDs are defined in MEX.H)
 *
 *
 *
typedef enum {
        mxUNKNOWN_CLASS,        // Mystery. 
        mxCELL_CLASS,           // CELLS will be discussed in another lecture.
        mxSTRUCT_CLASS,         //<----------- we discuss this one, today.
        
        mxLOGICAL_CLASS,
        mxCHAR_CLASS,           //<----------- string.
        
        mxVOID_CLASS,           // Reserved.
 
            //we know these types!
        mxDOUBLE_CLASS,
        mxSINGLE_CLASS,
        mxINT8_CLASS,
        mxUINT8_CLASS,
        mxINT16_CLASS,
        mxUINT16_CLASS,
        mxINT32_CLASS,
        mxUINT32_CLASS,
        mxINT64_CLASS,
        mxUINT64_CLASS,
       
                //handle to function!
        mxFUNCTION_CLASS
} mxClassID
*/
// substructure_field_num = mxGetFieldNumber(pa, "substructure");


//NOTE_1:   
/*
    It may be the case of an array, i.e. an array whose elements are instances of the same structure.
    However, the type of variable contained in the same fields but for different elements of the array, may be different! 
    In this case, we just analyze the element 0 of the array. 

*/

// END of example.
//---------------------------------------------------------------
// Compile it, this way:  mex MyMex1.c; 
// You may run it, e.g.

// [a,b,c]= MyMex1( zeros(2,3), uint8([2,3,4]),rand(3,4,5,'single')) ;

//---------------------------------------------------------------
// Questions:  Ask, via Moodle or email j.guivant@unsw.edu.au
//---------------------------------------------------------------
