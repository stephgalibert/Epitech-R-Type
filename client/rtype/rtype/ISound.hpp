#pragma once

#include <string>

#include "MemoryFile.hpp"

class ISound
{
public:
	virtual ~ISound(void) {}
	virtual void stop(std::string const& tostop) = 0;
	virtual void play(std::string const& play) = 0;
	virtual void setLoop(std::string const& toloop, bool value) = 0;
	virtual void pause(std::string const& topause) = 0;
	virtual void setVolumeBySample(std::string const& sample, float value) = 0;
	virtual float getVolumeBySample(std::string const& sample) = 0;
	virtual void addSample(std::string const& name, MemoryFile const& file) = 0;
	virtual void addSample(std::string const& name, std::string const& path) = 0;
	virtual sf::SoundSource::Status getStatus(std::string const& name) const = 0;
};