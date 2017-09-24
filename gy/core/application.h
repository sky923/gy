#ifndef __gy_core_application_h__
#define __gy_core_application_h__

#include <memory>
#include <thread>
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
	virtual result_t execute() final;
private:
	result_t onExecute();

protected:
	virtual result_t onPreFinalize() override;
	virtual result_t onFinalize() override;
	virtual result_t onPostFinalize() override;

public:
	static std::shared_ptr<GApplication> get();

protected:
	std::atomic<bool> bHasStartedEventDispatch;
	std::atomic<bool> bTryToExit;
	// main thread but just for dispatch system message and has low priority
	std::thread::id mainThreadId;
	// user thread using mainly and has processing almost every jobs
	std::thread::id eventDispatchThreadId;
};

result_t startApplication(std::shared_ptr<GApplication>&&);
namespace gy
{
#include "application.inl"
}

#endif
