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

namespace ReportGen
{
    /// <summary>
    /// A line in the CSV file.
    /// </summary>
    public sealed class CsvLine
    {
        /// <summary>
        /// Split a CSV line and return the component columns.
        /// </summary>
        internal static string[] SplitCsvLine(string line)
        {
            var trimmedCols = from column in line.Trim().Split(',') select column.Trim();
            return trimmedCols.TakeWhile((s) => !string.IsNullOrEmpty(s)).ToArray();
        }

        public CsvLine(string lineText)
        {
            this.Columns = SplitCsvLine(lineText);
        }

        public string[] Columns
        {
            get;
            private set;
        }
    }

    /// <summary>
    /// Reads and parses CSV files.
    /// </summary>
    public sealed class CsvFile
    {
        public CsvFile(string filePath)
        {
            var fileLines = File.ReadAllLines(filePath);

            this.Headings = CsvLine.SplitCsvLine(fileLines[0]);

            var lines = new List<CsvLine>();

            for (int lineIndex = 1; lineIndex < fileLines.Length; ++lineIndex)
            {
                lines.Add(new CsvLine(fileLines[lineIndex]));
            }

            this.Lines = lines.ToArray();
        }

        /// <summary>
        /// Array of headings in the CSV file.
        /// </summary>
        public string[] Headings
        {
            get;
            private set;
        }

        /// <summary>
        /// Array of lines in the CSV file.
        /// </summary>
        public CsvLine[] Lines
        {
            get;
            private set;
        }

        /// <summary>
        /// Dump to console output.
        /// </summary>
        public void Dump(TextWriter output)
        {
            output.WriteLine("  Headings:");

            foreach (var heading in this.Headings)
            {
                output.WriteLine("    " + heading);
            }

            output.WriteLine("  Lines:");

            int lineIndex = 0;

            foreach (var line in this.Lines)
            {
                output.WriteLine("    [" + lineIndex + "]");

                int colIndex = 0;

                foreach (var column in line.Columns)
                {
                    output.WriteLine("      [" + colIndex + "] " + column);

                    ++colIndex;
                }

                ++lineIndex;
            }
        }

        /// <summary>
        /// Write the CSV file to Javascript.
        /// Assign the data to the specified global variable.
        /// </summary>
        public void ToCombinedJavaScript(TextWriter output, string variableName)
        {
            output.WriteLine("var " + variableName + " = [");

            var csvColumns = this.Headings;

            ColumnsToJavaScript(output, csvColumns, true);

            foreach (var csvLine in this.Lines)
            {
                output.WriteLine(",");

                ColumnsToJavaScript(output, csvLine.Columns, false);
            }

            output.WriteLine();
            output.WriteLine("];");
        }

        /// <summary>
        /// Write CSV columns to JSON.
        /// </summary>
        private void ColumnsToJavaScript(TextWriter output, string[] csvColumns, bool doQuotes)
        {
            output.Write("[");

            int colIndex = 0;

            foreach (var column in csvColumns)
            {
                if (colIndex > 0)
                {
                    output.Write(", ");
                }

                if (doQuotes)
                {
                    output.Write("\"");
                }

                output.Write(column);

                if (doQuotes)
                {
                    output.Write("\"");
                }

                ++colIndex;
            }

            output.Write("]");
        }

        /// <summary>
        /// Write the CSV file to Javascript.
        /// Assign the data to the specified global variable.
        /// </summary>
        public void ToSeparatedJavaScript(TextWriter output, string variableName)
        {
            output.WriteLine("var " + variableName + " =  [");

            for (int colIndex = 1; colIndex < this.Headings.Length; ++colIndex)
            {
                if (colIndex > 1)
                {
                    output.WriteLine(",");
                }

                output.WriteLine("{");

                var columnName = this.Headings[colIndex];

                output.Write("name: ");
                output.Write("\"");
                output.Write(columnName);
                output.Write("\"");
                output.WriteLine(",");
                output.Write("num_frames: ");
                output.Write(this.Lines.Length);
                output.WriteLine(",");
                output.WriteLine("data: [");

                var csvHeadings = new string[] 
                {
                    this.Headings[0],
                    this.Headings[colIndex],
                };

                ColumnsToJavaScript(output, csvHeadings, true);

                foreach (var csvLine in this.Lines)
                {
                    output.WriteLine(",");

                    var csvColumns = new string[] 
                    {
                        csvLine.Columns[0],
                        csvLine.Columns[colIndex],
                    };

                    ColumnsToJavaScript(output, csvColumns, false);
                }

                output.WriteLine();
                output.WriteLine("]");
                output.Write("}");
            }

            output.WriteLine();
            output.WriteLine("];");
        }
        /// <summary>
        /// Write the Csv file to JSON.
        /// </summary>
        public void ToJSON(TextWriter output)
        {
            output.WriteLine("[");

            var csvColumns = this.Headings;

            ColumnsToJSON(output, csvColumns);

            foreach (var csvLine in this.Lines)
            {
                output.WriteLine(",");

                ColumnsToJSON(output, csvLine.Columns);
            }

            output.WriteLine();
            output.WriteLine("]");
        }

        /// <summary>
        /// Write CSV columns to JSON.
        /// </summary>
        private void ColumnsToJSON(TextWriter output, string[] csvColumns)
        {
            output.Write("[");

            int colIndex = 0;

            foreach (var column in csvColumns)
            {
                if (colIndex > 0)
                {
                    output.Write(", ");
                }

                output.Write("\"");
                output.Write(column);
                output.Write("\"");

                ++colIndex;
            }

            output.Write("]");
        }

    }
}
