var _width = 1500;
var _height = 1500;
var cols = 10;
var rows = 10;
var w,h,m;
var arr = [];
var display = true;
var asd = [];
var startDrawing = false;


function setup() {
	createCanvas(_width,_height);

	w = _width / cols;
	h = _height / rows;
	for(var x = 0; x < cols; x++){
		arr[x] = new Array(this.rows);
		for(var y = 0; y < rows; y++){ 
			g = new gowno(x, y, w, h);
			arr[x][y] = g;
			asd.push(g);
		}    
	}


}

function draw() {	
	if(display) {
		for(var i = 0; i < cols; i++) {
			for(var j = 0; j < rows; j++) {
				arr[i][j].show();
			}
		}
		display = false;
	}
}

function mouseDragged() {
	var pos_y = mouseY;
	var pos_x = mouseX;
	var a = floor(pos_x/w);
    var b = floor(pos_y/h);
	arr[a][b].set = true;
	arr[a][b].show();
}

function keyPressed() {
	if (keyCode === DELETE || keyCode === BACKSPACE) {
	var pos_y = mouseY;
	var pos_x = mouseX;
	var a = floor(pos_x/w);
	var b = floor(pos_y/h);
	arr[a][b].set = false;
	arr[a][b].show();
	}

	if(keyCode === ENTER) {
		var writer = createWriter('newMap.txt');
		writer.print(rows + ' ' +cols + ' 0');
		for(var i = 0; i < asd.length; i++) {
			if(asd[i].set) {
				writer.print(asd[i].x + ' ' + asd[i].y);
				//console.log();
			}
		}
		writer.close();
	}
} 

  function gowno(x, y, w, h) {
	this.x = x;
	this.y = y;
	this.w = w;
	this.h = h;

	this.set = false;

	this.show = function() {
		if(this.set == true) {
			fill(128, 159, 255);
		} else {
			fill(240, 240, 240);
		}
		rect(this.x*this.w, this.y*this.h, this.w, this.h);
	}

	this.showRGB = function(r,g,b) {
		fill(r,g,b);
		rect(this.x*this.w, this.y*this.h, this.w, this.h);
	}
  }