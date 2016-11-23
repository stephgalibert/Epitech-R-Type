#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <iostream>

#include "ISound.hpp"

/* Utilisé pour les bruitages (son court) */
class SoundBox : public ISound
{
public:
	SoundBox(void);
	virtual ~SoundBox(void);
	virtual void stop(std::string const& tostop);
	virtual void play(std::string const& toplay);
	virtual void setLoop(std::string const& toloop, bool value);
	virtual void pause(std::string const& topause);
	virtual void setVolumeBySample(std::string const& sample, float value);
	virtual float getVolumeBySample(std::string const& sample);
	virtual void addSample(std::string const& name, MemoryFile const& file);
	virtual void addSample(std::string const& name, std::string const& file);
	virtual sf::SoundSource::Status getStatus(std::string const& name) const;
	sf::Sound *getSound(std::string const& key) const;

private:
	struct SoundStruct
	{
		sf::Sound *sound;
		sf::SoundBuffer *buffer;
	};
	std::unordered_map<std::string, SoundStruct *> _sample;
};

