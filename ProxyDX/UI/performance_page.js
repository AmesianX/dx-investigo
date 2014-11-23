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

var PerformancePage = (function () {
    "use strict";

    //
    // Expand data to a list of pages using a template.
    //
    var expand_pages_list = function (page_element, pages_data) {

        var page_list_expanded = $('#page_list_template').tmpl({});
        var page_list_item_expanded = $('#page_list_item_template').tmpl(pages_data);
        page_list_item_expanded.appendTo(page_list_expanded.find('.pages_list'));
        page_list_expanded.appendTo(page_element.find('.page_content'));

        //console.log('Expanding: ');
        //console.log(pages_data);
        //console.log("To: " + pages_list_id + " using template: " + page_list_template_id);
    };

    var generate_pages = function (parent_page, parent_page_name, pages_list, parent_breadcrumbs) { 
        var page;
        var full_page_name;
        var new_sub_page;
        var pages_list_id;
        var i, j;


        for (i = 0; i < pages_list.length; i += 1) {
            page = pages_list[i];
            full_page_name = parent_page_name + page.id;
            var template_data = {
                name: full_page_name,
                title: page.name,
                breadcrumbs: parent_breadcrumbs
            };
            new_sub_page = PerformanceSubPage.generate(full_page_name, page.name, '#performance_page_template', template_data);
            parent_page.add_sub_page(new_sub_page);

            // Update the id for the page to be used in page expansion later.
            page.id = full_page_name; //todo: this should be done automatically by the generate fn.

            if (page.pages) {

                var breadcrumbs = $.extend([], parent_breadcrumbs);
                breadcrumbs.push({
                    page_name: full_page_name, 
                    page_title: page.name
                });

                generate_pages(new_sub_page, full_page_name + '_', page.pages, breadcrumbs);

                expand_pages_list($('#' + full_page_name), page.pages);
            }

            if (page.variables) {
                for (j = 0; j < page.variables.length; j += 1) {
                    var variable = page.variables[j];
                    new_sub_page.add_variable(variable.id, variable.name);
                }
            }
        }
    };

    // Create a page to add to the application.
    var public_create = function (page_name, page_title, template_data, app) {

        // Page instance public interface.
        var page_public = Page.create(page_name, page_title, template_data, app);

        var breadcrumbs = $.extend([], template_data.breadcrumbs);
        breadcrumbs.push({
            page_name: page_name,
            page_title: page_title
        });

        var datamanager = app.get_datamanager();
        datamanager.get_pages( function(data) {
            generate_pages(page_public, page_name + '__', data.pages, breadcrumbs);
            expand_pages_list($('#' + page_name), data.pages);
        });

        return page_public;
    };

    // PerformancePage public interface.
    return $.extend($.extend({}, Page), {
        create: public_create
    });
}());