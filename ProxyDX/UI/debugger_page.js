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

var DebuggerPage = (function () {
    "use strict";

    // Create a page to add to the application.
    var public_create = function (page_name, page_title, template_data, app) {

        // Page instance public interface.
        var page_public = Page.create(page_name, page_title, template_data, app);

        var page_id = '#' + page_name;
        var page_element = $(page_id);

        var datamanager = app.get_datamanager();
        datamanager.get_breakpoints(function (breakpoints) {

            var breakpoint_list_item_expanded = $('#breakpoint_list_item_template').tmpl(breakpoints);
            breakpoint_list_item_expanded.appendTo(page_element.find('.breakpoints_list'));
        });

        page_element.find('.breakpoint_button').live('click', function () {

            var break_point_location = $(this).attr('id');

            $.ajax({  
              type: "GET",  
              url: "/set_breakpoint",  
              data: {
                break_point_location: break_point_location
              },
            });              
        });                        

        return page_public;
    };

    // DebuggerPage public interface.
    return $.extend($.extend({}, Page), {
        create: public_create
    });
}());