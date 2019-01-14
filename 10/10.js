var ctx;
var canvas;

function Star(x, y, vx, vy) {
	this.x = x;
	this.y = y;
	this.vx = vx;
	this.vy = vy;
}

//var T = 10946;
//var T = 10943;
var T = 10945;

function scale(v) {
	v = (v - 100) / 200;
	//v = (v + 55000 / 110000);
	var w = canvas.width;
	var h = canvas.height;
	if (w < h)
		return v * w;
	else
		return v * h;
}

Star.prototype.draw = function() {
	var x = this.x + this.vx * T;
	var y = this.y + this.vy * T;
	ctx.fillRect(scale(x), scale(y), 1, 1);
};

window.addEventListener('load', function() {
	// MAIN or ALT
	var stars = MAIN;
	//
	canvas = document.getElementById('canvas');
	ctx = canvas.getContext('2d');
	function resize() {
		canvas.width = window.innerWidth - 20;
		canvas.height = window.innerWidth - 20;
	}
	window.addEventListener('resize', resize);
	var run = false;
	window.addEventListener('keydown', function(e) {
		if (e.keyCode == 80)
			run = ! run;
	});
	resize();
	var lastT = 0;
	function tick(t) {
		var dt = (t - lastT) / 5000;
		lastT = t;
		if (run) {
			T += dt;
		}
		ctx.clearRect(0, 0, canvas.width, canvas.height);
		ctx.fillStyle = 'rgb(255, 255, 255)';
		for (var i in stars) {
			stars[i].draw(t);
		}
		window.requestAnimationFrame(tick);
	};
	tick(0);
});
