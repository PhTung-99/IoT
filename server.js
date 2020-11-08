const { WSASERVICE_NOT_FOUND } = require('constants');
const { json } = require('express');
var express = require('express');  
const { Socket } = require('net');
const { emit } = require('process');
var app = express();  
var server = require('http').createServer(app); 
var io = require('socket.io')(server); 
var dth11 = '{"teamId":"4","status":"pending"}';
var myDb, collection;
const mongoClient = require('mongodb').MongoClient

const url = "mongodb://localhost:27017"

app.use(express.json())

mongoClient.connect(url, (err, db) => {

    if (err) {
        console.log("Error while connecting mongo client")
    } else {

        myDb = db.db('DTH11')
        collection = myDb.collection('Log')
    }
});
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
        var parse_obj = JSON.parse(dth11);
        
        //dateJson = '{"Time":"'+getNow()+'"}';
        dateJson = JSON.parse('{"Time":"'+getNow()+'"}');
        var timeDTH11 = Object.assign(dateJson, parse_obj)
        saveData(timeDTH11);
            
    });
    client.on('DTH11', function(data) {
        data = '{"teamId":"4","status":"pending"}';
        var parse_obj = JSON.parse(data);
        dateJson = JSON.parse('{"Time":"'+getNow()+'"}');
        var timeDTH11 = Object.assign(dateJson, parse_obj)
        saveData(timeDTH11);
    });
});
io.on('disconnection', function(client) { 
    console.log("Disconnect");
    db.close();
});
//start our web server and socket.io server listening
server.listen(3000, function(){
  console.log('listening on *:3000');
}); 

function getNow()
{
    var today = new Date();
    var date = today.getDate()+'/'+(today.getMonth()+1)+'/'+today.getFullYear();
    var time = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();
    var dateTime = time+'-'+date
    return dateTime;
}
function saveData(data) {
    if(myDb != null && collection != null)
    {
        collection.insertOne(data);
    }
    else
    {
        console.log("Fail to connect collection or database");
    }
    
}
