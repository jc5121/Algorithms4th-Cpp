//tunnel is a ssh2 clientConnection object 
var tunnel = require('reverse-tunnel-ssh');

host_ip = '47.92.5.66';
username = 'root';
password = 'bupt@123';
dstHost = '0.0.0.0'; // bind to all IPv4 interfaces 

web_port = 8181;
rosbridge_port = 9090;
mjpeg_port = 8080;


var conn_web = tunnel({
  host: host_ip,
  username: username,
  password: password,
  dstHost: dstHost,
  dstPort: web_port,
  //srcHost: '127.0.0.1', // default 
  //srcPort: dstPort // default is the same as dstPort 
}, function(error, clientConnection) {
  // 
});


var conn_rosbridge = tunnel({
  host: host_ip,
  username: username,
  password: password,
  dstHost: dstHost,
  dstPort: rosbridge_port,
  //srcHost: '127.0.0.1', // default 
  //srcPort: dstPort // default is the same as dstPort 
}, function(error, clientConnection) {
  // 
});


var conn_mjpeg = tunnel({
  host: host_ip,
  username: username,
  password: password,
  dstHost: dstHost,
  dstPort: mjpeg_port,
  //srcHost: '127.0.0.1', // default 
  //srcPort: dstPort // default is the same as dstPort 
}, function(error, clientConnection) {
  // 
});

conn_web.on('forward-in', function (port) {
  console.log('Forwarding from ' + host_ip + ':' + port);
});

conn_rosbridge.on('forward-in', function (port) {
  console.log('Forwarding from ' + host_ip + ':' + port);
});

conn_mjpeg.on('forward-in', function (port) {
  console.log('Forwarding from ' + host_ip + ':' + port);
});
