function triangleContains(ax, ay, bx, by, cx, cy, x, y) {

    let det = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax)
    
    return  det * ((bx - ax) * (y - ay) - (by - ay) * (x - ax)) > 0 &&
            det * ((cx - bx) * (y - by) - (cy - by) * (x - bx)) > 0 &&
            det * ((ax - cx) * (y - cy) - (ay - cy) * (x - cx)) > 0 

}






let width = 500, height = 500

// clockwise
let triangle1 = {

    A : { x: 10, y: -10 },
    C : { x: 20, y: 100 },
    B : { x: -90, y: 10 },
    
    color: '#f00',

}

// counter clockwise
let triangle2 = {

    A : { x: 20, y: -60 },
    B : { x: 90, y: 20 },
    C : { x: 20, y: 60 },

    color: '#00f',
    
}


let scale = 2
let mouse = { x: 0, y: 0 }






// DRAW >

let wrapper = document.querySelector('div.wrapper')

wrapper.onmousemove = ({ layerX:x, layerY:y }) => {
    
    x -= width / 2
    y -= height / 2
    x /= scale
    y /= scale
    
    mouse.x = x
    mouse.y = y
    
    drawInteractive()

}

function drawArrow(ctx, A, B) {

    let v = normalize(sub(B, A), 3)
    let I = center(A, B)
    
    let p
    
    p = add(I, rotate(v, 90), v)
    ctx.moveTo(p.x, p.y)
    ctx.lineTo(I.x, I .y)
    p = add(I, rotate(v, -90), v)
    ctx.lineTo(p.x, p.y)

}

function drawTriangle(ctx, { A, B, C, color }) {

    ctx.beginPath()
    ctx.moveTo(A.x, A.y)
    ctx.lineTo(B.x, B.y)
    ctx.lineTo(C.x, C.y)
    ctx.closePath()
    
    ctx.fillStyle = color + '6'
    ctx.strokeStyle = color
    ctx.fill()
    
    drawArrow(ctx, A, B)
    drawArrow(ctx, B, C)
    drawArrow(ctx, C, A)
    
    ctx.stroke()

}

function contains({ A, B, C }, P) {

    return triangleContains(A.x, A.y, B.x, B.y, C.x, C.y, P.x, P.y)

}

function resetCanvas(canvas) {

    canvas.width = width
    canvas.height = height
    
    let ctx = canvas.getContext('2d')

    ctx.resetTransform()
    ctx.clearRect(0, 0, width, height)
    ctx.setTransform(scale, 0, 0, scale, width/2, height/2)
    
}

function drawDots() {

    let canvas = document.querySelector('canvas#dots')
    let ctx = canvas.getContext('2d')

    resetCanvas(canvas)
    
    let count = 1000

    for (let i = 0; i < count; i++) {

        let x = width * (Math.random() - .5)
        let y = width * (Math.random() - .5)
        
        ctx.beginPath()
        ctx.ellipse(x, y, 1, 1, 0, 0, 2 * Math.PI)
        
        if (contains(triangle1, { x, y })) {
        
            ctx.fillStyle = '#f00'
        
        } else if (contains(triangle2, { x, y })) {
        
            ctx.fillStyle = '#00f'
        
        } else {
        
            ctx.fillStyle = '#0003'
        
        }

        
        ctx.fill()
        
    }
    
}

function drawInteractive() {

    let canvas = document.querySelector('canvas#interactive')
    let ctx = canvas.getContext('2d')

    resetCanvas(canvas)
    
    ctx.beginPath()
    ctx.moveTo(0, -height/2)
    ctx.lineTo(0, height/2)
    ctx.moveTo(-width/2, 0)
    ctx.lineTo(width/2, 0)
    ctx.strokeStyle = '#0003'
    ctx.stroke()
    
    drawTriangle(ctx, triangle1)
    drawTriangle(ctx, triangle2)
    
    ctx.beginPath()
    ctx.ellipse(mouse.x, mouse.y, 4, 4, 0, 0, 2 * Math.PI)
    
    if (contains(triangle1, mouse)) {
    
        ctx.fillStyle = triangle1.color + 'a'
        ctx.fill()
        
    } else if (contains(triangle2, mouse)) {
    
        ctx.fillStyle = triangle2.color + 'a'
        ctx.fill()
        
    } else {
    
        ctx.strokeStyle = 'black'
        ctx.stroke()
        
    }
    
}

drawDots()
drawInteractive()










// trigo

function add(...points) {
    
    let x = 0, y = 0
    
    for (let point of points) {
    
        x += point.x
        y += point.y
    
    }
    
    return { x, y }

}

function center(...points) {
    
    let x = 0, y = 0
    
    for (let point of points) {
    
        x += point.x
        y += point.y
    
    }
    
    x /= points.length
    y /= points.length
    
    return { x, y }

}

function sub(A, B) {

    let x = A.x - B.x
    let y = A.y - B.y
    
    return { x, y }

}

function normalize({ x, y }, length = 10) {

    let r = length / Math.sqrt(x * x + y * y)
    
    x *= r
    y *= r
    
    return { x, y }

}

function rotate({ x, y }, angle = 90) {

    let length = Math.sqrt(x * x + y * y)
    
    angle *= Math.PI / 180
    angle += Math.atan2(y, x)
    
    x = length * Math.cos(angle)
    y = length * Math.sin(angle)
    
    return { x, y }

}

* {
    margin: 0;
}

html {
    font-family: monospace;
}

body {
    padding: 32px;
}

span.red {
    color: #f00;
}

span.blue {
    color: #00f;
}

canvas {
    position: absolute;
    border: solid 1px #ddd;
}

<p><span class="red">red triangle</span> is clockwise</p>
<p><span class="blue">blue triangle</span> is couter clockwise</p>
<br>
<div class="wrapper">
    <canvas id="dots"></canvas>
    <canvas id="interactive"></canvas>
</div>


