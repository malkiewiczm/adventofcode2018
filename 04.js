function go(log) {
	var sleeps = [];
	var counts = [];
	var curr = 0;
	var last_time_awake = new Date();
	for (var i = 0; i < log.length; ++i) {
		if (log[i][1] == 0) {
			curr = log[i][2];
		} else if (log[i][1] == 1) {
			last_time_awake = log[i][0];
		} else {
			var amt = log[i][0] - last_time_awake;
			amt /= 60000;
			var from = last_time_awake.getMinutes();
			var to = log[i][0].getMinutes();
			if (sleeps[curr]) {
				for (var j = from; j < to; ++j){
					sleeps[curr][j] += 1;
				}
			} else {
				var arr = [];
				for (var j = 0; j < 60; ++j) {
					arr[j] = 0;
				}
				for (var j = from; j < to; ++j){
					arr[j] = 1;
				}
				sleeps[curr] = arr;
			}
		}
	}
	console.log('-----');
	var biggest = [ 0, 0];
	for (var i in sleeps) {
		var sum = 0;
		for (var j in sleeps[i]) {
			sum += sleeps[i][j];
		}
		console.log(i, sum);
		if (sum > biggest[1]) {
			biggest[1] = sum;
			biggest[0] = i;
		}
	}
	console.log('biggest', biggest);
	var arr = sleeps[biggest[0]];
	var where = 0;
	for (var i in arr) {
		if (arr[i] > arr[where]) {
			where = i;
		}
	}
	console.log(where);
	biggest = [ 0, 0, 0 ];
	for (var i in sleeps) {
		for (var j in sleeps[i]) {
			if (sleeps[i][j] > biggest[2]) {
				biggest[2] = sleeps[i][j];
				biggest[1] = j;
				biggest[0] = i;
			}
		}
	}
	console.log('biggest', biggest);
	console.log(biggest[0] * biggest[1]);
}

