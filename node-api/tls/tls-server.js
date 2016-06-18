/**
 * Created by admin on 2015/8/1.
 */
'use strict';
var fs = require('fs');
var tls = require('tls');

var options = {
	key : fs.readFileSync('./cert/srv/key.pem'),
	cert: fs.readFileSync('./cert/srv/cert.pem'),

	// This is necessary only if using the client certificate authentication.
	//requestCert: true,

	rejectUnauthorized: true,

	ca: [fs.readFileSync('./cert/srv/cert.pem')]
};

var server = tls.createServer(options, function (socket) {
	console.log('server connected', socket.authorized ? 'authorized' : 'unauthorized');
	socket.write("welcome!\n");
	socket.setEncoding('utf8');
	socket.pipe(socket);
});

server.listen(8000, function () {
	console.log('server bound');
});

server.on('error', function (err) {
	console.error(err);
});
