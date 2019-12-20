/*
 * File:   Web.js
 * Author: Rakul R Sampath
 *
 * Created on 18 December 2019, 12:13
 *
 * Node JS/Javascript Task
 */

var http = require('http');
var fs = require('fs');

function handle_incoming_request(req, res) {
	console.log("INCOMING REQUEST: " + req.method + " " + req.url);
	load_sensor_data(function (err, readings) {
		if (err) {
			console.log("Couldn't read file");
		}
		console.log(readings);
		res.writeHead(200, {
			"Content-Type": "application/json"
		});
		var readingData = readings.trim().split(',')
		var i;
		for (i = 0; i < readingData.length; i++) {
			res.end(JSON.stringify({
				timeValue: readingData[0].trim(),
				temperatureData: readingData[1].trim(),
				humidityMeasuredValue: readingData[2].trim(),
				speedOfWind: readingData[3].trim(),
				locationName: readingData[4].trim(),

			}));
		}
	});
}

function load_sensor_data(callback) {
	fs.readFile(
		"sensorlog.txt", 'utf8',
		function (err, readings) {
			if (err) {
				callback(err);
				return;
			}
			callback(null, readings);
		}
	);
}
var s = http.createServer(handle_incoming_request);
s.listen(8080);

