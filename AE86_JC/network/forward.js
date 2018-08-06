// Simple port forwarding ...
// forward.js <local port> <forward host> <forward port>
// // i.e. "forward.js 8080 1.2.3.4 80" will forward 127.0.0.1:8080 to 1.2.3.4:80
// var net = require("net");

// var portIn = process.argv[2],
//     hostOut = process.argv[3],
//     portOut = process.argv[4];

// net.createServer(function(connIn) {
// 	var connOut = net.createConnection(portOut, hostOut);
// 	connIn.pipe(connOut);
// 	connOut.pipe(connIn);
// 	connOut.on("end", connIn.end.bind(connIn));
// 	connIn.on("end", connOut.end.bind(connOut));
// }).listen(portIn);\


var forward = require('http-port-forward');
 
// forward all local 1088 port http requests to 88 port. 
forward(8181, 8182);