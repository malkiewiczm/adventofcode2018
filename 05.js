var fs = require('fs');

function one(ins) {
	var l = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
	var u = 'abcdefghijklmnopqrstuvwxyz';
	for ( ; ; ) {
		var last_len = ins.length;
		for (var i = 0; i < 26; ++i) {
			var a = l.charAt(i) + u.charAt(i);
			var b = u.charAt(i) + l.charAt(i);
			ins = ins.split(a).join('');
			ins = ins.split(b).join('');
		}
		if (last_len == ins.length) {
			break;
		}
	}
	return ins.length;
}

function two(ins) {
	var l = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
	var u = 'abcdefghijklmnopqrstuvwxyz';
	var smallest = 1 / 0;
	for (var i = 0; i < 26; ++i) {
		var ins0 = ins.split(l.charAt(i)).join('').split(u.charAt(i)).join('');
		var ret = one(ins0);
		if (ret < smallest) {
			smallest = ret;
		}
	}
	console.log('smallest', smallest);
}

fs.readFile('in.txt', function(err, data) {
	if (err)
		throw err;
	data = data.toString().trim();
	console.log(one(data));
	//console.log(one('dabAcCaCBAcCcaDA'));
	//two(data);
	//two('dabAcCaCBAcCcaDA');
});
