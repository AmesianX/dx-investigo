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

//
// Logic and behavior for the 'Config' page of the app.
//
var ConfigPage = (function () {
    "use strict";

    // Create a page to add to the application.
    var public_create = function (page_name, page_title, template_data, app) {

        // Page instance public interface.
        var page_public = Page.create(page_name, page_title, template_data, app);
        var page_id = '#' + page_name;

        // Used for assigning ids to objects in the config tree.
        var next_id = 1;

        // Keep a reference to the raw config data so it can be filtered.
        var config_data = null;  

        /*todo: one day enable the filter.
        var matches_filter = function(data, filter) {
            var matches = String(data).toLowerCase().indexOf(filter) != -1;
            return matches;
        };

        var apply_filter = function(data, filter) {

            if (TemplateHelpers.is_array(data)) {
                var new_data = [];

                for (var i = 0; i < data.length; i += 1) {
                    if (data[i] != null) {
                        var new_element = apply_filter(data[i], filter);
                        if (new_element != null) {
                            new_data.push(new_element);
                        }
                    }
                }

                if (new_data.length == 0) {
                    return null;
                } else {
                    return new_data;
                }
            } else if (TemplateHelpers.is_object(data)) {
                if (data.value != null) {
                    var new_value = apply_filter(data.value, filter);
                    if (new_value != null || matches_filter(data.name, filter)) {

                        var new_object = {};
                        jQuery.extend(new_object, data);                        
                        new_object.value = new_value;
                        return new_object;
                    }
                } else {
                    if (matches_filter(data.name, filter)) {
                        return data;
                    }
                }

                return null;
            } else {
                if (matches_filter(data, filter)) {
                    return data;
                } else {
                    return null;
                }
            }
        };
        */

        // Recursively assign ids to the config tree for the purpose of turning it
        // into a table tree.
        var assign_ids = function (data, parent_id) {

            if (TemplateHelpers.is_array(data)) {
                for (var i = 0; i < data.length; i += 1) {
                    assign_ids(data[i], parent_id);
                }
            } else if (TemplateHelpers.is_object(data)) {
                data.id = next_id;
                data.parent_id = parent_id;
                next_id += 1;
                if (data.value != null) {
                    assign_ids(data.value, data.id);
                    }
                }
        };

        //todo: move to utils.
        $.fn.expandAll = function() {
            $(this).find("tr").removeClass("collapsed").addClass("expanded").each(function(){
                $(this).expand();
            });
        };        

        // Expand the config tree data to a html tree view and
        // inject it into the page.
        var init_config_tree = function () {

            var filtered_data = config_data;

            /*todo: one day, enable the filter.

            var filter = $('#config_filter').val(); //todo: don't depend on abs id.
            if (filter !== "") {
                filtered_data = apply_filter(filtered_data, filter.toLowerCase()) || [];
            }
            */

            //console.log("Filtered:");
            //console.log(filtered_data);

            var config_tree_expanded = $('#config_hierarchy_template').tmpl(filtered_data);
            var config_list_element = $(page_id).find('#config_list');
            config_list_element.empty();
            config_tree_expanded.appendTo(config_list_element);

            config_list_element.treeTable().expandAll();           
        }

        var datamanager = app.get_datamanager();
        datamanager.get_config(function (data) {

            config_data = data;

            assign_ids(config_data, -1);
                    
            init_config_tree();
        });

        //todo: make this less dependent on the abs id.
        $('#config_filter_button').click(function () {
            init_config_tree();
        });

        $('#config_clear_filter_button').click(function () {

            $('#config_filter').val('');

            init_config_tree();
        });

        return page_public;
    };

    // ConfigPage public interface.
    return $.extend($.extend({}, Page), {
        create: public_create
    });
}());