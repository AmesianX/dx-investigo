//Copyright (C) 2012 Ashley Davis
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
//documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
//and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
//WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

var Graph = (function () {

	var create_graph = function (graph_element, data_window) {

		var min = 0;
		var max = 0;
		var graph_width = graph_element.width();
		var graph_height = graph_element.height();
		var ctx = graph_element.get(0).getContext("2d");
		var left_right_gutter = 40;
		var bottom_gutter = 15;
		var most_recent_value = 0;

		// Array of arrays or array, each inner array actually containing data.
		// Elements are when 'data_window' is exceeded.
		//
		//  double_buffer --> Level A
		//  	|
		//		|-- [] --> Level B, Chunk list
		//		|	|
		//		|	|-- [1, 2, 3, 4] --> Level C, data chunk
		//		|	|
		//		|	|-- [1, 2, 3, 4]
		//		|	|
		//		|	|-- [1, 2, 3, 4]
		//		|
		//		|-- []
		//			|
		//			|-- [1, 2, 3, 4]
		//			|
		//			|-- [1, 2, 3, 4]
		//			|
		//			|-- [1, 2, 3, 4]
		//		
		var double_buffer = [[], []];

		// Total data elements in the data store.
		var total_data = 0;

 		ctx.lineJoin = "miter";
	    ctx.lineWidth = 0.7;

		var render_graph = function () {

			//
			// Clear background.
			//

			ctx.clearRect(0, 0, graph_width, graph_height);

			if (total_data == 0) {
				return; // Nothing yet.
			}

			// 
			// Render lines.
			//

			ctx.strokeStyle = "#6CA9D3";
			ctx.beginPath();

			var started = false;
			var x = left_right_gutter;
			var x_step = (graph_width - (left_right_gutter * 2)) / data_window;
			var y_multiplier = (graph_height - bottom_gutter) / max;
			var amount_per_buffer = [ 0, 0 ];

			for (var i = 0; i < double_buffer.length; i += 1) { // A, double buffer.

				var chunk_list = double_buffer[i];

				for (var j = 0; j < chunk_list.length; j += 1) { // B, chunk list.

					var data_chunk = chunk_list[j];
					amount_per_buffer[i] += data_chunk.length;

					for (var k = 0; k < data_chunk.length; k += 1) { // C, data chunk.

						var data_value = data_chunk[k];
						var frame = data_value[0];
						var value = data_value[1];
						var y = (graph_height - bottom_gutter) - (value * y_multiplier);

						/*todo:
						if ((frame % 100) === 0) {
							ctx.fillText(frame, x, graph_height - 2);
						}
						*/

						if (started) {
							
							ctx.lineTo(x, y);
						} 
						else {
							started = true;

							ctx.moveTo(x, y);
						}

						x += x_step;						
					}
				}
			}

			ctx.stroke();

			//
			// Render the green line that shows the current point of insertion in the graph.
			//

			ctx.strokeStyle = "#00FF00";
			ctx.beginPath();

			x = left_right_gutter + (amount_per_buffer[0] * x_step);
			var y1 = (graph_height - bottom_gutter) - (0 * y_multiplier);
			var y2 = (graph_height - bottom_gutter) - (max * y_multiplier); 
			ctx.moveTo(x, y1);
			ctx.lineTo(x, y2);

			ctx.stroke();

			// 
			// Render text for the most recent value.
			//

			ctx.fillText(most_recent_value, x+10, y2+10);

			//
			// Render text.
			//

			x = left_right_gutter;

			for (var i = 0; i < double_buffer.length; i += 1) { // A, double buffer.

				var chunk_list = double_buffer[i];

				for (var j = 0; j < chunk_list.length; j += 1) { // B, chunk list.

					var data_chunk = chunk_list[j];

					for (var k = 0; k < data_chunk.length; k += 1) { // C, data chunk.

						var data_value = data_chunk[k];
						var frame = data_value[0];
						var value = data_value[1];

						if ((frame % 100) === 0) {
							ctx.fillText(frame, x, graph_height - 2);
						}

						x += x_step;
					}
				}

			}
		};

		var update_graph = function (incoming_data) {

			// Update most recent value.

			if (incoming_data.length > 0) {
				most_recent_value = incoming_data[incoming_data.length-1][1];
			}			

			double_buffer[0].push(incoming_data);

			total_data += incoming_data.length;

			// Remove data when there is more than 'data_window'

			if (total_data > data_window) {

				// Remove data from second buffer.

				while (total_data > data_window && double_buffer[1].length > 0) {
					
					var overflow = total_data - data_window;

					if (overflow >= double_buffer[1][0].length) {

						// Remove first array.
						total_data -= double_buffer[1][0].length;

						double_buffer[1] = double_buffer[1].splice(1);

					}
					else {

						// Remove part of first array, then bail.
						total_data -= overflow;

						double_buffer[1][0] = double_buffer[1][0].splice(overflow);
						break;
					}
				}

				// Remove data from first buffer.

				while (total_data > data_window && double_buffer[0].length > 0) {
					
					var overflow = total_data - data_window;

					if (overflow >= double_buffer[0][0].length) {

						// Remove first array.
						total_data -= double_buffer[0][0].length;

						double_buffer[0] = double_buffer[0].splice(1);
					}
					else {

						// Remove part of first array, then bail.
						total_data -= overflow;

						double_buffer[0][0] = double_buffer[0][0].splice(overflow);
						break;
					}
				}

				if (double_buffer[1].length == 0) {

					// Dropped all data from second buffer.
					// Swap double buffers.
					var tmp = double_buffer[1];
					double_buffer[1] = double_buffer[0]
					double_buffer[0] = tmp;
				}
			}

			//
			// Scan for min, max values.
			// Recompute total data amount.
			//
			min = Number.MAX_VALUE;
			max = Number.MIN_VALUE;
			total_data = 0;

			// 
			// Recompute min / max
			//
			for (var i = 0; i < double_buffer.length; i += 1) { // A, double buffer.

				var chunk_list = double_buffer[i];

				for (var j = 0; j < chunk_list.length; j += 1) { // B, chunk list.

					var data_chunk = chunk_list[j];
					total_data += data_chunk.length;

					for (var k = 0; k < data_chunk.length; k += 1) { // C, data chunk.

						var data_value = data_chunk[k];

						if (data_value[1] < min) {
							min = data_value[1];
						}

						if (data_value[1] > max) {
							max = data_value[1];
						}
					}
				}
			}					

			render_graph();
		};

		//
		// Graph instance public interface.
		//
		return {
			update: update_graph,


		};
	};

	//
	// Graph public interface.
	//
	return {
		create: create_graph
	};

})();


