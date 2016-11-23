#include "AConnection.h"

const PartyManager & AConnection::getPartyManager(void) const {
	return _pm;
	// TODO: insérer une instruction return ici
}

const RequestHandler & AConnection::getRequestHandler(void) const {
	return _rh;
	// TODO: insérer une instruction return ici
}

void AConnection::setID(int id) {
	_id = id;
}

const std::shared_ptr<Party>& AConnection::getCurrentParty(void) const {
	return this->_party;
}

AConnection::AConnection(PartyManager &pm, RequestHandler &rh, ConnectionManager &cm) : _pm(pm), _rh(rh), _cm(cm) {}


AConnection::~AConnection() {}
