#include "Timer.hpp"

Timer::Timer(void)
{
  _running = false;
  _value = 0;
}

Timer::~Timer(void)
{

}

float Timer::restart(void)
{
	float elapsed = 0.;

	elapsed = getElapsedTime();
	_value = 0.;
	start();
	return (elapsed);
}

void Timer::toggle(void)
{
  if (!_running)
    start();
  else
    pause();
}

void Timer::start(void)
{
  this->_current = std::chrono::steady_clock::now();
  if (!_running)
    _running = true;
}

void Timer::pause(void)
{
  if (this->_running)
    {
      _value += getElapsedTime();
      _running = false;
    }
}

float Timer::getElapsedTime(void)
{
  if (_running)
    {
      _begin = std::chrono::steady_clock::now();
      std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float> >(_begin - _current);
      return (time_span.count() + _value);
    }
  return (this->_value);
}
