/* MyMex2.c ; version 2017.1. 
 * 
 * example code for interfacing C- functions with Matlab.
 *
 *
 * In this example, we implement a function, which is SPECIFICALLY made for implementing
 * 2D Occupancy Grids, i.e. a sort of 2d histogram.
 * (This is a real example, because we actually do something...)
 *
 *  In this function we expect to be called in this way:
 *  M = MyMex2( A, B )
 *
 * Where:
 * A is a vector of 5x1 elements, class double, whose interpretation/convention is explained below.
 * B is a matrix of 2xN elements, class double, representing coordinates of 2D points.
 * 
 * Variable A is intended to indicate this [ x1,x2,y1,y2, s ]
 * where we understand that the caller wants to define a ROI (2D region of interest)
 *  [x1:x2] x [y1:y2], and specify sizes (square, grid cells)  = s.
 *  The function will implement an "Occupancy Grid", for indicating population of points in each grid cell
 *  It will return a matrix of proper size and of class unsigned int of 16 bits.
 *  Each element of the matrix corresponds to a grid cell, and will contain the number of points that belong 
 *  to that grid cell.
 *  (i.e. it is a 2D HISTOGRAM )
 
 * Variable B is assumed to contain a cloud of 2D points. It must be of size 2 x N, 
 * being N decided by the caller.
 * The first row is interpreted as x-coordinates of the points; the second row as y-coordinates.
 *
 *  Jose Guivant - MTRN2500 - S2.2017
 */


// We need to include this header, for including useful declarations to the compiler.
#include "mex.h"



// --------------- my part here ----

//Declare some C-functions, which I define later.
static void DescribeVariable(const mxArray *ma);
static void ErrorInInput1(void);
static void ErrorInInput2(void);
static void BadCheck(int e);
static void ByeByeFunction(void);

static int IfFailBeQuiet=0;


// the main entry, to this MEX functions, is here,  "mexFunction(...)"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    //some local C variables.
    const mwSize  *dimsA;   mwSize        numDimsA; 
    const mwSize  *dimsB;   mwSize        numDimsB; 
    const mxArray *maA,*maB;
    
    
    
    
    // We can also define STATIC variables. They will persist through multiple calls to this MEX function
    {   static int FlagLoaded=0;
        if (FlagLoaded==0)
        {    FlagLoaded=1;
             mexAtExit(ByeByeFunction);             
             mexPrintf("Hello. You are using MyMEx2.c, version 2016.1\n");
             //for instance, I use a static variable, as a flag, for installing
             //a callback function, just once.
        }
    }
    
    
    // If my function expects certain type of inputs, I should verify 
    // that the caller is respecting those assumptions.
    // Here we expect two input arguments, and one output variable.
    if (( nrhs != 2 )||(nlhs!=1))
    {   if (IfFailBeQuiet){   goto FailQuietly ; }
        
        mexPrintf("This function expects 2 input and 1 output arguments!  (e.g. C=MyMex2(A,B);)\n");
        mexErrMsgTxt("Error in MyMex2:");       //this is the way, when we want to generate ERROR
        return;
    } 
    
    
    
    // get the pointers of the current input variables, which are just 2.
    maA = prhs[0];    maB = prhs[1];
    
    // get info (size,dimensionality) about the input variables
    numDimsA = mxGetNumberOfDimensions(maA);    // how many dimensions
    dimsA = mxGetDimensions(maA);               // length of each dimension
    numDimsB = mxGetNumberOfDimensions(maB);    //  as case maA
    dimsB = mxGetDimensions(maB);               //  as case maB
    
    
    /* Now I verify the consistency of the input data
     * It is my responsability to verify that the data is consistent 
     * IN THIS PARTICULAR function I expect 2 input arguments:
     * The first one must be a 5x1 vector, class double
     * Second one must be a 2xN vector, class double (N could be any N>0)
    */
    
    if (numDimsA<1){   ErrorInInput1();  }
    if (mxGetClassID(maA)!=mxDOUBLE_CLASS){   ErrorInInput1();}
    if (dimsA[0]!=5){   ErrorInInput1();  }
    //I just consider the first dimension, that must be of length =5;
    
    
    // in this one, I want to be  strict, so it must be 2XN, and of class "double".
    if (numDimsB!=2){   ErrorInInput2();  }             
    if (mxGetClassID(maB)!=mxDOUBLE_CLASS){   ErrorInInput2();}     
    
    if ((dimsB[0]!=2)||(dimsB[1]<1)){   ErrorInInput2();  }
    // it must have 2 rows and at least 1 column.
    
    
    // Now, because I am sure the data seems OK, I continue processing the call.
        
    {   double x1,x2,y1,y2,d,a ; int error=0 ; double Nx,Ny ; int iNx,iNy;
        double *pA,*pB;
        
        pA = mxGetPr(maA);             //this is a pointer to the actual data!
        
        // I expect the data, in the first argument, to contain [x1;x2;y1;y2;d]
        x1 = pA[0]; x2 = pA[1]; y1 = pA[2]; y2 = pA[3]; d = pA[4]; 
        //Elements (1:5) in Matlab, are here, in C, [0:4]
        
        // I also check if the data makes sense
        if (d<1e-10){   BadCheck(1); }              // Grid's cells too small. No sense. Bye.
        if (x1>x2){   a=x1; x1=x2 ; x2=a ; }        // x1,x2 seems inverted. Correct order.
        if (y1>y2){   a=y1; y1=y2 ; y2=a ; }        // y1,y2 seems inverted. Correct order.
        Nx = ((x2-x1)/d);                    // for the given range [x1:x2] and the grid cell size I need Nx cells in X
        Ny = ((y2-y1)/d);                    // for the given range [y1:y2] and the grid cell size I need Nx cells in Y
        if ((Nx<1.0)||(Ny<1.0)){   BadCheck(2); }       //non sense...
        //Nx+=1.0; Ny+=1.0;                             // some safety gap.
        if ( (Nx*Ny)>3000000.0)              // some other limits, e.g. no more than "3Mega" elements
        {   BadCheck(3); }
        
        iNx= (int)Nx;      iNy= (int)Ny;       // I use integers for representing indexes, in C/C++ 
        
        // I create a proper matrix for reporting the result.
        // is this case a iNy x iNx, uint16 matrix.
        plhs[0] = mxCreateNumericMatrix(iNy, iNx, mxINT16_CLASS,mxREAL); 
        
        if (plhs[0]==NULL){   BadCheck(4); }        //just in case, if there is no available memory....
        
        // Finally, because all is OK, I do the real calculation.
        {   unsigned short int *pO = (unsigned short int*)mxGetPr(plhs[0]);
            int numOfPoints = dimsB[1];     
            int i,ix,iy,ixy;
            double x,y,c;
            c=1.0/d;
            pB = mxGetPr(maB);                  //get pointer to data of entry B
            for (i=0;i<numOfPoints;i++,pB+=2)
            {   x=pB[0] ; y=pB[1] ;             //why am I doing "pB+=2"? (we discuss it in the lecture)
                ix = (int)((x-x1)*c);           // convert (x,y) to indexes (ix,iy)
                iy = (int)((y-y1)*c); 
                if ( (ix<0)||(ix>=iNx)||(iy<0)||(iy>=iNy))
                {    continue ; } // point is outside the ROI, ignore it.
                
                ixy = ix*iNy+iy;  // see note about memory organization in a Matlab matrix (note #2)
                pO[ixy]++;        //increment associated grid cell element, in Matrix.
            }
        }
    }           
    return;
    
    
    
    
    
    
    //----------------------------------------------
    //alternative quiet way of "failing": just returning empty variables, [], in each of the required output vars.
    
