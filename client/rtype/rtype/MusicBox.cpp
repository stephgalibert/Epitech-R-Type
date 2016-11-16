#include "MusicBox.hpp"

MusicBox::MusicBox(void)
{

}

MusicBox::~MusicBox(void)
{
	for (auto it : _sample) {
		if (it.second) {
			delete (it.second);
		}
	}
}

void MusicBox::play(std::string const& toplay)
{
	if (_sample.find(toplay) == _sample.cend()) {
		throw (std::runtime_error("MusicBox: can not play " + toplay));
	}
	_sample[toplay]->play();
}

void MusicBox::setLoop(std::string const& toloop, bool value)
{
	if (_sample.find(toloop) == _sample.cend()) {
		throw (std::runtime_error("MusicBox: can not loop " + toloop));
	}
	_sample[toloop]->setLoop(value);
}

void MusicBox::stop(std::string const& tostop)
{
	if (_sample.find(tostop) == _sample.cend()) {
		throw (std::runtime_error("MusicBox: can not stop " + tostop));
	}
	_sample[tostop]->stop();
}

void ::MusicBox::pause(std::string const& topause)
{
	if (_sample.find(topause) == _sample.cend()) {
		throw (std::runtime_error("MusicBox: can not pause " + topause));
	}
	_sample[topause]->pause();
}

void MusicBox::setVolumeBySample(std::string const& sample, float value)
{
	if (_sample.find(sample) == _sample.cend()) {
		throw (std::runtime_error("MusicBox: can not set volume " + sample));
	}
	_sample[sample]->setVolume(value);
}

float MusicBox::getVolumeBySample(std::string const& sample)
{
	if (_sample.find(sample) == _sample.cend()) {
		throw (std::runtime_error("MusicBox: can not set volume " + sample));
	}
	return (_sample[sample]->getVolume());
}

void MusicBox::addSample(std::string const& name, MemoryFile const& file)
{
  sf::Music *sample = NULL;

	if (_sample.find(name) == _sample.cend()) {
		sample = new sf::Music;
		if (!sample->openFromMemory(file.data, file.size)) {
			delete (sample);
			throw (std::runtime_error(name + " not found lol"));
		}
		_sample.insert(std::make_pair(name, sample));
	}
}

void MusicBox::addSample(std::string const& name, std::string const& path)
{
	sf::Music *sample = NULL;

	if (_sample.find(name) == _sample.cend()) {
		sample = new sf::Music;
		if (!sample->openFromFile(path)) {
			delete (sample);
			throw (std::runtime_error(name + " not found lol"));
		}
		_sample.insert(std::make_pair(name, sample));
	}
}

sf::SoundSource::Status MusicBox::getStatus(std::string const& name) const
{
	if (_sample.find(name) == _sample.cend()) {
		throw (std::runtime_error("MusicBox: can not get " + name + " status"));
	}
	return (_sample.at(name)->getStatus());
}

sf::Music &MusicBox::getMusic(std::string const& key)
{
	if (_sample.find(key) == _sample.cend()) {
		throw (std::runtime_error("MusicBox: can not get " + key + " status"));
	}
	return (*_sample.at(key));
}