var log = [
	[new Date('1518-05-29 00:00'), 0, 1151],
	[new Date('1518-05-12 00:02'), 0, 439],
	[new Date('1518-04-11 00:33'), 1],
	[new Date('1518-06-23 00:52'), 2],
	[new Date('1518-10-25 00:48'), 1],
	[new Date('1518-09-09 00:55'), 1],
	[new Date('1518-10-29 00:18'), 1],
	[new Date('1518-10-24 00:43'), 2],
	[new Date('1518-11-03 00:57'), 2],
	[new Date('1518-04-10 00:03'), 1],
	[new Date('1518-07-17 00:46'), 2],
	[new Date('1518-10-02 00:47'), 2],
	[new Date('1518-04-02 00:48'), 2],
	[new Date('1518-04-27 00:57'), 2],
	[new Date('1518-07-19 00:46'), 2],
	[new Date('1518-09-28 00:44'), 2],
	[new Date('1518-11-05 00:45'), 2],
	[new Date('1518-11-17 00:50'), 2],
	[new Date('1518-08-03 00:15'), 1],
	[new Date('1518-09-21 00:26'), 1],
	[new Date('1518-04-13 00:00'), 0, 947],
	[new Date('1518-08-03 00:39'), 1],
	[new Date('1518-11-23 00:23'), 2],
	[new Date('1518-08-02 00:27'), 2],
	[new Date('1518-10-08 00:04'), 0, 499],
	[new Date('1518-07-12 23:58'), 0, 3449],
	[new Date('1518-09-07 00:38'), 2],
	[new Date('1518-11-16 00:43'), 2],
	[new Date('1518-04-29 00:23'), 1],
	[new Date('1518-10-31 00:53'), 2],
	[new Date('1518-06-25 00:15'), 2],
	[new Date('1518-10-20 23:50'), 0, 947],
	[new Date('1518-08-24 00:23'), 2],
	[new Date('1518-11-11 00:57'), 2],
	[new Date('1518-06-03 00:01'), 0, 947],
	[new Date('1518-09-29 00:43'), 2],
	[new Date('1518-08-24 00:43'), 2],
	[new Date('1518-07-16 00:10'), 1],
	[new Date('1518-06-08 00:21'), 2],
	[new Date('1518-08-17 00:49'), 1],
	[new Date('1518-08-02 00:25'), 1],
	[new Date('1518-09-28 00:53'), 2],
	[new Date('1518-10-19 00:03'), 0, 337],
	[new Date('1518-04-15 00:53'), 1],
	[new Date('1518-09-25 00:52'), 1],
	[new Date('1518-07-17 00:39'), 1],
	[new Date('1518-11-17 00:04'), 0, 2341],
	[new Date('1518-06-06 00:08'), 1],
	[new Date('1518-08-05 00:09'), 1],
	[new Date('1518-04-30 23:56'), 0, 809],
	[new Date('1518-08-19 00:53'), 2],
	[new Date('1518-06-07 00:00'), 0, 2341],
	[new Date('1518-04-15 23:50'), 0, 3019],
	[new Date('1518-09-02 00:55'), 2],
	[new Date('1518-11-19 00:59'), 2],
	[new Date('1518-05-03 00:29'), 1],
	[new Date('1518-11-17 23:49'), 0, 337],
	[new Date('1518-07-02 00:39'), 2],
	[new Date('1518-05-26 00:53'), 1],
	[new Date('1518-06-03 00:20'), 1],
	[new Date('1518-07-14 00:08'), 1],
	[new Date('1518-05-25 00:03'), 0, 1481],
	[new Date('1518-03-19 00:24'), 1],
	[new Date('1518-06-13 00:41'), 1],
	[new Date('1518-07-16 00:49'), 2],
	[new Date('1518-06-01 00:40'), 2],
	[new Date('1518-06-24 00:34'), 2],
	[new Date('1518-04-15 00:00'), 0, 499],
	[new Date('1518-08-24 23:56'), 0, 3019],
	[new Date('1518-04-04 00:03'), 1],
	[new Date('1518-11-05 00:00'), 0, 3119],
	[new Date('1518-05-23 00:54'), 2],
	[new Date('1518-09-19 00:57'), 2],
	[new Date('1518-09-10 00:56'), 2],
	[new Date('1518-05-27 00:04'), 0, 3067],
	[new Date('1518-07-18 00:00'), 1],
	[new Date('1518-08-16 00:36'), 2],
	[new Date('1518-11-12 23:57'), 0, 1481],
	[new Date('1518-07-02 23:46'), 0, 499],
	[new Date('1518-08-17 00:14'), 1],
	[new Date('1518-07-09 23:57'), 0, 2791],
	[new Date('1518-04-11 23:59'), 0, 3067],
	[new Date('1518-09-08 00:20'), 1],
	[new Date('1518-11-10 00:41'), 1],
	[new Date('1518-06-10 00:29'), 2],
	[new Date('1518-04-28 00:55'), 2],
	[new Date('1518-05-22 23:58'), 0, 3019],
	[new Date('1518-07-06 23:57'), 0, 1973],
	[new Date('1518-09-25 00:00'), 0, 1481],
	[new Date('1518-10-22 23:47'), 0, 1973],
	[new Date('1518-10-12 00:42'), 2],
	[new Date('1518-06-18 00:41'), 1],
	[new Date('1518-10-03 00:22'), 2],
	[new Date('1518-10-22 00:50'), 1],
	[new Date('1518-09-24 00:00'), 0, 337],
	[new Date('1518-06-30 23:58'), 0, 2243],
	[new Date('1518-07-01 23:57'), 0, 1951],
	[new Date('1518-06-27 00:57'), 2],
	[new Date('1518-06-24 00:56'), 2],
	[new Date('1518-09-21 00:56'), 2],
	[new Date('1518-10-06 00:36'), 2],
	[new Date('1518-04-28 00:16'), 2],
	[new Date('1518-07-19 23:57'), 0, 3067],
	[new Date('1518-08-27 00:14'), 1],
	[new Date('1518-08-27 00:15'), 2],
	[new Date('1518-04-10 23:57'), 0, 809],
	[new Date('1518-10-02 00:04'), 0, 2243],
	[new Date('1518-09-15 00:47'), 1],
	[new Date('1518-04-29 00:01'), 0, 439],
	[new Date('1518-04-17 00:16'), 1],
	[new Date('1518-11-23 00:16'), 1],
	[new Date('1518-09-29 00:03'), 0, 3449],
	[new Date('1518-10-09 00:03'), 1],
	[new Date('1518-09-18 00:00'), 0, 1951],
	[new Date('1518-05-31 00:54'), 2],
	[new Date('1518-11-07 00:31'), 2],
	[new Date('1518-09-02 00:44'), 1],
	[new Date('1518-07-03 00:55'), 2],
	[new Date('1518-09-11 00:35'), 2],
	[new Date('1518-08-05 00:53'), 2],
	[new Date('1518-06-13 00:55'), 2],
	[new Date('1518-11-02 00:02'), 0, 3119],
	[new Date('1518-06-17 00:50'), 1],
	[new Date('1518-08-03 00:36'), 2],
	[new Date('1518-05-02 00:53'), 1],
	[new Date('1518-06-25 00:48'), 2],
	[new Date('1518-11-10 23:58'), 0, 3019],
	[new Date('1518-08-23 00:36'), 2],
	[new Date('1518-10-26 00:53'), 2],
	[new Date('1518-05-02 00:46'), 2],
	[new Date('1518-07-29 00:45'), 2],
	[new Date('1518-03-19 00:02'), 0, 787],
	[new Date('1518-07-16 00:03'), 0, 947],
	[new Date('1518-10-28 00:02'), 0, 1951],
	[new Date('1518-10-30 00:04'), 0, 947],
	[new Date('1518-08-06 00:56'), 2],
	[new Date('1518-08-05 00:03'), 0, 2791],
	[new Date('1518-04-04 00:42'), 1],
	[new Date('1518-07-06 00:12'), 2],
	[new Date('1518-06-24 00:46'), 1],
	[new Date('1518-05-03 00:59'), 2],
	[new Date('1518-11-07 00:18'), 1],
	[new Date('1518-08-14 00:56'), 1],
	[new Date('1518-03-28 00:02'), 0, 499],
	[new Date('1518-08-07 00:57'), 2],
	[new Date('1518-07-05 00:53'), 2],
	[new Date('1518-05-31 00:38'), 1],
	[new Date('1518-07-04 00:17'), 1],
	[new Date('1518-10-12 00:58'), 2],
	[new Date('1518-10-08 00:44'), 1],
	[new Date('1518-05-22 00:55'), 2],
	[new Date('1518-07-10 23:57'), 0, 947],
	[new Date('1518-04-08 00:33'), 2],
	[new Date('1518-08-08 00:44'), 1],
	[new Date('1518-05-19 00:57'), 2],
	[new Date('1518-04-05 00:01'), 0, 499],
	[new Date('1518-07-04 00:59'), 2],
	[new Date('1518-09-27 00:34'), 1],
	[new Date('1518-11-01 00:21'), 2],
	[new Date('1518-11-23 00:32'), 1],
	[new Date('1518-10-31 00:36'), 2],
	[new Date('1518-04-29 00:57'), 2],
	[new Date('1518-07-10 00:55'), 2],
	[new Date('1518-10-11 00:09'), 1],
	[new Date('1518-10-26 00:28'), 1],
	[new Date('1518-10-27 00:36'), 1],
	[new Date('1518-10-13 00:36'), 1],
	[new Date('1518-05-21 00:35'), 1],
	[new Date('1518-07-24 00:07'), 1],
	[new Date('1518-03-20 00:00'), 0, 499],
	[new Date('1518-04-01 00:08'), 1],
	[new Date('1518-05-13 00:48'), 2],
	[new Date('1518-08-18 00:16'), 1],
	[new Date('1518-04-08 00:19'), 1],
	[new Date('1518-11-11 00:48'), 2],
	[new Date('1518-09-22 00:16'), 1],
	[new Date('1518-04-28 00:27'), 1],
	[new Date('1518-07-24 00:36'), 2],
	[new Date('1518-07-31 00:23'), 1],
	[new Date('1518-03-27 00:48'), 1],
	[new Date('1518-06-26 00:43'), 2],
	[new Date('1518-07-13 00:18'), 1],
	[new Date('1518-11-11 23:58'), 0, 2243],
	[new Date('1518-09-15 00:25'), 1],
	[new Date('1518-10-09 00:20'), 1],
	[new Date('1518-09-30 00:00'), 0, 2341],
	[new Date('1518-10-29 00:59'), 2],
	[new Date('1518-08-08 00:14'), 1],
	[new Date('1518-05-04 23:56'), 0, 1151],
	[new Date('1518-05-16 00:19'), 1],
	[new Date('1518-09-14 00:59'), 2],
	[new Date('1518-11-21 00:53'), 2],
	[new Date('1518-09-19 00:40'), 2],
	[new Date('1518-08-22 00:30'), 1],
	[new Date('1518-10-18 00:29'), 2],
	[new Date('1518-11-14 00:25'), 1],
	[new Date('1518-06-02 00:36'), 1],
	[new Date('1518-11-04 00:03'), 0, 3449],
	[new Date('1518-08-21 00:00'), 0, 2089],
	[new Date('1518-04-19 00:17'), 2],
	[new Date('1518-07-28 00:30'), 1],
	[new Date('1518-06-09 00:30'), 1],
	[new Date('1518-10-09 23:59'), 0, 1367],
	[new Date('1518-06-21 23:59'), 0, 631],
	[new Date('1518-10-31 00:51'), 1],
	[new Date('1518-10-29 00:04'), 0, 89],
	[new Date('1518-09-08 00:58'), 2],
	[new Date('1518-03-31 00:01'), 0, 3449],
	[new Date('1518-11-20 23:49'), 0, 947],
	[new Date('1518-09-15 00:50'), 2],
	[new Date('1518-09-01 00:48'), 2],
	[new Date('1518-11-14 23:56'), 0, 3119],
	[new Date('1518-04-17 00:45'), 2],
	[new Date('1518-08-26 00:02'), 1],
	[new Date('1518-03-25 00:00'), 0, 2791],
	[new Date('1518-06-21 00:00'), 0, 3019],
	[new Date('1518-08-07 00:10'), 1],
	[new Date('1518-09-26 00:24'), 1],
	[new Date('1518-10-08 00:24'), 2],
	[new Date('1518-08-15 23:59'), 0, 947],
	[new Date('1518-07-31 00:01'), 0, 89],
	[new Date('1518-04-22 00:26'), 2],
	[new Date('1518-08-17 00:03'), 0, 337],
	[new Date('1518-06-04 00:31'), 1],
	[new Date('1518-10-08 00:27'), 1],
	[new Date('1518-06-02 00:19'), 1],
	[new Date('1518-08-01 00:47'), 2],
	[new Date('1518-05-04 00:00'), 0, 1973],
	[new Date('1518-10-12 00:53'), 1],
	[new Date('1518-09-14 00:22'), 2],
	[new Date('1518-06-02 00:56'), 2],
	[new Date('1518-07-25 00:54'), 1],
	[new Date('1518-07-03 23:50'), 0, 2617],
	[new Date('1518-05-13 00:00'), 0, 1951],
	[new Date('1518-11-01 00:05'), 1],
	[new Date('1518-05-03 00:49'), 1],
	[new Date('1518-09-18 00:48'), 1],
	[new Date('1518-07-25 00:59'), 2],
	[new Date('1518-11-19 00:28'), 1],
	[new Date('1518-04-25 00:21'), 2],
	[new Date('1518-08-24 00:41'), 1],
	[new Date('1518-08-20 00:54'), 2],
	[new Date('1518-11-15 23:57'), 0, 3019],
	[new Date('1518-05-15 00:00'), 1],
	[new Date('1518-04-09 00:56'), 2],
	[new Date('1518-10-25 00:58'), 2],
	[new Date('1518-03-18 00:01'), 0, 89],
	[new Date('1518-08-05 00:10'), 2],
	[new Date('1518-09-02 00:40'), 2],
	[new Date('1518-07-05 00:35'), 1],
	[new Date('1518-08-06 00:25'), 1],
	[new Date('1518-11-07 23:50'), 0, 499],
	[new Date('1518-04-24 00:10'), 1],
	[new Date('1518-10-30 00:57'), 1],
	[new Date('1518-07-09 00:23'), 1],
	[new Date('1518-06-26 00:05'), 1],
	[new Date('1518-08-04 00:57'), 2],
	[new Date('1518-05-06 00:01'), 1],
	[new Date('1518-10-12 00:00'), 0, 3449],
	[new Date('1518-06-06 00:47'), 2],
	[new Date('1518-09-15 00:42'), 2],
	[new Date('1518-06-14 00:11'), 2],
	[new Date('1518-05-20 00:33'), 2],
	[new Date('1518-07-29 00:03'), 1],
	[new Date('1518-07-22 00:04'), 0, 3449],
	[new Date('1518-08-31 00:37'), 2],
	[new Date('1518-04-06 00:06'), 1],
	[new Date('1518-09-27 00:56'), 2],
	[new Date('1518-07-09 00:11'), 2],
	[new Date('1518-07-09 00:06'), 1],
	[new Date('1518-03-22 00:26'), 2],
	[new Date('1518-10-16 00:24'), 1],
	[new Date('1518-04-13 00:57'), 2],
	[new Date('1518-03-31 00:42'), 2],
	[new Date('1518-04-02 00:52'), 1],
	[new Date('1518-07-19 00:17'), 1],
	[new Date('1518-09-03 00:33'), 1],
	[new Date('1518-09-12 00:35'), 1],
	[new Date('1518-06-18 00:55'), 2],
	[new Date('1518-05-15 00:54'), 2],
	[new Date('1518-05-01 00:33'), 2],
	[new Date('1518-06-22 00:42'), 1],
	[new Date('1518-09-01 00:55'), 2],
	[new Date('1518-10-17 23:58'), 0, 439],
	[new Date('1518-04-11 00:46'), 2],
	[new Date('1518-03-20 00:08'), 1],
	[new Date('1518-09-04 00:34'), 1],
	[new Date('1518-04-11 00:20'), 2],
	[new Date('1518-04-18 00:41'), 2],
	[new Date('1518-09-19 00:49'), 1],
	[new Date('1518-06-15 00:39'), 1],
	[new Date('1518-06-22 00:48'), 2],
	[new Date('1518-03-26 23:59'), 0, 2617],
	[new Date('1518-08-29 00:44'), 2],
	[new Date('1518-06-01 00:04'), 0, 3449],
	[new Date('1518-06-17 00:03'), 0, 89],
	[new Date('1518-07-07 00:35'), 2],
	[new Date('1518-07-06 00:05'), 1],
	[new Date('1518-03-26 00:47'), 2],
	[new Date('1518-09-20 00:09'), 1],
	[new Date('1518-08-29 00:39'), 1],
	[new Date('1518-09-27 00:52'), 1],
	[new Date('1518-04-09 00:15'), 1],
	[new Date('1518-11-08 00:27'), 2],
	[new Date('1518-09-15 00:18'), 2],
	[new Date('1518-06-04 00:25'), 2],
	[new Date('1518-11-22 00:07'), 1],
	[new Date('1518-11-11 00:38'), 1],
	[new Date('1518-04-15 00:36'), 1],
	[new Date('1518-04-03 23:50'), 0, 809],
	[new Date('1518-07-18 00:42'), 1],
	[new Date('1518-03-29 23:58'), 0, 337],
	[new Date('1518-04-07 00:54'), 1],
	[new Date('1518-06-28 23:53'), 0, 89],
	[new Date('1518-08-04 00:29'), 1],
	[new Date('1518-05-08 00:47'), 1],
	[new Date('1518-11-02 00:23'), 1],
	[new Date('1518-05-02 00:15'), 1],
	[new Date('1518-05-27 23:58'), 0, 373],
	[new Date('1518-09-29 00:19'), 1],
	[new Date('1518-08-25 00:45'), 2],
	[new Date('1518-09-23 00:39'), 2],
	[new Date('1518-09-14 00:15'), 1],
	[new Date('1518-04-24 23:50'), 0, 2243],
	[new Date('1518-07-01 00:39'), 2],
	[new Date('1518-04-16 00:51'), 2],
	[new Date('1518-07-30 00:28'), 1],
	[new Date('1518-09-12 23:58'), 0, 1367],
	[new Date('1518-07-08 00:37'), 1],
	[new Date('1518-06-23 00:13'), 1],
	[new Date('1518-10-22 00:38'), 1],
	[new Date('1518-09-14 00:52'), 1],
	[new Date('1518-06-02 00:24'), 2],
	[new Date('1518-07-07 00:54'), 2],
	[new Date('1518-06-27 00:32'), 2],
	[new Date('1518-03-20 00:54'), 2],
	[new Date('1518-08-27 23:56'), 0, 3449],
	[new Date('1518-08-22 00:45'), 2],
	[new Date('1518-07-22 00:40'), 2],
	[new Date('1518-09-03 00:28'), 2],
	[new Date('1518-09-01 00:35'), 1],
	[new Date('1518-07-06 00:22'), 1],
	[new Date('1518-08-08 00:00'), 0, 89],
	[new Date('1518-07-17 00:50'), 1],
	[new Date('1518-10-04 00:56'), 2],
	[new Date('1518-05-10 00:19'), 1],
	[new Date('1518-07-14 00:02'), 0, 89],
	[new Date('1518-10-24 23:58'), 0, 2791],
	[new Date('1518-04-14 00:58'), 2],
	[new Date('1518-06-08 00:47'), 2],
	[new Date('1518-03-27 00:38'), 2],
	[new Date('1518-11-22 00:03'), 0, 2243],
	[new Date('1518-03-31 00:22'), 1],
	[new Date('1518-11-13 23:58'), 0, 337],
	[new Date('1518-04-18 00:22'), 1],
	[new Date('1518-04-10 00:58'), 2],
	[new Date('1518-11-02 00:53'), 2],
	[new Date('1518-10-30 00:40'), 2],
	[new Date('1518-07-05 23:50'), 0, 3119],
	[new Date('1518-08-12 00:36'), 2],
	[new Date('1518-04-18 23:52'), 0, 2617],
	[new Date('1518-09-17 00:04'), 0, 2089],
	[new Date('1518-05-31 00:03'), 0, 2617],
	[new Date('1518-10-18 00:10'), 1],
	[new Date('1518-04-05 00:43'), 1],
	[new Date('1518-10-11 00:32'), 2],
	[new Date('1518-04-10 00:45'), 1],
	[new Date('1518-05-04 00:20'), 2],
	[new Date('1518-06-11 00:25'), 1],
	[new Date('1518-08-13 00:58'), 2],
	[new Date('1518-10-01 00:06'), 1],
	[new Date('1518-07-30 00:48'), 2],
	[new Date('1518-07-12 00:54'), 2],
	[new Date('1518-04-28 00:01'), 0, 787],
	[new Date('1518-11-16 00:31'), 1],
	[new Date('1518-08-08 00:28'), 2],
	[new Date('1518-11-19 00:57'), 1],
	[new Date('1518-06-07 00:36'), 2],
	[new Date('1518-03-28 00:45'), 2],
	[new Date('1518-05-13 00:46'), 1],
	[new Date('1518-09-22 00:18'), 2],
	[new Date('1518-04-29 23:57'), 0, 1151],
	[new Date('1518-08-15 00:57'), 2],
	[new Date('1518-06-25 00:29'), 1],
	[new Date('1518-09-02 23:59'), 0, 1973],
	[new Date('1518-10-28 00:26'), 1],
	[new Date('1518-04-19 00:05'), 1],
	[new Date('1518-04-25 00:49'), 2],
	[new Date('1518-10-08 23:48'), 0, 1951],
	[new Date('1518-07-18 00:01'), 2],
	[new Date('1518-09-30 00:45'), 2],
	[new Date('1518-09-15 00:30'), 2],
	[new Date('1518-08-13 00:42'), 2],
	[new Date('1518-05-16 00:03'), 0, 499],
	[new Date('1518-08-08 23:58'), 0, 2617],
	[new Date('1518-05-25 00:26'), 1],
	[new Date('1518-05-17 00:26'), 1],
	[new Date('1518-04-23 00:41'), 2],
	[new Date('1518-10-23 23:53'), 0, 1367],
	[new Date('1518-07-25 23:57'), 0, 337],
	[new Date('1518-09-27 23:57'), 0, 809],
	[new Date('1518-11-11 00:54'), 1],
	[new Date('1518-09-07 23:59'), 0, 499],
	[new Date('1518-05-16 23:53'), 0, 1973],
	[new Date('1518-10-14 00:58'), 2],
	[new Date('1518-05-17 00:00'), 1],
	[new Date('1518-09-09 23:56'), 0, 3119],
	[new Date('1518-04-28 00:30'), 2],
	[new Date('1518-03-30 00:17'), 1],
	[new Date('1518-08-21 00:23'), 2],
	[new Date('1518-04-06 00:55'), 2],
	[new Date('1518-05-08 00:59'), 2],
	[new Date('1518-07-11 00:16'), 2],
	[new Date('1518-06-09 00:04'), 0, 2341],
	[new Date('1518-10-24 00:46'), 1],
	[new Date('1518-07-18 00:44'), 2],
	[new Date('1518-09-05 23:57'), 0, 631],
	[new Date('1518-04-13 00:37'), 2],
	[new Date('1518-03-18 00:59'), 2],
	[new Date('1518-07-23 00:40'), 1],
	[new Date('1518-07-18 00:58'), 2],
	[new Date('1518-11-03 00:33'), 1],
	[new Date('1518-04-22 00:10'), 1],
	[new Date('1518-07-05 00:01'), 0, 89],
	[new Date('1518-07-15 00:18'), 1],
	[new Date('1518-04-16 00:00'), 1],
	[new Date('1518-10-15 00:36'), 1],
	[new Date('1518-09-09 00:57'), 2],
	[new Date('1518-04-26 00:00'), 0, 787],
	[new Date('1518-10-21 23:57'), 0, 3449],
	[new Date('1518-06-19 00:50'), 2],
	[new Date('1518-03-18 00:35'), 1],
	[new Date('1518-10-26 00:04'), 0, 787],
	[new Date('1518-10-09 00:09'), 2],
	[new Date('1518-04-28 00:40'), 1],
	[new Date('1518-11-03 00:03'), 0, 2341],
	[new Date('1518-08-03 00:53'), 1],
	[new Date('1518-10-29 00:47'), 2],
	[new Date('1518-09-30 00:15'), 1],
	[new Date('1518-05-21 00:53'), 2],
	[new Date('1518-05-03 00:05'), 1],
	[new Date('1518-06-05 00:59'), 2],
	[new Date('1518-08-04 00:04'), 0, 1367],
	[new Date('1518-04-15 00:57'), 2],
	[new Date('1518-05-02 00:54'), 2],
	[new Date('1518-11-06 00:47'), 2],
	[new Date('1518-05-18 00:49'), 2],
	[new Date('1518-03-29 00:03'), 0, 2341],
	[new Date('1518-09-27 00:00'), 0, 1973],
	[new Date('1518-06-20 00:58'), 2],
	[new Date('1518-06-23 00:39'), 2],
	[new Date('1518-07-25 00:41'), 2],
	[new Date('1518-03-26 00:03'), 0, 337],
	[new Date('1518-10-02 00:10'), 1],
	[new Date('1518-08-01 00:20'), 1],
	[new Date('1518-06-11 00:51'), 1],
	[new Date('1518-06-23 00:00'), 0, 1951],
	[new Date('1518-09-27 00:45'), 2],
	[new Date('1518-09-05 00:53'), 1],
	[new Date('1518-11-20 00:42'), 2],
	[new Date('1518-10-31 23:48'), 0, 2617],
	[new Date('1518-10-07 00:50'), 1],
	[new Date('1518-09-05 00:55'), 2],
	[new Date('1518-08-29 00:53'), 2],
	[new Date('1518-09-16 00:59'), 2],
	[new Date('1518-07-14 00:19'), 2],
	[new Date('1518-09-22 00:58'), 2],
	[new Date('1518-06-23 00:43'), 1],
	[new Date('1518-07-15 00:15'), 2],
	[new Date('1518-07-08 00:02'), 0, 89],
	[new Date('1518-07-11 00:48'), 2],
	[new Date('1518-09-25 00:59'), 2],
	[new Date('1518-05-23 00:36'), 1],
	[new Date('1518-03-22 00:04'), 0, 2341],
	[new Date('1518-09-06 00:41'), 2],
	[new Date('1518-06-25 00:02'), 0, 947],
	[new Date('1518-05-16 00:54'), 2],
	[new Date('1518-06-23 23:58'), 0, 2791],
	[new Date('1518-05-07 00:45'), 1],
	[new Date('1518-07-14 23:50'), 0, 1973],
	[new Date('1518-04-01 00:28'), 2],
	[new Date('1518-10-11 00:41'), 2],
	[new Date('1518-06-19 00:00'), 0, 3449],
	[new Date('1518-07-24 23:49'), 0, 89],
	[new Date('1518-05-30 00:58'), 2],
	[new Date('1518-10-25 00:43'), 2],
	[new Date('1518-05-04 00:07'), 1],
	[new Date('1518-10-05 00:00'), 0, 809],
	[new Date('1518-08-01 00:04'), 0, 89],
	[new Date('1518-07-30 00:00'), 0, 89],
	[new Date('1518-07-17 00:00'), 0, 499],
	[new Date('1518-07-06 00:38'), 2],
	[new Date('1518-06-26 00:51'), 2],
	[new Date('1518-09-28 00:27'), 1],
	[new Date('1518-06-09 00:31'), 2],
	[new Date('1518-10-22 00:43'), 2],
	[new Date('1518-10-31 00:41'), 1],
	[new Date('1518-06-14 00:04'), 1],
	[new Date('1518-07-19 00:38'), 2],
	[new Date('1518-05-22 00:38'), 1],
	[new Date('1518-11-10 00:29'), 2],
	[new Date('1518-10-23 00:05'), 1],
	[new Date('1518-06-16 00:38'), 2],
	[new Date('1518-04-24 00:47'), 2],
	[new Date('1518-07-23 00:03'), 0, 631],
	[new Date('1518-06-08 00:40'), 1],
	[new Date('1518-05-08 00:53'), 2],
	[new Date('1518-09-04 00:38'), 2],
	[new Date('1518-08-29 00:50'), 1],
	[new Date('1518-11-10 00:15'), 1],
	[new Date('1518-11-23 00:54'), 2],
	[new Date('1518-11-05 00:36'), 1],
	[new Date('1518-10-04 00:02'), 0, 2341],
	[new Date('1518-04-06 00:00'), 0, 1367],
	[new Date('1518-07-17 23:46'), 0, 2089],
	[new Date('1518-06-15 00:44'), 2],
	[new Date('1518-04-10 00:17'), 2],
	[new Date('1518-08-31 00:32'), 1],
	[new Date('1518-05-03 00:30'), 2],
	[new Date('1518-09-11 00:23'), 1],
	[new Date('1518-06-12 00:54'), 2],
	[new Date('1518-11-08 23:50'), 0, 1481],
	[new Date('1518-08-31 00:59'), 2],
	[new Date('1518-09-25 00:40'), 1],
	[new Date('1518-09-23 00:11'), 2],
	[new Date('1518-06-06 00:57'), 2],
	[new Date('1518-05-03 00:18'), 2],
	[new Date('1518-09-22 00:24'), 1],
	[new Date('1518-09-06 00:50'), 1],
	[new Date('1518-05-01 00:46'), 1],
	[new Date('1518-05-07 00:46'), 2],
	[new Date('1518-10-21 00:51'), 2],
	[new Date('1518-05-08 00:34'), 2],
	[new Date('1518-08-25 23:53'), 0, 337],
	[new Date('1518-08-04 00:19'), 2],
	[new Date('1518-10-25 00:53'), 2],
	[new Date('1518-09-26 00:53'), 2],
	[new Date('1518-05-17 23:57'), 0, 2089],
	[new Date('1518-08-06 00:01'), 0, 631],
	[new Date('1518-07-04 00:43'), 2],
	[new Date('1518-06-22 00:57'), 1],
	[new Date('1518-05-17 00:01'), 2],
	[new Date('1518-05-14 00:19'), 2],
	[new Date('1518-05-25 23:56'), 0, 89],
	[new Date('1518-08-11 00:44'), 2],
	[new Date('1518-11-03 00:50'), 2],
	[new Date('1518-06-10 00:03'), 0, 631],
	[new Date('1518-06-11 00:42'), 2],
	[new Date('1518-07-09 00:03'), 0, 3119],
	[new Date('1518-04-02 00:34'), 1],
	[new Date('1518-08-20 00:00'), 0, 3449],
	[new Date('1518-06-13 00:00'), 0, 3019],
	[new Date('1518-07-17 00:57'), 2],
	[new Date('1518-03-23 00:37'), 2],
	[new Date('1518-07-08 00:50'), 2],
	[new Date('1518-09-04 00:30'), 2],
	[new Date('1518-05-25 00:35'), 2],
	[new Date('1518-07-28 00:21'), 1],
	[new Date('1518-09-04 00:56'), 1],
	[new Date('1518-06-19 00:11'), 1],
	[new Date('1518-07-03 00:00'), 1],
	[new Date('1518-06-17 23:56'), 0, 2341],
	[new Date('1518-04-28 00:14'), 1],
	[new Date('1518-11-04 00:57'), 2],
	[new Date('1518-11-04 00:11'), 1],
	[new Date('1518-09-15 00:41'), 1],
	[new Date('1518-07-23 23:59'), 0, 1481],
	[new Date('1518-11-06 23:58'), 0, 3119],
	[new Date('1518-10-31 00:22'), 1],
	[new Date('1518-04-04 00:59'), 2],
	[new Date('1518-08-31 00:50'), 1],
	[new Date('1518-11-23 00:03'), 0, 1481],
	[new Date('1518-09-08 23:56'), 0, 1973],
	[new Date('1518-04-13 00:55'), 1],
	[new Date('1518-09-21 00:01'), 0, 1973],
	[new Date('1518-05-02 23:46'), 0, 631],
	[new Date('1518-09-11 00:00'), 0, 2617],
	[new Date('1518-09-22 23:49'), 0, 2617],
	[new Date('1518-09-01 23:58'), 0, 2617],
	[new Date('1518-11-10 00:52'), 2],
	[new Date('1518-11-21 00:03'), 1],
	[new Date('1518-06-09 00:46'), 2],
	[new Date('1518-11-18 00:37'), 2],
	[new Date('1518-03-30 00:30'), 2],
	[new Date('1518-08-09 00:34'), 2],
	[new Date('1518-04-02 00:00'), 0, 2791],
	[new Date('1518-05-01 00:06'), 1],
	[new Date('1518-03-19 00:58'), 2],
	[new Date('1518-08-19 00:30'), 1],
	[new Date('1518-06-07 00:54'), 1],
	[new Date('1518-11-01 00:58'), 2],
	[new Date('1518-08-28 00:22'), 2],
	[new Date('1518-09-16 00:09'), 1],
	[new Date('1518-03-21 00:44'), 2],
	[new Date('1518-05-08 00:57'), 1],
	[new Date('1518-07-27 23:56'), 0, 809],
	[new Date('1518-05-19 00:53'), 1],
	[new Date('1518-10-12 00:37'), 1],
	[new Date('1518-09-24 00:51'), 2],
	[new Date('1518-11-22 00:09'), 2],
	[new Date('1518-09-13 00:23'), 2],
	[new Date('1518-09-05 00:02'), 0, 2341],
	[new Date('1518-08-08 00:53'), 2],
	[new Date('1518-07-22 00:12'), 1],
	[new Date('1518-11-16 00:59'), 2],
	[new Date('1518-05-21 00:02'), 0, 89],
	[new Date('1518-03-23 00:45'), 1],
	[new Date('1518-04-04 00:55'), 1],
	[new Date('1518-10-25 00:57'), 1],
	[new Date('1518-07-31 00:52'), 2],
	[new Date('1518-04-02 23:49'), 0, 947],
	[new Date('1518-04-18 00:17'), 2],
	[new Date('1518-10-08 00:08'), 1],
	[new Date('1518-05-06 00:23'), 1],
	[new Date('1518-11-09 00:04'), 1],
	[new Date('1518-09-01 00:52'), 1],
	[new Date('1518-08-14 00:00'), 0, 499],
	[new Date('1518-07-11 00:20'), 1],
	[new Date('1518-03-26 00:40'), 1],
	[new Date('1518-06-01 23:58'), 0, 337],
	[new Date('1518-07-26 00:07'), 1],
	[new Date('1518-04-13 00:25'), 1],
	[new Date('1518-09-26 00:03'), 0, 1973],
	[new Date('1518-06-07 00:56'), 2],
	[new Date('1518-06-21 00:22'), 1],
	[new Date('1518-11-12 00:55'), 2],
	[new Date('1518-08-21 23:56'), 0, 3449],
	[new Date('1518-04-07 00:03'), 0, 809],
	[new Date('1518-10-01 00:43'), 2],
	[new Date('1518-03-31 00:39'), 1],
	[new Date('1518-07-25 00:30'), 1],
	[new Date('1518-07-29 00:16'), 1],
	[new Date('1518-07-28 00:23'), 2],
	[new Date('1518-07-27 00:00'), 0, 2617],
	[new Date('1518-06-04 00:55'), 2],
	[new Date('1518-03-24 00:59'), 2],
	[new Date('1518-10-29 00:56'), 1],
	[new Date('1518-06-10 00:07'), 1],
	[new Date('1518-08-29 00:01'), 0, 3449],
	[new Date('1518-09-09 00:37'), 1],
	[new Date('1518-03-23 23:58'), 0, 787],
	[new Date('1518-03-21 00:01'), 0, 2089],
	[new Date('1518-03-24 00:56'), 1],
	[new Date('1518-07-07 00:40'), 1],
	[new Date('1518-10-24 00:03'), 1],
	[new Date('1518-05-01 00:50'), 2],
	[new Date('1518-11-14 00:52'), 2],
	[new Date('1518-05-19 00:22'), 1],
	[new Date('1518-05-24 00:03'), 0, 373],
	[new Date('1518-10-22 00:55'), 2],
	[new Date('1518-06-12 00:00'), 1],
	[new Date('1518-10-30 00:59'), 2],
	[new Date('1518-08-30 00:02'), 0, 2617],
	[new Date('1518-10-24 00:23'), 2],
	[new Date('1518-03-27 00:26'), 1],
	[new Date('1518-07-26 00:50'), 2],
	[new Date('1518-08-06 00:45'), 1],
	[new Date('1518-06-22 00:59'), 2],
	[new Date('1518-09-17 00:18'), 1],
	[new Date('1518-09-02 00:37'), 1],
	[new Date('1518-11-21 00:31'), 1],
	[new Date('1518-09-23 00:05'), 1],
	[new Date('1518-10-24 00:47'), 2],
	[new Date('1518-06-06 00:45'), 1],
	[new Date('1518-05-09 00:54'), 2],
	[new Date('1518-07-13 00:53'), 2],
	[new Date('1518-06-15 23:50'), 0, 3449],
	[new Date('1518-08-03 00:46'), 2],
	[new Date('1518-06-16 00:01'), 1],
	[new Date('1518-07-25 00:20'), 2],
	[new Date('1518-09-11 00:56'), 2],
	[new Date('1518-10-04 00:47'), 1],
	[new Date('1518-09-19 00:01'), 0, 1481],
	[new Date('1518-11-08 00:46'), 2],
	[new Date('1518-06-09 00:36'), 1],
	[new Date('1518-08-24 00:01'), 1],
	[new Date('1518-08-21 00:56'), 2],
	[new Date('1518-11-13 00:07'), 1],
	[new Date('1518-07-14 00:51'), 2],
	[new Date('1518-10-15 00:41'), 2],
	[new Date('1518-07-04 00:02'), 1],
	[new Date('1518-06-06 00:39'), 2],
	[new Date('1518-06-20 00:06'), 1],
	[new Date('1518-06-08 00:15'), 1],
	[new Date('1518-07-15 00:37'), 2],
	[new Date('1518-06-29 00:42'), 2],
	[new Date('1518-04-04 00:51'), 2],
	[new Date('1518-03-24 00:41'), 2],
	[new Date('1518-09-21 23:56'), 0, 1481],
	[new Date('1518-11-18 00:01'), 1],
	[new Date('1518-07-19 00:44'), 1],
	[new Date('1518-08-14 00:58'), 2],
	[new Date('1518-07-11 00:10'), 1],
	[new Date('1518-08-19 00:04'), 0, 2341],
	[new Date('1518-08-13 00:56'), 1],
	[new Date('1518-08-11 00:00'), 0, 3019],
	[new Date('1518-06-13 23:46'), 0, 499],
	[new Date('1518-04-17 00:04'), 0, 3449],
	[new Date('1518-11-20 00:17'), 1],
	[new Date('1518-05-13 23:59'), 0, 1367],
	[new Date('1518-09-20 00:42'), 2],
	[new Date('1518-11-20 00:55'), 2],
	[new Date('1518-10-09 00:44'), 2],
	[new Date('1518-05-13 00:38'), 2],
	[new Date('1518-06-30 00:54'), 2],
	[new Date('1518-11-13 00:23'), 2],
	[new Date('1518-03-24 00:06'), 1],
	[new Date('1518-05-13 00:12'), 1],
	[new Date('1518-05-09 00:35'), 1],
	[new Date('1518-03-26 00:52'), 1],
	[new Date('1518-06-25 00:07'), 1],
	[new Date('1518-11-03 00:55'), 1],
	[new Date('1518-06-15 00:01'), 0, 3449],
	[new Date('1518-05-18 00:44'), 1],
	[new Date('1518-04-19 00:38'), 2],
	[new Date('1518-11-07 00:26'), 1],
	[new Date('1518-09-18 00:45'), 2],
	[new Date('1518-05-14 00:16'), 1],
	[new Date('1518-11-12 00:44'), 1],
	[new Date('1518-09-19 00:38'), 1],
	[new Date('1518-08-03 00:56'), 2],
	[new Date('1518-04-27 00:44'), 1],
	[new Date('1518-04-22 00:00'), 0, 947],
	[new Date('1518-08-03 00:03'), 0, 2243],
	[new Date('1518-10-30 00:22'), 1],
	[new Date('1518-03-25 00:58'), 2],
	[new Date('1518-08-28 00:18'), 1],
	[new Date('1518-05-10 00:43'), 2],
	[new Date('1518-07-07 00:27'), 1],
	[new Date('1518-06-26 00:18'), 2],
	[new Date('1518-03-21 00:58'), 2],
	[new Date('1518-07-10 00:48'), 1],
	[new Date('1518-10-31 00:44'), 2],
	[new Date('1518-04-23 00:19'), 1],
	[new Date('1518-09-20 00:04'), 0, 499],
	[new Date('1518-10-08 00:41'), 2],
	[new Date('1518-08-05 00:45'), 1],
	[new Date('1518-04-25 00:35'), 1],
	[new Date('1518-09-17 00:57'), 2],
	[new Date('1518-10-19 00:09'), 1],
	[new Date('1518-09-06 23:50'), 0, 2791],
	[new Date('1518-11-20 00:47'), 1],
	[new Date('1518-07-18 23:58'), 0, 499],
	[new Date('1518-08-21 00:12'), 1],
	[new Date('1518-09-13 00:39'), 2],
	[new Date('1518-11-07 00:23'), 2],
	[new Date('1518-08-23 23:47'), 0, 1481],
	[new Date('1518-10-31 00:00'), 0, 89],
	[new Date('1518-07-29 00:13'), 2],
	[new Date('1518-04-20 23:46'), 0, 1481],
	[new Date('1518-03-22 00:18'), 1],
	[new Date('1518-11-06 00:03'), 0, 337],
	[new Date('1518-07-27 00:08'), 1],
	[new Date('1518-05-12 00:35'), 1],
	[new Date('1518-05-18 00:20'), 1],
	[new Date('1518-04-14 00:41'), 1],
	[new Date('1518-08-06 00:33'), 2],
	[new Date('1518-04-07 00:42'), 2],
	[new Date('1518-09-18 00:58'), 2],
	[new Date('1518-03-27 00:35'), 1],
	[new Date('1518-08-30 00:22'), 1],
	[new Date('1518-07-18 00:56'), 1],
	[new Date('1518-05-01 23:56'), 0, 2791],
	[new Date('1518-06-27 23:46'), 0, 1973],
	[new Date('1518-06-26 00:49'), 1],
	[new Date('1518-06-21 00:41'), 2],
	[new Date('1518-05-06 00:03'), 2],
	[new Date('1518-07-04 00:14'), 2],
	[new Date('1518-04-07 23:56'), 0, 1951],
	[new Date('1518-07-27 00:54'), 2],
	[new Date('1518-06-26 00:37'), 1],
	[new Date('1518-06-30 00:52'), 1],
	[new Date('1518-10-27 00:50'), 2],
	[new Date('1518-10-23 00:50'), 2],
	[new Date('1518-06-30 00:29'), 2],
	[new Date('1518-05-07 00:51'), 1],
	[new Date('1518-10-24 00:35'), 1],
	[new Date('1518-09-03 00:12'), 1],
	[new Date('1518-08-10 00:32'), 1],
	[new Date('1518-08-07 00:33'), 1],
	[new Date('1518-10-08 00:22'), 1],
	[new Date('1518-08-16 00:16'), 1],
	[new Date('1518-03-25 00:26'), 1],
	[new Date('1518-05-22 00:04'), 0, 3449],
	[new Date('1518-08-26 23:58'), 0, 787],
	[new Date('1518-05-26 00:55'), 2],
	[new Date('1518-09-15 00:13'), 1],
	[new Date('1518-09-06 00:38'), 1],
	[new Date('1518-04-07 00:37'), 1],
	[new Date('1518-06-28 00:59'), 2],
	[new Date('1518-05-07 23:47'), 0, 1367],
	[new Date('1518-03-21 00:54'), 1],
	[new Date('1518-05-09 00:49'), 2],
	[new Date('1518-08-01 23:57'), 0, 1481],
	[new Date('1518-05-08 00:02'), 1],
	[new Date('1518-08-02 00:57'), 2],
	[new Date('1518-04-21 00:05'), 1],
	[new Date('1518-09-14 00:01'), 0, 1951],
	[new Date('1518-04-05 00:56'), 2],
	[new Date('1518-06-27 00:49'), 1],
	[new Date('1518-07-15 00:01'), 1],
	[new Date('1518-08-31 23:59'), 0, 809],
	[new Date('1518-08-09 23:56'), 0, 809],
	[new Date('1518-04-11 00:19'), 1],
	[new Date('1518-11-14 00:49'), 1],
	[new Date('1518-04-19 23:57'), 0, 3067],
	[new Date('1518-03-28 00:12'), 1],
	[new Date('1518-10-27 00:02'), 0, 631],
	[new Date('1518-07-14 00:25'), 1],
	[new Date('1518-04-09 00:04'), 0, 2617],
	[new Date('1518-10-05 00:44'), 2],
	[new Date('1518-08-13 00:03'), 0, 439],
	[new Date('1518-08-23 00:13'), 1],
	[new Date('1518-10-08 00:09'), 2],
	[new Date('1518-08-26 00:54'), 2],
	[new Date('1518-09-18 00:38'), 1],
	[new Date('1518-07-11 23:59'), 0, 499],
	[new Date('1518-10-25 00:07'), 1],
	[new Date('1518-06-10 00:53'), 2],
	[new Date('1518-07-02 00:20'), 1],
	[new Date('1518-11-16 00:47'), 1],
	[new Date('1518-11-15 00:27'), 1],
	[new Date('1518-08-25 00:20'), 1],
	[new Date('1518-05-30 00:37'), 1],
	[new Date('1518-09-10 00:26'), 1],
	[new Date('1518-08-17 00:16'), 2],
	[new Date('1518-10-15 00:44'), 1],
	[new Date('1518-10-05 00:38'), 1],
	[new Date('1518-03-26 00:53'), 2],
	[new Date('1518-11-15 00:58'), 2],
	[new Date('1518-10-13 23:56'), 0, 947],
	[new Date('1518-10-14 23:58'), 0, 3449],
	[new Date('1518-05-10 23:59'), 0, 631],
	[new Date('1518-08-12 00:11'), 1],
	[new Date('1518-03-31 00:25'), 2],
	[new Date('1518-06-05 00:15'), 1],
	[new Date('1518-09-07 00:00'), 1],
	[new Date('1518-05-11 00:48'), 2],
	[new Date('1518-09-03 00:53'), 2],
	[new Date('1518-05-19 00:00'), 0, 439],
	[new Date('1518-04-13 23:59'), 0, 499],
	[new Date('1518-08-22 23:56'), 0, 1481],
	[new Date('1518-10-14 00:06'), 1],
	[new Date('1518-04-23 23:56'), 0, 947],
	[new Date('1518-04-15 00:44'), 2],
	[new Date('1518-09-12 00:50'), 2],
	[new Date('1518-08-13 00:30'), 1],
	[new Date('1518-07-28 23:52'), 0, 809],
	[new Date('1518-11-08 00:05'), 1],
	[new Date('1518-10-13 00:50'), 2],
	[new Date('1518-10-03 00:01'), 0, 2791],
	[new Date('1518-04-26 00:16'), 1],
	[new Date('1518-05-20 00:22'), 1],
	[new Date('1518-04-18 00:03'), 1],
	[new Date('1518-10-01 00:00'), 0, 787],
	[new Date('1518-09-25 00:42'), 2],
	[new Date('1518-06-07 00:26'), 1],
	[new Date('1518-09-04 00:00'), 0, 2341],
	[new Date('1518-07-10 00:33'), 2],
	[new Date('1518-10-18 00:49'), 1],
	[new Date('1518-06-28 00:04'), 1],
	[new Date('1518-11-21 00:18'), 2],
	[new Date('1518-07-23 00:57'), 2],
	[new Date('1518-08-20 00:35'), 1],
	[new Date('1518-06-19 00:25'), 2],
	[new Date('1518-04-21 00:14'), 2],
	[new Date('1518-06-26 23:59'), 0, 337],
	[new Date('1518-06-08 00:01'), 0, 499],
	[new Date('1518-07-12 00:33'), 1],
	[new Date('1518-09-09 00:41'), 2],
	[new Date('1518-04-17 23:49'), 0, 89],
	[new Date('1518-06-11 23:53'), 0, 2089],
	[new Date('1518-04-26 23:58'), 0, 3019],
	[new Date('1518-08-10 00:52'), 2],
	[new Date('1518-11-19 00:47'), 2],
	[new Date('1518-06-27 00:19'), 1],
	[new Date('1518-09-24 00:27'), 1],
	[new Date('1518-07-09 00:36'), 2],
	[new Date('1518-08-15 00:00'), 0, 337],
	[new Date('1518-05-18 00:32'), 2],
	[new Date('1518-07-25 00:01'), 1],
	[new Date('1518-06-05 00:00'), 0, 337],
	[new Date('1518-10-15 23:58'), 0, 439],
	[new Date('1518-09-04 00:57'), 2],
	[new Date('1518-04-10 00:37'), 2],
	[new Date('1518-07-04 00:48'), 1],
	[new Date('1518-09-13 00:20'), 1],
	[new Date('1518-11-01 00:34'), 1],
	[new Date('1518-06-29 23:54'), 0, 337],
	[new Date('1518-08-07 00:26'), 2],
	[new Date('1518-05-08 23:56'), 0, 2089],
	[new Date('1518-04-02 00:59'), 2],
	[new Date('1518-06-11 00:03'), 0, 1481],
	[new Date('1518-10-19 00:50'), 2],
	[new Date('1518-06-06 00:51'), 1],
	[new Date('1518-11-06 00:38'), 1],
	[new Date('1518-03-29 00:42'), 1],
	[new Date('1518-08-12 00:00'), 0, 1973],
	[new Date('1518-08-31 00:02'), 0, 439],
	[new Date('1518-08-09 00:09'), 1],
	[new Date('1518-04-03 00:44'), 2],
	[new Date('1518-05-07 00:00'), 0, 631],
	[new Date('1518-03-27 00:49'), 2],
	[new Date('1518-10-10 00:59'), 2],
	[new Date('1518-06-04 00:21'), 1],
	[new Date('1518-03-23 00:51'), 2],
	[new Date('1518-08-18 00:52'), 2],
	[new Date('1518-11-14 00:40'), 2],
	[new Date('1518-06-25 23:50'), 0, 631],
	[new Date('1518-10-05 00:20'), 2],
	[new Date('1518-05-11 00:32'), 1],
	[new Date('1518-06-19 00:42'), 1],
	[new Date('1518-09-12 00:01'), 0, 2617],
	[new Date('1518-08-30 00:24'), 2],
	[new Date('1518-10-15 00:47'), 2],
	[new Date('1518-05-17 00:55'), 2],
	[new Date('1518-04-07 00:56'), 2],
	[new Date('1518-10-16 00:43'), 2],
	[new Date('1518-08-17 23:57'), 0, 337],
	[new Date('1518-08-07 00:00'), 0, 2243],
	[new Date('1518-06-11 00:58'), 2],
	[new Date('1518-05-12 00:58'), 2],
	[new Date('1518-10-05 00:09'), 1],
	[new Date('1518-05-07 00:56'), 2],
	[new Date('1518-10-08 00:56'), 2],
	[new Date('1518-03-21 00:32'), 1],
	[new Date('1518-11-20 00:03'), 0, 1973],
	[new Date('1518-05-05 23:53'), 0, 787],
	[new Date('1518-08-11 00:41'), 1],
	[new Date('1518-05-30 00:02'), 0, 631],
	[new Date('1518-10-10 00:55'), 1],
	[new Date('1518-06-03 00:40'), 2],
	[new Date('1518-03-29 00:46'), 2],
	[new Date('1518-11-10 00:03'), 0, 787],
	[new Date('1518-08-21 00:44'), 1],
	[new Date('1518-06-10 00:34'), 1],
	[new Date('1518-06-20 00:03'), 0, 809],
	[new Date('1518-07-21 00:04'), 0, 373],
	[new Date('1518-05-06 00:47'), 2],
	[new Date('1518-04-10 00:35'), 1],
	[new Date('1518-04-05 00:37'), 2],
	[new Date('1518-06-19 00:32'), 2],
	[new Date('1518-04-04 00:22'), 2],
	[new Date('1518-06-30 00:04'), 1],
	[new Date('1518-04-25 00:05'), 1],
	[new Date('1518-09-15 23:57'), 0, 2243],
	[new Date('1518-07-10 00:10'), 1],
	[new Date('1518-10-21 00:02'), 1],
	[new Date('1518-10-20 00:01'), 0, 1151],
	[new Date('1518-03-27 00:31'), 2],
	[new Date('1518-04-22 23:59'), 0, 1367],
	[new Date('1518-11-09 00:37'), 2],
	[new Date('1518-10-11 00:35'), 1],
	[new Date('1518-10-28 00:42'), 2],
	[new Date('1518-11-21 00:04'), 2],
	[new Date('1518-08-15 00:13'), 1],
	[new Date('1518-10-13 00:04'), 0, 1973],
	[new Date('1518-04-09 00:47'), 1],
	[new Date('1518-11-17 00:37'), 1],
	[new Date('1518-03-31 23:58'), 0, 499],
	[new Date('1518-05-10 00:03'), 0, 3449],
	[new Date('1518-11-21 00:07'), 1],
	[new Date('1518-09-04 00:18'), 1],
	[new Date('1518-09-28 00:51'), 1],
	[new Date('1518-05-19 23:58'), 0, 2089],
	[new Date('1518-04-09 23:51'), 0, 809],
	[new Date('1518-07-28 00:53'), 2],
	[new Date('1518-10-06 00:16'), 1],
	[new Date('1518-03-23 00:25'), 1],
	[new Date('1518-07-01 00:29'), 1],
	[new Date('1518-04-05 00:10'), 1],
	[new Date('1518-08-02 00:43'), 1],
	[new Date('1518-06-24 00:14'), 1],
	[new Date('1518-04-09 00:26'), 2],
	[new Date('1518-06-29 00:05'), 1],
	[new Date('1518-06-01 00:35'), 1],
	[new Date('1518-06-17 00:57'), 2],
	[new Date('1518-09-13 00:30'), 1],
	[new Date('1518-09-15 00:00'), 0, 337],
	[new Date('1518-05-19 00:39'), 2],
	[new Date('1518-05-09 00:52'), 1],
	[new Date('1518-10-17 00:04'), 0, 1151],
	[new Date('1518-10-06 23:57'), 0, 809],
	[new Date('1518-08-04 00:15'), 1],
	[new Date('1518-11-19 00:00'), 0, 2791],
	[new Date('1518-04-03 00:05'), 1],
	[new Date('1518-08-17 00:52'), 2],
	[new Date('1518-04-19 00:21'), 1],
	[new Date('1518-10-18 00:51'), 2],
	[new Date('1518-10-11 00:02'), 0, 1951],
	[new Date('1518-06-06 00:02'), 0, 2791],
	[new Date('1518-10-07 00:52'), 2],
	[new Date('1518-11-08 00:35'), 1],
	[new Date('1518-09-23 00:14'), 1],
	[new Date('1518-03-23 00:04'), 0, 1481],
	[new Date('1518-06-19 00:29'), 1],
	[new Date('1518-05-14 23:47'), 0, 947],
	[new Date('1518-09-06 00:57'), 2],
	[new Date('1518-10-03 00:14'), 1],
	[new Date('1518-06-04 00:00'), 0, 787],
	[new Date('1518-10-05 23:58'), 0, 787],
	[new Date('1518-09-11 00:39'), 1],
	[new Date('1518-04-26 00:56'), 2]
];

var log2 = [
	[new Date('1518-11-01 00:00'), 0, 10 ],
	[new Date('1518-11-01 00:05'), 1],
	[new Date('1518-11-01 00:25'), 2],
	[new Date('1518-11-01 00:30'), 1],
	[new Date('1518-11-01 00:55'), 2],
	[new Date('1518-11-01 23:58'), 0, 99 ],
	[new Date('1518-11-02 00:40'), 1],
	[new Date('1518-11-02 00:50'), 2],
	[new Date('1518-11-03 00:05'), 0, 10 ],
	[new Date('1518-11-03 00:24'), 1],
	[new Date('1518-11-03 00:29'), 2],
	[new Date('1518-11-04 00:02'), 0, 99 ],
	[new Date('1518-11-04 00:36'), 1],
	[new Date('1518-11-04 00:46'), 2],
	[new Date('1518-11-05 00:03'), 0, 99 ],
	[new Date('1518-11-05 00:45'), 1],
	[new Date('1518-11-05 00:55'), 2],
];

var sort_by = function(a, b) {
	return a[0] - b[0];
};

log.sort(sort_by);
log2.sort(sort_by);

go(log);