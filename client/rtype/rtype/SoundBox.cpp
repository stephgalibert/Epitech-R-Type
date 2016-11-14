#include "SoundBox.hpp"

SoundBox::SoundBox(void)
{
}

SoundBox::~SoundBox(void)
{
	for (auto it : _sample) {
		if (it.second) {
			delete (it.second->sound);
			delete (it.second->buffer);
			delete (it.second);
		}
	}
}

void SoundBox::play(std::string const& toplay)
{
	if (_sample.find(toplay) == _sample.cend()) {
		throw (std::runtime_error("SoundBox: can not play " + toplay));
	}
	_sample[toplay]->sound->play();
}

void SoundBox::setLoop(std::string const& toloop, bool value)
{
	if (_sample.find(toloop) == _sample.cend()) {
		throw (std::runtime_error("SoundBox: can not loop " + toloop));
	}
	_sample[toloop]->sound->setLoop(value);
}

void SoundBox::stop(std::string const& tostop)
{
	if (_sample.find(tostop) == _sample.cend()) {
		throw (std::runtime_error("SoundBox: can not stop " + tostop));
	}
	_sample[tostop]->sound->stop();
}

void SoundBox::pause(std::string const& topause)
{
	if (_sample.find(topause) == _sample.cend()) {
		throw (std::runtime_error("SoundBox: can not pause " + topause));
	}
	_sample[topause]->sound->pause();
}

void SoundBox::setVolumeBySample(std::string const& sample, float value)
{
	if (_sample.find(sample) == _sample.cend()) {
		throw (std::runtime_error("SoundBox: can not set volume " + sample));
	}
	_sample[sample]->sound->setVolume(value);
}

float SoundBox::getVolumeBySample(std::string const& sample)
{
	if (_sample.find(sample) == _sample.cend()) {
		throw (std::runtime_error("SoundBox: can not set volume " + sample));
	}
	return (_sample[sample]->sound->getVolume());
}

void SoundBox::addSample(std::string const& name, MemoryFile const& file)
{
	SoundStruct *sound = NULL;

	if (_sample.find(name) == _sample.cend()) {
		sound = new SoundStruct;
		sound->buffer = new sf::SoundBuffer;
		if (!sound->buffer->loadFromMemory(file.data, file.size)) {
			delete (sound->buffer);
			delete (sound);
			throw (std::runtime_error(name + " not found"));
		}
		sound->sound = new sf::Sound;
		sound->sound->setBuffer(*sound->buffer);
		_sample.insert(std::make_pair(name, sound));
	}
}

sf::SoundSource::Status SoundBox::getStatus(std::string const& name) const
{
	if (_sample.find(name) == _sample.cend()) {
		throw (std::runtime_error("Soundbox: can not get " + name + " status"));
	}
	return (_sample.at(name)->sound->getStatus());
}
