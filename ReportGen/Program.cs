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
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Reflection;
using RazorEngine;
using RazorEngine.Templating;

namespace ReportGen
{
    public static class Program
    {
        static readonly string GraphDataVariable = "graph_data";
        static readonly string EmbeddedResourceDir = "ReportGen.ReportUI";
        static readonly string GraphTemplateResource = "ReportGen.ReportUI.GraphTemplate.html";
        static readonly string JQueryResource = "jquery-1.7.1.min.js";

        static void Main(string[] args)
        {
            if (args.Length == 0 || args.Length > 3)
            {
                Console.WriteLine(
@"
Usage: reportgen.exe <input-file(s)> [<report-dir>]

input-files:    Path to a single file or a wildcard.
report-dir:     Optional path to output performance report.");
                return;
            }

            string inputFilePath = args[0];
            string reportDir = args.Length > 1 ? args[1] : null;

            try
            {
                GenerateReport(inputFilePath, reportDir);
            }
            catch (System.Exception ex)
            {
                Console.WriteLine("Error: unhandled exception.");
                Console.WriteLine(ex);            	
            }
        }

        /// <summary>
        /// Generate a report based on input files to a particular output dir.
        /// </summary>
        private static void GenerateReport(string inputFilePath, string reportDir)
        {
            var inputDir = Path.GetDirectoryName(inputFilePath);
            if (string.IsNullOrEmpty(inputDir))
            {
                inputDir = ".";
            }

            var outputDir = 
                string.IsNullOrEmpty(reportDir) ?  
                    Path.Combine(inputDir, "Report") :
                    reportDir;

            Directory.CreateDirectory(outputDir);

            Console.WriteLine("Input: " + inputFilePath);
            Console.WriteLine("Output: " + outputDir);

            // Read the template for pages in the report.
            string reportTemplateText;
            using (var templateStream = new StreamReader(Assembly.GetExecutingAssembly().GetManifestResourceStream(GraphTemplateResource)))
            {
                reportTemplateText = templateStream.ReadToEnd();
            }

            string[] inputFiles = GetInputFiles(inputFilePath, inputDir);

            var reportFiles = new List<string>();

            foreach (var inputFile in inputFiles)
            {
                var reportFileName = Path.GetFileNameWithoutExtension(inputFile) + ".html";
                
                if (!reportFileName.ToLower().Contains("overview"))
                {
                    reportFiles.Add(reportFileName);
                }
            }

            foreach (var inputFile in inputFiles)
            {
                var reportFileName = Path.GetFileNameWithoutExtension(inputFile) + ".html";

                if (reportFileName.ToLower().Contains("overview"))
                {
                    // Create an index file out of the overview.
                    reportFileName = "Index.html";
                }

                GenerateReport(inputFile, outputDir, reportFileName, reportTemplateText, GraphDataVariable, reportFiles);
            }

            CopyResourceToFile(EmbeddedResourceDir, JQueryResource, outputDir);
        }

        /// <summary>
        /// Copy an embedded resource to a file.
        /// </summary>
        private static void CopyResourceToFile(string resourceDir, string resourceName, string outputDir)
        {
            var fullResourceName = resourceDir + "." + resourceName;
            using (var templateStream = new StreamReader(Assembly.GetExecutingAssembly().GetManifestResourceStream(fullResourceName)))
            {
                var resourceText = templateStream.ReadToEnd();
                var outputFile = Path.Combine(outputDir, resourceName);
                File.WriteAllText(outputFile, resourceText);
            }
        }

        /// <summary>
        /// Generate a report from a particular performance log file.
        /// </summary>
        private static void GenerateReport(string inputFilePath, string outputDir, string reportFileName, string reportTemplateText, string graphDataVariable, List<string> reportFiles)
        {
            var csvFile = new CsvFile(inputFilePath);

            var graphJavascriptFileName = Path.GetFileNameWithoutExtension(inputFilePath) + ".js";
            var graphJavascriptFilePath = Path.Combine(outputDir, graphJavascriptFileName);

            var reportFilePath = Path.Combine(outputDir, reportFileName);

            Console.WriteLine("Generating: " + graphJavascriptFilePath);
            Console.WriteLine("Generating: " + reportFilePath);

            using (var output = new StreamWriter(graphJavascriptFilePath))
            {
                csvFile.ToSeparatedJavaScript(output, graphDataVariable);
            }

            var html = 
                ExpandTemplate(reportTemplateText, 
                    new ReportTemplateModel
                    {
                        GraphDataJavascriptFile = graphJavascriptFileName,
                        GraphDataVariable = graphDataVariable,
                        Reports = reportFiles,
                    });
            File.WriteAllText(reportFilePath, html);
        }

        /// <summary>
        /// Figure out the set of inputs files based on the wild-card input.
        /// </summary>
        private static string[] GetInputFiles(string inputFilePath, string inputDir)
        {
            if (inputFilePath.Contains('*'))
            {
                // Input path has wild card.
                var pattern = Path.GetFileName(inputFilePath);
                return Directory.GetFiles(inputDir, pattern);
            }
            else
            {
                // No wild card, file directly specified on cmd line.
                return new string[] { inputFilePath };
            }
        }

        /// <summary>
        /// Expand a razor template in embedded resources to a file.
        /// </summary>
        private static void ExpandResourceToFile<ModelT>(string resourceDir, string resourceName, string outputDir, ModelT model)
        {
            var expanded = ExpandResource(resourceDir, resourceName, model);
            var outputFile = Path.Combine(outputDir, resourceName);
            File.WriteAllText(outputFile, expanded);
        }

        /// <summary>
        /// Expand a razor template in embedded resources.
        /// </summary>
        private static string ExpandResource<ModelT>(string resourceDir, string resourceName, ModelT model)
        {
            var fullResourceName = resourceDir + "." + resourceName;
            using (var templateStream = new StreamReader(Assembly.GetExecutingAssembly().GetManifestResourceStream(fullResourceName)))
            {
                var template = templateStream.ReadToEnd();
                return ExpandTemplate(template, model);
            }
        }

        /// <summary>
        /// Expand a razor template.
        /// </summary>
        private static string ExpandTemplate<ModelT>(string templateText, ModelT model)
        {
            try
            {
                return Razor.Parse(templateText, model);
            }
            catch (TemplateCompilationException ex)
            {
                Console.WriteLine("Template Errors: ");

                foreach (var error in ex.Errors)
                {
                    Console.WriteLine(error);
                }

                throw new Exception("Failed to compile template!");
            }
        }
    }
}
