var fs = require('fs');

function one(ins0) {
	var graph = [];
	var ins = [];
	for (var i in ins0) {
		var before = ins0[i].substr(5, 1);
		var after = ins0[i].substr(36, 1);
		if (! graph[after]) {
			graph[after] = [];
		}
		graph[after].push(before);
		ins[before] = true;
		ins[after] = true;
	}
	var visited = [];
	//throw 0;
	var done = [];
	var visit = function(node) {
		visited[node] = true;
		done.push(node);
		for (var i in graph) {
			var where = graph[i].indexOf(node);
			if (where >= 0)
				graph[i].splice(where, 1);
		}
	};
	for ( ;; ) {
		var possible = [];
		for (var i in ins) {
			if (empty(graph[i]) && ! visited[i])
				possible.push(i);
		}
		if (possible.length == 0)
			break;
		possible.sort();
		visit(possible[0]);
	}
	return done;
}

function clone_graph(g) {
	var ret = [];
	for (var i in g) {
		ret[i] = [];
		for (var j in g[i])
			ret[i][j] = g[i][j];
	}
	return ret;
}

function each(obj, f) {
	for (var k in obj) {
		f(k, obj[k]);
	}
}

function empty(arr) {
	return !(arr && arr.length != 0);
}

function get_order(ins0) {
	var g = [];
	for (var i in ins0) {
		var before = ins0[i].substr(5, 1);
		var after = ins0[i].substr(36, 1);
		if (! g[before]) {
			g[before] = [];
		}
		g[before].push(after);
	}
	var ALPHA = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
	var biggest = [ 0, '', null ];
	for (var unique = 0; unique < 26; ++unique) {
		var starting = ALPHA.charAt(unique);
		var Q = [ starting ];
		var order = [];
		var visited = [];
		while (Q.length > 0) {
			var r = Q.shift();
			if (visited[r])
				continue;
			visited[r] = true;
			order.push(r);
			for (var i in g[r]) {
				Q.push(g[r][i]);
			}
		}
		console.log(order.toString());
		if (order.length > biggest[0]) {
			biggest[0] = order.length;
			biggest[1] = starting;
			biggest[2] = order;
		}
	}
	return biggest[2];
}

function two(ins0) {
	var order = get_order(ins0);
	throw order;
	console.log(order);
	var graph = [];
	var ins = [];
	for (var i in ins0) {
		var before = ins0[i].substr(5, 1);
		var after = ins0[i].substr(36, 1);
		if (! graph[after]) {
			graph[after] = [];
		}
		graph[after].push(before);
		ins[before] = true;
		ins[after] = true;
	}
	var get_time = function(str) {
		//return str.charCodeAt(0) - 64;
		return str.charCodeAt(0) - 4;
	};
	var done = [];
	var rm = function(node) {
		for (var i in graph) {
			var where = graph[i].indexOf(node);
			if (where >= 0)
				graph[i].splice(where, 1);
		}
		done[node] = true;
	};
	var workers = [];
	for (var i = 0; i < 5; ++i) {
		workers[i] = {
			t : 0,
			job : null,
		};
	}
	var t = 0;
	var is_job_being_worked_on = function(job) {
		for (var i in workers) {
			if (workers[i].job == job)
				return true;
		}
		return false;
	};
	var get_next_job = function() {
		for (var i in order) {
			var cjob = order[i];
			if (!done[cjob] && empty(graph[cjob]) && !is_job_being_worked_on(cjob)) {
				return cjob;
			}
		}
		return -1;
	};
	var get_ready_worker = function() {
		for (var i in workers) {
			if (workers[i].t <= t)
				return i;
		}
		return -1;
	};
	for (var ov = 0; ov < 10000; ++ov) {
		for ( ; ; ) {
			var job_added = false;
			var who = get_ready_worker();
			if (who != -1) {
				if (workers[who].job) {
					rm(workers[who].job);
					workers[who].job = null;
				}
				var job = get_next_job();
				if (job != -1) {
					workers[who].job = job;
					workers[who].t = t + get_time(job);
					//console.log(t, who, 'got job', job);
					job_added = true;
				}
			}
			if (!job_added)
				break;
		}
		++t;
	}
	var biggest = 0;
	for (var i in workers) {
		biggest = Math.max(workers[i].t, biggest);
	}
	console.log('t', biggest);
	console.log('answer is not 218');
}

fs.readFile('in.txt', function(err, data) {
	if (err)
		throw err;
	data = data.toString().trim().split('\n');
	two(data);
});
