//
//  Header.h
//  FemSC
//
//  Created by Philippe Devloo on 7/30/15.
//
//

#ifndef FemSC_Panic_h
#define FemSC_Panic_h

///\cond
#include <iostream>
#include <exception>
///\endcond

#ifdef USING_MKL
// #include "pzerror.h" // This is a NeoPZ file, and should be dependent on its linking
#else

#ifdef WIN32
    #define __PRETTY_FUNCTION__ __FUNCTION__
#endif

extern bool PanicMessage;

static void DebugStop()
{
    if(PanicMessage)
    {
        std::cout << "\nYour chance to put a breakpoint here\n" << std::flush;
    }
    std::bad_exception myex;
    throw myex;

}
#endif // USING_MKL
#endif // FemSC_Panic_h
