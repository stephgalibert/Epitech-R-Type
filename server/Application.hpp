//
// Application.hpp for  in /home/jordan/workspace/R-type/server
//
// Made by jordan
// Login   <jordan@epitech.net>
//
// Started on  Mon Nov 21 16:11:11 2016 jordan
// Last update Mon Nov 21 16:42:58 2016 jordan
//

#pragma once

class Application {
 public:
  Application(PartyManager & cm);
 private:
  PartyManager & _cm;
  RequestHandler _rh;
  ConnectionManager _cm;
};
