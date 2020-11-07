var express = require('express');  
const { Socket } = require('net');
const { emit } = require('process');
var app = express();  
var server = require('http').createServer(app); 
var io = require('socket.io')(server); 

//keep track of how times clients have clicked the button

app.use(express.static(__dirname + '/public')); 
//redirect / to our index.html file
app.get('/', function(req, res,next) {  
    res.sendFile(__dirname + '/public/index.html');
});

io.on('connection', function(client) { 
    console.log('Client connected...'); 
    
    client.on('up', function(data) {
        io.emit('sttXe', "up");
    });
    client.on('down', function(data) {
        io.emit('sttXe', "down");
    });
    client.on('left', function(data) {
        io.emit('sttXe', "left");
    });
    client.on('right', function(data) {
        io.emit('sttXe', "right");
        console.log("Client  cvbn..."); 
    });
    client.on('message', function(data) {
        console.log(data); 
    });
});
//start our web server and socket.io server listening
server.listen(3000, function(){
  console.log('listening on *:3000');
}); 