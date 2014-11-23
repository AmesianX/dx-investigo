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

var testMode = false;

var App = (function () {
    "use strict";

    var create = function () {
        
        // App instance public interface.
        var app_public = {};

        // Private data.
        // Pages added to the app.
        var pages = {};
        var datamanager = DataManager.create();

        // Constructor.
        var constructor = function () {
        };

        // Add a named page.
        var add_page = function (page) {
            pages[page.get_name()] = page;
            return page;
        };

        // Retreive a page by name.
        var get_page = function (page_name) {
            return pages[page_name];
        };

        var get_pages = function () {
            var pages_copy = $.extend({}, pages);
            return pages_copy;
        };

        var get_datamanager = function () {
            return datamanager;
        };

        // App instance public interface.
        app_public.add_page = add_page;
        app_public.get_page = get_page;
        app_public.get_pages = get_pages;
        app_public.get_datamanager = get_datamanager;

        constructor();
        return app_public;
    };

    // App public interface.
    return {
        create: create
    };
}());

