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

var DataManager = (function () {

	var public_create = function () {

        var get_breakpoints = function (success_callback) {
            if (testMode) {
                success_callback(test_breakpoints);
            } else {
                $.ajax({
                    url: '/get_breakpoints',
                    dataType: 'json',
                    data: {},
                    async: false,
                    success: success_callback
                });
            }
        }

		var get_config = function (success_callback) {

	        if (testMode) {
	            success_callback(test_config);
	        } else {
	            $.ajax({
	                url: '/get_config',
	                dataType: 'json',
	                data: {},
	                async: true,
	                success: success_callback
	            });
	        }
		};

		var get_state = function (success_callback) {
			//todo: test mode!
            $.ajax({
                url: '/get_state',
                dataType: 'json',
                data: {},
                async: true,
                success: success_callback
            });
		};

		var get_inspector_status = function (success_callback) {
			//todo: test mode!
            $.ajax({
                url: '/get_inspector_status',
                dataType: 'json',
                data: {},
                async: true,
                success: success_callback
            });

		}

		var get_pages = function (success_callback) {
	        if (testMode) {
	            // In test mode, fake some ajax data.
	            success_callback(test_data);

	        } else {

	            // Not in test mode, do the real ajax call.
	            $.ajax({
	                url: '/get_pages',
	                dataType: 'json',
	                data: {},
	                async: false,
	                success: success_callback
	            });
	        }
		};

		// DataManager instance public interface.
		return {
			get_config: get_config,
			get_state: get_state,
			get_inspector_status: get_inspector_status,
			get_pages: get_pages,
            get_breakpoints: get_breakpoints
		};
	};


	// DataManager public interface.
	return {
		create: public_create
	};

})();