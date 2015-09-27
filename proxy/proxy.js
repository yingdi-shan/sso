var http = require('http'),
    httpProxy = require('http-proxy');

var addresses = require('./sso_server.json')


var proxy = httpProxy.createProxyServer();



var hashCode = function (str) {
    var hash = 0;
    if (str.length == 0) return hash;
    for (var i = 0; i < str.length; i++) {
        var char = str.charCodeAt(i);
        hash = ((hash << 5) - hash) + char;
        hash = hash & hash; // Convert to 32bit integer
    }
    return hash;
}

var server = http.createServer(function (req, res) {
    var param = require('url').parse(req.url, true).query;
    
    var sso_id;
    if("username" in param)
        sso_id= hashCode(param.username)%addresses.length;
    else
        sso_id=Math.floor(Math.random()*addresses.length);
    
    var target = { target: addresses[sso_id]};

     proxy.web(req, res, target);
});

server.on('connection', function (socket) {
    socket.setNoDelay(true);
});


server.listen(8090);