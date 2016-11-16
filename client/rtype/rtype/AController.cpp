#include "AController.hpp"

AController::AController(ProjectResource &resource)
	: _resource(resource)
{
}

AController::~AController(void)
{
}

ProjectResource &AController::getProjectResource(void)
{
	return (_resource);
}