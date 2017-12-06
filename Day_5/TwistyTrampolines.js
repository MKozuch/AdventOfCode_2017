// Author: MKozuch
// Date: 17-12-06

var http = require('http');
var querystring = require('querystring');


function calcJumps_trampolines(arr){
    var jumps = 0;
    var index = 0;
    var oldIndex = 0;
    var upperBound = arr.length;

    while(index >= 0 & index < upperBound){
        oldIndex = index;
        index += arr[index];
        arr[oldIndex] += 1;

        jumps +=1;
    }
    return jumps;
}

function calcJumps_strangetrampolines(arr){
    var jumps = 0;
    var index = 0;
    var oldIndex = 0;
    var upperBound = arr.length;

    var jumps = 0;
    var index = 0;
    var oldIndex = 0;
    var upperBound = arr.length;
    var offset = 0;

    while(index >= 0 & index < upperBound){
        offset = arr[index];
        oldIndex = index;
        index += offset;

        if(offset >= 3){
            arr[oldIndex] -= 1;
        }
        else{
            arr[oldIndex] += 1;
        }

        jumps +=1;
    }
    return jumps;
}

const server = http.createServer();
server.on('request', (request, response) => {
    if(request.url == '/trampolines' || request.url == '/strangetrampolines'){
        if(request.method == 'POST'){

            var rawData = '';
            request.on('data', function(chunk){
                rawData += chunk.toString();
                if(rawData.length > 1e6)
                    request.connection.destroy();
            });


            request.on('end', function(){
                var arrStr = rawData.split('\r\n');
                var arrStrFilt = arrStr.filter(val => { return RegExp('^-?[0-9]+$').test(val) });
                var arr = arrStrFilt.map(val => { return Number(val) });

                var jumps = 0;
                if(request.url == '/trampolines'){
                    jumps = calcJumps_trampolines(arr);
                }
                else if( request.url == '/strangetrampolines'){
                    jumps = calcJumps_strangetrampolines(arr);
                }
                else{
                    jumps = -1;
                }

                response.writeHead(200, {'Content-Type': 'text/html'});
                response.end(String(jumps));
            });
        }
        else{
            response.writeHead(405, {'Content-Type': 'text/html'});
            repsonse.end("POST");
        }
    }
    else{
        response.writeHead(404, {'Content-Type': 'text/html'});
        response.write('URL not found');
        response.end();
    }
});

server.listen(8080);