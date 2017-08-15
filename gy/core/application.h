#ifndef __gy_core_application_h__
#define __gy_core_application_h__

#include <memory>
#include "application_entrypoint.h"

class GApplication
{
protected:
	GApplication();
public:
	virtual ~GApplication();

private:
	result_t initialize();
protected:
	virtual result_t onPreInitialize();
	virtual result_t onInitialize();
	virtual result_t onPostInitialize();
	
protected:
	friend result_t startApplication(std::shared_ptr<GApplication>&&);
	result_t execute();
private:
	result_t onExecute();
	
private:
	result_t finalize();
protected:
	virtual result_t onPreFinalize();
	virtual result_t onFinalize();
	virtual result_t onPostFinalize();

public:
	static std::shared_ptr<GApplication> get();
};

result_t startApplication(std::shared_ptr<GApplication>&&);
namespace gy
{
#include "application.inl"
}

#endif
