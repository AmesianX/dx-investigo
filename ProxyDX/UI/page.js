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

var Page = (function () {
     "use strict";

     // Enable event logging for JQuery mobile events.
     var logEvents = true; 

     var inject_navbar = function (header, template_data) {
        var navbar_expanded = $('#navbar_template').tmpl(template_data);
        navbar_expanded.appendTo(header);   
     }

    // Add a breadcrumb trail to the header.
    var inject_breadcrumb_trail = function (header, template_data) {

        var breadcrumb_expanded = $('#breadcrumb_template').tmpl(template_data);
        breadcrumb_expanded.appendTo(header);
    };

    // Inject elements that appear on every page.
    var inject_page_elements = function (page, template_data) {

        var header = $('#header_template').tmpl(template_data);
        inject_navbar(header, template_data);
        inject_breadcrumb_trail(header, template_data);
        header.prependTo(page);


        var footer = $('#footer_template').tmpl(template_data);
        footer.appendTo(page);

    };

    var gen_page_html = function (page_template_id, template_data) {
        var expanded = $(page_template_id).tmpl(template_data);

        // Inject a header and footer into the page.
        inject_page_elements(expanded, template_data);

        //console.log("HTML:");
        //console.log(expanded);
        expanded.appendTo($('#body'));
    };

    // Create a page to add to the application.
    // HTML for the page is expected to exist in the DOM.
    var internal_create = function (page_name, page_title, app) {

        var page_id = '#' + page_name;
        var page_is_visible = false;

        // Container for sub-pages.
        var sub_pages = {};

        // Page instance public interface.
        var page_public = {};

        // Set the jquery mobile theme.
        $(page_id).attr('data-theme', "b");

        // Page constructor.
        var constructor = function () {

            $(page_id).live('pagebeforeload', function (event) {
                if (logEvents) {
                    console.log('Event pagebeforeload: ' + page_name);
                }
            });

            $(page_id).live('pageload', function (event) {
                if (logEvents) {
                    console.log('Event pageload: ' + page_name);
                }
            });

            $(page_id).live('pageloadfailed', function (event) {
                if (logEvents) {
                    console.log('Event pageloadfailed: ' + page_name);
                }
            });

            $(page_id).live('pagebeforechange', function (event) {
                if (logEvents) {
                    console.log('Event pagebeforechange: ' + page_name);
                }
            });

            $(page_id).live('pagechange', function (event) {
                if (logEvents) {
                    console.log('Event pagechange: ' + page_name);
                }
            });

            $(page_id).live('pagechangefailed', function (event) {
                if (logEvents) {
                    console.log('Event pagechangefailed: ' + page_name);
                }
            });

            $(page_id).live('pagebeforeshow', function (event) {
                if (logEvents) {
                    console.log('Event pagebeforeshow: ' + page_name);
                }
            });

            $(page_id).live('pagebeforehide', function (event) {
                if (logEvents) {
                    console.log('Event pagebeforehide: ' + page_name);
                }
            });

            $(page_id).live('pageshow', function (event) {
                if (logEvents) {
                    console.log('Event pageshow: ' + page_name);
                }

                if (page_public.onshow) {
                    page_public.onshow();
                }
            });

            $(page_id).live('pagehide', function (event) {
                if (logEvents) {
                    console.log('Event pagehide: ' + page_name);
                }

                if (page_public.onhide) {
                    page_public.onhide();
                }
            });

            $(page_id).live('pagecreate', function (event) {
                if (logEvents) {
                    console.log('Event pagecreate: ' + page_name);
                }
            });

            $(page_id).live('pageinit', function (event) {
                if (logEvents) {
                    console.log('Event pageinit: ' + page_name);
                }
            });

            $(page_id).live('pageremove', function (event) {
                if (logEvents) {
                    console.log('Event pageremove: ' + page_name);
                }
            });

            $(page_id).live('updatelayout', function (event) {
                if (logEvents) {
                    console.log('Event updatelayout: ' + page_name);
                }
            });

            $(page_id).live('pagebeforecreate', function (event) {
                if (logEvents) {
                    console.log('Event pagebeforecreate: ' + page_name);
                }

                if (page_public.precreate) {
                    page_public.precreate();
                }
            });
        };

        var get_name = function () { return page_name; };
        var get_title = function () { return page_title; };
        var add_sub_page = function (sub_page) { sub_pages[sub_page.get_name()] = sub_page; };
        var get_sub_page = function (page_name) { return sub_pages[page_name]; };
        var is_visible = function () { return page_is_visible; }

        var onshow = function () {

            console.log("onshow: " + page_name);

            page_is_visible = true;
        };

        var onhide = function () {

            console.log("onhide: " + page_name);

            page_is_visible = false;
        };

        // Activate appropriate 'tab' button for the page.
        var page_name_prefix = page_name.split('__')[0];
        var active_btn_id = '.' + page_name_prefix;
        $(page_id).find(active_btn_id).addClass('ui-btn-active');

        // Page instance public interface.
        page_public.get_name = get_name;
        page_public.get_title = get_title;
        page_public.add_sub_page = add_sub_page;
        page_public.get_sub_page = get_sub_page;
        page_public.onshow = onshow;
        page_public.onhide = onhide;
        page_public.is_visible = is_visible;

        constructor();
        return page_public;
    };

    //todo: just incorporate name/title int template_data and rename it to page_data.
    var public_create = function(page_name, page_title, template_data, app) {

        var page_id = '#' + page_name;

        // Inject a header and footer into the page.
        inject_page_elements($(page_id), template_data);

        return internal_create(page_name, page_title, app);
    };

    // Generate a page, creates HTML and adds to the DOM.
    var public_generate = function (page_name, page_title, page_template_id, template_data, app) {

        //console.log("Generated page: " + page_name + " with template: " + page_template_id);

        gen_page_html(page_template_id, template_data);
        return internal_create(page_name, page_title, app);
    };

    // Page public interface.
    return {
        create: public_create,
        generate: public_generate
    };

}());    