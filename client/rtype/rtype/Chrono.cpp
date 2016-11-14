#include "Chrono.h"

Tools::Chronometer::Chronometer(void)
{
  this->_running = false;
  this->_value = 0;
}

Tools::Chronometer::~Chronometer(void)
{

}

float Tools::Chronometer::restart(void)
{
	float elapsed = 0.;

	elapsed = getElapsedTime();
	this->_value = 0.;
	start();
	return (elapsed);
}

void Tools::Chronometer::toggle(void)
{
  if (!this->_running)
    start();
  else
    pause();
}

void Tools::Chronometer::start(void)
{
  this->_current = std::chrono::steady_clock::now();
  if (!this->_running)
    this->_running = true;
}

void Tools::Chronometer::pause(void)
{
  if (this->_running)
    {
      this->_value += getElapsedTime();
      this->_running = false;
    }
}

float Tools::Chronometer::getElapsedTime(void)
{
  if (this->_running)
    {
      this->_begin = std::chrono::steady_clock::now();
      std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float> >(this->_begin - this->_current);
      return (time_span.count() + this->_value);
    }
  return (this->_value);
}