FailQuietly:
    
    
    if (nlhs>0)
    {   int i;
        for (i=0;i<nlhs;i++){  plhs[i] = mxCreateNumericMatrix(0, 0, mxINT16_CLASS,mxREAL);  }
    }    
    return ;
     
    
    
}

//---------------------------------------------------------
// .. some functions to report errors...

static void ErrorInInput1(void)
{   mexErrMsgTxt( "Error: A must be 5x1, class double (C=MyMex2(A,B);)");
}
static void ErrorInInput2(void)
{   mexErrMsgTxt( "Error: B must be 2xN, class double (C=MyMex2(A,B);)");
}
static void BadCheck(int e)
{   mexPrintf("Error #%d in MyMex2().",e) ; // (you may be more explicit reporting errors)
    mexErrMsgTxt("Another error!"); 
}


//---------------------------------------------------------

// when this MEX module is unloaded from memory (and destroyed), this function
// will be called by the system.
// because I installed it via "atexit()", one by this module.
// this function would be called when you close Matlab, or when you do "clear all" or when
// you recompile the mex file (if a previous instance of it was already in memory)

static void ByeByeFunction(void)
{   mexPrintf("The DLL mex module MyMex2.mex is being unloaded...\nHasta la vista!\n");
    // this is a good opportunity to free resources
    // such as dynamic memory, file handles, ...etc,etc; which you
    // may have created/obtained for this module. 
    //It is your RESPOSIBILITY
}    
//---------------------------------------------------------

/* Note #2:
 *
 *In a matrix of size N1xN2xN3.
 * the matrix contents are stored in linear memory. The elements are ordered as follows:
 *  [M(1,1,1),..M(i,1,1),...M(N1,1,1)]
 * then [ M(1,2,1) ....M(N1,2,1)]  then ...then [ M(1,N2,1) ....M(N1,N2,1)] ....
 * 
 * Consequently, the linear index for element (a,b,c) of a matrix of size N1xN2xN3
 * would be  
 *      i=a+(b-1)*N1 + (c-1)*N1*N2 , in Matlab ( a in [1,N1], b in [1,N2] .... and i in [1,N1*N2*N3])
 *      i=a+ b   *N1 +  c   *N1*N2 , in C/C++  ( a in [0,N1), b in [0,N2) ....and i in [0,N1*N2*N3))
 * 
 */

// .......................................................................

// DONE.
// Questions : ask the lecturer. Jose Guivant - j.guivant@unsw.edu.au OR via MTRN2500's Moodle


// .......................................................................