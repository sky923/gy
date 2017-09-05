#ifndef __gy_core_application_h__
#define __gy_core_application_h__

#include <memory>
#include "application_entrypoint.h"

class GApplication : public GObject
{
protected:
	GApplication();
public:
	virtual ~GApplication();

protected:
	virtual result_t onPreInitialize() override;
	virtual result_t onInitialize() override;
	virtual result_t onPostInitialize() override;
	
protected:
	friend result_t startApplication(std::shared_ptr<GApplication>&&);
	result_t execute();
private:
	result_t onExecute();
	
protected:
	virtual result_t onPreFinalize() override;
	virtual result_t onFinalize() override;
	virtual result_t onPostFinalize() override;

public:
	static std::shared_ptr<GApplication> get();
};

result_t startApplication(std::shared_ptr<GApplication>&&);
namespace gy
{
#include "application.inl"
}

#endif
