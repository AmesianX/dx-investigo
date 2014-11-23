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


var app = App.create(); //todo: good for debugging, but should move this inside the module.

//
// Page initialization.
//

(function () {
    "use strict";

    console.log("Startup");

    $(document).bind("mobileinit", function () {
        console.log("jQueryMobile init.");
    });
}());

//
// DOM ready.
//        
$(function () {

    console.log("DOM ready");

    console.log("Generating pages...");

    console.log(document.URL);

    if (document.URL.startsWith("file://")) {
        console.log("Automatically entering test mode.");
        testMode = true;
    }

    var root_page_breadcrumbs = [{ page_name: 'home', page_title: 'Home' }];

    app.add_page(Page.create('home', 'Home', { name: 'home', title: 'Home' }, app));
    app.add_page(ConfigPage.create('config', 'Config', { name: 'config', title: 'Config', breadcrumbs: root_page_breadcrumbs }, app));
    app.add_page(PerformancePage.create('performance', 'Performance', { name: 'performance', title: 'Performance', breadcrumbs: root_page_breadcrumbs  }, app));
    app.add_page(DebuggerPage.create('debugger', 'Debugger', { name: 'debugger', title: 'Debugger', breadcrumbs: root_page_breadcrumbs }, app));
    app.add_page(InspectorPage.create('inspector', 'Inspector', { name: 'inspector', title: 'Inspector', breadcrumbs: root_page_breadcrumbs }, app));
    app.add_page(Page.create('frame_analysis', 'Frame Analysis', { name: 'frame_analysis', title: 'Frame Analysis', breadcrumbs: root_page_breadcrumbs }, app));
    app.add_page(Page.create('resources', 'Resources', { name: 'resources', title: 'Resources', breadcrumbs: root_page_breadcrumbs }, app));
    app.add_page(Page.create('output', 'Output', { name: 'output', title: 'Output', breadcrumbs: root_page_breadcrumbs }, app));
    app.add_page(Page.create('about', 'About', { name: 'about', title: 'About', breadcrumbs: root_page_breadcrumbs }, app));

    //todo: hack to set title, should do this in the page template.
    //todo: what was the link where I found this?
    $(":jqmData(role='page')").attr("data-title", document.title);

    //todo: replace ajax calls with datamanager.

    /*todo: Client message handling, might want this again one day.
    var add_message = function (message) {
        $('#output').append($('<p/>').text(message));
    };

    var message_poll_interval = 1000;

    var message_poll = function () {

        $.ajax({  //todo: wrap me!
            type: "GET",  
            dataType: 'json',
            url: "/get_messages",  
            data: {},
            async: true,
            success: function(data) {

                for (var i = 0; i < data.length; i += 1) {
                    add_message(data[i]);
                }
            }

        });                   


        setTimeout(message_poll, message_poll_interval); // Poll
    };

    if (!testMode)
    {
        message_poll();
    }
    */

    // The current state of performance logging.
    var perf_logging_enabled = false;
    var draw_calls_enabled = true;
    var state_poll_interval = 1000;
    var perf_log_enabled_text = "Stop Performance Logging";
    var perf_log_disabled_text = "Start Performance Logging";
    var draw_calls_enabled_text = "Disable Draw Calls";
    var draw_calls_disabled_text = "Enable Draw Calls";

    $(".performance_logging").live('click', function () {  
        
        $.ajax({  
          type: "GET",  
          url: "/toggle_performance_logging"
        });              
    });

    $(".toggle_draw_calls").live('click', function () {  

        $.ajax({  
          type: "GET",  
          url: "/toggle_draw_calls"
        });              
    });

    // Poll every second to see if performance logging has started / stopped.
    var state_poll = function () {

        $.ajax({  //todo: wrap me!
            type: "GET",  
            dataType: 'json',
            url: "/get_status",  
            data: {},
            async: true,
            success: function(data) {

                if (data.perf_logging_enabled != perf_logging_enabled) {
                    perf_logging_enabled = data.perf_logging_enabled;

                    if (perf_logging_enabled) {
                        $('.performance_logging .ui-btn-text').text(perf_log_enabled_text);
                    } else {
                        $('.performance_logging .ui-btn-text').text(perf_log_disabled_text);
                    }

                    
                }

                if (data.draw_calls_enabled != draw_calls_enabled) {
                    draw_calls_enabled = data.draw_calls_enabled;

                    if (draw_calls_enabled) {
                        $('.toggle_draw_calls .ui-btn-text').text(draw_calls_enabled_text);
                    } else {
                        $('.toggle_draw_calls .ui-btn-text').text(draw_calls_disabled_text);
                    }

                    
                }
            }

        });                   

        setTimeout(state_poll, state_poll_interval); // Poll
    };

    if (!testMode)
    {
        state_poll();
    }

    /*todo: old screen shot code.  Might want to bring this online again.
    $("#take_screenshot").click(function () {  

        $.ajax({  
          type: "GET",  
          dataType: 'json',
          url: "/take_screenshot",  
          data: {},
          async: true,
          success: function(data) {
            if (data.error) {
                console.log("Error: " + data.error);                
                display_error(data.error);
            } else if (data.screenshot_filename) {
                console.log("Screenshot: " + data.screenshot_filename);
                var msg = '<p>Screenshot:</p><p style="font-size: 0.5em">' + data.screenshot_filepath + '</p><img src="' + data.screenshot_filename + '">';
                display_message(msg);
            } else {
                //todo: log a generic error.
                console.log("Unexplained error!");
            }
          }
        });              
    });     
    */

    var logEvents = false;

    $('#body').live('pagebeforeload', function (event) {
        if (logEvents) {
            console.log('Body event pagebeforeload');
        }
    });

    $('#body').live('pageload', function (event) {
        if (logEvents) {
            console.log('Body event pageload');
        }
    });

    $('#body').live('pageloadfailed', function (event) {
        if (logEvents) {
            console.log('Body event pageloadfailed');
        }
    });

    $('#body').live('pagebeforechange', function (event) {
        if (logEvents) {
            console.log('Body event pagebeforechange');
        }
    });

    $('#body').live('pagechange', function (event) {
        if (logEvents) {
            console.log('Body event pagechange');
        }
    });

    $('#body').live('pagechangefailed', function (event) {
        if (logEvents) {
            console.log('Body event pagechangefailed');
        }
    });

    $('#body').live('pagebeforeshow', function (event) {
        if (logEvents) {
            console.log('Body event pagebeforeshow');
        }
    });

    $('#body').live('pagebeforehide', function (event) {
        if (logEvents) {
            console.log('Body event pagebeforehide');
        }
    });

    $('#body').live('pageshow', function (event) {
        if (logEvents) {
            console.log('Body event pageshow');
        }


    });

    $('#body').live('pagehide', function (event) {
        if (logEvents) {
            console.log('Body event pagehide');
        }
    });

    $('#body').live('pagecreate', function (event) {
        if (logEvents) {
            console.log('Body event pagecreate');
        }
    });

    $('#body').live('pageinit', function (event) {
        if (logEvents) {
            console.log('Body event pageinit');
        }
    });

    $('#body').live('pageremove', function (event) {
        if (logEvents) {
            console.log('Body event pageremove');
        }
    });

    $('#body').live('updatelayout', function (event) {
        if (logEvents) {
            console.log('Body event updatelayout');
        }
    });

    $('#body').live('pagebeforecreate', function (event) {
        if (logEvents) {
            console.log('Body event pagebeforecreate');
        }
    });

    //
    // Persist header/footer during page transitions.
    //
    // http://stackoverflow.com/questions/6258866/persistent-header-in-jquery-mobile
    //

    /*todo: can i get this working?
    // dynamically move the header and footer between pages on load events
    $('div.ui-page').live('pagebeforeshow', function (event, ui) {
        // avoid duplicating the header on the first page load
        if (ui.prevPage.length == 0) return;

        // remove the jQuery Mobile-generated header
        $('.ui-header').addClass('to-remove-now');
        $('#header').removeClass('to-remove-now');
        $('.to-remove-now').remove();

        // grab the code from the current header and footer
        header = $('#header')[0].outerHTML;
        footer = $('#footer')[0].outerHTML;

        // mark the existing header and footer for deletion
        $('#header').addClass('to-remove');
        $('#footer').addClass('to-remove');

        // prepend the header and append the footer to the generated HTML
        event.currentTarget.innerHTML = header + event.currentTarget.innerHTML + footer;
    });

    // remove header from previous page 
    $('div.ui-page').live('pagehide', function (event, ui) {
        $('.to-remove').remove();
    });    
    */
});
