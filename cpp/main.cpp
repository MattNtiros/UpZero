#include <iostream>
#include "ossie/ossieSupport.h"

#include "UpZero.h"
int main(int argc, char* argv[])
{
    UpZero_i* UpZero_servant;
    Resource_impl::start_component(UpZero_servant, argc, argv);
    return 0;
}

