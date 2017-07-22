#ifndef __gy_core_application_h__
#define __gy_core_application_h__

#include "../pil/type.h"
#include <memory>

class GApplication
{
protected:
	GApplication();
public:
	virtual ~GApplication();

protected:
	friend result_t startApplication(std::shared_ptr<GApplication>&&);
	virtual result_t execute() = 0;

public:
	static std::shared_ptr<GApplication> get();
};

result_t startApplication(std::shared_ptr<GApplication>&&);
namespace gy
{
#include "application.inl"
}
#endif