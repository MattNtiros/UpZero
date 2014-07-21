#ifndef UPZERO_IMPL_BASE_H
#define UPZERO_IMPL_BASE_H

#include <boost/thread.hpp>
#include <ossie/Resource_impl.h>
#include <ossie/ThreadedComponent.h>

#include <bulkio/bulkio.h>

class UpZero_base : public Resource_impl, protected ThreadedComponent
{
    public:
        UpZero_base(const char *uuid, const char *label);
        ~UpZero_base();

        void start() throw (CF::Resource::StartError, CORBA::SystemException);

        void stop() throw (CF::Resource::StopError, CORBA::SystemException);

        void releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

        void loadProperties();

    protected:
        // Member variables exposed as properties
        unsigned short upsample_factor;

        // Ports
        bulkio::InFloatPort *dataFloat_In;
        bulkio::OutFloatPort *dataFloat_Out;

    private:
};
#endif // UPZERO_IMPL_BASE_H
