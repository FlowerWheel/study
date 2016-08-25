/**
 * Created by admin on 2015/8/1.
 */
'use strict';
var tls = require('tls');
var fs = require('fs');

var options = {
	// These are necessary only if using the client certificate authentication
	//key: fs.readFileSync('./cert/cli/key.pem'),
	//cert: fs.readFileSync('./cert/cli/csr.pem'),
	//
	//// This is necessary only if the server uses the self-signed certificate
	host: '127.0.0.1',

	ca: [fs.readFileSync('./cert/srv/cert.pem')],

	rejectUnauthorized: false,

	checkServerIdentity: function (host, cert) {
		return true;
	}
};

var socket = tls.connect(8000, options, function () {
	console.log('client connected', socket.authorized ? 'authorized' : 'unauthorized');
	process.stdin.pipe(socket);
	process.stdin.resume();
});
socket.setEncoding('utf8');
socket.on('data', function (data) {
	console.log(data);
});
//socket.on('end', function() {
//	server.close();
//});