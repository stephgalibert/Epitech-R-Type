var express = require('express');
var app = express();
var port = 80;
var ConnectionServer = require('./app/ConnectionServer');
var Client = ConnectionServer('127.0.0.1', '4242');
Client.Connect();

app.use(express.static('html'));

app.get('/Connect', (req, res) => {
    Client = ConnectionServer(req.query.ip, req.query.port);
    Client.Connect();
    res.json({
        success: true
    });
});

app.get('/GetParty', (req, res) => {
    res.json({
        success: true,
        Party: Client.GetPartys()
    });
});

app.get('/CreateParty', (req, res) => {
    Client.CreateParty(req.query.name, req.query.password);
    res.json({
        success: true
    });
});

app.listen(port, () => {
    console.log('Magic happen on : ' + port)
});