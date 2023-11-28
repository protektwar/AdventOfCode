var ctx = $("canvas")[0].getContext("2d");
var W = 500;
var H = 500;

var point = { x: W / 2, y: H / 2 };
var triangle = randomTriangle();

$("canvas").click(function(evt) {
    point.x = evt.pageX - $(this).offset().left;
    point.y = evt.pageY - $(this).offset().top;
    test();
});

$("canvas").dblclick(function(evt) {
    triangle = randomTriangle();
    test();
});

test();

function test() {
    var result = ptInTriangle(point, triangle.a, triangle.b, triangle.c);
    
    var info = "point = (" + point.x + "," + point.y + ")\n";
    info += "triangle.a = (" + triangle.a.x + "," + triangle.a.y + ")\n";
    info += "triangle.b = (" + triangle.b.x + "," + triangle.b.y + ")\n";
    info += "triangle.c = (" + triangle.c.x + "," + triangle.c.y + ")\n";
    info += "result = " + (result ? "true" : "false");

    $("#result").text(info);
    render();
}

function ptInTriangle(p, p0, p1, p2) {
    var A = 1/2 * (-p1.y * p2.x + p0.y * (-p1.x + p2.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y);
    var sign = A < 0 ? -1 : 1;
    var s = (p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y) * sign;
    var t = (p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y) * sign;
    
    return s > 0 && t > 0 && (s + t) < 2 * A * sign;
}

function render() {
    ctx.fillStyle = "#CCC";
    ctx.fillRect(0, 0, 500, 500);
    drawTriangle(triangle.a, triangle.b, triangle.c);
    drawPoint(point);
}

function drawTriangle(p0, p1, p2) {
    ctx.fillStyle = "#999";
    ctx.beginPath();
    ctx.moveTo(p0.x, p0.y);
    ctx.lineTo(p1.x, p1.y);
    ctx.lineTo(p2.x, p2.y);
    ctx.closePath();
    ctx.fill();
    ctx.fillStyle = "#000";
    ctx.font = "12px monospace";
    ctx.fillText("1", p0.x, p0.y);
    ctx.fillText("2", p1.x, p1.y);
    ctx.fillText("3", p2.x, p2.y);
}

function drawPoint(p) {
    ctx.fillStyle = "#F00";
    ctx.beginPath();
    ctx.arc(p.x, p.y, 5, 0, 2 * Math.PI);
    ctx.fill();
}

function rand(min, max) {
	return Math.floor(Math.random() * (max - min + 1)) + min;
}

function randomTriangle() {
    return {
        a: { x: rand(0, W), y: rand(0, H) },
        b: { x: rand(0, W), y: rand(0, H) },
        c: { x: rand(0, W), y: rand(0, H) }
    };
}

<script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
<pre>Click: place the point.
Double click: random triangle.</pre>
<pre id="result"></pre>
<canvas width="500" height="500"></canvas>
