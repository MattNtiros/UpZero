#include "UpZero_base.h"

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    The following class functions are for the base class for the component class. To
    customize any of these functions, do not modify them here. Instead, overload them
    on the child class

******************************************************************************************/

UpZero_base::UpZero_base(const char *uuid, const char *label) :
    Resource_impl(uuid, label),
    ThreadedComponent()
{
    loadProperties();

    dataFloat_In = new bulkio::InFloatPort("dataFloat_In");
    addPort("dataFloat_In", dataFloat_In);
    dataFloat_Out = new bulkio::OutFloatPort("dataFloat_Out");
    addPort("dataFloat_Out", dataFloat_Out);
}

UpZero_base::~UpZero_base()
{
    delete dataFloat_In;
    dataFloat_In = 0;
    delete dataFloat_Out;
    dataFloat_Out = 0;
}

/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
void UpZero_base::start() throw (CORBA::SystemException, CF::Resource::StartError)
{
    Resource_impl::start();
    ThreadedComponent::startThread();
}

void UpZero_base::stop() throw (CORBA::SystemException, CF::Resource::StopError)
{
    Resource_impl::stop();
    if (!ThreadedComponent::stopThread()) {
        throw CF::Resource::StopError(CF::CF_NOTSET, "Processing thread did not die");
    }
}

void UpZero_base::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    // This function clears the component running condition so main shuts down everything
    try {
        stop();
    } catch (CF::Resource::StopError& ex) {
        // TODO - this should probably be logged instead of ignored
    }

    Resource_impl::releaseObject();
}

void UpZero_base::loadProperties()
{
    addProperty(upsample_factor,
                2,
                "upsample_factor",
                "upsample_factor",
                "readwrite",
                "",
                "external",
                "configure");

}


