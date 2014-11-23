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


var PerformanceSubPage = (function () {
    "use strict";

    // Create a page to add to the application.
    var public_generate = function (page_name, page_title, page_template_id, template_data, app) {

        // Private variables.
        var page_id = '#' + page_name;
        var content_id = '#' + page_name + '_content';

        // setup control widget
        var updateInterval = 50; //todo: move this to global settings.
        var dataWindow = 1000; 

        // Variables added to the page.
        var variables = [];

        // Page instance public interface.
        var page_public = Page.generate(page_name, page_title, page_template_id, template_data, app);

        var super_onshow = page_public.onshow;
        var super_onhide = page_public.onhide;


        var init_variable = function (variable, graph_x_offset, graph_width) {

            //console.log('Initializing variable: ' + variable.id + ' ' + variable.name);

            var graph_name = page_name + '__' + variable.id + '_graph';
            var graph_id = '#' + graph_name;

            var graph_label_id = '#' + graph_name + '_label';

            var template_data = {
                name: variable.name,
                graph_id: graph_name
            };

            var expanded = $('#variable_template').tmpl(template_data);

            expanded.appendTo($(page_id).find('.variables_content'));

            $(graph_label_id).offset({ left: graph_x_offset });

            var graph_element = $(graph_id);
            graph_element.offset({ left: graph_x_offset });
            graph_element.attr('width', graph_width);

            var graph = Graph.create(graph_element, dataWindow);
            return graph;
        };

        var onshow = function () {
            if (super_onshow) {
                super_onshow();
            }

            var content = $(content_id);
            var width = content.width();
            var height = content.height();

            var page = $(page_id);
            var page_width = page.width();
            var graph_width = page_width * 0.8;
            var graph_x_offset = page_width * 0.1;

            //console.log("page size: " + $(page_id).width() + ' ' + $(page_id).height());
            //console.log("content size: " + width + ' ' + height);

            var variables_content = page.find('.variables_content').assertSingle();
            variables_content.empty();

            var graphs = {};
            var variable_ids = [];

            if (variables) {
                for (var i = 0; i < variables.length; i += 1) {
                    var variable = variables[i];
                    var graph = init_variable(variable, graph_x_offset, graph_width);
                    if (graph) {
                        graphs[variable.id] = graph;
                        variable_ids.push(variable.id);
                    }
                }
            }

            variable_ids = variable_ids.toString(); // Convert to comma sep string.

            var update_graph = function (retreived_data) {

                for (var i = 0; i < retreived_data.length; ++i) {

                    var variable_id = retreived_data[i].id;
                    var data = retreived_data[i].data;
                    var variable_history = data.history;

                    if (variable_history.length > 0) {
                        graphs[variable_id].update(variable_history);
                    }
                }
            };

            if (graphs.length == 0) {
                return;
            }

            var update = function () {

                if (!page_public.is_visible()) { // Page no longer visible, stop AJAX poll.
                    graphs = null; // Try to hurry up the garbage collector.
                    return;
                }

                if (testMode) { //todo: move to data manager.
                    update_graph(test_variable_history);

                    setTimeout(update, updateInterval); // Poll

                } else {
                    // Not in test mode, do the real ajax call.

                    $.ajax({
                        url: '/get_variable_history?variable_id=' + variable_ids,
                        dataType: 'json',
                        data: {},
                        async: true,
                        success: function (data) {

                            update_graph(data);

                            setTimeout(update, updateInterval); // Poll
                        },
                        error:  function (data) {

                            setTimeout(update, updateInterval); // Poll
                        }
                    });
                    
                }

            };

            update();
        };

        var onhide = function () {
            if (super_onhide) {
                super_onhide();
            }
        };

        // Add a variable to the page.
        var add_variable = function (variable_id, variable_name) {

            variables.push({
                id: variable_id,
                name: variable_name
            });
        };

        // Callback functions.
        page_public.onshow = onshow;
        page_public.onhide = onhide;
        page_public.add_variable = add_variable;

        return page_public;
    };

    // PerformancePage public interface.
    return $.extend($.extend({}, Page), {
        generate: public_generate
    });
}());