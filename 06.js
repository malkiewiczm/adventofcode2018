var fs = require('fs');

function one(ins) {
	var top_left = { x : 1/0, y : 1/0 };
	var bot_right = { x : 0, y : 0 };
	var coords = [];
	for (var i in ins) {
		var splt = ins[i].split(',');
		coords[i] = { x : 0, y : 0, big : false };
		coords[i].x = parseInt(splt[0].trim());
		coords[i].y = parseInt(splt[1].trim());
		if (coords[i].x < top_left.x) {
			top_left.x = coords[i].x;
		}
		if (coords[i].y < top_left.y) {
			top_left.y = coords[i].y;
		}
		if (coords[i].x > bot_right.x) {
			bot_right.x = coords[i].x;
		}
		if (coords[i].y > bot_right.y) {
			bot_right.y = coords[i].y;
		}
	}
	var grid = [];
	for (var y = top_left.y; y <= bot_right.y; ++y) {
		grid[y] = [];
	}
	var foreach_coord = function(f) {
		for (var y = top_left.y; y <= bot_right.y; ++y) {
			for (var x = top_left.x; x <= bot_right.x; ++x) {
				f(x, y);
			}
		}
	};
	var dist = function(p, x, y) {
		return Math.abs(p.x - x) + Math.abs(p.y - y);
	};
	(function() {
		var op = function(x, y) {
			var closest = 0;
			var closestd = 1/0;
			for (var i in coords) {
				var d = dist(coords[i], x, y);
				if (d < closestd) {
					closestd = d;
					closest = i;
				}
			}
			coords[closest].big = true;
		};
		for (var x = top_left.x - 1; x <= bot_right.x + 1; ++x) {
			var y0 = top_left.y - 1;
			var y1 = bot_right.y + 1;
			op(x, y0);
			op(x, y1);
		}
		for (var y = top_left.y; y <= bot_right.y; ++y) {
			var x0 = top_left.x - 1;
			var x1 = bot_right.x + 1;
			op(x0, y);
			op(x1, y);
		}
	})();
	/*
	foreach_coord(function(x, y) {
		var closest = 0;
		var closestd = 1/0;
		for (var i in coords) {
			var d = dist(coords[i], x, y);
			if (d < closestd) {
				closestd = d;
				closest = i;
			}
		}
		var n = 0;
		for (var i in coords) {
			var d = dist(coords[i], x, y);
			if (d == closestd) {
				++n;
			}
		}
		if (n == 1 && !coords[closest].big) {
			grid[y][x] = closest;
		} else {
			grid[y][x] = -1;
		}
	});
	foreach_coord(function(x, y) {
		var closest = 0;
		var closestd = 1/0;
		for (var i in coords) {
			if (coords[i].big)
				continue;
			var d = dist(coords[i], x, y);
			
		}
		var n = 0;
		for (var i in coords) {
			var d = dist(coords[i], x, y);
			if (d == closestd) {
				++n;
			}
		}
		if (n == 1 && !coords[closest].big) {
			grid[y][x] = closest;
		} else {
			grid[y][x] = -1;
		}
	});
	*/
	foreach_coord(function(x, y) {
		for (var i in coords) {
			/*
			if (coords[i].big)
				continue;
				*/
			var d = dist(coords[i], x, y);
			if (grid[y][x]) {
				grid[y][x] += d;
			} else {
				grid[y][x] = d;
			}
		}
	});
	/*
	var counts = [];
	foreach_coord(function(x, y) {
		var k = grid[y][x];
		if (k < 10000) {
			if (counts[k])
				++counts[k];
			else
				counts[k] = 1;
		}
	});
	var bbb = -1;
	for (var i in counts) {
		if (counts[i] > bbb) {
			bbb = counts[i];
		}
	}
	console.log(bbb);
	*/
	var bbb = 0;
	foreach_coord(function(x, y) {
		var k = grid[y][x];
		if (k < 10000) {
			++bbb;
		}
	});
	console.log(bbb);
	console.log('61 is not right');
}

fs.readFile('altin.txt', function(err, data) {
	if (err)
		throw err;
	data = data.toString().trim().split('\n');
	one(data);
});
