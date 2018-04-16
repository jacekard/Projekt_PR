function Maze(r, c, w, h) {
	this.grid = [];
	this.rows = r;
	this.cols = c;
	this.w = w;
	this.h = h;

	this.Init = function() {
		this.grid = new Array(cols);
		for(var i = 0; i < this.cols; i++) {
			this.grid[i] = new Array(this.rows);
		}

		for(var i = 0; i < this.cols; i++) {
			for(var j = 0; j < this.rows; j++) {
				var cell = new Cell(i,j, this.rows, this.cols, this.grid);
				this.grid[i][j] = cell;
			}
		}
	}

	this.show = function() {
		for(var i = 0; i < this.cols; i++) {
			for(var j = 0; j < this.rows; j++) {
				this.grid[i][j].show();
			}
		}
	}
}

function Cell(j, i, c, g) {
	this.x = j;
	this.y = i;

	this.show = function() {
	stroke(color(random(255),255,255));
	strokeWeight(w/10);
	noFill();
	}
}