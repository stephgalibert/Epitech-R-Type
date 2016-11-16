#pragma once

# include <SFML/Audio.hpp>
# include <unordered_map>
# include <iostream>

# include "ISound.hpp"

/* Utiliser pour les musiques (son long) */
class MusicBox : public ISound
{
public:
	MusicBox(void);
	virtual ~MusicBox(void);

	virtual void stop(std::string const& tostop);
	virtual void play(std::string const& toplay);
	virtual void setLoop(std::string const& toloop, bool value);
	virtual void pause(std::string const& topause);
	virtual void setVolumeBySample(std::string const& sample, float value);
	virtual float getVolumeBySample(std::string const& sample);
	virtual void addSample(std::string const& name, MemoryFile const& file);
	void addSample(std::string const& name, std::string const& path);
	virtual sf::SoundSource::Status getStatus(std::string const& name) const;
	sf::Music &getMusic(std::string const& key);
private:
	std::unordered_map<std::string, sf::Music *> _sample;
};