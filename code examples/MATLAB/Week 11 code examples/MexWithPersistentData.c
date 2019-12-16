/* MexWithPersistentData.c ; version 2017.1. 
 * 
 * example code for interfacing C- functions with Matlab.
 
 * Basic function, in which we "calloc" memory, and make it persistent.
 * In addition, we use some static variables, which are also persistent, like in C/C++.
 *
 *  Jose Guivant - MTRN2500 - S2.2017
 */


// We need to include this header, for including useful declarations to the compiler.
#include "mex.h"

// --------------- my part here ----

static void ByeByeFunction(void);      

static float *MyBuffer1 = NULL;     // .. to be created dynamically.
static float  MyBuffer2[100];       // created statically.


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    //some local C variables.
    
    
    //run this, once. When the MEX module is loaded, first time (never used before, or after being unloaded.)
    
    if (MyBuffer1==NULL)
    {   MyBuffer1 = (float*)mxCalloc(100,sizeof(float));        //create c array using "calloc"
        if (MyBuffer1==NULL){  return ; }                       // it may fail (e.g. no memory is available.)
        mexMakeMemoryPersistent(MyBuffer1);                     //to make it persistent, even ater the function ends.
        mexAtExit(ByeByeFunction);                              //install callback function; for "closing things" before DLL is removed.
        mexPrintf("Created buffer (p=[%p]), and made it persistent.\n",MyBuffer1);
        
        //initialize/use data....etc.
        MyBuffer1[80]=100;
        MyBuffer2[80]=200;
    }
    
    //Use it.
    MyBuffer1[80]+=1.1111f;
    MyBuffer2[80]+=1.1111f;
    mexPrintf("value of internal buffer, item[80]=[%.2f][%.2f]\n",MyBuffer1[80],MyBuffer2[80]);

    return;
}

//---------------------------------------------------------

// When this MEX module is unloaded from memory (and destroyed), this function
// will be called by the system, because I installed it via "atexit()".
// this function would be called when you close Matlab, or when you do "clear all" or when
// you recompile the mex file (and if a previous instance of it was already in memory)

static void ByeByeFunction(void)
{   mexPrintf("The DLL/mex module is being unloaded...\nHasta la vista!\n");
    // this is a good opportunity to free resources
    // such as dynamic memory, file handles, ...etc,etc; which you
    // may have created/obtained for this module. 
    //It is your RESPOSIBILITY
    
    if  (MyBuffer1!= NULL)
    {   mxFree(MyBuffer1); 
        MyBuffer1= NULL;    // innecessary (the MEX/DLL is being unloaded), but just in case.
        mexPrintf("(Free any persisten memory blocks we had created.)\n");
    }
    
}    
//---------------------------------------------------------
