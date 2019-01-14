var fs = require('fs');

function one(ins) {
	console.log(ins.length);
}

fs.readFile('in.txt', function(err, data) {
	if (err)
		throw err;
	data = data.toString().trim().split('\n');
	one(data);
});
