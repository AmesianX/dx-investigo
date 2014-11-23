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

var InspectorPage = (function () {
    "use strict";

    // Create a page to add to the application.
    var public_create = function (page_name, page_title, template_data, app) {

        // Page instance public interface.
        var page_public = Page.create(page_name, page_title, template_data, app);

        var super_onshow = page_public.onshow;

        var page_id = '#' + page_name;
        var status_update_interval = 100;
        var inspector_status = "running";
        var suspend_location = "n/a";
        var suspend_count = 1;
        var datamanager = app.get_datamanager();

        var init_directx_state_display = function (page_content_element) {

            datamanager.get_state(function (data) {
                    var list_expanded = $('#suspended_state_template').tmpl({})
                    list_expanded.appendTo(page_content_element);

                    var render_state_item_expanded = $('#render_state_item_template').tmpl(data.render_state);
                    render_state_item_expanded.appendTo(list_expanded);

                    page_content_element.trigger('create');
                });

        };

        var init_controls = function (state_data) {

            // Read value of the step count, so it can be restored.
            var step_count = $('#inspector_step_count');
            if (step_count.length > 0) {
                suspend_count = $('#inspector_step_count').val();
            }

            var template_id = '#inspector_' + inspector_status + '_template';
            var template_element = $(template_id);
            if (template_element === null || template_element.length === 0) {
                console.log("Template with ID not found: " + template_id);
                return;
            }

            var template_data = {
                inspector_status: inspector_status,
                suspend_location: suspend_location,
                suspend_count: suspend_count,
                state_data: state_data
            };

            var controls_template_expanded = $(template_id).tmpl(template_data);

            var page_content_element = $(page_id).find('.page_content');
            page_content_element.empty();
            controls_template_expanded.appendTo(page_content_element);

            if (state_data !== null && inspector_status === "suspended") {

                page_content_element.find('#inspector_backbuffer_screenshot').attr("src", "/get_backbuffer?"+(new Date()).getTime());
                page_content_element.find('#inspector_rendertarget_screenshot').attr("src", "/get_rendertarget?"+(new Date()).getTime());


                // Create textures templated data.
                var textures_template_data = [];
                for (var texture_index = 0; texture_index <= state_data.max_bound_texture_index; ++texture_index) {
                    textures_template_data.push({ 
                        'texture_url': '/get_bound_texture?' + (new Date()).getTime()+ '&index=' + texture_index
                    });
                }

                var textures_expanded = $('#texture_template').tmpl(textures_template_data);
                var textures_list = page_content_element.find('.textures');
                textures_expanded.appendTo(textures_list);

                var render_state_item_expanded = $('#render_state_item_template').tmpl(state_data.render_state);
                render_state_item_expanded.appendTo(page_content_element.find('#inspector_render_state'));
            }

            page_content_element.trigger('create');
        };

        var status_update = function () {

            if (!page_public.is_visible()) {
                // Page is no longer visible, stop the ajax poll.
                return;
            }

            datamanager.get_inspector_status(function (data) {
                if (inspector_status === data.inspector_status &&
                    suspend_location == data.suspend_location) {
                    // No change.
                    return;
                }

                inspector_status = data.inspector_status;
                suspend_location = data.suspend_location;

                init_controls(data);
            });

            setTimeout(status_update, status_update_interval); // Poll
        };

        var init_status_update = function () {

            status_update();
        };

        var onshow = function () {
            if (super_onshow) {
                super_onshow();
            }

            init_controls();
            init_status_update();

            //todo: absstract out ajax calls
            //todo: don't hit element id directly.
            $('#inspector_suspend_button').live('click', function () {

                $.ajax({  
                  type: "GET",  
                  url: "/suspend",  
                  data: {}
              });
            });

            $('#inspector_resume_button').live('click', function () {
                $.ajax({  
                  type: "GET",  
                  url: "/resume",  
                  data: {}
              });
            });

            $('#inspector_step_button').live('click', function () {
                $.ajax({  
                  type: "GET",  
                  url: "/step",  
                  data: {
                    count: $('#inspector_step_count').val()
                  }
              });
            });

            $('#inspector_breakpoint_button').live('click', function () {
                $.ajax({  
                  type: "GET",  
                  url: "/trigger_breakpoint_now",  
                  data: {}
              });
            });                        
        };

        page_public.onshow = onshow;

        return page_public;
    };

    // InspectorPage public interface.
    return $.extend($.extend({}, Page), {
        create: public_create
    });
}());