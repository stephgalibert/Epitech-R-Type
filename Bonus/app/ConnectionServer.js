const net = require('net');

function ParseBuffer(buf, serv) {
    var i = 0;
    while (i < buf.length) {
        switch (buf.readUInt8(i)) {
            case CommandType.GetParty:
                if (i == 0) {
                    serv.PartyList = [];
                }
                serv.PartyList.push(new Party(buf, i));
                i += buf.readUInt8(i + 4) + 5;
                break;
            case CommandType.Ping:
                if (i == 0) {
                    serv.PartyList = [];
                }
                i += 8;
                break;
        }
    }
}

function isFull(buf) {
    var i = 0;
    while (i < buf.length) {
        switch (buf.readUInt8(i)) {
            case CommandType.GetParty:
                i += buf.readUInt8(i + 4) + 5;
                break;
            case CommandType.Ping:
                i += 8;
                return true;
            default:
                i++;
                break;
        }
    }
    return false;
}

class Party {
    constructor(buffer, cursor) {
        this.nbPlayers = buffer.readUInt8(cursor + 1);
        this.pwdPresent = buffer.readUInt8(cursor + 2) != 0;
        this.running = buffer.readUInt8(cursor + 3) != 0;
        var size = buffer.readUInt8(cursor + 4);
        this.name = buffer.toString('utf-8', cursor + 5, size + cursor + 5);
    }

    getName() {
        return this.name;
    }

    isRunning() {
        return this.running;
    }

    hasPassword() {
        return this.pwdPresent;
    }

    getNbPlayers() {
        return this.nbPlayers;
    }
}

var CommandType = {
    Ping: 0,
    Error: 1,
    Disconnected: 2,
    GetParty: 3,
    GameStatus: 4,
    Connect: 5,
    CreateParty: 6,
    Score: 7,
    Respawn: 8,
    Message: 9,
    Spawn: 10,
    Move: 11,
    Destroyed: 12,
    Fire: 13,
    Collision: 14,
    LoadedPowder: 15,
    SpawnPowerUp: 16,
    Disconnect: 17,
    SpawnPlayer: 18
}

class Server {
    constructor(ip, port) {
        this.ip = ip;
        this.port = port;
        this.taskArray = [];
        this.Connected = false;
        this.client = null;
        this.PartyList = [];
        this.buf = new Buffer([]);
    }
    Connect() {
        this.client = net.connect({
            port: this.port,
            host: this.ip
        }, () => {
            this.Connected = true;
            setInterval(() => {
                this.Updater()
            }, 700);
        });
        this.client.on('data', (data) => {
            this.buf = Buffer.concat([this.buf, data], this.buf.length + data.length);
            if (isFull(this.buf)) {
                ParseBuffer(this.buf, this);
                this.buf = new Buffer([]);
            }
        });
        this.client.on('end', () => {
            this.Connected = false;
            this.client = null;
        });
        this.client.on('close', () => {
            this.Connected = false;
            this.client = null;
        });
        this.client.on('error', () => {
            this.client = null;
            this.Connected = true;
        })
    }
    Updater() {
        if (this.client != null) {
            var buf1 = new Buffer([CommandType.GetParty, 0, 0, 0, 0]);
            this.client.write(buf1, 'utf-8');
        }
    }

    CreateParty(PartyName, PartyPassword) {
        var cmd = PartyName + ";" + PartyPassword;
        var buf1 = new Buffer([CommandType.CreateParty, 0, 0]);
        var buf2 = Buffer.from(cmd);
        buf1.writeUInt16LE(buf2.length, 1);
        var buff = Buffer.concat([buf1, buf2], buf1.length + buf2.length);
        this.client.write(buff, 'utf-8');
    }

    GetPartys() {
        return this.PartyList;
    }
}

module.exports = function (ip, port) {
    return new Server(ip, port);
}